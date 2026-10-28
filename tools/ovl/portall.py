#!/usr/bin/env python3
"""tools/ovl/portall.py (session 141): A B: for every matched function of overlay A, find unmatched functions of B with the same
mnemonic sequence, port the C with port.py and keep matches (hand.py keep)."""
import os, re, subprocess, sys, glob
A, B = sys.argv[1:3]
R = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
TMP = os.path.join(R, 'out', 'ovl', 'port')
os.makedirs(TMP, exist_ok=True)
def rank(o):
    rows = {}
    for l in open(f'{R}/out/ovl/{o}/rank.tsv').read().splitlines()[1:]:
        f = l.split('\t'); rows[f[1]] = f
    return rows
def mn(o, f):
    r = subprocess.run(['python3', 'tools/kh1tool.py', 'asm', f], cwd=R, env={**os.environ, 'KH1_OVL': o}, capture_output=True, text=True)
    return tuple(m.group(1) for m in re.finditer(r'\*/\s+(\S+)', r.stdout))
for o in (A, B):
    subprocess.run(['python3', 'tools/kh1tool.py', 'rank', '--limit', '0', '--segment', 'all'], cwd=R, env={**os.environ, 'KH1_OVL': o}, capture_output=True)
ra, rb = rank(A), rank(B)
srcs = {}
for p in glob.glob(f'{R}/ovl/{A}/**/*.c', recursive=True):
    if '/auto/' in p: continue
    m = re.match(r'(func_[0-9a-f]{8})', os.path.basename(p))
    if m: srcs[m.group(1)[5:]] = p
unb = {a: f for a, f in rb.items() if f[17] != 'src'}
bysize = {}
for a, f in unb.items(): bysize.setdefault(f[3], []).append(a)
n = 0
for a, p in sorted(srcs.items()):
    if a not in ra: continue
    cands = bysize.get(ra[a][3], [])
    if not cands: continue
    sa = mn(A, 'func_' + a)
    for c in list(cands):
        if mn(B, 'func_' + c) != sa: continue
        mode = os.path.basename(p).split('.')
        out = f'{TMP}/{B}_{c}' + ('.' + mode[-2] if len(mode) > 2 else '') + '.c'
        r = subprocess.run(['python3', os.path.join(R, 'tools', 'ovl', 'port.py'), A, 'func_' + a, B, 'func_' + c, p, out], cwd=R, capture_output=True, text=True)
        if not os.path.exists(out): continue
        t = subprocess.run(['python3', 'tools/ovl/hand.py', 'try', B, 'func_' + c, out], cwd=R, capture_output=True, text=True).stdout.split('\n')[0]
        print(A, a, '->', B, c, t, r.stdout.strip()[:100], flush=True)
        if 'MATCH  match' in t:
            subprocess.run(['python3', 'tools/ovl/hand.py', 'keep', B, 'func_' + c, out], cwd=R, capture_output=True)
            cands.remove(c); n += 1
            break
print('ported', n)
