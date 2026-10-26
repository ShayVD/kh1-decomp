#!/usr/bin/env python3
"""The pointers in an overlay's data part, for a port that runs the overlay as native C
(docs/native-overlays.md, include/platform/ovl.h).

  python3 -I tools/ovl/relocs.py NAME     # writes ovl/NAME/relocs.tsv from out/overlays/NAME.x

On the PS2 a word in the overlay's data that holds 0x00F2xxxx is a pointer into the overlay
itself: a function (a callback table) or more data. A port loads the same bytes into its
memory map, so after each load host/port/ovl.c rewrites those words: a function's to the
native function, a data address's to the memory map's. A word that points inside a function
(the jump tables gcc wrote for the PS2 code's switches) is left alone: the native C has its
own switches. Words are found by value (the overlay area 0x00F20000 - 0x00FE0000), so check
new rows by eye: an integer in that range would be taken for a pointer.

Only addresses are written (never the file's bytes), like layout.tsv.
"""
from __future__ import annotations

import os
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BASE, AREA_END = 0x00F20000, 0x00FE0000
SRC_DIR = Path(os.environ.get("KH1_OVERLAYS", ROOT / "out" / "overlays"))


def layout(name: str) -> tuple[list[int], int]:
    starts, end = [], 0
    for line in (ROOT / "ovl" / name / "layout.tsv").read_text().splitlines():
        if line and not line.startswith(("#", "addr")):
            f = line.split("\t")
            starts.append(int(f[0], 16))
            end = max(end, int(f[1], 16))
    return starts, end


def main() -> int:
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    name = sys.argv[1]
    blob = (SRC_DIR / f"{name}.x").read_bytes()
    starts, code_end = layout(name)
    funcs = set(starts)
    rows, labels = [], 0
    for off in range((code_end - BASE + 3) & ~3, len(blob) - 3, 4):
        v = struct.unpack_from("<I", blob, off)[0]
        if not BASE <= v < AREA_END:
            continue
        if v in funcs:
            rows.append((BASE + off, v, "func"))
        elif v >= code_end:
            rows.append((BASE + off, v, "data"))
        else:
            labels += 1
    path = ROOT / "ovl" / name / "relocs.tsv"
    with path.open("w") as f:
        f.write(f"# {name}.x data words that point into the overlay (tools/ovl/relocs.py): a port "
                f"rewrites them after each load. {labels} words pointing inside functions (jump "
                "tables) left out.\n")
        f.write("addr\ttarget\tkind\n")
        for a, v, k in rows:
            f.write(f"{a:08x}\t{v:08x}\t{k}\n")
    print(f"wrote {path.relative_to(ROOT)}: {len(rows)} pointers "
          f"({sum(1 for r in rows if r[2] == 'func')} functions), {labels} jump-table words left out")
    return 0


if __name__ == "__main__":
    sys.exit(main())
