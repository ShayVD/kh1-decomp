#!/usr/bin/env python3
"""The full-screen packets' table against the ELF and the C (phase 5, docs/renderer-spec.md 5.4 "Session 99").

Under a wide view a port stretches the static full-screen packets (host/port/fullscreen.c, applied by the
host's GIF path under KH1_HOST_WIDE) and the passes built in C write the view's edges themselves
(include/platform/view.h). A full-screen send in neither keeps the 4:3 canvas, which is silent: session 98's
wide run found one (the stored frame back). So this walks every send through func_00106b18 (the
lui / addiu pairs before a call, tools/vu/gs_packets.py --callers, and every `func_00106b18(D_x)` in src/),
finds its SPRITEs whose XYZ X together span the canvas (x 1792 .. 2304 to within 4 px, one sprite or a set
of columns; a half-size one, x 1792 .. 2048 over 192 lines, is a capture into a buffer of its own) and
checks:

  - a full-screen sprite whose two XYZ words are data (no `D_x[i] = ...` in src/ writes them) is in a
    fullscreen.c row with KH1_FS_X (a half-size one KH1_FS_XS), or the send is in EXEMPT;
  - a send whose full-screen sprites' XYZ are all written from C has no X / XS row (the stretch would count
    the view twice), and every such write names the view (PLAT_VIEW_*) or is in WRITE_EXEMPT;
  - a textured full-screen sprite whose u spans 255 texels or more (a copy of the target, the display or a
    capture) is in a row with KH1_FS_U, or the send is in EXEMPT;
  - every fullscreen.c row is still a send (no stale rows).

Needs the user's ELF (the packets are its data); prints names and coordinates, never packet bytes.

    python3 -I tools/host/fscheck.py [--elf SLPS_251.98] [--table host/port/fullscreen.c] [--src src] [-v]

Exit 1 with one line per problem; -v also lists every full-screen send.
"""
import argparse
import os
import re
import sys
from pathlib import Path

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools", "vu"))
import gs_packets as gp  # noqa: E402

SEND_FN = 0x00106B18
X0, X1, XH = 0x7000, 0x9000, 0x8000  # the canvas's edges and its half, in sixteenths
SLACK = 4 * 16
# a 4:3 edge as a C literal's low halfword: 0x7000 / 0x9000 and the blurs' -2 / -4 px bases
EDGES = {0x7000, 0x9000, 0x6FE0, 0x8FE0, 0x6FC0, 0x8FC0}

# full-screen sends that stay 4:3 on purpose
EXEMPT = {
    "D_002A6960": "brightfade.c func_00106000 case 2: the frame copy into the 640-wide movie buffer at 0x118000 "
                  "(renderer-spec 5.3: movies stay 4:3 and centred)",
    "D_002BBC20": "framectl.c func_0010f580: the system-message band's own 512 x 128 display at 0x3600 "
                  "(renderer-spec 4.15: read circuit 1, stays 4:3 and centred)",
    "D_002BBCC0": "framectl.c func_0010f658: the system-message band's box and its two red lines (4.15, as above)",
}
# C writes of a full-screen XYZ word that keep the 4:3 literal on purpose: (word, a piece of the expression)
WRITE_EXEMPT = {
    ("D_002A6970[10]", "0x174007000"): "brightfade.c case 2's flash over the 640-wide movie buffer (stays 4:3)",
    ("D_002A6970[11]", "(u64)y"): "brightfade.c case 2's flash: its right edge is the movie buffer's width",
}

SEND_C = re.compile(r"\bfunc_00106b18\s*\(\s*(?:\([^()]*\)\s*)?&?\s*(D_[0-9A-F]{8})\s*\)")
DECL = re.compile(r"\bextern\s+(u64|s64|u32|s32)\s+(D_[0-9A-F]{8})\s*\[\s*\]")
WRITE = re.compile(r"\b(D_[0-9A-F]{8})\s*\[\s*(\d+|0x[0-9a-fA-F]+)\s*\]\s*=(?!=)")
ROW = re.compile(r"\{\s*(D_[0-9A-F]{8})\s*,\s*([A-Z_0-9| ]+?)\s*,\s*\"([^\"]*)\"\s*\}")
SIZE = {"u64": 8, "s64": 8, "u32": 4, "s32": 4}
XYZ_REGS = (0x04, 0x05, 0x0C, 0x0D)


def table(path):
    """fullscreen.c's rows: send -> (flags, name)"""
    text = re.sub(r"/\*.*?\*/", "", open(path).read(), flags=re.S)
    m = re.search(r"\bkh1_fullscreen\[\]\s*=\s*\{(.*?)\n\};", text, re.S)
    if not m:
        sys.exit("fscheck: %s has no kh1_fullscreen[]" % path)
    return {s: (set(f.replace(" ", "").split("|")), n) for s, f, n in ROW.findall(m.group(1))}


