# hc.py FILE FUNC ITERS SEED: hill-climb lines between /*P*/ and /*Q*/ (dep-respecting), in-process LCS (RO env for rodata)
import os, sys, re, random, io, contextlib, tempfile, shutil
sys.path.insert(0, '/home/claude/kh1-decomp/tools/matching')
f, fn, iters, seed = sys.argv[1], sys.argv[2], int(sys.argv[3]), int(sys.argv[4]); random.seed(seed)
_d = tempfile.mkdtemp(prefix='s11w2hc_')
if os.environ.get('RO'):
    import lchkro_s10 as L; L.tempfile.mkdtemp = lambda *a, **k: _d
else: import lchk_s10 as L
s = open(f).read(); a = s.index('/*P*/\n') + 6; b = s.index('/*Q*/')
stmts = [l for l in s[a:b].split('\n') if l.strip()]
ident = re.compile(r'[A-Za-z_]\w*')
def info(l):
    m = re.match(r'\s*([A-Za-z_][\w>\-\.\[\]]*)\s*[-+|&]?=[^=]', l)
    d = m.group(1) if m else None
    dv = d if d and re.fullmatch(r'\w+', d) else None
    rhs = l.split('=', 1)[1] if m else l
    u = set(ident.findall(rhs))
    if d and not dv: u |= set(ident.findall(d))
    return dv, u, d
INF = {l: info(l) for l in stmts}; op = {l: i for i, l in enumerate(stmts)}
def valid(p):
    pos = {l: i for i, l in enumerate(p)}
    for x in p:
        dx, ux, _ = INF[x]
        for y in p:
            if op[x] >= op[y]: continue
            dy, uy, _ = INF[y]
            dep = (dx and (dx in uy or dx == dy)) or (dy and dy in ux) or ('/*FIX*/' in x and '/*FIX*/' in y)
            if dep and pos[x] > pos[y]: return False
    return True
tmp = os.path.join(os.path.dirname(os.path.abspath(f)), '.s11w2_hc%d.c' % seed)
def score(p):
    open(tmp, 'w').write(s[:a] + '\n'.join(p) + '\n' + s[b:])
    o = io.StringIO()
    with contextlib.redirect_stdout(o): r = L.check(tmp, fn)
    if not r or fn not in r: return 10**9
    v = r[fn]; return (v[0] + 4 * abs(v[2] - v[3])) * 1000 + v[1]
cur = stmts[:]; cs = score(cur); best = cs; print('start', cs, flush=True)
try:
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
                best = sc; open(f + '.best', 'w').write(s[:a] + '\n'.join(p) + '\n' + s[b:])
            if sc == 0: break
finally:
    print('best', best); os.remove(tmp); shutil.rmtree(_d, True)
