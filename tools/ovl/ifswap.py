#!/usr/bin/env python3
"""tools/ovl/ifswap.py (session 141, wwm1 round 22): OVL DRAFT

For each `if (C) {` ... `} else {` ... `}` at one indentation level, try the draft with the two arms swapped
and the condition negated (a simple comparison is flipped, == <-> != and so on; anything else becomes !(C)).
That decides which arm falls through, beqz vs bnezl, and the arm order. Prints hand.py try's result per site
and writes a matching version to $OVLTOOL_DIR/ifs_match_FUNC.c (default out/ovl/tools). ONLY=12,40 applies just
those sites (1-based line numbers of the `if`), together, and OUT=path writes that version. Keep a result only
if hand.py's score goes down."""
import subprocess, sys, re, os
W = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
D = os.environ.get('OVLTOOL_DIR', os.path.join(W, 'out', 'ovl', 'tools'))
os.makedirs(D, exist_ok=True)
o, d = sys.argv[1:3]
base = os.path.basename(d)
f = base.split('.')[0]
mode = '.' + base.split('.')[1] if base.count('.') > 1 else ''
L = open(d).read().split('\n')


def neg(c):
    for a, b in (('!=', '=='), ('==', '!='), ('>=', '<'), ('<=', '>'), ('<', '>='), ('>', '<=')):
        m = re.match(r'^([^<>=!&|?]+?)\s*%s\s*([^<>=!&|?]+)$' % re.escape(a), c)
        if m:
            return '%s %s %s' % (m.group(1).strip(), b, m.group(2).strip())
    if c.startswith('!') and '&&' not in c and '||' not in c:
        return c[1:]
    return '!(%s)' % c


def run(T, tag):
    p = os.path.join(D, 'ifs_%s_%s%s.c' % (o, f, mode))
    open(p, 'w').write('\n'.join(T))
    r = subprocess.run(['python3', 'tools/ovl/hand.py', 'try', o, f, p], cwd=W, capture_output=True, text=True).stdout.split('\n')[0]
    print(tag, r[10:100], flush=True)
    if 'MATCH' in r and 'FAIL' not in r:
        open(os.path.join(D, 'ifs_match_%s%s.c' % (f, mode)), 'w').write('\n'.join(T))
    return r


r0 = subprocess.run(['python3', 'tools/ovl/hand.py', 'try', o, f, d], cwd=W, capture_output=True, text=True).stdout.split('\n')[0]
print('base', r0[10:100], flush=True)
ONLY = [int(x) for x in os.environ.get('ONLY', '').split(',') if x]
OUT = os.environ.get('OUT')
for i, l in enumerate(L):
    if ONLY and i + 1 not in ONLY:
        continue
    m = re.match(r'^(\s*)(?:\} else )?if \((.*)\) \{\s*$', l)
    if not m or l.strip().startswith('}'):
        continue
    ind = m.group(1)
    # find the matching "} else {" at the same indent, then the closing "}"
    depth, j, e, k = 0, i, None, None
    for j in range(i, len(L)):
        depth += L[j].count('{') - L[j].count('}')
        if depth == 0 and j > i or (j > i and depth == 1 and L[j] == ind + '} else {' and e is None and L[j].count('{') == 1):
            if L[j] == ind + '} else {' and e is None:
                e = j
                continue
            if L[j] == ind + '}':
                k = j
            break
    if e is None or k is None:
        continue
    T = L[:i] + ['%sif (%s) {' % (ind, neg(m.group(2)))] + L[e + 1:k] + [ind + '} else {'] + L[i + 1:e] + L[k:]
    if ONLY:
        L = T
        continue
    run(T, 'swap line %d' % (i + 1))
if ONLY:
    run(L, 'swap lines %s' % ONLY)
    if OUT:
        open(OUT, 'w').write('\n'.join(L))
