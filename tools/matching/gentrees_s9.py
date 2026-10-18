import json, itertools, sys
# gentrees.py KEY LEAFSET-json  -> all trees over leaves
key=sys.argv[1]; L=json.loads(sys.argv[2])
def trees(ls):
    if len(ls)==1: yield ls[0]; return
    for i in range(1,len(ls)):
        for a in trees(ls[:i]):
            for b in trees(ls[i:]): yield (a,b)
def src(t): return '(%s)'%L[t] if isinstance(t,str) else '(%s | %s)'%(src(t[0]),src(t[1]))
def name(t): return t if isinstance(t,str) else '(%s|%s)'%(name(t[0]),name(t[1]))
for p in itertools.permutations(sorted(L)):
    for t in trees(list(p)):
        print(json.dumps({key:src(t),'#P':name(t)}))
