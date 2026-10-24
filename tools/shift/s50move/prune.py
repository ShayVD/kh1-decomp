#!/usr/bin/env python3
"""Drop a draft module's unused file-scope declarations (phase 4, session 50;
docs/modules.md "Session 50"): single-line externs and prototypes, and
typedef blocks whose names nothing else in the file uses, until stable.

  python3 -I tools/shift/s50move/prune.py FILE.c

Check the file again afterwards (tools/checkfile.py), and run fcheck.sh:
cover_check reads every file's sized externs."""
import re,sys
p=sys.argv[1]; t=open(p).read()
def strip(s): return re.sub(r'/\*.*?\*/|//[^\n]*','',s,flags=re.S)
while True:
    lines=t.split('\n'); changed=False
    # build blocks
    i=0; blocks=[]
    while i<len(lines):
        l=lines[i]
        if re.match(r'typedef (struct|union)\s*\w*\s*\{\s*$',l) or re.match(r'typedef (struct|union)\s*\w*\s*\{.*\}\s*\w+;',l):
            j=i
            if '}' not in l or not re.search(r'\}\s*\w+\s*(__attribute__.*)?;',l):
                while not re.match(r'\}\s*\w+.*;',lines[j]): j+=1
            blk='\n'.join(lines[i:j+1]); m=re.search(r'\}\s*(\w+)[^}]*;\s*(/\*.*\*/)?\s*$',strip(blk).rstrip()+'\n' if False else blk)
            names=re.findall(r'\}\s*(\w+)',re.sub(r'__attribute__\s*\(\(.*?\)\)\s*','',strip(blk)))  # } __attribute__((...)) NAME;
            blocks.append((i,j,names[-1:] ))
            i=j+1; continue
        s=strip(l).strip()
        if '__asm__' in s: pass  # an alias under a rename macro (`#define D_X D_X_<addr>`): kept
        elif l.startswith(('extern ','void ','s32 ','f32 ','u32 ','s8 ','u8 ','M2C_UNK ','int ')) and s.endswith(';') and '{' not in s:
            if '(' in s and not s.startswith('extern'):
                m=re.search(r'(\w+)\s*\(',s); names=[m.group(1)] if m else []
            else:
                s2=re.sub(r'\[[^\]]*\]','',s)
                s2=re.sub(r'\([^)]*\)','',s2)
                names=re.findall(r'(\w+)\s*(?:,|;)',s2)
            blocks.append((i,i,names))
        elif re.match(r'typedef [^{]*;',s):
            m=re.findall(r'(\w+)\s*(?:\[[^\]]*\])*\s*(?:__attribute__\(\(.*\)\))?\s*;',s)
            m2=re.search(r'\(\s*\*\s*(\w+)\s*\)',s)
            names=[m2.group(1)] if m2 else m[:1]
            blocks.append((i,i,names))
        i+=1
    full=strip(t)
    for (a,b,names) in reversed(blocks):
        if not names: continue
        blk=strip('\n'.join(lines[a:b+1]))
        rest=full.replace(blk,'',1)
        if all(not re.search(r'\b'+re.escape(n)+r'\b',rest) for n in names):
            del lines[a:b+1]; changed=True
            t='\n'.join(lines); full=strip(t)
    t='\n'.join(lines)
    if not changed: break
t=re.sub(r'\n{3,}','\n\n',t)
open(p,'w').write(t)
