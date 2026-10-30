#!/usr/bin/env python3
"""tools/ovl/i2a.py (session 141, wwm1 round 19): OVL DRAFT [N]

Turn the constant initializers in the declarations at the top of the function's body (`s32 a = 0, b = 0;`)
into plain assignments placed after the last declaration, then try the source order and N random orders
(default 40) with hand.py try. The order of these assignments can decide which stack slot each spilled
local gets, where no order of the initializers does (wm func_00f4b878). Prints the base and best word
counts and writes the best version to $I2A_DIR/best_OVL_FUNC[.mode].c (default out/ovl/i2a). Needs at
least two constant initializers. Check the best file's hand.py score before keeping it."""
import subprocess, sys, re, random, os
W = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
D = os.environ.get('I2A_DIR', os.path.join(W, 'out', 'ovl', 'i2a'))
o, path = sys.argv[1], sys.argv[2]
N = int(sys.argv[3]) if len(sys.argv) > 3 else 40
base = os.path.basename(path)
f = base.split('.')[0]
mode = '.' + base.split('.')[1] if base.count('.') > 1 else ''
L = open(path).read().split('\n')
start = next(i for i, l in enumerate(L) if re.search(r'\b%s\s*\(' % f, l) and not l.startswith(' ') and not l.rstrip().endswith(';'))
while '{' not in L[start]:
    start += 1
DECL = re.compile(r'^(\s+)((?:register |volatile |const )*(?:unsigned |signed )?[A-Za-z_]\w*(?:\s*\*+)?)\s+(.+);\s*$')
inits, newdecl, k = [], {}, start + 1
while k < len(L):
    m = DECL.match(L[k])
    if not m or '(' in m.group(3) and '=' not in m.group(3):
        if L[k].strip() == '':
            k += 1
            continue
        break
    parts = [p.strip() for p in re.split(r',(?![^()]*\))', m.group(3))]
    keep = []
    for p in parts:
        mm = re.match(r'^(\**\s*\w+)\s*=\s*(-?(?:0x[0-9A-Fa-f]+|\d+)(?:\.\d*f?)?f?|NULL)$', p)
        if mm:
            inits.append((mm.group(1).lstrip('*').strip(), mm.group(2)))
            keep.append(mm.group(1))
        else:
            keep.append(p)
    newdecl[k] = '%s%s %s;' % (m.group(1), m.group(2), ', '.join(keep))
    k += 1
last = k
if len(inits) < 2:
    print(o, f, 'inits', len(inits), 'skip')
    raise SystemExit
tmp = os.path.join(D, '%s_%s%s.c' % (o, f, mode))
os.makedirs(os.path.dirname(tmp), exist_ok=True)


def run(order):
    T = [newdecl.get(i, l) for i, l in enumerate(L)]
    ind = re.match(r'^(\s*)', L[start + 1]).group(1) or '    '
    T = T[:last] + ['%s%s = %s;' % (ind, v, c) for v, c in order] + T[last:]
    open(tmp, 'w').write('\n'.join(T))
    r = subprocess.run(['python3', 'tools/ovl/hand.py', 'try', o, f, tmp], cwd=W, capture_output=True, text=True).stdout.split('\n')[0]
    if 'MATCH' in r and 'FAIL' not in r:
        return 0, T
    w = re.search(r'(\d+) words', r)
    return (int(w.group(1)) if w else 9999), T


r0 = subprocess.run(['python3', 'tools/ovl/hand.py', 'try', o, f, path], cwd=W, capture_output=True, text=True).stdout.split('\n')[0]
w0 = int(re.search(r'(\d+) words', r0).group(1)) if re.search(r'(\d+) words', r0) else 9999
best = (w0, None)
orders = [list(inits)]
random.seed(1)
for _ in range(N):
    x = list(inits)
    random.shuffle(x)
    orders.append(x)
for od in orders:
    n, T = run(od)
    if n < best[0]:
        best = (n, T)
        open(os.path.join(D, 'best_%s_%s%s.c' % (o, f, mode)), 'w').write('\n'.join(T))
    if n == 0:
        break
print(o, f, 'inits', len(inits), 'base', w0, 'best', best[0], flush=True)
