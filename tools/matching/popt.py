# popt.py FILE FUNC RO DIR [maxlen]: greedy permutation optimiser over runs of o->field statements
import sys,re,subprocess,difflib,itertools,os
f,func,ro,d=sys.argv[1:5]; maxlen=int(sys.argv[5]) if len(sys.argv)>5 else 5
tmp=f'/home/claude/kh1-decomp/{d}/.w6g2_po.c'
def score(src):
    open(tmp,'w').write(src)
    r=subprocess.run(['python3','tools/matching/wqb03_rr.py',ro,'try',func,'--file',tmp,'--out-dir',d,'--diff'],cwd='/home/claude/kh1-decomp',capture_output=True,text=True).stdout.splitlines()
    if not r: return 10**6
    if 'MATCH' in r[0] and 'mismatch' not in r[0]: return 0
    o=[];u=[]
    nm=lambda x: re.sub(r'0x1[0-9a-f]{5}$','L',x)
    for l in r[1:]:
        m=re.match(r'^([0-9a-f]{8}) (..) (.{40}) ?(.*)$',l)
        if not m: continue
        a,b=m.group(3).strip(),m.group(4).strip()
        if a: o.append(nm(a))
        if b: u.append(nm(b))
    if not o: return 10**6
    sm=difflib.SequenceMatcher(None,o,u,autojunk=False)
    return sum(max(i2-i1,j2-j1) for tg,i1,i2,j1,j2 in sm.get_opcodes() if tg!='equal')
L=open(f).read().split('\n')
st=re.compile(r'^(\s+)o->(\w+)( = (.*)|\+\+| &= (.*));$')
best=score('\n'.join(L)); print('start',best,flush=True)
i=0
while i<len(L):
    j=i
    while j<len(L) and st.match(L[j]) and (j==i or st.match(L[j]).group(1)==st.match(L[i]).group(1)): j+=1
    n=j-i
    if n>=2:
        run=L[i:j]; ok=True
        writes=[st.match(x).group(2) for x in run]
        if len(set(writes))<len(writes): ok=False
        for x in run:
            m=st.match(x); e=(m.group(4) or m.group(5) or '')
            for w in writes:
                if w!=m.group(2) and re.search(r'o->%s\b'%w,e): ok=False
        if ok and n<=maxlen:
            cands=[]
            for perm in itertools.permutations(run):
                if list(perm)==run: continue
                s=score('\n'.join(L[:i]+list(perm)+L[j:]))
                cands.append((s,perm))
            cands.sort(key=lambda x:x[0])
            if cands and cands[0][0]<best:
                best=cands[0][0]; L[i:j]=list(cands[0][1])
                open(f,'w').write('\n'.join(L))
                print('line',i+1,'->',best,flush=True)
        i=j
    else: i+=1
os.remove(tmp)
print('final',best)
