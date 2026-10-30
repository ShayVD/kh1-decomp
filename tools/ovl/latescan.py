#!/usr/bin/env python3
"""tools/ovl/latescan.py (session 141, wgb round 44): find loads that alias analysis placed differently.

    python3 tools/ovl/latescan.py OVL [draft.c ...]    # default: every nonmatchings/session141/OVL/func_*.c

For each draft, compares the target's loads with our build's (stack loads ignored) and prints the drafts with:
- LATE: a load (mnemonic + offset) that the target issues after at least two more stores of its basic block
  than ours does. gcc hoisted it above stores it took to be independent; the original read it in a way that
  may alias them (docs/overlays.md: a struct-view bitfield read, gb func_00f333f8).
- MORE: a load key the target repeats more often than ours; MOREOP: the same by mnemonic only, which also
  catches reloads whose addressing differs (`lwc1 0(t1)` against `lwc1 9984(v0)`). gcc kept the value in a
  register; in the original a store in between may alias it (docs/overlays.md: a pointer set twice, gb
  func_00f3f2b0).
Output: `<score> <func> <file> LATE: ... | MORE: ... | MOREOP: ...`.
"""
import collections
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import msd  # noqa: E402

ROOT = msd.ROOT
LD = ('lw', 'lh', 'lhu', 'lb', 'lbu', 'ld', 'lwc1', 'lq', 'ldl', 'ldr', 'lwl', 'lwr')
ST = ('sw', 'sh', 'sb', 'sd', 'swc1', 'sq', 'sdl', 'sdr', 'swl', 'swr')
BRK = set(msd.BR) | {'jr', 'jalr'}


def loads(col: list) -> dict:
    """load key -> [stores seen earlier in the same block, ...] in order"""
    res = collections.defaultdict(list)
    st = 0
    for t in col:
        t = t.strip()
        if not t:
            continue
        op = t.split()[0]
        if op in BRK:
            st = 0
        elif op in ST:
            st += 1
        elif op in LD:
            m = re.search(r'(-?\d+)\((\w+)\)', t)
            if m and m.group(2) == 'sp':
                continue
            res[op + ' ' + (m.group(1) if m else '?')].append(st)
    return res


def scan(ovl: str, p: Path):
    func = re.search(r'func_[0-9a-f]{8}', p.name).group(0)
    lines = msd.diff(ovl, func, p).splitlines()
    m = re.search(r'score (\d+)', lines[0]) if lines else None
    if not m:
        return None
    ca = [ln[12:53] for ln in lines[1:] if len(ln) >= 13]
    cb = [ln[53:] for ln in lines[1:] if len(ln) >= 13]
    a, b = loads(ca), loads(cb)
    late = [f'{k} +{x - y}' for k in a if k in b for x, y in zip(a[k], b[k]) if x - y >= 2]
    more = [f'{k} x{len(a[k])}/{len(b[k])}' for k in a if k in b and len(a[k]) > len(b[k])]
    ta = collections.Counter(k.split()[0] for k in a for _ in a[k])
    tb = collections.Counter(k.split()[0] for k in b for _ in b[k])
    moreop = [f'{k} {ta[k]}/{tb[k]}' for k in ta if ta[k] > tb[k]]
    if not (late or more or moreop):
        return None
    return f"{m.group(1)} {func} {p.name} LATE: {' '.join(late)} | MORE: {' '.join(more)} | MOREOP: {' '.join(moreop)}"


def main() -> int:
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    ovl = sys.argv[1]
    files = [Path(x).resolve() for x in sys.argv[2:]] or sorted(
        (ROOT / f'nonmatchings/session141/{ovl}').glob('func_*.c'))
    for p in files:
        if p.name.endswith('.h3.c'):
            continue
        r = scan(ovl, p)
        if r:
            print(r, flush=True)
    return 0


if __name__ == '__main__':
    sys.exit(main())
