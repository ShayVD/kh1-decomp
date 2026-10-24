#!/usr/bin/env python3
"""Module move helper (phase 4, session 36; docs/modules.md "Session 36").

  python3 -I tools/shift/s36move/mod.py draft OUT.c func_X ...
      write a draft module: the bodies in the order given, and every
      declaration / include of their old files that they use (one line per
      source, with the file it came from; conflicting views stay side by
      side for you to merge).  Data-header includes go at the end.
  python3 -I tools/shift/s36move/mod.py remove func_X ...
      delete the definitions from their current files (out/gen/placements.tsv,
      so run `make` first), then the declarations and data-piece includes
      only they used; delete a file with no function left (EMPTY), and print
      comments that name a moved function (NOTE) so they can move too.

The draft is a starting point: merge the views, check it with
tools/checkfile.py, then `remove`, `make` and the float build.
"""
import sys, re, os
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent)); import ctop
ROOT = str(Path(__file__).resolve().parents[3]); os.chdir(ROOT)
def placements():
    src={}
    for l in open('out/gen/placements.tsv'):
        p=l.rstrip('\n').split('\t')
        if len(p)>3 and p[0]!='addr': src[p[1]]=p[3]
    return src
def strip_comments(t): return re.sub(r'/\*.*?\*/|//[^\n]*','',t,flags=re.S)
def idents(t): return set(re.findall(r'\b[A-Za-z_]\w*\b',strip_comments(t)))
KW=set('extern static const volatile unsigned signed int char short long float double void struct union enum typedef register inline __inline__ __attribute__ aligned mode TI DI SI s8 u8 s16 u16 s32 u32 s64 u64 f32 f64 u128 s128'.split())
def declared(t,k):
    """names a decl item declares."""
    s=strip_comments(t).strip()
    if k=='pp':
        m=re.match(r'#\s*define\s+(\w+)',s)
        if m: return {m.group(1)}
        m=re.match(r'#include\s+"data/pieces/(D_\w+?)(_s)?\.h"',s)
        if m: return {'@piece:'+m.group(1)}
        return set()
    if k!='decl': return set()
    s=re.sub(r'__attribute__\s*\(\(.*?\)\)','',s)
    if s.startswith('typedef'):
        body=re.sub(r'\{.*\}','',s,flags=re.S)
        m=re.findall(r'(\w+)\s*(?:\[[^\]]*\]\s*)*(?:\)\s*\([^)]*\))?\s*[;,]',body)
        n=set(m)
        m2=re.search(r'\(\s*\*\s*(\w+)\s*\)',body)
        if m2: n.add(m2.group(1))
        return n
    if re.match(r'(struct|union|enum)\s+\w+\s*\{',s) and s.rstrip(';').rstrip().endswith('}'):
        return {re.match(r'(?:struct|union|enum)\s+(\w+)',s).group(1)}
    s2=re.sub(r'\{.*\}','',s,flags=re.S)  # initializers / struct bodies
    s2=re.sub(r'=[^,;]*','',s2)
    names=set()
    # function prototype: name before first '(' not preceded by '(*'
    depth=0; cur=''
    parts=[]; 
    for ch in s2:
        if ch=='(': depth+=1
        if ch==')': depth-=1
        if ch==',' and depth==0: parts.append(cur); cur=''
        else: cur+=ch
    parts.append(cur)
    for p in parts:
        p=p.strip().rstrip(';')
        m=re.search(r'\(\s*\*+\s*(\w+)\s*\)',p)
        if m: names.add(m.group(1)); continue
        m=re.search(r'(\w+)\s*\(',p)
        if m and m.group(1) not in KW: names.add(m.group(1)); continue
        m=re.search(r'(\w+)\s*(\[[^\]]*\]\s*)*$',p)
        if m and m.group(1) not in KW: names.add(m.group(1))
    return names
