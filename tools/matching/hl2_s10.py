# hl.py FILE ADDR ITERS SEED : hill-climb /*P*/../*Q*/ line order, LCS score (lcs*100+pos), deps respected; writes best to FILE.best
import subprocess, sys, re, random, os
f, addr, iters, seed = sys.argv[1], sys.argv[2], int(sys.argv[3]), int(sys.argv[4])
random.seed(seed)
s = open(f).read()
a = s.index('/*P*/\n') + 6; b = s.index('/*Q*/')
stmts = [l for l in s[a:b].split('\n') if l.strip()]
ident = re.compile(r'[A-Za-z_]\w*')
def info(l):
    m = re.match(r'\s*\**([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*[-+|&]?=[^=]', l)
    dv = m.group(1) if m and not m.group(2) else None
    rhs = l.split('=', 1)[1] if m else l
    return dv, set(ident.findall(rhs))
INF = {l: info(l) for l in stmts}
orig_pos = {l: i for i, l in enumerate(stmts)}
SF={}; _n=0
for l in stmts:
    if '/*FIX*/' in l: _n+=1
    SF[l]=_n
def valid(p):
    # keep relative order of any two lines where one defines a var the other mentions
    pos = {l: i for i, l in enumerate(p)}
    for x in p:
        dx, ux = INF[x]
        for y in p:
            if x is y or orig_pos[x] >= orig_pos[y]: continue
            dy, uy = INF[y]
            dep = (dx and (dx in uy or dx == dy)) or (dy and dy in ux) or ('/*FIX*/' in x and '/*FIX*/' in y)
            if dep and pos[x] > pos[y]: return False
    nf=0
    for x in p:
        if '/*FIX*/' in x: nf+=1
        elif '/*S*/' in x and SF[x]!=nf: return False
    return True
R = '/home/claude/kh1-decomp'
mode = os.path.dirname(os.path.relpath(f, R + '/src'))
tmp = f'{R}/src/{mode}/.w14_hl{seed}.c'
def score(p):
    open(tmp, 'w').write(s[:a] + '\n'.join(p) + '\n' + s[b:])
    out = subprocess.run(['python3', R + '/tools/matching/lcs_s8.py', tmp, addr], cwd=R, capture_output=True, text=True).stdout
    m = re.search(r'(\d+) vs (\d+) lcsoff (\d+) posoff (\d+)', out)
    if not m: return 10**9
    return (int(m.group(3)) + 4 * abs(int(m.group(1)) - int(m.group(2)))) * 1000 + int(m.group(4))
cur = stmts[:]; cs = score(cur); best = cs; bp = cur[:]
print('start', cs, flush=True)
for it in range(iters):
    p = cur[:]
    for _ in range(random.choice([1, 1, 1, 2, 3])):
        i = random.randrange(len(p)); l = p.pop(i); p.insert(random.randrange(len(p) + 1), l)
    if not valid(p): continue
    sc = score(p)
    if sc <= cs:
        if sc < cs: print(it, sc, flush=True)
        cur, cs = p, sc
        if sc < best:
            best, bp = sc, p[:]
            open(f + '.best', 'w').write(s[:a] + '\n'.join(bp) + '\n' + s[b:])
        if sc == 0: break
print('best', best)
os.remove(tmp)
