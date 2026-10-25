#!/usr/bin/env python3
"""The GPU pipelines the game's draw states need (phase 5, docs/renderer-spec.md 4.13 "Session 123").

  python3 -I tools/host/drawpipes.py [--elf SLPS_251.98] [--no-c] [-v]

Walks every static send's GIF packets the way tools/host/dmawalk.py --state does (the same chains, seeds
and receivers) and takes, at each drawing kick (an XYZ(F)2 that fills the vertex queue for the PRIM in
force: POINT 1, LINE / LINESTRIP / SPRITE 2, triangles 3; a strip keeps its last vertices, a PRIM write
empties the queue, an XYZ(F)3 adds without drawing), the registers that draw reads: PRIM, the context
CTXT picks (FRAME, ZBUF, TEST, ALPHA, TEX0, TEX1, CLAMP), FOGCOL and TEXA.  A register the send does not
write is the drawing environment's (ENV: D_004D8EF0's values, renderer-spec 4.7, and the TEX0 renderer B
leaves in the slot), so a 2D packet that sets only TEST / ALPHA / TEX0 draws into the 3D target with
its Z24 buffer.  The draw states the C builds at run time are added from C_STATES (renderers A and B,
the HUD's environment, the shadow pass: renderer-spec 3.2 / 4.7 / 4.11), each marked with its source;
--no-c leaves them out.  Each distinct state goes through host/port/drawstate.c (tools/host/pipecount.c,
compiled here with gcc into out/host/) and the result is the table of GPU pipelines and fragment shaders
with the senders that use each.  -v lists every state with its pipelines.

Needs the user's ELF (the packets are its data); prints counts, names and decoded keys, never packet bytes.
"""
from __future__ import annotations

import argparse
import collections
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "host"))
sys.path.insert(0, str(ROOT / "tools" / "vu"))
import dmawalk  # noqa: E402

ORDER = ["PRIM", "FRAME", "ZBUF", "TEST", "ALPHA", "TEX0", "TEX1", "CLAMP", "FOGCOL", "TEXA"]
# the drawing environment a send's packets start from (renderer-spec 3.1 / 4.7: D_004D8EF0, both contexts):
# FRAME 0x800D0 (the 3D target, CT32), ZBUF 0x31000070 (Z24, ZMSK 0), TEST 0x5000D (ATST GREATER 0, ZTST
# GEQUAL), ALPHA 0x44, TEX1 0x60 (bilinear), CLAMP 5 (CLAMP / CLAMP), TEXA TA0 0x80; TEX0 renderer B's
# default 0x2006E005DD313600 (PSMT8 128 x 128 at 0x3600, CLUT 0x3700)
ENV = {"FRAME": 0x800D0, "ZBUF": 0x31000070, "TEST": 0x5000D, "ALPHA": 0x44, "TEX0": 0x2006E005DD313600,
       "TEX1": 0x60, "CLAMP": 5, "FOGCOL": 0, "TEXA": 0x80}
CTX = {"FRAME", "ZBUF", "TEST", "ALPHA", "TEX0", "TEX1", "CLAMP"}
NEED = [1, 2, 2, 3, 3, 3, 2, 0]   # vertices a PRIM type's first drawing kick needs (7: none)
STRIP = {2: 1, 4: 2, 5: 2}        # LINESTRIP / TRISTRIP / TRIFAN keep their last 1 / 2 (a fan its first)


