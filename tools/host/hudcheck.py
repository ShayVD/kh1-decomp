#!/usr/bin/env python3
"""The HUD's anchor table against the C (phase 5, docs/renderer-spec.md 5.3.1 and 5.4 "Session 93").

Each gameplay HUD part builds its drawing environment (`func_002370c8(&D_x)`, gspkt.c) and sends it
(`func_00237018(&D_x, 22, 1)`) before its sprites, and a port moves the part by the environment it
sent (host/port/hudanchor.c, applied by the host's GIF path under KH1_HOST_WIDE). A HUD file the table
does not list keeps no anchor and is drawn in the centred 4:3 canvas, which is silent. So this reads
every environment the C builds or sends and checks:

  - each one sent from src/hud is either in kh1_hud_anchors[] (moved to its side) or in
    kh1_hud_markers[] (over 3D, not moved), and not in both;
  - each table entry is still an environment some file sends (no stale rows);
  - an environment outside src/hud is one OTHER names (gspkt.c's default one).

No build and no game data: it reads src/ and host/port/hudanchor.c.

    python3 -I tools/host/hudcheck.py [--table host/port/hudanchor.c] [--src src] [-v]

Exit 1 with one line per problem; -v also lists every environment with its file.
"""
import argparse
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

# environments built or sent outside src/hud: what they are
OTHER = {
    "D_006480D0": "gspkt.c's default environment (func_002372e0 / func_00237318: no main-ELF caller, an overlay's)",
}

BUILD = re.compile(r"\bfunc_002370c8\s*\(\s*&?\s*(D_[0-9A-F]{8})\s*\)")
SEND = re.compile(r"\bfunc_00237018\s*\(\s*&?\s*(D_[0-9A-F]{8})\s*,\s*(?:22|0x16)\s*,")
ENTRY = re.compile(r"\{\s*(D_[0-9A-F]{8})\s*,")


def table(path):
    """kh1_hud_anchors[] and kh1_hud_markers[]: their environments, in order"""
    text = open(path).read()
    out = {}
    for name in ("kh1_hud_anchors", "kh1_hud_markers"):
        m = re.search(r"\b%s\[\]\s*=\s*\{(.*?)\n\};" % name, text, re.S)
        if not m:
            sys.exit("hudcheck: %s has no %s[]" % (path, name))
        body = re.sub(r"/\*.*?\*/", "", m.group(1), flags=re.S)
        out[name] = ENTRY.findall(body)
    return out["kh1_hud_anchors"], out["kh1_hud_markers"]


def environments(src):
    """symbol -> [file:line, ...] for every environment the C builds or sends"""
    envs = {}
    for d, _, files in os.walk(src):
        for f in sorted(files):
            if not f.endswith(".c"):
                continue
            p = os.path.join(d, f)
            for i, line in enumerate(open(p, errors="replace"), 1):
                for m in BUILD.finditer(line):
                    envs.setdefault(m.group(1), []).append("%s:%d" % (os.path.relpath(p, ROOT), i))
                for m in SEND.finditer(line):
                    envs.setdefault(m.group(1), []).append("%s:%d" % (os.path.relpath(p, ROOT), i))
    return envs


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--table", default=os.path.join(ROOT, "host", "port", "hudanchor.c"))
    ap.add_argument("--src", default=os.path.join(ROOT, "src"))
    ap.add_argument("-v", action="store_true", help="list every environment")
    a = ap.parse_args()
    anchors, markers = table(a.table)
    envs = environments(a.src)
    problems = []
    for sym in sorted(set(anchors) & set(markers)):
        problems.append("%s is both an anchor and a marker" % sym)
    for sym in sorted(set(anchors + markers) - set(envs)):
        problems.append("%s is in the table but no file in %s builds or sends it" % (sym, os.path.relpath(a.src, ROOT)))
    hud = other = 0
    for sym, where in sorted(envs.items()):
        in_hud = any(w.startswith("src/hud/") for w in where)
        kind = "anchor" if sym in anchors else "marker" if sym in markers else OTHER.get(sym)
        if in_hud:
            hud += 1
            if sym not in anchors and sym not in markers:
                problems.append("%s (%s) is a HUD environment in neither kh1_hud_anchors nor kh1_hud_markers"
                                % (sym, ", ".join(where)))
        else:
            other += 1
            if sym not in OTHER and sym not in anchors and sym not in markers:
                problems.append("%s (%s) is an environment outside src/hud that OTHER does not name"
                                % (sym, ", ".join(where)))
        if a.v:
            print("%s  %-7s %s" % (sym, kind if kind in ("anchor", "marker") else "other", ", ".join(where)))
    for p in problems:
        print("hudcheck: " + p)
    print("hudcheck: %d HUD environments (%d anchored, %d markers), %d other; %d problems"
          % (hud, len(anchors), len(markers), other, len(problems)))
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
