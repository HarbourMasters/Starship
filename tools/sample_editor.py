#!/usr/bin/env python3
"""
Starship Sample Editor — browse, export, and replace audio samples in an o2r archive.

Run without arguments (or with `gui`) to open the graphical interface.
All subcommands are also available on the CLI:

  list    [--filter TEXT] [--codec N]
  info    <asset-path>
  export  <asset-path> [--out FILE] [--decode]
  play    <asset-path>
  replace <asset-path> --input AUDIO [--out-dir DIR]
  gui     [archive]
"""

from __future__ import annotations

import argparse
import array
import json
import re
import os
import shutil
import struct
import subprocess
import sys
import tempfile
import threading
import wave
import xml.dom.minidom
import xml.etree.ElementTree as ET
import zipfile

# ─── constants ────────────────────────────────────────────────────────────────

OTR_HEADER_SIZE = 64
BODY_OFFSET     = OTR_HEADER_SIZE
SAMPLE_RES_TYPE = 0x41554643   # Torch::ResourceType::Sample      (AUFC)
LOOP_RES_TYPE   = 0x4150434C   # Torch::ResourceType::AdpcmLoop   (APCL)
BOOK_RES_TYPE   = 0x41504342   # Torch::ResourceType::AdpcmBook   (APCB)
INST_RES_TYPE   = 0x494E5354   # Torch::ResourceType::Instrument  (INST)
DRUM_RES_TYPE   = 0x4452554D   # Torch::ResourceType::Drum        (DRUM)
FONT_RES_TYPE   = 0x53464E54   # Torch::ResourceType::SoundFont   (SFNT)

CODEC_NAMES  = {0: "ADPCM", 1: "S8", 2: "S16MEM", 3: "SMALL_ADPCM", 4: "REVERB", 5: "S16"}
MEDIUM_NAMES = {0: "Ram",   1: "Unk", 2: "Cart",   3: "Disk",        5: "RamUnloaded"}

# N64 VADPCM: each 9-byte frame decodes to 16 S16 samples
ADPCM_FRAME_BYTES   = 9
ADPCM_FRAME_SAMPLES = 16

AUDIO_REF_HZ  = 32000.0
MIXER_RATE_HZ = 32000

LOOP_INFINITE = 0xFFFFFFFF

# CRC-64 table — matches libultraship/src/ship/utils/StrHash64.cpp exactly.
# Used to map archive entry paths to the loop_hash/book_hash stored in sample binaries.
_CRC64_TABLE = (
    0x0000000000000000, 0x42f0e1eba9ea3693, 0x85e1c3d753d46d26, 0xc711223cfa3e5bb5,
    0x493366450e42ecdf, 0x0bc387aea7a8da4c, 0xccd2a5925d9681f9, 0x8e224479f47cb76a,
    0x9266cc8a1c85d9be, 0xd0962d61b56fef2d, 0x17870f5d4f51b498, 0x5577eeb6e6bb820b,
    0xdb55aacf12c73561, 0x99a54b24bb2d03f2, 0x5eb4691841135847, 0x1c4488f3e8f96ed4,
    0x663d78ff90e185ef, 0x24cd9914390bb37c, 0xe3dcbb28c335e8c9, 0xa12c5ac36adfde5a,
    0x2f0e1eba9ea36930, 0x6dfeff5137495fa3, 0xaaefdd6dcd770416, 0xe81f3c86649d3285,
    0xf45bb4758c645c51, 0xb6ab559e258e6ac2, 0x71ba77a2dfb03177, 0x334a9649765a07e4,
    0xbd68d2308226b08e, 0xff9833db2bcc861d, 0x388911e7d1f2dda8, 0x7a79f00c7818eb3b,
    0xcc7af1ff21c30bde, 0x8e8a101488293d4d, 0x499b3228721766f8, 0x0b6bd3c3dbfd506b,
    0x854997ba2f81e701, 0xc7b97651866bd192, 0x00a8546d7c558a27, 0x4258b586d5bfbcb4,
    0x5e1c3d753d46d260, 0x1cecdc9e94ace4f3, 0xdbfdfea26e92bf46, 0x990d1f49c77889d5,
    0x172f5b3033043ebf, 0x55dfbadb9aee082c, 0x92ce98e760d05399, 0xd03e790cc93a650a,
    0xaa478900b1228e31, 0xe8b768eb18c8b8a2, 0x2fa64ad7e2f6e317, 0x6d56ab3c4b1cd584,
    0xe374ef45bf6062ee, 0xa1840eae168a547d, 0x66952c92ecb40fc8, 0x2465cd79455e395b,
    0x3821458aada7578f, 0x7ad1a461044d611c, 0xbdc0865dfe733aa9, 0xff3067b657990c3a,
    0x711223cfa3e5bb50, 0x33e2c2240a0f8dc3, 0xf4f3e018f031d676, 0xb60301f359dbe0e5,
    0xda050215ea6c212f, 0x98f5e3fe438617bc, 0x5fe4c1c2b9b84c09, 0x1d14202910527a9a,
    0x93366450e42ecdf0, 0xd1c685bb4dc4fb63, 0x16d7a787b7faa0d6, 0x5427466c1e109645,
    0x4863ce9ff6e9f891, 0x0a932f745f03ce02, 0xcd820d48a53d95b7, 0x8f72eca30cd7a324,
    0x0150a8daf8ab144e, 0x43a04931514122dd, 0x84b16b0dab7f7968, 0xc6418ae602954ffb,
    0xbc387aea7a8da4c0, 0xfec89b01d3679253, 0x39d9b93d2959c9e6, 0x7b2958d680b3ff75,
    0xf50b1caf74cf481f, 0xb7fbfd44dd257e8c, 0x70eadf78271b2539, 0x321a3e938ef113aa,
    0x2e5eb66066087d7e, 0x6cae578bcfe24bed, 0xabbf75b735dc1058, 0xe94f945c9c3626cb,
    0x676dd025684a91a1, 0x259d31cec1a0a732, 0xe28c13f23b9efc87, 0xa07cf2199274ca14,
    0x167ff3eacbaf2af1, 0x548f120162451c62, 0x939e303d987b47d7, 0xd16ed1d631917144,
    0x5f4c95afc5edc62e, 0x1dbc74446c07f0bd, 0xdaad56789639ab08, 0x985db7933fd39d9b,
    0x84193f60d72af34f, 0xc6e9de8b7ec0c5dc, 0x01f8fcb784fe9e69, 0x43081d5c2d14a8fa,
    0xcd2a5925d9681f90, 0x8fdab8ce70822903, 0x48cb9af28abc72b6, 0x0a3b7b1923564425,
    0x70428b155b4eaf1e, 0x32b26afef2a4998d, 0xf5a348c2089ac238, 0xb753a929a170f4ab,
    0x3971ed50550c43c1, 0x7b810cbbfce67552, 0xbc902e8706d82ee7, 0xfe60cf6caf321874,
    0xe224479f47cb76a0, 0xa0d4a674ee214033, 0x67c58448141f1b86, 0x253565a3bdf52d15,
    0xab1721da49899a7f, 0xe9e7c031e063acec, 0x2ef6e20d1a5df759, 0x6c0603e6b3b7c1ca,
    0xf6fae5c07d3274cd, 0xb40a042bd4d8425e, 0x731b26172ee619eb, 0x31ebc7fc870c2f78,
    0xbfc9838573709812, 0xfd39626eda9aae81, 0x3a28405220a4f534, 0x78d8a1b9894ec3a7,
    0x649c294a61b7ad73, 0x266cc8a1c85d9be0, 0xe17dea9d3263c055, 0xa38d0b769b89f6c6,
    0x2daf4f0f6ff541ac, 0x6f5faee4c61f773f, 0xa84e8cd83c212c8a, 0xeabe6d3395cb1a19,
    0x90c79d3fedd3f122, 0xd2377cd44439c7b1, 0x15265ee8be079c04, 0x57d6bf0317edaa97,
    0xd9f4fb7ae3911dfd, 0x9b041a914a7b2b6e, 0x5c1538adb04570db, 0x1ee5d94619af4648,
    0x02a151b5f156289c, 0x4051b05e58bc1e0f, 0x87409262a28245ba, 0xc5b073890b687329,
    0x4b9237f0ff14c443, 0x0962d61b56fef2d0, 0xce73f427acc0a965, 0x8c8315cc052a9ff6,
    0x3a80143f5cf17f13, 0x7870f5d4f51b4980, 0xbf61d7e80f251235, 0xfd913603a6cf24a6,
    0x73b3727a52b393cc, 0x31439391fb59a55f, 0xf652b1ad0167feea, 0xb4a25046a88dc879,
    0xa8e6d8b54074a6ad, 0xea16395ee99e903e, 0x2d071b6213a0cb8b, 0x6ff7fa89ba4afd18,
    0xe1d5bef04e364a72, 0xa3255f1be7dc7ce1, 0x64347d271de22754, 0x26c49cccb40811c7,
    0x5cbd6cc0cc10fafc, 0x1e4d8d2b65facc6f, 0xd95caf179fc497da, 0x9bac4efc362ea149,
    0x158e0a85c2521623, 0x577eeb6e6bb820b0, 0x906fc95291867b05, 0xd29f28b9386c4d96,
    0xcedba04ad0952342, 0x8c2b41a1797f15d1, 0x4b3a639d83414e64, 0x09ca82762aab78f7,
    0x87e8c60fded7cf9d, 0xc51827e4773df90e, 0x020905d88d03a2bb, 0x40f9e43324e99428,
    0x2cffe7d5975e55e2, 0x6e0f063e3eb46371, 0xa91e2402c48a38c4, 0xebeec5e96d600e57,
    0x65cc8190991cb93d, 0x273c607b30f68fae, 0xe02d4247cac8d41b, 0xa2dda3ac6322e288,
    0xbe992b5f8bdb8c5c, 0xfc69cab42231bacf, 0x3b78e888d80fe17a, 0x7988096371e5d7e9,
    0xf7aa4d1a85996083, 0xb55aacf12c735610, 0x724b8ecdd64d0da5, 0x30bb6f267fa73b36,
    0x4ac29f2a07bfd00d, 0x08327ec1ae55e69e, 0xcf235cfd546bbd2b, 0x8dd3bd16fd818bb8,
    0x03f1f96f09fd3cd2, 0x41011884a0170a41, 0x86103ab85a2951f4, 0xc4e0db53f3c36767,
    0xd8a453a01b3a09b3, 0x9a54b24bb2d03f20, 0x5d45907748ee6495, 0x1fb5719ce1045206,
    0x919735e51578e56c, 0xd367d40ebc92d3ff, 0x1476f63246ac884a, 0x568617d9ef46bed9,
    0xe085162ab69d5e3c, 0xa275f7c11f7768af, 0x6564d5fde549331a, 0x279434164ca30589,
    0xa9b6706fb8dfb2e3, 0xeb46918411358470, 0x2c57b3b8eb0bdfc5, 0x6ea7525342e1e956,
    0x72e3daa0aa188782, 0x30133b4b03f2b111, 0xf7021977f9cceaa4, 0xb5f2f89c5026dc37,
    0x3bd0bce5a45a6b5d, 0x79205d0e0db05dce, 0xbe317f32f78e067b, 0xfcc19ed95e6430e8,
    0x86b86ed5267cdbd3, 0xc4488f3e8f96ed40, 0x0359ad0275a8b6f5, 0x41a94ce9dc428066,
    0xcf8b0890283e370c, 0x8d7be97b81d4019f, 0x4a6acb477bea5a2a, 0x089a2aacd2006cb9,
    0x14dea25f3af9026d, 0x562e43b4931334fe, 0x913f6188692d6f4b, 0xd3cf8063c0c759d8,
    0x5dedc41a34bbeeb2, 0x1f1d25f19d51d821, 0xd80c07cd676f8394, 0x9afce626ce85b507,
)


# ─── CRC-64 hash (matches Archive::Load → CRC64(filePath)) ───────────────────

def crc64_hash(s: str) -> int:
    """Compute the CRC-64 of a UTF-8 string, exactly as libultraship does."""
    crc = 0xFFFFFFFFFFFFFFFF
    for byte in s.encode("utf-8"):
        crc = _CRC64_TABLE[((crc >> 56) ^ byte) & 0xFF] ^ ((crc << 8) & 0xFFFFFFFFFFFFFFFF)
    return crc


def _extract_path_addr(path: str) -> tuple[int, str]:
    """Return (sort_key, display_str) for address-based sorting.

    Priority:
    1. Explicit 0x literal in path          → hex, displayed as 0x…
    2. Last path component is all hex chars AND (contains a–f OR is zero-padded
       like '060') → interpreted as hex, displayed as 0x…
    3. Last decimal integer anywhere in path → decimal value, displayed as 0x…
    All non-empty results are displayed in 0x… form.
    """
    # 1. Explicit 0x prefix
    m = re.search(r'0[xX]([0-9a-fA-F]+)', path)
    if m:
        val = int(m.group(1), 16)
        return val, f"0x{val:X}"

    # 2. Last path component that looks like a bare hex address
    last = path.rstrip("/").rsplit("/", 1)[-1]
    if last and re.fullmatch(r"[0-9a-fA-F]+", last, re.IGNORECASE):
        has_af    = bool(re.search(r"[a-fA-F]", last))
        zero_padded = len(last) > 1 and last[0] == "0"
        if has_af or zero_padded:
            val = int(last, 16)
            return val, f"0x{val:X}"

    # 3. Last decimal integer in path, shown as hex
    hits = re.findall(r"\d+", path)
    if hits:
        val = int(hits[-1])
        return val, f"0x{val:X}"
    return 0, ""


# ─── binary parsing ───────────────────────────────────────────────────────────

