# hc.py FILE MODE TAG ITERS [SEED]: hill-climb order of lines between /*P*/ and /*Q*/ (checkfile score: words differ of first FAIL/MATCH line for ADDR env)
import sys,re,random,subprocess,os
f,mode,tag,iters=sys.argv[1],sys.argv[2],sys.argv[3],int(sys.argv[4]); seed=int(sys.argv[5]) if len(sys.argv)>5 else 1
random.seed(seed)
ADDR=os.environ.get('ADDR')
s=open(f).read(); a=s.index('/*P*/\n')+6; b=s.index('/*Q*/')
pre,body,post=s[:a],s[a:b],s[b:]
L=[l for l in body.split('\n') if l.strip()]
ident=re.compile(r'[A-Za-z_]\w*')
def info(l):
    m=re.match(r'\s*([A-Za-z_]\w*)\s*(\+|-|\*|/|\||&)?=[^=]',l)
    dv=m.group(1) if m else None
    uses=set(ident.findall(l))
    return dv,uses
INF=[info(l) for l in L]
n=len(L)
must=set()
for i in range(n):
    for j in range(i+1,n):
        di,ui=INF[i]; dj,uj=INF[j]
        if '/*FIX*/' in L[i] and '/*FIX*/' in L[j]: must.add((i,j))
        if (di and di in uj) or (dj and dj in ui): must.add((i,j))
def valid(p):
    pos={x:k for k,x in enumerate(p)}
    return all(pos[i]<pos[j] for i,j in must)
tf='/home/claude/kh1-decomp/src/%s/.w16_hc_%s.c'%(mode,tag)
def score(p):
    open(tf,'w').write(pre+'\n'.join(L[i] for i in p)+'\n'+post)
    r=subprocess.run(['python3','tools/checkfile.py',tf],cwd='/home/claude/kh1-decomp',capture_output=True,text=True)
    for line in r.stdout.splitlines():
        if ADDR and not line.startswith(ADDR): continue
        if 'MATCH' in line: return 0
        m=re.search(r'(\d+) vs (\d+), (\d+) words',line)
        if m: return int(m.group(3))+ (0 if m.group(1)==m.group(2) else int(os.environ.get("SZPEN","1000")))
    return 99999
cur=list(range(n)); cs=score(cur); best=cs; print('start',cs,flush=True)
for it in range(iters):
    p=cur[:]
    i=random.randrange(n); j=random.randrange(n)
    x=p.pop(i); p.insert(j,x)
    if random.random()<0.3:
        i=random.randrange(n); j=random.randrange(n); x=p.pop(i); p.insert(j,x)
    if p==cur or not valid(p): continue
    sc=score(p)
    if sc<=cs:
        if sc<cs: print(it,sc,flush=True)
        cur,cs=p,sc
        if sc<best:
            best=sc; open('/tmp/claude-0/s7/w16/t/hc_%s.best'%tag,'w').write(pre+'\n'.join(L[i] for i in p)+'\n'+post)
        if sc==0: break
print('final',cs)
