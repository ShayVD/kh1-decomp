#!/usr/bin/env python3
# autofix.py FILE : iteratively fix 'conflicting types' inside //@INS..//@END block
import sys,re,subprocess
f=sys.argv[1]
for it in range(30):
    r=subprocess.run(['python3','/home/claude/kh1-decomp/tools/checkfile.py',f],capture_output=True,text=True,cwd='/home/claude/kh1-decomp')
    out=r.stdout+r.stderr
    names=re.findall(r"conflicting types for `(\w+)'",out)+re.findall(r"redefinition of `(\w+)'",out)
    if not names: print(out[-3000:]); break
    s=open(f).read(); i=s.index('//@INS\n'); j=s.index('//@END\n')
    a,b,c=s[:i],s[i:j],s[j:]
    n=names[0]; done=False
    # typedef?
    m=re.search(r'^typedef [^;]*?\b'+n+r'\s*;\n',b,re.M|re.S)
    if m and re.search(r'\b'+n+r'\b\s*;',a):
        b=b.replace(m.group(0),'',1); done=True; print('drop typedef',n)
    if not done:
        m=re.search(r'^(extern\s+)?([\w\s\*]+?)\b'+n+r'\s*\(([^;]*)\)\s*;\n',b,re.M)
        if m: b=b.replace(m.group(0),'',1); done=True; print('drop proto',n)
    if not done:
        m=re.search(r'^extern ([^;\n]*?)\s*(\**)\s*\b'+n+r'\s*(\[[^\]]*\])?\s*;\n',b,re.M)
        if m:
            t=m.group(1)+(' '+m.group(2) if m.group(2) else '')
            if m.group(3): rep='#define %s ((%s *)%s)\n'%(n,t,n)
            else: rep='#define %s (*(%s *)&%s)\n'%(n,t,n)
            b=b.replace(m.group(0),rep,1); c=c.replace('//@END\n','#undef %s\n//@END\n'%n,1) if False else c
            b=b+'#undef %s\n'%n; done=True; print('redef',n)
        else:
            # multi-decl extern line like 'extern V4 A, B;'
            m=re.search(r'^extern ([\w ]+?) ([^;\n]*\b'+n+r'\b[^;\n]*);\n',b,re.M)
            if m:
                rest=[x.strip() for x in m.group(2).split(',') if x.strip()!=n]
                new=('extern %s %s;\n'%(m.group(1),', '.join(rest)) if rest else '')+'#define %s (*(%s *)&%s)\n'%(n,m.group(1),n)
                b=b.replace(m.group(0),new,1); b=b+'#undef %s\n'%n; done=True; print('redef-multi',n)
    if not done: print('cannot fix',n); print(out[-1500:]); break
    open(f,'w').write(a+b+c)
