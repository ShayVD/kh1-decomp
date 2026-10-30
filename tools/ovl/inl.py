#!/usr/bin/env python3
"""tools/ovl/inl.py (session 141, wwm1 round 21): OVL DRAFT

For each local temp set as `v = EXPR;` and read once more, on the next statement line, try the draft with
EXPR written inline at that read (in parentheses), one temp at a time. Only locals declared in the function
are considered, never a global store. Prints hand.py try's result per temp and writes a matching version to
$OVLTOOL_DIR/inl_match_FUNC.c (default out/ovl/tools). Check that the inlined expression does not move a side
effect (a call) past another one before keeping it."""
import subprocess, sys, re, os
W = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
D = os.environ.get('OVLTOOL_DIR', os.path.join(W, 'out', 'ovl', 'tools'))
os.makedirs(D, exist_ok=True)
o, d = sys.argv[1:3]
base = os.path.basename(d)
f = base.split('.')[0]
mode = '.' + base.split('.')[1] if base.count('.') > 1 else ''
L = open(d).read().split('\n')
start = next(i for i, l in enumerate(L) if re.search(r'\b%s\s*\(' % f, l) and not l.startswith(' ') and not l.rstrip().endswith(';'))
body = '\n'.join(L[start:])
ASG = re.compile(r'^(\s*)([A-Za-z_]\w*)\s*=\s*([^=].*);\s*$')


def run(T, tag):
    p = os.path.join(D, 'inl_%s_%s%s.c' % (o, f, mode))
    open(p, 'w').write('\n'.join(T))
    r = subprocess.run(['python3', 'tools/ovl/hand.py', 'try', o, f, p], cwd=W, capture_output=True, text=True).stdout.split('\n')[0]
    print(tag, r[10:100], flush=True)
    if 'MATCH' in r and 'FAIL' not in r:
        open(os.path.join(D, 'inl_match_%s%s.c' % (f, mode)), 'w').write('\n'.join(T))


r0 = subprocess.run(['python3', 'tools/ovl/hand.py', 'try', o, f, d], cwd=W, capture_output=True, text=True).stdout.split('\n')[0]
print('base', r0[10:100])
for i in range(start + 1, len(L) - 1):
    m = ASG.match(L[i])
    if not m:
        continue
    v, e = m.group(2), m.group(3)
    # locals only: v must be declared in the function body above (never a global store)
    if not any(re.match(r'^\s+(?:register |volatile |const |unsigned |signed )*[A-Za-z_]\w*[\s\*]+[^;(=]*\b%s\b' % v, x) for x in L[start + 1:i]):
        continue
    uses = len(re.findall(r'\b%s\b' % v, body))
    if uses != 2:  # the assignment and one read (declaration lines without init are not counted below)
        decl = len(re.findall(r'^\s*[A-Za-z_][\w\s\*,]*\b%s\b[^=]*;' % v, body, re.M))
        if uses - decl != 2:
            continue
    j = i + 1
    while j < len(L) and L[j].strip() == '':
        j += 1
    if not re.search(r'\b%s\b' % v, L[j]) or re.match(r'^\s*%s\s*=' % v, L[j]):
        continue
    T = list(L)
    T[j] = re.sub(r'\b%s\b' % v, lambda _: '(' + e + ')', T[j], count=1)
    T[i] = ''
    run(T, 'inline %s (line %d)' % (v, i + 1))
