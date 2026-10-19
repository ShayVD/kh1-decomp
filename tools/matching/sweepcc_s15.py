# (session 15) score drafts from a list file ("addr mode nonmatchings/path RO") under compilers (arg 2, comma list) x extra flags (arg 3, comma list)
# sweepcc.py LIST: score drafts under several compilers (CCOVR) and extra flags
import sys, os, shutil
sys.path.insert(0,os.path.dirname(os.path.abspath(__file__)))
os.environ.setdefault('WDIR','/tmp/s15_w')
os.makedirs(os.environ['WDIR'], exist_ok=True)
import lro7_s15 as L
R=str(L.ROOT)+'/'
ccs=sys.argv[2].split(',') if len(sys.argv)>2 else ['ee-gcc2.96','ee-gcc2.9-991111a','ee-gcc2.9-991111-01']
xfls=sys.argv[3].split(',') if len(sys.argv)>3 else ['']
for line in open(sys.argv[1]):
    a,mode,f,ro=line.split()
    dst=R+'src/'+mode+'/.s15sw_'+a+'.c'; shutil.copy(R+'nonmatchings/'+f,dst)
    os.environ['RO']=ro
    for cc in ccs:
        for x in xfls:
            os.environ['CCOVR']=cc; os.environ['XFL']=x
            try: r=L.check(dst,a)
            except Exception as e: r=None; print('ERR',e)
            print(a,f.split('/')[-1][:30],cc,x,r and r.get('func_'+a),flush=True)
    os.remove(dst)
