# osrch.py DUMP LO HI OVERRIDES(json {reg:"name"}) [ITERS] : minimal-change sched1 reorder of insns[LO:HI] to reach target allocation
import sys, json, random, math, os
sys.path.insert(0,os.path.dirname(os.path.abspath(__file__))); import la2
insns,refs,txt=la2.load(sys.argv[1]); LO=int(sys.argv[2]); HI=int(sys.argv[3]); ov={int(k):v for k,v in json.loads(sys.argv[4]).items()}
IT=int(sys.argv[5]) if len(sys.argv)>5 else 30000
Q=la2.sim(insns,refs)
target={}
for q in Q:
    for r in q['regs']:
        if LO*2-20 <= q['birth'] <= HI*2+40: target[r]=la2.NAMES.get(q.get('phys'))
target.update(ov)
pre=insns[LO:HI]
def regs_of(i):
    s=set(r for r,_ in i['sets']); u=set(r for r,_,_ in i['uses']); return s,u
def ismem(i): return '(mem' in i['txt'].split('(expr_list')[0]
import re
SZ={'QI':1,'HI':2,'SI':4,'DI':8,'TI':16,'SF':4}
def memaddr(i):
    t=i['txt'].split('(expr_list')[0]
    m=re.search(r'\(mem[/a-z]*:(\w+) \(plus:SI \(reg[/a-z]*:SI (\d+)\)\s*\(const_int (-?\d+)',t)
    if m: return (int(m.group(2)),int(m.group(3)),SZ.get(m.group(1),8))
    m=re.search(r'\(mem[/a-z]*:(\w+) \(reg[/a-z]*:SI (\d+)\)',t)
    if m: return (int(m.group(2)),0,SZ.get(m.group(1),8))
    return None
def isstore(i): return '(set (mem' in i['txt']
def dep(a,b):
    sa,ua=regs_of(a); sb,ub=regs_of(b)
    if sa&ub or sa&sb or ua&sb: return True
    if a['kind']!='insn' or b['kind']!='insn': return True
    if ismem(a) and ismem(b) and (isstore(a) or isstore(b)):
        ma=memaddr(a); mb=memaddr(b)
        if ma and mb and ma[0]==mb[0] and ma[0]!=None and (ma[1]+ma[2]<=mb[1] or mb[1]+mb[2]<=ma[1]): return False
        return True
    if 'volatile' in a['txt'] or 'unspec' in a['txt']: return True
    return False
ORD={id(x):k for k,x in enumerate(pre)}
MUST=set((id(x),id(y)) for x in pre for y in pre if ORD[id(x)]<ORD[id(y)] and dep(x,y))
def valid(seq):
    pos={id(x):k for k,x in enumerate(seq)}
    return all(pos[a]<pos[b] for a,b in MUST)
def score(seq,show=False):
    Q=la2.sim(insns[:LO]+seq+insns[HI:],refs); s=0
    for q in Q:
        for r in q['regs']:
            if r in target and la2.NAMES.get(q.get('phys'))!=target[r]:
                s+=1
                if show: print('  miss r%d %s want %s pri %d bd %d-%d'%(r,la2.NAMES.get(q.get('phys')),target[r],q['pri'],q['birth'],q['death']))
    return s
print('score now',score(pre,True)); sys.stdout.flush()
base=[id(x) for x in pre]
def kd(seq):
    p={id(x):k for k,x in enumerate(seq)}; n=0
    for i in range(len(base)):
        for j in range(i+1,len(base)):
            if p[base[i]]>p[base[j]]: n+=1
    return n
def obj(seq): return score(seq)*30+kd(seq)
random.seed(int(os.environ.get('SEED','3'))); best=(9e9,None)
P=len(pre)
for restart in range(int(os.environ.get('R','2'))):
    cur=list(pre); cs=obj(cur)
    for it in range(IT):
        Tm=max(0.3,20*(1-it/(IT*0.8)))
        n=list(cur); a=random.randrange(P); b=max(0,min(P-1,a+random.randint(-12,12)))
        x=n.pop(a); n.insert(b,x)
        if not valid(n): continue
        sc=obj(n)
        if sc<=cs or random.random()<math.exp((cs-sc)/Tm): cur,cs=n,sc
        if cs<best[0]: best=(cs,list(cur))
    print(restart,best[0],score(best[1]),kd(best[1])); sys.stdout.flush()
seq=best[1]
print('final score',score(seq,True))
# report moves: insns whose relative order changed
p={id(x):k for k,x in enumerate(seq)}
for k,x in enumerate(seq):
    o=ORD[id(x)]
    if o!=k: print('pos %d (was %d) uid %d %s'%(k+LO,o+LO,x['uid'],' '.join(x['txt'].split('\n')[0:2])[:110].replace('  ','')))
