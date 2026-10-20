#!/usr/bin/env python3
"""Check that the SHIFT_FLOAT keep list still holds every name a PCSX2 bisection found (session 21).

  python3 -I tools/shift/keep_check.py out/shift/m12-float/float_covered.txt [--reach FILE]

The float build keeps a name in place when cover_check.py, reach_check.py, float_keep.txt or the
pointer-table-only rule lists it (the union is float_covered.txt). The names below hung, crashed or
garbled the game when they floated (docs/shiftable-plan.md, sessions 18-21). A reach_check rule
change must not let one of them float again; `make shift SHIFT_FLOAT=1` runs this check and fails
when one is missing. A name with a tail is needed only while its tail stays in place (the head of a
0x4000-byte table declared 0x40 bytes: when the tail floats with it, the copy reads the right bytes).
With --reach, each name also says whether reach_check's own list has it."""
from __future__ import annotations

import argparse
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

# (name, tail or None, where it was found)
RUNTIME = [
    ("D_005512A0", None, "s18: entries 52..63 of D_00550400 (stale writes in a RAM dump)"),
    ("D_0063F248", None, "s18: IOP-written field of D_0063D640"),
    ("D_0063F540", None, "s18: IOP-written field of D_0063D640"),
    ("D_00573AC0", None, "s19: GIF packet buffer (uncached alias)"),
    ("D_00573AD0", None, "s19: inside the GIF packet buffer"),
    ("D_00472190", "D_004721D0", "s20: 0x4000-byte table declared 0x40 (func_001073f0)"),
    ("D_004761D0", "D_00476210", "s20: 0x4000-byte table declared 0x40 (func_001072c0)"),
    ("D_0047A210", "D_0047A250", "s20: 0x4000-byte table declared 0x40"),
    ("D_002A6274", None, "s21: read as D_002A6274+4 for D_002A6278 (Agrabah walls; addend_check)"),
    ("D_002A6278", None, "s21: the name reached through D_002A6274+4"),
    ("D_003E4658", None, "s20: stored buffer pointer, 0x310 bytes (garbled text)"),
] + [(f"D_{a:08X}", None, "s20: inside D_003E4658's 0x310-byte buffer")
     for a in range(0x003E4660, 0x003E46A9, 8)] + [
    ("D_0046D800", None, "s20: sceCd buffer (uncached alias)"),
    ("D_0046DC40", None, "s20: D_0046D800's neighbour"),
] + [(n, None, "s20: staging arena D_003F8380 ... (black field)")
     for n in ("D_003F8380", "D_003F8F80", "D_003F9F80", "D_003FA380", "D_003FA780", "D_0040E780",
               "D_0040EB80")] + [
    (n, None, "s20: parallel object/table records (hang loading the save)")
    for n in ("D_0046E120", "D_00472160", "D_004761A0", "D_004761C0", "D_0047A1E0")] + [
    ("D_0048BFD0", None, "s22: head of a 0x90-byte record the tables point at (split_check; Agrabah sky)"),
    ("D_002A6178", None, "s22: colour field of the GIF packet at D_002A6120 (split_check; no title)"),
    ("D_002A6658", None, "s22: colour field of the GIF packet at D_002A65D0 (split_check; no title)"),
]


def c_defined() -> set[str]:
    p = ROOT / "out/gen/data.tsv"
    if not p.exists():
        return set()
    return {ln.split("\t")[1] for ln in p.read_text().splitlines()[1:] if ln.strip()}


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("covered", type=Path, help="the keep list (float_covered.txt)")
    ap.add_argument("--reach", type=Path, help="reach_check's own list (float_reach.txt), for the report")
    a = ap.parse_args()
    keep = {ln.strip() for ln in a.covered.read_text().splitlines() if ln.strip() and not ln.startswith("#")}
    reach = set(a.reach.read_text().split()) if a.reach else set()
    cdef = c_defined()
    missing = 0
    for name, tail, why in RUNTIME:
        if tail and tail in cdef and tail not in keep:
            state = "not needed (its tail floats)"
        elif name not in cdef:
            state = "not C-defined (stays)"
        elif name in keep:
            state = "kept" + (" (reach_check)" if name in reach else "")
        else:
            state = "MISSING"
            missing += 1
        if a.reach or state == "MISSING":
            print(f"{name:12} {state:28} {why}")
    print(f"keep_check: {len(RUNTIME) - missing}/{len(RUNTIME)} runtime names kept"
          + ("" if not missing else f"; {missing} MISSING"), file=sys.stderr)
    return 1 if missing else 0


if __name__ == "__main__":
    sys.exit(main())
