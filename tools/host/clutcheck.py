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

Session 114: the HUD's sprites take their TEX0 from a descriptor at run time (a TIM2 header): ui.c's pair
builder func_0024aa48 writes it twice, the first forced to PSMT8 CSA 0 CLD 1, so each pair call is a load of all
16 slots and a read of the same CLUT whatever the descriptor holds (the builder's shape is checked, PAIR_SHAPE). A
TEX value stored with no register number next to it (into a named word or through a pointer) is either a
reviewed descriptor (DESCRIPTORS: the timer's three fonts, which must reach a pair caller) or self-loading (CLD 1
to 3 at a constant CSA: the field text's glyphs, renderer-spec 4.10), else a problem. `--table` prints the 2D
palette table (every (CBP, CPSM, PSM, CSA) read, with its readers: renderer-spec 4.9 "Session 114").

A heuristic over the text, as giftags.py: a TEX value is a 64-bit expression with an indexed PSM, CPSM 0 / 2 /
10, assigned within 6 lines of a register number 6 / 7 / 22 / 23 (TEX0_1 / 2, TEX2_1 / 2) or passed with one
to func_0011fb38; branches are taken in source order (a load in one arm counts for the other). Reads only the
repository's C (no game data, no ELF).

    python3 -I tools/host/clutcheck.py [--src src] [--dirs text,menu] [-v] [--table]

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

# ui.c's pair builder (renderer-spec 4.10): a HUD sprite's UiPkt starts with two TEX0_1 words from one
# descriptor (func_0024a6b8: unk0 / unk10 = x, unk8 / unk18 = 6), the first forced to PSMT8 CSA 0 CLD 1, so it
# loads the whole 256-entry CLUT at the descriptor's own CBP before the second reads it; func_002388b8 copies both
# words in front of every quad. Any descriptor value is then self-loading: checked here by the builder's shape.
PAIR = "func_0024aa48"
PAIR_SHAPE = {
    "func_0024aa48": (r"\bfunc_0024a6b8\s*\(", r"->\s*f56\s*=\s*0\s*;", r"->\s*f61\s*=\s*1\s*;",
                      r"->\s*f20\s*=\s*0x13\s*;"),
    "func_0024a6b8": (r"->\s*unk0\s*=\s*x\s*;", r"->\s*unk8\s*=\s*6\s*;", r"->\s*unk10\s*=\s*x\s*;",
                      r"->\s*unk18\s*=\s*6\s*;"),
}
# the pair builder's callers that take the descriptor as an argument: function -> its argument's index
PAIR_CALLERS = {"func_0024aa48": 2, "func_002474e8": 1}
# TEX0 values the C stores into a named word with no register number next to it (session 114): word -> the
# descriptor it is the +0x18 of (Tex_4268b0's tb.unk18), which must reach a pair caller
DESCRIPTORS = {
    "D_006692D8": "D_006692C0",  # timer.nostrict.c func_00248400: the minigame timer's three fonts (timer.c)
    "D_00669308": "D_006692F0",
    "D_00669338": "D_00669320",
}

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
            if c == PAIR and not FN.match(t.rstrip(";")):  # not the builder's own definition
                ev.append(("pair", i, t.split(PAIR, 1)[1].strip()))
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
            elif f is not None and not fb:
                lhs = re.split(r"[{};:]", t.split("=", 1)[0])[-1].strip()  # after a `case N:` label
                if re.fullmatch(r"\*?\s*[A-Za-z_]\w*", lhs):
                    ev.append(("store", i, f, lhs.lstrip("* ")))
    return ev


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--src", default=os.path.join(ROOT, "src"))
    ap.add_argument("--dirs", help="the src/ folders read (comma-separated; default all but sdk)")
    ap.add_argument("-v", action="store_true", help="list every picture's loads and reads")
    ap.add_argument("--table", action="store_true", help="print the 2D palette table: every (CBP, CPSM, PSM, CSA) "
                    "read, with its readers (renderer-spec 4.9 \"Session 114\")")
    a = ap.parse_args()
    fns, where, text, bodies = {}, {}, {}, {}
    dirs = a.dirs.split(",") if a.dirs else sorted(d for d in os.listdir(a.src)
                                                    if d != "sdk" and os.path.isdir(os.path.join(a.src, d)))
    for d in dirs:
        for dp, dn, fn in sorted(os.walk(os.path.join(a.src, d))):
            dn.sort()
            for name in sorted(fn):
                if name.endswith(".c"):
                    path = os.path.join(dp, name)
                    text[path] = strip_ps2(open(path, errors="replace").read())
                    for f, body in functions(path).items():
                        fns[f] = events(body, path)
                        bodies[f] = "\n".join(t for _, t in body)
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
    problems, used, nload, nread, nvar, npic, pairs = [], set(), 0, 0, 0, 0, set()
    table = {}  # (CBP, CPSM, PSM, CSA) -> {reader function}

    def note(t, f):
        table.setdefault((t["cbp"], t["cpsm"], t["psm"], t["csa"]), set()).add(f)

    # the pair builder's shape: the two TEX0 words from one descriptor, the first forced to load
    if PAIR in fns:
        for g, pats in PAIR_SHAPE.items():
            src = bodies.get(g)
            if src is None:
                problems.append("%s: not found: the HUD's TEX0 pair is not checked" % g)
                continue
            for pat in pats:
                if not re.search(pat, src):
                    problems.append("%s (%s): no longer matches /%s/: the HUD's TEX0 pair (the first forced to "
                                    "PSMT8 CSA 0 CLD 1) changed; re-check PAIR_SHAPE" % (g, where[g], pat))
    # TEX values stored into named words: each a reviewed descriptor that reaches a pair caller
    seen_desc, selfs = set(), set()
    for f in sorted(fns):
        for e in fns[f]:
            if e[0] != "store":
                continue
            t = e[2]
            if e[3] not in DESCRIPTORS and t["cld"] in (1, 2, 3) and t["csa"] is not None and t["csm"] == 0:
                # a TEX0 that always loads the slots it reads from its own CBP (the field text's glyphs, CLD 1 on
                # every glyph through a REGLIST tag, renderer-spec 4.10): self-loading whatever the CBP
                selfs.add((f, e[1]))
                note(t, "%s (CLD %d, self-loading)" % (f, t["cld"]))
                continue
            if e[3] not in DESCRIPTORS:
                problems.append("%s (%s:%d): a TEX value (CBP 0x%04X) stored into %s with no register number next to "
                                "it: add it to DESCRIPTORS with what reads it" % (
                                    f, where[f], e[1], e[2]["cbp"] or 0, e[3]))
                continue
            seen_desc.add(e[3])
            base = DESCRIPTORS[e[3]]
            callers = [g for g, k in PAIR_CALLERS.items()
                       if any(re.search(r"\b%s\s*\((?:[^,;()]*(?:\([^()]*\))?[^,;()]*,){%d}\s*&?\s*%s\b" % (g, k, base), src)
                              for src in text.values())]
            if not callers:
                problems.append("%s: its descriptor %s reaches no pair caller (%s)" % (
                    e[3], base, " / ".join(PAIR_CALLERS)))
                continue
            note(e[2], "%s (%s via %s)" % (f, base, callers[0]))
    for d in sorted(set(DESCRIPTORS) - seen_desc):
        problems.append("%s: in DESCRIPTORS, but no TEX value is stored into it now" % d)
    if "func_002474e8" in fns and not any(e[0] == "pair" for e in fns["func_002474e8"]):
        problems.append("func_002474e8: no longer calls the pair builder %s: PAIR_CALLERS is stale" % PAIR)

    def flat(f, depth, seen):
        out = []
        for e in fns.get(f, []):
            if e[0] == "hdr":
                out += [t + (HEADER_INIT,) for t in headers.get(e[2], [])]  # the header's TEX0, sent first
            elif e[0] == "call" and e[2] in fns and e[2] not in seen and depth < 4:
                out += flat(e[2], depth + 1, seen | {e[2]})
            elif e[0] in ("tex", "tag", "pair"):
                out.append(e + (f,))
        return out

    for f in sorted(fns):
        if f == HEADER_INIT or not any(e[0] in ("hdr", "send") for e in fns[f]):
            continue
        ev = flat(f, 0, {f})
        if not any(e[0] in ("tag", "pair") for e in ev):
            continue
        npic += 1
        slots, cbp01 = [None] * 16, [None, None]
        for k, e in enumerate(ev):
            if e[0] == "tag":
                continue
            if e[0] == "pair":
                # the descriptor's CLUT, all 16 slots, then read by the same descriptor (func_002388b8's tag has TME)
                pairs.add((e[3], e[1]))
                desc = ("pair", e[2])
                slots = [desc] * 16
                cbp01 = [None, None]
                note({"cbp": "pair", "cpsm": None, "psm": None, "csa": None}, f)
                if a.v:
                    print("%s: %s:%d (%s) loads and reads a HUD descriptor's CLUT (the pair %s)" % (
                        f, where[e[3]], e[1], e[3], e[2]))
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
                note(t, f)
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
    if a.table:
        def key(k):
            return tuple(-2 if v == "pair" else -1 if v is None else v for v in k)
        print("CBP\tCPSM\tPSM\tCSA\treaders\tfunctions")
        for k in sorted(table, key=key):
            cbp, cpsm, psm, csa = k
            rd = sorted(table[k])
            print("%s\t%s\t%s\t%s\t%d\t%s" % (
                "a HUD descriptor's" if cbp == "pair" else "0x%04X" % cbp if cbp is not None else "variable", "0x%X" % cpsm if cpsm is not None else "-",
                "0x%02X" % psm if psm is not None else "variable", csa if csa is not None else "variable",
                len(rd), " ".join(rd)))
    for p in problems:
        print("clutcheck: " + p)
    print("clutcheck: %d pictures, %d CLUT loads, %d CLUT reads checked (%d at a variable CSA), %d HUD TEX0 "
          "pair calls, %d self-loading TEX0 stores, %d loaded elsewhere, %d descriptors stored, %d problems" % (
              npic, nload, nread, nvar, len(pairs), len(selfs), len(used), len(seen_desc), len(problems)))
    sys.exit(1 if problems else 0)


if __name__ == "__main__":
    main()
