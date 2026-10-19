# la2.py: local-alloc simulator for one-block (or first-block) functions from an ee-gcc 2.96 .lreg dump.
# Model: qty per local pseudo (one death); tie output with a dying same-size direct operand; hard-reg lives and
# call clobbers; copy suggestions; priority floor_log2(refs)*refs*size*10000/(death-birth); closed-interval conflicts.
import re, math, sys
def tok(s):
    i=0; n=len(s)
    while i<n:
        c=s[i]
        if c in '()[]': yield c; i+=1
        elif c.isspace(): i+=1
        elif c=='"':
            j=s.index('"',i+1); yield s[i:j+1]; i=j+1
        else:
            j=i
            while j<n and s[j] not in '()[] \t\n': j+=1
            yield s[i:j]; i=j
def parse(s):
    st=[[]]
    for t in tok(s):
        if t in '([': st.append([])
        elif t in ')]':
            x=st.pop(); st[-1].append(x)
        else: st[-1].append(t)
    return st[0]
HARD=80
SIZES={'QI':1,'HI':2,'SI':4,'DI':8,'TI':16,'SF':4,'DF':8}
def isreg(x): return isinstance(x,list) and x and isinstance(x[0],str) and x[0].split(':')[0].split('/')[0]=='reg'
def regno(x): return int(x[1])
def mode(x): return x[0].split(':')[1] if ':' in x[0] else 'VOID'
def head(x): return x[0].split(':')[0].split('/')[0] if isinstance(x,list) and x and isinstance(x[0],str) else None
def allregs(x, inmem=False, out=None):
    if out is None: out=[]
    if isreg(x): out.append((regno(x),inmem,mode(x))); return out
    if isinstance(x,list):
        h=head(x); m=inmem or h=='mem'
        for y in x[1:]: allregs(y,m,out)
    return out
def load(path):
    txt=open(path).read()
    chunks=re.split(r'\n(?=\((?:insn|call_insn|jump_insn|note|code_label|barrier)[/a-z]* )', txt)
    insns=[]
    for c in chunks:
        m=re.match(r'\((insn|call_insn|jump_insn|code_label)[/a-z]* (\d+)',c)
        if not m: continue
        if m.group(1)=='code_label': insns.append(dict(kind='label',uid=int(m.group(2)))); continue
        t=parse(c)[0]
        pat=t[4]
        notes=t[-1] if len(t)>7 else []
        dead=set(); unused=set()
        def walk(n):
            if isinstance(n,list) and n:
                h=n[0] if isinstance(n[0],str) else ''
                if h.startswith('expr_list:REG_DEAD') and isreg(n[1]): dead.add(regno(n[1]))
                if h.startswith('expr_list:REG_UNUSED') and isreg(n[1]): unused.add(regno(n[1]))
                for y in n[1:]: walk(y)
        walk(notes)
        sets=[]; uses=[]
        def dopat(p):
            h=head(p)
            if h=='set':
                d,s=p[1],p[2]
                if isreg(d) or (head(d)=='subreg' and isreg(d[1])):
                    dr=d if isreg(d) else d[1]; sets.append((regno(dr),mode(dr)))
                else: uses.extend(allregs(d))
                uses.extend(allregs(s))
            elif h=='parallel':
                for q in p[1]: dopat(q)
            elif h=='clobber':
                if isreg(p[1]): sets.append((regno(p[1]),mode(p[1])))
            else: uses.extend(allregs(p))
        dopat(pat)
        direct=[]
        if head(pat)=='set':
            s=pat[2]
            cand=[s] if (isreg(s) or head(s)=='subreg') else (s[1:] if isinstance(s,list) else [])
            for o in cand:
                if head(o)=='subreg' and isreg(o[1]): direct.append((regno(o[1]),mode(o))); continue
                if isreg(o): direct.append((regno(o),mode(o)))
        fu=[]
        if m.group(1)=='call_insn':
            fu=[regno(y[1]) for y in (t[-2] if isinstance(t[-2],list) else []) if isinstance(y,list) and head(y)=='expr_list' for y in [y[1]] if head(y)=='use' and isreg(y[1])] if False else []
            fu=[int(x) for x in re.findall(r'\(use \(reg:\w+ (\d+)',c)]
        insns.append(dict(kind=m.group(1),uid=int(m.group(2)),sets=sets,uses=[u for u in uses]+[(r,False,'SI') for r in fu],dead=dead,unused=unused,direct=direct,txt=c))
    refs={}; 
    for m in re.finditer(r'Register (\d+) used (\d+) times',txt): refs[int(m.group(1))]=int(m.group(2))
    return insns, refs, txt
