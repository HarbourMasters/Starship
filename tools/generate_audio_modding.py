#!/usr/bin/env python3
"""
Update the audio sample entries in src/assets/modding.yml so that replacement
files can be placed at human-readable alias paths instead of hex paths.

Before:
  ast_audio/ast_audio_v1_sample_100E0: ast_audio/ast_audio_v1_sample_100E0

After:
  ast_audio/ast_audio_v1_sample_100E0: ast_audio/se_ding

Entries without an alias are left unchanged.
"""

import json
import re
import sys
from pathlib import Path

ROOT        = Path(__file__).resolve().parent.parent
ALIASES_JSON = ROOT / "sf64_aliases.json"
MODDING_YML  = ROOT / "src" / "assets" / "modding.yml"


def main() -> None:
    with open(ALIASES_JSON) as f:
        aliases: dict[str, str] = json.load(f)["aliases"]
    # aliases: {"ast_audio/ast_audio_v1_sample_100E0": "se_ding", ...}

    text  = MODDING_YML.read_text()
    lines = text.splitlines(keepends=True)
    out   = []
    changed = 0
    skipped = 0

    sample_re = re.compile(
        r'^(\s+)(ast_audio/ast_audio_v1_sample_[0-9A-Fa-f]+)'
        r':\s*(ast_audio/ast_audio_v1_sample_[0-9A-Fa-f]+)\s*$'
    )

    for line in lines:
        m = sample_re.match(line)
        if m:
            indent   = m.group(1)
            key      = m.group(2)   # archive key (kept as-is)
            if key in aliases:
                alias     = aliases[key]
                directory = key.split("/")[0]
                new_value = f"{directory}/{alias}"
                out.append(f"{indent}{key}: {new_value}\n")
                changed += 1
            else:
                out.append(line)
                skipped += 1
        else:
            out.append(line)

    MODDING_YML.write_text("".join(out))
    print(f"Updated {changed} entries, {skipped} sample entries had no alias (left unchanged)")
    print(f"Written to {MODDING_YML.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
