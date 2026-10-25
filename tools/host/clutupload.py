#!/usr/bin/env python3
"""Every CLUT the C uploads into GS memory, and when, from the C (phase 5, docs/renderer-spec.md 4.13 "Session 115").

clutcheck.py (sessions 113 / 114) checks that each textured sprite loads its CLUT into the GS's CLUT buffer
(TEX0 / TEX2 CLD) in its own picture. This is the other half for a port's palette cache: which GS memory blocks
hold a CLUT, who writes them and how often, so a cache keyed by (CBP, CSA) knows when an entry goes stale. It
finds every CLUT-shaped image upload in src/ (all but sdk):

  - `PlatGsSetDefLoadImage(li, dbp, dbw, psm, x, y, w, h)` and gifpkt.c's `func_0011fbb0(dbp, dbw, psm, x, y,
    w, h, qwc, src, buf)` with a colour PSM (CT32 / CT24 / CT16 / CT16S, or a variable one) and a CLUT's
    rectangle (8 x 2: 16 colours, 16 x 16: 256, or 16 wide by a variable height);
  - a destination that is a parameter of its function is followed to every call of that function in src/ (one
    level per step, up to three), so roombg.c's `func_00100d18(.., i + 0x3e00)` reads `0x3E00 + i`;
  - the CLUTs written another way (a BITBLTBUF built in a DMA chain, a sprite drawn into a CLUT's blocks):
    OTHER, each checked by a pattern that must still be in its function.

Each uploading function must be in REVIEWED with when it rewrites the blocks: `load` (a room, a file or an
effect being loaded: the cache is refilled when the load runs), `draw` (uploaded again just before each draw that
reads it, over blocks other draws share: the contents change within a frame), `frame` (rewritten once a frame by
an animation: the readers see the new colours from the next frame), `boot` (once) or `uncalled` (no caller in
the main ELF). An upload in a function
not listed, or a listed one with no upload left, is a problem. `--table` prints the list (renderer-spec 4.13
"Session 115"). Reads only the repository's C (no game data, no ELF).

    python3 -I tools/host/clutupload.py [--src src] [--table]

Exit 1 with one line per problem.
"""
import argparse
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from clutcheck import FN, functions  # noqa: E402
from fscheck import strip_ps2  # noqa: E402

# the upload calls: name -> (index of dbp, of psm, of w, of h)
UPLOADS = {"PlatGsSetDefLoadImage": (1, 3, 6, 7), "func_0011fbb0": (0, 2, 5, 6)}
COLOUR_PSM = (0, 1, 2, 10)
CLUT_RECTS = ((8, 2), (16, 16))