def _res_type(data: bytes) -> int:
    """Read the ResourceType field from an OTR header (bytes 4-7 LE)."""
    if len(data) < 8:
        return 0
    return struct.unpack_from("<I", data, 4)[0]


def _res_version(data: bytes) -> int:
    """Read the version field from an OTR header (bytes 8-11 LE)."""
    if len(data) < 12:
        return 0
    return struct.unpack_from("<I", data, 8)[0]


def is_sample_entry(data: bytes) -> bool:
    if len(data) < BODY_OFFSET + 8:
        return False
    if data[0:1] == b"<":
        return False
    return _res_type(data) == SAMPLE_RES_TYPE


def parse_sample_binary(data: bytes) -> dict | None:
    """Parse a Sample binary entry.

    Handles two on-disk versions:
      v1 — full entry: codec, medium, unk, size, loop_hash, book_hash, raw[size]
      v2 — redirect:   canonical_hash (u64) only; audio data lives in the canonical entry
    """
    if len(data) < BODY_OFFSET + 8:
        return None

    version = _res_version(data)

    if version == 2:
        canonical_hash = struct.unpack_from("<Q", data, BODY_OFFSET)[0]
        return dict(
            is_redirect=True, canonical_hash=canonical_hash, canonical_path=None,
            codec=0, medium=0, unk=0, size=0,
            loop_hash=0, book_hash=0, has_loop=False, has_book=False,
            adpcm_frames=0, pcm_samples=0, raw=b"",
            loop_data=None, book_data=None,
        )

    # Version 1: full entry
    if len(data) < BODY_OFFSET + 23:
        return None
    off    = BODY_OFFSET
    codec  = data[off]
    medium = data[off + 1]
    unk    = data[off + 2]
    size   = struct.unpack_from("<I", data, off + 3)[0]
    loop_h = struct.unpack_from("<Q", data, off + 7)[0]
    book_h = struct.unpack_from("<Q", data, off + 15)[0]
    body   = off + 23
    raw    = data[body: body + size]

    # Estimate frame/sample counts for duration display
    if codec == 0:  # ADPCM: 9 bytes/frame, 16 samples/frame
        adpcm_frames = size // ADPCM_FRAME_BYTES
        pcm_samples  = adpcm_frames * ADPCM_FRAME_SAMPLES
    elif codec == 5:  # S16 PCM: 2 bytes/sample
        adpcm_frames = 0
        pcm_samples  = size // 2
    else:
        adpcm_frames = 0
        pcm_samples  = 0

    return dict(
        is_redirect=False, canonical_hash=None, canonical_path=None,
        codec=codec, medium=medium, unk=unk, size=size,
        loop_hash=loop_h, book_hash=book_h,
        has_loop=loop_h != 0, has_book=book_h != 0,
        adpcm_frames=adpcm_frames, pcm_samples=pcm_samples,
        raw=raw,
        # resolved after archive scan:
        loop_data=None, book_data=None,
    )


def parse_loop_binary(data: bytes) -> dict | None:
    """Parse an AdpcmLoop entry from its OTR binary (after 64-byte header).

    Layout (all LE):
      start         u32  — first looping frame (inclusive)
      end           u32  — last looping frame (exclusive)
      count         u32  — loop iterations; 0xFFFFFFFF = infinite
      state[16]     i16  — ADPCM decoder state at loop point (only if count != 0)
    """
    off = BODY_OFFSET
    if len(data) < off + 12:
        return None
    start = struct.unpack_from("<I", data, off)[0]
    end   = struct.unpack_from("<I", data, off + 4)[0]
    count = struct.unpack_from("<I", data, off + 8)[0]
    state = []
    if count != 0 and len(data) >= off + 12 + 32:
        for i in range(16):
            state.append(struct.unpack_from("<h", data, off + 12 + i * 2)[0])
    return dict(start=start, end=end, count=count, state=state)


def parse_book_binary(data: bytes) -> dict | None:
    """Parse an AdpcmBook entry from its OTR binary (after 64-byte header).

    Layout (all LE):
      order          u32  — predictor order (history depth per half-frame)
      numPredictors  u32  — number of codebook entries
      book_size      u32  — = 8 * order * numPredictors
      book[book_size] i16 — flat coefficient table; layout [pred][j=0..order][k=0..8]
                            maps to coef_table[pred][k][j] for the VADPCM decoder

    The coefficients encode how past samples predict the next one.
    Each predictor is a set of (order × 8) coefficients that form a prediction
    filter for one 8-sample sub-block within a 16-sample ADPCM frame.
    """
    off = BODY_OFFSET
    if len(data) < off + 12:
        return None
    order  = struct.unpack_from("<I", data, off)[0]
    n_pred = struct.unpack_from("<I", data, off + 4)[0]
    count  = struct.unpack_from("<I", data, off + 8)[0]
    if len(data) < off + 12 + count * 2:
        return None
    book = []
    for i in range(count):
        book.append(struct.unpack_from("<h", data, off + 12 + i * 2)[0])
    return dict(order=order, num_predictors=n_pred, book=book)


_PITCH_SLOTS = ("low", "normal", "high")
_PITCH_ORDER  = ["low", "normal", "high", "drum"]


def parse_instrument_tunings(data: bytes) -> list[tuple[int, float, str]]:
    """Extract (sample_hash, tuning, slot) triples from an Instrument binary entry.

    Instrument body layout (all LE, no padding):
      isRelocated      u8
      normalRangeLo    u8
      normalRangeHi    u8
      adsrDecayIndex   u8
      envelope_hash    u64
      low_sample_hash  u64   tuning_low   f32   ← slot "low"
      norm_sample_hash u64   tuning_norm  f32   ← slot "normal"
      high_sample_hash u64   tuning_high  f32   ← slot "high"

    Three pitch slots: low (below normalRangeLo), normal, high (above normalRangeHi).
    A slot with hash=0 means that pitch range reuses the normal sample.
    """
    off = BODY_OFFSET
    if len(data) < off + 48:
        return []
    pairs = []
    off += 4  # skip 4 header bytes
    off += 8  # skip envelope_hash
    for slot in _PITCH_SLOTS:
        h = struct.unpack_from("<Q", data, off)[0]
        t = struct.unpack_from("<f", data, off + 8)[0]
        if h != 0 and t != 0.0:
            pairs.append((h, t, slot))
        off += 12
    return pairs


def parse_drum_tuning(data: bytes) -> tuple[int, float] | None:
    """Extract (sample_hash, tuning) from a Drum binary entry.

    Drum body layout (all LE, no padding):
      adsrDecayIndex   u8
      pan              u8
      isRelocated      u8
      sample_hash      u64
      tuning           f32
      envelope_hash    u64
    """
    off = BODY_OFFSET
    if len(data) < off + 15:
        return None
    off += 3  # skip 3 header bytes
    h = struct.unpack_from("<Q", data, off)[0]
    t = struct.unpack_from("<f", data, off + 8)[0]
    if h != 0 and t != 0.0:
        return h, t
    return None


def parse_soundfont_binary(data: bytes) -> dict | None:
    """Parse a SoundFont binary entry.

    Layout (all LE, after 64-byte OTR header):
      numInstruments  u8
      numDrums        u8
      sampleBankId1   u8
      sampleBankId2   u8
      inst_crcs[]     u64 × numInstruments   — CRC64 of each instrument archive path
      drum_crcs[]     u64 × numDrums         — CRC64 of each drum archive path
    """
    off = BODY_OFFSET
    if len(data) < off + 4:
        return None
    num_inst  = data[off]
    num_drums = data[off + 1]
    bank_id1  = data[off + 2]
    off += 4
    inst_crcs, drum_crcs = [], []
    for _ in range(num_inst):
        if len(data) < off + 8:
            break
        inst_crcs.append(struct.unpack_from("<Q", data, off)[0])
        off += 8
    for _ in range(num_drums):
        if len(data) < off + 8:
            break
        drum_crcs.append(struct.unpack_from("<Q", data, off)[0])
        off += 8
    return dict(num_inst=num_inst, num_drums=num_drums, bank_id1=bank_id1,
                inst_crcs=inst_crcs, drum_crcs=drum_crcs)


# ─── VADPCM decoder ───────────────────────────────────────────────────────────
# Ported from tools/aifc_decode.c (my_decodeframe / readaifccodebook).
# Decodes Nintendo N64 VADPCM (4:1 ADPCM): 9 bytes → 16 S16 samples per frame.

def _build_coef_table(order: int, num_predictors: int, flat_book: list[int]) -> list:
    """Build the 3D prediction table used by _decode_frame.

    flat_book layout (from binary): [pred][j=0..order-1][k=0..7]
    Stored as pred * order * 8 + j * 8 + k  →  coef_table[pred][k][j]
    Extra columns (j >= order) are derived and encode cross-frame prediction.
    """
    table = []
    for pred in range(num_predictors):
        entry = [[0] * (order + 8) for _ in range(8)]
        base = pred * order * 8
        for j in range(order):
            for k in range(8):
                entry[k][j] = flat_book[base + j * 8 + k]

        # Derived entries — replicate readaifccodebook logic exactly
        for k in range(1, 8):
            entry[k][order] = entry[k - 1][order - 1]
        entry[0][order] = 1 << 11  # 2048

        for k in range(1, 8):
            for j in range(8):
                if j < k:
                    entry[j][k + order] = 0
                else:
                    entry[j][k + order] = entry[j - k][order]

        table.append(entry)
    return table


