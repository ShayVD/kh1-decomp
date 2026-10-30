#!/usr/bin/env python3
"""Nothrow lever search for overlay near-miss drafts (session 141, wwm2 round 64; docs/overlays.md
"Branch-likely vs plain branch").

    python3 tools/ovl/nothrow.py OVL draft.c [draft.c ...]   # the given drafts
    python3 tools/ovl/nothrow.py --scan OVL [DIR ...]         # every func_*.c in DIR (default nonmatchings/session141/OVL)
    python3 tools/ovl/nothrow.py --all                        # --scan of every nonmatchings/session141/* overlay,
                                                              # plus the drafts listed in ovl/*/drafts.tsv

reorg fills a conditional branch's delay slot with the plain branch only when the stolen insn is
harmless on the other path. A call counts as killing the call-clobbered registers only when it
cannot throw, and gcc 2.96 marks a call nothrow only when the callee is defined earlier in the same
file. So a CONTEXT_ONLY definition of a callee above the function can turn a `beqzl` into the
original's `beqz` (or the reverse). Matches found this way: gb func_00f350d0 and func_00f35a80 (wwm1),
dktitle func_00f228c8 (wwm2).

For each draft this compiles the draft like hand.py try (ovl.h prepended, the build mode taken from a
draft.<mode>.c name) and disassembles the original and ours. It aligns the two (difflib on the
opcodes with the -likely `l` dropped) and finds the branches where one side is plain and the other
is -likely. For every such branch it collects the callees of the `jal`s near it in our code: up to 48
insns forward from the branch, 24 forward from its target, and 16 back. A callee qualifies when the
draft declares it with a prototype and does not define it already.

Each qualifying callee is tried alone: a CONTEXT_ONLY definition (named parameters, an empty body,
`return 0;` for a non-void return) goes right after its prototype. Then every pair of the best four
singles is tried. The output is one `== OVL func path: base N` line per draft that has a
likely/plain mismatch, then one indented line per try (`+func_X: N (gain G)`). A final `GAIN` line
per draft lists the best set when it beats the base. The drafts are never written; candidates are
built in a temporary directory only. Read the candidate before keeping it, and land it the usual way
(ordcheck, size rule, hand.py keep for a match).
"""
import itertools
import os
import re
import subprocess
import sys
import tempfile
from difflib import SequenceMatcher
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

LIKELY = re.compile(r'^(beq|bne|beqz|bnez|blez|bgtz|bltz|bgez|bc1t|bc1f)l$')
PLAIN = re.compile(r'^(beq|bne|beqz|bnez|blez|bgtz|bltz|bgez|bc1t|bc1f)$')


def base_op(op):
    return op[:-1] if LIKELY.match(op) else op


def likely_mismatches(a, b):
    """indexes into b (ours) where the aligned target insn differs from ours only in -likely"""
    oa = [base_op(x.split(' ', 1)[0]) for x in a]
    ob = [base_op(x.split(' ', 1)[0]) for x in b]
    out = []
    sm = SequenceMatcher(None, oa, ob, autojunk=False)
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag != 'equal':
            continue
        for k in range(i2 - i1):
            ra = a[i1 + k].split(' ', 1)[0]
            rb = b[j1 + k].split(' ', 1)[0]
            if ra != rb and base_op(ra) == base_op(rb) and (LIKELY.match(ra) or LIKELY.match(rb)):
                out.append((j1 + k, ra, rb))
    return out


def near_callees(b, idx, addr0):
    """callee addresses (0x...) of the jals near branch b[idx]"""
    found = []

    def target(k):
        m = re.search(r'(0x[0-9a-f]+)$', b[k])
        return (int(m.group(1), 16) - addr0) // 4 if m else None

    def walk(start, budget, depth):
        """the first jals on each path from start, following branches (depth levels)"""
        k = start
        while 0 <= k < len(b) and budget > 0:
            op, _, rest = b[k].partition(' ')
            if op == 'jal' and rest:
                t = rest.strip()
                if t not in found:
                    found.append(t)
            elif op in ('jr', 'j'):
                return
            elif (op == 'b' or PLAIN.match(op) or LIKELY.match(op)) and depth > 0:
                t = target(k)
                if t is not None:
                    walk(t, budget, depth - 1)
                if op == 'b':
                    return
            k += 1
            budget -= 1
    walk(idx + 2, 48, 2)
    t = target(idx)
    if t is not None:
        walk(t, 24, 1)
    for k in range(max(idx - 16, 0), idx):
        op, _, rest = b[k].partition(' ')
        if op == 'jal' and rest.strip() not in found:
            found.append(rest.strip())
    return found


PROTO = r'(?m)^([ \t]*(?:extern\s+)?((?:const\s+|unsigned\s+|signed\s+|struct\s+)*\w+[\s\*]*?))\b%s\s*\(([^;{]*?)\)\s*;'


def split_params(params):
    parts, cur, depth = [], '', 0
    for ch in params:
        depth += (ch == '(') - (ch == ')')
        if ch == ',' and depth == 0:
            parts.append(cur.strip())
            cur = ''
        else:
            cur += ch
    parts.append(cur.strip())
    return parts


def definition(name, ret, params):
    ret = ret.strip()
    body = '{}' if re.match(r'^void$', ret) else '{ return 0; }'
    ps = split_params(params)
    if ps in ([''], ['void']):
        plist = 'void'
    elif any('(' in p or '[' in p or '...' in p for p in ps):
        plist = ''  # old-style definition
    else:
        plist = ', '.join('%s a%d' % (p, i) for i, p in enumerate(ps))
    return ' CONTEXT_ONLY %s %s(%s) %s' % (ret, name, plist, body)


