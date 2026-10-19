# (session 15) vrun ADDR MODE RO FILE...: score each file (copied into src/MODE as a dot file); writes FILE.s
# vrun.py ADDR MODE RO FILE...: score each C file (copied into src/MODE) for func ADDR
import sys, os, shutil
sys.path.insert(0,os.path.dirname(os.path.abspath(__file__)))
os.environ.setdefault('WDIR','/tmp/s15_w')
os.makedirs(os.environ['WDIR'], exist_ok=True)
import lro7_s15 as L
R=str(L.ROOT)+'/'
a,mode,ro=sys.argv[1:4]; os.environ['RO']=ro
for f in sys.argv[4:]:
    dst=R+'src/'+mode+'/.s15v_'+a+'.c'; shutil.copy(f,dst)
    try: r=L.check(dst,a)
    except Exception as e: r=None; print('ERR',e)
    print(os.path.basename(f), r and r.get('func_'+a), flush=True)
    shutil.copy(os.environ['WDIR']+'/last.s', f+'.s')
    os.remove(dst)
