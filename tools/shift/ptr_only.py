#!/usr/bin/env python3
"""Print the data names that only a C pointer table names (session 21).

  python3 -I tools/shift/ptr_only.py

define_ptr_tables.py moved pointer tables into the one C file that uses them, with an
`extern u8 D_X[];` per entry after a "Pointer tables only this file uses" comment. Their
entries then have a C file in data_owners.tsv, so the float build's pointer-table-only rule
(SHIFT_FLOAT_PTR_ONLY=0: names only pieces' .words name stay in place) missed them. Floated,
33 of them were among the 44 names that left Agrabah's storage room walls undrawn (session 21
bisection). A name counts when the file names it only inside that block, as a table entry."""
from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MARK = "/* Pointer tables only this file uses"


def main() -> None:
    out: set[str] = set()
    for p in sorted((ROOT / "src").rglob("*.c")):
        s = p.read_text(errors="replace")
        i = s.find(MARK)
        if i < 0:
            continue
        blk, rest = s[i:], s[:i]
        names = set(re.findall(r"extern\s+\w+\s+(D_[0-9A-F]{8})\[\];", blk))
        tables = set(re.findall(r"^\S.*?\b(D_[0-9A-F]{8})\s*\[[^\]]*\]\s*(?:ALIGNED\(\d+\)\s*)?=", blk, re.M))
        out |= {n for n in names - tables if not re.search(r"\b" + n + r"\b", rest)}
    print("\n".join(sorted(out)))


if __name__ == "__main__":
    main()
