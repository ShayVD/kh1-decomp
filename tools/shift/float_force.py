#!/usr/bin/env python3
"""Take names out of the float build's keep list (Makefile SHIFT_FLOAT_FORCE, session 24).

  python3 -I tools/shift/float_force.py out/shift/m12-float/float_covered.txt NAME|@FILE ...

For runtime bisecting only: a name a check keeps (reach_check, float_keep.txt, keep_check's
runtime list) can be floated on purpose to test a hypothesis about it. The default build never
sets it."""
from __future__ import annotations

import sys
from pathlib import Path


def main() -> int:
    covered = Path(sys.argv[1])
    force: set[str] = set()
    for x in sys.argv[2:]:
        force |= set(Path(x[1:]).read_text().split()) if x.startswith("@") else {x}
    lines = covered.read_text().splitlines()
    kept = [ln for ln in lines if ln.split()[0:1] and ln.split()[0] not in force or not ln.split()]
    covered.write_text("\n".join(kept) + "\n")
    print(f"float_force: {len(lines) - len(kept)} keep lines removed for {len(force)} forced names")
    return 0


if __name__ == "__main__":
    sys.exit(main())