# function -> (when, what), every function that writes a CLUT into GS memory
REVIEWED = {
    # src/game, src/gfx, src/model, src/obj, src/ppp: the 3D side
    "func_00100d18": ("load", "the room's 16-colour CLUTs, 8 x 2 at 0x3E00 + i (i < n0), from the background file "
                      "(roombg.c func_00101048, once per room)"),
    "func_00100d90": ("load", "the room's 256-colour CLUTs, 16 x 16 at 0x3E00 + i for every 4th i from n0 to n1"),
    "func_0015f488": ("draw", "renderer B: the model record's CLUT, 16 x 16 to 0x3700, in the upload list before "
                      "every draw (a REF to the record's colours: the source changes, the block does not)"),
    "func_0015fa20": ("draw", "the eye overlay: its CLUT, 16 x 16 to 0x3700, between the overlay's two sends"),
    "func_00135ed0": ("draw", "the crossfade's second texture: its CLUT, 16 x 16 to the record's CBP (0x3700, "
                      "D_0055C680.x8), uploaded in the crossfade's own packet"),
    "func_00102118": ("frame", "the texture animations: palette A to 0x3600 and B to 0x3A00 (scratch), then two "
                      "sprites into the room CLUT at 0x3E00 + v (renderer-spec 4.13, keys 90000 + 10 id, after "
                      "every room draw: the room sees the blend one frame later)"),
    "func_00109180": ("draw", "mdlpkt.c's 8 x 2 CLUT upload: the shaped wipe's to 0x3A00 (brightfade.c "
                      "func_00106438) and the field text's icons' to 0x3C00 (fldtext.c func_0010c410: control codes 6 .. 9, the icon "
                      "sheet PSMT4 128 x 48 at 0x3A00 with it), each before its send"),
    "pppKeMdlTfdDraw": ("draw", "a ppp model whose palette fades: a 256-colour ramp (kemdltfd.c func_001a9460) "
                        "built and uploaded as 16 x 16 at the resource's CBP + 4 x page before each draw"),
    "pppKeMdlTfdUvDraw": ("draw", "the same, with the model's UVs scrolled"),
    "pppKeMdlTfd2Draw": ("draw", "the same, the \"2\" class"),
    "pppKeMdlTfdUv2Draw": ("draw", "the same, the \"2\" class with UVs"),
    "pppKeMdlTfd3Draw": ("draw", "the same, the \"3\" class (kemdltfd3.nostrict.c)"),
    "pppKeMdlTfdUv3Draw": ("draw", "the same, the \"3\" class with UVs"),
    "pppKeTkFadeDraw": ("draw", "the ppp screen fade: its 256-colour ramp, 16 x 16 at the resource TEX0's CBP, "
                        "before its quad"),
    "func_00180b40": ("load", "a ppp effect's CLUTs (TIM2 PSMT8: 16 x 16, PSMT4: 8 x 2) into the texture slot the "
                      "effect was given (pppsys.c's allocator: CBPs from 0x3D40 rebased), when the effect loads"),
    "func_00180ab8": ("load", "a ppp effect's images into its slot; CLUT-shaped only by its variable sizes"),
    # src/hud, src/text, src/menu, src/gfx's 2D: renderer-spec 4.9's table
    "func_00239368": ("boot", "the HUD's six CLUT rows D_00648230, 16 x 16 to 0x3FD8, at the HUD's set-up"),
    "func_002393d8": ("draw", "the timer: the window font's CLUT (D_003F1660, the bytes at 0x3DFC) again at 0x3A00 "
                      "with the font at 0x3600, at the start of every timer draw (timer.c func_00248140)"),
    "func_00249a48": ("draw", "a HUD TIM2 picture's CLUT at its TEX0's CBP (16 x 16 or 8 x 2): the gauges' three "
                      "(gauge.nostrict.c func_0023d698) and the timer's icon (func_00247cc8) at 0x3A00, each "
                      "before its draw"),
    "func_00242c08": ("draw", "a face picture: its CLUT 16 x 16 to 0x3C00 and its PSMT8 image to 0x3A00, in its "
                      "own packet"),
    "func_00242ef8": ("draw", "the same, the second face draw"),
    "func_001f2eb8": ("boot", "the window font's CLUT D_003F1660, 16 x 16 to 0x3DFC, with the headers "
                      "(text.nofill.c); the windows re-send it before they draw (renderer-spec 4.12)"),
    "func_0010c438": ("load", "the field text's 8 x 2 CLUT pairs: 0x3FDC .. 0x3FEB from the ELF (func_0010e8d0, the "
                      "field's set-up) and 0x3FEC .. 0x3FF3 built by func_0010e610 (func_0010e750, when a room "
                      "loads); the glyphs' TEX0 CLD 1 loads them (renderer-spec 4.10)"),
    "func_0010b030": ("load", "the object windows' sheet (PSMT8H at 0x1800): its CLUT 16 x 16 to 0x3FF4 and the same "
                      "colours with RGB cleared (alpha only) to 0x3FF8, when a room loads (roomload.c func_00112968)"),
    "func_001aa0e0": ("uncalled", "a TIM2 picture's CLUT (16 wide, clutSize / 64 high) at its CBP; no caller or "
                      "address of it in the main ELF (an overlay's, if any)"),
    "func_001ef950": ("boot", "the message font's CLUT, 16 x 16 to 0x3FFC from the disc's font file, once at boot "
                      "(gamestate.nostrict.c)"),
    "func_0020b338": ("draw", "menubg's image and CLUT (0x3640) as a packet built at the menu's set-up, sent before "
                      "each of its draws"),
    "func_00219500": ("draw", "config's image and CLUT (0x3680), the same way"),
    "func_0021d188": ("draw", "journal's 256 x 256 image and CLUT (0x3700), the same way"),
    "func_0021e120": ("draw", "journal's 64 x 64 pictures and their CLUT (0x3680), in its own packet per draw"),
}

# CLUTs written without an upload call: function -> (pattern that must be in its body, what)
OTHER = {
    "func_0015f488": (r"0x9b80\s*<<\s*33", "BITBLTBUF DBP 0x3700 DBW 1 CT32 in the upload list"),
    "func_0015fa20": (r"0x9b80\s*<<\s*33", "BITBLTBUF DBP 0x3700 DBW 1 CT32"),
    "func_00102118": (r"func_00101f80|func_00101f30", "the cross-fade's upload chains and sprites"),
}


def args_of(text, start):
    """the top-level arguments of the call whose '(' is at text[start]"""
    depth, cur, out = 0, "", []
    for ch in text[start:]:
        if ch == "(":
            depth += 1
            if depth == 1:
                continue
        elif ch == ")":
            depth -= 1
            if depth == 0:
                out.append(cur.strip())
                return out
        elif ch == "," and depth == 1:
            out.append(cur.strip())
            cur = ""
            continue
        cur += ch
    return None


def num(e):
    e = re.sub(r"\(\s*(?:u16|s16|u32|s32|u64|s64)\s*\)", "", e).strip()
    try:
        return int(e, 0)
    except ValueError:
        return None


