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
  - an environment outside src/hud is one OTHER names (gspkt.c's default one);
  - (session 94) each staging send in src/hud (`func_00237018(D_x, D_y - D_x, 1)`: the part's sprites,
    built in the shared staging buffer D_00351E10) comes after an environment send, in its own
    function or in a caller before the call that reaches it, and every environment that can reach it
    keeps the same side. The host's GIF path moves a staging send by the environment sent before it,
    so a staging send under no environment, or under two parts' environments with different sides,
    would draw a part where another part goes.

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
SIDE = re.compile(r"\{\s*(D_[0-9A-F]{8})\s*,\s*(-?\d+)\s*,")
# a staging send: the base, then a length that is a difference (D_y - D_x, (D_y - D_x) >> 4, *pp - *bp)
STAGE = re.compile(r"\bfunc_00237018\s*\(\s*&?\s*(\*?\w+)\s*,\s*[^,;]*-[^,;]*,\s*1\s*\)")
FUNC = re.compile(r"^(?:[A-Za-z_][\w ]*?[\s\*]+)(\w+)\s*\([^;{]*\)\s*\{\s*(?:/\*.*\*/\s*)?$")
CALL = re.compile(r"\b(\w+)\s*\(")


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


def sides(path):
    """kh1_hud_anchors[]'s environments -> side (-1 left, 0 centre, 1 right)"""
    text = open(path).read()
    m = re.search(r"\bkh1_hud_anchors\[\]\s*=\s*\{(.*?)\n\};", text, re.S)
    return {s: int(v) for s, v in SIDE.findall(re.sub(r"/\*.*?\*/", "", m.group(1), flags=re.S))}


def functions(src):
    """name -> (file, first line, [(line, kind, what)]) for every C function in src: kind "env" (an
    environment send, what = its symbol), "stage" (a staging send, what = its base), "call" (what =
    the callee)"""
    funcs = {}
    for d, _, files in os.walk(src):
        for f in sorted(files):
            if not f.endswith(".c"):
                continue
            p = os.path.join(d, f)
            rel = os.path.relpath(p, os.path.dirname(os.path.abspath(src)))
            cur = None
            for i, line in enumerate(open(p, errors="replace"), 1):
                if cur is None:
                    m = FUNC.match(line)
                    if m and not line.startswith(("typedef", "struct", "union", "enum", "#")):
                        cur = (m.group(1), rel, i, [])
                    continue
                if line.startswith("}"):
                    funcs.setdefault(cur[0], (cur[1], cur[2], cur[3]))
                    cur = None
                    continue
                code = re.sub(r"/\*.*?\*/|//.*", "", line)
                for m in SEND.finditer(code):
                    cur[3].append((i, "env", m.group(1)))
                for m in STAGE.finditer(code):
                    cur[3].append((i, "stage", m.group(1)))
                for m in CALL.finditer(code):
                    if m.group(1) != "func_00237018":
                        cur[3].append((i, "call", m.group(1)))
    return funcs


def staging(funcs):
    """[(file:line, base, function, {environment: [the path that reaches it]})] for every staging send
    in src/hud: the environments sent before it in its function, else before a call of its function in
    a caller (up to 6 callers up, through functions that send none before the call)"""
    callers = {}
    for name, (_, _, ev) in funcs.items():
        for line, kind, what in ev:
            if kind == "call" and what in funcs and what != name:
                callers.setdefault(what, []).append((name, line))

    def before(name, line):
        """the last environment sent in name before line, or None"""
        last = None
        for l, kind, what in funcs[name][2]:
            if l >= line:
                break
            if kind == "env":
                last = what
        return last

    out = []
    for name, (path, _, ev) in sorted(funcs.items()):
        if not path.startswith("src/hud/"):
            continue
        for line, kind, what in ev:
            if kind != "stage":
                continue
            found = {}
            todo, seen = [(name, line, [name])], set()
            while todo:
                fn, l, chain = todo.pop()
                env = before(fn, l)
                if env:
                    found.setdefault(env, chain)
                    continue
                if len(chain) > 6:
                    continue
                for c, cl in callers.get(fn, []):
                    if (c, cl) not in seen:
                        seen.add((c, cl))
                        todo.append((c, cl, chain + [c]))
            out.append(("%s:%d" % (path, line), what, name, found))
    return out


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
                    envs.setdefault(m.group(1), []).append("%s:%d" % (os.path.relpath(p, os.path.dirname(os.path.abspath(src))), i))
                for m in SEND.finditer(line):
                    envs.setdefault(m.group(1), []).append("%s:%d" % (os.path.relpath(p, os.path.dirname(os.path.abspath(src))), i))
    return envs


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--table", default=os.path.join(ROOT, "host", "port", "hudanchor.c"))
    ap.add_argument("--src", default=os.path.join(ROOT, "src"))
    ap.add_argument("-v", action="store_true", help="list every environment")
    a = ap.parse_args()
    anchors, markers = table(a.table)
    side = sides(a.table)
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
    stages = staging(functions(a.src))
    for where, base, fn, found in stages:
        kinds = {side.get(e, "marker" if e in markers else "?") for e in found}
        if not found:
            problems.append("staging send %s (%s, in %s) follows no environment send" % (base, where, fn))
        elif len(kinds) > 1:
            problems.append("staging send %s (%s, in %s) follows environments with different sides: %s"
                            % (base, where, fn, ", ".join("%s (%s via %s)" % (e, side.get(e, "marker" if e in markers
                                                         else "?"), " <- ".join(c)) for e, c in sorted(found.items()))))
        if a.v:
            print("stage %s  %s in %s: after %s" % (base, where, fn, ", ".join(
                "%s via %s" % (e, " <- ".join(c)) for e, c in sorted(found.items())) or "nothing"))
    for p in problems:
        print("hudcheck: " + p)
    print("hudcheck: %d HUD environments (%d anchored, %d markers), %d other; %d staging sends; %d problems"
          % (hud, len(anchors), len(markers), other, len(stages), len(problems)))
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
