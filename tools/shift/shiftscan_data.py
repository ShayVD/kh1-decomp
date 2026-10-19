import struct, sys, collections, bisect
# NOTE: written for a one-off scan in session 12; input paths point at a scratch snapshot of out/ (copy out/ and edit the paths to rerun).
elf = open('/home/claude/kh1-decomp/SLPS_251.98','rb').read()
base_off, base = 0x80, 0x100000
def word(a): return struct.unpack_from('<I', elf, base_off + a - base)[0]
layout=[]
for l in open('/home/claude/kh1-decomp/layout.tsv'):
    if l[0] in '#a': continue
    p=l.split('\t'); layout.append((int(p[0],16), int(p[1],16)))
starts=[a for a,_ in layout]; startset=set(starts)
D0, D1 = 0x272c70, 0x494050
TEXT_END, BSS_END = 0x272c70, 0x675018
cnt=collections.Counter(); per64=collections.defaultdict(collections.Counter)
jt_runs=0; jt_words=0; run=[]
# known D_ symbols referenced by code
dsyms=set()
for l in open('/tmp/claude-0/s12/s12w15/ext_syms.tsv'):
    s,a,n=l.split('\t')
    if s.startswith('D_'): dsyms.add(int(a,16))
ptr_words=[]
def fn_of(v):
    i=bisect.bisect_right(starts, v)-1
    return layout[i] if i>=0 else None
for a in range(D0, D1, 4):
    v=word(a)
    k=None
    if 0x100000 <= v < TEXT_END:
        if v in startset: k='text:func-start'
        elif v%4==0:
            f=fn_of(v); k='text:inside-func' if f and v < f[1] else 'text:other'
        else: k='text:unaligned'
    elif TEXT_END <= v < D1:
        k='data/rodata'
    elif D1 <= v < BSS_END: k='bss'
    if k:
        cnt[k]+=1; per64[a>>16][k]+=1; ptr_words.append((a,v,k))
    # jump-table-like runs: consecutive words inside the same function
    if k=='text:inside-func':
        f=fn_of(v)
        if run and run[-1][1]==f and run[-1][0]==a-4: run.append((a,f))
        else:
            if len(run)>=2: jt_runs+=1; jt_words+=len(run)
            run=[(a,f)]
    else:
        if len(run)>=2: jt_runs+=1; jt_words+=len(run)
        run=[]
print('scanned bytes', hex(D1-D0))
for k,v in cnt.most_common(): print(f'  {k}: {v}')
print('total pointer-like words', sum(cnt.values()))
print('jump-table-like runs (>=2 consecutive words into one function):', jt_runs, 'words', jt_words)
print('per 64K block of data (block: counts):')
for b in sorted(per64): print(f'  0x{b:04x}0000', dict(per64[b]))
# where pointer targets in data/rodata/bss land relative to referenced D_ syms
tgt_known=sum(1 for a,v,k in ptr_words if v in dsyms)
print('pointer-like words whose target is a D_ symbol code references:', tgt_known)
# zero-filled tail? count zero words
z=sum(1 for a in range(D0,D1,4) if word(a)==0); print('zero words', z, 'of', (D1-D0)//4)
# refine data/rodata targets
def byte(a): return elf[base_off + a - base]
cat=collections.Counter()
for a,v,k in ptr_words:
    if k!='data/rodata': continue
    if v%4==0: cat['aligned']+=1
    elif byte(v-1)==0 and 32<=byte(v)<127: cat['unaligned-string-start']+=1
    else: cat['unaligned-other']+=1
print('data/rodata targets:', dict(cat))
# self-consistency: words whose target is itself a pointer-like word or zero region
# bss targets aligned?
print('bss aligned', sum(1 for a,v,k in ptr_words if k=='bss' and v%4==0), 'of', cnt['bss'])
# func-start pointers grouped into tables (runs of >=3 consecutive func-start words)
runs=0; inrun=0; prev=None; r=0
for a,v,k in ptr_words:
    if k=='text:func-start':
        if prev==a-4 or prev==a-8: r+=1
        else:
            if r>=3: runs+=1; inrun+=r
            r=1
        prev=a
if r>=3: runs+=1; inrun+=r
print('function-pointer tables (>=3 func-start words, stride<=8):', runs, 'words', inrun)
