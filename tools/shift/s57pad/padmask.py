"""Write the game's button masks as include/platform/pad.h constants (phase 4,
session 57; docs/portability.md rule 2 "Session 57").

  python3 -I tools/shift/s57pad/padmask.py FILE..

Rewrites `D_00425BC8->xN & 0xV` (the decoded pad state: +0x8 pressed,
+0x10 repeated, ...) as PAD_ names: the low 16 bits as buttons, bits 16-23
as PAD_RSTICK(..), bits 28-31 as PAD_LSTICK(..), a direction on both the
d-pad and the left stick as PAD_DIR(..).  Includes platform/pad.h.  The
constants are the same numbers, so `make` stays byte-identical."""
import re, sys, pathlib
B = ['PAD_SELECT', 'PAD_L3', 'PAD_R3', 'PAD_START', 'PAD_UP', 'PAD_RIGHT', 'PAD_DOWN', 'PAD_LEFT',
     'PAD_L2', 'PAD_R2', 'PAD_L1', 'PAD_R1', 'PAD_TRIANGLE', 'PAD_CIRCLE', 'PAD_CROSS', 'PAD_SQUARE']

def bits(v):
    return [B[i] for i in range(16) if v >> i & 1]

def expr(v):
    lo, rs, ls = v & 0xffff, (v >> 16) & 0xff, (v >> 24) & 0xff
    if (rs & 0xf) or (ls & 0xf):
        return None  # not a direction bit: leave the number
    both = lo & 0xf0 & ls
    parts = []
    if both: parts.append('PAD_DIR(%s)' % ' | '.join(bits(both)))
    rest_lo, rest_ls = lo & ~both, ls & ~both
    parts += bits(rest_lo)
    if rest_ls: parts.append('PAD_LSTICK(%s)' % ' | '.join(bits(rest_ls)))
    if rs: parts.append('PAD_RSTICK(%s)' % ' | '.join(bits(rs)))
    if not parts: return None
    return parts[0] if len(parts) == 1 else '(%s)' % ' | '.join(parts)

for f in sys.argv[1:]:
    p = pathlib.Path(f); t = p.read_text(); n = 0
    def rep(m):
        global n
        e = expr(int(m.group(2), 16))
        if e is None: return m.group(0)
        n += 1
        return m.group(1) + e
    t2 = re.sub(r'(D_00425BC8->x[0-9a-f]+ & )(0x[0-9A-Fa-f]+)\b', rep, t)
    if n and '#include "platform/pad.h"' not in t2:
        m = re.search(r'^#include "common.h"\n', t2, re.M) or re.search(r'^#include .*\n', t2, re.M)
        t2 = t2[:m.end()] + '#include "platform/pad.h"\n' + t2[m.end():]
    if t2 != t: p.write_text(t2)
    print(f, n)
