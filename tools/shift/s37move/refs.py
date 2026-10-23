#!/usr/bin/env python3
"""Calls and data of each function in an address range (phase 4, session 37).

  python3 -I tools/shift/s37move/refs.py LO HI      (hex, e.g. 001fd248 00200000)

Reads the relocations of the built objects (run `make` first), so it lists
what each matched function in [LO, HI) calls (C:) and which D_ names it
addresses (D:), with its current source file.  Group a module move by these
(docs/modules.md "Checklist for a module move")."""
import collections
import os
import re
import subprocess
import sys
from pathlib import Path

os.chdir(Path(__file__).resolve().parents[3])
if len(sys.argv) != 3:
    sys.exit(__doc__)
lo, hi = sys.argv[1].lower().zfill(8), sys.argv[2].lower().zfill(8)
pl = [l.rstrip('\n').split('\t') for l in open('out/gen/placements.tsv')][1:]
fs = [p for p in pl if lo <= p[0] < hi]
refs = collections.defaultdict(set)
for o in sorted(set(p[2] for p in fs)):
    out = subprocess.run(['mips-linux-gnu-objdump', '-r', o], capture_output=True, text=True).stdout
    sec = None
    for line in out.splitlines():
        m = re.match(r'RELOCATION RECORDS FOR \[(.*)\]', line)
        if m:
            sec = m.group(1)
            continue
        p = line.split()
        if len(p) == 3 and sec and sec.startswith('.text.'):
            refs[sec[6:]].add(re.sub(r'[+-]0x\w+$', '', p[2]))
for p in fs:
    r = refs.get(p[1], set())
    c = sorted(x for x in r if not x.startswith(('D_', '.')) and x != 'VALUE')
    d = sorted(x for x in r if x.startswith('D_'))
    print(p[0], p[1], p[3].replace('src/', ''), 'C:' + ','.join(c), 'D:' + ','.join(d), sep='\t')
