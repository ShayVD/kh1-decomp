# rtry.py SRC FN DIR : apply replacement variants given in VARS file (python dict name->list of (old,new))
import sys,subprocess,re,os
src,fn,d,vf=sys.argv[1:5]
s0=open(src).read()
V=eval(open(vf).read())
for k,reps in V.items():
    s=s0
    for o,n in reps:
        if o not in s: print(k,'MISSING',o[:40]); break
        s=s.replace(o,n)
    else:
        open(d+'/.c2_r%d.c'%os.getpid()+'','w').write(s)
        r=subprocess.run(['python3','tools/checkfile.py',d+'/.c2_r%d.c'%os.getpid()+''],capture_output=True,text=True).stdout
        l=[x for x in r.split('\n') if x.startswith(fn)]
        print(k,l or r[-300:],flush=True)
        if l and 'MATCH' in l[0]: open(src+'.'+k+'.match','w').write(s)
import os
try: os.remove(d+'/.c2_r%d.c'%os.getpid()+'')
except: pass
