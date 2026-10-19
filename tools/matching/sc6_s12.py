# sc6.py file addr [RO] [-d] : compile, true DP LCS words vs original; -d prints an aligned diff
import sys, os, subprocess, re
W=os.environ.get('WDIR','/tmp/sc6_s12'); os.makedirs(W,exist_ok=True); os.environ['WDIR']=W
args=[a for a in sys.argv[1:] if not a.startswith('-')]; fl=[a for a in sys.argv[1:] if a.startswith('-')]
os.environ['RO']=args[2] if len(args)>2 else '0'
sys.path.insert(0,os.path.dirname(os.path.abspath(__file__))); import lro6_s12 as L
addr=args[1]
r=L.check(args[0], addr)
if not r: print('FAIL'); sys.exit(1)
d,pos,n,sz=r['func_'+addr]
def dis(f,a,n):
    o=subprocess.run(['mips-linux-gnu-objdump','-d','-z','-m','mips:5900','-EL','-M','gpr-names=32','--start-address=0x'+a,'--stop-address=0x%x'%(int(a,16)+n),f],capture_output=True,text=True).stdout
    return [l.split('\t',2)[2].replace('\t',' ').strip() if l.count('\t')>=2 else '' for l in o.split('\n') if re.match(r'\s+[0-9a-f]+:\t',l)], [l.split('\t')[1].strip() for l in o.split('\n') if re.match(r'\s+[0-9a-f]+:\t',l)]
ours,ow=dis(W+'/td/c.elf',addr,n); th,tw=dis('/home/claude/kh1-decomp/SLPS_251.98',addr,sz)
open(W+'/ours.txt','w').write('\n'.join(ours)+'\n'); open(W+'/orig.txt','w').write('\n'.join(th)+'\n')
a=ow;b=tw
P=[[0]*(len(b)+1) for _ in range(len(a)+1)]
for i in range(len(a)-1,-1,-1):
    Pi=P[i];Pn=P[i+1];ai=a[i]
    for j in range(len(b)-1,-1,-1):
        Pi[j]=Pn[j+1]+1 if ai==b[j] else (Pn[j] if Pn[j]>Pi[j+1] else Pi[j+1])
m=P[0][0]
print('TLCS %d (orig-unmatched %d, ours-unmatched %d) size %d vs %d pos %d'%(len(b)-m+len(a)-m if False else max(len(a),len(b))-m, len(b)-m, len(a)-m, n, sz, pos))
if '-d' in fl:
    i=j=0; out=[]
    while i<len(a) or j<len(b):
        if i<len(a) and j<len(b) and a[i]==b[j]: out.append('    %4x %s'%(j*4,th[j])); i+=1;j+=1
        elif j<len(b) and (i==len(a) or P[i][j+1]>=P[i+1][j]): out.append(' >  %4x %s'%(j*4,th[j])); j+=1
        else: out.append(' <  %4x %s'%(i*4,ours[i])); i+=1
    open(W+'/diff.txt','w').write('\n'.join(out)+'\n')