NAMES={2:'v0',3:'v1',4:'a0',5:'a1',6:'a2',7:'a3',8:'t0',9:'t1',10:'t2',11:'t3',12:'t4',13:'t5',14:'t6',15:'t7',24:'t8',25:'t9',16:'s0',17:'s1',18:'s2',19:'s3',20:'s4',21:'s5',22:'s6',23:'s7',30:'s8',31:'ra'}
ORDER=[2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,30]
SAVED=[16,17,18,19,20,21,22,23,30]
CLOB=set(ORDER)|{31}
FORDER=list(range(32,52))
FSAVED=[52,54,56,58,60,62]
for i in range(32,64): NAMES[i]='f%d'%(i-32)
def sim(seq, refs, localregs=None, seed_hard=True):
    # seq: list of insns of ONE block in order
    occ={}
    for n,ins in enumerate(seq,1):
        for r,_ in ins['sets']: occ.setdefault(r,[]).append(n)
        for r,_,_ in ins['uses']: occ.setdefault(r,[]).append(n)
    qof={}; Q=[]; hard={}  # hard reg -> list of intervals
    hlive={}
    calls=[]
    def hbusy(r,a,b): hard.setdefault(r,[]).append((a,b))
    for n,ins in enumerate(seq,1):
        if ins['kind']=='call_insn': calls.append(2*n)
        # uses
        for r,inm,md in ins['uses']:
            if r<HARD:
                if r in hlive and (r in ins['dead'] or ins['kind']=='call_insn'): hbusy(r,hlive.pop(r),2*n)
                continue
            if r in qof: Q[qof[r]]['death']=max(Q[qof[r]]['death'],2*n)
        for r,md in ins['sets']:
            if r<HARD:
                if r in ins['unused']: hbusy(r,2*n,2*n+1)
                else:
                    if r in hlive: hbusy(r,hlive.pop(r),2*n)
                    if ins['kind']!='call_insn': hlive[r]=2*n
                    elif r==2:
                        for later in seq[n:]:
                            if any(u[0]==2 for u in later['uses']): hlive[r]=2*n; break
                            if any(x[0]==2 for x in later['sets']) or later['kind']=='call_insn': break
                continue
            if localregs is not None and r not in localregs: continue
            if r in qof: continue
            tied=None
            for u,um in ins['direct']:
                if u>=HARD and u in ins['dead'] and u in qof and SIZES.get(um,4)==SIZES.get(md,4) and ((um in ('SF','DF'))==(md in ('SF','DF'))):
                    q=Q[qof[u]]
                    if q['death']<=2*n: tied=qof[u]; break
            if tied is not None:
                qof[r]=tied; Q[tied]['refs']+=refs.get(r,2); Q[tied]['regs'].append(r)
            else:
                qof[r]=len(Q); Q.append(dict(regs=[r],refs=refs.get(r,2),birth=2*n,death=2*n+1,mode=md,sugg=[]))
        # suggestions: hard dest with dying direct pseudo operand, or pseudo dest with dying direct hard operand
        if len(ins['sets'])==1:
            d,dm=ins['sets'][0]
            for u,um in ins['direct']:
                if u not in ins['dead']: continue
                if d<64 and u>=HARD and u in qof: Q[qof[u]]['sugg'].append(d); break
                if u<HARD and d>=HARD and d in qof: Q[qof[d]]['sugg'].append(u); break
        if ins['kind']=='call_insn':
            for r in CLOB: pass
    for r,a in hlive.items(): hbusy(r,a,10**9)
    NI=len(seq)
    for q in Q:
        size=2 if q['mode']=='TI' else 1
        q['pri']=int(math.floor(math.log2(max(q['refs'],1)))*q['refs']*size*10000/max(q['death']-q['birth'],1))
        q['cross']=any(q['birth']<c<q['death'] for c in calls)
    idx=sorted(range(len(Q)),key=lambda i:(-Q[i]['pri'],i))
    busy={r:list(v) for r,v in hard.items()}
    def free(r,b,d): return all(not(b<d2 and b2<d) for b2,d2 in busy.get(r,[]))
    def ffr(q,b,d,just):
        fp=q['mode'] in ('SF','DF')
        pool=(FSAVED if q['cross'] else FORDER) if fp else (SAVED if q['cross'] else ORDER)
        sug=[s for s in q['sugg'] if s in pool]
        if just: cand=sug
        else: cand=sug+pool
        for r in cand:
            if free(r,b,d):
                busy.setdefault(r,[]).append((b,d)); return r
        return None
    for q in Q:
        if q['mode'] in ('CC','CCFP'): q['phys']='fp'
    for i in idx:
        q=Q[i]
        if q.get('phys')=='fp': continue
        if q['sugg']:
            q['phys']=ffr(q,q['birth'],q['death'],True)
    for i in idx:
        q=Q[i]
        if q.get('phys') is not None: continue
        b,d=q['birth'],q['death']
        fb=max(0,b-2+b%2); fd=min(NI*2+1,d+2-d%2)
        r=None
        if fb<b or d<fd: r=ffr(q,fb,fd,False)
        if r is None: r=ffr(q,b,d,False)
        q['phys']=r
    return Q
if __name__=='__main__':
    insns,refs,txt=load(sys.argv[1])
    Q=sim(insns,refs)
    for i,q in enumerate(Q): print(i,q['regs'],q['refs'],q['pri'],NAMES.get(q.get('phys'),q.get('phys')),q['birth'],q['death'])
