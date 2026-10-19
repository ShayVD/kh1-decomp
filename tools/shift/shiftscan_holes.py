import subprocess,collections
# NOTE: written for a one-off scan in session 12; input paths point at a scratch snapshot of out/ (copy out/ and edit the paths to rerun).
exec(open('/tmp/claude-0/s12/s12w15/bin/shiftscan_data.py').read().split("print('scanned")[0])
holes=[]
for l in open('/tmp/claude-0/s12/s12w15/snap/gen/rodata.tsv').read().splitlines()[1:]:
    a,n,o=l.split('\t')
    out=subprocess.run(['mips-linux-gnu-readelf','-SW','/tmp/claude-0/s12/s12w15/snap/'+o.replace('out/','',1)],capture_output=True,text=True).stdout
    for x in out.splitlines():
        p=x.replace('[ ','[').split()
        if len(p)>6 and p[1]==n: holes.append((int(a,16),int(a,16)+int(p[5],16)))
def inhole(a): return any(s<=a<e for s,e in holes)
c=collections.Counter(k for a,v,k in ptr_words if not inhole(a))
print('blob-only pointer-like words (compiled rodata holes removed):', dict(c), sum(c.values()))
placed=set(int(l.split('\t')[0],16) for l in open('/tmp/claude-0/s12/s12w15/snap/gen/placements.tsv').read().splitlines()[1:])
asmsrc=set(int(l.split('\t')[0],16) for l in open('/tmp/claude-0/s12/s12w15/snap/gen/placements.tsv').read().splitlines()[1:] if l.split('\t')[3].endswith('.s'))
cc=collections.Counter(); tg=collections.Counter()
for a,v,k in ptr_words:
    if k!='text:inside-func' or inhole(a): continue
    f=fn_of(v)[0]
    kind='asm' if f in asmsrc else 'C' if f in placed else 'unplaced'
    cc[kind]+=1; tg[(kind,hex(f))]+=1
print(dict(cc)); print(tg.most_common(15))
