#!/usr/bin/env python3
"""fperm.py FILE CALLER DIR: for every callee prototype with f32/f64 params, try every
position of the float params among the int params (keeping each group's order),
rewriting the prototype and all call sites in FILE; print improvements."""
import sys, re, subprocess, os, itertools
f, caller, d = sys.argv[1], sys.argv[2], sys.argv[3]
base = open(f).read()
R = '/home/claude/kh1-decomp'
def run(t):
    p = os.path.join(R, d, '.c2_fperm.c'); open(p, 'w').write(t)
    r = subprocess.run(['python3', 'tools/checkfile.py', p], capture_output=True, text=True, cwd=R).stdout
    os.remove(p)
    for l in r.splitlines():
        if l.startswith(caller[5:]): return l
    return 'ERR'
def score(l):
    if 'MATCH' in l: return 0
    m = re.search(r', (\d+) words', l); return int(m.group(1)) if m else 9999
def split_args(s):
    out, dep, cur = [], 0, ''
    for ch in s:
        if ch == ',' and dep == 0: out.append(cur.strip()); cur = ''; continue
        if ch in '([': dep += 1
        if ch in ')]': dep -= 1
        cur += ch
    if cur.strip(): out.append(cur.strip())
    return out
b0 = run(base); print('base', b0)
for pm in re.finditer(r'^([^\n;{}()]*?)\b(func_[0-9a-f]{8})\(([^;{}]*)\);', base, re.M):
    name, params = pm.group(2), split_args(pm.group(3))
    isf = [bool(re.match(r'(f32|f64|float|double)\b', p)) for p in params]
    if not any(isf) or all(isf): continue
    fl = [p for p, x in zip(params, isf) if x]; il = [p for p, x in zip(params, isf) if not x]
    n = len(params); best = None
    for pos in itertools.combinations(range(n), len(fl)):
        seq = []; fi = ii = 0
        for k in range(n):
            if k in pos: seq.append(('f', fi)); fi += 1
            else: seq.append(('i', ii)); ii += 1
        np = pm.group(1) + name + '(' + ', '.join(il[k] if t == 'i' else fl[k] for t, k in seq) + ');'
        s = base[:pm.start()] + '@@P@@' + base[pm.end():]
        ok = True
        def fix(m):
            global ok
            a = split_args(m.group(1))
            if len(a) != n: return m.group(0)
            fa = [x for x, y in zip(a, isf) if y]; ia = [x for x, y in zip(a, isf) if not y]
            return name + '(' + ', '.join(ia[k] if t == 'i' else fa[k] for t, k in seq) + ')'
        # call sites: name( ... ) balanced, one level
        s = re.sub(name + r'\(((?:[^()]|\([^()]*(?:\([^()]*\))*[^()]*\))*)\)', fix, s)
        s = s.replace('@@P@@', np)
        l = run(s)
        if best is None or score(l) < best[0]: best = (score(l), pos, np, l)
        if score(l) == 0: break
    print(name, best[1], best[3], best[2] if best[0] < score(b0) else '')