def params(line):
    """the parameter names of a function definition's first line"""
    m = re.search(r"\((.*)\)", line)
    if not m:
        return []
    out = []
    for p in m.group(1).split(","):
        w = re.findall(r"[A-Za-z_]\w*", p)
        out.append(w[-1] if w and w[-1] != "void" else None)
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--src", default=os.path.join(ROOT, "src"))
    ap.add_argument("--table", action="store_true", help="print every CLUT upload with its destination and when")
    a = ap.parse_args()
    bodies, heads, where = {}, {}, {}
    for d in sorted(os.listdir(a.src)):
        if d == "sdk" or not os.path.isdir(os.path.join(a.src, d)):
            continue
        for dp, dn, fn in sorted(os.walk(os.path.join(a.src, d))):
            dn.sort()
            for name in sorted(fn):
                if not name.endswith(".c"):
                    continue
                path = os.path.join(dp, name)
                fnre = re.compile(r"^[A-Za-z_][\w \*]*\b(\w+)\s*\(.*\)\s*\{?\s*$")
                cur = None
                for i, line in enumerate(strip_ps2(open(path, errors="replace").read()).splitlines(), 1):
                    m = fnre.match(line)
                    if m and not line.rstrip().endswith(";") and not line.startswith((" ", "\t", "#")) \
                            and m.group(1) not in ("if", "while", "for", "switch"):
                        cur = m.group(1)
                        bodies[cur], heads[cur], where[cur] = [], line, os.path.relpath(path, a.src)
                        continue
                    if cur and line.startswith("}"):
                        cur = None
                    elif cur:
                        bodies[cur].append(line)
    text = {f: "\n".join(b) for f, b in bodies.items()}

    def callers(f):
        for g, t in text.items():
            for m in re.finditer(r"\b%s\s*\(" % re.escape(f), t):
                yield g, args_of(t, m.end() - 1)

    def dest(f, e, depth=0):
        """the destination expression(s) of e in function f, parameters followed to the callers"""
        v = num(e)
        if v is not None:
            return {"0x%04X" % v}
        e = e.strip()
        ps = params(heads.get(f, ""))
        if re.fullmatch(r"[A-Za-z_]\w*", e) and e in ps and depth < 3:
            out = set()
            for g, args in callers(f):
                if args and len(args) > ps.index(e):
                    out |= dest(g, args[ps.index(e)], depth + 1)
            return out or {e + " (no caller)"}
        return {re.sub(r"\s+", " ", e)}

    problems, rows, seen = [], [], set()
    for f in sorted(text):
        for name, (idp, ipsm, iw, ih) in UPLOADS.items():
            for m in re.finditer(r"\b%s\s*\(" % name, text[f]):
                args = args_of(text[f], m.end() - 1)
                if not args or len(args) <= ih:
                    continue
                psm, w, h = num(args[ipsm]), num(args[iw]), num(args[ih])
                if psm is not None and psm not in COLOUR_PSM:
                    continue
                if (w, h) not in CLUT_RECTS and not (w == 16 and h is None) and not (w is None and h is None and psm is None):
                    continue
                if w is None and h is None and f != "func_00180ab8":
                    continue  # an image of variable size with a variable PSM: an image, not a CLUT
                size = {(8, 2): "16", (16, 16): "256"}.get((w, h), "variable")
                for d in sorted(dest(f, args[idp])):
                    rows.append((d, size, f, where[f]))
                seen.add(f)
    for f, (pat, what) in OTHER.items():
        if f not in text:
            problems.append("%s: in OTHER but not in src/" % f)
        elif not re.search(pat, text[f]):
            problems.append("%s: OTHER's pattern /%s/ (%s) is no longer in it" % (f, pat, what))
        else:
            seen.add(f)
    for f in sorted(seen - set(REVIEWED)):
        problems.append("%s (%s): uploads a CLUT but is not in REVIEWED (when does it rewrite the blocks?)"
                        % (f, where[f]))
    for f in sorted(set(REVIEWED) - seen):
        problems.append("%s: in REVIEWED but no CLUT upload found in it" % f)
    if a.table:
        print("block\tcolours\twhen\tfunction\tfile\twhat")
        done = set()
        for d, size, f, w in sorted(rows, key=lambda r: (r[0], r[2])):
            if f in REVIEWED:
                print("%s\t%s\t%s\t%s\t%s\t%s" % (d, size, REVIEWED[f][0], f, w, REVIEWED[f][1]))
                done.add(f)
        for f in sorted(OTHER):
            if f in REVIEWED and f not in done:
                print("-\t-\t%s\t%s\t%s\t%s (%s)" % (REVIEWED[f][0], f, where.get(f, "?"), REVIEWED[f][1], OTHER[f][1]))
    for p in problems:
        print("clutupload: " + p)
    kinds = {}
    for f in seen & set(REVIEWED):
        kinds[REVIEWED[f][0]] = kinds.get(REVIEWED[f][0], 0) + 1
    print("clutupload: %d CLUT uploads in %d functions (%s), %d problems"
          % (len(rows), len(seen), ", ".join("%s %d" % kv for kv in sorted(kinds.items())), len(problems)))
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
