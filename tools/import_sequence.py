#!/usr/bin/env python3
"""
import_sequence.py — N64 sequence bytecode importer for Starship (SF64 port).

Given a raw N64 sequence binary (.m64 / .mus / headerless bytes) this tool:
  1. Disassembles the bytecode to human-readable text.
  2. Generates a Starship XML descriptor (ResourceFactoryXMLSequenceV0 format).
  3. Optionally packs the XML + binary into a mod .o2r archive.

Usage:
    # Disassemble only
    python3 tools/import_sequence.py seq_corneria.m64 --disassemble

    # Generate XML descriptor (binary is referenced by path inside archive)
    python3 tools/import_sequence.py seq_corneria.m64 \\
        --asset ast_audio/corneria_custom \\
        --index 2 --medium Ram --cache Temporary

    # Pack XML + binary into a mod archive (requires o2r_builder on PATH)
    python3 tools/import_sequence.py seq_corneria.m64 \\
        --asset ast_audio/corneria_custom \\
        --index 2 --pack --out-dir mods/my_mod

Attributes written to the XML (ResourceFactoryXMLSequenceV0):
    Version      always "0"
    Medium       one of: Ram, Cart, Disk  (default: Ram)
    CachePolicy  one of: Temporary, Persistent, Either, Permanent  (default: Temporary)
    Size         byte count of the raw binary (informational; factory re-reads from file)
    Index        seqId (0–66) this sequence replaces  (default: 0)
    Streamed     always "false" for raw binary imports
    Path         in-archive path to the raw binary (e.g. ast_audio/corneria_custom.m64)

The XML is named <asset>.xml; the binary is copied/renamed to <asset>.<ext>.
"""

import argparse
import os
import shutil
import struct
import sys
import xml.dom.minidom
import xml.etree.ElementTree as ET
from collections import deque

# ---------------------------------------------------------------------------
# N64 sequence bytecode disassembler — recursive / graph-based
#
# The N64 audio engine has three execution levels:
#   SEQ     — sequence player (top level)
#   CHANNEL — per-channel player
#   LAYER   — per-layer note player
#
# Each level reads its own section of the binary starting at a pointer:
#   SEQ:     starts at offset 0
#   CHANNEL: started by  SEQ  opcode 0x90+ch  (ldchan)
#   LAYER:   started by  CHAN opcode 0x90+lay  (ldlayer)
#
# The same byte 0x90+N means *ldchan* at SEQ level and *ldlayer* at CHANNEL
# level. A linear disassembler therefore misses almost all note data.
# This disassembler uses BFS to follow every cross-reference.
# ---------------------------------------------------------------------------

_NOTE_NAMES = ["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"]

def _note_name(pitch):
    octave = pitch // 12 - 1
    return f"{_NOTE_NAMES[pitch % 12]}{octave}"


# ── Primitive readers ────────────────────────────────────────────────────────

def _read_u8(data, pc):
    if pc >= len(data):
        raise IndexError(f"PC={pc:#06x} out of range (size={len(data):#x})")
    return data[pc], pc + 1

def _read_s8(data, pc):
    v, pc = _read_u8(data, pc)
    return (v - 256) if v >= 128 else v, pc

def _read_u16be(data, pc):
    if pc + 1 >= len(data):
        raise IndexError(f"PC={pc:#06x} out of range reading u16")
    return (data[pc] << 8) | data[pc + 1], pc + 2

def _read_cu16(data, pc):
    """Compressed u16: MSB set → two-byte value; else one-byte value."""
    hi, pc = _read_u8(data, pc)
    if hi & 0x80:
        lo, pc = _read_u8(data, pc)
        return ((hi & 0x7F) << 8) | lo, pc
    return hi, pc


# ── Shared control-flow opcodes (0xC0-0xFF, identical at SEQ and CHANNEL) ───

