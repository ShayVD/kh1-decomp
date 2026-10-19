# (session 15) random statement-order + dead no-else FP test search for func_00125240; HDR=header file (types/externs), run in a scratch dir: python3 -I srch125_s15.py SEED N "TEST1|TEST2"
# random search over statement order + dead no-else test position for 00125240
import sys, os, random, shutil
sys.path.insert(0,os.path.dirname(os.path.abspath(__file__)))
os.environ.setdefault('WDIR','/tmp/s15_srch'); os.makedirs(os.environ['WDIR'],exist_ok=True)
os.environ['RO']='0'
import lro7_s15 as L
R=str(L.ROOT)+'/'
HDR=open(os.environ.get('HDR','hdr.c')).read()
S=["D_002E2790.x = p->x;","D_002E2790.y = p->x;","D_002E2790.z = p->x;","D_002E2790.w = 1.0f;","p->y = -10000.0f;","D_004F77E0 = p->x;","p->w = 1.0f;","p->z = 10000.0f;","D_002E27A4 = p->x;"]
TESTS=sys.argv[3].split('|') if len(sys.argv)>3 else ["if (p[-1].x < -10000.0f) y = 0;"]
PRE=sys.argv[4] if len(sys.argv)>4 else ""
def src(order,tpos,test):
    body=[S[i] for i in order]; body.insert(tpos,test)
    return HDR+"void func_00125240(void) {\n    V4f *p = &D_002E2780;\n    f32 y;\n"+PRE+"    p->x = 0.0f;\n    "+"\n    ".join(body)+"\n    y = 53.0f;\n    func_00124c68(y);\n    func_00125000();\n    func_0011ef10(0x1adb0, func_00125000);\n    func_0011ef10(0x20f58, func_001251a0);\n    func_0017f510();\n}\n"
dst=R+'src/hand/.s15r_125_%s.c'%sys.argv[1]
def score(s):
    open(dst,'w').write(s)
    r=L.check(dst,'00125240'); 
    if not r: return 999
    w,pos,n,sz=r['func_00125240']; return w+(0 if n==sz else 50)
random.seed(int(sys.argv[1])); N=int(sys.argv[2])
best=(999,None); seen=set()
cur=(list(range(9)),0,0); cs=score(src(cur[0],cur[1],TESTS[cur[2]]))
for it in range(N):
    o,t,k=list(cur[0]),cur[1],cur[2]
    m=random.random()
    if m<0.5:
        i,j=random.sample(range(9),2); o[i],o[j]=o[j],o[i]
    elif m<0.8:
        i=random.randrange(9); x=o.pop(i); o.insert(random.randrange(9),x)
    elif m<0.95: t=random.randrange(10)
    else: k=random.randrange(len(TESTS))
    key=(tuple(o),t,k)
    if key in seen: continue
    seen.add(key)
    sc=score(src(o,t,TESTS[k]))
    if sc<=cs or random.random()<0.05:
        cur=(o,t,k); cs=sc
    if sc<best[0]:
        best=(sc,key); print(it,sc,key,flush=True); open('best_%s.c'%sys.argv[1],'w').write(src(o,t,TESTS[k]))
        if sc==0: break
print('BEST',best)
os.remove(dst)
