#!/usr/bin/env python3
"""The CLUTs the windows' and text's packets read, from the C (phase 5, docs/renderer-spec.md 4.8 / 4.9, session 113).

fscheck.py (session 112) models the GS's CLUT buffer on the packets it walks in the ELF; the text and window
packets are built per draw in a scratch frame by the C (renderer-spec 4.9), so it never sees them. This reads
the same thing from the source: per function, in source order, every TEX0 / TEX2 value the C writes (a
constant, or an expression of constants and variables: a field that depends on a variable is "variable"),
the textured GIF tags (PRE with TME), the static headers it sends first (`D_003F1E70` / `D_003F2270`, whose
TEX0 func_001f2eb8 writes) and the functions it calls that write packets (inlined at the call). One sending
function is one picture. With fscheck's CLUT model (clut_load / clut_reads: CLD 1 .. 5, CBP0 / CBP1, an
8-bit load fills all 16 slots from CSA, a 4-bit one slot CSA), each TEX value written after a textured tag
and before the next tag (the per-glyph / per-part TEX2 in A+D) or current at it is a read: an indexed PSM
needs its slots loaded earlier in the picture from the same CBP / CPSM (a variable CSA: all 16 slots; a
variable PSM: taken as 4-bit), else (function, CBP) is in CLUT_EXPECTED naming who loads it. A load with a
variable CBP or CLD, or CSM2, is reported (not modelled).

A heuristic over the text, as giftags.py: a TEX value is a 64-bit expression with an indexed PSM, CPSM 0 / 2 /
10, assigned within 6 lines of a register number 6 / 7 / 22 / 23 (TEX0_1 / 2, TEX2_1 / 2) or passed with one
to func_0011fb38; branches are taken in source order (a load in one arm counts for the other). Reads only the
repository's C (no game data, no ELF).

    python3 -I tools/host/clutcheck.py [--src src] [--dirs text,menu] [-v]

Exit 1 with one line per problem.
"""
import argparse
import os
import re
import sys
import warnings

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from fscheck import PSM4, PSM8, clut_load, clut_reads, strip_ps2  # noqa: E402

FN = re.compile(r"^[A-Za-z_][\w \*]*\b(func_[0-9a-f]{8})\s*\(.*\)\s*\{?\s*$")
LIT = re.compile(r"0[xX][0-9a-fA-F]{9,16}")
SENDERS = re.compile(r"\b(PlatDmaSend|func_00106b18|func_00237018|sceDmaSend)\s*\(")
CALL = re.compile(r"\b(func_[0-9a-f]{8})\s*\(")
REG = re.compile(r"=\s*(6|7|22|23|0x0?6|0x0?7|0x16|0x17)\s*;")
FB38 = re.compile(r"func_0011fb38\s*\(\s*(6|7|22|23|0x0?6|0x0?7|0x16|0x17)\s*,\s*([^;]*?)\s*,\s*\w+\s*\)")
HEADER_INIT = "func_001f2eb8"  # text.nofill.c: writes the four static headers once (renderer-spec 4.8)
HEADERS = ("D_003F1A70", "D_003F1E70", "D_003F2270", "D_003F27D0")
POSTFIX = re.compile(r"(?<!\w)[A-Za-z_]\w*(?:\s*(?:->|\.)\s*\w+|\s*\[[^\]]*\])*")
FIELDS = {"psm": (20, 6), "cbp": (37, 14), "cpsm": (51, 4), "csm": (55, 1), "csa": (56, 5), "cld": (61, 3)}

# functions whose sprites read a CLUT that no TEX0 / TEX2 in their picture loads, on purpose (the buffer
# holds it from another send's load): (function, the CLUT's CBP) -> who loads it
CLUT_EXPECTED = {
    ("func_001f94f0", 0x3FFC): "wintext.nostrict.c's message draw sends each glyph as the whole chain from its head (the END "
                               "tag's QWC 11: the head's TEX2 PSMT8 CLD 2 of 0x3FFC, the sprite tag, the glyph), so the "
                               "message font's CLUT is loaded again before every glyph; the inline icons drawn between "
                               "glyphs (control code 15: func_001fc330's window font, CLD 2 of 0x3DFC) do not carry over",
}


def value(expr):
    """the 64-bit value of a C expression at two settings of its variables (0 and 0x1F: a variable is taken as
    a palette number or a PSM, 5 bits; one wide enough to spill into CSM / CLD is not modelled), or None"""
    e = re.sub(r"\(\s*(?:u64|s64|u32|s32|unsigned long long|long long|unsigned long|long)\s*\)", "", expr)
    e = re.sub(r"\b(0[xX][0-9a-fA-F]+|\d+)[uUlL]+\b", r"\1", e)
    if not re.search(r"\b0[xX]", e) or re.search(r"[?:\"'{}]|\(\s*\*|->\s*\(", e):
        return None
    e = POSTFIX.sub("V", e)
    out = []
    warnings.simplefilter("ignore", SyntaxWarning)  # "V(...)": a call, refused below
    for v in (0, 0x1F):
        try:
            out.append(eval(e.replace("V", str(v)), {"__builtins__": {}}) & (1 << 64) - 1)
        except Exception:
            return None
    return out