def _shared_ctrl(data, pc, cmd, orig_pc, ctx, ln, refs):
    """Decode one shared control-flow opcode.

    Returns (mnemonic_string, new_pc, is_terminal).
    Returns (None, pc, False) when cmd is not a shared opcode.
    Appends to refs: list of (offset, ctx, label, large_notes).
    """
    if cmd == 0xFF:
        return "return", pc, True
    if cmd == 0xFE:
        return "wait_1tick", pc, True          # exits script tick
    if cmd == 0xFD:
        delay, pc = _read_cu16(data, pc)
        return f"wait {delay}", pc, True       # exits script tick
    if cmd == 0xFC:
        off, pc = _read_u16be(data, pc)
        refs.append((off, ctx, f"sub_{off:04X}", ln))
        return f"call @{off:#06x}", pc, False
    if cmd == 0xFB:
        off, pc = _read_u16be(data, pc)
        refs.append((off, ctx, f"@{off:04X}", ln))
        return f"goto @{off:#06x}", pc, True   # follow at worklist level
    if cmd == 0xFA:
        off, pc = _read_u16be(data, pc)
        refs.append((off, ctx, f"@{off:04X}", ln))
        return f"jump_if_nonzero @{off:#06x}", pc, False
    if cmd == 0xF9:
        off, pc = _read_u16be(data, pc)
        refs.append((off, ctx, f"@{off:04X}", ln))
        return f"jump_if_neg @{off:#06x}", pc, False
    if cmd == 0xF8:
        n, pc = _read_u8(data, pc)
        return f"loop {n}x", pc, False
    if cmd == 0xF7:
        return "loop_end", pc, False
    if cmd == 0xF6:
        return "loop_break", pc, True
    if cmd == 0xF5:
        off, pc = _read_u16be(data, pc)
        refs.append((off, ctx, f"@{off:04X}", ln))
        return f"jump_if_nonneg @{off:#06x}", pc, False
    if cmd == 0xF4:
        rel, pc = _read_s8(data, pc)
        tgt = pc + rel
        refs.append((tgt, ctx, f"@{tgt:04X}", ln))
        return f"branch_always {rel:+d}  (@{tgt:04X})", pc, False
    if cmd == 0xF3:
        rel, pc = _read_s8(data, pc)
        tgt = pc + rel
        refs.append((tgt, ctx, f"@{tgt:04X}", ln))
        return f"branch_if_zero {rel:+d}  (@{tgt:04X})", pc, False
    if cmd == 0xF2:
        rel, pc = _read_s8(data, pc)
        tgt = pc + rel
        refs.append((tgt, ctx, f"@{tgt:04X}", ln))
        return f"branch_if_neg {rel:+d}  (@{tgt:04X})", pc, False
    if cmd == 0xF1:
        n, pc = _read_u8(data, pc)
        return f"pool_fill {n}", pc, False
    if cmd == 0xF0:
        return "pool_clear", pc, False
    return None, pc, False


# ── SEQ level ────────────────────────────────────────────────────────────────

