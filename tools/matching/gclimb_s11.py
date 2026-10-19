# gclimb.py FILE FUNC ITERS SEED OUT [start-token-list]: lines between /*P*/ /*Q*/ of form 'LHS = RHS; //T' where T is the C type; tokens cN | kN sN
import os,sys,io,contextlib,random,re
sys.path.insert(0,'/home/claude/kh1-decomp/tools/matching')
if os.environ.get('RO'): import lchkro_s10 as L
else: import lchk_s10 as L
f,fn,iters,seed,out=sys.argv[1],sys.argv[2],int(sys.argv[3]),int(sys.argv[4]),sys.argv[5]; random.seed(seed)
s=open(f).read(); a=s.index('/*P*/\n')+6; b=s.index('/*Q*/')
st=[l for l in s[a:b].split('\n') if l.strip()]
P=[]
for l in st:
    m=re.match(r'\s*(.*?)\s*=\s*(.*?);\s*//\s*(\S+)',l)
    P.append((m.group(1),m.group(2),m.group(3)) if m else None)
N=len(st)
decl=''.join('    %s gk%d;\n'%(P[i][2],i) for i in range(N) if P[i])
body_at=s.index('{',s.index(fn+'('))+1
tmp=os.path.join(os.path.dirname(os.path.abspath(f)),'.s11w61_gc.c')
def gen(toks):
    o=[]
    for t in toks:
        n=int(t[1:])
        if t[0]=='c': o.append(st[n] if not P[n] else '    %s = %s;'%(P[n][0],P[n][1]))
        elif t[0]=='k': o.append('    gk%d = %s;'%(n,P[n][1]))
        else: o.append('    %s = gk%d;'%(P[n][0],n))
    return s[:body_at]+'\n'+decl+s[body_at:a]+'\n'.join(o)+'\n'+s[b:]
def valid(p):
    pos={t:i for i,t in enumerate(p)}
    for n in range(N):
        if 'k%d'%n in pos and pos['k%d'%n]>pos['s%d'%n]: return False
    return True
cache={}
def score(p):
    k=' '.join(p)
    if k in cache: return cache[k]
    open(tmp,'w').write(gen(p)); o=io.StringIO()
    with contextlib.redirect_stdout(o): r=L.check(tmp,fn)
    v=10**9 if not r or fn not in r else (r[fn][0]+4*abs(r[fn][2]-r[fn][3]))*1000+r[fn][1]
    cache[k]=v; return v
cur=sys.argv[6].split() if len(sys.argv)>6 else ['c%d'%i for i in range(N)]
cs=score(cur); best=cs; print('start',cs,flush=True)
for it in range(iters):
    p=cur[:]
    for _ in range(random.choice([1,1,1,2,3])):
        if random.random()<0.2:
            n=random.choice([i for i in range(N) if P[i]])
            if 'c%d'%n in p:
                i=p.index('c%d'%n); p[i]='s%d'%n; p.insert(random.randrange(i+1),'k%d'%n)
            else:
                p.remove('k%d'%n); p[p.index('s%d'%n)]='c%d'%n
        else:
            i=random.randrange(len(p)); x=p.pop(i); p.insert(random.randrange(len(p)+1),x)
    if not valid(p): continue
    sc=score(p)
    if sc<=cs:
        if sc<cs: print(it,sc,' '.join(p),flush=True)
        cur,cs=p,sc
        if sc<best: best=sc; open(out,'w').write(gen(p)); open(out+'.tok','w').write(' '.join(p))
print('best',best); os.remove(tmp)
