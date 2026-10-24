#!/usr/bin/env python3
"""Draft one module per flag mode from an address range (phase 4, session 50;
docs/modules.md "Session 50").

  python3 -I tools/shift/s50move/group.py src/ppp/NAME LO HI [--skip f,...]

Takes every function of out/gen/placements.tsv in [LO, HI) that is still in
src/auto or src/hand (hand/vu0.c and the hand asm excepted), groups them by
their file's flag mode (src/hand/<mode>/ or default), writes
src/ppp/NAME.c, NAME.<mode>.c with assemble.py, prunes them and runs
tools/checkfile.py on each.  Prints the function list per file.
"""
import sys, os, subprocess, re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[3]; os.chdir(ROOT)
HERE = Path(__file__).resolve().parent
base, lo, hi = sys.argv[1], int(sys.argv[2], 16), int(sys.argv[3], 16)
skip = set()
if '--skip' in sys.argv: skip = set(sys.argv[sys.argv.index('--skip') + 1].split(','))
MODES = 'nofill nostrict nostrict_nofill nogcse nostrict_nogcse n32 n32_nogcse n32_nostrict nosi nogcse_nosi nogcse_nosib faddr nostrict_norcse norlo fmam nostrict_nosib'.split()
groups = {}
for l in open('out/gen/placements.tsv'):
    p = l.rstrip('\n').split('\t')
    if p[0] == 'addr' or len(p) < 4: continue
    a = int(p[0], 16)
    if not (lo <= a < hi): continue
    s = p[3]
    if not (s.startswith('src/auto/') or s.startswith('src/hand/')) or s == 'src/hand/vu0.c' or not s.endswith('.c'): continue
    if p[1] in skip: continue
    parts = s.split('/')
    mode = parts[2] if len(parts) > 3 and parts[2] in MODES else ''
    groups.setdefault(mode, []).append((a, p[1]))
def diffs(path):
    """checkfile -v: {addr: [differing word lines]}."""
    r = subprocess.run([sys.executable, 'tools/checkfile.py', path, '-v'], capture_output=True, text=True)
    out, cur = {}, None
    for x in (r.stdout + r.stderr).splitlines():
        m = re.match(r'([0-9a-f]{8}) (MATCH|FAIL)', x)
        if m: cur = m.group(1); out[cur] = [] if m.group(2) == 'FAIL' else None; continue
        if cur and out.get(cur) is not None and x.startswith('  '):
            w = x.split()  # addr ours X orig Y: the low half of ours is the unplaced rodata offset
            out[cur].append((w[0], w[2][:4], w[4]) if len(w) >= 5 else x.strip())
    return out, (r.stdout + r.stderr)
src = {}
for l in open('out/gen/placements.tsv'):
    p = l.rstrip('\n').split('\t')
    if len(p) > 3: src[p[0]] = p[3]
oldcache = {}
for mode, fs in sorted(groups.items()):
    out = base + ('.' + mode if mode else '') + '.c'
    names = [n for a, n in sorted(fs)]
    print('==', out, len(names), ' '.join(names))
    subprocess.run([sys.executable, '-I', str(HERE / 'assemble.py'), out] + names)
    subprocess.run([sys.executable, '-I', str(HERE / 'prune.py'), out])
    new, txt = diffs(out)
    if not new: print(txt[-3000:]); continue
    for a, n in sorted(fs):
        k = '%08x' % a
        if k not in new: print('  MISSING', k, n); continue
        if new[k] is None: continue
        o = src[k]
        if o not in oldcache: oldcache[o] = diffs(o)[0]
        same = oldcache[o].get(k) == new[k]
        print('  %s %s FAIL %d words, %s' % (k, n, len(new[k]), 'same as its old file (rodata)' if same else 'NEW DIFF'))
