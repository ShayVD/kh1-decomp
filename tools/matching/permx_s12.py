# permx.py TEMPLATE OUT ADDR N : TEMPLATE has @S@ placeholder; statements in file TEMPLATE.stm (one per line); random/full perms
import sys, itertools, random, time, os
sys.path.insert(0,'/home/claude/kh1-decomp/tools/matching')
os.environ.setdefault('WDIR','/tmp/claude-0/s12/s12w1')
import lchk_s10 as L
tpl=open(sys.argv[1]).read(); out=sys.argv[2]; addr=sys.argv[3]; N=int(sys.argv[4])
st=[l.rstrip('\n') for l in open(sys.argv[1]+'.stm') if l.strip()]
best=None; t0=time.time(); seen=set()
perms = list(itertools.permutations(range(len(st)))) if N==0 else None
it = perms if perms else (random.sample(range(len(st)),len(st)) for _ in range(N))
res=[]
for p in it:
    p=tuple(p)
    if p in seen: continue
    seen.add(p)
    open(out,'w').write(tpl.replace('@S@','\n'.join(st[i] for i in p)))
    r=L.check(out)
    if not r: continue
    v=[x for k,x in r.items() if addr in k][0]
    sc=(v[0],v[1],abs(v[2]-v[3]))
    res.append((sc,p))
    if best is None or sc<best[0]:
        best=(sc,p); print(sc,p,flush=True)
        if sc[1]==0 and sc[2]==0: break
res.sort(); print('top', res[:8]); print('time',time.time()-t0)
