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
  - every fullscreen.c row is still a send (no stale rows);
  - (session 100) the other GIF paths: the chains sent through sceDmaSend (PlatDmaSend, the tag in a1) and
    gspkt.c's func_00237018 get the same walk, so a static full-screen packet there needs a row too; and a
    function in src/ that writes both 4:3 edges as literals (a left 0x7000 / 0x6FE0 / 0x6FC0 and a right
    0x9000 / 0x8FE0 / 0x8FC0 halfword, outside `#ifdef KH1_PS2` branches and comments) builds a full-screen
    rectangle in C that keeps the canvas: it should name the view (PLAT_VIEW_GX0 / GX1) or be in LIT_EXEMPT;
  - (session 107) no send whose packet sets FRAME draws from its buffer's left edge past FBW x 64 under the
    wide view (--side16, 960 x 544's margin by default: data XYZ by the row's stretch, C-written XYZ by
    their PLAT_VIEW_* edges), or it is in OVER_EXPECTED (the menu capture: 5.1as / 5.1at);
  - (session 108) the GS memory blocks each such send's drawn rectangle covers (FBP, FBW and the PSM's page
    and block order, y included; sends stretched over the view and the environment's frame skipped, as
    above) stay inside the blocks it covers on the PS2 (side 0) and inside the renderer-spec 3.1 region
    its FBP is in, or the send and region are in BLOCK_EXPECTED: a capture or copy landing on a live buffer
    (the texture slot, the Z area, the display) fails even inside its FBW.
  - (session 109) the render-to-texture sends outside that walk get the same block check: the shadow windows
    D_004F7820[i] / D_004F7C10[i] and the crossfade func_00135ed0, built by the game's own C under
    gcc -m32 (tools/host/rtsends.c; skipped with a note without it), the eye overlay D_0035C4A0 +
    D_0035C550 with the tags texspot's C stores (RT_DATA), and case 2's frame copy at each display width
    with its C-written FRAME and XYZ evaluated (CVARS); a sprite the view does not stretch is clipped by
    its SCISSOR, and PACKED RGBAQ / UV / XYZ are read as the GS reads them.

Needs the user's ELF (the packets are its data); prints names and coordinates, never packet bytes.

    python3 -I tools/host/fscheck.py [--elf SLPS_251.98] [--table host/port/fullscreen.c] [--src src] [--cc gcc] [-v]

