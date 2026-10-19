# togm.py BASE FUNC passes ALT1 ALT2 [ALT3...]: greedy coordinate descent, each occurrence of any ALT may be replaced by any other ALT
import os, sys, io, contextlib, re
sys.path.insert(0, '/home/claude/kh1-decomp/tools/matching')
import lchk_s10 as L
if os.environ.get('EX'): L.extra = os.environ['EX'].split()
base, fn, passes = sys.argv[1], sys.argv[2], int(sys.argv[3]); alts = sys.argv[4:]
s = open(base).read()
parts = re.split('(' + '|'.join(re.escape(a) for a in sorted(alts, key=len, reverse=True)) + ')', s)
idx = list(range(1, len(parts), 2))
state = [alts.index(parts[k]) for k in idx]
p = os.path.join(os.path.dirname(os.path.abspath(base)), '.s11tog_%d.c' % os.getpid())
def build(st):
    q = parts[:]
    for k, b in zip(idx, st): q[k] = alts[b]
    return ''.join(q)
def score(st):
    open(p, 'w').write(build(st))
    o = io.StringIO()
    with contextlib.redirect_stdout(o): r = L.check(p, fn)
    if not r or fn not in r: return (10**9, 0)
    v = r[fn]; return (v[0] + 4 * abs(v[2] - v[3]), v[1])
cur = score(state); print('start', cur, len(idx), flush=True)
for ps in range(passes):
    imp = False
    for n in range(len(idx)):
        for a in range(len(alts)):
            if a == state[n]: continue
            st = state[:]; st[n] = a
            sc = score(st)
            if sc < cur:
                cur, state, imp = sc, st, True; print('pass', ps, 'occ', n, '->', alts[a], sc, flush=True)
    if not imp: break
open(base + '.tog', 'w').write(build(state)); print('best', cur)
