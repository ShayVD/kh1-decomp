#!/usr/bin/env python3
"""List drafts whose diff has commutative instructions with their two source operands swapped.

    python3 tools/ovl/swapscan.py OVL [DIR]          # every func_*.c in DIR (default nonmatchings/session141/OVL)

Prints `score count func file addresses` for each draft where a differing line is the same commutative op
(addu, or, and, xor, nor, add.s, mul.s, daddu, mult, multu) with the same destination and the two sources
in the other order. Ways to fix them: put the sum in a fresh variable (`w = z + i` instead of `i = z + i`),
or write the address as an integer sum in the target's order (`(T *)(j * sizeof(T) + (u32)base)`,
`*(f32 *)((u32)b + (i << 2))`); see docs/overlays.md.
"""
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import msd  # noqa: E402

COMM = ('addu', 'or', 'and', 'xor', 'nor', 'add.s', 'mul.s', 'daddu', 'mult', 'multu')
OPS = re.compile(r'(\S+)\s+([^,]+),([^,]+),([^,]+)$')


def main() -> int:
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    ovl = sys.argv[1]
    d = msd.ROOT / (sys.argv[2] if len(sys.argv) > 2 else f"nonmatchings/session141/{ovl}")
    for p in sorted(d.glob('func_*.c')):
        func = re.match(r'func_[0-9a-f]{8}', p.name).group(0)
        lines = msd.diff(ovl, func, p).splitlines()
        m = re.search(r'score (\d+)', lines[0] if lines else '')
        hits = []
        for ln in lines[1:]:
            if len(ln) < 13 or '!=' not in ln[:13]:
                continue
            a, b = OPS.match(ln[12:53].strip()), OPS.match(ln[53:].strip())
            if a and b and a.group(1) in COMM and a.group(1) == b.group(1) and a.group(2) == b.group(2) \
                    and a.group(3) == b.group(4) and a.group(4) == b.group(3):
                hits.append(ln[:8])
        if hits:
            print(m.group(1) if m else '?', len(hits), func, p.name, ' '.join(hits), flush=True)
    return 0


if __name__ == '__main__':
    sys.exit(main())