def _decode_frame(frame: bytes, state: list, order: int, coef_table: list) -> None:
    """Decode one 9-byte ADPCM frame, updating state[0..15] in-place."""
    header   = frame[0]
    scale    = 1 << (header >> 4)
    optimalp = header & 0xF

    ix = [0] * 16
    for i in range(0, 16, 2):
        c = frame[1 + i // 2]
        ix[i]     = c >> 4
        ix[i + 1] = c & 0xF
    for i in range(16):
        if ix[i] >= 8:
            ix[i] -= 16
        ix[i] *= scale

    entry  = coef_table[optimalp]
    in_vec = [0] * (order + 8)

    for half in range(2):
        # Seed in_vec with the last `order` decoded samples from the prior half-block
        if half == 0:
            for i in range(order):
                in_vec[i] = state[16 - order + i]
        else:
            for i in range(order):
                in_vec[i] = state[8 - order + i]

        for i in range(8):
            ind = half * 8 + i
            in_vec[order + i] = ix[ind]
            # floor(dot(entry[i], in_vec, length=order+i) / 2048)
            dp = sum(entry[i][x] * in_vec[x] for x in range(order + i))
            state[ind] = dp // 2048 + ix[ind]


def vadpcm_to_pcm(raw: bytes, book: dict) -> bytes:
    """Decode N64 VADPCM bytes to S16 little-endian PCM.

    The output sample rate is whatever rate the ROM encoded the sample at.
    Call at 32 kHz if no tuning is known; the engine tunes pitch by sample rate.
    """
    order     = book["order"]
    num_pred  = book["num_predictors"]
    flat_book = book["book"]
    coef_table = _build_coef_table(order, num_pred, flat_book)

    state  = [0] * 16
    output = array.array("h")  # signed 16-bit

    n_frames = len(raw) // ADPCM_FRAME_BYTES
    for f in range(n_frames):
        frame = raw[f * ADPCM_FRAME_BYTES: (f + 1) * ADPCM_FRAME_BYTES]
        _decode_frame(frame, state, order, coef_table)
        for v in state:
            output.append(max(-32768, min(32767, v)))

    return output.tobytes()


# ─── archive helpers ──────────────────────────────────────────────────────────

def list_samples(archive_path: str,
                 name_filter: str = "",
                 codec_filter: int = -1,
                 bank_filter: str = "") -> list[dict]:
    """Single-pass scan: collect samples, loops, books, instruments, drums, and
    soundfonts; cross-link everything by CRC-64 hash to infer per-sample tuning,
    bank membership, and instrument usage."""
    loop_by_hash:       dict[int, dict]                    = {}
    book_by_hash:       dict[int, dict]                    = {}
    tuning_lists:       dict[int, list[float]]             = {}
    pitch_roles:        dict[int, set[str]]                = {}
    font_by_inst_crc:   dict[int, str]                              = {}  # inst_crc64 → font_path
    font_by_drum_crc:   dict[int, str]                              = {}  # drum_crc64 → font_path
    inst_slot_data:     dict[int, list[tuple[str, str, float]]]     = {}  # hash → [(inst_path, slot, tuning)]
    drum_slot_data:     dict[int, list[tuple[str, float]]]          = {}  # hash → [(drum_path, tuning)]
    raw_samples:        list[tuple[str, bytes]]            = []

    def _add_tuning(sample_hash: int, tuning: float):
        tuning_lists.setdefault(sample_hash, []).append(tuning)

    with zipfile.ZipFile(archive_path, "r") as z:
        for name in z.namelist():
            data = z.read(name)
            if len(data) < BODY_OFFSET + 4 or data[0:1] == b"<":
                continue
            rt = _res_type(data)
            if rt == SAMPLE_RES_TYPE:
                raw_samples.append((name, data))
            elif rt == LOOP_RES_TYPE:
                parsed = parse_loop_binary(data)
                if parsed is not None:
                    loop_by_hash[crc64_hash(name)] = parsed
            elif rt == BOOK_RES_TYPE:
                parsed = parse_book_binary(data)
                if parsed is not None:
                    book_by_hash[crc64_hash(name)] = parsed
            elif rt == FONT_RES_TYPE:
                parsed = parse_soundfont_binary(data)
                if parsed:
                    for crc in parsed["inst_crcs"]:
                        if crc:
                            font_by_inst_crc[crc] = name
                    for crc in parsed["drum_crcs"]:
                        if crc:
                            font_by_drum_crc[crc] = name
            elif rt == INST_RES_TYPE:
                for h, t, slot in parse_instrument_tunings(data):
                    _add_tuning(h, t)
                    pitch_roles.setdefault(h, set()).add(slot)
                    inst_slot_data.setdefault(h, []).append((name, slot, t))
            elif rt == DRUM_RES_TYPE:
                pair = parse_drum_tuning(data)
                if pair:
                    _add_tuning(pair[0], pair[1])
                    pitch_roles.setdefault(pair[0], set()).add("drum")
                    drum_slot_data.setdefault(pair[0], []).append((name, pair[1]))

    results = []
    pending_redirects: list[tuple[str, dict]] = []  # (name, partial_info)

    for name, data in raw_samples:
        if name_filter and name_filter.lower() not in name.lower():
            continue
        info = parse_sample_binary(data)
        if info is None:
            continue

        if info["is_redirect"]:
            pending_redirects.append((name, info))
            continue

        if codec_filter >= 0 and info["codec"] != codec_filter:
            continue
        h                 = crc64_hash(name)
        info["path"]      = name
        info["hash"]      = h
        addr, addr_str    = _extract_path_addr(name)
        info["addr"]      = addr
        info["addr_str"]  = addr_str
        info["loop_data"] = loop_by_hash.get(info["loop_hash"])
        info["book_data"] = book_by_hash.get(info["book_hash"])
        info["pitch_roles"] = sorted(
            pitch_roles.get(h, set()),
            key=lambda r: _PITCH_ORDER.index(r) if r in _PITCH_ORDER else 99)

        # Resolve tuning: prefer the value closest to 1.0 as the "normal pitch" reference
        all_t = tuning_lists.get(h, [])
        if all_t:
            info["tuning"]      = min(all_t, key=lambda t: abs(t - 1.0))
            info["all_tunings"] = sorted(set(all_t))
            info["sample_rate"] = round(info["tuning"] * AUDIO_REF_HZ)
        else:
            info["tuning"]      = None
            info["all_tunings"] = []
            info["sample_rate"] = None

        # Bank + instrument provenance
        banks: set[str] = set()
        used_by: list[str] = []
        provenance: list[dict] = []
        slot_tunings: dict[str, float] = {}
        for ipath, slot, t in inst_slot_data.get(h, []):
            font = font_by_inst_crc.get(crc64_hash(ipath), "")
            if font:
                banks.add(font)
            used_by.append(f"{_font_short(font) if font else '?'}:{_path_tail(ipath)}({slot[0].upper()})")
            provenance.append({"font": font, "inst_path": ipath, "slot": slot, "tuning": t})
            slot_tunings.setdefault(slot, t)
        for dpath, t in drum_slot_data.get(h, []):
            font = font_by_drum_crc.get(crc64_hash(dpath), "")
            if font:
                banks.add(font)
            used_by.append(f"{_font_short(font) if font else '?'}:{_path_tail(dpath)}(D)")
            provenance.append({"font": font, "inst_path": dpath, "slot": "drum", "tuning": t})
            slot_tunings.setdefault("drum", t)
        info["banks"]       = sorted(banks)
        info["used_by"]     = sorted(used_by)
        info["provenance"]  = provenance
        info["slot_tunings"] = slot_tunings

        if bank_filter and bank_filter not in banks:
            continue

        results.append(info)

    # Resolve v2 redirects: copy canonical's audio fields, override path-specific ones.
    canonical_by_hash = {s["hash"]: s for s in results}
    for name, rinfo in pending_redirects:
        canonical = canonical_by_hash.get(rinfo["canonical_hash"])
        if canonical is None:
            continue
        if codec_filter >= 0 and canonical["codec"] != codec_filter:
            continue
        h              = crc64_hash(name)
        info           = dict(canonical)
        info["path"]   = name
        info["hash"]   = h
        info["is_redirect"]    = True
        info["canonical_hash"] = rinfo["canonical_hash"]
        info["canonical_path"] = canonical["path"]
        addr, addr_str = _extract_path_addr(name)
        info["addr"]   = addr
        info["addr_str"] = addr_str
        # Instruments/drums now reference the canonical hash directly, so the
        # redirect's own hash is unreferenced.  Use whatever pitch_roles the
        # redirect itself has (old archives where instruments still pointed here),
        # falling back to the canonical's roles for freshly-extracted archives.
        own_roles = pitch_roles.get(h, set())
        if own_roles:
            info["pitch_roles"] = sorted(
                own_roles,
                key=lambda r: _PITCH_ORDER.index(r) if r in _PITCH_ORDER else 99)
        # else: keep canonical's pitch_roles (already copied via dict(canonical))
        all_t = tuning_lists.get(h, [])
        if all_t:
            info["tuning"]      = min(all_t, key=lambda t: abs(t - 1.0))
            info["all_tunings"] = sorted(set(all_t))
            info["sample_rate"] = round(info["tuning"] * AUDIO_REF_HZ)
        # else: keep canonical's tuning (already copied via dict(canonical))
        # Provenance for redirects: check if this redirect path is referenced by its own
        # instruments/drums (older archives), otherwise inherit canonical's provenance.
        own_banks: set[str] = set()
        own_used: list[str] = []
        own_prov: list[dict] = []
        own_slot_t: dict[str, float] = {}
        for ipath, slot, t in inst_slot_data.get(h, []):
            font = font_by_inst_crc.get(crc64_hash(ipath), "")
            if font:
                own_banks.add(font)
            own_used.append(f"{_font_short(font) if font else '?'}:{_path_tail(ipath)}({slot[0].upper()})")
            own_prov.append({"font": font, "inst_path": ipath, "slot": slot, "tuning": t})
            own_slot_t.setdefault(slot, t)
        for dpath, t in drum_slot_data.get(h, []):
            font = font_by_drum_crc.get(crc64_hash(dpath), "")
            if font:
                own_banks.add(font)
            own_used.append(f"{_font_short(font) if font else '?'}:{_path_tail(dpath)}(D)")
            own_prov.append({"font": font, "inst_path": dpath, "slot": "drum", "tuning": t})
            own_slot_t.setdefault("drum", t)
        if own_banks:
            info["banks"]        = sorted(own_banks)
            info["used_by"]      = sorted(own_used)
            info["provenance"]   = own_prov
            info["slot_tunings"] = own_slot_t
        if bank_filter and bank_filter not in info.get("banks", []):
            continue
        results.append(info)

    results.sort(key=lambda x: x["path"])
    return results


def read_sample(archive_path: str, asset_path: str) -> tuple[dict | None, bytes | None]:
    """Read one sample entry; no loop/book resolution."""
    with zipfile.ZipFile(archive_path, "r") as z:
        if asset_path not in z.namelist():
            return None, None
        data = z.read(asset_path)
    return parse_sample_binary(data), data


def read_sample_full(archive_path: str,
                     asset_path: str) -> tuple[dict | None, dict | None, dict | None]:
    """Read one sample plus its loop, book, and tuning by scanning the same archive.

    Transparently follows v2 redirect entries to their canonical sample.
    """
    target_hash = crc64_hash(asset_path)

    with zipfile.ZipFile(archive_path, "r") as z:
        if asset_path not in z.namelist():
            return None, None, None
        data = z.read(asset_path)
        info = parse_sample_binary(data)
        if info is None:
            return None, None, None

        # Follow redirect: find canonical entry by CRC64 hash
        if info.get("is_redirect"):
            canonical_hash = info["canonical_hash"]
            for name in z.namelist():
                if crc64_hash(name) == canonical_hash:
                    cdata = z.read(name)
                    cinfo = parse_sample_binary(cdata)
                    if cinfo and not cinfo.get("is_redirect"):
                        cinfo["canonical_path"] = name
                        info = cinfo
                        info["is_redirect"]    = True
                        info["canonical_hash"] = canonical_hash
                        info["canonical_path"] = name
                    break
            if info.get("is_redirect") and not info.get("canonical_path"):
                return None, None, None

        loop: dict | None = None
        book: dict | None = None
        all_tunings: list[float] = []
        pitch_role_set: set[str] = set()

        for name in z.namelist():
            entry = z.read(name)
            if len(entry) < BODY_OFFSET + 4 or entry[0:1] == b"<":
                continue
            rt = _res_type(entry)
            h  = crc64_hash(name)
            if rt == LOOP_RES_TYPE and h == info["loop_hash"]:
                loop = parse_loop_binary(entry)
            elif rt == BOOK_RES_TYPE and h == info["book_hash"]:
                book = parse_book_binary(entry)
            elif rt == INST_RES_TYPE:
                for sh, t, slot in parse_instrument_tunings(entry):
                    if sh == target_hash:
                        all_tunings.append(t)
                        pitch_role_set.add(slot)
            elif rt == DRUM_RES_TYPE:
                pair = parse_drum_tuning(entry)
                if pair and pair[0] == target_hash:
                    all_tunings.append(pair[1])
                    pitch_role_set.add("drum")

    info["loop_data"]   = loop
    info["book_data"]   = book
    info["hash"]        = crc64_hash(asset_path)
    info["pitch_roles"] = sorted(
        pitch_role_set,
        key=lambda r: _PITCH_ORDER.index(r) if r in _PITCH_ORDER else 99)
    addr, addr_str      = _extract_path_addr(asset_path)
    info["addr"]        = addr
    info["addr_str"]    = addr_str
    info["all_tunings"] = sorted(set(all_tunings))
    if all_tunings:
        info["tuning"]      = min(all_tunings, key=lambda t: abs(t - 1.0))
        info["sample_rate"] = round(info["tuning"] * AUDIO_REF_HZ)
    else:
        info["tuning"]      = None
        info["sample_rate"] = None
    return info, loop, book


# ─── shared helpers ───────────────────────────────────────────────────────────

def _fmt_size(n: int) -> str:
    return f"{n / 1024:.1f} KB" if n >= 1024 else f"{n} B"


def _fmt_pitch_short(roles: list[str]) -> str:
    if not roles:
        return ""
    abbr = {"low": "L", "normal": "N", "high": "H", "drum": "D"}
    return "+".join(abbr.get(r, r[0].upper()) for r in roles)


def _fmt_pitch_long(roles: list[str]) -> str:
    if not roles:
        return "—"
    return ", ".join(r.capitalize() for r in roles)


def _font_short(path: str) -> str:
    """Extract the hex-address suffix from a SoundFont archive path for display."""
    m = re.search(r"sound_font[_/]?([0-9A-Fa-f]+)$", path, re.IGNORECASE)
    if m:
        return m.group(1)
    last = path.rsplit("/", 1)[-1]
    return last[-10:] if last else path


def _path_tail(path: str) -> str:
    """Return the last path component."""
    return path.rsplit("/", 1)[-1]


def _fmt_duration(pcm_samples: int, rate: int = MIXER_RATE_HZ) -> str:
    secs = pcm_samples / rate
    return f"{secs:.3f}s"


def _write_wav(pcm: bytes, path: str, channels: int = 1, rate: int = MIXER_RATE_HZ):
    with wave.open(path, "wb") as w:
        w.setnchannels(channels)
        w.setsampwidth(2)
        w.setframerate(rate)
        w.writeframes(pcm)


def _count_frames(path: str, sample_rate: int) -> int:
    """Return number of audio frames (samples per channel) in the file, or 0 on failure."""
    ext = os.path.splitext(path)[1].lower()
    if ext == ".wav":
        try:
            with wave.open(path, "rb") as w:
                return w.getnframes()
        except Exception:
            pass
    if shutil.which("ffprobe"):
        try:
            out = subprocess.check_output(
                ["ffprobe", "-v", "quiet", "-print_format", "json",
                 "-show_streams", "-select_streams", "a:0", path],
                stderr=subprocess.DEVNULL)
            s = json.loads(out)["streams"][0]
            if s.get("nb_samples") not in (None, "N/A", ""):
                return int(s["nb_samples"])
            if s.get("duration"):
                return int(float(s["duration"]) * sample_rate)
        except Exception:
            pass
    return 0


def _probe_audio(path: str) -> tuple[int, int]:
    ext = os.path.splitext(path)[1].lower()
    if ext == ".wav":
        try:
            with wave.open(path, "rb") as w:
                return w.getframerate(), w.getnchannels()
        except Exception:
            pass
    if shutil.which("ffprobe"):
        try:
            out = subprocess.check_output(
                ["ffprobe", "-v", "quiet", "-print_format", "json",
                 "-show_streams", "-select_streams", "a:0", path],
                stderr=subprocess.DEVNULL)
            s = json.loads(out)["streams"][0]
            return int(s["sample_rate"]), int(s["channels"])
        except Exception:
            pass
    raise RuntimeError("Cannot detect audio metadata — install ffprobe.")


def _make_xml(audio_arch_path: str, fmt: str, tuning: float, unk: int,
              loop: dict | None = None) -> str:
    """Build the XML descriptor for a custom-format sample replacement.

    loop — optional dict with keys start, end, count (already scaled to the
            new file's sample rate).  Omit predictor states: they are ADPCM-only
            and ignored by the engine for S16 PCM replacements.
    """
    root = ET.Element("Sample")
    root.set("Version",      "0")
    root.set("Codec",        "S16")
    root.set("Medium",       "Ram")
    root.set("bit26",        str(unk))
    root.set("Tuning",       f"{tuning:.6f}")
    root.set("Size",         "0")
    root.set("Relocated",    "0")
    root.set("Path",         audio_arch_path)
    root.set("CustomFormat", fmt)
    if loop is not None:
        lel = ET.SubElement(root, "ADPCMLoop")
        lel.set("Start", str(loop["start"]))
        lel.set("End",   str(loop["end"]))
        lel.set("Count", str(loop["count"]))
    raw = ET.tostring(root, encoding="unicode")
    dom = xml.dom.minidom.parseString(raw)
    return dom.toprettyxml(indent="  ").replace('<?xml version="1.0" ?>\n', "")


def _upsert_mod_o2r(mod_path: str,
                    xml_arch_path: str, xml_bytes: bytes,
                    audio_arch_path: str, audio_bytes: bytes):
    existing: dict[str, bytes] = {}
    if os.path.isfile(mod_path):
        with zipfile.ZipFile(mod_path, "r") as z:
            for name in z.namelist():
                existing[name] = z.read(name)
    existing[xml_arch_path]   = xml_bytes
    existing[audio_arch_path] = audio_bytes
    with zipfile.ZipFile(mod_path, "w", compression=zipfile.ZIP_DEFLATED) as z:
        for name, data in existing.items():
            z.writestr(name, data)


def _scale_loop(loop_data: dict, orig_rate: int, new_rate: int) -> dict | None:
    """Return loop points scaled from orig_rate to new_rate, or None if not looping."""
    if loop_data is None:
        return None
    scale = new_rate / orig_rate
    return dict(
        start=round(loop_data["start"] * scale),
        end=round(loop_data["end"]   * scale),
        count=loop_data["count"],
    )


def _do_replace(archive_path: str, asset_path: str,
                audio_path: str, out_dir: str) -> dict:
    sample_rate, channels = _probe_audio(audio_path)
    tuning = (sample_rate * channels) / AUDIO_REF_HZ

    # Use full scan to get loop data and original sample rate.
    info, loop, _book = read_sample_full(archive_path, asset_path)
    unk       = info["unk"]  if info else 0
    orig_rate = _effective_rate(info) if info else MIXER_RATE_HZ

    orig_frames = info["pcm_samples"] if info else 0
    new_frames  = _count_frames(audio_path, sample_rate)
    orig_dur    = orig_frames / orig_rate if orig_rate and orig_frames else 0.0
    new_dur     = new_frames  / sample_rate if sample_rate and new_frames else 0.0
    shorter     = orig_dur > 0.0 and new_dur > 0.0 and new_dur < orig_dur

    scaled_loop = _scale_loop(loop, orig_rate, sample_rate) if loop else None

    ext         = os.path.splitext(audio_path)[1].lower().lstrip(".")
    audio_arch  = asset_path + "." + ext
    xml_content = _make_xml(audio_arch, ext, tuning, unk, loop=scaled_loop)

    mod_name = os.path.splitext(os.path.basename(archive_path))[0]
    mod_o2r  = os.path.join(out_dir, f"{mod_name}_audio_replacements.o2r")

    with open(audio_path, "rb") as f:
        audio_bytes = f.read()

    _upsert_mod_o2r(mod_o2r,
                    asset_path,  xml_content.encode(),
                    audio_arch,  audio_bytes)
    return dict(sample_rate=sample_rate, channels=channels,
                tuning=tuning, mod_o2r=mod_o2r,
                loop=scaled_loop, orig_rate=orig_rate,
                orig_dur=orig_dur, new_dur=new_dur, shorter=shorter)


# ─── project store ────────────────────────────────────────────────────────────

def _project_default_path(archive_path: str) -> str:
    return os.path.splitext(archive_path)[0] + "_project.json"


def load_project(project_path: str) -> dict:
    """Load a project file. Returns dict with keys: archive, out_dir, replacements.
    All paths are resolved to absolute paths relative to the project file location."""
    with open(project_path, encoding="utf-8") as f:
        data = json.load(f)
    base = os.path.dirname(os.path.abspath(project_path))

    def _abs(p: str) -> str:
        return p if os.path.isabs(p) else os.path.normpath(os.path.join(base, p))

    archive = _abs(data.get("archive", ""))
    out_dir = _abs(data.get("out_dir", "."))
    replacements = {asset: _abs(audio) for asset, audio in data.get("replacements", {}).items()}
    return dict(archive=archive, out_dir=out_dir, replacements=replacements)


def save_project(project_path: str, archive: str, out_dir: str,
                 replacements: dict[str, str]) -> None:
    """Save a project file. Paths are stored relative to the project file."""
    base = os.path.dirname(os.path.abspath(project_path))

    def _rel(p: str) -> str:
        try:
            r = os.path.relpath(os.path.abspath(p), base)
            return r if not r.startswith(os.sep * 2) else p
        except ValueError:
            return p

    data = {
        "version": 1,
        "archive": _rel(archive),
        "out_dir": _rel(out_dir) if out_dir else ".",
        "replacements": {asset: _rel(audio) for asset, audio in replacements.items()},
    }
    with open(project_path, "w", encoding="utf-8") as f:
        json.dump(data, f, indent=2)


# ─── alias store ──────────────────────────────────────────────────────────────

def _aliases_path(archive_path: str) -> str:
    return os.path.splitext(archive_path)[0] + "_aliases.json"


def load_aliases(archive_path: str) -> dict[str, str]:
    p = _aliases_path(archive_path)
    if os.path.isfile(p):
        try:
            with open(p, encoding="utf-8") as f:
                data = json.load(f)
            return data.get("aliases", data) if isinstance(data, dict) else {}
        except Exception:
            pass
    return {}


def save_aliases(archive_path: str, aliases: dict[str, str]) -> None:
    with open(_aliases_path(archive_path), "w", encoding="utf-8") as f:
        json.dump({"version": 1, "aliases": aliases}, f, indent=2)


def export_aliases_to(aliases: dict[str, str], out_path: str) -> None:
    with open(out_path, "w", encoding="utf-8") as f:
        json.dump({"version": 1, "aliases": aliases}, f, indent=2)


def _play_pcm_wav(pcm: bytes, sample_rate: int = MIXER_RATE_HZ):
    """Write PCM to a temp WAV and play via ffplay (blocking)."""
    if not shutil.which("ffplay"):
        raise RuntimeError("ffplay not found — install ffmpeg.")
    with tempfile.NamedTemporaryFile(suffix=".wav", delete=False) as tf:
        tmp = tf.name
    try:
        _write_wav(pcm, tmp, rate=sample_rate)
        subprocess.run(["ffplay", "-nodisp", "-autoexit", tmp],
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                       check=True)
    finally:
        try:
            os.unlink(tmp)
        except OSError:
            pass


def _effective_rate(info: dict) -> int:
    """Return the best-known playback sample rate for a sample.

    For ADPCM the real recording rate comes from instrument/drum tuning:
      sample_rate = round(tuning * 32000)
    Falls back to MIXER_RATE_HZ (32000) when tuning is unknown.
    """
    sr = info.get("sample_rate")
    return sr if sr else MIXER_RATE_HZ


def _decode_sample(info: dict,
                   slot_tuning: float | None = None) -> tuple[bytes, int] | None:
    """Return (S16 LE PCM, sample_rate) for a sample, or None if not playable.

    slot_tuning — when provided, overrides the default tuning so the sample plays
    back at the pitch for a specific instrument slot (Low/Normal/High/Drum).
    """
    codec = info.get("codec")
    rate  = round(slot_tuning * AUDIO_REF_HZ) if slot_tuning else _effective_rate(info)
    if codec == 5:
        return info["raw"], rate
    if codec == 0:
        book = info.get("book_data")
        if book is None:
            return None
        return vadpcm_to_pcm(info["raw"], book), rate
    return None


# ─── CLI subcommands ──────────────────────────────────────────────────────────

def _loop_str(info: dict) -> str:
    ld = info.get("loop_data")
    if not info["has_loop"]:
        return "none"
    if ld is None:
        return f"yes  (hash 0x{info['loop_hash']:016X}, data unavailable)"
    cnt = "∞" if ld["count"] == LOOP_INFINITE else str(ld["count"])
    return f"yes  start={ld['start']}  end={ld['end']}  count={cnt}"


def _book_str(info: dict) -> str:
    bd = info.get("book_data")
    if not info["has_book"]:
        return "none"
    if bd is None:
        return f"yes  (hash 0x{info['book_hash']:016X}, data unavailable)"
    return f"order={bd['order']}  predictors={bd['num_predictors']}"


def cmd_list(args):
    samples = list_samples(args.archive,
                           args.filter or "",
                           args.codec if args.codec is not None else -1)
    if not samples:
        print("No matching samples found.")
        return
    aliases = load_aliases(args.archive)
    w = max((len(s["path"]) for s in samples), default=12)
    aliased = {s["path"]: aliases[s["path"]] for s in samples if s["path"] in aliases}
    if aliased:
        aw = max((len(v) for v in aliased.values()), default=5)
        aw = max(aw, 5)
        hdr = (f"{'Asset path':{w}}  {'Alias':{aw}}  "
               f"{'Codec':12}  {'Size':>10}  {'Duration':>9}  Loop  Book")
    else:
        aw = 0
        hdr = f"{'Asset path':{w}}  {'Codec':12}  {'Size':>10}  {'Duration':>9}  Loop  Book"
    print(hdr);  print("-" * len(hdr))
    for s in samples:
        dur = _fmt_duration(s["pcm_samples"]) if s["pcm_samples"] else "—"
        codec = CODEC_NAMES.get(s["codec"], "?")
        if aliased:
            alias = aliased.get(s["path"], "")
            print(f"{s['path']:{w}}  {alias:{aw}}  {codec:12}  "
                  f"{_fmt_size(s['size']):>10}  {dur:>9}  "
                  f"{'yes' if s['has_loop'] else 'no ':4}  "
                  f"{'yes' if s['has_book'] else 'no'}")
        else:
            print(f"{s['path']:{w}}  {codec:12}  "
                  f"{_fmt_size(s['size']):>10}  {dur:>9}  "
                  f"{'yes' if s['has_loop'] else 'no ':4}  "
                  f"{'yes' if s['has_book'] else 'no'}")
    counts = {}
    for s in samples:
        k = CODEC_NAMES.get(s["codec"], f"UNK({s['codec']})")
        counts[k] = counts.get(k, 0) + 1
    print(f"\nTotal: {len(samples)}  ({', '.join(f'{v} {k}' for k,v in sorted(counts.items()))})")


def cmd_info(args):
    info, loop, book = read_sample_full(args.archive, args.asset)
    if info is None:
        sys.exit(f"error: sample '{args.asset}' not found.")

    aliases = load_aliases(args.archive)
    alias = aliases.get(args.asset, "")
    print(f"Path      : {args.asset}")
    if alias:
        print(f"Alias     : {alias}")
    print(f"Codec     : {info['codec']} ({CODEC_NAMES.get(info['codec'], '?')})", end="")
    if info["codec"] == 0:
        print("  — Nintendo N64 VADPCM 4:1 (9 bytes → 16 S16 samples/frame)")
    elif info["codec"] == 5:
        print("  — S16 PCM (port custom audio)")
    else:
        print()
    print(f"Medium    : {info['medium']} ({MEDIUM_NAMES.get(info['medium'], '?')})")
    print(f"Unk bit   : {info['unk']}")
    print(f"Raw size  : {info['size']:,} bytes  ({_fmt_size(info['size'])})")

    rate = _effective_rate(info)
    if info["tuning"] is not None:
        all_t = info.get("all_tunings", [info["tuning"]])
        tuning_str = f"{info['tuning']:.6f}"
        if len(all_t) > 1:
            tuning_str += "  (others: " + ", ".join(f"{t:.4f}" for t in all_t if t != info["tuning"]) + ")"
        print(f"Tuning    : {tuning_str}")
        print(f"Rate      : ~{rate} Hz  (= tuning × 32000)")
    else:
        print(f"Tuning    : unknown  (not referenced by any instrument/drum in this archive)")
        print(f"Rate      : {MIXER_RATE_HZ} Hz  (fallback — may sound pitched up or down)")

    if info["codec"] == 0 and info["adpcm_frames"]:
        print(f"Frames    : {info['adpcm_frames']:,} ADPCM frames → "
              f"{info['pcm_samples']:,} PCM samples "
              f"(~{_fmt_duration(info['pcm_samples'], rate)} @ {rate} Hz)")
    elif info["pcm_samples"]:
        print(f"Samples   : {info['pcm_samples']:,} S16 "
              f"(~{_fmt_duration(info['pcm_samples'], rate)} @ {rate} Hz)")

    # Loop
    print(f"\nLoop      : {_loop_str(info)}")
    if loop and loop["state"]:
        st = " ".join(str(v) for v in loop["state"])
        print(f"  Predictor state: [{st}]")

    # Book
    print(f"Book      : {_book_str(info)}")
    if book:
        n_coef = book["order"] * book["num_predictors"] * 8
        print(f"  {n_coef} total coefficients  "
              f"(order={book['order']} × predictors={book['num_predictors']} × 8)")


def cmd_export(args):
    info, loop, book = read_sample_full(args.archive, args.asset)
    if info is None:
        sys.exit(f"error: sample '{args.asset}' not found.")

    base = os.path.basename(args.asset)
    decode = getattr(args, "decode", False)

    rate = _effective_rate(info)
    if info["codec"] == 5:
        out = args.out or (base + ".wav")
        _write_wav(info["raw"], out, rate=rate)
        print(f"Exported S16 PCM → WAV: {out}  ({info['pcm_samples']:,} samples @ {rate} Hz)")

    elif info["codec"] == 0 and (decode or args.out and args.out.endswith(".wav")):
        if book is None:
            sys.exit("error: no book found — cannot decode ADPCM.")
        print("Decoding ADPCM…", end=" ", flush=True)
        pcm = vadpcm_to_pcm(info["raw"], book)
        out = args.out or (base + ".wav")
        _write_wav(pcm, out, rate=rate)
        rate_note = f"{rate} Hz" if info["tuning"] else f"{rate} Hz (tuning unknown, may be wrong pitch)"
        print(f"done.\nExported decoded WAV: {out}  ({info['pcm_samples']:,} samples @ {rate_note})")

    else:
        out = args.out or (base + ".bin")
        with open(out, "wb") as f:
            f.write(info["raw"])
        print(f"Exported raw {CODEC_NAMES.get(info['codec'], '?')}: {out}  ({info['size']:,} B)")


def cmd_play(args):
    if not shutil.which("ffplay"):
        sys.exit("error: ffplay not found — install ffmpeg.")
    info, loop, book = read_sample_full(args.archive, args.asset)
    if info is None:
        sys.exit(f"error: sample '{args.asset}' not found.")

    rate  = _effective_rate(info)
    codec = info["codec"]
    if codec == 5:
        _play_pcm_wav(info["raw"], rate)
    elif codec == 0:
        if book is None:
            sys.exit("error: no book found — cannot decode ADPCM for playback.")
        print("Decoding ADPCM…", end=" ", flush=True)
        pcm = vadpcm_to_pcm(info["raw"], book)
        rate_note = f"{rate} Hz" if info["tuning"] else f"{rate} Hz (tuning unknown)"
        print(f"playing at {rate_note}…")
        _play_pcm_wav(pcm, rate)
    else:
        sys.exit(f"Playback not supported for codec {CODEC_NAMES.get(codec, codec)}.")


def cmd_replace(args):
    if not os.path.isfile(args.input):
        sys.exit(f"error: input file not found: {args.input}")
    ext = os.path.splitext(args.input)[1].lower().lstrip(".")
    if ext not in ("wav", "ogg", "mp3"):
        sys.exit(f"error: unsupported format '.{ext}'. Use wav, ogg, or mp3.")
    out_dir = os.path.abspath(args.out_dir) if args.out_dir else os.path.dirname(args.archive)
    os.makedirs(out_dir, exist_ok=True)
    r = _do_replace(args.archive, args.asset, args.input, out_dir)
    print(f"Sample rate : {r['sample_rate']} Hz | Channels: {r['channels']} | Tuning: {r['tuning']:.4f}")
    if r.get("loop"):
        lp = r["loop"]
        cnt = "∞" if lp["count"] == LOOP_INFINITE else str(lp["count"])
        print(f"Loop        : start={lp['start']}  end={lp['end']}  count={cnt}"
              f"  (scaled from {r['orig_rate']} Hz → {r['sample_rate']} Hz)")
    else:
        print("Loop        : none")
    if r.get("shorter"):
        print(f"WARNING     : replacement is shorter than original "
              f"({r['new_dur']:.3f}s vs {r['orig_dur']:.3f}s) — "
              f"silence will pad the end in-game")
    print(f"Mod archive : {r['mod_o2r']}")
    print(f"Place {os.path.basename(r['mod_o2r'])} in the mods/ folder to apply.")


def cmd_batch_replace(args):
    """Replace multiple samples in one pass from a folder or JSON mapping file."""
    if args.dir:
        folder = os.path.abspath(args.dir)
        audio_map: dict[str, str] = {}
        for fname in os.listdir(folder):
            ext = os.path.splitext(fname)[1].lower()
            if ext in (".wav", ".ogg", ".mp3"):
                key = os.path.splitext(fname)[0].lower()
                audio_map[key] = os.path.join(folder, fname)

        samples = list_samples(args.archive)
        aliases = load_aliases(args.archive)
        mapping: dict[str, str] = {}
        for s in samples:
            p     = s["path"]
            bname = os.path.basename(p).lower()
            alias = aliases.get(p, "")
            alias_key = alias.lower().replace(" ", "_") if alias else None
            hit = audio_map.get(bname) or (alias_key and audio_map.get(alias_key))
            if hit:
                mapping[p] = hit
        if not mapping:
            sys.exit("No filename matches found in folder.")
    elif args.mapping:
        with open(args.mapping, encoding="utf-8") as f:
            data = json.load(f)
        mapping = data.get("mapping", data) if isinstance(data, dict) else data
        if not isinstance(mapping, dict):
            sys.exit("error: mapping JSON must be an object { asset_path: audio_file, … }")
    else:
        sys.exit("error: supply --dir or --mapping")

    out_dir = os.path.abspath(args.out_dir) if args.out_dir else os.path.dirname(
        os.path.abspath(args.archive))
    os.makedirs(out_dir, exist_ok=True)

    errors: list[str] = []
    warnings: list[str] = []
    n = len(mapping)
    for i, (sample_path, audio_path) in enumerate(mapping.items()):
        tag = f"[{i + 1}/{n}]"
        print(f"{tag} {os.path.basename(sample_path)} ← {os.path.basename(audio_path)}", end="  ")
        try:
            r = _do_replace(args.archive, sample_path, audio_path, out_dir)
            if r.get("shorter"):
                print(f"⚠  (shorter: {r['new_dur']:.3f}s vs {r['orig_dur']:.3f}s)")
                warnings.append(f"{sample_path}: {r['new_dur']:.3f}s < {r['orig_dur']:.3f}s original")
            else:
                print("✓")
        except Exception as e:
            print(f"✗  ({e})")
            errors.append(f"{sample_path}: {e}")

    mod_name = os.path.splitext(os.path.basename(args.archive))[0]
    mod_o2r  = os.path.join(out_dir, f"{mod_name}_audio_replacements.o2r")
    print(f"\nMod archive : {mod_o2r}")
    print(f"Place it in the mods/ folder to apply.")
    if warnings:
        print(f"\n{len(warnings)} warning(s) — replacements shorter than originals:")
        for w in warnings:
            print(f"  ⚠  {w}")
    if errors:
        print(f"\n{len(errors)} error(s):")
        for e in errors:
            print(f"  {e}")
        sys.exit(1)


def cmd_save_project(args):
    """Add or update a replacement entry in a project file."""
    proj = args.project or _project_default_path(args.archive)
    replacements: dict[str, str] = {}
    archive  = args.archive
    out_dir  = args.out_dir or ""
    if os.path.isfile(proj):
        existing = load_project(proj)
        replacements = existing["replacements"]
        archive  = existing["archive"] or archive
        out_dir  = existing["out_dir"] or out_dir
    replacements[args.asset] = os.path.abspath(args.input)
    save_project(proj, archive, out_dir, replacements)
    print(f"Project     : {proj}")
    print(f"  {args.asset}  →  {args.input}")
    print(f"  ({len(replacements)} replacement(s) total)")


def cmd_apply_project(args):
    """Re-apply all replacements recorded in a project file."""
    proj = load_project(args.project)
    archive = proj["archive"]
    out_dir = args.out_dir or proj["out_dir"] or os.path.dirname(os.path.abspath(archive))
    replacements = proj["replacements"]

    if not replacements:
        print("No replacements in project.")
        return
    if not os.path.isfile(archive):
        sys.exit(f"error: archive not found: {archive}")
    os.makedirs(out_dir, exist_ok=True)

    errors:   list[str] = []
    warnings: list[str] = []
    n = len(replacements)
    for i, (asset, audio) in enumerate(replacements.items()):
        tag = f"[{i + 1}/{n}]"
        print(f"{tag} {os.path.basename(asset)} ← {os.path.basename(audio)}", end="  ")
        if not os.path.isfile(audio):
            msg = f"audio file not found: {audio}"
            print(f"✗  ({msg})")
            errors.append(f"{asset}: {msg}")
            continue
        try:
            r = _do_replace(archive, asset, audio, out_dir)
            if r.get("shorter"):
                print(f"⚠  (shorter: {r['new_dur']:.3f}s vs {r['orig_dur']:.3f}s)")
                warnings.append(f"{asset}: {r['new_dur']:.3f}s < {r['orig_dur']:.3f}s original")
            else:
                print("✓")
        except Exception as e:
            print(f"✗  ({e})")
            errors.append(f"{asset}: {e}")

    mod_name = os.path.splitext(os.path.basename(archive))[0]
    mod_o2r  = os.path.join(out_dir, f"{mod_name}_audio_replacements.o2r")
    print(f"\nMod archive : {mod_o2r}")
    print(f"Place it in the mods/ folder to apply.")
    if warnings:
        print(f"\n{len(warnings)} warning(s) — replacements shorter than originals:")
        for w in warnings:
            print(f"  ⚠  {w}")
    if errors:
        print(f"\n{len(errors)} error(s):")
        for e in errors:
            print(f"  {e}")
        sys.exit(1)


def cmd_alias(args):
    aliases = load_aliases(args.archive)
    if args.alias is None:
        print(aliases.get(args.asset, ""))
    elif args.alias:
        aliases[args.asset] = args.alias
        save_aliases(args.archive, aliases)
        print(f"Alias set: {args.asset!r} → {args.alias!r}")
    else:
        if args.asset in aliases:
            del aliases[args.asset]
            save_aliases(args.archive, aliases)
            print(f"Alias removed: {args.asset!r}")
        else:
            print(f"No alias for: {args.asset!r}")


def cmd_export_aliases(args):
    aliases = load_aliases(args.archive)
    base = os.path.splitext(args.archive)[0]
    out = args.out or (base + "_aliases_export.json")
    export_aliases_to(aliases, out)
    print(f"Exported {len(aliases)} alias(es) → {out}")


# ─── GUI ─────────────────────────────────────────────────────────────────────

def cmd_gui(args):
    try:
        import tkinter as tk
        from tkinter import filedialog, messagebox, ttk
    except ImportError:
        sys.exit("error: tkinter is not available in this Python install.")

    # ── colour palette (Catppuccin Mocha) ─────────────────────────────────────
    BG       = "#1e1e2e"
    BG2      = "#181825"
    BG3      = "#313244"
    FG       = "#cdd6f4"
    FG_DIM   = "#6c7086"
    ACCENT   = "#89b4fa"
    ACCENT2  = "#a6e3a1"
    WARN     = "#f38ba8"
    SEL_BG   = "#45475a"
    FONT     = ("Helvetica", 11)
    FONT_SML = ("Helvetica", 9)
    FONT_MON = ("Menlo", 10) if sys.platform == "darwin" else ("Consolas", 10)

    # ── main window ───────────────────────────────────────────────────────────
    class App(tk.Tk):
        def __init__(self):
            super().__init__()
            self.title("Starship Sample Editor")
            self.configure(bg=BG)
            self.geometry("1380x780")
            self.minsize(960, 560)

            self._samples:             list[dict]      = []
            self._filtered:            list[dict]      = []
            self._archive_path:        str             = ""
            self._loading:             bool            = False
            self._aliases:             dict[str, str]  = {}
            self._alias_current_path:  str             = ""
            self._batch_mapping:       dict[str, str]  = {}
            self._node_map:            dict[str, dict] = {}  # iid → {sample, slot, tuning, leaf}
            self._iids_by_path:        dict[str, list[str]] = {}  # path → [leaf iids]
            self._project_path:        str             = ""

            self._build_styles()
            self._build_ui()

            initial = getattr(args, "archive", None)
            if initial and os.path.isfile(initial):
                self._archive_var.set(initial)
                self.after(100, self._load_archive)

        # ── style ─────────────────────────────────────────────────────────────
        def _build_styles(self):
            s = ttk.Style(self)
            s.theme_use("clam")
            s.configure(".",
                background=BG, foreground=FG,
                fieldbackground=BG3, troughcolor=BG2,
                selectbackground=SEL_BG, selectforeground=FG,
                font=FONT)
            s.configure("TFrame",  background=BG)
            s.configure("TLabel",  background=BG, foreground=FG)
            s.configure("TButton", background=BG3, foreground=FG,
                        relief="flat", padding=(8, 4))
            s.map("TButton",
                  background=[("active", ACCENT), ("pressed", ACCENT)],
                  foreground=[("active", BG2)])
            s.configure("Accent.TButton", background=ACCENT, foreground=BG2)
            s.map("Accent.TButton",
                  background=[("active", FG), ("pressed", FG)],
                  foreground=[("active", BG2)])
            s.configure("Warn.TButton", background=WARN, foreground=BG2)
            s.configure("TEntry",
                fieldbackground=BG3, foreground=FG, insertcolor=FG, relief="flat")
            s.configure("TCombobox",
                fieldbackground=BG3, foreground=FG,
                selectbackground=SEL_BG, relief="flat")
            s.map("TCombobox",
                  fieldbackground=[("readonly", BG3)],
                  foreground=[("readonly", FG)])
            s.configure("Treeview",
                background=BG2, foreground=FG,
                fieldbackground=BG2, rowheight=22,
                borderwidth=0, relief="flat")
            s.configure("Treeview.Heading",
                background=BG3, foreground=ACCENT,
                relief="flat", font=(*FONT[:1], FONT[1], "bold"))
            s.map("Treeview",
                  background=[("selected", SEL_BG)],
                  foreground=[("selected", FG)])
            s.configure("Vertical.TScrollbar",
                background=BG3, troughcolor=BG2,
                arrowcolor=FG_DIM, relief="flat", width=10)

        # ── UI layout ─────────────────────────────────────────────────────────
        def _build_ui(self):
            # top bar
            top = ttk.Frame(self, padding=(10, 8, 10, 6))
            top.pack(fill="x")
            ttk.Label(top, text="Archive", foreground=FG_DIM).pack(side="left")
            self._archive_var = tk.StringVar()
            ttk.Entry(top, textvariable=self._archive_var,
                      width=44).pack(side="left", padx=(6, 4))
            ttk.Button(top, text="Browse…",
                       command=self._browse_archive).pack(side="left", padx=(0, 4))
            ttk.Button(top, text="Load", style="Accent.TButton",
                       command=self._load_archive).pack(side="left", padx=(0, 16))
            ttk.Label(top, text="Output", foreground=FG_DIM).pack(side="left")
            self._outdir_var = tk.StringVar()
            ttk.Entry(top, textvariable=self._outdir_var,
                      width=28).pack(side="left", padx=(6, 4))
            ttk.Button(top, text="…",
                       command=self._pick_outdir).pack(side="left")

            # filter / action bar
            fbar = ttk.Frame(self, padding=(10, 0, 10, 6))
            fbar.pack(fill="x")
            ttk.Label(fbar, text="Filter", foreground=FG_DIM).pack(side="left")
            self._filter_var = tk.StringVar()
            self._filter_var.trace_add("write", self._on_filter_change)
            ttk.Entry(fbar, textvariable=self._filter_var,
                      width=24).pack(side="left", padx=(6, 10))
            ttk.Label(fbar, text="Codec", foreground=FG_DIM).pack(side="left")
            self._codec_var = tk.StringVar(value="All")
            codec_box = ttk.Combobox(
                fbar, textvariable=self._codec_var, width=14,
                state="readonly",
                values=["All"] + [f"{v} ({k})" for k, v in sorted(CODEC_NAMES.items())])
            codec_box.pack(side="left", padx=(6, 10))
            codec_box.bind("<<ComboboxSelected>>", lambda _: self._on_filter_change())
            ttk.Label(fbar, text="Bank", foreground=FG_DIM).pack(side="left")
            self._bank_var = tk.StringVar(value="All")
            self._bank_box = ttk.Combobox(
                fbar, textvariable=self._bank_var, width=14,
                state="readonly", values=["All"])
            self._bank_box.pack(side="left", padx=(6, 10))
            self._bank_box.bind("<<ComboboxSelected>>", lambda _: self._on_filter_change())
            self._btn_scan = ttk.Button(fbar, text="Scan Folder…",
                                        command=self._action_scan_folder)
            self._btn_scan.pack(side="left", padx=(0, 6))
            self._btn_scan.state(["disabled"])
            self._btn_replace_all = ttk.Button(fbar, text="Replace All  (0)",
                                               style="Accent.TButton",
                                               command=self._action_replace_all)
            self._btn_replace_all.pack(side="left", padx=(0, 10))
            self._btn_replace_all.state(["disabled"])
            ttk.Separator(fbar, orient="vertical").pack(side="left", fill="y", padx=(0, 8))
            ttk.Button(fbar, text="Open Project",
                       command=self._action_open_project).pack(side="left", padx=(0, 4))
            self._btn_save_project = ttk.Button(fbar, text="Save Project",
                                                command=self._action_save_project)
            self._btn_save_project.pack(side="left", padx=(0, 10))
            self._btn_save_project.state(["disabled"])
            self._status_var = tk.StringVar(value="Open an archive to begin.")
            ttk.Label(fbar, textvariable=self._status_var,
                      foreground=FG_DIM, font=FONT_SML).pack(side="right")

            # main area
            pane = ttk.Frame(self, padding=(10, 0, 10, 10))
            pane.pack(fill="both", expand=True)
            pane.columnconfigure(0, weight=3)
            pane.columnconfigure(1, weight=1, minsize=330)
            pane.rowconfigure(0, weight=1)

            # sample list
            list_frame = ttk.Frame(pane)
            list_frame.grid(row=0, column=0, sticky="nsew", padx=(0, 6))
            list_frame.rowconfigure(0, weight=1)
            list_frame.columnconfigure(0, weight=1)

            cols = ("alias", "path", "addr", "file", "codec", "size", "dur", "loop", "book", "pitch")
            self._tree = ttk.Treeview(list_frame, columns=cols,
                                      show="tree headings", selectmode="browse")
            self._tree.heading("alias", text="Alias",
                               command=lambda: self._sort_by("alias"))
            self._tree.heading("path",  text="Asset path",
                               command=lambda: self._sort_by("path"))
            self._tree.heading("addr",  text="Addr",
                               command=lambda: self._sort_by("addr"))
            self._tree.heading("file",  text="Replace With")
            self._tree.heading("codec", text="Codec",
                               command=lambda: self._sort_by("codec"))
            self._tree.heading("size",  text="Size",
                               command=lambda: self._sort_by("size"))
            self._tree.heading("dur",   text="Duration",
                               command=lambda: self._sort_by("pcm_samples"))
            self._tree.heading("loop",  text="Loop")
            self._tree.heading("book",  text="Book")
            self._tree.heading("pitch", text="Pitch",
                               command=lambda: self._sort_by("pitch"))
            self._tree.column("#0",    width=260, stretch=True)   # tree label column
            self._tree.column("alias", width=0,   stretch=False)  # hidden, kept for compat
            self._tree.column("path",  width=0,   stretch=False)  # hidden, kept for compat
            self._tree.column("addr",  width=88,  stretch=False, anchor="e")
            self._tree.column("file",  width=160, stretch=False)
            self._tree.column("codec", width=90,  stretch=False, anchor="center")
            self._tree.column("size",  width=80,  stretch=False, anchor="e")
            self._tree.column("dur",   width=76,  stretch=False, anchor="e")
            self._tree.column("loop",  width=46,  stretch=False, anchor="center")
            self._tree.column("book",  width=46,  stretch=False, anchor="center")
            self._tree.column("pitch", width=56,  stretch=False, anchor="center")

            vsb = ttk.Scrollbar(list_frame, orient="vertical",
                                command=self._tree.yview)
            self._tree.configure(yscrollcommand=vsb.set)
            self._tree.tag_configure("redirect", foreground=FG_DIM)
            self._tree.grid(row=0, column=0, sticky="nsew")
            vsb.grid(row=0, column=1, sticky="ns")

            self._tree.bind("<<TreeviewSelect>>", self._on_select)
            self._tree.bind("<Double-1>",         self._on_double_click)
            self._tree.bind("<Button-2>",         self._on_heading_menu)
            self._tree.bind("<Button-3>",         self._on_heading_menu)

            # detail panel
            detail = ttk.Frame(pane, padding=(10, 0, 0, 0))
            detail.grid(row=0, column=1, sticky="nsew")
            detail.columnconfigure(1, weight=1)

            ttk.Label(detail, text="Sample Details",
                      foreground=ACCENT,
                      font=(*FONT[:1], FONT[1]+1, "bold")).grid(
                row=0, column=0, columnspan=2, sticky="w", pady=(0, 8))

            self._detail_labels: dict[str, tk.StringVar] = {}
            detail_rows = [
                ("Path",      "path"),
                ("Canonical", "canonical"),
                ("Addr",      "addr"),
                ("Hash",      "hash"),
                ("Pitch",     "pitch"),
                ("Banks",     "banks"),
                ("Used by",   "used_by"),
                ("Codec",     "codec"),
                ("Medium",    "medium"),
                ("Size",      "size"),
                ("Duration",  "duration"),
                ("Loop",      "loop"),
                ("Book",      "book"),
            ]
            for i, (label, key) in enumerate(detail_rows, start=1):
                ttk.Label(detail, text=label, foreground=FG_DIM,
                          font=FONT_SML).grid(row=i, column=0, sticky="nw",
                                              padx=(0, 8), pady=2)
                var = tk.StringVar(value="—")
                self._detail_labels[key] = var
                ttk.Label(detail, textvariable=var, foreground=FG,
                          font=FONT_MON, wraplength=235,
                          justify="left").grid(row=i, column=1, sticky="nw", pady=2)

            # Alias — editable entry, auto-saved on Return / focus change
            alias_row = len(detail_rows) + 1
            ttk.Label(detail, text="Alias", foreground=FG_DIM,
                      font=FONT_SML).grid(row=alias_row, column=0, sticky="nw",
                                          padx=(0, 8), pady=(8, 2))
            self._alias_var = tk.StringVar()
            self._alias_entry = ttk.Entry(detail, textvariable=self._alias_var,
                                          font=FONT_MON)
            self._alias_entry.grid(row=alias_row, column=1, sticky="ew", pady=(8, 2))
            self._alias_entry.bind("<Return>",   lambda *_: self._save_alias())
            self._alias_entry.bind("<FocusOut>", lambda *_: self._save_alias())
            self._alias_entry.state(["disabled"])

            btn_row = len(detail_rows) + 4
            ttk.Frame(detail, height=1).grid(row=btn_row - 1, column=0, columnspan=2,
                                             sticky="ew", pady=(10, 8))

            self._btn_play = ttk.Button(detail, text="▶  Play",
                                        command=self._action_play)
            self._btn_play.grid(row=btn_row, column=0, columnspan=2,
                                sticky="ew", pady=2)

            self._btn_export = ttk.Button(detail, text="↓  Export",
                                          command=self._action_export)
            self._btn_export.grid(row=btn_row+1, column=0, columnspan=2,
                                  sticky="ew", pady=2)

            self._btn_assign = ttk.Button(detail, text="↔  Assign Audio…",
                                          command=self._assign_audio)
            self._btn_assign.grid(row=btn_row+2, column=0, columnspan=2,
                                  sticky="ew", pady=2)

            self._btn_export_aliases = ttk.Button(detail, text="⬆  Export Aliases…",
                                                   command=self._action_export_aliases)
            self._btn_export_aliases.grid(row=btn_row+3, column=0, columnspan=2,
                                          sticky="ew", pady=(10, 2))

            for btn in (self._btn_play, self._btn_export, self._btn_assign,
                        self._btn_export_aliases):
                btn.state(["disabled"])

        # ── loading ───────────────────────────────────────────────────────────
        def _browse_archive(self):
            path = filedialog.askopenfilename(
                title="Open o2r archive",
                filetypes=[("Starship archive", "*.o2r *.otr"), ("All", "*")])
            if path:
                self._archive_var.set(path)
                self._load_archive()

        def _load_archive(self):
            path = self._archive_var.get().strip()
            if not path or not os.path.isfile(path):
                self._status_var.set("Archive not found.")
                return
            if self._loading:
                return
            self._archive_path = path
            self._samples.clear()
            self._filtered.clear()
            self._aliases = {}
            self._alias_current_path = ""
            self._batch_mapping = {}
            if not self._outdir_var.get():
                self._outdir_var.set(os.path.dirname(os.path.abspath(path)))
            self._tree.delete(*self._tree.get_children())
            self._clear_detail()
            self._btn_scan.state(["disabled"])
            self._btn_replace_all.state(["disabled"])
            self._btn_export_aliases.state(["disabled"])
            self._bank_var.set("All")
            self._bank_box.configure(values=["All"])
            self._status_var.set("Loading…")
            self._loading = True
            threading.Thread(target=self._load_thread, daemon=True).start()

        def _load_thread(self):
            try:
                samples = list_samples(self._archive_path)
                self.after(0, self._load_done, samples, None)
            except Exception as e:
                self.after(0, self._load_done, [], str(e))

        def _load_done(self, samples: list[dict], error: str | None):
            self._loading = False
            if error:
                self._status_var.set(f"Error: {error}")
                return
            self._samples = samples
            self._aliases = load_aliases(self._archive_path)
            self._btn_scan.state(["!disabled"])
            self._btn_export_aliases.state(["!disabled"])
            self._btn_save_project.state(["!disabled"])
            all_banks = sorted({b for s in samples for b in s.get("banks", [])},
                               key=lambda p: _font_short(p))
            self._bank_box.configure(values=["All"] + all_banks)
            self._bank_var.set("All")
            self._apply_filter()

        # ── filtering ─────────────────────────────────────────────────────────
        def _on_filter_change(self, *_):
            self._apply_filter()

        def _get_codec_num(self) -> int:
            sel = self._codec_var.get()
            if sel != "All":
                try:
                    return int(sel.split("(")[1].rstrip(")"))
                except Exception:
                    pass
            return -1

        def _apply_filter(self, *_):
            self._refresh_tree()

        def _refresh_tree(self):
            self._tree.delete(*self._tree.get_children())
            self._node_map.clear()
            self._iids_by_path.clear()

            text      = self._filter_var.get().lower()
            codec_num = self._get_codec_num()
            bank_sel  = self._bank_var.get()

            def _matches(s: dict, p: dict | None) -> bool:
                """Return True if (sample, provenance_entry) passes all active filters."""
                if codec_num >= 0 and s["codec"] != codec_num:
                    return False
                if not text:
                    return True
                # Build all searchable strings for this leaf
                checks = [
                    s["path"],
                    self._aliases.get(s["path"], ""),
                    CODEC_NAMES.get(s["codec"], ""),
                    s.get("addr_str", ""),
                ]
                if p:
                    checks += [
                        p["font"],
                        _font_short(p["font"]),
                        p["inst_path"],
                        _path_tail(p["inst_path"]),
                        p["slot"],
                    ]
                return any(text in f.lower() for f in checks if f)

            # Build tree: font_path → inst_path → [(sample, slot, tuning)]
            font_inst: dict[str, dict[str, list]] = {}
            unassigned: list[dict] = []

            for s in self._samples:
                prov = s.get("provenance", [])
                if not prov:
                    # Unassigned — check against sample fields only
                    if bank_sel == "All" and _matches(s, None):
                        unassigned.append(s)
                    continue
                for p in prov:
                    if bank_sel != "All" and p["font"] != bank_sel:
                        continue
                    if not _matches(s, p):
                        continue
                    f = p["font"]
                    i = p["inst_path"]
                    font_inst.setdefault(f, {}).setdefault(i, []).append(
                        (s, p["slot"], p["tuning"]))

            leaf_counter = [0]
            leaf_total   = [0]

            def _insert_leaf(parent: str, s: dict, slot: str | None, tuning: float | None):
                iid  = f"leaf:{leaf_counter[0]}"
                leaf_counter[0] += 1
                leaf_total[0]   += 1
                alias    = self._aliases.get(s["path"], "")
                basename = os.path.basename(s["path"])
                label    = f"{alias}  ({basename})" if alias and alias != basename else basename
                slot_tag = f" [{slot[0].upper()}]" if slot else ""
                fmap     = self._batch_mapping.get(s["path"], "")
                dur      = _fmt_duration(s["pcm_samples"]) if s["pcm_samples"] else "—"
                is_redir = s.get("is_redirect", False)
                codec_c  = ("→ " if is_redir else "") + CODEC_NAMES.get(s["codec"], f"?({s['codec']})")
                eff_rate = round(tuning * AUDIO_REF_HZ) if tuning else _effective_rate(s)
                rate_str = f"~{eff_rate} Hz" if tuning else ""
                self._tree.insert(parent, "end", iid=iid,
                    text=label + slot_tag,
                    tags=("redirect",) if is_redir else (),
                    values=(
                        alias,
                        s["path"],
                        s.get("addr_str", ""),
                        os.path.basename(fmap) if fmap else "",
                        codec_c,
                        _fmt_size(s["size"]),
                        dur,
                        "✓" if s["has_loop"] else "",
                        "✓" if s["has_book"] else "",
                        _fmt_pitch_short([slot] if slot else s.get("pitch_roles", [])),
                    ))
                self._node_map[iid] = {
                    "leaf": True, "sample": s, "slot": slot, "tuning": tuning}
                self._iids_by_path.setdefault(s["path"], []).append(iid)

            _SLOT_ORDER = {"low": 0, "normal": 1, "high": 2, "drum": 3}

            for font_path in sorted(font_inst, key=_font_short):
                font_iid = f"font:{font_path}"
                self._tree.insert("", "end", iid=font_iid, open=True,
                    text=f"Bank  {_font_short(font_path)}")
                self._node_map[font_iid] = {"leaf": False}

                for inst_path in sorted(font_inst[font_path]):
                    inst_iid = f"inst:{font_path}:{inst_path}"
                    self._tree.insert(font_iid, "end", iid=inst_iid, open=True,
                        text=_path_tail(inst_path))
                    self._node_map[inst_iid] = {"leaf": False}

                    entries = font_inst[font_path][inst_path]
                    entries.sort(key=lambda e: _SLOT_ORDER.get(e[1], 99))
                    for s, slot, tuning in entries:
                        _insert_leaf(inst_iid, s, slot, tuning)

            if unassigned:
                u_iid = "__unassigned__"
                self._tree.insert("", "end", iid=u_iid, open=not text,
                    text="Unassigned")
                self._node_map[u_iid] = {"leaf": False}
                for s in sorted(unassigned, key=lambda x: x["path"]):
                    _insert_leaf(u_iid, s, None, None)

            # Collect unique samples visible in the tree (for batch scan / replace)
            seen: set[str] = set()
            self._filtered = []
            for nd in self._node_map.values():
                if nd.get("leaf"):
                    p = nd["sample"]["path"]
                    if p not in seen:
                        seen.add(p)
                        self._filtered.append(nd["sample"])

            n     = leaf_total[0]
            total = len(self._samples)
            self._status_var.set(
                f"{n} shown / {total} total" if n != total else f"{n} samples")

        # ── sort context menu ─────────────────────────────────────────────────
        def _on_heading_menu(self, event):
            region = self._tree.identify("region", event.x, event.y)
            if region != "heading":
                return
            menu = tk.Menu(self, tearoff=0)
            menu.configure(bg=BG3, fg=FG, activebackground=SEL_BG,
                           activeforeground=FG, relief="flat")
            for label, col in (
                ("Sort by Path  (A → Z)",       "path"),
                ("Sort by Alias  (A → Z)",      "alias"),
                ("Sort by Address  (↑)",         "addr"),
                ("Sort by CRC64 Hash  (↑)",      "hash"),
                ("Sort by Pitch  (L → N → H → D)", "pitch"),
                ("Sort by Bank",                 "bank"),
                ("Sort by Codec",                "codec"),
                ("Sort by Size",                 "size"),
                ("Sort by Duration",             "pcm_samples"),
            ):
                menu.add_command(label=label,
                                 command=lambda c=col: self._sort_by(c))
            menu.post(event.x_root, event.y_root)

        # ── sorting ───────────────────────────────────────────────────────────
        _sort_asc = True
        _sort_col = "path"

        def _sort_by(self, col: str):
            if self._sort_col == col:
                self._sort_asc = not self._sort_asc
            else:
                self._sort_col = col
                self._sort_asc = True
            if col == "alias":
                self._filtered.sort(
                    key=lambda s: self._aliases.get(s["path"], "").lower(),
                    reverse=not self._sort_asc)
            elif col == "addr":
                self._filtered.sort(
                    key=lambda s: s.get("addr", 0),
                    reverse=not self._sort_asc)
            elif col == "hash":
                self._filtered.sort(
                    key=lambda s: s.get("hash", 0),
                    reverse=not self._sort_asc)
            elif col == "pitch":
                self._filtered.sort(
                    key=lambda s: (
                        [_PITCH_ORDER.index(r) if r in _PITCH_ORDER else 99
                         for r in s.get("pitch_roles", [])] or [99]
                    ),
                    reverse=not self._sort_asc)
            elif col == "bank":
                self._filtered.sort(
                    key=lambda s: sorted(_font_short(b) for b in s.get("banks", [])) or [""],
                    reverse=not self._sort_asc)
            else:
                key_map = {"path": "path", "codec": "codec",
                           "size": "size", "pcm_samples": "pcm_samples"}
                key = key_map.get(col, "path")
                self._filtered.sort(key=lambda s: s[key], reverse=not self._sort_asc)
            self._refresh_tree()

        # ── selection ─────────────────────────────────────────────────────────
        def _selected_sample(self) -> tuple[dict | None, str | None, float | None]:
            """Return (sample, slot, slot_tuning) for the selected leaf, or (None, None, None)."""
            sel = self._tree.selection()
            if not sel:
                return None, None, None
            nd = self._node_map.get(sel[0])
            if nd and nd.get("leaf"):
                s     = nd["sample"]
                slot  = nd["slot"]
                t     = nd["tuning"]
                if t is None:
                    t = _effective_rate(s) / AUDIO_REF_HZ if s.get("tuning") else None
                return s, slot, t
            return None, None, None

        def _on_select(self, _event):
            self._commit_alias()
            s, slot, slot_tuning = self._selected_sample()
            if s is None:
                self._clear_detail()
                return

            self._alias_current_path = s["path"]
            self._alias_var.set(self._aliases.get(s["path"], ""))
            self._alias_entry.state(["!disabled"])

            self._detail_labels["path"].set(s["path"])
            self._detail_labels["canonical"].set(
                s.get("canonical_path") or "—")
            self._detail_labels["addr"].set(s.get("addr_str") or "—")
            self._detail_labels["hash"].set(
                f"0x{s['hash']:016X}" if s.get("hash") is not None else "—")
            pitch_label = slot.capitalize() if slot else _fmt_pitch_long(s.get("pitch_roles", []))
            self._detail_labels["pitch"].set(pitch_label)
            banks = s.get("banks", [])
            self._detail_labels["banks"].set(
                "\n".join(_font_short(b) for b in banks) if banks else "—")
            used_by = s.get("used_by", [])
            self._detail_labels["used_by"].set(
                "\n".join(used_by[:8]) + ("\n…" if len(used_by) > 8 else "")
                if used_by else "—")
            codec_str = CODEC_NAMES.get(s["codec"], f"?({s['codec']})")
            if s.get("is_redirect"):
                codec_str = "→ " + codec_str
            self._detail_labels["codec"].set(codec_str)
            self._detail_labels["medium"].set(
                f"{MEDIUM_NAMES.get(s['medium'], '?')}  ({s['medium']})")
            self._detail_labels["size"].set(f"{s['size']:,} bytes")

            # Duration + sample rate — use slot-specific tuning when available
            rate = round(slot_tuning * AUDIO_REF_HZ) if slot_tuning else _effective_rate(s)
            if s["pcm_samples"]:
                prefix = f"{s['adpcm_frames']:,} frames × 16 = " if s["adpcm_frames"] else ""
                if slot_tuning is not None:
                    rate_note = f"~{rate} Hz  [{slot or 'normal'}]"
                elif s.get("tuning") is not None:
                    rate_note = f"~{rate} Hz"
                    if len(s.get("all_tunings", [])) > 1:
                        rate_note += f"  ({len(s['all_tunings'])} tunings)"
                else:
                    rate_note = f"{MIXER_RATE_HZ} Hz (unknown)"
                self._detail_labels["duration"].set(
                    f"{prefix}{s['pcm_samples']:,} smps\n"
                    f"~{_fmt_duration(s['pcm_samples'], rate)} @ {rate_note}")
            else:
                self._detail_labels["duration"].set("—")

            # Loop
            ld = s.get("loop_data")
            if not s["has_loop"]:
                self._detail_labels["loop"].set("none")
            elif ld is None:
                self._detail_labels["loop"].set(
                    f"yes\n(hash 0x{s['loop_hash']:016X}\ndata unavailable)")
            else:
                cnt = "∞" if ld["count"] == LOOP_INFINITE else str(ld["count"])
                self._detail_labels["loop"].set(
                    f"start  {ld['start']:,}\n"
                    f"end    {ld['end']:,}\n"
                    f"count  {cnt}")

            # Book
            bd = s.get("book_data")
            if not s["has_book"]:
                self._detail_labels["book"].set("none")
            elif bd is None:
                self._detail_labels["book"].set(
                    f"yes\n(hash 0x{s['book_hash']:016X}\ndata unavailable)")
            else:
                n_coef = bd["order"] * bd["num_predictors"] * 8
                self._detail_labels["book"].set(
                    f"order        {bd['order']}\n"
                    f"predictors   {bd['num_predictors']}\n"
                    f"coefficients {n_coef}")

            # Buttons — play is enabled whenever the codec is decodable;
            # missing ffplay is reported on click, not silently here.
            can_play = (s["codec"] == 5 or
                        (s["codec"] == 0 and s.get("book_data") is not None))
            for btn in (self._btn_export, self._btn_assign):
                btn.state(["!disabled"])
            if can_play:
                self._btn_play.state(["!disabled"])
            else:
                self._btn_play.state(["disabled"])

        def _on_double_click(self, _event):
            s, _slot, _t = self._selected_sample()
            if s:
                self._assign_audio_to(s)

        def _clear_detail(self):
            for var in self._detail_labels.values():
                var.set("—")
            self._alias_var.set("")
            self._alias_current_path = ""
            self._alias_entry.state(["disabled"])
            for btn in (self._btn_play, self._btn_export, self._btn_assign):
                btn.state(["disabled"])

        # ── alias helpers ─────────────────────────────────────────────────────
        def _commit_alias(self):
            path = self._alias_current_path
            if not path or not self._archive_path:
                return
            alias = self._alias_var.get().strip()
            current = self._aliases.get(path, "")
            if alias == current:
                return
            if alias:
                self._aliases[path] = alias
            else:
                self._aliases.pop(path, None)
            save_aliases(self._archive_path, self._aliases)
            # Update tree node text for all leaves of this path
            for iid in self._iids_by_path.get(path, []):
                try:
                    nd       = self._node_map.get(iid, {})
                    slot     = nd.get("slot")
                    basename = os.path.basename(path)
                    label    = f"{alias}  ({basename})" if alias and alias != basename else basename
                    slot_tag = f" [{slot[0].upper()}]" if slot else ""
                    self._tree.item(iid, text=label + slot_tag)
                    self._tree.set(iid, "alias", alias)
                except Exception:
                    pass

        def _save_alias(self):
            self._commit_alias()

        def _action_export_aliases(self):
            if not self._aliases:
                messagebox.showinfo("No aliases",
                                    "No aliases defined yet.\n\n"
                                    "Select a sample and type an alias in the Alias field.",
                                    parent=self)
                return
            default_name = (os.path.splitext(os.path.basename(self._archive_path))[0]
                            + "_aliases.json")
            out = filedialog.asksaveasfilename(
                title="Export aliases",
                defaultextension=".json",
                initialfile=default_name,
                filetypes=[("JSON", "*.json"), ("All", "*")])
            if out:
                export_aliases_to(self._aliases, out)
                messagebox.showinfo(
                    "Exported",
                    f"Exported {len(self._aliases)} alias(es) to:\n{out}",
                    parent=self)

        # ── actions ───────────────────────────────────────────────────────────
        def _action_play(self):
            s, slot, slot_tuning = self._selected_sample()
            if s is None:
                return
            result = _decode_sample(s, slot_tuning)
            if result is None:
                messagebox.showinfo(
                    "Cannot play",
                    f"Codec {CODEC_NAMES.get(s['codec'], s['codec'])} is not "
                    f"supported for playback, or book data is missing.",
                    parent=self)
                return
            pcm, rate = result
            if not shutil.which("ffplay"):
                if sys.platform == "darwin":
                    hint = "Install ffmpeg via Homebrew:\n  brew install ffmpeg"
                elif sys.platform.startswith("win"):
                    hint = "Install ffmpeg and add it to PATH:\n  https://ffmpeg.org/download.html"
                else:
                    hint = "Install ffmpeg (e.g. sudo apt install ffmpeg)"
                messagebox.showwarning(
                    "ffplay not found",
                    f"ffplay is required for audio playback but was not found.\n\n{hint}",
                    parent=self)
                return

            def _run():
                try:
                    _play_pcm_wav(pcm, rate)
                except Exception:
                    pass

            threading.Thread(target=_run, daemon=True).start()

        def _action_export(self):
            s, slot, slot_tuning = self._selected_sample()
            if not s:
                return

            codec = s["codec"]

            eff_rate = round(slot_tuning * AUDIO_REF_HZ) if slot_tuning else _effective_rate(s)
            slot_note = f" [{slot}]" if slot and slot != "normal" else ""

            if codec == 5:
                out = filedialog.asksaveasfilename(
                    title="Export sample", defaultextension=".wav",
                    initialfile=os.path.basename(s["path"]) + ".wav",
                    filetypes=[("WAV", "*.wav"), ("All", "*")])
                if out:
                    _write_wav(s["raw"], out, rate=eff_rate)
                    messagebox.showinfo("Exported",
                        f"Saved WAV to:\n{out}\n\nRate: {eff_rate} Hz{slot_note}")

            elif codec == 0:
                choice = filedialog.asksaveasfilename(
                    title="Export ADPCM sample",
                    initialfile=os.path.basename(s["path"]),
                    filetypes=[("Decoded WAV", "*.wav"),
                               ("Raw ADPCM binary", "*.bin"),
                               ("All", "*")])
                if not choice:
                    return
                if choice.lower().endswith(".wav"):
                    if s.get("book_data") is None:
                        messagebox.showerror("Error",
                            "No book data available — cannot decode ADPCM.")
                        return
                    self._status_var.set("Decoding ADPCM…")
                    self.update_idletasks()
                    pcm  = vadpcm_to_pcm(s["raw"], s["book_data"])
                    _write_wav(pcm, choice, rate=eff_rate)
                    self._status_var.set(f"{len(self._filtered)} samples")
                    rate_note = f"{eff_rate} Hz{slot_note}"
                    messagebox.showinfo("Exported",
                        f"Decoded WAV saved to:\n{choice}\n\nSample rate: {rate_note}")
                else:
                    with open(choice, "wb") as f:
                        f.write(s["raw"])
                    messagebox.showinfo("Exported",
                        f"Raw ADPCM ({_fmt_size(s['size'])}) saved to:\n{choice}")

            else:
                out = filedialog.asksaveasfilename(
                    title="Export raw sample data",
                    defaultextension=".bin",
                    initialfile=os.path.basename(s["path"]) + ".bin",
                    filetypes=[("Raw binary", "*.bin"), ("All", "*")])
                if out:
                    with open(out, "wb") as f:
                        f.write(s["raw"])
                    messagebox.showinfo("Exported",
                        f"Saved {_fmt_size(s['size'])} of raw "
                        f"{CODEC_NAMES.get(codec, '?')} to:\n{out}")

        # ── batch assign / replace ────────────────────────────────────────────
        def _pick_outdir(self):
            d = filedialog.askdirectory(parent=self,
                                        title="Select output directory")
            if d:
                self._outdir_var.set(d)

        def _assign_audio_to(self, s: dict):
            path  = s["path"]
            audio = filedialog.askopenfilename(
                parent=self,
                title=f"Assign audio to {os.path.basename(path)}",
                filetypes=[("Audio files", "*.wav *.ogg *.mp3"),
                           ("WAV", "*.wav"), ("OGG", "*.ogg"),
                           ("MP3", "*.mp3"), ("All", "*")])
            if audio:
                self._batch_mapping[path] = audio
                for iid in self._iids_by_path.get(path, []):
                    try:
                        self._tree.set(iid, "file", os.path.basename(audio))
                    except Exception:
                        pass
                self._update_replace_all_btn()

        def _assign_audio(self):
            s, _slot, _t = self._selected_sample()
            if s:
                self._assign_audio_to(s)

        def _update_replace_all_btn(self):
            n = len(self._batch_mapping)
            self._btn_replace_all.configure(text=f"Replace All  ({n})")
            self._btn_replace_all.state(["!disabled"] if n else ["disabled"])

        def _action_scan_folder(self):
            if not self._samples:
                return
            folder = filedialog.askdirectory(parent=self,
                                             title="Folder with audio files")
            if not folder:
                return
            audio_map: dict[str, str] = {}
            for fname in os.listdir(folder):
                ext = os.path.splitext(fname)[1].lower()
                if ext in (".wav", ".ogg", ".mp3"):
                    key = os.path.splitext(fname)[0].lower()
                    audio_map[key] = os.path.join(folder, fname)

            matched = 0
            for s in self._samples:
                p         = s["path"]
                bname     = os.path.basename(p).lower()
                alias     = self._aliases.get(p, "")
                alias_key = alias.lower().replace(" ", "_") if alias else None
                hit       = audio_map.get(bname) or (
                    alias_key and audio_map.get(alias_key))
                if hit:
                    self._batch_mapping[p] = hit
                    for iid in self._iids_by_path.get(p, []):
                        try:
                            self._tree.set(iid, "file", os.path.basename(hit))
                        except Exception:
                            pass
                    matched += 1

            self._update_replace_all_btn()
            self._status_var.set(
                f"Matched {matched} / {len(self._samples)} from folder.")

        def _action_replace_all(self):
            if not self._batch_mapping:
                return
            out_dir = self._outdir_var.get().strip()
            if not out_dir:
                out_dir = os.path.dirname(os.path.abspath(self._archive_path))
            os.makedirs(out_dir, exist_ok=True)
            items = list(self._batch_mapping.items())
            self._btn_replace_all.state(["disabled"])
            self._btn_scan.state(["disabled"])

            def worker():
                errors: list[str] = []
                n = len(items)
                for i, (sp, ap) in enumerate(items):
                    self.after(0, self._status_var.set,
                               f"Replacing {i + 1} / {n}…")
                    try:
                        _do_replace(self._archive_path, sp, ap, out_dir)
                        def _mark_ok(p=sp, a=ap):
                            for iid in self._iids_by_path.get(p, []):
                                try: self._tree.set(iid, "file", "✓ " + os.path.basename(a))
                                except Exception: pass
                        self.after(0, _mark_ok)
                    except Exception as e:
                        errors.append(f"{os.path.basename(sp)}: {e}")
                        def _mark_err(p=sp):
                            for iid in self._iids_by_path.get(p, []):
                                try: self._tree.set(iid, "file", "✗")
                                except Exception: pass
                        self.after(0, _mark_err)
                self.after(0, self._replace_all_done,
                           n - len(errors), errors, out_dir)

            threading.Thread(target=worker, daemon=True).start()

        def _replace_all_done(self, done: int,
                              errors: list[str], out_dir: str):
            self._btn_scan.state(["!disabled"])
            self._update_replace_all_btn()
            mod_name = os.path.splitext(os.path.basename(self._archive_path))[0]
            mod_o2r  = os.path.join(out_dir,
                                    f"{mod_name}_audio_replacements.o2r")
            if errors:
                self._status_var.set(
                    f"Done: {done} replaced, {len(errors)} failed.")
                messagebox.showerror(
                    "Errors",
                    f"{done} replaced, {len(errors)} failed:\n\n"
                    + "\n".join(errors[:15])
                    + ("\n…" if len(errors) > 15 else ""),
                    parent=self)
            else:
                self._status_var.set(f"Replaced {done} sample(s).")
                messagebox.showinfo(
                    "Done",
                    f"Replaced {done} sample(s).\n\n"
                    f"Mod archive:\n{mod_o2r}\n\n"
                    f"Place it in the mods/ folder to apply.",
                    parent=self)

        def _action_open_project(self):
            path = filedialog.askopenfilename(
                title="Open Project",
                filetypes=[("Sample editor project", "*.json"), ("All files", "*.*")],
                parent=self)
            if not path:
                return
            try:
                proj = load_project(path)
            except Exception as e:
                messagebox.showerror("Error", f"Could not load project:\n{e}", parent=self)
                return
            self._project_path = path
            self.title(f"Starship Sample Editor — {os.path.basename(path)}")
            # Load archive if it's different from the current one
            if proj["archive"] and proj["archive"] != self._archive_path:
                self._archive_var.set(proj["archive"])
                self._load_archive()
            # Populate output dir
            if proj["out_dir"]:
                self._outdir_var.set(proj["out_dir"])
            # Populate batch mapping from project replacements
            valid = {a: p for a, p in proj["replacements"].items() if os.path.isfile(p)}
            missing = [a for a in proj["replacements"] if a not in valid]
            self._batch_mapping.update(valid)
            self._update_replace_all_btn()
            # Update tree "Replace With" column for loaded entries
            for asset, audio in valid.items():
                for iid in self._iids_by_path.get(asset, []):
                    try:
                        self._tree.set(iid, "file", os.path.basename(audio))
                    except Exception:
                        pass
            msg = f"Loaded project: {len(valid)} replacement(s)."
            if missing:
                msg += f"\n\n{len(missing)} audio file(s) not found (paths may need updating):\n"
                msg += "\n".join(f"  {a}" for a in missing[:10])
                if len(missing) > 10:
                    msg += "\n  …"
                messagebox.showwarning("Missing Files", msg, parent=self)
            else:
                self._status_var.set(msg)

        def _action_save_project(self):
            if not self._archive_path:
                return
            init = self._project_path or _project_default_path(self._archive_path)
            path = filedialog.asksaveasfilename(
                title="Save Project",
                initialfile=os.path.basename(init),
                initialdir=os.path.dirname(init),
                defaultextension=".json",
                filetypes=[("Sample editor project", "*.json"), ("All files", "*.*")],
                parent=self)
            if not path:
                return
            out_dir = self._outdir_var.get().strip() or os.path.dirname(
                os.path.abspath(self._archive_path))
            try:
                save_project(path, self._archive_path, out_dir, self._batch_mapping)
            except Exception as e:
                messagebox.showerror("Error", f"Could not save project:\n{e}", parent=self)
                return
            self._project_path = path
            self.title(f"Starship Sample Editor — {os.path.basename(path)}")
            self._status_var.set(
                f"Project saved: {len(self._batch_mapping)} replacement(s)  →  {os.path.basename(path)}")

    App().mainloop()


# ─── entry point ─────────────────────────────────────────────────────────────

def main():
    parser = argparse.ArgumentParser(
        description="Starship sample editor — browse, export, replace audio in o2r archives.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    sub = parser.add_subparsers(dest="command")

    p_list = sub.add_parser("list",    help="List samples.")
    p_list.add_argument("archive")
    p_list.add_argument("--filter", metavar="TEXT")
    p_list.add_argument("--codec",  type=int, metavar="N")

    p_info = sub.add_parser("info",    help="Show details for one sample.")
    p_info.add_argument("archive")
    p_info.add_argument("asset", metavar="ASSET_PATH")

    p_exp  = sub.add_parser("export",  help="Export sample data.")
    p_exp.add_argument("archive")
    p_exp.add_argument("asset", metavar="ASSET_PATH")
    p_exp.add_argument("--out",    metavar="FILE")
    p_exp.add_argument("--decode", action="store_true",
                       help="Decode ADPCM to WAV instead of raw export.")

    p_play = sub.add_parser("play",    help="Play a sample (S16 or ADPCM) via ffplay.")
    p_play.add_argument("archive")
    p_play.add_argument("asset", metavar="ASSET_PATH")

    p_rep  = sub.add_parser("replace", help="Replace a sample with custom audio.")
    p_rep.add_argument("archive")
    p_rep.add_argument("asset", metavar="ASSET_PATH")
    p_rep.add_argument("--input",   required=True, metavar="AUDIO_FILE")
    p_rep.add_argument("--out-dir", metavar="DIR")

    p_bat  = sub.add_parser("batch-replace",
                             help="Replace many samples at once from a folder or mapping file.")
    p_bat.add_argument("archive")
    src = p_bat.add_mutually_exclusive_group(required=True)
    src.add_argument("--dir",     metavar="FOLDER",
                     help="Folder to scan; matches audio files to samples by basename.")
    src.add_argument("--mapping", metavar="JSON_FILE",
                     help="JSON file with { \"asset/path\": \"audio/file.wav\", … }.")
    p_bat.add_argument("--out-dir", metavar="DIR",
                       help="Output directory for the mod o2r (default: archive directory).")

    p_sproj = sub.add_parser("save-project",
                              help="Add or update a replacement entry in a project file.")
    p_sproj.add_argument("archive")
    p_sproj.add_argument("asset", metavar="ASSET_PATH")
    p_sproj.add_argument("--input",   required=True, metavar="AUDIO_FILE",
                         help="Replacement audio file to record in the project.")
    p_sproj.add_argument("--project", metavar="JSON_FILE",
                         help="Project file to write (default: <archive>_project.json).")
    p_sproj.add_argument("--out-dir", metavar="DIR",
                         help="Output directory to store in the project.")

    p_aproj = sub.add_parser("apply-project",
                              help="Re-apply all replacements recorded in a project file.")
    p_aproj.add_argument("project", metavar="PROJECT_FILE")
    p_aproj.add_argument("--out-dir", metavar="DIR",
                         help="Override output directory from the project.")

    p_al   = sub.add_parser("alias",
                             help="Get or set a human-readable alias for a sample.")
    p_al.add_argument("archive")
    p_al.add_argument("asset",  metavar="ASSET_PATH")
    p_al.add_argument("alias",  nargs="?", default=None, metavar="ALIAS",
                      help="New alias text. Omit to read; pass empty string to remove.")

    p_exal = sub.add_parser("export-aliases",
                             help="Export all aliases to a JSON file.")
    p_exal.add_argument("archive")
    p_exal.add_argument("--out", metavar="FILE",
                        help="Output path (default: <archive>_aliases_export.json)")

    p_gui  = sub.add_parser("gui",     help="Launch graphical interface (default).")
    p_gui.add_argument("archive", nargs="?", default=None)

    args = parser.parse_args()
    if args.command is None:
        args.command = "gui"
        args.archive = None

    {
        "list":           cmd_list,
        "info":           cmd_info,
        "export":         cmd_export,
        "play":           cmd_play,
        "replace":        cmd_replace,
        "batch-replace":  cmd_batch_replace,
        "save-project":   cmd_save_project,
        "apply-project":  cmd_apply_project,
        "alias":          cmd_alias,
        "export-aliases": cmd_export_aliases,
        "gui":            cmd_gui,
    }[args.command](args)


if __name__ == "__main__":
    main()
