#!/usr/bin/env python3
"""tools/ovl/port.py (session 141): SRC_OVL SRC_FUNC DST_OVL DST_FUNC src.c out.c
Map a matched C file of one overlay onto a same-shape function of another: pair the two asm
listings line by line, map every D_/func_ symbol (and lui-base + offset data addresses), rewrite."""
import os, re, subprocess, sys
R = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
so, sf, do, df, src, out = sys.argv[1:7]
def asm(o, f):
    r = subprocess.run(['python3', 'tools/kh1tool.py', 'asm', f], cwd=R,
                       env={**os.environ, 'KH1_OVL': o}, capture_output=True, text=True)
    L = []
    for l in r.stdout.splitlines():
        m = re.match(r'\s*/\* [0-9A-F]+ [0-9A-F]+ \*/\s+(\S+)\s*(.*)', l)
        if m: L.append((m.group(1), m.group(2)))
    return L
a, b = asm(so, sf), asm(do, df)
if len(a) != len(b):
    sys.exit(f'length differs {len(a)} {len(b)}')
mp = {sf: df}
hia, hib = {}, {}
def syms(s): return re.findall(r'\b(?:D|func|jtbl)_[0-9A-Fa-f]{8}\b', s)
for (ma, oa), (mb, ob) in zip(a, b):
    if ma != mb: sys.exit(f'mnemonic differs: {ma} {oa} / {mb} {ob}')
    for x, y in zip(syms(oa), syms(ob)):
        if mp.get(x, y) != y: print('conflict', x, mp[x], y)
        mp[x] = y
    if ma == 'lui':
        ra, va = oa.split(','); rb, vb = ob.split(',')
        if va.startswith('0x'): hia[ra] = int(va, 16); hib[rb] = int(vb, 16)
        else: hia.pop(ra, None); hib.pop(rb, None)
    m1 = re.search(r'(-?\d+)\((\$\w+)\)$', oa); m2 = re.search(r'(-?\d+)\((\$\w+)\)$', ob)
    if m1 and m2 and m1.group(2) in hia and m2.group(2) in hib:
        x = 'D_%08X' % ((hia[m1.group(2)] << 16) + int(m1.group(1)))
        y = 'D_%08X' % ((hib[m2.group(2)] << 16) + int(m2.group(1)))
        if mp.get(x, y) != y: print('conflict', x, mp[x], y)
        mp[x] = y
code = open(src).read()
code = re.sub(r'^/\*.*?\*/\n', '', code, count=1, flags=re.S)
code = code.replace('#include "ovl.h"\n', '')
def rep(m):
    t = m.group(0)
    for k in (t, t.upper().replace('FUNC_', 'func_').replace('D_', 'D_')):
        pass
    if t in mp: return mp[t]
    if t.startswith('D_') and ('D_' + t[2:].upper()) in mp: return mp['D_' + t[2:].upper()]
    if t.startswith('func_'):
        for k, v in mp.items():
            if k.lower() == t.lower(): return v
    return t
code = re.sub(r'\b(?:D|func)_[0-9A-Fa-f]{8}\b', rep, code)
# hi-based function addresses (lui 0xf3 + addiu -23520) are not mapped; report unmapped symbols
left = [s for s in set(re.findall(r'\b(?:D|func)_00F[2-9A-Fa-f][0-9A-Fa-f]{4}\b', code)) if s not in mp.values() and s.upper() not in [v.upper() for v in mp.values()]]
if left: print('unmapped:', sorted(left))
open(out, 'w').write(code)
