#!/usr/bin/env python3
"""The renderer's state list from a host run (phase 5, docs/renderer-spec.md 4.7).

  KH1_HOST_TRACE=4 out/host/kh1-host > run.txt     (KH1_HOST_ISO=..., KH1_HOST_OVL=stub:2 ...)
  python3 -I tools/host/gsstate.py run.txt [--exe out/host/kh1-host] [--sends] [--draws] [--uploads] [--targets]
                                           [--nodes [--frame N]] [--extents [--via SYM ...]]

The run-time twin of `tools/host/dmawalk.py --state`, which reads only the chains the ELF
holds: KH1_HOST_TRACE=4 (host/null/dmawalk.c) prints after each send's line every distinct GS
state register value the send writes ("kh1-host:   gs REG VALUE"), and this collects them:
per register, each distinct value decoded (tools/vu/gs_packets.py) with the chains that send
it, named by the host symbol at the chain's start (`nm` of the host executable; "stack" /
"spr" / "heap" when the chain is not in the image).  So the text windows' buffers
(D_003F1A70 ...), built at run time and zero in the ELF, get the same census as the static
chains.  --sends adds a count of sends per chain.  --draws (a KH1_HOST_TRACE=5 run, session 79)
lists the draw states host/null/gsregs.c's register file counted ("kh1-host:   draw ..."): each
distinct PRIM + FRAME / ZBUF / TEST / ALPHA / TEX0 / CLAMP the vertex kicks drew with (the state
carried over from earlier sends included), decoded, with its kicks, primitives and the chains whose
data kicked them.  --uploads (KH1_HOST_TRACE=5, session 80) lists the transfers into GS memory
host/null/gsmem.c took ("kh1-host:   upload ..."): each distinct destination (DBP, DBW, DPSM) and
rectangle, how often, the pixels written and the chains that sent them.  --targets (session 81)
lists the render targets ("kh1-host:   target ..."): each FRAME / ZBUF the draws (and VU1 program
starts, for context 2) wrote through, its extent and primitives; --draws marks a draw state whose
texture lies in one ("texture in target N").  --nodes (session 83) lists the draw / immediate
list nodes ("kh1-host: node ..." lines, src/model/mdlgs.nostrict.c's PlatGsListNode): one frame's
command order (the last frame with a draw list, or --frame N) with each node's callback, payload,
sends, kicks and uploads, then every distinct node of the run, each checked against
tools/host/drawkeys.py's key map (a node whose list, callback and key no insert in src/ explains
is marked NOT IN THE KEY MAP).  --extents (session 91, renderer-spec 5.3.1) lists the vertices'
extent per drawing send in target pixels (XYZ less XYOFFSET, the ", xy" of a draw line): a send
from a shared staging buffer (--via, default D_00351E10, every HUD part's sprites) is keyed by the
drawing environment sent before it (`D_00651C00 > D_00351E10`: the gauges), so each HUD part gets
its own rectangle to check against 5.3.1's table, with the anchor 5.3's rule gives it.

The values come from the user's disc and ELF at run time: never commit the output.
"""
from __future__ import annotations

import argparse
import bisect
import collections
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "host"))
sys.path.insert(0, str(ROOT / "tools" / "vu"))
import gs_packets  # noqa: E402
from dmawalk import print_state  # noqa: E402

SEND = re.compile(r"^kh1-host: dma ch (\d+) chcr ([0-9a-f]{8}) tadr ([0-9a-f]{8}):")
GS = re.compile(r"^kh1-host:   gs ([0-9a-f]{2}) ([0-9a-f]{16})$")
DRAW = re.compile(r"^kh1-host:   draw prim ([0-9a-f]{3}) frame ([0-9a-f]{8}) zbuf ([0-9a-f]{8}) test ([0-9a-f]{8}) "
                  r"alpha ([0-9a-f]{16}) tex0 ([0-9a-f]{16}) clamp ([0-9a-f]{16}): (\d+) kicks, (\d+) prims"
                  r"(?:, xy (-?\d+) (-?\d+) (-?\d+) (-?\d+))?(?:, reads target (\d+))?$")
TARGET = re.compile(r"^kh1-host:   target (\d+) bp ([0-9a-f]{4}) bw (\d+) psm ([0-9a-f]{2}) rows (\d+) "
                    r"mask ([0-9a-f]{8}): (\d+) prims$")
