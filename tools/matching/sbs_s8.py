# sbs.py SRC ADDR [from to]: side-by-side ours vs orig (LCS aligned) of one function
import sys, os, subprocess, difflib, re
W=os.environ.get('WDIR', '/tmp/claude-0/s8/w12'); src=sys.argv[1]; addr=sys.argv[2]
env=dict(os.environ, WDIR=W, W9_DUMP='1')
print(subprocess.run(['python3','/home/claude/kh1-decomp/tools/matching/lcs_s8.py',src,addr],env=env,capture_output=True,text=True).stdout.strip())
txt=open(W+'/ours.txt').read()
m=re.search(r'<[^>]*%s[^>]*>:\n(.*?)(\n\n|\Z)'%addr.lstrip('0'), txt, re.S)
if not m:
    m=re.search(r'Disassembly of section \.f_func_%s:\n\n[^\n]*\n(.*?)(\n\n|\Z)'%addr, txt, re.S)
ours=[l.split('\t',1)[1] for l in m.group(1).split('\n') if '\t' in l]
n=len(ours)
o=subprocess.run(['mips-linux-gnu-objdump','-d','-m','mips:5900','-EL','-M','gpr-names=32','--start-address=0x'+addr,'--stop-address=0x%x'%(int(addr,16)+4*(n+40)),'/home/claude/kh1-decomp/SLPS_251.98'],capture_output=True,text=True).stdout
th=[l.split('\t',1)[1] for l in o.split('\n') if re.match(r'\s+[0-9a-f]+:\t',l)]
th=th[:n] if len(sys.argv)<=5 else th[:int(sys.argv[5])]
ow=[x.split('\t')[0].strip() for x in ours]; tw=[x.split('\t')[0].strip() for x in th]
sm=difflib.SequenceMatcher(None,ow,tw,autojunk=False)
a0=int(addr,16); lo=int(sys.argv[3],16) if len(sys.argv)>3 else 0; hi=int(sys.argv[4],16) if len(sys.argv)>4 else 1<<40
for tag,i1,i2,j1,j2 in sm.get_opcodes():
    for k in range(max(i2-i1,j2-j1)):
        i=i1+k; j=j1+k
        a=ours[i].replace('\t',' ') if i<i2 else ''; b=th[j].replace('\t',' ') if j<j2 else ''
        ad=a0+4*(j if j<j2 else j1)
        if lo<=ad<hi and (tag!='equal' or len(sys.argv)>3):
            print('%06x %s %-38s %s'%(ad,'=' if tag=='equal' else '*',a[:38],b[:38]))