Exit 1 with one line per problem; -v also lists every full-screen send.
"""
import argparse
import os
import re
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools", "vu"))
import gs_packets as gp  # noqa: E402

SEND_FN = 0x00106B18
# the other GIF senders: (function, the tag's argument register)
OTHER_SENDERS = ((0x00266F38, 5), (0x00237018, 4), (0x001E05A8, 4))
# sceDmaSend (a1), gspkt.c func_00237018 (a0), frame.c func_001e05a8 (a0: the stored frame's path-2 sends)
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

# (session 107) full-screen sends drawn from their buffer's left edge past its width under the wide view, on
# purpose: send -> reason
OVER_EXPECTED = {
    "D_002B6760": "capture.c: the menu capture, KH1_FS_XS into the PS2's 256-wide buffer at 0x3600 (FBW 4); a "
                  "port's buffer is the view's half wide (5.1an), the host's fill clips at FBW x 64 (5.1at)",
}

# (session 108) renderer-spec 3.1's memory map as block ranges [lo, hi) of 256 bytes: (lo, hi, name)
REGIONS = (
    (0x0000, 0x0E00, "display (CT24 512 x 448)"),
    (0x0E00, 0x1A00, "Z area (Z24 512 x 384; the message font at 0x1000, PSMT8H at 0x1800, the 640-wide buffer "
                     "at 0x1180)"),
    (0x1A00, 0x2600, "3D target (CT32 512 x 384)"),
    (0x2600, 0x3600, "room background textures"),
    (0x3600, 0x3A00, "texture slot 0x3600 (field uploads, fonts, menu images, renderer B CLUT 0x3700)"),
    (0x3A00, 0x3D7C, "off-screen buffer 0x3A00 (shadows, texspot, crossfade; face CLUT 0x3C00)"),
    (0x3D7C, 0x3E00, "window font and its CLUT 0x3DFC"),
    (0x3E00, 0x4000, "room and UI CLUTs"),
)
# sends whose drawn blocks leave their FBP's region or the PS2's footprint on purpose: (send, region's
# first block, or "wide" for blocks past the PS2's footprint) -> reason
BLOCK_EXPECTED = {
    ("D_002A5620", 0x3A00): "sceneeff.c: the depth blur's half-size capture, 512 x 192 CT32 at 0x3600 spans "
                            "0x3600 .. 0x3C00 on the PS2 too (over the off-screen buffer, rewritten before its "
                            "next use)",
    ("D_002A5A90", 0x3A00): "the depth blur's capture, as D_002A5620's (the same buffer)",
    ("D_002A5620", "wide"): "the depth blur's capture at the view's half (x 0 .. 338.8) stays inside its FBW 8 but "
                            "reaches the right halves of its pages the PS2's 256 leave alone: 0x3680 .. (the "
                            "menus' CLUT 0x3680, uploaded per draw) and 0x3A80 .. (the off-screen buffer, redrawn "
                            "each frame); scratch there as the left halves are on the PS2 (5.1at, 5.1av)",
    ("D_002A5A90", "wide"): "the depth blur's capture, as D_002A5620's",
    ("D_002A6960", 0x0E00): "brightfade.c case 2: the frame copy into the display as 640 x 448 CT24 runs to "
                            "block 0x1180 over the Z area's first rows on the PS2 too (movies, 4:3)",
    ("D_002B6760", "wide"): "capture.c: the menu capture stretched into its 256-wide buffer (OVER_EXPECTED) "
                            "wraps into blocks 0x3900 .. 0x393F; a port's buffer is the view's half (5.1an)",
    # (session 109) the off-screen buffer's 256 x 256 CT32 (renderer-spec 3.4) runs to block 0x3DFF, over the
    # window font (0x3D7C .. 0x3DFB) and its CLUT 0x3DFC on the PS2 too: the windows re-send the font's
    # uploads (func_001f82b0 -> func_001f8270, 4.12) before they draw, after the list's render-to-texture
    ("D_004F7820", 0x3D7C): "shadow.c func_001284a0: the shadow windows of 196 and 256 (D_002E27E0[1..2]) clear "
                            "rows 224 .. 255 of the off-screen buffer, the window font's blocks (4.12: re-sent "
                            "before the windows draw)",
    ("D_0035C4A0", 0x3D7C): "texspot: the eye overlay's 256 x 256 copy fills the whole off-screen buffer, the "
                            "window font's blocks with it (as D_004F7820's)",
    ("func_00135ed0", 0x3D7C): "objdraw: the crossfade of a texture 256 high (CROSSFADE_SIZES) fills rows 224 .. "
                               "255, the window font's blocks (as D_004F7820's)",
}
# (session 109) the render-to-texture sends outside the walk above (renderer-spec 3.4), checked the same way:
# - packets the game's own C builds at run time (tools/host/rtsends.c runs the builders under gcc -m32): the
#   shadow windows D_004F7820[i] / D_004F7C10[i] (func_001284a0 / func_00128738, one per size
#   D_002E27E0[i] from the ELF), and the texture crossfade func_00135ed0 for each image size below (the
#   model's texture, from the disc at run time: the slot 0x3600 holds up to 256 x 256);
CROSSFADE_SIZES = ((64, 64), (128, 128), (256, 128), (128, 256), (256, 256))
RT_SOURCES = ("tools/host/rtsends.c", "src/gfx/shadow.c", "src/gfx/gifpkt.c", "src/obj/objdraw.nostrict.c")
# - data packets the C finishes at run time: (file, the sends in order (one picture: the GS state carries
#   from one to the next), what they are); the file's `D_x.x0 = n;` / `.x3` / `.x4` stores give the tags
#   their QWC / ID / ADDR (the ELF holds zeros), and its `p->xNN = D_...` stores into the packet that
#   `p = (Pkt *)PLAT_UNCACHED(&D_x)` names move a sprite anywhere: its rectangle is its SCISSOR;
RT_DATA = (("src/gfx/texspot.nostrict.c", ("D_0035C4A0", "D_0035C550"),
            "texspot func_00175600: the eye overlay (renderer-spec 3.4 item 3)"),)
# - sends whose FRAME / XYZ words the C writes from a local: (the local, its values, why), each value's
#   writes evaluated (with the simple assignments before them in their function) instead of the data's
RT_BUILT = ("D_004F7820", "D_004F7C10", "func_00135ed0")
CVARS = {"D_002A6960": ("v", (512, 640), "brightfade.c case 2: func_001110d0's display width")}
# the block order inside a page: CT32 / CT24 (8 x 4 blocks of 8 x 8, a 64 x 32 page) and CT16 / CT16S
# (4 x 8 blocks of 16 x 8, a 64 x 64 page), GS manual 8.3
BLOCKS32 = ((0, 1, 4, 5, 16, 17, 20, 21), (2, 3, 6, 7, 18, 19, 22, 23),
            (8, 9, 12, 13, 24, 25, 28, 29), (10, 11, 14, 15, 26, 27, 30, 31))
BLOCKS16 = ((0, 2, 8, 10), (1, 3, 9, 11), (4, 6, 12, 14), (5, 7, 13, 15),
            (16, 18, 24, 26), (17, 19, 25, 27), (20, 22, 28, 30), (21, 23, 29, 31))
BLOCKS16S = ((0, 2, 16, 18), (1, 3, 17, 19), (8, 10, 24, 26), (9, 11, 25, 27),
             (4, 6, 20, 22), (5, 7, 21, 23), (12, 14, 28, 30), (13, 15, 29, 31))
# PSM -> (block width, block height, the page's block order)
PSM_BLOCKS = {0x00: (8, 8, BLOCKS32), 0x01: (8, 8, BLOCKS32), 0x02: (16, 8, BLOCKS16),
              0x0A: (16, 8, BLOCKS16S)}

# functions whose C writes both 4:3 edges on purpose (none today): "file:function" -> reason
LIT_EXEMPT = {}
LEFT, RIGHT = {0x7000, 0x6FE0, 0x6FC0}, {0x9000, 0x8FE0, 0x8FC0}
FUNC = re.compile(r"^[A-Za-z_][\w \*]*?\b(\w+)\s*\([^;{}]*\)\s*\{", re.M)
# a literal compared against (a loop bound, a range test) is not a coordinate
CMP = re.compile(r"[<>]=?\s*$")

SEND_C = re.compile(r"\bfunc_00106b18\s*\(\s*(?:\([^()]*\)\s*)?&?\s*(D_[0-9A-F]{8})\s*\)")
DECL = re.compile(r"\bextern\s+(u64|s64|u32|s32)\s+(D_[0-9A-F]{8})\s*\[\s*\]")
WRITE = re.compile(r"\b(D_[0-9A-F]{8})\s*\[\s*(\d+|0x[0-9a-fA-F]+)\s*\]\s*=(?!=)")
ROW = re.compile(r"\{\s*(D_[0-9A-F]{8})\s*,\s*([A-Z_0-9| ]+?)\s*,\s*\"([^\"]*)\"\s*\}")
SIZE = {"u64": 8, "s64": 8, "u32": 4, "s32": 4}
XYZ_REGS = (0x04, 0x05, 0x0C, 0x0D)
# (session 109) a PACKED register's quadword as the A+D value it writes (GS manual 3.3.2): RGBAQ's four
# bytes, UV's two 14-bit fields, XYZ's x / y halfwords and 32-bit z (the run-time builders send these)
_XYZ = lambda lo, hi: (lo & 0xFFFF) | (lo >> 32 & 0xFFFF) << 16 | (hi & 0xFFFFFFFF) << 32  # noqa: E731
PACKED = {0x01: lambda lo, hi: (lo & 0xFF) | (lo >> 32 & 0xFF) << 8 | (hi & 0xFF) << 16 | (hi >> 32 & 0xFF) << 24,
          0x03: lambda lo, hi: (lo & 0x3FFF) | (lo >> 32 & 0x3FFF) << 16,
          0x04: _XYZ, 0x05: _XYZ, 0x0C: _XYZ, 0x0D: _XYZ}


def edge_literal(expr):
    """a 4:3 edge in an expression: a hex literal whose low halfword is one, or the decimal 28672 / 36864
    (the stored frame's float maths)"""
    return any(int(h, 16) & 0xFFFF in EDGES for h in re.findall(r"0x([0-9a-fA-F]+)", expr)) or \
        bool(re.search(r"(?<![\w.])(28672|36864)(\.0*f?)?(?![\w.])", expr))


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


def header_sizes(inc):
    """the u64 / u32 arrays the headers declare (session 100: data_003D.h's D_003DAE40)"""
    sizes = {}
    for dp, _dn, fn in sorted(os.walk(inc)):
        for f in sorted(fn):
            if f.endswith(".h"):
                for t, n in DECL.findall(open(os.path.join(dp, f), errors="replace").read()):
                    sizes.setdefault(n, SIZE[t])
    return sizes


def scan_c(src, inc=os.path.join(ROOT, "include")):
    """the sends named in C, and every constant-index write: address -> [(word, expression, file:line)]"""
    sends, writes = {}, {}
    hsizes = header_sizes(inc)
    for path in c_sources(src):
        text = open(path, errors="replace").read()
        rel = os.path.relpath(path, ROOT)
        for m in SEND_C.finditer(text):
            sends.setdefault(m.group(1), rel)
        sizes = dict(hsizes)
        sizes.update({n: SIZE[t] for t, n in DECL.findall(text)})
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


def strip_ps2(text):
    """the text a port compiles: comments and `#ifdef KH1_PS2` (or `#ifndef`'s else) branches blanked,
    line numbers kept"""
    text = re.sub(r"/\*.*?\*/", lambda m: "\n" * m.group(0).count("\n"), text, flags=re.S)
    text = re.sub(r"//[^\n]*", "", text)
    out, stack = [], []
    for line in text.split("\n"):
        m = re.match(r"\s*#\s*(ifdef|ifndef|if|else|elif|endif)\b\s*(\S*)", line)
        if m:
            d, arg = m.groups()
            if d in ("ifdef", "ifndef", "if"):
                stack.append([arg == "KH1_PS2" and d != "if", d == "ifdef" and arg == "KH1_PS2"])
            elif d in ("else", "elif") and stack and stack[-1][0]:
                stack[-1][1] = not stack[-1][1]
            elif d == "endif" and stack:
                stack.pop()
            out.append("")
            continue
        out.append("" if any(drop for _ps2, drop in stack) else line)
    return "\n".join(out)


def literal_rects(src):
    """functions whose port C holds both a left and a right 4:3 edge literal: (file, function, line, lits)"""
    found = []
    for path in c_sources(src):
        text = strip_ps2(open(path, errors="replace").read())
        rel = os.path.relpath(path, ROOT) if path.startswith(ROOT) else path
        heads = [(m.start(), m.group(1)) for m in FUNC.finditer(text)] + [(len(text), None)]
        for (a, name), (b, _n) in zip(heads, heads[1:]):
            body = text[a:b]
            lo, hi = set(), set()
            for m in re.finditer(r"0x([0-9a-fA-F]+)", body):
                if CMP.search(body[max(0, m.start() - 4):m.start()]):
                    continue
                h = int(m.group(1), 16) & 0xFFFF
                (lo if h in LEFT else hi if h in RIGHT else set()).add(m.group(0))
            if lo and hi:
                found.append((rel, name, text.count("\n", 0, a) + 1, sorted(lo) + sorted(hi)))
    return found


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
                    g = rl[k % nreg]
                    out.append((r & 0xFF, v, a) if g == 0x0E else (g, PACKED.get(g, lambda lo, _hi: lo)(v, r), a))
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
    return sprites_of(regs(img, head))


def sprites_of(rl):
    """each SPRITE a register list draws: (x0, x1, y0, y1 in sixteenths, u span in texels, textured, XYZ
    addresses, the two vertices' x, the FRAME and XYOFFSET its context's packet set (None: the
    environment's), the FRAME's address, the context's SCISSOR (None: the environment's))"""
    out, prim, vx, uv, env, at = [], 0, [], [], {}, {}
    for r, v, a in rl:
        if r in (0x18, 0x19, 0x4C, 0x4D, 0x40, 0x41):
            env[r], at[r] = v, a
        elif r == 0x00:
            prim, vx, uv = v & 0x7FF, [], []
        elif r == 0x03:
            uv.append(gp.bits(v, 0, 14) / 16)
        elif r in XYZ_REGS:
            vx.append((gp.bits(v, 0, 16), gp.bits(v, 16, 16), a))
            if prim & 7 == 6 and len(vx) == 2:
                (xa, ya, aa), (xb, yb, ab) = vx
                du = abs(uv[-1] - uv[-2]) if len(uv) >= 2 else 0
                ctx = prim >> 9 & 1
                out.append((min(xa, xb), max(xa, xb), min(ya, yb), max(ya, yb), du, bool(prim & 0x10), (aa, ab),
                            (xa, xb), env.get(0x4C + ctx), env.get(0x18 + ctx), at.get(0x4C + ctx),
                            env.get(0x40 + ctx)))
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


def view_x(expr, side16, x):
    """a C-written XYZ word's x under the wide view, in sixteenths: its x (an xyz() / XYZ() macro's first
    argument, else the word's low halfword) with PLAT_VIEW_* at the margin; when it names a local too, the
    data's x (what the C gives on the PS2) moved by the same at the margin less at 0, the local 0 (it moves
    both alike); None when it does not evaluate"""
    if "PLAT_VIEW" not in expr:
        return x
    m = re.match(r"\s*(?:xyz|XYZ)\s*\((.*)\)\s*$", expr, re.S)
    x_expr = m.group(1) if m else expr
    if m:  # the first argument: up to the first comma at depth 0
        depth = 0
        for i, c in enumerate(x_expr):
            depth += c == "(" or -(c == ")")
            if c == "," and depth == 0:
                x_expr = x_expr[:i]
                break
    x_expr = re.sub(r"\(\s*(?:u|s)(?:8|16|32|64)\s*\)|\(\s*f32\s*\)", "", x_expr)
    x_expr = re.sub(r"\b(0x[0-9a-fA-F]+|\d+)[uUlL]+\b", r"\1", x_expr)
    names = {}

    def val(side):
        names.update({"PLAT_VIEW_SIDE16": side, "PLAT_VIEW_W16": 8192 + 2 * side, "PLAT_VIEW_GX0": X0 - side,
                      "PLAT_VIEW_GX1": X1 + side})
        e = re.sub(r"\b(?!0x)[A-Za-z_]\w*\b", lambda n: str(names.get(n.group(0), 0)), x_expr)
        if not re.fullmatch(r"[\s\dxa-fA-F()+\-*/|&<>.]*", e):
            return None
        try:
            v = eval(e.replace("/", "//"), {"__builtins__": {}})
        except (SyntaxError, ZeroDivisionError, TypeError):
            return None
        return int(v) & 0xFFFF if not m else int(v)

    a = val(side16)
    if a is None or not set(re.findall(r"\b(?!0x)[A-Za-z_]\w*\b", x_expr)) <= set(names):
        b = val(0)
        return None if a is None or b is None else x + a - b
    return a


def wide_x(p, flags, writes, side16):
    """a sprite's x range under the wide view, in sixteenths: data XYZ stretched by the send's row (KH1_FS_X
    about the canvas, KH1_FS_XS from its left edge), C-written XYZ moved by what their PLAT_VIEW_* give;
    None when a C write does not evaluate"""
    xs = []
    for x, w in zip(p[7], p[6]):
        if w in writes:
            vs = [view_x(e, side16, x) for _w, e, _at in writes[w]]
            if None in vs:
                return None
            xs += vs
        elif "KH1_FS_X" in flags:
            xs.append(X0 - side16 + (x - X0) * (8192 + 2 * side16) / 8192)
        elif "KH1_FS_XS" in flags:
            xs.append(X0 + (x - X0) * (8192 + 2 * side16) / 8192)
        else:
            xs.append(x)
    return min(xs), max(xs)


def overrun(sp, flags, writes, side16):
    """(session 107) a send drawn from its buffer's left edge past its FRAME's width (FBW x 64) under the
    wide view: (pixel x0, x1, FBW x 64) of the sprites drawn into one frame together (a set of columns is one
    picture), else None.  A send stretched over the view (its left edge before the buffer's) draws into the
    view's own target, which a port sizes to the view; one that keeps the left edge and grows to the right
    (a buffer of the PS2's width) runs into the blocks after it (5.1as).  The environment's frame (no FRAME
    in the packet) is the target or the display: the view's in a port, not checked"""
    by = {}
    for p in sp:
        if p[8] is None:
            continue
        xr = wide_x(p, flags, writes, side16)
        if xr is None:
            continue
        off = gp.bits(p[9], 0, 16) if p[9] is not None else X0
        by.setdefault(p[8] & 0xFFFFFFFF, []).append(((xr[0] - off) / 16, (xr[1] - off) / 16))
    for frame, rs in sorted(by.items()):
        px0, px1, width = min(r[0] for r in rs), max(r[1] for r in rs), gp.bits(frame, 16, 6) * 64
        if px0 >= -2 and px1 > width + 1:
            return px0, px1, width
    return None


def frame_rects(sp, flags, writes, side16, free=frozenset()):
    """(session 108) the pixel rectangle each FRAME the sprites set is drawn over: {FRAME: (x0, x1, y0, y1)},
    x under the wide view at side16 (0: the PS2); a frame drawn from before its left edge (stretched over
    the view: the port's target is the view's size) or a C write that does not evaluate is left out.
    (session 109) a sprite the view does not stretch is clipped by its context's SCISSOR when the packets
    set one, and a sprite with an XYZ word in `free` (moved by the C at run time) is its whole SCISSOR"""
    by = {}
    for p in sp:
        if p[8] is None:
            continue
        xr = wide_x(p, flags, writes, side16)
        if xr is None:
            continue
        xo = gp.bits(p[9], 0, 16) if p[9] is not None else X0
        yo = gp.bits(p[9], 32, 16) if p[9] is not None else 0x7400
        r = [(xr[0] - xo) / 16, (xr[1] - xo) / 16, (p[2] - yo) / 16, (p[3] - yo) / 16]
        sc = p[11]
        stretched = flags & {"KH1_FS_X", "KH1_FS_XS"} or any(
            "PLAT_VIEW" in e for w in p[6] for _w, e, _at in writes.get(w, ()))
        if sc is not None and not stretched:
            s4 = (gp.bits(sc, 0, 11), gp.bits(sc, 16, 11) + 1, gp.bits(sc, 32, 11), gp.bits(sc, 48, 11) + 1)
            if free & set(p[6]):
                r = list(s4)
            r = [max(r[0], s4[0]), min(r[1], s4[1]), max(r[2], s4[2]), min(r[3], s4[3])]
            if r[0] >= r[1] or r[2] >= r[3]:
                continue
        elif free & set(p[6]):
            continue
        by.setdefault(p[8] & 0xFFFFFFFF, []).append(tuple(r))
    out = {}
    for frame, rs in by.items():
        x0, x1 = min(r[0] for r in rs), max(r[1] for r in rs)
        if x0 < -2:
            continue
        out[frame] = (max(0, x0), x1, max(0, min(r[2] for r in rs)), max(r[3] for r in rs))
    return out


def blocks(frame, rect):
    """the GS memory blocks (256 bytes each) the pixel rectangle covers in the frame (FBP, FBW, PSM): x past
    FBW x 64 runs into the next pages as on the GS; None for a PSM not in PSM_BLOCKS"""
    fbp, fbw, psm = gp.bits(frame, 0, 9) * 32, gp.bits(frame, 16, 6), gp.bits(frame, 24, 6)
    if psm not in PSM_BLOCKS:
        return None
    bw, bh, order = PSM_BLOCKS[psm]
    pw, ph = bw * len(order[0]), bh * len(order)
    x0, x1, y0, y1 = int(rect[0]), int(-(-rect[1] // 1)), int(rect[2]), int(-(-rect[3] // 1))
    out = set()
    for y in range(y0 - y0 % bh, y1, bh):
        for x in range(x0 - x0 % bw, x1, bw):
            page = (y // ph) * max(fbw, 1) + x // pw
            out.add((fbp + page * 32 + order[y % ph // bh][x % pw // bw]) & 0x3FFF)
    return out


def region(b):
    return next((r for r in REGIONS if r[0] <= b < r[1]), None)


def spans(bs):
    """sorted blocks as 'lo .. hi' ranges (hi inclusive)"""
    out, run = [], None
    for b in sorted(bs):
        if run and b == run[1] + 1:
            run[1] = b
        else:
            run = [b, b]
            out.append(run)
    return ", ".join("0x%04X" % a if a == z else "0x%04X .. 0x%04X" % (a, z) for a, z in out)


def block_check(s, fn, sp, flags, writes, side16, verbose, free=frozenset(), label=None):
    """(session 108) the problems of one send's drawn blocks, and the BLOCK_EXPECTED keys it used; label
    names a variant (session 109: a run-time build) in the messages, s stays BLOCK_EXPECTED's key"""
    problems, used = [], set()
    ps2, wide = frame_rects(sp, flags, writes, 0, free), frame_rects(sp, flags, writes, side16, free)
    key, s = s, label or s
    cfr = {p[8] & 0xFFFFFFFF for p in sp if p[8] is not None and p[10] in writes}
    for frame in sorted(wide):
        bw, bp = blocks(frame, wide[frame]), blocks(frame, ps2.get(frame, wide[frame]))
        if bw is None:
            problems.append("%s (%s): FRAME PSM 0x%02X has no block order in PSM_BLOCKS" % (
                s, fn, gp.bits(frame, 24, 6)))
            continue
        own = region(gp.bits(frame, 0, 9) * 32)
        if verbose:
            print("%s (%s): FRAME FBP 0x%04X FBW %d PSM 0x%02X%s, blocks %s under the wide view (PS2: %s)" % (
                s, fn, gp.bits(frame, 0, 9) * 32, gp.bits(frame, 16, 6), gp.bits(frame, 24, 6),
                " (written from C: the data's value)" if frame in cfr else "", spans(bw), spans(bp)))
        out = bw - bp
        if out:
            if (key, "wide") in BLOCK_EXPECTED:
                used.add((key, "wide"))
            else:
                problems.append("%s (%s): under the wide view draws blocks %s, past the PS2's (%s): size its "
                                "buffer to the view or add (send, \"wide\") to BLOCK_EXPECTED" % (
                                    s, fn, spans(out), spans(bp)))
        for r in sorted({region(b) for b in bw} - {own}, key=lambda r: r[0] if r else -1):
            if r and (key, r[0]) in BLOCK_EXPECTED:
                used.add((key, r[0]))
                continue
            hit = {b for b in bw if region(b) == r}
            problems.append("%s (%s): its frame at 0x%04X (%s) draws blocks %s in %s: a live buffer, or add it "
                            "to BLOCK_EXPECTED" % (s, fn, gp.bits(frame, 0, 9) * 32, own[2] if own else "?",
                                                   spans(hit), r[2] if r else "no region"))
    return problems, used


class Overlay:
    """(session 109) the ELF's image with run-time state on top: 8-byte words the C stores ({address:
    value}) and buffers it builds ([(address, bytes)]), for regs()"""

    def __init__(self, base, words=None, bufs=()):
        self.base, self.words, self.bufs = base, dict(words or {}), list(bufs)

    def ok(self, a, n=16):
        return any(v <= a and a + n <= v + len(d) for v, d in self.bufs) or self.base.ok(a, n)

    def q(self, a):
        for v, d in self.bufs:
            if v <= a and a + 16 <= v + len(d):
                return struct.unpack_from("<QQ", d, a - v)
        lo, hi = self.base.q(a)
        return self.words.get(a, lo), self.words.get(a + 8, hi)


def c_eval(expr, names):
    """a C integer expression of literals and the given names (casts and suffixes dropped), as 64 bits;
    None when it holds anything else"""
    e = re.sub(r"\(\s*(?:u|s)(?:8|16|32|64)\s*\)", "", expr)
    e = re.sub(r"\b(0x[0-9a-fA-F]+|\d+)[uUlL]+\b", r"\1", e)
    e = re.sub(r"\b(?!0x)[A-Za-z_]\w*\b", lambda n: str(names[n.group(0)]) if n.group(0) in names else "?", e)
    if not re.fullmatch(r"[\s\dxa-fA-F()+\-*/|&<>~]*", e):
        return None
    try:
        return int(eval(e.replace("/", "//"), {"__builtins__": {}})) & (1 << 64) - 1
    except (SyntaxError, ZeroDivisionError, TypeError):
        return None


def cvar_words(s, var, value, writes, addrs):
    """(session 109) the C's writes of a send's words (addrs) with the local var = value: ({address: value},
    the words that do not evaluate). Each write's locals come from the simple `name = expr;` lines before it
    in its function, evaluated in order"""
    words, bad = {}, []
    for a in sorted(addrs & set(writes)):
        for word, expr, at in writes[a]:
            path, line = at.rsplit(":", 1)
            lines = open(os.path.join(ROOT, path), errors="replace").read().split("\n")[:int(line) - 1]
            body = []
            for ln in reversed(lines):
                if re.match(r"^[A-Za-z_].*\)\s*\{\s*$", ln):
                    break
                body.append(ln)
            names = {var: value}
            for ln in reversed(body):
                m = re.match(r"^\s*([a-z]\w*)\s*=\s*([^;=]+);\s*$", ln)
                if m and m.group(1) != var:
                    v = c_eval(m.group(2), names)
                    if v is not None:
                        names[m.group(1)] = v
            v = c_eval(expr, names)
            if v is None:
                bad.append("%s = %s (%s)" % (word, expr, at))
            else:
                words[a] = v
    return words, bad


def rt_data(img, src):
    """(session 109) RT_DATA's sends: [(name, register list, free XYZ addresses)] with the C's tag stores;
    a problem string for a file that no longer has them"""
    out, problems = [], []
    for path, chain, what in RT_DATA:
        text = open(os.path.join(src, os.path.relpath(path, "src")), errors="replace").read()
        words = {}
        for name in chain:
            a = int(name[2:], 16)
            st = {f: int(v, 0) for n, f, v in re.findall(r"\b(D_[0-9A-F]{8})\.x([034])\s*=\s*(\w+)\s*;", text)
                  if n == name}
            if "0" not in st or "3" not in st:
                problems.append("%s: %s's tag stores (.x0 / .x3) not found: %s is not walked" % (path, name, what))
                break
            lo = img.q(a)[0]
            lo = (lo & ~0xFFFF) | st["0"]
            lo = (lo & ~(0xFF << 24)) | st["3"] << 24
            if "4" in st:
                lo = (lo & 0xFFFFFFFF) | (st["4"] & 0xFFFFFFFF) << 32
            words[a] = lo
        else:
            free = set()
            m = re.search(r"\bp\s*=\s*\([^)]*\)\s*PLAT_UNCACHED\s*\(\s*&\s*(D_[0-9A-F]{8})\s*\)", text)
            if m:
                free = {int(m.group(1)[2:], 16) + int(o, 16)
                        for o in re.findall(r"\bp->x([0-9a-f]+)\s*=\s*D_[0-9A-F]{8}\.[ab]\b", text)}
            ov = Overlay(img, words)
            rl = [r for name in chain for r in regs(ov, int(name[2:], 16))]
            out.append((chain[0], "+".join(chain), rl, free, what))
    return out, problems


def rt_built(img, cc):
    """(session 109) the run-time builders' chains from tools/host/rtsends.c: [(name, variant, register
    list)], or a note why they were skipped"""
    lo, hi = img.q(0x002E27E0)
    sizes = struct.unpack("<4i", struct.pack("<QQ", lo, hi))[:3]
    args = [str(w) for w in sizes] + [str(n) for wh in CROSSFADE_SIZES for n in wh]
    with tempfile.TemporaryDirectory() as tmp:
        exe = os.path.join(tmp, "rtsends")
        cmd = [cc, "-m32", "-malign-double", "-std=gnu89", "-O1", "-w", "-fno-strict-aliasing", "-ffunction-sections",
               "-fdata-sections", "-DKH1_HOST", "-I" + os.path.join(ROOT, "include"), "-I" + os.path.join(ROOT, "src"),
               "-Wl,--gc-sections", "-o", exe] + [os.path.join(ROOT, f) for f in RT_SOURCES] + ["-lm"]
        try:
            r = subprocess.run(cmd, capture_output=True, text=True)
            if r.returncode:
                return None, "%s -m32 failed (gcc-multilib?): the run-time builders were not checked" % cc
            out = subprocess.run([exe] + args, capture_output=True, text=True, check=True).stdout
        except (OSError, subprocess.CalledProcessError) as e:
            return None, "rtsends: %s: the run-time builders were not checked" % e
    chains = {}
    for line in out.splitlines():
        f = line.split()
        if len(f) == 5 and f[0] == "CHAIN":
            va = int(f[3], 16)
            ov = Overlay(img, bufs=[(va, bytes.fromhex(f[4]))])
            chains.setdefault((f[1], f[2]), []).extend(regs(ov, va))
    return [(n, v, rl) for (n, v), rl in chains.items()], "%d run-time builds (shadow sizes %s)" % (
        len(chains), "/".join(map(str, sizes)))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", default=os.path.join(ROOT, "SLPS_251.98"))
    ap.add_argument("--layout", default=os.path.join(ROOT, "layout.tsv"))
    ap.add_argument("--table", default=os.path.join(ROOT, "host", "port", "fullscreen.c"))
    ap.add_argument("--src", default=os.path.join(ROOT, "src"))
    ap.add_argument("--side16", type=int, default=1325,
                    help="the wide view's margin in canvas sixteenths (1325: 960 x 544, host/port/view.c)")
    ap.add_argument("--cc", default=os.environ.get("CC", "gcc"), help="the host C compiler (with -m32) for "
                    "tools/host/rtsends.c")
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
    for fn, reg in OTHER_SENDERS:
        for _site, f, a in gp.callers(img, Path(args.layout), fn, reg):
            if img.ok(a):
                sends.setdefault("D_%08X" % a, "func_%08x" % f)

    problems, nfull, overs, bused, nframed = [], 0, set(), set(), 0
    for s in sorted(sends):
        a = int(s[2:], 16)
        if not img.ok(a):
            continue
        allsp = sprites(img, a)
        kind, sp = classify(allsp)
        if any(p[8] is not None for p in allsp):
            nframed += 1
            if s in CVARS:  # the C's values instead of the data's (session 109)
                var, values, _why = CVARS[s]
                addrs = {w for p in allsp for w in p[6] + (p[10],)}
                for v in values:
                    words, bad = cvar_words(s, var, v, writes, addrs)
                    problems += ["%s (%s): %s does not evaluate with %s = %d" % (s, sends[s], b, var, v) for b in bad]
                    wl = {a: e for a, e in writes.items() if a not in words}
                    bp, bu = block_check(s, sends[s], sprites(Overlay(img, words), a), rows.get(s, (set(), None))[0],
                                         wl, args.side16, args.v, label="%s (%s = %d)" % (s, var, v))
                    problems += bp
                    bused |= bu
            else:
                bp, bu = block_check(s, sends[s], allsp, rows.get(s, (set(), None))[0], writes, args.side16, args.v)
                problems += bp
                bused |= bu
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
        o = overrun([p for p, _k in sp], flags, writes, args.side16)
        if o:
            overs.add(s)
            if args.v:
                print("%s (%s): draws x %.1f .. %.1f under the wide view, past its frame's %d%s" % (
                    s, sends[s], o[0], o[1], o[2], " (expected)" if s in OVER_EXPECTED else ""))
            if s not in OVER_EXPECTED:
                problems.append("%s (%s): drawn past its frame's width under the wide view (x %.1f .. %.1f, "
                                "FBW x 64 = %d): size its buffer to the view or add it to OVER_EXPECTED" % (
                                    s, sends[s], o[0], o[1], o[2]))
        if s in EXEMPT:
            if name:
                problems.append("%s is in EXEMPT and has a row (%s)" % (s, name))
            continue
        for k, want in (("full", "KH1_FS_X"), ("half", "KH1_FS_XS")):
            n = sum(1 for _p, kk in static if kk == k)
            if n and want not in flags:
                problems.append("%s (%s): %d %s sprite(s) with XYZ in data, and no %s row in %s" % (
                    s, sends[s], n, k, want, os.path.relpath(args.table, ROOT)))
        if not static and flags & {"KH1_FS_X", "KH1_FS_XS"}:  # all from C: the C names the view instead
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
                if flags & {"KH1_FS_X", "KH1_FS_XS"}:
                    # session 100: a send stretched by its row (static sprites beside C-written ones, the
                    # stored frame's zoom) keeps canvas units in C; the view there would count twice
                    if "PLAT_VIEW" in expr:
                        problems.append("%s (%s) writes %s = %s: the view's edge in a send its row stretches "
                                        "(canvas units there)" % (where, s, word, expr))
                    continue
                if "PLAT_VIEW" in expr or any(kk == word and pp in expr for kk, pp in WRITE_EXEMPT):
                    continue
                if edge_literal(expr):
                    problems.append("%s (%s) writes %s = %s: a 4:3 edge, not the view's (PLAT_VIEW_GX0 / GX1)" % (
                        where, s, word, expr))
    # (session 109) the render-to-texture sends outside the walk: data the C finishes, then the run-time builds
    nrt = 0
    data, dp = rt_data(img, args.src)
    problems += dp
    for key, label, rl, free, what in data:
        sp = sprites_of(rl)
        nrt += 1
        bp, bu = block_check(key, what.split(":")[0], sp, set(), {}, args.side16, args.v, frozenset(free), label)
        problems += bp
        bused |= bu
    built, note = rt_built(img, args.cc)
    print("fscheck: " + note)
    for name, var, rl in built or ():
        nrt += 1
        bp, bu = block_check(name, "run time", sprites_of(rl), set(), {}, args.side16, args.v,
                             label="%s[%s]" % (name, var))
        problems += bp
        bused |= bu
    for s, (_f, name) in rows.items():
        if s not in sends:
            problems.append("%s (%s): a row in the table, but no send of it" % (s, name))
    for s in OVER_EXPECTED:
        if s not in overs:
            problems.append("%s: in OVER_EXPECTED, but no longer drawn past its frame's width" % s)
    for k in BLOCK_EXPECTED:
        if k not in bused and (built is not None or k[0] not in RT_BUILT):
            problems.append("%s: in BLOCK_EXPECTED for %s, but no longer drawn there" % (
                k[0], "0x%04X" % k[1] if k[1] != "wide" else "the wide view"))
    for s in EXEMPT:
        if s not in sends:
            problems.append("%s: in EXEMPT, but no send of it" % s)
    lits = literal_rects(args.src)
    for rel, name, line, ls in lits:
        key = "%s:%s" % (os.path.basename(rel), name)
        if args.v:
            print("%s:%d %s: both 4:3 edges as literals (%s)%s" % (rel, line, name, ", ".join(ls),
                                                                   " (exempt)" if key in LIT_EXEMPT else ""))
        if key not in LIT_EXEMPT:
            problems.append("%s:%d %s writes both 4:3 edges (%s): a full-screen rectangle built in C names the "
                            "view (PLAT_VIEW_GX0 / GX1) or is in LIT_EXEMPT" % (rel, line, name, ", ".join(ls)))
    for k in LIT_EXEMPT:
        if not any("%s:%s" % (os.path.basename(r), n) == k for r, n, _l, _ls in lits):
            problems.append("%s: in LIT_EXEMPT, but no longer writes both edges" % k)
    for p in problems:
        print("fscheck: " + p)
    print("fscheck: %d sends, %d full-screen (%d rows, %d exempt), %d C rectangles with both 4:3 edges, "
          "%d drawn past their frame's width (%d expected), %d sends setting FRAME and %d render-to-texture "
          "sends from the C (%d block overlaps expected), %d problems" % (
              len(sends), nfull, len(rows), len(EXEMPT), len(lits), len(overs), len(overs & set(OVER_EXPECTED)),
              nframed, nrt, len(bused), len(problems)))
    sys.exit(1 if problems else 0)


if __name__ == "__main__":
    main()