def c_states():
    """the draw states the C builds at run time: (sender, {register: value}) over ENV"""
    out = []
    # renderer A (renderer-spec 4.11): its meshes' tags draw TRISTRIP | IIP | TME (+ FGE, ABE) in context 2
    # (the clipped polygons TRIFAN: the same pipeline), field.c's grid environments set TEST_2 0x5000D,
    # 0x5010D (AREF 16), 0x507FD (AREF 127), ZBUF_2 ZMSK 1 for the translucent pass (key 50000), ALPHA_2 0x44,
    # TEX1_2 0x60; the meshes' TEX0_2 / CLAMP_2 come with the disc's models (PSMT8 + CT32 and REPEAT here: a
    # guess the real-disc run checks), the tags' FGE from the model
    for fge in (0, 1):
        for test, zmsk in ((0x5000D, 0), (0x5010D, 0), (0x507FD, 0), (0x5000D, 1)):
            out.append(("renderer A (field.c grid, TEST_2 %#x%s%s)" % (test, ", ZMSK 1" if zmsk else "",
                                                                       ", FGE" if fge else ""),
                        {"PRIM": 0x25C | fge << 5 | 1 << 9, "TEST": test, "ZBUF": 0x31000070 | zmsk << 32,
                         "CLAMP": 0}))
    # renderer A's TEST_2 0x31001 (ATST NEVER, AFAIL FB_ONLY: colour only, no Z) section of 4.11
    out.append(("renderer A (TEST_2 0x31001)", {"PRIM": 0x25C | 1 << 9, "TEST": 0x31001, "CLAMP": 0}))
    # renderer B (mdlgs.nostrict.c func_0015f128 / func_0015f488, renderer-spec 3.2): TRIFAN | IIP | TME |
    # FGE | ABE in context 1, pass 1 ATST GEQUAL AREF min(k, 120) ZTST GEQUAL, pass 2 ATST LESS AREF k with
    # ZMSK 1, ALPHA 0x44 or the default (0 - 0) x FIX + Cs (FIX 0x80), TEX0 PSMT8 CLUT CT32, CLAMP 5,
    # FOGCOL per draw
    for alpha in (0x44, 0x800000002A):
        out.append(("renderer B pass 1 (ALPHA %#x)" % alpha,
                    {"PRIM": 0x7D, "TEST": 0x5080B, "ALPHA": alpha, "FOGCOL": 0x808080}))
        out.append(("renderer B pass 2 (ALPHA %#x)" % alpha,
                    {"PRIM": 0x7D, "TEST": 0x50805, "ZBUF": 0x31000070 | 1 << 32, "ALPHA": alpha,
                     "FOGCOL": 0x808080}))
    # the HUD's default environment func_002370c8 (4.7): TEST_1 0x30003 (ALWAYS / ALWAYS), TEXA 0x80 / 0x80,
    # its parts' SPRITE | TME | FST and TRIANGLE | IIP | TME | FST (func_002388b8's gauges), ALPHA 0x44 or the
    # numbers' 0x48 (FIX 0x80), PSMT4 / PSMT8 pictures with ABE
    for prim in (0x156, 0x15B):
        for alpha in (0x44, 0x8000000048):
            for tex0 in (0x2002A00521423A00 & ~(63 << 20) | 0x14 << 20, 0x2002A00521423A00 & ~(63 << 20) | 0x13 << 20):
                out.append(("HUD (func_002370c8, PRIM %#x, ALPHA %#x, PSM %#x)" % (prim, alpha, tex0 >> 20 & 63),
                            {"PRIM": prim, "TEST": 0x30003, "ALPHA": alpha, "TEX0": tex0,
                             "TEXA": 0x80 | 0x80 << 32}))
    # the shadow (shadow.c, renderer-spec 3.4 / 4.11): the casters draw into the 0x3A00 buffer (FRAME 0x401D0
    # FBW 4) with Z16S at 0x3800 under func_001284a0's environment, TEST 0x5000D (their PRIM a guess:
    # TRISTRIP | IIP in context 2, untextured); the receivers' batches (PRIM 0x312E4000's TRISTRIP | IIP | TME |
    # ABE | CTXT2) sample it with func_00128738's TEX0 (CT32 256 x 256), TEX1 0x61, CLAMP REGION_CLAMP and
    # ALPHA 0x44 (FIX 0x80)
    out.append(("shadow casters (func_001284a0's environment; PRIM a guess)",
                {"PRIM": 0x20C, "FRAME": 0x1000401D0, "ZBUF": 0x3A0001C0, "TEST": 0x5000D}))
    out.append(("shadow receivers (func_00128738)",
                {"PRIM": 0x25C, "TEX0": 0x2000000620013A00, "TEX1": 0x61, "CLAMP": 0xA | 1 << 4 | 254 << 14 |
                 1 << 24 | 254 << 34, "ALPHA": 0x8000000044}))
    return out


def kicks(seq):
    """the register sets at each drawing kick of one send's GIF writes (seq: dmawalk.Gif.seq)"""
    regs = {1: {}, 2: {}}
    glob = {}
    prim, n = 0, 0
    for name, v in seq:
        if name == "PRIM":
            prim, n = v & 0x7FF, 0
            continue
        if name in ("XYZ2", "XYZF2", "XYZ3", "XYZF3"):
            t = prim & 7
            need = NEED[t]
            if not need:
                continue
            n += 1
            if n < need:
                continue
            if name in ("XYZ3", "XYZF3"):
                n = need - 1 if t in STRIP else 0
                continue
            c = 2 if prim >> 9 & 1 else 1
            yield prim, {**ENV, **{k: glob[k] for k in glob}, **regs[c]}
            n = need - 1 if t in STRIP else 0
            continue
        base, _, ctx = name.partition("_")
        if base in CTX and ctx in ("1", "2"):
            regs[int(ctx)][base] = v
        elif name in ("FOGCOL", "TEXA"):
            glob[name] = v


