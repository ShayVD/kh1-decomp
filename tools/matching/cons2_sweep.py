#!/usr/bin/env python3
# sweep.py FILE... : for each near-miss, find func, best mode, then try proto deletion & s32->void* flips
import sys,re,subprocess,os,glob,json
ROOT='/home/claude/kh1-decomp'
MODES=['src/hand','src/hand/nostrict','src/hand/nofill','src/hand/nostrict_nofill']
def check(code,d,fn):
    p=os.path.join(ROOT,d,'.c2_sw.c'); open(p,'w').write(code)
    r=subprocess.run(['python3','tools/checkfile.py',p,'-v'],capture_output=True,text=True,cwd=ROOT,timeout=120).stdout
    os.remove(p)
    lines=r.split('\n'); res=None; diffs=[]
    for i,l in enumerate(lines):
        if l.startswith(fn.replace('func_','')+' '):
            if 'MATCH' in l and 'FAIL' not in l: return 0,0,[]
            m=re.search(r'(\d+) vs (\d+), (\d+) words',l)
            if not m: return 9999,9999,[]
            j=i+1
            while j<len(lines) and lines[j].startswith('  '):
                diffs.append(lines[j].split()); j+=1
            n=int(m.group(3)); same=m.group(1)==m.group(2)
            # rodata-ish: ours lui 0x4000 or ours low16==0 and same opcode/regs
            real=0
            for dd in diffs:
                if len(dd)<5: real+=1; continue
                o,g=int(dd[2],16),int(dd[4],16)
                if (o>>16)==(g>>16) and (o&0xffff)==0 and (g>>26) in (0x0f,0x23,0x37,0x31,0x09,0x35,0x27,0x21,0x24,0x25,0x20): continue
                if (o>>26)==0x0f and (o&0xffff)==0x4000 and (g>>26)==0x0f: continue
                if (o>>21)==(g>>21) and (o>>26)==0x0f: continue
                real+=1
            return (n if not same else n), (real if same else 9999), diffs
    return 9999,9999,[]
def fname(path,code):
    base=os.path.basename(path)[5:].split('.')[0].split('_')[0]
    names=re.findall(r'^\w[\w \t\*]*?\b(func_[0-9a-f]{8})[ \t]*\([^;\n]*$',code,re.M)
    for n in names:
        if n.endswith(base.lower()) or n.endswith(base): return n
    return names[-1] if names else None
def done(fn):
    r=subprocess.run(['grep','-rlE',r'^[a-zA-Z].*\b'+fn+r'\s*\([^;]*$','src/hand','--include=*.c'],capture_output=True,text=True,cwd=ROOT).stdout.split()
    return [x for x in r if not os.path.basename(x).startswith('.')]
def variants(code):
    V=[]
    protos=[l for l in code.split('\n') if re.match(r'^[\w\s\*]+\b(func_\w+|sce\w+)\s*\([^)]*\)\s*;\s*$',l)]
    for l in protos: V.append(('np:'+re.search(r'(func_\w+|sce\w+)\s*\(',l).group(1),code.replace(l+'\n','',1)))
    if len(protos)>1:
        c=code
        for l in protos:
            if 'f32' not in l and 'f64' not in l and 'double' not in l: c=c.replace(l+'\n','',1)
        V.append(('np:allint',c))
    # struct field flips s32 -> void*
    for m in re.finditer(r'\b(s32|u32|int)(\s+)(x[0-9a-f]+|[a-z]\w*)\s*([;,])',code):
        a,b=m.span()
        if code.rfind('typedef',0,a)<0: continue
        # only within typedef struct bodies: ensure there's an unclosed '{' before
        pre=code[:a]; 
        if pre.count('{')-pre.count('}')<=0: continue
        if pre.rfind('typedef')<pre.rfind('\n}') and pre.rfind('\n}')>pre.rfind('typedef'): pass
        new=code[:a]+'void *'+m.group(3)+m.group(4)+code[b:]
        if m.group(4)==',':
            # s32 a, b; -> split: only flip first by making it own decl
            new=code[:a]+'void *'+m.group(3)+'; '+m.group(1)+code[b:]
        V.append(('vp:'+m.group(3)+'@'+str(a),new))
    return V
out=[]
for path in sys.argv[1:]:
    code=open(path).read()
    if 'common.h' not in code and '#include' not in code: code='#include "common.h"\n'+code
    fn=fname(path,code)
    if not fn: print(path,'NOFUNC',flush=True); continue
    dn=done(fn)
    if dn: print(path,fn,'ALREADY',dn,flush=True); continue
    best=None
    for d in MODES:
        n,real,_=check(code,d,fn)
        if best is None or (real,n)<(best[1],best[2]): best=(d,real,n)
    d,real,n=best
    print(path,fn,'base',d,n,'real',real,flush=True)
    if real==0: print('  BASE-RODATA-ONLY',flush=True); continue
    if n>=200: continue
    for k,c in variants(code):
        try: nn,rr,_=check(c,d,fn)
        except Exception as e: continue
        if (rr,nn)<(real,n) or nn==0:
            print('  ',k,nn,'real',rr,flush=True)
            if rr==0:
                open('/tmp/claude-0/s/cons2/sw_%s.c'%fn,'w').write(c); print('  ** MATCH',k,d,flush=True)
