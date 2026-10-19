# (session 15) random climb of statement order between /*P*/ and /*Q*/ (one statement per line, def-before-use kept) plus optional insertion of one test line
# pclimb.py FILE ADDR MODE RO SEED N [TESTS sep by |]: random climb over statement order between /*P*/ and /*Q*/
# (one statement per line, def-before-use kept), plus optional insertion of one test line (position climbs too).
import sys, os, random, re
sys.path.insert(0,os.path.dirname(os.path.abspath(__file__)))
os.environ.setdefault('WDIR','/tmp/s15_pc'); os.makedirs(os.environ['WDIR'],exist_ok=True)
f,addr,mode,ro,seed,N=sys.argv[1:7]; os.environ['RO']=ro
TESTS=[""]+(sys.argv[7].split('|') if len(sys.argv)>7 else [])
import lro7_s15 as L
R=str(L.ROOT)+'/'
s=open(f).read(); i=s.index('/*P*/\n')+6; j=s.index('/*Q*/')
pre,mid,post=s[:i],s[i:j],s[j:]
st=[l for l in mid.split('\n') if l.strip()]
ID=re.compile(r'[A-Za-z_]\w*')
def du(l):
    m=re.match(r'\s*([A-Za-z_]\w*)\s*(=|<<=|\+=|-=|\|=)',l)
    d=m.group(1) if m else None
    u=set(ID.findall(l if not m or m.group(2)!='=' else l[m.end():]))
    return d,u
DU=[du(l) for l in st]
def ok(o):
    for a in range(len(o)):
        da,ua=DU[o[a]]
        for b in range(a+1,len(o)):
            db,ub=DU[o[b]]
            if o[a]>o[b]:
                # originally b before a: forbidden if dependency
                if (db and db in ua) or (da and da in ub) or (da and da==db): return False
    return True
dst=R+'src/'+mode+'/.s15pc_'+addr+'.c'
def src(o,t,k):
    body=[st[x] for x in o]
    if k: body.insert(t,'        '+TESTS[k])
    return pre+'\n'.join(body)+'\n'+post
def score(c):
    open(dst,'w').write(c)
    r=L.check(dst,addr)
    if not r: return 9999
    w,pos,n,sz=r['func_'+addr]; return w+(0 if n==sz else 50)
random.seed(int(seed)); n=len(st)
cur=(list(range(n)),0,0); cs=score(src(*cur)); print('base',cs,flush=True)
best=cs; seen=set()
for it in range(int(N)):
    o,t,k=list(cur[0]),cur[1],cur[2]; m=random.random()
    if m<0.4: a,b=random.sample(range(n),2); o[a],o[b]=o[b],o[a]
    elif m<0.75: a=random.randrange(n); x=o.pop(a); o.insert(random.randrange(n),x)
    elif m<0.92: t=random.randrange(n+1)
    else: k=random.randrange(len(TESTS))
    key=(tuple(o),t,k)
    if key in seen or not ok(o): continue
    seen.add(key); sc=score(src(o,t,k))
    if sc<=cs or random.random()<0.03: cur=(o,t,k); cs=sc
    if sc<best:
        best=sc; print(it,sc,k,t,flush=True); open(f+'.best%s.c'%seed,'w').write(src(o,t,k))
        if sc==0: break
print('BEST',best); os.remove(dst)
