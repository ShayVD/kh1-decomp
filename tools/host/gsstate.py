#!/usr/bin/env python3
"""The renderer's state list from a host run (phase 5, docs/renderer-spec.md 4.7).

  KH1_HOST_TRACE=4 out/host/kh1-host > run.txt     (KH1_HOST_ISO=..., KH1_HOST_OVL=stub:2 ...)
  python3 -I tools/host/gsstate.py run.txt [--exe out/host/kh1-host] [--sends] [--draws]

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
data kicked them.

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
                  r"alpha ([0-9a-f]{16}) tex0 ([0-9a-f]{16}) clamp ([0-9a-f]{16}): (\d+) kicks, (\d+) prims$")
DRAW_REGS = (0x00, 0x4C, 0x4E, 0x47, 0x42, 0x06, 0x08)


def print_draws(draws) -> None:
    """draws: (prim, frame, zbuf, test, alpha, tex0, clamp) -> [kicks, prims, {chain: None}]"""
    print("# draw states (KH1_HOST_TRACE=5): %d" % len(draws))
    for key, (kicks, prims, chains) in sorted(draws.items(), key=lambda kv: -kv[1][0]):
        print("%6d kicks %6d prims  %s" % (kicks, prims, " ".join(sorted(chains))))
        for reg, v in zip(DRAW_REGS, key):
            if reg != 0x00 and not v:
                continue  # not read by this draw (gsregs.c leaves it 0)
            print("\t%-10s %s" % (gs_packets.GSREG.get(reg, "reg%02x" % reg), gs_packets.decode(reg, v)))


class Syms:
    def __init__(self, exe: Path):
        out = subprocess.run(["nm", "-n", str(exe)], capture_output=True, text=True, check=True).stdout
        rows = []
        for line in out.splitlines():
            f = line.split()
            if len(f) == 3 and f[1] in "bBdDrR" and not f[2].startswith("."):
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


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("log", type=Path, help="a KH1_HOST_TRACE=4 run's output")
    ap.add_argument("--exe", type=Path, default=ROOT / "out/host/kh1-host")
    ap.add_argument("--sends", action="store_true", help="also the number of sends per chain")
    ap.add_argument("--draws", action="store_true", help="also the draw states (a KH1_HOST_TRACE=5 run)")
    a = ap.parse_args()
    syms = Syms(a.exe)
    state = collections.defaultdict(dict)
    sends = collections.Counter()
    draws = {}
    cur, nsend, nval = None, 0, 0
    for line in a.log.read_text(errors="replace").splitlines():
        m = SEND.match(line)
        if m:
            ch, tadr = int(m.group(1)), int(m.group(3), 16)
            cur = "%s ch%d" % (syms.at(tadr), ch)
            sends[cur] += 1
            nsend += 1
            continue
        m = GS.match(line)
        if m and cur:
            reg, v = int(m.group(1), 16), int(m.group(2), 16)
            state[gs_packets.GSREG.get(reg, "reg%02x" % reg)].setdefault(v, {})[cur] = None
            nval += 1
            continue
        m = DRAW.match(line)
        if m and cur:
            key = tuple(int(m.group(i), 16) for i in range(1, 8))
            d = draws.setdefault(key, [0, 0, {}])
            d[0] += int(m.group(8))
            d[1] += int(m.group(9))
            d[2][cur] = None
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
    print("# %d sends, %d chains, %d registers, %d distinct values" % (
        nsend, len(sends), len(state), sum(len(v) for v in state.values())), file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
