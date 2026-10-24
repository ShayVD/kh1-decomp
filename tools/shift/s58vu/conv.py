"""Switch game files to include/platform/vu.h (phase 4, session 58;
docs/portability.md rule 2 "Session 58").

  python3 -I tools/shift/s58vu/conv.py FILE..

For every libvu0 routine in functions.tsv (by its sceVu0 name, its func_
address, or a file's own `_dNN` alias of either): drops the file's own
prototypes of it (any indentation, `__asm__("..")` labels included) and its
`#define OLD ((T (*)(..)) OLD)` / `#undef OLD` cast views, renames the calls
`OLD(` to the PlatVu0 macro, renames other uses (function pointers) to the
sceVu0 name, and includes "platform/vu.h" after "common.h" (or the first
include).  Prints LEFT for anything it could not place.  `make` is the
judge."""
import re, sys, pathlib

root = pathlib.Path(__file__).resolve().parents[3]
names = {}
for l in (root / 'functions.tsv').read_text().split('\n'):
    f = l.split('\t')
    if len(f) < 2 or not re.match(r'_?sceV(pu|u)0', f[0]) or f[0].startswith('_'): continue
    plat = 'PlatVpu0' + f[0][len('sceVpu0'):] if f[0].startswith('sceVpu0') else 'PlatVu0' + f[0][len('sceVu0'):]
    names[f[0]] = (f[0], plat)
    names['func_' + f[1]] = (f[0], plat)
alt = '|'.join(sorted(names, key=len, reverse=True))
OLD = r'(?P<old>(?:%s)(?:_d\d+)?)\b' % alt
KW = {'return', 'else', 'do', 'case', 'goto', 'if', 'while', 'for', 'switch', 'sizeof'}
decl_re = re.compile(r'^\s*(?:extern\s+)?(?:static\s+)?(?P<type>[A-Za-z_]\w*)[\s\*]+' + OLD + r'\s*\(')
cast_re = re.compile(r'^\s*#\s*(define|undef)\s+' + OLD)

arity = {m.group(1): len(m.group(2).split(',')) if m.group(2).strip() else 0
         for m in re.finditer(r'^#define (PlatVp?u0\w+)\(([^)]*)\)', (root / 'include/platform/vu.h').read_text(), re.M)}

def calls(txt):
    # (macro, argument count, line) of every PlatVu0 call in txt
    for m in re.finditer(r'\b(PlatVp?u0\w+)\(', txt):
        depth, n, i, empty = 1, 1, m.end(), True
        while depth and i < len(txt):
            c = txt[i]
            if c in '([': depth += 1
            elif c in ')]': depth -= 1
            elif c == ',' and depth == 1: n += 1
            if depth and not c.isspace(): empty = False
            i += 1
        yield m.group(1), 0 if empty else n, txt.count('\n', 0, m.start()) + 1

def base(old):
    return names[re.sub(r'_d\d+$', '', old)]

for f in sys.argv[1:]:
    p = pathlib.Path(f); lines = p.read_text().split('\n'); out = []; i = 0
    while i < len(lines):
        l = lines[i]
        m = decl_re.match(l)
        if m and m.group('type') not in KW:
            # a prototype: up to its ';' (may span lines)
            j = i; text = l
            while ';' not in text and j + 1 < len(lines):
                j += 1; text += '\n' + lines[j]
            body = text[m.end():]
            if '{' not in body and re.search(r'\)\s*(__asm__\s*\("[^"]*"\)\s*)?;\s*(/\*.*\*/)?\s*$', text):
                i = j + 1; continue
        if cast_re.match(l):
            i += 1; continue
        l = re.sub(OLD + r'\s*\(', lambda m: base(m.group('old'))[1] + '(', l)
        l = re.sub(OLD, lambda m: base(m.group('old'))[0], l) if not l.lstrip().startswith(('/*', '*')) else l
        out.append(l); i += 1
    txt = '\n'.join(out)
    inc = '#include "platform/vu.h"'
    if inc not in txt:
        m = re.search(r'^#include "common.h"\n', txt, re.M) or re.search(r'^#include .*\n', txt, re.M)
        if m: txt = txt[:m.end()] + inc + '\n' + txt[m.end():]
        else: txt = inc + '\n' + txt
    p.write_text(txt)
    for mac, n, line in calls(txt):
        if mac in arity and n != arity[mac]:
            print('ARITY %s:%d %s takes %d, given %d' % (f, line, mac, arity[mac], n))
    for l in txt.split('\n'):
        if re.search(r'\bsceV(pu|u)0\w+\b', l) and not re.search(r'\bPlatV', l) and 'include' not in l:
            print('LEFT', f, l.strip())
