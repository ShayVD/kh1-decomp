#!/usr/bin/env python3
"""Fold a file-local view of the text windows into TextWin (phase 4, session 38;
docs/modules.md "Session 38").

  python3 -I tools/shift/s38move/fold.py FILE.c TYPE [--write]

TYPE is a `typedef struct { ... } TYPE;` in FILE.c that describes a TextWin
(include/text/textwin.h) with padding.  Every field is matched by offset and
type to a TextWin member; `VAR->field` for each variable or parameter declared
`TYPE *VAR` becomes `VAR->member`, and TYPE becomes TextWin (the typedef goes,
the include is added).  A field with no member of the same type and offset is
printed and nothing is written.  `make` is the judge afterwards: a different
member path can change scheduling (func_001fea38's +0xd2).
"""
import re, sys
from pathlib import Path

SIZE = {'u8': 1, 's8': 1, 'char': 1, 'u16': 2, 's16': 2, 'u32': 4, 's32': 4,
        'f32': 4, 'int': 4, 'u64': 8, 's64': 8, 'ptr': 4}

# TextWin members: offset -> [(type, path)]
TW = {}
def tw(off, typ, path): TW.setdefault(off, []).append((typ, path))
for i, n in enumerate(['x0', 'x4', 'x8', 'prev', 'next', 'x14', 'x18', 'x1c', 'x20']):
    tw(4 * i, 'ptr' if n not in ('x4', 'x8') else 's32', n)
for o in range(0x24, 0x40, 4): tw(o, 's32', 'x%x' % o)
tw(0x40, 'u32', 'u40.v.x40'); tw(0x44, 'u32', 'u40.v.x44')
tw(0x48, 's32', 'u48.w.lo'); tw(0x4c, 's32', 'u48.w.hi'); tw(0x48, 'u64', 'u48.q')
for o in (0x50, 0x54, 0x58, 0x5c, 0x6c, 0x70, 0x7c, 0x80, 0x84, 0x88, 0x90, 0xac, 0xb0, 0xb4):
    tw(o, 's32', 'x%x' % o)
tw(0x8c, 's32', 'state')
tw(0x60, 'ptr', 'desc'); tw(0x64, 'ptr', 'x64'); tw(0x68, 'ptr', 'x68')
for o in (0x74, 0x78, 0x94, 0x98, 0x9c, 0xa0, 0xa4, 0xa8): tw(o, 'f32', 'x%x' % o)
for o in range(0xb8, 0xd0, 2): tw(o, 's16', 'x%x' % o)
for o in (0xd0, 0xd2, 0xd4, 0xd6): tw(o, 's16', 'ud0.s.x%x' % o)
tw(0xd0, 'u16', 'ud0.u.xd0'); tw(0xd2, 'u16', 'ud0.u.xd2'); tw(0xd0, 'u64', 'ud0.q')
tw(0xd8, 's16', 'xd8'); tw(0xda, 's16', 'xda'); tw(0xdc, 'u8[16]', 'xdc')


def cexpr(s):
    s = s.strip()
    if not re.fullmatch(r'[0-9a-fA-FxX\s+\-*()]+', s): raise ValueError(s)
    return eval(s, {})


def layout(body):
    off, out = 0, []
    for decl in body.split(';'):
        decl = re.sub(r'/\*.*?\*/', '', decl, flags=re.S).strip()
        if not decl: continue
        m = re.match(r'(?:struct\s+\w+\s*\*|(?:volatile\s+)?(\w+))\s*(.*)', decl, re.S)
        base = 'ptr' if decl.startswith('struct') else m.group(1)
        for d in m.group(2).split(','):
            d = d.strip()
            if ':' in d: raise ValueError('bitfield ' + d)
            ptr = d.startswith('*') or base == 'void' and d.startswith('*')
            name = re.match(r'\**\s*(\w+)', d).group(1)
            arr = re.findall(r'\[([^\]]*)\]', d)
            typ = 'ptr' if (ptr or base == 'ptr') else base
            if typ not in SIZE: raise ValueError('type ' + typ)
            sz = SIZE[typ]
            off = (off + sz - 1) // sz * sz
            n = 1
            for a in arr: n *= cexpr(a)
            out.append((off, typ + ('[%d]' % n if arr else ''), name))
            off += sz * n
    return out


def main():
    path, typ, write = sys.argv[1], sys.argv[2], '--write' in sys.argv
    src = Path(path).read_text()
    m = re.search(r'typedef struct\s*\{([^{}]*)\}\s*' + typ + r'\s*;[^\n]*\n', src, re.S)
    if not m: sys.exit('no typedef ' + typ)
    fmap, bad = {}, []
    for off, t, name in layout(m.group(1)):
        if name.startswith('pad'): continue
        cands = [p for tt, p in TW.get(off, []) if tt == t]
        if cands: fmap[name] = cands[0]
        else: bad.append('0x%x %s %s' % (off, t, name))
    if bad:
        print('NO MEMBER:', '; '.join(bad)); sys.exit(1)
    out = src[:m.start()] + src[m.end():]
    vars_ = set(re.findall(r'\b' + typ + r'\s*\*\s*(\w+)', out))
    n = 0
    for v in vars_:
        def rep(mm):
            nonlocal n
            f = mm.group(1)
            if f not in fmap: print('UNKNOWN', v, f); return mm.group(0)
            n += 1
            return v + '->' + fmap[f]
        out = re.sub(r'\b' + v + r'->(\w+)\b', rep, out)
    out = re.sub(r'\b' + typ + r'\b', 'TextWin', out)
    if '"text/textwin.h"' not in out:
        out = out.replace('#include "common.h"\n', '#include "common.h"\n#include "text/textwin.h"\n', 1)
    print('%s: %d accesses through %s' % (typ, n, ', '.join(sorted(vars_))))
    print('map:', ', '.join('%s=%s' % kv for kv in fmap.items() if kv[0] != kv[1]))
    if write: Path(path).write_text(out)

main()