GONE_FUNCS=set()
def remove(funcs):
    GONE_FUNCS.update(funcs)
    src=placements(); byfile={}
    for f in funcs: byfile.setdefault(src[f],set()).add(f)
    for path,fs in byfile.items():
        its=ctop.items(open(path).read())
        keep=[it for it in its if not (it[1]=='func' and it[2] in fs)]
        gone=set().union(*(idents(it[0]) for it in its if it[1]=='func' and it[2] in fs))|fs
        got={it[2] for it in its if it[1]=='func'} & fs
        for f in fs-got:  # a macro-generated definition: delete its MACRO(f, ...) line (session 50)
            for i,(t,k,n) in enumerate(keep):
                m=re.search(r'^[ \t]*(\w+)\(\s*'+f+r'\b.*\)[ \t]*\n',t,flags=re.M)
                if m and k!='func':
                    keep[i]=(t[:m.start()]+t[m.end():],k,n); gone|=idents(m.group(0)); got.add(f); break
        assert got==fs,(path,fs-got)
        prune(path,keep,gone)
def prune(path,its,gone):
    changed=True
    while changed:
        changed=False
        for i,(t,k,n) in enumerate(its):
            d=declared(t,k)
            if not d: continue
            if not ({x[7:] if x.startswith('@piece:') else x for x in d} & gone): continue
            used=set()
            for j,(t2,k2,n2) in enumerate(its):
                if j!=i and not (k2=='pp' and t2.strip().startswith('#include')): used|=idents(t2)
            pieces=[x for x in d if x.startswith('@piece:')]
            if pieces:
                m=re.search(r'#include\s+"([^"]+)"',t)
                htypes=set()
                for it in ctop.items(open('include/'+m.group(1)).read()):
                    if it[1]=='decl' and strip_comments(it[0]).strip().startswith(('typedef','struct','union')): htypes|=declared(it[0],'decl')
                if htypes & used: continue
                if pieces[0][7:] not in used: gone|=idents(t); its.pop(i); changed=True; break
                continue
            if not (d & used):
                gone|=idents(t); its.pop(i); changed=True; break
    for t,k,n in its:
        if k=='comment' and set(re.findall(r'func_[0-9a-f]{8}',t)) & GONE_FUNCS and ' are in ' not in t and ' is in ' not in t: print('NOTE',path,t.strip())
    if not any(k=='func' for t,k,n in its):
        print('EMPTY',path); os.remove(path); return
    out=''.join(t for t,k,n in its)
    out=re.sub(r'\n{3,}','\n\n',out)
    open(path,'w').write(out)
def draft(out,funcs):
    src=placements()
    bodies=[]; decls=[]; tops=[]; seen=set()
    files=[]
    for f in funcs:
        if src[f] not in files: files.append(src[f])
    allits={p:ctop.items(open(p).read()) for p in files}
    for f in funcs:
        for t,k,n in allits[src[f]]:
            if k=='func' and n==f: bodies.append(t.strip('\n')+'\n')
    used=set().union(*(idents(b) for b in bodies))
    # iterate: decls whose names are used (types pull in more names)
    chosen=[]
    changed=True
    while changed:
        changed=False
        for p in files:
            for t,k,n in allits[p]:
                if k not in ('decl','pp'): continue
                key=strip_comments(t).strip()
                if key in seen: continue
                d=declared(t,k)
                if k=='pp' and not d:
                    if key.startswith('#include') and key not in seen:
                        seen.add(key); chosen.append((p,t,k)); changed=True
                    continue
                if any(x.startswith('@piece:') and x[7:] in used for x in d) or (d & used):
                    seen.add(key); chosen.append((p,t,k)); used|=idents(t); changed=True
    defined={n for b in bodies for n in [re.findall(r'(\w+)\s*\(',b.split('{')[0])[0]]}
    hdr=[]; tail=[]
    for p,t,k in chosen:
        s=strip_comments(t).strip()
        if k=='pp' and 'data/pieces/' in s or re.match(r'#include\s+"data/data_',s): tail.append(s+'   /* '+p+' */')
        else: hdr.append(t.strip('\n') + ('' if k=='pp' else '   /* '+p+' */'))
    with open(out,'w') as o:
        o.write('/* TODO */\n')
        o.write('\n'.join(hdr)+'\n\n')
        o.write('\n'.join(bodies))
        o.write('\n'+'\n'.join(tail)+'\n')
if __name__=='__main__':
    if len(sys.argv) < 3 or sys.argv[1] not in ('draft', 'remove'): sys.exit(__doc__)
    if sys.argv[1]=='draft': draft(sys.argv[2],sys.argv[3:])
    elif sys.argv[1]=='remove': remove(sys.argv[2:])
