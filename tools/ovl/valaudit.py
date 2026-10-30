#!/usr/bin/env python3
"""Value audit of overlay near-miss drafts (session 141, wgb rounds 51-52; docs/overlays.md
"Audit values before registers").

    python3 tools/ovl/valaudit.py OVL draft.c [draft.c ...]   # the given drafts
    python3 tools/ovl/valaudit.py --scan OVL [DIR ...]         # every func_*.c in DIR (default nonmatchings/session141/OVL)

Compiles each draft like hand.py try (ovl.h prepended, the build mode taken from a draft.<mode>.c name) and
disassembles the original and the draft. For every jal it finds the instruction that last set each integer
argument register the callee takes (a0-a3, t0-t3, up to the arity of the callee's prototype in the draft; f32
parameters go to FP registers and are skipped), with the register names dropped, so `sll 0x1` against `move`
or `addiu 8624` against `addiu -20296` shows up. It also prints the non-sp immediates and load/store offsets
that only one side has, and says when the two sides call different callee sequences. Output: one `== func`
line per draft that has a note (score from autodecomp), then one indented line per note.

Most notes are not bugs: an address form (lw 4(r) against addiu 4 + lw 0(r)), a spill choice (an argument
loaded from the stack on one side), constant reuse (li 1 / and against andi 1), or calls merged by
cross-jumping. A different argument source at a call, or a different lui/addiu symbol pair, is worth reading
in the C. See also tools/ovl/xsym.py for functions in a draft that are not in the overlay's layout.
"""
import os
import re
import subprocess
import sys
import tempfile
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

ARGS = ['a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3']
NOWRITE = ('sw', 'sh', 'sb', 'sd', 'sq', 'swc1', 'sdc1', 'swl', 'swr', 'sdl', 'sdr',
           'b', 'beq', 'bne', 'beqz', 'bnez', 'blez', 'bgtz', 'bltz', 'bgez', 'beql', 'bnel', 'beqzl', 'bnezl',
           'blezl', 'bgtzl', 'bltzl', 'bgezl', 'bc1t', 'bc1f', 'bc1tl', 'bc1fl', 'j', 'jr', 'jal', 'jalr',
           'nop', 'div', 'divu', 'div1', 'divu1', 'mtc1', 'c.eq.s', 'c.lt.s', 'c.le.s', 'syscall', 'break',
           'mthi', 'mtlo', 'sync', 'cache')
BRANCH = re.compile(r'^(b|beq|bne|beqz|bnez|blez|bgtz|bltz|bgez|beql|bnel|beqzl|bnezl|blezl|bgtzl|bltzl|bgezl'
                    r'|bc1tl?|bc1fl?|j|jr)$')


def parse(line):
    parts = line.split(' ', 1)
    ops = [o.strip() for o in parts[1].split(',')] if len(parts) > 1 else []
    return parts[0], ops


def writes(op, ops):
    if op in NOWRITE or not ops:
        return None
    if op in ('mult', 'multu', 'mult1', 'multu1') and len(ops) == 2:
        return None
    return ops[0] if re.match(r'^[a-z][a-z0-9]$', ops[0]) else None


def desc(op, ops):
    """the instruction with register names dropped, keeping immediates, offsets and sp/zero"""
    keep = []
    for o in ops:
        m = re.match(r'^(-?(?:0x[0-9a-f]+|[0-9]+))\((\w+)\)$', o)
        if m:
            keep.append('%s(%s)' % (m.group(1), 'sp' if m.group(2) == 'sp' else 'r'))
        elif re.match(r'^-?(0x[0-9a-f]+|[0-9]+)$', o) or o in ('sp', 'zero'):
            keep.append(o)
    return op + ' ' + ','.join(keep)


def calls(asm):
    """(callee, {argreg: desc}) per jal; the delay slot counts, the scan back stops at a branch or jal"""
    out = []
    ins = [parse(ln) for ln in asm]
    for i, (op, ops) in enumerate(ins):
        if op != 'jal':
            continue
        found = {}
        if i + 1 < len(ins):
            w = writes(*ins[i + 1])
            if w in ARGS:
                found[w] = desc(*ins[i + 1])
        for op2, ops2 in reversed(ins[:i]):
            if op2 == 'jal' or BRANCH.match(op2):
                break
            w = writes(op2, ops2)
            if w in ARGS and w not in found:
                found[w] = desc(op2, ops2)
        out.append((ops[0] if ops else '?', found))
    return out


