# lap.py LA_TRACE : local-alloc qtys sorted by priority
import sys,re,math
L=[l for l in open(sys.argv[1]) if l.startswith('LQ')]
out=[]
for l in L:
    d=dict(re.findall(r'(\w+)=(-?\d+)',l)); d={k:int(v) for k,v in d.items()}
    n=d['refs']; pri=int((int(math.log2(n)) if n>0 else 0)*n*1/(d['death']-d['birth'])*10000) if d['death']>d['birth'] else 0
    p=d['phys']; pn=('f%d'%(p-32)) if p>=32 else ('r%d'%p if p>=0 else '-')
    out.append((pri,d['q'],d['reg'],n,d['birth'],d['death'],d['calls'],pn,d['sugg'],d['copysugg']))
for x in sorted(out,key=lambda x:(-x[0],x[1])): print('pri %5d q%-2d r%-4d refs %-2d [%3d,%3d] calls %-2d -> %-4s sugg %d/%d'%x)
