#!/usr/bin/env python3
"""Instruction multiset difference between an overlay function and a near-miss draft.

    python3 tools/ovl/msd.py OVL FUNC draft.c          # one draft
    python3 tools/ovl/msd.py --scan OVL [DIR]          # every func_*.c in DIR (default nonmatchings/session141/OVL)

Compiles the draft like hand.py try (ovl.h prepended, the build mode taken from a draft.<mode>.c name), then
counts (mnemonic, last immediate) pairs on each side of the diff, branches by mnemonic only, and prints what
only the target has and what only the draft has. Jump-table loads (the lw/addu/addiu/lui/sll that feed a `jr`
other than `jr ra`) are dropped, since the draft object's table address is not relocated. A one-instruction
difference such as `addiu 2272` against `addiu 142`, or `srl` against `sra`, usually names the expression
rewrite (here: shift before the add; an unsigned type). --scan prints one line per draft:
`<differing instructions> <score> <func> <file> T: {...} O: {...}`, so sort -n puts the closest first.
"""
import collections
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BR = ('b', 'beq', 'bne', 'beqz', 'bnez', 'jal', 'bgez', 'blez', 'bltz', 'bgtz', 'beql', 'bnel', 'beqzl', 'bnezl',
      'bgezl', 'blezl', 'bltzl', 'bgtzl', 'bc1t', 'bc1f', 'bc1tl', 'bc1fl')


def diff(ovl: str, func: str, draft: Path) -> str:
    mode = draft.suffixes[-2][1:] if len(draft.suffixes) > 1 else ""
    with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False) as fh:
        fh.write('#include "ovl.h"\n' + draft.read_text())
        path = fh.name
    try:
        r = subprocess.run([sys.executable, "tools/autodecomp.py", "try", func, "--file", path, "--diff"], cwd=ROOT,
                           capture_output=True, text=True, env=dict(os.environ, KH1_OVL=ovl, KH1_MODE=mode))
    finally:
        os.unlink(path)
    return r.stdout


def key(t: str):
    t = t.strip()
    if not t:
        return None
    op = t.split()[0]
    if op in BR:
        return op
    imm = re.findall(r'(?<![\w$])(-?0x[0-9a-f]+|-?\d+)(?!\()', t[len(op):])
    return op + ' ' + ','.join(imm[-1:])


def regs(t: str) -> list:
    return re.findall(r'\b([astvk][0-9]|v[01]|at|gp|s8|ra|zero)\b', t)


def mask(col: list) -> list:
    drop = set()
    for k, t in enumerate(col):
        m = re.match(r'jr\s+(\w+)$', t.strip())
        if not m or m.group(1) == 'ra':
            continue
        want = {m.group(1)}
        for j in range(k - 1, max(k - 9, -1), -1):
            u = col[j].strip()
            if not u:
                continue
            rs = regs(u)
            if u.split()[0] in ('lw', 'addu', 'addiu', 'lui', 'sll') and rs and rs[0] in want:
                drop.add(j)
                want |= set(rs[1:])
    return [key(t) for j, t in enumerate(col) if j not in drop and key(t)]


def msd(ovl: str, func: str, draft: Path):
    out = diff(ovl, func, draft)
    ca, cb = [], []
    for ln in out.splitlines()[1:]:
        if len(ln) >= 13:
            ca.append(ln[12:53])
            cb.append(ln[53:])
    a, b = collections.Counter(mask(ca)), collections.Counter(mask(cb))
    m = re.search(r'score (\d+)', out)
    score = int(m.group(1)) if m else (0 if ' MATCH ' in out else 99999)
    return score, dict(a - b), dict(b - a)


def main() -> int:
    if len(sys.argv) >= 3 and sys.argv[1] == '--scan':
        ovl = sys.argv[2]
        d = ROOT / (sys.argv[3] if len(sys.argv) > 3 else f"nonmatchings/session141/{ovl}")
        for p in sorted(d.glob('func_*.c')):
            func = re.match(r'func_[0-9a-f]{8}', p.name).group(0)
            score, a, b = msd(ovl, func, p)
            a.pop('nop ', None)
            b.pop('nop ', None)
            print(sum(a.values()) + sum(b.values()), score, func, p.name, 'T:', a, 'O:', b, flush=True)
        return 0
    if len(sys.argv) != 4:
        sys.exit(__doc__)
    score, a, b = msd(sys.argv[1], sys.argv[2], Path(sys.argv[3]).resolve())
    print('score', score)
    print('target only:', a)
    print('draft only: ', b)
    return 0


if __name__ == '__main__':
    sys.exit(main())
