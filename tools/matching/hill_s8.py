# hill.py FILE MODE ITERS SEED [rr ADDR FUNC]: hill-climb order of lines between /*P*/ and /*Q*/ (deps respected)
import subprocess, sys, re, random, os
f, mode, iters, seed = sys.argv[1], sys.argv[2], int(sys.argv[3]), int(sys.argv[4])
rr = sys.argv[5:8] if len(sys.argv) > 5 else None
R = '/home/claude/kh1-decomp'; W = os.environ.get('WDIR', '/tmp/claude-0/s8/w5')
random.seed(seed)
s = open(f).read()
a = s.index('/*P*/\n') + 6; b = s.index('/*Q*/')
stmts = [l for l in s[a:b].split('\n') if l.strip()]
ident = re.compile(r'[A-Za-z_]\w*')
def info(l):
    m = re.match(r'\s*\**([A-Za-z_]\w*)\s*=[^=]', l)
    dv = m.group(1) if m else None
    rhs = l.split('=', 1)[1] if m else l
    return dv, set(ident.findall(rhs))
INF = {l: info(l) for l in stmts}
def valid(p):
    seen = set(); defs = {INF[l][0] for l in p if INF[l][0]}
    for l in p:
        dv, uses = INF[l]
        for u in uses:
            if u in defs and u not in seen: return False
        if '/*FIX*/' in l and any('/*FIX*/' in x for x in p[p.index(l)+1:]) is False: pass
        if dv: seen.add(dv)
    fx = [l for l in p if '/*FIX*/' in l]
    return fx == [l for l in stmts if '/*FIX*/' in l]
tmp = f'{R}/src/{mode}/.w5_h{seed}.c'
def score(p):
    open(tmp, 'w').write(s[:a] + '\n'.join(p) + '\n' + s[b:])
    if rr:
        out = subprocess.run(['python3', W + '/rr.py', rr[0], 'try', rr[1], '--file', tmp, '--out-dir', 'src/' + mode], cwd=R, capture_output=True, text=True).stdout
        if 'MATCH  match' in out: return 0
        m = re.search(r'(\d+) vs (\d+) bytes, (\d+) words', out)
    else:
        out = subprocess.run(['python3', 'tools/checkfile.py', tmp], cwd=R, capture_output=True, text=True).stdout
        if ' MATCH' in out: return 0
        m = re.search(r'(\d+) vs (\d+), (\d+) words', out)
    return int(m.group(3)) + 4 * abs(int(m.group(1)) - int(m.group(2))) if m else 10**6
cur = stmts[:]; cs = score(cur); best = cs
print('start', cs, flush=True)
for it in range(iters):
    p = cur[:]
    i, j = random.sample(range(len(p)), 2)
    if random.random() < 0.5: p[i], p[j] = p[j], p[i]
    else: x = p.pop(i); p.insert(j, x)
    if not valid(p): continue
    sc = score(p)
    if sc <= cs:
        cur, cs = p, sc
        if sc < best:
            best = sc; open(f + '.best', 'w').write(s[:a] + '\n'.join(p) + '\n' + s[b:]); print(it, sc, flush=True)
        if sc == 0: break
os.remove(tmp)
print('best', best)