def imms(asm):
    c = Counter()
    for ln in asm:
        op, ops = parse(ln)
        if op in ('jal', 'j') or BRANCH.match(op):
            continue
        d = desc(op, ops)
        if '(sp)' not in d and d.split(' ', 1)[1]:
            c[d] += 1
    return c


def arities(text):
    """callee address (as objdump prints it) -> number of integer argument registers, from the prototypes"""
    ar = {}
    for m in re.finditer(r'\bfunc_00([0-9a-f]{6})\s*\(([^;{)]*(?:\([^)]*\)[^;{)]*)*)\)\s*;', text):
        addr = '0x' + m.group(1).lstrip('0')
        params = m.group(2).strip()
        if params in ('', 'void'):
            ar[addr] = 0
            continue
        if '...' in params:
            continue
        parts, cur, depth = [], '', 0
        for ch in params:
            depth += (ch == '(') - (ch == ')')
            if ch == ',' and depth == 0:
                parts.append(cur)
                cur = ''
            else:
                cur += ch
        parts.append(cur)
        n = sum(1 for p in parts if not (re.match(r'^(f32|float|double|f64)\b', p.strip()) and '*' not in p))
        ar[addr] = min(n, 8)
    return ar


def worker(files):
    sys.path.insert(0, str(ROOT / 'tools'))
    os.chdir(ROOT)
    import autodecomp as AD
    AD._init()
    AD._orig = AD.K.require_orig(AD._cfg)
    for path in files:
        fn = Path(path).name.split('.')[0]
        text = Path(path).read_text()
        try:
            f = AD.K.find_func(fn)
            sym = AD._names.get(f.addr, 'func_%08x' % f.addr)
            with tempfile.TemporaryDirectory() as td:
                ok, why = AD.build_and_compare(f, sym, '#include "ovl.h"\n' + text, Path(td))
            if not AD.LAST_BYTES:
                print('== %s %s: does not compile' % (fn, path), flush=True)
                continue
            a = AD.disasm(AD._orig.read(f.addr, f.size), f.addr)
            b = AD.disasm(AD.LAST_BYTES, f.addr)
        except Exception as e:  # noqa: BLE001
            print('== %s %s: %s' % (fn, path, e), flush=True)
            continue
        ca, cb = calls(a), calls(b)
        notes = []
        if [x[0] for x in ca] != [x[0] for x in cb]:
            notes.append('callee sequence differs: target %s ours %s' % ([x[0] for x in ca], [x[0] for x in cb]))
        else:
            ar = arities(text)
            for k, ((callee, fa), (_, fb)) in enumerate(zip(ca, cb)):
                for r in ARGS[:ar.get(callee, 0)]:
                    if fa.get(r) != fb.get(r):
                        notes.append('call %d %s %s: target [%s] ours [%s]' % (k, callee, r, fa.get(r), fb.get(r)))
        ia, ib = imms(a), imms(b)
        if ia != ib:
            notes.append('target only %s | ours only %s' % (dict(ia - ib), dict(ib - ia)))
        if notes and not ok:
            print('== %s %s (%s)' % (fn, path, why), flush=True)
            for n in notes:
                print('   ' + n, flush=True)


def main():
    argv = sys.argv[1:]
    if argv[:1] == ['--worker']:
        worker(argv[1:])
        return 0
    if not argv:
        sys.exit(__doc__)
    if argv[0] == '--scan':
        ovl = argv[1]
        dirs = [Path(d) for d in argv[2:]] or [ROOT / 'nonmatchings' / 'session141' / ovl]
        files = sorted(str(p) for d in dirs for p in (ROOT / d).glob('func_*.c'))
    else:
        ovl, files = argv[0], argv[1:]
    groups = {}
    for p in files:
        sfx = Path(p).suffixes
        groups.setdefault(sfx[-2][1:] if len(sfx) > 1 else '', []).append(str(Path(p).resolve()))
    for mode, fs in sorted(groups.items()):
        subprocess.run([sys.executable, __file__, '--worker'] + fs, cwd=ROOT,
                       env=dict(os.environ, KH1_OVL=ovl, KH1_MODE=mode))
    return 0


if __name__ == '__main__':
    sys.exit(main())