def c_sources(src):
    for dp, _dn, fn in sorted(os.walk(src)):
        for f in sorted(fn):
            if f.endswith(".c"):
                yield os.path.join(dp, f)


def scan_c(src):
    """the sends named in C, and every constant-index write: address -> [(word, expression, file:line)]"""
    sends, writes = {}, {}
    for path in c_sources(src):
        text = open(path, errors="replace").read()
        rel = os.path.relpath(path, ROOT)
        for m in SEND_C.finditer(text):
            sends.setdefault(m.group(1), rel)
        sizes = {n: SIZE[t] for t, n in DECL.findall(text)}
        for m in WRITE.finditer(text):
            sym, idx = m.group(1), int(m.group(2), 0)
            if sym not in sizes:
                continue
            end = text.find(";", m.end())
            expr = text[m.end():end]
            # a chained assignment's value is the last one
            expr = re.split(r"\bD_[0-9A-F]{8}\s*\[[^]]*\]\s*=(?!=)", expr)[-1].strip()
            line = text.count("\n", 0, m.start()) + 1
            addr = int(sym[2:], 16) + idx * sizes[sym]
            writes.setdefault(addr, []).append(("%s[%d]" % (sym, idx), expr, "%s:%d" % (rel, line)))
    return sends, writes


def regs(img, head):
    """(register, value, the value's address) for every register a send's chain writes"""
    out, a, seen, stack = [], head, set(), []

    def payload(a, n):
        end = a + 16 * n
        while a < end:
            lo, hi = img.q(a)
            nloop, flg, nreg = gp.bits(lo, 0, 15), gp.bits(lo, 58, 2), gp.bits(lo, 60, 4) or 16
            pre, prim = gp.bits(lo, 46, 1), gp.bits(lo, 47, 11)
            rl = [gp.bits(hi, 4 * i, 4) for i in range(nreg)]
            a += 16
            if pre:
                out.append((0x00, prim, None))
            if flg == 0:
                for k in range(nloop * nreg):
                    if a >= end:
                        break
                    v, r = img.q(a)
                    out.append((r & 0xFF if rl[k % nreg] == 0x0E else rl[k % nreg], v, a))
                    a += 16
            elif flg == 1:
                for k in range(nloop * nreg):
                    q = img.q(a + 16 * (k // 2))
                    out.append((rl[k % nreg], q[k % 2], a + 16 * (k // 2) + 8 * (k % 2)))
                a += ((nloop * nreg + 1) // 2) * 16
            else:
                a += 16 * nloop

    for _ in range(1024):
        if a in seen or not img.ok(a):
            break
        seen.add(a)
        lo, _hi = img.q(a)
        qwc, tid, addr = lo & 0xFFFF, lo >> 28 & 7, lo >> 32 & 0x7FFFFFFF
        if tid in (0, 3, 4):
            if qwc and img.ok(addr, 16 * qwc):
                payload(addr, qwc)
            if tid == 0:
                break
            a += 16
        elif tid in (1, 7):
            if qwc:
                payload(a + 16, qwc)
            if tid == 7:
                break
            a += 16 + 16 * qwc
        elif tid == 2:
            if qwc:
                payload(a + 16, qwc)
            a = addr
        elif tid == 5:
            stack.append(a + 16 + 16 * qwc)
            a = addr
        elif tid == 6:
            if not stack:
                break
            a = stack.pop()
    return out


def sprites(img, head):
    """each SPRITE a send draws: (x0, x1, y0, y1 in sixteenths, u span in texels, textured, XYZ addresses)"""
    out, prim, vx, uv = [], 0, [], []
    for r, v, a in regs(img, head):
        if r == 0x00:
            prim, vx, uv = v & 0x7FF, [], []
        elif r == 0x03:
            uv.append(gp.bits(v, 0, 14) / 16)
        elif r in XYZ_REGS:
            vx.append((gp.bits(v, 0, 16), gp.bits(v, 16, 16), a))
            if prim & 7 == 6 and len(vx) == 2:
                (xa, ya, aa), (xb, yb, ab) = vx
                du = abs(uv[-1] - uv[-2]) if len(uv) >= 2 else 0
                out.append((min(xa, xb), max(xa, xb), min(ya, yb), max(ya, yb), du, bool(prim & 0x10), (aa, ab)))
                vx, uv = [], []
    return out


def covers(spans, lo, hi):
    """the x spans together cover lo .. hi (gaps up to a pixel)"""
    at = None
    for a, b in sorted(spans):
        if at is None:
            if a > lo + SLACK:
                return False
            at = b
        elif a <= at + 16:
            at = max(at, b)
    return at is not None and at >= hi - SLACK


def is_half(s):
    return abs(s[0] - X0) <= SLACK and abs(s[1] - XH) <= SLACK and s[3] - s[2] <= 200 * 16


def classify(sp):
    """the send's kind ('full', 'half' or None) and its full-screen sprites, each with its own kind"""
    full = [s for s in sp if s[1] - s[0] >= 16 * 16 and not is_half(s)]
    half = [s for s in sp if is_half(s)]
    if full and covers([(s[0], s[1]) for s in full], X0, X1):
        full = [s for s in full if s[1] > X0 + SLACK and s[0] < X1 - SLACK]
        return "full", [(s, "full") for s in full] + [(s, "half") for s in half]
    if half:
        return "half", [(s, "half") for s in half]
    return None, []


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", default=os.path.join(ROOT, "SLPS_251.98"))
    ap.add_argument("--layout", default=os.path.join(ROOT, "layout.tsv"))
    ap.add_argument("--table", default=os.path.join(ROOT, "host", "port", "fullscreen.c"))
    ap.add_argument("--src", default=os.path.join(ROOT, "src"))
    ap.add_argument("-v", action="store_true")
    args = ap.parse_args()
    img = gp.Image(Path(args.elf))
    rows = table(args.table)
    csends, writes = scan_c(args.src)
    sends = {}
    for _site, fn, a in gp.callers(img, Path(args.layout), SEND_FN):
        sends.setdefault("D_%08X" % a, "func_%08x" % fn)
    for s, f in csends.items():
        sends.setdefault(s, f)

    problems, nfull = [], 0
    for s in sorted(sends):
        a = int(s[2:], 16)
        if not img.ok(a):
            continue
        kind, sp = classify(sprites(img, a))
        if not kind:
            continue
        nfull += 1
        flags, name = rows.get(s, (set(), None))
        static = [(p, k) for p, k in sp if not any(w in writes for w in p[6])]
        textured = [p for p, _k in sp if p[5] and p[4] >= 255]
        cw = sorted({w for p, _k in sp for w in p[6] if w in writes})
        if args.v:
            print("%s %s (%s): %d sprites, %d with data XYZ, %d C-written XYZ words, %d copies; row %s%s" % (
                s, kind, sends[s], len(sp), len(static), len(cw), len(textured),
                "|".join(sorted(flags)) or "none", " (exempt)" if s in EXEMPT else ""))
        if s in EXEMPT:
            if name:
                problems.append("%s is in EXEMPT and has a row (%s)" % (s, name))
            continue
        for k, want in (("full", "KH1_FS_X"), ("half", "KH1_FS_XS")):
            n = sum(1 for _p, kk in static if kk == k)
            if n and want not in flags:
                problems.append("%s (%s): %d %s sprite(s) with XYZ in data, and no %s row in %s" % (
                    s, sends[s], n, k, want, os.path.relpath(args.table, ROOT)))
        if not static and flags & {"KH1_FS_X", "KH1_FS_XS"}:
            problems.append("%s (%s): its XYZ are written from C, but its row stretches X too" % (s, sends[s]))
        if textured and "KH1_FS_U" not in flags:
            problems.append("%s (%s): %d copy sprite(s) (u over %g texels) and no KH1_FS_U row" % (
                s, sends[s], len(textured), max(p[4] for p in textured)))
        for p, k in sp:
            ws = [x for w in p[6] for x in writes.get(w, [])]
            if not ws:
                continue
            if k == "half":
                # a buffer of its own: its left edge stays 0x7000, its right edge is the view's half
                if not any("PLAT_VIEW" in e for _w, e, _at in ws):
                    problems.append("%s (%s): the half-size sprite's XYZ written from C (%s) without the view's "
                                    "width (PLAT_VIEW_W16 / 2)" % (s, sends[s], ws[0][2]))
                continue
            for word, expr, where in ws:
                if "PLAT_VIEW" in expr or any(kk == word and pp in expr for kk, pp in WRITE_EXEMPT):
                    continue
                if any(int(h, 16) & 0xFFFF in EDGES for h in re.findall(r"0x([0-9a-fA-F]+)", expr)):
                    problems.append("%s (%s) writes %s = %s: a 4:3 edge, not the view's (PLAT_VIEW_GX0 / GX1)" % (
                        where, s, word, expr))
    for s, (_f, name) in rows.items():
        if s not in sends:
            problems.append("%s (%s): a row in the table, but no send of it" % (s, name))
    for s in EXEMPT:
        if s not in sends:
            problems.append("%s: in EXEMPT, but no send of it" % s)
    for p in problems:
        print("fscheck: " + p)
    print("fscheck: %d sends, %d full-screen (%d rows, %d exempt), %d problems" % (
        len(sends), nfull, len(rows), len(EXEMPT), len(problems)))
    sys.exit(1 if problems else 0)


if __name__ == "__main__":
    main()
