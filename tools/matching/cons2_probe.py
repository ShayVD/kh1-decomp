#!/usr/bin/env python3
"""probe.py FILE CALLER [DIR]: for each callee prototype `RET func_X(ARGS);` in FILE,
insert a stub definition of it right above CALLER's definition and run checkfile;
report which callee (if any) changes the caller's word count / matches."""
import sys, re, subprocess, os
f, caller = sys.argv[1], sys.argv[2]
d = sys.argv[3] if len(sys.argv) > 3 else os.path.dirname(os.path.abspath(f))
s = open(f).read()
m = re.search(r'^[^\n;]*\b' + caller + r'\s*\([^;{]*\)\s*\{', s, re.M)
a = m.start()
body = s[a:]
callees = set(re.findall(r'\b(func_[0-9a-f]{8})\s*\(', body)) - {caller}
def run(t):
    p = os.path.join(d, '.c2_probe.c'); open(p, 'w').write(t)
    r = subprocess.run(['python3', 'tools/checkfile.py', p], capture_output=True, text=True, cwd='/home/claude/kh1-decomp').stdout
    os.remove(p)
    for l in r.splitlines():
        if l.startswith(caller[5:]): return l
    return r.strip().splitlines()[-1:] 
print('base', run(s))
for c in sorted(callees):
    hdrs = ''.join(open(h).read() for h in re.findall(r'#include "(/[^"]+)"', s))
    pm = re.search(r'^\s*(?:extern\s+)?([A-Za-z_][\w\s\*]*?)\b' + c + r'\s*\(([^;{]*)\)\s*;', s, re.M) or re.search(r'^\s*(?:extern\s+)?([A-Za-z_][\w\s\*]*?)\b' + c + r'\s*\(([^;{]*)\)\s*;', hdrs, re.M)
    if not pm: print(c, 'no prototype'); continue
    ret, args = pm.group(1).strip(), pm.group(2).strip()
    if args in ('', 'void'): params = 'void'
    else:
        ps = [x.strip() for x in args.split(',')]
        if ps[-1] == '...': print(c, 'varargs'); continue
        def nm(p, i):
            if re.search(r'\(\s*\*', p): return p.replace('(*', '(*p%d' % i)
            toks = p.replace('*', ' * ').split()
            if len(toks) >= 2 and re.match(r'^[A-Za-z_]\w*$', toks[-1]) and toks[-1] not in ('int','char','long','short','unsigned','signed','float','double') and toks[-2] != 'struct':
                base = ' '.join(toks[:-1])
                if base not in ('unsigned', 'signed', 'const'): return p
            return p + ' p%d' % i
        params = ', '.join(nm(p, i) for i, p in enumerate(ps))
    stub = ret + ' ' + c + '(' + params + ') { ' + ('' if ret == 'void' else 'return 0; ') + '}\n'
    print(c, run(s[:a] + stub + s[a:]))
