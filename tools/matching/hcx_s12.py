# hcx.py TEMPLATE OUT ADDR ITERS SEED : hill-climb order of TEMPLATE.stm lines; constraint: a line 'kN = ' must precede lines using kN (word match)
import sys, random, re, os, time
sys.path.insert(0,'/home/claude/kh1-decomp/tools/matching')
os.environ.setdefault('WDIR','/tmp/claude-0/s12/s12w1')
import lchk_s10 as L
tpl=open(sys.argv[1]).read(); out=sys.argv[2]; addr=sys.argv[3]; N=int(sys.argv[4]); random.seed(int(sys.argv[5]))
st=[l.rstrip('\n') for l in open(sys.argv[1]+'.stm') if l.strip()]
defs={}
for i,l in enumerate(st):
    m=re.match(r'\s*(\w+) = ',l)
    if m: defs[m.group(1)]=i
need={i:[defs[v] for v in defs if defs[v]!=i and re.search(r'\b%s\b'%v, l.split('=',1)[1] if '=' in l else l)] for i,l in enumerate(st)}
def ok(p):
    pos={x:k for k,x in enumerate(p)}
    return all(pos[d]<pos[i] for i in p for d in need[i])
cache={}
def score(p):
    p=tuple(p)
    if p in cache: return cache[p]
    open(out,'w').write(tpl.replace('@S@','\n'.join(st[i] for i in p)))
    r=L.check(out); v=[x for k,x in r.items() if addr in k][0] if r else (999,999,0,1)
    cache[p]=(v[0],v[1],abs(v[2]-v[3])); return cache[p]
cur=list(range(len(st))); cs=score(cur); best=(cs,cur[:]); print('start',cs,flush=True)
for it in range(N):
    p=cur[:]
    for _ in range(random.choice([1,1,2])):
        i,j=random.sample(range(len(p)),2)
        if random.random()<.5: p[i],p[j]=p[j],p[i]
        else: x=p.pop(i); p.insert(j,x)
    if not ok(p): continue
    s=score(p)
    if s<=cs:
        if s<cs: print(it,s,p,flush=True)
        cur,cs=p,s
        if s<best[0]: best=(s,p[:])
        if s[1]==0 and s[2]==0: break
print('best',best)
open(out,'w').write(tpl.replace('@S@','\n'.join(st[i] for i in best[1])))