UPLOAD = re.compile(r"^kh1-host:   upload (host|copy) dbp ([0-9a-f]{4}) dbw (\d+) dpsm ([0-9a-f]{2}) "
                    r"at (\d+),(\d+) size (\d+)x(\d+): (\d+) pixels$")
PSM = {0x00: "PSMCT32", 0x01: "PSMCT24", 0x02: "PSMCT16", 0x0A: "PSMCT16S", 0x13: "PSMT8", 0x14: "PSMT4",
       0x1B: "PSMT8H", 0x24: "PSMT4HL", 0x2C: "PSMT4HH", 0x30: "PSMZ32", 0x31: "PSMZ24", 0x32: "PSMZ16",
       0x3A: "PSMZ16S"}
DRAW_REGS = (0x00, 0x4C, 0x4E, 0x47, 0x42, 0x06, 0x08)
NODE = re.compile(r"^kh1-host: node (draw|imm) (-?\d+) cb ([0-9a-f]{8}) arg ([0-9a-f]{8})$")
NODE_MAIN = "kh1-host: node main"
VBLANK = re.compile(r"^kh1-host: vblank (\d+)$")
LIST_END = re.compile(r"^kh1-host: list (draw|imm) end: (\d+) nodes, frame (\d+)$")
KICKS = re.compile(r"^kh1-host:   draw prim .*: (\d+) kicks, (\d+) prims")
VIA = ("D_00351E10",)  # the HUD's staging buffer (src/hud: every part's sprites are built and sent there)


def anchor(x0: float, y0: float, x1: float, y1: float) -> str:
    """renderer-spec 5.3 step 2's rule on a 512 x 384 rectangle: a third of each side"""
    if x0 <= 0 and x1 >= 511 and y0 <= 0 and y1 >= 383:
        return "full screen"
    h = "right" if x0 >= 512 * 2 / 3 else "left" if x1 <= 512 / 3 else "centre"
    v = "bottom" if y0 >= 384 * 2 / 3 else "top" if y1 <= 384 / 3 else "middle"
    return h + ", " + v


def print_extents(extents) -> None:
    """extents: key -> [sends, prims, x0, y0, x1, y1, {frame: None}] in 1/16 pixels"""
    print("# drawn extents per send (KH1_HOST_TRACE=5; target pixels from XYOFFSET, renderer-spec 5.3.1): %d"
          % len(extents))
    for key, (n, prims, x0, y0, x1, y1, frames) in sorted(extents.items(), key=lambda kv: (kv[1][3], kv[1][2])):
        f = sorted(frames)
        r = tuple(v / 16 for v in (x0, y0, x1, y1))
        print("\t(%7.1f, %7.1f)-(%7.1f, %7.1f)  %-13s %5d sends %6d prims  frames %d-%d  %s" % (
            r + (anchor(*r), n, prims, f[0], f[-1], key)))


def print_uploads(uploads) -> None:
    """uploads: (kind, dbp, dbw, dpsm, x, y, w, h) -> [count, pixels, {chain: None}]"""
    print("# uploads into GS memory (KH1_HOST_TRACE=5): %d distinct" % len(uploads))
    for (kind, dbp, dbw, psm, x, y, w, h), (n, px, chains) in sorted(uploads.items(), key=lambda kv: kv[0][1:]):
        short = "" if px == n * w * h else " (SHORT: %d of %d pixels)" % (px, n * w * h)
        print("\t%s DBP 0x%04x DBW %d %s at (%d, %d) %dx%d: %d time(s)%s  %s" % (
            kind, dbp, dbw, PSM.get(psm, "psm%02x" % psm), x, y, w, h, n, short, ", ".join(chains)))


