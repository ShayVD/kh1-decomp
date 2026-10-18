# hill-climb statement order between /*P*/ and /*Q*/ ; usage hc_f.py BASE ITERS SEED
# Session 10 (w2): edit the scratch path/mode below and the address it checks before use; needs WDIR.
import subprocess, os, sys, random, re
import os; W=os.environ['WDIR']; R='/home/claude/kh1-decomp'
sys.path.insert(0, R+'/tools'); 
base = open(sys.argv[1]).read(); iters = int(sys.argv[2]); random.seed(int(sys.argv[3]))
lines = base.split('\n'); i0 = lines.index('/*P*/'); i1 = lines.index('/*Q*/'); blk = lines[i0+1:i1]
fn = f'{R}/src/hand/nofill/.w2_hc.c'
# persistent checker: import mchk machinery once
import importlib.util
SEED = sys.argv[3]; sys.argv = ['mchk.py']
spec = importlib.util.spec_from_file_location('mchk', W+'/mchk.py'); M = importlib.util.module_from_spec(spec); spec.loader.exec_module(M)
import io, contextlib
def score(b):
    s = '\n'.join(lines[:i0+1] + b + lines[i1:]); open(fn, 'w').write(s)
    f = io.StringIO()
    with contextlib.redirect_stdout(f): M.check(fn)
    o = f.getvalue()
    if 'MATCH' in o: return 0
    m = re.search(r'FAIL (\d+) vs (\d+), (\d+)w', o)
    if not m: return 9999
    return int(m.group(3)) + (0 if m.group(1) == m.group(2) else 500)
def valid(b):
    # define-before-use for f7,f4,f2,t
    for v in ['f7', 'f4', 'f2', 't']:
        d = [i for i, l in enumerate(b) if re.match(r'\s*%s = ' % v, l)]
        u = [i for i, l in enumerate(b) if re.search(r'\b%s\b' % v, l) and not re.match(r'\s*%s = ' % v, l)]
        if d and u and min(u) < d[0]: return False
    return True
cur = blk[:]; best = score(cur); print('start', best)
seen = {}
for it in range(iters):
    b = cur[:]
    i, j = random.sample(range(len(b)), 2)
    x = b.pop(i); b.insert(j, x)
    if not valid(b): continue
    k = tuple(b)
    if k in seen: continue
    sc = score(b); seen[k] = sc
    if sc <= best:
        if sc < best: print(it, sc, flush=True)
        best = sc; cur = b
        if sc == 0: break
print('best', best); print('\n'.join(cur))
open(W+'/hc_best_%s.txt' % SEED, 'w').write('\n'.join(cur))
os.remove(fn)