def with_defs(text, names):
    """text with a CONTEXT_ONLY definition after each named callee's prototype, or None"""
    for name in names:
        m = re.search(PROTO % re.escape(name), text)
        if not m:
            return None
        end = m.end()
        text = text[:end] + definition(name, m.group(2), m.group(3)) + text[end:]
    return text


def defined(text, name):
    return re.search(r'\b%s\s*\([^;{]*\)\s*\{' % re.escape(name), text) is not None


def worker(files):
    sys.path.insert(0, str(ROOT / 'tools'))
    os.chdir(ROOT)
    import autodecomp as AD
    AD._init()
    AD._orig = AD.K.require_orig(AD._cfg)
    ovl = os.environ.get('KH1_OVL', '?')

    def build(f, sym, text):
        with tempfile.TemporaryDirectory() as td:
            ok, why = AD.build_and_compare(f, sym, '#include "ovl.h"\n' + text, Path(td))
        if ok:
            return 0, AD.LAST_BYTES
        m = re.search(r'score (\d+)', why)
        return (int(m.group(1)) if m else 99999), AD.LAST_BYTES

    for path in files:
        fn = Path(path).name.split('.')[0]
        text = Path(path).read_text()
        try:
            f = AD.K.find_func(fn)
            sym = AD._names.get(f.addr, 'func_%08x' % f.addr)
            base, ours = build(f, sym, text)
            if not ours or base == 0:
                continue
            a = AD.disasm(AD._orig.read(f.addr, f.size), f.addr)
            b = AD.disasm(ours, f.addr)
        except Exception as e:  # noqa: BLE001
            print('== %s %s %s: %s' % (ovl, fn, path, e), flush=True)
            continue
        mis = likely_mismatches(a, b)
        if not mis:
            continue
        cands = []
        for idx, ra, rb in mis:
            for t in near_callees(b, idx, f.addr):
                name = 'func_%08x' % int(t, 16)
                if name not in cands and name != fn and not defined(text, name) \
                        and re.search(PROTO % re.escape(name), text):
                    cands.append(name)
        print('== %s %s %s: base %d, %d likely/plain mismatch(es) (%s), candidates %s' % (
            ovl, fn, path, base, len(mis), ', '.join('%s/%s' % (ra, rb) for _, ra, rb in mis[:6]),
            ' '.join(cands) or '-'), flush=True)
        singles = []
        for name in cands:
            t = with_defs(text, [name])
            if t is None:
                continue
            sc, _ = build(f, sym, t)
            singles.append((sc, name))
            print('   +%s: %d (gain %d)' % (name, sc, base - sc), flush=True)
        singles.sort()
        best = (base, ())
        for sc, name in singles:
            if sc < best[0]:
                best = (sc, (name,))
        top = [n for _, n in singles[:4]]
        for x, y in itertools.combinations(top, 2):
            t = with_defs(text, [x, y])
            if t is None:
                continue
            sc, _ = build(f, sym, t)
            print('   +%s +%s: %d (gain %d)' % (x, y, sc, base - sc), flush=True)
            if sc < best[0]:
                best = (sc, (x, y))
        if best[0] < base:
            print('GAIN %s %s %s %d -> %d with %s' % (ovl, fn, path, base, best[0], ' '.join(best[1])), flush=True)


def run(ovl, files):
    groups = {}
    for p in files:
        sfx = Path(p).suffixes
        groups.setdefault(sfx[-2][1:] if len(sfx) > 1 else '', []).append(str(Path(p).resolve()))
    for mode, fs in sorted(groups.items()):
        subprocess.run([sys.executable, __file__, '--worker'] + fs, cwd=ROOT,
                       env=dict(os.environ, KH1_OVL=ovl, KH1_MODE=mode))


def listed(ovl):
    tsv = ROOT / 'ovl' / ovl / 'drafts.tsv'
    out = []
    if tsv.exists():
        for ln in tsv.read_text().splitlines():
            parts = ln.split('\t')
            if len(parts) >= 2 and parts[0].startswith('func_') and (ROOT / parts[1]).exists():
                out.append(str(ROOT / parts[1]))
    return out


def main():
    argv = sys.argv[1:]
    if argv[:1] == ['--worker']:
        worker(argv[1:])
        return 0
    if not argv:
        sys.exit(__doc__)
    if argv[0] == '--all':
        ovls = sorted({p.name for p in (ROOT / 'nonmatchings' / 'session141').iterdir() if p.is_dir()}
                      | {p.parent.name for p in (ROOT / 'ovl').glob('*/drafts.tsv')})
        for ovl in ovls:
            d = ROOT / 'nonmatchings' / 'session141' / ovl
            files = sorted(str(p) for p in d.glob('func_*.c')) if d.is_dir() else []
            have = {Path(p).name.split('.')[0] for p in files}
            files += [p for p in listed(ovl) if Path(p).name.split('.')[0] not in have]
            if files:
                run(ovl, files)
        return 0
    if argv[0] == '--scan':
        ovl = argv[1]
        dirs = [Path(d) for d in argv[2:]] or [ROOT / 'nonmatchings' / 'session141' / ovl]
        files = sorted(str(p) for d in dirs for p in (ROOT / d).glob('func_*.c'))
    else:
        ovl, files = argv[0], argv[1:]
    run(ovl, files)
    return 0


if __name__ == '__main__':
    sys.exit(main())