def print_targets(targets) -> None:
    """targets: number -> [bp, bw, psm, rows, mask, prims, {chain: None}] (the last line's extent)"""
    print("# render targets (KH1_HOST_TRACE=5, host/null/gsmem.c): %d" % len(targets))
    for n, (bp, bw, psm, rows, mask, prims, chains) in sorted(targets.items()):
        print("\ttarget %d: block 0x%04x (page 0x%03x) FBW %d %s %d rows, bits %08x: %d prims  %s" % (
            n, bp, bp // 32, bw, PSM.get(psm, "psm%02x" % psm), rows, mask, prims, ", ".join(chains)))


def print_draws(draws) -> None:
    """draws: (prim, frame, zbuf, test, alpha, tex0, clamp) -> [kicks, prims, {chain: None}, {target: None}]"""
    print("# draw states (KH1_HOST_TRACE=5): %d" % len(draws))
    for key, (kicks, prims, chains, targets) in sorted(draws.items(), key=lambda kv: -kv[1][0]):
        reads = "  (texture in target %s)" % ", ".join(map(str, sorted(targets))) if targets else ""
        print("%6d kicks %6d prims  %s%s" % (kicks, prims, " ".join(sorted(chains)), reads))
        for reg, v in zip(DRAW_REGS, key):
            if reg != 0x00 and not v:
                continue  # not read by this draw (gsregs.c leaves it 0)
            print("\t%-10s %s" % (gs_packets.GSREG.get(reg, "reg%02x" % reg), gs_packets.decode(reg, v)))


class Syms:
    def __init__(self, exe: Path, kinds: str = "bBdDrR"):
        out = subprocess.run(["nm", "-n", str(exe)], capture_output=True, text=True, check=True).stdout
        rows = []
        for line in out.splitlines():
            f = line.split()
            if len(f) == 3 and f[1] in kinds and not f[2].startswith("."):
                rows.append((int(f[0], 16), f[2]))
        self.addr = [a for a, _ in rows]
        self.name = [n for _, n in rows]
        m = re.search(r"^([0-9a-f]+) [A-Za-z] end$", out, re.M)
        self.end = int(m.group(1), 16) if m else (self.addr[-1] + 0x100000 if self.addr else 0)

    def at(self, a: int) -> str:
        i = bisect.bisect_right(self.addr, a) - 1
        if i < 0 or a >= self.end:
            return "stack" if a >= 0xF0000000 else "heap"
        off = a - self.addr[i]
        return self.name[i] + ("+%#x" % off if off else "")


def key_map() -> list[tuple]:
    """tools/host/drawkeys.py's rows: (list, key, var, callback, payload)"""
    import tempfile
    with tempfile.TemporaryDirectory() as d:
        tsv = Path(d) / "keys.tsv"
        subprocess.run([sys.executable, "-I", str(ROOT / "tools/host/drawkeys.py"), "--tsv", str(tsv)],
                       capture_output=True, text=True, check=True)
        rows = []
        for line in tsv.read_text().splitlines()[1:]:
            f = line.split("\t")
            rows.append(("imm" if f[2] == "immediate" else "draw", int(f[0], 16), f[1], f[3], f[4]))
    return rows


def explain(rows, lst: str, key: int, cb: str, arg: str) -> str:
    """the drawkeys row that explains a node, or ''"""
    if cb == "func_0015ff78":
        return "renderer B entry (e->x28, data-driven)"
    ok = [r for r in rows if r[0] == lst and r[3] in (cb, "fn") and (not r[4] or r[4] == arg)]
    for rl, rk, var, rcb, payload in ok:  # a literal key first
        if (var.startswith(" ") or not var) and key == rk:
            return "0x%X%s" % (rk, var)
    for rl, rk, var, rcb, payload in ok:  # literal + a variable (a running count, texanim's 10 id)
        if var and not var.startswith(" ") and key >= rk:
            return "0x%X+%s" % (rk, var)
    return ""


def print_nodes(nodes, events, frame, fns: Syms, data: Syms) -> None:
    """nodes: list of dicts in run order; events: frame -> [node dict or a main-thread send's chain]"""
    if frame is None:
        frame = max((f for f, ev in events.items() if any(isinstance(e, dict) and e["list"] == "draw" for e in ev)),
                    default=None)
    print("# draw / immediate list nodes (KH1_HOST_TRACE=5): %d run" % len(nodes))
    if frame is not None and frame in events:
        print("# frame %d's command order (list, key, callback, payload: sends, kicks, prims, uploads; main = "
              "main-thread sends outside the lists)" % frame)
        ev = events[frame]
        i = 0
        while i < len(ev):
            n = ev[i]
            if not isinstance(n, dict):
                j = i
                while j < len(ev) and not isinstance(ev[j], dict):
                    j += 1
                chains = list(dict.fromkeys(ev[i:j]))
                print("\tmain %2d sends: %s%s" % (j - i, ", ".join(chains[:6]), " ..." if len(chains) > 6 else ""))
                i = j
                continue
            print("\t%-4s %10d  0x%-8X %-15s %-14s %2d sends %5d kicks %5d prims %2d uploads%s" % (
                n["list"], n["key"], n["key"] & 0xFFFFFFFF, fns.at(n["cb"]), data.at(n["arg"]) if n["arg"] else "-",
                n["sends"], n["kicks"], n["prims"], n["uploads"], "" if n["why"] else "  NOT IN THE KEY MAP"))
            i += 1
    else:
        print("# no frame with a draw list%s" % ("" if frame is None else " (frame %d)" % frame))
    seen = {}
    for n in nodes:
        k = (n["list"], n["key"], n["cb"], n["arg"])
        d = seen.setdefault(k, [0, 0, 0, 0, n["why"]])
        d[0] += 1
        d[1] += n["sends"]
        d[2] += n["kicks"]
        d[3] += n["uploads"]
    print("# distinct nodes (list, key, callback, payload: runs, sends, kicks, uploads; the key map row)")
    bad = 0
    for (lst, key, cb, arg), (runs, sends, kicks, ups, why) in sorted(seen.items(), key=lambda kv: (kv[0][0] != "draw", kv[0][1])):
        bad += not why
        print("\t%-4s %10d  %-15s %-14s %4d runs %5d sends %6d kicks %4d uploads  %s" % (
            lst, key, fns.at(cb), data.at(arg) if arg else "-", runs, sends, kicks, ups, why or "NOT IN THE KEY MAP"))
    print("# %d distinct nodes, %d not in the key map" % (len(seen), bad))


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("log", type=Path, help="a KH1_HOST_TRACE=4 run's output")
    ap.add_argument("--exe", type=Path, default=ROOT / "out/host/kh1-host")
    ap.add_argument("--sends", action="store_true", help="also the number of sends per chain")
    ap.add_argument("--draws", action="store_true", help="also the draw states (a KH1_HOST_TRACE=5 run)")
    ap.add_argument("--uploads", action="store_true", help="also the uploads into GS memory (KH1_HOST_TRACE=5)")
    ap.add_argument("--targets", action="store_true", help="also the render targets drawn into (KH1_HOST_TRACE=5)")
    ap.add_argument("--nodes", action="store_true", help="also the draw / immediate list nodes (KH1_HOST_TRACE=5)")
    ap.add_argument("--frame", type=int, help="with --nodes: the frame whose command order to print")
    ap.add_argument("--extents", action="store_true", help="also the drawn rectangle per send (KH1_HOST_TRACE=5)")
    ap.add_argument("--via", action="append", help="a staging buffer keyed by the send before it (default %s)"
                    % ", ".join(VIA))
    a = ap.parse_args()
    syms = Syms(a.exe)
    state = collections.defaultdict(dict)
    sends = collections.Counter()
    draws = {}
    uploads = {}
    targets = {}
    extents = {}
    via = tuple(a.via or VIA)
    ext, ext_new = None, False
    env = None  # the last send not from a staging buffer: what keys a staging send's extent
    nodes, events, vframe = [], {}, 0  # events: frame -> nodes and main-thread sends, in run order
    node = None  # the node whose sends these are
    cur, nsend, nval = None, 0, 0
    for line in a.log.read_text(errors="replace").splitlines():
        m = SEND.match(line)
        if m:
            ch, tadr = int(m.group(1)), int(m.group(3), 16)
            cur = "%s ch%d" % (syms.at(tadr), ch)
            base = cur.split("+")[0].split(" ")[0]
            if base in via:
                ext = "%s > %s" % (env or "?", cur)
            else:
                ext, env = cur, cur
            ext_new = True
            sends[cur] += 1
            nsend += 1
            if node is not None:
                node["sends"] += 1
            else:
                events.setdefault(vframe, []).append(cur)
            continue
        m = VBLANK.match(line)
        if m:
            vframe, node, cur, env = int(m.group(1)), None, None, None
            continue
        m = NODE.match(line)
        if m:
            node = {"list": m.group(1), "key": int(m.group(2)), "cb": int(m.group(3), 16), "arg": int(m.group(4), 16),
                    "sends": 0, "kicks": 0, "prims": 0, "uploads": 0}
            nodes.append(node)
            events.setdefault(vframe, []).append(node)
            cur = None
            continue
        if line == NODE_MAIN:
            node, cur = None, None
            continue
        if LIST_END.match(line):
            node, cur = None, None
            continue
        if node is not None and cur:
            k = KICKS.match(line)
            if k:
                node["kicks"] += int(k.group(1))
                node["prims"] += int(k.group(2))
            elif UPLOAD.match(line):
                node["uploads"] += 1
        m = GS.match(line)
        if m and cur:
            reg, v = int(m.group(1), 16), int(m.group(2), 16)
            state[gs_packets.GSREG.get(reg, "reg%02x" % reg)].setdefault(v, {})[cur] = None
            nval += 1
            continue
        m = DRAW.match(line)
        if m and cur:
            key = tuple(int(m.group(i), 16) for i in range(1, 8))
            d = draws.setdefault(key, [0, 0, {}, {}])
            d[0] += int(m.group(8))
            d[1] += int(m.group(9))
            d[2][cur] = None
            if m.group(14):
                d[3][int(m.group(14))] = None
            if m.group(10) and int(m.group(9)):
                xy = [int(m.group(i)) for i in range(10, 14)]
                e = extents.setdefault(ext, [0, 0, xy[0], xy[1], xy[2], xy[3], {}])
                e[0] += ext_new
                ext_new = False
                e[1] += int(m.group(9))
                e[2], e[3] = min(e[2], xy[0]), min(e[3], xy[1])
                e[4], e[5] = max(e[4], xy[2]), max(e[5], xy[3])
                e[6][vframe] = None
            continue
        m = TARGET.match(line)
        if m and cur:
            n = int(m.group(1))
            t = targets.setdefault(n, [0, 0, 0, 0, 0, 0, {}])
            t[:5] = [int(m.group(2), 16), int(m.group(3)), int(m.group(4), 16), int(m.group(5)),
                     int(m.group(6), 16)]
            t[5] += int(m.group(7))
            t[6][cur] = None
            continue
        m = UPLOAD.match(line)
        if m and cur:
            key = (m.group(1), int(m.group(2), 16), int(m.group(3)), int(m.group(4), 16)) + tuple(
                int(m.group(i)) for i in range(5, 9))
            u = uploads.setdefault(key, [0, 0, {}])
            u[0] += 1
            u[1] += int(m.group(9))
            u[2][cur] = None
        elif not line.startswith("kh1-host:   "):
            cur = None
    if not nsend:
        sys.exit("gsstate: no send lines in %s (run with KH1_HOST_TRACE=4)" % a.log)
    if not nval:
        print("gsstate: no gs lines: the run's trace level was below 4", file=sys.stderr)
    print_state(state)
    if a.sends:
        print("# sends per chain")
        for c, n in sends.most_common():
            print("\t%5d  %s" % (n, c))
    if a.draws:
        if not draws:
            print("gsstate: no draw lines: the run's trace level was below 5", file=sys.stderr)
        print_draws(draws)
    if a.uploads:
        if not uploads:
            print("gsstate: no upload lines (trace level below 5, or no uploads)", file=sys.stderr)
        print_uploads(uploads)
    if a.targets:
        if not targets:
            print("gsstate: no target lines (trace level below 5, or nothing drawn)", file=sys.stderr)
        print_targets(targets)
    if a.extents:
        if not extents:
            print("gsstate: no draw extents (trace level below 5, or a host built before session 91)", file=sys.stderr)
        print_extents(extents)
    if a.nodes:
        if not nodes:
            print("gsstate: no node lines (trace level below 5, or no list ran)", file=sys.stderr)
        rows = key_map()
        fns = Syms(a.exe, "tTwW")
        for n in nodes:
            n["why"] = explain(rows, n["list"], n["key"], fns.at(n["cb"]), syms.at(n["arg"]) if n["arg"] else "")
        print_nodes(nodes, events, a.frame, fns, syms)
    print("# %d sends, %d chains, %d registers, %d distinct values" % (
        nsend, len(sends), len(state), sum(len(v) for v in state.values())), file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
