#!/usr/bin/env python3
"""
Generate explicit NAUDIO:V1:SAMPLE YAML entries for every entry in sf64_aliases.json
and append them to ast_audio.yaml AFTER audio_soundfont_table.

Ordering matters: Torch has two phases:
  1. Pre-register all YAML offsets in gAddrMap (blocks auto-generation cascade)
  2. ParseNode in YAML order — explicit entries need FONT_TABLE.entries populated,
     which only happens after audio_soundfont_table processes.

Reads the soundfont table from sf64.o2r to recover `parent` and `sampleBankId`
for each sample (both required fields that are not stored in the aliases JSON).
"""

import bisect
import json
import re
import struct
import sys
import zipfile
from pathlib import Path

ROOT         = Path(__file__).resolve().parent.parent
ALIASES_JSON = ROOT / "sf64_aliases.json"
O2R_PATH     = ROOT / "test" / "sf64.o2r"
# Entries are appended to ast_audio.yaml itself, after audio_soundfont_table.
AUDIO_YAML   = ROOT / "assets" / "yaml" / "us" / "rev1" / "ast_audio.yaml"
# Sentinel: entries go after this key (last table entry that must precede samples).
AFTER_KEY    = "audio_seq_font_table:"

OTR_HEADER = 64  # bytes

# ── binary helpers ────────────────────────────────────────────────────────────

def _u8(data, off):  return struct.unpack_from("<B", data, off)[0]
def _i16(data, off): return struct.unpack_from("<h", data, off)[0]
def _u32(data, off): return struct.unpack_from("<I", data, off)[0]
def _u64(data, off): return struct.unpack_from("<Q", data, off)[0]


def parse_soundfont_table(raw: bytes) -> list[dict]:
    """Return list of {addr, size, bankId} sorted by addr, derived from the
    binary AudioTable entry for the SOUNDFONT format."""
    body = raw[OTR_HEADER:]
    # int16 medium, uint32 addr, uint32 count
    count = _u32(body, 6)
    ENTRY = 20  # crc(8) + size(4) + medium(1) + policy(1) + sd1(2) + sd2(2) + sd3(2)
    entries = []
    off = 10
    for _ in range(count):
        sz   = _u32(body, off + 8)
        sd1  = _i16(body, off + 14)
        entries.append({"sz": sz, "bankId": (sd1 >> 8) & 0xFF})
        off += ENTRY
    return entries


def build_font_ranges(sf_paths: list[str], font_info: list[dict]) -> list[tuple]:
    """Return sorted list of (addr, end_addr, bankId) — one per SoundFont."""
    addrs = []
    for path in sf_paths:
        m = re.search(r"sound_font_([0-9A-Fa-f]+)$", path)
        if m:
            addrs.append(int(m.group(1), 16))
    addrs.sort()

    ranges = []
    for i, (addr, info) in enumerate(zip(addrs, font_info)):
        end = addr + info["sz"]
        ranges.append((addr, end, info["bankId"]))
    return sorted(ranges)


def find_font(ranges: list[tuple], offset: int):
    """Binary search: return (parent, bankId) for the SoundFont that owns offset."""
    lo, hi = 0, len(ranges) - 1
    while lo <= hi:
        mid = (lo + hi) // 2
        addr, end, bankId = ranges[mid]
        if addr <= offset < end:
            return addr, bankId
        elif offset < addr:
            hi = mid - 1
        else:
            lo = mid + 1
    return None, None


# ── main ──────────────────────────────────────────────────────────────────────

def main() -> None:
    with open(ALIASES_JSON) as f:
        aliases: dict[str, str] = json.load(f)["aliases"]
    # {archive_path: alias}  e.g. {"ast_audio/ast_audio_v1_sample_100E0": "se_ding"}

    with zipfile.ZipFile(O2R_PATH) as z:
        names = z.namelist()
        sf_paths = sorted(n for n in names if "sound_font" in n)
        font_table_raw = z.read("ast_audio/audio_soundfont_table")

    font_info   = parse_soundfont_table(font_table_raw)
    font_ranges = build_font_ranges(sf_paths, font_info)

    # Resolve each archive path to (alias, offset, parent, bankId), then
    # deduplicate by alias — keep the entry with the lowest offset so that
    # the canonical sample (the first one encountered by Torch) is documented.
    canonical: dict[str, tuple] = {}   # alias → (offset, parent, bankId)
    skipped = 0

    for archive_path, alias in aliases.items():
        m = re.search(r"_sample_([0-9A-Fa-f]+)$", archive_path)
        if not m:
            skipped += 1
            continue

        offset = int(m.group(1), 16)
        parent, bank_id = find_font(font_ranges, offset)

        if parent is None:
            print(f"WARNING: no font found for {alias} (offset 0x{offset:X})", file=sys.stderr)
            skipped += 1
            continue

        # Keep the occurrence with the smallest offset as canonical.
        if alias not in canonical or offset < canonical[alias][0]:
            canonical[alias] = (offset, parent, bank_id)

    # Build the new sample block.
    sample_lines: list[str] = [
        "\n",
        "# --- auto-generated sample entries (tools/generate_sample_yaml.py) ---\n",
        "# Must stay AFTER audio_soundfont_table so FONT_TABLE.entries is populated\n",
        "# when Torch parses these in phase 2.\n",
        "\n",
    ]
    for alias, (offset, parent, bank_id) in sorted(canonical.items()):
        sample_lines.append(f"{alias}:\n")
        sample_lines.append(f"  type: NAUDIO:V1:SAMPLE\n")
        sample_lines.append(f"  offset: 0x{offset:X}\n")
        sample_lines.append(f"  parent: 0x{parent:X}\n")
        sample_lines.append(f"  sampleBankId: {bank_id}\n")
        sample_lines.append(f"  symbol: {alias}\n")
        sample_lines.append("\n")

    # Read existing ast_audio.yaml, strip any previously generated block, then
    # re-append the fresh block after AFTER_KEY.
    existing = AUDIO_YAML.read_text()

    # Strip old generated block (everything from the sentinel comment onward).
    gen_marker = "\n# --- auto-generated sample entries"
    if gen_marker in existing:
        existing = existing[: existing.index(gen_marker)]

    # Find the end of the AFTER_KEY entry so we can insert after it.
    idx = existing.find(AFTER_KEY)
    if idx == -1:
        print(f"ERROR: '{AFTER_KEY}' not found in {AUDIO_YAML}", file=sys.stderr)
        sys.exit(1)

    # Advance past the entire AFTER_KEY block (until next blank line or EOF).
    end = existing.find("\n\n", idx)
    insert_at = end if end != -1 else len(existing)

    result = existing[:insert_at] + "".join(sample_lines)
    AUDIO_YAML.write_text(result)
    print(f"Appended {len(canonical)} unique sample entries to {AUDIO_YAML.relative_to(ROOT)}")
    if skipped:
        print(f"Skipped {skipped} entries (no matching font range)")


if __name__ == "__main__":
    main()
