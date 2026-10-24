"""padmask.py for the pad state held in a local (phase 4, session 58).

  python3 -I tools/shift/s57pad/padvar.py FILE..

After `V = D_00425BC8->xN` (or `T *V = D_00425BC8`), rewrites `V & 0xM`
(or `V->xN & 0xM`) up to the end of the function as PAD_ names with
padmask.py's expr().  Includes platform/pad.h.  Same numbers, so `make`
stays byte-identical."""
import re, sys, pathlib
sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
argv, sys.argv = sys.argv, sys.argv[:1]  # padmask.py runs on its argv when imported
from padmask import expr
sys.argv = argv

for f in sys.argv[1:]:
    p = pathlib.Path(f); lines = p.read_text().split('\n'); var = None; n = 0
    for i, l in enumerate(lines):
        m = re.search(r'\b(\w+)\s*=\s*D_00425BC8(->x(?:4|8|10))?\s*;', l)
        if m:
            var = re.escape(m.group(1)) + (r'->x(?:4|8|10)' if not m.group(2) else '')
            continue
        if l.startswith('}'):
            var = None
        if var:
            def sub(mm):
                e = expr(int(mm.group(2), 16))
                return mm.group(1) + e if e else mm.group(0)
            new = re.sub(r'(\b%s\s*&\s*)(0x[0-9A-Fa-f]+)\b' % var, sub, l)
            if new != l: n += 1; lines[i] = new
    txt = '\n'.join(lines)
    inc = '#include "platform/pad.h"'
    if n and inc not in txt:
        m = re.search(r'^#include "common.h"\n', txt, re.M) or re.search(r'^#include .*\n', txt, re.M)
        txt = txt[:m.end()] + inc + '\n' + txt[m.end():]
    p.write_text(txt)
    print(f, n)
