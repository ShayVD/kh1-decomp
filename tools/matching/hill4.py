# hill3.py NAME FILE DIR ITERS SEED : dependency-respecting hill climb of lines between /*P*/ and /*Q*/
# A line "V = ...;" defines V (simple identifier). Any later-use of V must stay after its def.
# Lines containing "/*FIX*/" never move relative to each other.
import subprocess, sys, re, random, os, difflib
name, f, d, iters = sys.argv[1], sys.argv[2], sys.argv[3], int(sys.argv[4])
seed = int(sys.argv[5]) if len(sys.argv) > 5 else 1
TRY = ['python3', os.environ.get('TRYPY', 'tools/autodecomp.py')]
s = open(f).read()
a = s.index('/*P*/\n')+6; b = s.index('/*Q*/')
stmts = [l for l in s[a:b].split('\n') if l.strip()]
tmp = f'/home/claude/kh1-decomp/src/hand/{d}/.w6f9_h4_{name}_{seed}.c'
ident = re.compile(r'[A-Za-z_]\w*')
def info(l):
    m = re.match(r'\s*([A-Za-z_]\w*)\s*=[^=]', l)
    dv = m.group(1) if m else None
    rhs = l.split('=', 1)[1] if m else l
    uses = set(ident.findall(rhs))
    return dv, uses
INF = {l: info(l) for l in stmts}
def valid(p):
    seen = set(); defs = {INF[l][0] for l in p if INF[l][0]}
    fix = [l for l in p if '/*FIX*/' in l]
    if fix != [l for l in stmts if '/*FIX*/' in l]: return False
    for l in p:
        dv, uses = INF[l]
        for u in uses:
            if u in defs and u not in seen and u != dv: return False
        if dv: seen.add(dv)
    return True
def nd(out):
    lines = out.splitlines()
    if lines and 'MATCH' in lines[0] and 'mismatch' not in lines[0]: return 0
    o, u = [], []
    for l in lines[1:]:
        m = re.match(r'^([0-9a-f]{8}) (..) (.{40}) ?(.*)$', l)
        if not m: continue
        x, y = m.group(3).strip(), m.group(4).strip()
        nm = lambda z: re.sub(r'0x1[0-9a-f]{5}$', 'L', z)
        if x: o.append(nm(x))
        if y: u.append(nm(y))
    if not o: return 10**6
    sm = difflib.SequenceMatcher(None, o, u, autojunk=False)
    return sum(max(i2-i1, j2-j1) for tg, i1, i2, j1, j2 in sm.get_opcodes() if tg != 'equal')
def score(p):
    src = s[:a] + '\n'.join(p) + '\n' + s[b:]
    open(tmp,'w').write(src)
    if os.environ.get('CHK'):
        r = subprocess.run(['python3','tools/checkfile.py',tmp],cwd='/home/claude/kh1-decomp',capture_output=True,text=True).stdout
        for l in r.splitlines():
            if l.startswith(name[5:]):
                if 'MATCH' in l: return 0, src
                m = re.search(r'(\d+) vs (\d+), (\d+) words', l)
                if m: return int(m.group(3)) + 4*abs(int(m.group(1))-int(m.group(2))), src
        return 10**6, src
    r = subprocess.run([*TRY,'try',name,'--file',tmp,'--out-dir',f'src/hand/{d}'],cwd='/home/claude/kh1-decomp',capture_output=True,text=True).stdout
    l = r.splitlines()[0] if r else ''
    if 'MATCH' in l and 'mismatch' not in l: return 0, src
    m = re.search(r'(\d+) vs (\d+) bytes, (\d+) words', l)
    return (int(m.group(3)) + 4*abs(int(m.group(1))-int(m.group(2)))) if m else 10**6, src
random.seed(seed)
assert valid(stmts), 'initial order invalid'
cur = stmts[:]; cs, src0 = score(cur); best = cs
print('start', cs, flush=True)
it = 0; tries = 0
while it < iters:
    p = cur[:]
    i, j = random.randrange(len(p)), random.randrange(len(p))
    if random.random() < 0.5: p[i], p[j] = p[j], p[i]
    else: x = p.pop(i); p.insert(j, x)
    tries += 1
    if not valid(p) or p == cur: continue
    it += 1
    sc, src = score(p)
    if sc <= cs:
        if sc < cs: print(it, sc, flush=True)
        cur, cs = p, sc
        if sc < best:
            best = sc; open(f + '.best', 'w').write(src)
        if sc == 0: print('MATCH'); open(f + '.match', 'w').write(src); break
os.remove(tmp)
print('final', cs)
