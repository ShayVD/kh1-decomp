#!/usr/bin/env python3
""""No PROVIDE inside the image" check for the shiftable link (step 3).

Lists every symbol the shift link would still take from a PROVIDE fallback
(out/gen/symbols.ld, original addresses) with an address inside the image
0x00100000-0x00675018, once these are linked: every src/ object (as the
normal build compiles them), the unmatched exports (shift/unmatched/*.s) and
the alias table (shift/aliases.ld, or generated on the fly with --fresh).

Expected: D_ names in the file-backed data (0x00272C70-0x00494068) and .bss
(0x00494080-0x00675018), which the shift link defines as data/bss base +
offset. Everything else is reported; the goal is none. Exit status 1 when
any non-D_ name (or a D_ name in the code range) is left.

  python3 -I tools/shift/provide_check.py [--fresh] [--list]
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import aliases as A  # noqa: E402
import kh1tool as K  # noqa: E402

DATA_LO, DATA_HI = 0x00272C70, 0x00494068
BSS_LO, BSS_HI = 0x00494080, 0x00675018
ALIAS_RE = re.compile(r"^([\w.$]+) = ", re.M)


def classify(name: str, a: int) -> str:
    d = name.startswith("D_")
    if a < A.TEXT_HI:
        return "code"
    if a < DATA_HI:
        return "D_ data" if d else "data (not D_)"
    if a < BSS_LO:
        return "D_ gap" if d else "gap (not D_)"
    return "D_ bss" if d else "bss (not D_)"


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--fresh", action="store_true", help="generate the aliases now instead of reading shift/aliases.ld")
    ap.add_argument("--list", action="store_true", help="also list the expected D_ data/bss names")
    a = ap.parse_args()
    defined, canon, refs, provides = A.collect()
    if a.fresh or not A.DEFAULT_OUT.exists():
        aliased = {n for n, _t, _o in A.build_aliases(defined, canon, refs, provides)[0]}
    else:
        aliased = set(ALIAS_RE.findall(A.DEFAULT_OUT.read_text()))
    registry = K.load_registry()
    left: dict[str, list[tuple[str, int]]] = {}
    unknown = []
    for name in sorted(refs):
        if name in defined or name in aliased:
            continue
        addr = A.address_of(name, provides, registry)
        if addr is None:
            unknown.append(name)
            continue
        if A.IMAGE_LO <= addr <= A.IMAGE_HI:
            left.setdefault(classify(name, addr), []).append((name, addr))
    expected = {"D_ data", "D_ bss", "D_ gap"}
    bad = 0
    print("Symbols the shift link would still take from a PROVIDE inside 0x00100000-0x00675018:")
    for cls in sorted(left, key=lambda c: (c in expected, c)):
        rows = sorted(left[cls], key=lambda r: r[1])
        ok = cls in expected
        bad += 0 if ok else len(rows)
        print(f"  {cls:16} {len(rows):6}  {'expected (base + offset)' if ok else 'NOT RESOLVED'}")
        if not ok or a.list:
            for name, addr in rows:
                users = sorted(refs[name])
                print(f"      0x{addr:08x}  {name}  ({users[0]}{f' +{len(users) - 1}' if len(users) > 1 else ''})")
    if unknown:
        print(f"  no address known for {len(unknown)}: {', '.join(unknown[:20])}")
    print(f"non-D_ (or code) names left: {bad}")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
