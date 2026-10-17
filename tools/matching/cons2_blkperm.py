#!/usr/bin/env python3
# blkperm.py SRC FUNCHEX DIR N : randomly permute statements between /*P*/ and /*Q*/
import sys,random,subprocess,re,os
src,fn,d,N=sys.argv[1],sys.argv[2],sys.argv[3],int(sys.argv[4])
s=open(src).read()
pre,rest=s.split('/*P*/\n',1); blk,post=rest.split('/*Q*/\n',1)
st=[l for l in blk.split('\n') if l.strip()]
out=d+'/.c2_bp_%d.c'%os.getpid()+''; best=None
random.seed(int(sys.argv[5]) if len(sys.argv)>5 else 1)
def run(order):
    open(out,'w').write(pre+'\n'.join(order)+'\n'+post)
    r=subprocess.run(['python3','/home/claude/kh1-decomp/tools/checkfile.py',out],capture_output=True,text=True,cwd='/home/claude/kh1-decomp').stdout
    for l in r.split('\n'):
        if l.startswith(fn):
            if 'MATCH' in l: return 0
            m=re.search(r'(\d+) words',l); return int(m.group(1)) if m else 9999
    return 9999
bw=run(st); print('base',bw)
cur=st[:]; cw=bw
for i in range(N):
    o=cur[:]
    for _ in range(random.randint(1,3)):
        a,b=random.randrange(len(o)),random.randrange(len(o)); o[a],o[b]=o[b],o[a]
    w=run(o)
    if w<=cw:
        cur,cw=o,w
        if w<bw: bw=w; print(i,w,flush=True); open(src+'.best','w').write(pre+'/*P*/\n'+'\n'.join(o)+'\n/*Q*/\n'+post)
        if w==0: break
import os; os.remove(out); print('final',bw)
