# dif.py file RO addr : score and LCS diff (opcode-level ok)
import sys, os, subprocess, difflib, re
os.environ['RO']=sys.argv[2] if sys.argv[2]!='-' else '0'
sys.path.insert(0,'/tmp/claude-0/s12/s12w2')
import lro12 as L
addr=sys.argv[3]
r=L.check(sys.argv[1], addr); print(r)
if not r: sys.exit()
d,pos,n,sz=r['func_'+addr]
W=os.environ['WDIR']
def dis(f,a,n):
    o=subprocess.run(['mips-linux-gnu-objdump','-d','-m','mips:5900','-EL','-M','gpr-names=32','--start-address=0x'+a,'--stop-address=0x%x'%(int(a,16)+n),f],capture_output=True,text=True).stdout
    return [l.split('\t',1)[1].replace('\t',' ') for l in o.split('\n') if re.match(r'\s+[0-9a-f]+:\t',l)]
ours=dis(W+'/td/c.elf',addr,n); th=dis('/home/claude/kh1-decomp/SLPS_251.98',addr,sz)
ow=[x.split(' ',1)[0] for x in ours]
sm=difflib.SequenceMatcher(None,[x.split(' ',1)[0] for x in ours],[x.split(' ',1)[0] for x in th],autojunk=False)
ctx=int(os.environ.get('CTX','3'))
for tag,i1,i2,j1,j2 in sm.get_opcodes():
    if tag=='equal': continue
    print('--- ours %x-%x / orig %x-%x'%(i1*4,i2*4,j1*4,j2*4))
    for k in range(max(0,i1-ctx),i1): print('   ',ours[k])
    for k in range(i1,i2): print(' < ',ours[k])
    for k in range(j1,j2): print(' > ',th[k])