def _disasm_seq_block(data, pc, refs):
    lines = []
    visited = set()
    while pc < len(data):
        if pc in visited: break
        visited.add(pc)
        orig_pc = pc
        try:
            cmd, pc = _read_u8(data, pc)
        except IndexError:
            break

        if cmd >= 0xF0:
            mn, pc, term = _shared_ctrl(data, pc, cmd, orig_pc, "seq", False, refs)
            lines.append(f"  [{orig_pc:04X}]  {mn or f'seq_0x{cmd:02X}'}")
            if term: break
            continue

        hi, lo = cmd & 0xF0, cmd & 0x0F

        if hi == 0x90:                         # ldchan
            off, pc = _read_u16be(data, pc)
            refs.append((off, "channel", f"channel_{lo}_{off:04X}", False))
            lines.append(f"  [{orig_pc:04X}]  ldchan ch={lo} @{off:#06x}")
        elif hi == 0xA0:                       # enable_channel (alt)
            off, pc = _read_u16be(data, pc)
            refs.append((off, "channel", f"channel_{lo}_{off:04X}", False))
            lines.append(f"  [{orig_pc:04X}]  enable_chan ch={lo} @{off:#06x}")
        elif cmd == 0xDF:
            lines.append(f"  [{orig_pc:04X}]  transposition_reset")
        elif cmd == 0xDE:
            v, pc = _read_s8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  transposition += {v:+d}")
        elif cmd == 0xDD:
            t, pc = _read_u8(data, pc)
            bpm = t * 0x30 / 0x80 * 60
            lines.append(f"  [{orig_pc:04X}]  tempo {t}  (~{bpm:.1f} BPM)")
        elif cmd == 0xDC:
            v, pc = _read_s8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  tempo_change {v:+d}")
        elif cmd == 0xDB:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  seq_volume {v}/127")
        elif cmd == 0xDA:
            s, pc = _read_u8(data, pc)
            v, pc = _read_u16be(data, pc)
            lines.append(f"  [{orig_pc:04X}]  fade state={s} timer={v}")
        elif cmd == 0xD9:
            v, pc = _read_s8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  fade_volume_mod {v}")
        elif cmd == 0xD8:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  mute_seq_vol {v}")
        elif cmd == 0xD7:
            mask, pc = _read_u16be(data, pc)
            chs = [i for i in range(16) if mask & (1 << (15 - i))]
            lines.append(f"  [{orig_pc:04X}]  enablechans mask={mask:#06x} {chs}")
        elif cmd == 0xD6:
            mask, pc = _read_u16be(data, pc)
            lines.append(f"  [{orig_pc:04X}]  disablechans mask={mask:#06x}")
        elif cmd == 0xD5:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  mute_vol_scale {v}/127")
        elif cmd == 0xD4:
            lines.append(f"  [{orig_pc:04X}]  mute")
        elif cmd == 0xD3:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  mute_behavior {v:#04x}")
        elif cmd == 0xD2:
            off, pc = _read_u16be(data, pc)
            lines.append(f"  [{orig_pc:04X}]  shortnote_gate_table @{off:#06x}")
        elif cmd == 0xD1:
            off, pc = _read_u16be(data, pc)
            lines.append(f"  [{orig_pc:04X}]  shortnote_vel_table @{off:#06x}")
        elif cmd == 0xD0:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  note_alloc_policy {v}")
        elif cmd == 0xCC:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  load_u8 {v}")
        elif cmd == 0xC9:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  arith_and {v:#04x}")
        elif cmd == 0xC8:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  arith_sub {v}")
        elif cmd == 0xC7:
            v, pc = _read_u8(data, pc)
            off, pc = _read_u16be(data, pc)
            lines.append(f"  [{orig_pc:04X}]  dynwrite @{off:#06x} += {v}")
        elif hi in (0x00, 0x10, 0x50, 0x70, 0x80):
            lines.append(f"  [{orig_pc:04X}]  io_{cmd:#04x} ch={lo}")
        elif hi == 0x20:
            off, pc = _read_u16be(data, pc)
            lines.append(f"  [{orig_pc:04X}]  enable_chan_alt ch={lo} @{off:#06x}")
        elif hi in (0x30, 0x40):
            port, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  ch_io_{cmd:#04x} ch={lo} port={port}")
        elif hi == 0x60:
            lines.append(f"  [{orig_pc:04X}]  channel_delay ch={lo}")
        elif hi == 0xB0:
            off, pc = _read_u16be(data, pc)
            lines.append(f"  [{orig_pc:04X}]  ldlayer_dyn ch={lo} @{off:#06x}")
        else:
            lines.append(f"  [{orig_pc:04X}]  seq_0x{cmd:02X}")
    return lines


# ── CHANNEL level ─────────────────────────────────────────────────────────────

def _disasm_channel_block(data, pc, refs):
    """Returns (lines, final_large_notes)."""
    lines   = []
    visited = set()
    ln      = False          # largeNotes state — tracks C3/C4 opcodes

    while pc < len(data):
        if pc in visited: break
        visited.add(pc)
        orig_pc = pc
        try:
            cmd, pc = _read_u8(data, pc)
        except IndexError:
            break

        if cmd >= 0xF0:
            mn, pc, term = _shared_ctrl(data, pc, cmd, orig_pc, "channel", ln, refs)
            lines.append(f"  [{orig_pc:04X}]  {mn or f'ch_0x{cmd:02X}'}")
            if term: break
            continue

        hi, lo = cmd & 0xF0, cmd & 0x0F

        if hi == 0x90:                         # ldlayer  (same byte as ldchan at seq level)
            off, pc = _read_u16be(data, pc)
            refs.append((off, "layer", f"layer_{off:04X}", ln))
            flag = "  ; large_notes" if ln else ""
            lines.append(f"  [{orig_pc:04X}]  ldlayer layer={lo} @{off:#06x}{flag}")
        elif hi == 0xA0:
            lines.append(f"  [{orig_pc:04X}]  free_layer layer={lo}")
        elif hi == 0xB0:
            lines.append(f"  [{orig_pc:04X}]  ldlayer_dyn layer={lo}")
        elif cmd == 0xEF:
            v, pc  = _read_u16be(data, pc)
            v2, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  ch_0xEF @{v:#06x} {v2}")
        elif cmd == 0xEE:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  pitchbend_2semi {v}")
        elif cmd == 0xED:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  reverb_index {v}")
        elif cmd == 0xEC:
            lines.append(f"  [{orig_pc:04X}]  vibrato_off")
        elif cmd == 0xEB:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  set_font_lookup {v}")
        elif cmd == 0xEA:
            lines.append(f"  [{orig_pc:04X}]  stop_script")
            break
        elif cmd == 0xE9:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  note_priority {v}")
        elif cmd == 0xE8:
            vals = []
            for _ in range(8):
                v, pc = _read_u8(data, pc); vals.append(v)
            lines.append(f"  [{orig_pc:04X}]  load_config_inline {vals}")
        elif cmd == 0xE7:
            off, pc = _read_u16be(data, pc)
            lines.append(f"  [{orig_pc:04X}]  load_config_block @{off:#06x}")
        elif cmd == 0xE6:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  book_offset {v}")
        elif cmd == 0xE5:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  some_priority {v}")
        elif cmd == 0xE4:
            lines.append(f"  [{orig_pc:04X}]  call_dyntable")
        elif cmd == 0xE3:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  vibrato_delay {v * 0x10}")
        elif cmd == 0xE2:
            a, pc = _read_u8(data, pc)
            b, pc = _read_u8(data, pc)
            c, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  vibrato_depth_ramp {a}→{b} delay={c}")
        elif cmd == 0xE1:
            a, pc = _read_u8(data, pc)
            b, pc = _read_u8(data, pc)
            c, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  vibrato_rate_ramp {a}→{b} delay={c}")
        elif cmd == 0xE0:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  volume_mod {v}/128")
        elif cmd == 0xDF:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  volume {v}/127")
        elif cmd == 0xDE:
            v, pc = _read_u16be(data, pc)
            lines.append(f"  [{orig_pc:04X}]  freq_mod {v}")
        elif cmd == 0xDD:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  pan {v}/127")
        elif cmd == 0xDC:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  pan_weight {v}")
        elif cmd == 0xDB:
            v, pc = _read_s8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  transposition {v:+d}")
        elif cmd == 0xDA:
            off, pc = _read_u16be(data, pc)
            lines.append(f"  [{orig_pc:04X}]  adsr_envelope @{off:#06x}")
        elif cmd == 0xD9:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  adsr_decay {v}")
        elif cmd == 0xD8:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  vibrato_depth {v * 8}")
        elif cmd == 0xD7:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  vibrato_rate {v * 32}")
        elif cmd in (0xD5, 0xD6):
            lines.append(f"  [{orig_pc:04X}]  nop_0x{cmd:02X}")
        elif cmd == 0xD4:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  reverb {v}")
        elif cmd == 0xD3:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  pitchbend_1oct {v}")
        elif cmd == 0xD2:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  adsr_sustain {v}")
        elif cmd == 0xD1:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  note_alloc {v}")
        elif cmd == 0xD0:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  stereo {v:#04x}")
        elif cmd == 0xCF:
            off, pc = _read_u16be(data, pc)
            lines.append(f"  [{orig_pc:04X}]  write_unkc4 @{off:#06x}")
        elif cmd == 0xCE:
            v, pc = _read_u16be(data, pc)
            lines.append(f"  [{orig_pc:04X}]  store_u16 {v:#06x}")
        elif cmd == 0xCD:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  disable_chan {v}")
        elif cmd == 0xCC:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  load_u8 {v}")
        elif cmd == 0xCB:
            off, pc = _read_u16be(data, pc)
            lines.append(f"  [{orig_pc:04X}]  dynread @{off:#06x}")
        elif cmd == 0xCA:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  mute_behavior {v:#04x}")
        elif cmd == 0xC9:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  arith_and {v:#04x}")
        elif cmd == 0xC8:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  arith_sub {v}")
        elif cmd == 0xC7:
            v, pc = _read_u8(data, pc)
            off, pc = _read_u16be(data, pc)
            lines.append(f"  [{orig_pc:04X}]  dynwrite @{off:#06x} += {v}")
        elif cmd == 0xC6:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  set_font {v}")
        elif cmd == 0xC5:
            lines.append(f"  [{orig_pc:04X}]  dyntable_index")
        elif cmd == 0xC4:
            ln = True
            lines.append(f"  [{orig_pc:04X}]  large_notes_on")
        elif cmd == 0xC3:
            ln = False
            lines.append(f"  [{orig_pc:04X}]  large_notes_off")
        elif cmd == 0xC2:
            off, pc = _read_u16be(data, pc)
            lines.append(f"  [{orig_pc:04X}]  dyntable_set @{off:#06x}")
        elif cmd == 0xC1:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  set_instrument {v}")
        elif hi in (0x30, 0x40):
            port, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  io_{cmd:#04x} layer={lo} port={port}")
        else:
            lines.append(f"  [{orig_pc:04X}]  ch_{cmd:#04x} layer={lo}")
    return lines, ln


# ── LAYER level ───────────────────────────────────────────────────────────────

def _disasm_layer_block(data, pc, refs, large_notes=False):
    lines       = []
    visited     = set()
    last_delay  = None
    def_delay   = None

    while pc < len(data):
        if pc in visited: break
        visited.add(pc)
        orig_pc = pc
        try:
            cmd, pc = _read_u8(data, pc)
        except IndexError:
            break

        if cmd == 0xFF:
            lines.append(f"  [{orig_pc:04X}]  end_layer"); break
        if cmd == 0xFE:
            lines.append(f"  [{orig_pc:04X}]  loop_back");  break
        if cmd == 0xFD:
            d, pc = _read_cu16(data, pc)
            last_delay = d
            lines.append(f"  [{orig_pc:04X}]  delay {d}")
            continue
        if cmd == 0xFC:
            off, pc = _read_u16be(data, pc)
            refs.append((off, "layer", f"sub_{off:04X}", large_notes))
            lines.append(f"  [{orig_pc:04X}]  call @{off:#06x}")
            continue
        if cmd == 0xFB:
            off, pc = _read_u16be(data, pc)
            refs.append((off, "layer", f"@{off:04X}", large_notes))
            lines.append(f"  [{orig_pc:04X}]  goto @{off:#06x}"); break
        if cmd == 0xF8:
            n, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  loop {n}x"); continue
        if cmd == 0xF7:
            lines.append(f"  [{orig_pc:04X}]  loop_end"); continue
        if cmd == 0xF6:
            lines.append(f"  [{orig_pc:04X}]  loop_break"); break
        if 0xD0 <= cmd <= 0xDF:
            lines.append(f"  [{orig_pc:04X}]  vel_table[{cmd & 0xF}]"); continue
        if 0xE0 <= cmd <= 0xEF:
            lines.append(f"  [{orig_pc:04X}]  gate_table[{cmd & 0xF}]"); continue
        if cmd == 0xCD:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  stereo {v:#04x}"); continue
        if cmd == 0xCC:
            lines.append(f"  [{orig_pc:04X}]  bit1_on"); continue
        if cmd == 0xCB:
            off, pc = _read_u16be(data, pc)
            di, pc  = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  envelope @{off:#06x} decay={di}"); continue
        if cmd == 0xCA:
            v, pc = _read_s8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  transpose {v:+d}"); continue
        if cmd == 0xC9:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  pan {v}/127"); continue
        if cmd == 0xC8:
            lines.append(f"  [{orig_pc:04X}]  portamento_off"); continue
        if cmd == 0xC7:
            mode, pc = _read_u8(data, pc)
            note, pc = _read_u8(data, pc)
            t, pc    = _read_cu16(data, pc) if (mode & 0x80) else _read_u8(data, pc)
            lines.append(
                f"  [{orig_pc:04X}]  portamento mode={mode:#04x} "
                f"note={_note_name(note)} time={t}"); continue
        if cmd == 0xC6:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  set_instrument {v}"); continue
        if cmd == 0xC5:
            lines.append(f"  [{orig_pc:04X}]  cont_notes_off"); continue
        if cmd == 0xC4:
            lines.append(f"  [{orig_pc:04X}]  cont_notes_on"); continue
        if cmd == 0xC3:
            d, pc = _read_cu16(data, pc)
            def_delay = d
            lines.append(f"  [{orig_pc:04X}]  set_default_delay {d}"); continue
        if cmd == 0xC2:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  set_gate {v}"); continue
        if cmd == 0xC1:
            v, pc = _read_u8(data, pc)
            lines.append(f"  [{orig_pc:04X}]  set_velocity {v}"); continue
        if cmd > 0xC0:
            lines.append(f"  [{orig_pc:04X}]  layer_0x{cmd:02X}"); continue

        # ── Note bytes (cmd <= 0xC0) ─────────────────────────────────────────
        pitch   = cmd & 0x3F
        variant = cmd >> 6          # 0 = full, 1 = short/alt, 2 = repeat
        pname   = _note_name(pitch)

        if not large_notes:
            # Short-note format: no per-note vel/gate
            if variant == 0:                          # full: explicit delay
                d, pc = _read_cu16(data, pc)
                last_delay = d
                lines.append(f"  [{orig_pc:04X}]  note {pname} delay={d}")
            elif variant == 1:                        # short: uses default delay
                dd = def_delay if def_delay is not None else "default"
                lines.append(f"  [{orig_pc:04X}]  note {pname} delay=default({dd})")
            else:                                     # repeat: reuse last delay
                lines.append(f"  [{orig_pc:04X}]  note {pname} delay=last({last_delay})")
        else:
            # Large-note format: explicit vel + gate per note
            if variant == 0:
                d, pc   = _read_cu16(data, pc)
                vel, pc = _read_u8(data, pc)
                gat, pc = _read_u8(data, pc)
                last_delay = d
                lines.append(f"  [{orig_pc:04X}]  note {pname} delay={d} vel={vel} gate={gat}")
            elif variant == 1:                        # 0x40: explicit delay, gate=0
                d, pc   = _read_cu16(data, pc)
                vel, pc = _read_u8(data, pc)
                last_delay = d
                lines.append(f"  [{orig_pc:04X}]  note {pname} delay={d} vel={vel} gate=0")
            else:                                     # 0x80: repeat delay
                vel, pc = _read_u8(data, pc)
                gat, pc = _read_u8(data, pc)
                lines.append(f"  [{orig_pc:04X}]  note {pname} delay=last({last_delay}) vel={vel} gate={gat}")

    return lines


# ── BFS graph disassembler ────────────────────────────────────────────────────

def disassemble(data):
    """Full recursive disassembly of raw N64 sequence bytes.

    Follows every ldchan / ldlayer / call / jump cross-reference to produce
    complete output for all SEQ, CHANNEL, and LAYER blocks.
    """
    blocks   = {}        # offset -> (label, ctx, lines)
    worklist = deque([(0, "seq", "seq", False)])

    MAX_BLOCKS = 4096
    while worklist and len(blocks) < MAX_BLOCKS:
        off, ctx, label, ln = worklist.popleft()
        if off in blocks or off >= len(data):
            continue

        refs = []
        try:
            if ctx == "seq":
                lines = _disasm_seq_block(data, off, refs)
            elif ctx == "channel":
                lines, _ = _disasm_channel_block(data, off, refs)
            else:                                     # layer
                lines = _disasm_layer_block(data, off, refs, ln)
        except Exception as exc:
            lines = [f"  [{off:04X}]  ; ERROR: {exc}"]

        blocks[off] = (label, ctx, lines)
        for r in refs:
            if r[0] not in blocks:
                worklist.append(r)

    ctx_tag = {"seq": "SEQ", "channel": "CHANNEL", "layer": "LAYER"}
    out = [f"Sequence size: {len(data)} bytes ({len(data):#06x})", ""]
    for off in sorted(blocks):
        label, ctx, lines = blocks[off]
        tag   = ctx_tag.get(ctx, ctx.upper())
        ruler = "─" * max(0, 56 - len(label) - len(tag))
        out.append(f"; ── {label}  [{off:#06x}]  {tag}  {ruler}")
        out.extend(lines)
        out.append("")

    if len(blocks) >= MAX_BLOCKS:
        out.append("; (output truncated — MAX_BLOCKS limit reached)")

    return "\n".join(out)


# ---------------------------------------------------------------------------
# XML generation (matches ResourceFactoryXMLSequenceV0)
# ---------------------------------------------------------------------------

_VALID_MEDIUM       = {"Ram", "Cart", "Disk"}
_VALID_CACHE_POLICY = {"Temporary", "Persistent", "Either", "Permanent"}


def make_xml(asset_path_no_ext, binary_ext, seq_size, seq_index, medium, cache_policy):
    """
    Build the XML descriptor consumed by ResourceFactoryXMLSequenceV0.

    asset_path_no_ext  – in-archive path without extension, e.g. "ast_audio/corneria_custom"
    binary_ext         – file extension of the raw binary, e.g. "m64"
    seq_size           – byte length of the raw binary (informational)
    seq_index          – seqId this sequence replaces (0–66)
    medium             – one of Ram / Cart / Disk
    cache_policy       – one of Temporary / Persistent / Either / Permanent
    """
    binary_path = f"{asset_path_no_ext}.{binary_ext}"

    root = ET.Element("Sequence")
    root.set("Version",     "0")
    root.set("Medium",      medium)
    root.set("CachePolicy", cache_policy)
    root.set("Size",        str(seq_size))
    root.set("Index",       str(seq_index))
    root.set("Streamed",    "false")
    root.set("Path",        binary_path)

    raw = ET.tostring(root, encoding="unicode")
    dom = xml.dom.minidom.parseString(raw)
    return dom.toprettyxml(indent="  ", encoding=None).replace('<?xml version="1.0" ?>\n', "")


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(
        description="Import a raw N64 sequence binary for the Starship (SF64) port."
    )
    parser.add_argument("binary",
        help="Raw N64 sequence binary (.m64, .mus, or any extension).")
    parser.add_argument("--disassemble", action="store_true",
        help="Print a disassembly of the sequence bytecode and exit.")
    parser.add_argument("--asset", default=None,
        help="In-archive asset path WITHOUT extension "
             "(e.g. ast_audio/corneria_custom). Required unless --disassemble.")
    parser.add_argument("--index", type=int, default=0,
        help="seqId (0–66) that this sequence replaces (default: 0).")
    parser.add_argument("--medium", default="Ram", choices=sorted(_VALID_MEDIUM),
        help="Storage medium (default: Ram).")
    parser.add_argument("--cache", default="Temporary",
        choices=sorted(_VALID_CACHE_POLICY),
        help="Cache policy (default: Temporary).")
    parser.add_argument("--out-dir", default=None,
        help="Output directory. Defaults to the directory of the input binary.")
    parser.add_argument("--pack", action="store_true",
        help="(NYI) Pack XML + binary into a .o2r mod archive after generating XML.")
    args = parser.parse_args()

    bin_path = os.path.abspath(args.binary)
    if not os.path.isfile(bin_path):
        print(f"error: file not found: {bin_path}", file=sys.stderr)
        sys.exit(1)

    with open(bin_path, "rb") as f:
        data = f.read()

    # ── Disassemble-only mode ─────────────────────────────────────────────────
    if args.disassemble:
        print(disassemble(bytearray(data)))
        return

    # ── XML generation ────────────────────────────────────────────────────────
    if args.asset is None:
        print("error: --asset is required when not using --disassemble.", file=sys.stderr)
        sys.exit(1)

    if args.index < 0 or args.index > 66:
        print(f"warning: --index {args.index} is outside the known range 0–66.", file=sys.stderr)

    ext = os.path.splitext(bin_path)[1].lstrip(".") or "m64"
    xml_content = make_xml(args.asset, ext, len(data), args.index, args.medium, args.cache)

    if args.out_dir is not None:
        out_dir = os.path.abspath(args.out_dir)
    else:
        out_dir = os.path.dirname(bin_path)

    asset_rel_dir = os.path.dirname(args.asset)
    dest_dir = os.path.join(out_dir, asset_rel_dir)
    os.makedirs(dest_dir, exist_ok=True)

    asset_basename = os.path.basename(args.asset)
    xml_out    = os.path.join(dest_dir, f"{asset_basename}.xml")
    binary_out = os.path.join(dest_dir, f"{asset_basename}.{ext}")

    with open(xml_out, "w", encoding="utf-8") as f:
        f.write(xml_content)

    if os.path.abspath(bin_path) != os.path.abspath(binary_out):
        shutil.copy2(bin_path, binary_out)

    print(f"Sequence size : {len(data)} bytes")
    print(f"Seq index     : {args.index}")
    print(f"Medium        : {args.medium}")
    print(f"Cache policy  : {args.cache}")
    print(f"XML written   : {xml_out}")
    print(f"Binary copied : {binary_out}")
    print()
    print("Next steps:")
    print(f"  1. Add both files to your .o2r mod archive:")
    print(f"       {args.asset}.xml")
    print(f"       {args.asset}.{ext}")
    print(f"  2. The engine will override seqId {args.index} automatically when your mod is loaded.")
    if args.pack:
        print()
        print("note: --pack not yet implemented; pack manually with your o2r_builder workflow.")


if __name__ == "__main__":
    main()
