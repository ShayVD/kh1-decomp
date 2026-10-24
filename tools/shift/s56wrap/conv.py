"""Switch game files to a Plat wrapper header (phase 4, session 56;
docs/portability.md rule 2 "Session 56").

  python3 -I tools/shift/s56wrap/conv.py platform/gs.h sceGsSyncPath=PlatGsSyncPath,func_00265bc0=PlatGsSyncPath FILE..

In each FILE: drops the file's own top-level prototypes of every OLD name and
its `#define OLD ((T (*)(..)) OLD)` / `#undef OLD` cast views, renames the
calls `OLD(` to `NEW(`, and includes the header after "common.h" (or the
first include).  Prints LEFT for an OLD name still in the text (comments,
function pointers): look at those by hand.  `make` is the judge; a call whose
result is stored may need the variable retyped (docs/matching-tips.md
"Session 56")."""
import re, sys, pathlib
hdr, pairs, files = sys.argv[1], sys.argv[2], sys.argv[3:]
pairs = [p.split('=') for p in pairs.split(',')]
for f in files:
    p = pathlib.Path(f); lines = p.read_text().split('\n'); out = []
    for l in lines:
        s = l.strip()
        skip = False
        for old, new in pairs:
            # prototype at top level, cast define, undef
            if re.match(r'^(extern\s+)?[A-Za-z_][\w\s\*]*\b%s\s*\([^;{]*\)\s*;\s*(/\*.*\*/)?$' % old, s) and not l.startswith(' '):
                skip = True
            if re.match(r'^#\s*(define|undef)\s+%s\b' % old, s):
                skip = True
        if skip: continue
        for old, new in pairs:
            l = re.sub(r'\b%s\s*\(' % old, new + '(', l)
        out.append(l)
    txt = '\n'.join(out)
    inc = '#include "%s"' % hdr
    if inc not in txt:
        m = re.search(r'^#include "common.h"\n', txt, re.M) or re.search(r'^#include .*\n', txt, re.M)
        if m: txt = txt[:m.end()] + inc + '\n' + txt[m.end():]
        else: txt = inc + '\n' + txt
    p.write_text(txt)
    for old, _ in pairs:
        if re.search(r'\b%s\b' % old, txt): print("LEFT", f, old)
