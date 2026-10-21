#!/usr/bin/env python3
"""How much of the game's fixed memory regions a PCSX2 savestate uses (session 26).

  python3 -I tools/shift/mem_regions.py STATE.p2s [STATE.p2s ...]

For each region past the ELF image (docs/shiftable-plan.md "Session 26": the fixed pools, the
block heap, the 0x9A0000 load area, the overlays, the 0xFE0000 slots, 0x1CE0000 and the stack)
it prints the last non-zero byte and a map of 64 KB blocks ('#' = something non-zero). Freed
memory keeps its old bytes, so the last non-zero byte is an upper bound on the high-water mark
since boot (PCSX2 starts with zeroed RAM).

It also walks func_00121c78's block heap: the free-list records are 20 bytes (+4 block start,
+8 size, +0x10 next), and the head is the record whose block starts at the heap base (0x820000,
or wherever the float moved D_00820000: pass --heap-base). Each head found prints its block count
and the end of the highest block in use now."""
from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from float_holes import ee_memory  # noqa: E402

REGIONS = [
    (0x006A0000, 0x00820000, "pools"),       # func_0014a090 / func_00133628 (session 25)
    (0x00820000, 0x009A0000, "block heap"),  # func_00121c78, end D_009A0000 (func_00121d60)
    (0x009A0000, 0x00F20000, "load 9A"),     # D_004D92DC, func_0011cb80 / func_0011cd20, dktitle.x
    (0x00F20000, 0x00FE0000, "overlays"),    # .x files are linked at 0xF20000 (wm.x's bss runs further)
    (0x00FE0000, 0x012E0000, "FE slots"),    # 12 slots of 0x40000 (D_00550400 entries, func_00155760)
    (0x012E0000, 0x01CE0000, "12E..1CE"),
    (0x01CE0000, 0x01FE0000, "1CE.."),       # func_00155a50 returns D_01CE0000
    (0x01FE0000, 0x02000000, "stack"),       # crt0
]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("states", nargs="+", type=Path)
    ap.add_argument("--heap-base", type=lambda x: int(x, 0), action="append", default=[],
                    help="block heap base to look for besides 0x820000 (D_00820000 of a float build)")
    a = ap.parse_args()
    bases = {0x00820000, *a.heap_base}
    for p in a.states:
        m = ee_memory(p)
        print(f"== {p.name}")
        for off in range(0x00300000, 0x00800000, 4):
            if struct.unpack_from("<I", m, off)[0] not in bases:
                continue
            recs, cur, seen = [], off - 4, set()
            while cur and cur not in seen and len(recs) < 600 and cur + 20 <= len(m):
                seen.add(cur)
                start, size = struct.unpack_from("<II", m, cur + 4)
                recs.append((start, size))
                cur = struct.unpack_from("<I", m, cur + 16)[0] & 0x1FFFFFF
            if all(min(bases) <= s <= 0x009A0000 for s, _ in recs):
                print(f"  heap head 0x{off - 4:08x}: {len(recs)} blocks, top 0x{max(s + n for s, n in recs):08x}")
        for lo, hi, name in REGIONS:
            seg = m[lo:hi]
            last = lo + len(seg.rstrip(b"\0"))
            blocks = "".join("#" if any(seg[i:i + 0x10000]) else "." for i in range(0, len(seg), 0x10000))
            print(f"  {name:10s} {lo:08x}-{hi:08x} last non-zero {last:08x}  {blocks}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