def state_words(prim, r):
    w = [prim]
    for k in ORDER[1:]:
        v = r[k]
        if k == "TEST":
            w.append(v & 0xFFFFFFFF)
        elif k == "FOGCOL":
            w.append(v & 0xFFFFFF)
        else:
            w += [v & 0xFFFFFFFF, v >> 32 & 0xFFFFFFFF]
    return tuple(w)


def build_counter() -> Path:
    exe = ROOT / "out" / "host" / "pipecount"
    srcs = [ROOT / "tools/host/pipecount.c"] + [ROOT / "host/port" / f for f in
                                                ("drawstate.c", "blend.c", "atest.c", "depth.c", "sampler.c",
                                                 "texfmt.c", "primasm.c")]
    if exe.exists() and all(exe.stat().st_mtime >= s.stat().st_mtime for s in srcs) and \
            exe.stat().st_mtime >= (ROOT / "include/platform/drawstate.h").stat().st_mtime:
        return exe
    exe.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run(["gcc", "-m32", "-malign-double", "-std=gnu89", "-O1", "-w", "-DKH1_HOST",
                    "-I" + str(ROOT / "include"), "-o", str(exe)] + [str(s) for s in srcs], check=True)
    return exe


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--elf", type=Path, default=ROOT / "SLPS_251.98")
    ap.add_argument("--no-c", action="store_true", help="the static packets only (no C_STATES)")
    ap.add_argument("-v", action="store_true", help="every draw state with its pipelines")
    a = ap.parse_args()
    if not (ROOT / "out/gen/data.tsv").exists():
        sys.exit("drawpipes: out/gen/data.tsv is missing: run make first")
    img, names = dmawalk.Image(a.elf), dmawalk.Names.ps2()
    dmawalk.apply_seeds(img, lambda n: names.by_name[n][0] if n in names.by_name else int(n[2:], 16), names)
    states = collections.OrderedDict()   # words -> {sender: None}
    walked, sends = {}, 0
    for call, fn, ch, tte, starts, kind in dmawalk.static_sends(img, names):
        if ch is None:
            continue
        for sname, start in starts:
            if img.kind(start) != "elf" or img.read(start, 16) == bytes(16):
                continue
            key = (start, ch, tte)
            if key not in walked:
                walked[key] = dmawalk.walk(img, start, ch, tte)
            tags, probs, rx, notes = walked[key]
            if probs or rx is None:
                continue
            g = rx if isinstance(rx, dmawalk.Gif) else rx.gif
            sends += 1
            for prim, r in kicks(g.seq):
                states.setdefault(state_words(prim, r), {})[fn.split(" via ")[0]] = None
    nstatic = len(states)
    if not a.no_c:
        for who, regs in c_states():
            r = {**ENV, **regs}
            states.setdefault(state_words(r["PRIM"], r), {})["C: " + who] = None
    exe = build_counter()
    text = "".join(" ".join("%x" % x for x in w) + "\n" for w in states)
    out = subprocess.run([str(exe)], input=text, capture_output=True, text=True, check=True).stdout.splitlines()
    users = collections.defaultdict(dict)
    rows = []
    for (w, who), line in zip(states.items(), out):
        ps = line.split(":", 1)[1].split()
        rows.append((w, who, ps))
        for p in ps:
            if p.isdigit():
                for s in who:
                    users[int(p)][s] = None
    print("# %d static sends walked, %d distinct draw states from their packets, %d from the C (C_STATES)" %
          (sends, nstatic, len(states) - nstatic))
    for line in out[len(states):]:
        if line.startswith("pipe "):
            n = int(line.split()[1].rstrip(":"))
            who = sorted(users[n])
            print("%s\n\t%d senders: %s%s" % (line, len(who), " ".join(who[:8]), " ..." if len(who) > 8 else ""))
        else:
            print(line)
    if a.v:
        for w, who, ps in rows:
            print("state prim %03x frame %08x zbuf %08x/%x test %08x alpha %08x/%x tex0 %08x%08x: %s  %s" % (
                w[0], w[1], w[3], w[4], w[5], w[6], w[7], w[9], w[8], " ".join(ps), " ".join(sorted(who))))
    return 0


if __name__ == "__main__":
    sys.exit(main())