def tex_fields(vals):
    """{field: value or None (variable)} of a TEX0 / TEX2 value, or None when it is not one with a CLUT"""
    f = {}
    for k, (lo, n) in FIELDS.items():
        a, b = (v >> lo & (1 << n) - 1 for v in vals)
        f[k] = a if a == b else None
    if f["psm"] is not None and f["psm"] not in PSM8 + PSM4:
        return None
    if f["cpsm"] not in (0, 2, 10) or f["csm"] is None or f["cbp"] == 0:
        return None
    return f


def word(f, **over):
    g = dict(f, **over)
    return sum((g[k] or 0) << FIELDS[k][0] for k in FIELDS)


def functions(path):
    """{function: [(line, text)]} of a C file, `#ifdef KH1_PS2` branches and comments left out"""
    out, cur = {}, None
    for i, line in enumerate(strip_ps2(open(path, errors="replace").read()).splitlines(), 1):
        m = FN.match(line)
        if m and not line.rstrip().endswith(";"):
            cur = m.group(1)
            out[cur] = []
        elif cur and line.startswith("}"):
            out[cur].append((i, line))
            cur = None
            continue
        if cur:
            out[cur].append((i, line))
    return out


def events(body, where):
    """the function's events in source order: ("tex", line, fields, register), ("tag", line, prim),
    ("hdr", line, name), ("call", line, function), ("send", line), ("def", line, header)"""
    ev = []
    stmts = [(i, st + ";") for i, t in body for st in t.split(";")]
    for k, (i, t) in enumerate(stmts):
        m = re.search(r"\b\w+\s*=\s*&?\s*(D_003F(?:1A70|1E70|2270|27D0))\s*;", t)
        if m:
            ev.append(("def", i, m.group(1)))
        for c in CALL.findall(t):
            ev.append(("call", i, c))
        if SENDERS.search(t):
            h = [n for n in HEADERS if n in t]
            ev.append(("hdr", i, h[0]) if h else ("send", i))
        fb = FB38.search(t)
        cands = [(fb.group(2), int(fb.group(1), 0))] if fb else []
        if not fb and "=" in t and (LIT.search(t) or re.search(r"0[xX][0-9a-fA-F]+\w*\s*<<|<<[^;]*0[xX]", t)):
            rhs = t.split("=", 1)[1].rsplit(";", 1)[0]
            near = [(abs(stmts[j][0] - i), abs(j - k), int(REG.search(stmts[j][1]).group(1), 0))
                    for j in range(max(0, k - 10), min(len(stmts), k + 11))
                    if j != k and abs(stmts[j][0] - i) <= 6 and REG.search(stmts[j][1])]
            cands = [(rhs, min(near)[2] if near else None)]
        for rhs, reg in cands:
            vals = value(rhs)
            if vals is None:
                continue
            v = vals[0]
            if not v & 0x3FFFFFFF0000 and v >> 46 & 1 and not v >> 58 & 3 and v >> 47 & 7 != 7 and v >> 51 & 1:
                # a GIF tag: PACKED, PRE, PRIM with TME
                ev.append(("tag", i, v >> 47 & 0x7FF))
                continue
            f = tex_fields(vals)
            if f is not None and reg is not None:
                ev.append(("tex", i, f, reg))
    return ev


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--src", default=os.path.join(ROOT, "src"))
    ap.add_argument("--dirs", help="the src/ folders read (comma-separated; default all but sdk)")
    ap.add_argument("-v", action="store_true", help="list every picture's loads and reads")
    a = ap.parse_args()
    fns, where = {}, {}
    dirs = a.dirs.split(",") if a.dirs else sorted(d for d in os.listdir(a.src)
                                                    if d != "sdk" and os.path.isdir(os.path.join(a.src, d)))
    for d in dirs:
        for dp, dn, fn in sorted(os.walk(os.path.join(a.src, d))):
            dn.sort()
            for name in sorted(fn):
                if name.endswith(".c"):
                    path = os.path.join(dp, name)
                    for f, body in functions(path).items():
                        fns[f] = events(body, path)
                        where[f] = os.path.relpath(path, a.src)
    # the headers' TEX writes, from their set-up
    headers = {}
    cur = None
    for e in fns.get(HEADER_INIT, []):
        if e[0] == "def":
            cur = e[2]
            headers[cur] = []
        elif e[0] == "tex" and cur:
            headers[cur].append(e)
    problems, used, nload, nread, nvar, npic = [], set(), 0, 0, 0, 0

    def flat(f, depth, seen):
        out = []
        for e in fns.get(f, []):
            if e[0] == "hdr":
                out += [t + (HEADER_INIT,) for t in headers.get(e[2], [])]  # the header's TEX0, sent first
            elif e[0] == "call" and e[2] in fns and e[2] not in seen and depth < 4:
                out += flat(e[2], depth + 1, seen | {e[2]})
            elif e[0] in ("tex", "tag"):
                out.append(e + (f,))
        return out

    for f in sorted(fns):
        if f == HEADER_INIT or not any(e[0] in ("hdr", "send") for e in fns[f]):
            continue
        ev = flat(f, 0, {f})
        if not any(e[0] == "tag" for e in ev):
            continue
        npic += 1
        slots, cbp01 = [None] * 16, [None, None]
        for k, e in enumerate(ev):
            if e[0] == "tag":
                continue
            t = e[2]
            if t["cld"] is None or (t["cld"] and t["cbp"] is None):
                problems.append("%s: %s:%d (%s): a TEX%s write with a variable %s: not modelled" % (
                    f, where[e[4]], e[1], e[4], "2" if e[3] >= 0x16 else "0", "CLD" if t["cld"] is None else "CBP"))
                continue
            if t["csm"]:
                problems.append("%s: %s:%d (%s): a CLUT load with CSM2: not modelled" % (f, where[e[4]], e[1], e[4]))
                continue
            psm = t["psm"] if t["psm"] is not None else PSM4[0]
            fill = clut_load(word(t, psm=psm, csa=t["csa"] or 0), cbp01)
            if t["csa"] is None and fill and psm in PSM4:
                fill = list(range(16))  # a 4-bit load at a variable CSA: any slot (not found)
            if fill:
                nload += 1
                for s in fill:
                    slots[s] = (t["cbp"], t["cpsm"])
                if a.v:
                    print("%s: %s:%d (%s) loads the CLUT 0x%04X (CPSM 0x%X, CLD %d, slots %s)" % (
                        f, where[e[4]], e[1], e[4], t["cbp"], t["cpsm"], t["cld"],
                        "all" if len(fill) == 16 else fill[0]))
            nxt = ev[k + 1] if k + 1 < len(ev) else None
            # every TEX write in a picture with textured sprites is read, unless the next one follows at once
            # (the windows' TEX2 PSMT8 CLD 2, then the part's PSMT4 palette)
            reads = [] if nxt and nxt[0] == "tex" and nxt[4] == e[4] and 0 < nxt[1] - e[1] <= 3 else [t]
            for t in reads:
                psm = t["psm"] if t["psm"] is not None else PSM4[0]
                want = clut_reads(word(t, psm=psm, csa=t["csa"] or 0))
                if not want:
                    continue
                if t["csa"] is None:
                    nvar += 1
                    want = list(range(16)) if psm in PSM4 else want
                nread += 1
                need = (t["cbp"], t["cpsm"])
                bad = [s for s in want if slots[s] != need]
                if a.v:
                    print("%s: reads the CLUT 0x%04X (PSM %s, CSA %s)%s" % (
                        f, need[0], "0x%02X" % t["psm"] if t["psm"] is not None else "variable",
                        t["csa"] if t["csa"] is not None else "variable", ", not loaded in the picture" if bad else ""))
                if bad:
                    if (f, need[0]) in CLUT_EXPECTED:
                        used.add((f, need[0]))
                    else:
                        problems.append("%s (%s): a sprite reads the CLUT 0x%04X (CSA %s) that no TEX0 / TEX2 before "
                                        "it in its picture loads (slot %d holds %s): add (function, CBP) to "
                                        "CLUT_EXPECTED with who loads it" % (
                                            f, where[f], need[0], t["csa"] if t["csa"] is not None else "variable",
                                            bad[0], "0x%04X" % slots[bad[0]][0] if slots[bad[0]] else "nothing"))
    for k in sorted(set(CLUT_EXPECTED) - used):
        problems.append("%s: in CLUT_EXPECTED for 0x%04X, but its CLUT is now loaded in the picture" % k)
    for p in problems:
        print("clutcheck: " + p)
    print("clutcheck: %d pictures, %d CLUT loads, %d CLUT reads checked (%d at a variable CSA), %d loaded "
          "elsewhere, %d problems" % (npic, nload, nread, nvar, len(used), len(problems)))
    sys.exit(1 if problems else 0)


if __name__ == "__main__":
    main()
