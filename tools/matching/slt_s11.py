import sys,re,collections
for f in sys.argv[1:]:
    c=collections.defaultdict(lambda:[0,0])
    for l in open(f):
        m=re.match(r'\s*(sw|lw)\s+\w+,(\d+)\(sp\)',l)
        if m: c[int(m.group(2))][m.group(1)=='lw']+=1
    print(f, ' '.join('%d:%d/%d'%(k,v[0],v[1]) for k,v in sorted(c.items()) if k<384))
