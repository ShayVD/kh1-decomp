#!/usr/bin/env python3
"""Functions named in an overlay's drafts or hand files that are not in that overlay (session 141, wgb round 51).

    python3 tools/ovl/xsym.py [OVL ...]          # default: every overlay with an ovl/OVL/layout.tsv

A port from a twin overlay can keep the twin's names for callbacks or calls into the overlay itself (wm
func_00f62440 passed gb's func_00f3b0b8 to func_001c01b0 and scored 96; with the wm twin func_00f621b0 it
scored 92). For each func_00XXXXXX in nonmatchings/*/OVL/*.c and ovl/OVL/hand/*.c (comments ignored) whose
address lies in the overlay's range but is not a function in ovl/OVL/layout.tsv, prints `OVL file [names]`.
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def main():
    ovls = sys.argv[1:] or sorted(p.parent.name for p in (ROOT / 'ovl').glob('*/layout.tsv'))
    for ovl in ovls:
        lay = {int(ln.split('\t')[0], 16) for ln in (ROOT / 'ovl' / ovl / 'layout.tsv').read_text().splitlines()
               if re.match(r'^[0-9a-f]+\t', ln)}
        if not lay:
            continue
        lo, hi = min(lay), max(lay) + 0x10000
        files = sorted(ROOT.glob('nonmatchings/*/%s/*.c' % ovl)) + sorted((ROOT / 'ovl' / ovl / 'hand').glob('*.c'))
        for p in files:
            s = re.sub(r'/\*.*?\*/', '', p.read_text(), flags=re.S)
            bad = sorted({'func_00' + m.group(1) for m in re.finditer(r'\bfunc_00([0-9a-f]{6})\b', s)
                          if lo <= int(m.group(1), 16) <= hi and int(m.group(1), 16) not in lay})
            if bad:
                print(ovl, p.relative_to(ROOT), bad)
    return 0


if __name__ == '__main__':
    sys.exit(main())
