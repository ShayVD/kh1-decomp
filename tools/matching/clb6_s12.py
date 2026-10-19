# clb6.py TEMPLATE OUT ADDR ITERS SEED [RO] : hill-climb statement order (TEMPLATE has @S@, TEMPLATE.stm lines), true-LCS score.
# constraints: scalar 'v = ' defs before uses; calls keep relative order; a line touching matrix X stays between the same
# pair of calls touching X as in the start order.
import sys, random, re, os, subprocess
W=os.environ.get('WDIR','/tmp/clb6_s12')+'/'; os.makedirs(W,exist_ok=True); os.environ['WDIR']=W
tpl=open(sys.argv[1]).read(); out=sys.argv[2]; addr=sys.argv[3]; N=int(sys.argv[4]); random.seed(int(sys.argv[5]))
os.environ['RO']=sys.argv[6] if len(sys.argv)>6 else '0'
sys.path.insert(0,os.path.dirname(os.path.abspath(__file__))); import lro6_s12 as L
from elf32 import Elf
orig=open('/home/claude/kh1-decomp/SLPS_251.98','rb').read()
st=[l.rstrip('\n') for l in open(sys.argv[1]+'.stm') if l.strip()]
iscall=[bool(re.match(r'\s*\w+\(.*\);\s*$',l)) for l in st]
defs={}
for i,l in enumerate(st):
    m=re.match(r'\s*(\w+)\s*(=|\+=|-=|\+\+|--)',l)
    if m and not l.strip().startswith('if'): defs.setdefault(m.group(1),[]).append(i)
need={}; after={}
for i,l in enumerate(st):
    mm=re.match(r'\s*(\w+)\s*(\+=|-=|\+\+|--)',l)
    rhs=l if mm else (l.split('=',1)[1] if (re.match(r'\s*\w+ = ',l) and not iscall[i]) else l)
    need[i]=[]; after[i]=[]
    for v,ds in defs.items():
        if re.search(r'\b%s\b'%v,rhs):
            pr=[d for d in ds if d<i]; nx=[d for d in ds if d>i]
            if pr: need[i].append(pr[-1])
            if nx: after[i].append(nx[0])
    m=re.match(r'\s*(\w+)\s*(=|\+=|-=|\+\+|--)',l)
    if m and m.group(1) in defs and i in defs[m.group(1)]:
        ds=defs[m.group(1)]; k=ds.index(i)
        if k>0: need[i].append(ds[k-1])
mats=set(re.findall(r'\b(m\d|t|mt)\b',' '.join(st)))
calls=[i for i in range(len(st)) if iscall[i]]
seg={}
for i,l in enumerate(st):
    if iscall[i]: continue
    for X in mats:
        if re.search(r'\b%s\['%X,l):
            pre=[c for c in calls if c<i and re.search(r'\b%s\b'%X,st[c])]
            post=[c for c in calls if c>i and re.search(r'\b%s\b'%X,st[c])]
            seg[i]=(pre[-1] if pre else None, post[0] if post else None)
def ok(p):
    pos={x:k for k,x in enumerate(p)}
    cs=[x for x in p if iscall[x]]
    if cs!=calls: return False
    for i in p:
        for d in need[i]:
            if pos[d]>pos[i]: return False
        for d in after[i]:
            if pos[d]<pos[i]: return False
        if i in seg:
            a,b=seg[i]
            if a is not None and pos[a]>pos[i]: return False
            if b is not None and pos[b]<pos[i]: return False
    return True
def fo(va):
    import struct
    ph,n=struct.unpack_from('<I',orig,28)[0],struct.unpack_from('<H',orig,44)[0]
    for k in range(n):
        t,off,v,pa,fs,ms=struct.unpack_from('<6I',orig,ph+32*k)
        if v<=va<v+fs: return off+va-v
A0=int(addr,16)
def tl(a,b):
    prev=[0]*(len(b)+1)
    for x in a:
        cur=[0]
        for j,y in enumerate(b):
            cur.append(prev[j]+1 if x==y else (prev[j+1] if prev[j+1]>cur[j] else cur[j]))
        prev=cur
    return prev[-1]
cache={}
def score(p):
    p=tuple(p)
    if p in cache: return cache[p]
    open(out,'w').write(tpl.replace('@S@','\n'.join(st[i] for i in p)))
    r=L.check(out, addr)
    if not r: cache[p]=(9999,); return cache[p]
    d,pos,n,sz=r['func_'+addr]
    E=Elf.load(W+'td/c.elf'); ob=E.section_bytes(E.section('.f_func_'+addr))
    th=orig[fo(A0):fo(A0)+sz]
    a=[ob[k:k+4] for k in range(0,len(ob),4)]; b=[th[k:k+4] for k in range(0,len(th),4)]
    m=tl(a,b); cache[p]=(len(b)-m+abs(len(a)-len(b)),pos); return cache[p]
cur=list(range(len(st))); assert ok(cur); cs=score(cur); best=(cs,cur[:]); print('start',cs,flush=True)
for it in range(N):
    p=cur[:]
    for _ in range(random.choice([1,1,2])):
        i,j=random.sample(range(len(p)),2)
        if random.random()<.4: p[i],p[j]=p[j],p[i]
        else: x=p.pop(i); p.insert(j,x)
    if not ok(p): continue
    s=score(p)
    import math
    T=float(os.environ.get('TEMP','0'))
    if s<=cs or (T>0 and random.random()<math.exp(-(s[0]-cs[0])/T)):
        if s<cs: print(it,s,flush=True)
        cur,cs=p,s
        if s<best[0]: best=(s,p[:])
        if s[0]==0: break
print('best',best[0])
open(out,'w').write(tpl.replace('@S@','\n'.join(st[i] for i in best[1])))
open(out+'.order','w').write(' '.join(map(str,best[1])))
