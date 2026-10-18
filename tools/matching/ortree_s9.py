import itertools, subprocess, re, sys, os
CC='/home/claude/kh1-decomp/tools/toolchain/ee-gcc2.9-991111a/bin/ee-gcc'
L={'M':'(u64)(m) << 23','W':'(u64)(w) << 32','X':'(u64)(x & 0xfff)','H':'(u64)(h) << 44','Y':'(u64)(y & 0xfff) << 12'}
regs={'$5':'M','$6':'W','$7':'X','$8':'H','$9':'Y'}
def trees(ls):
    if len(ls)==1: yield ls[0]; return
    for i in range(1,len(ls)):
        for a in trees(ls[:i]):
            for b in trees(ls[i:]): yield (a,b)
def src(t): return '(%s)'%L[t] if isinstance(t,str) else '(%s | %s)'%(src(t[0]),src(t[1]))
def name(t): return t if isinstance(t,str) else '(%s|%s)'%(name(t[0]),name(t[1]))
allt=[]
for p in itertools.permutations('MWXHY'):
    for t in trees(list(p)): allt.append(t)
prog=['typedef unsigned long u64;']
for i,t in enumerate(allt):
    prog.append('void f%d(u64 *p, int m, int w, int x, int h, int y) { *p = %s; }'%(i,src(t)))
open('ot.c','w').write('\n'.join(prog))
out=subprocess.run([CC,'-O2','-G0','-S','-o','-','ot.c'],capture_output=True,text=True).stdout
res={}
for m in re.finditer(r'^f(\d+):\n(.*?)\n\s*sd\s',out,re.S|re.M):
    i=int(m.group(1)); val=dict(regs)
    for line in m.group(2).split('\n'):
        mm=re.match(r'\s*or\s+(\$\d+),(\$\d+),(\$\d+)',line)
        if mm: val[mm.group(1)]='(%s|%s)'%(val[mm.group(2)],val[mm.group(3)])
    # final: find reg stored
    last=[l for l in m.group(2).split('\n') if re.match(r'\s*or\s',l)][-1]
    r=re.match(r'\s*or\s+(\$\d+)',last).group(1)
    res.setdefault(val[r],[]).append(name(allt[i]))
tgt=sys.argv[1] if len(sys.argv)>1 else '(((M|W)|(X|H))|Y)'
for k,v in res.items():
    if k==tgt: print('TARGET',k,len(v),v[:40])
print(len(res),'distinct outputs')
