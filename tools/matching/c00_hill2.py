# hill2.py NAME FILE DIR ITERS SEED : hill-climb lines between /*P*/ and /*Q*/, ndiff scoring; TRYPY env
import subprocess, sys, re, random, os, difflib
name, f, d, iters = sys.argv[1], sys.argv[2], sys.argv[3], int(sys.argv[4])
seed = int(sys.argv[5]) if len(sys.argv) > 5 else 1
TRY = ['python3', os.environ.get('TRYPY', 'tools/autodecomp.py')]
s = open(f).read()
a = s.index('/*P*/\n')+6; b = s.index('/*Q*/')
stmts = [l for l in s[a:b].split('\n') if l.strip()]
tmp = f'/home/claude/kh1-decomp/src/hand/{d}/.c00_hill_{name}_{seed}.c'
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
    r = subprocess.run([*TRY,'try',name,'--file',tmp,'--out-dir',f'src/hand/{d}','--diff'],cwd='/home/claude/kh1-decomp',capture_output=True,text=True).stdout
    return nd(r), src
random.seed(seed)
cur = stmts[:]; cs, src0 = score(cur); best = cs
print('start', cs, flush=True)
for it in range(iters):
    p = cur[:]
    i, j = random.randrange(len(p)), random.randrange(len(p))
    if random.random() < 0.5: p[i], p[j] = p[j], p[i]
    else: x = p.pop(i); p.insert(j, x)
    sc, src = score(p)
    if sc <= cs:
        if sc < cs: print(it, sc, flush=True)
        cur, cs = p, sc
        if sc < best:
            best = sc; open(f + '.best', 'w').write(src)
        if sc == 0: print('MATCH'); open(f + '.match', 'w').write(src); break
os.remove(tmp)
print('final', cs)
