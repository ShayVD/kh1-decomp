#!/usr/bin/env python3
"""The GIF tags the C writes as constants, by function (phase 5, docs/renderer-spec.md 4.9).

  python3 -I tools/host/giftags.py src/text/*.c [--all]

Packets built per draw in a scratch buffer (func_00122048's frames: the text windows, the menus)
are not in the ELF, so dmawalk.py cannot walk them; their GIF tags are 64-bit constants in the
C.  This lists, per function, every constant that reads as a PACKED GIF tag with PRE (NREG,
EOP, NLOOP when set, the PRIM decoded), the shape of the per-draw sprites and strips.  A heuristic
over the source text: a tag ORed together from parts, or built field by field, is missed, and a
constant of the same shape that is not a tag would be listed (none in src/text).  `--all` also
lists tags without PRE.  Reads only the repository's C (no game data).
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

PRIMS = ["POINT", "LINE", "LINESTRIP", "TRIANGLE", "TRISTRIP", "TRIFAN", "SPRITE", "?7"]
FN = re.compile(r"^[A-Za-z_][\w \*]*\b(func_[0-9a-f]{8})\s*\(.*\)\s*\{?\s*$")
LIT = re.compile(r"0x([0-9a-fA-F]{9,16})")


def prim(p: int) -> str:
    s = PRIMS[p & 7]
    for b, n in ((3, "IIP"), (4, "TME"), (5, "FGE"), (6, "ABE"), (7, "AA1"), (8, "FST"), (9, "CTXT2"), (10, "FIX")):
        if p >> b & 1:
            s += "|" + n
    return s


def tag(v: int, all_: bool) -> str | None:
    hi = v >> 32
    if hi >> 26 & 3:  # PACKED only
        return None
    pre = v >> 46 & 1
    if not pre and not all_:
        return None
    if pre and (v >> 47 & 7) == 7:
        return None  # PRIM type 7 is reserved: not a tag
    s = "%s nreg %d eop %d" % (prim(v >> 47 & 0x7FF) if pre else "no PRE", hi >> 28 or 16, v >> 15 & 1)
    if v & 0x7FFF:
        s += " nloop %d" % (v & 0x7FFF)
    return s


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("files", nargs="+", type=Path)
    ap.add_argument("--all", action="store_true", help="also tags without PRE")
    a = ap.parse_args()
    for path in a.files:
        cur, found = None, {}
        for line in path.read_text(errors="replace").splitlines():
            m = FN.match(line)
            if m:
                cur = m.group(1)
            for h in LIT.findall(line):
                s = tag(int(h, 16), a.all)
                if s and cur:
                    found.setdefault(cur, set()).add(s)
        for fn, tags in found.items():
            print("%-28s %s  %s" % (path.name, fn, "; ".join(sorted(tags))))
    return 0


if __name__ == "__main__":
    sys.exit(main())
