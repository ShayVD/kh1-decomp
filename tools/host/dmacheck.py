#!/usr/bin/env python3
"""List the DMA sends and the DMA addresses built by hand (phase 5, docs/vita-port-plan.md 5.1l).

  python3 -I tools/host/dmacheck.py [--list] [--tsv out/host/dmacheck.tsv]

The Vita renderer walks every chain PlatDmaSend is given (platform/dma.h); the
null platform does not, so a chain the host cannot walk shows nowhere else.
Two parts, read from the source (src/, not the SDK):

Rows (the default output, exit 1 when there are any): a DMA address built
with the PS2's masks instead of platform/dma.h's macros.  `(p & 0x0fffffff) |
0x80000000` (the scratchpad form of a tag address, PLAT_DMA_SPR_ADDR), `p &
0x0fffffff` (a physical address, PLAT_DMA_ADDR), `| 0x80000000` on an address
(PLAT_DMA_SPR) and the scratchpad's own bounds 0x70000000 / 0x70004000 stored
as an address (PLAT_SPR_BASE / PLAT_SPR_END).  On the host and the Vita a
pointer is not a PS2 address: the masks cut it.  DMA tag words (an id in bits
28-30: `n | 0x70000000` is an end tag) are not addresses and are not rows.

--list: every PlatDmaSend call, with its function and where the chain comes
from: a static name (its PS2 address and object; a data piece or a bss
definition), a scratchpad frame (heap.c's func_00122048, opdma.c's stacks), or
a pointer (a parameter, a field, a caller's buffer), for the renderer work.
Only names and source text are printed, no game bytes."""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

# (rx, macro): hand-built DMA addresses
MASKS = [
    (re.compile(r"&\s*0x0fffffff\s*\)\s*\|\s*0x80000000", re.I), "PLAT_DMA_SPR_ADDR"),
    (re.compile(r"&\s*0x0fffffff\b(?!\s*\)\s*\|)", re.I), "PLAT_DMA_ADDR"),
    (re.compile(r"\b\w+\s*\|\s*0x80000000\s*;"), "PLAT_DMA_SPR"),
    (re.compile(r"=\s*0x7000(?:0000|4000)\s*;"), "PLAT_SPR_BASE / PLAT_SPR_END"),
]
# Lines read by hand that look like a row and are not one: (file, text) -> why.
REVIEWED = {
    ("src/ppp/pppsys.c", "s->time = 0x70000000;"): "a frame count (a large time), not an address",
    ("src/ppp/pppsys.nostrict.c", "o->frame = 0x70000000;"): "a frame count, not an address",
    ("src/gfx/opdma.c", "p->s.w0 = 0x70000000;"): "an end tag's first word (id 7, qwc 0)",
    ("src/screen/wave.c", "e->w = 0x70000000;"): "the packet's end tag (id 7, qwc 0)",
}
SPR_FRAMES = ("func_00122048", "PLAT_DMA_SPR", "func_001aa950", "kkPush")


def sources():
    for f in sorted((ROOT / "src").rglob("*.c")):
        if "sdk" in f.relative_to(ROOT).parts:
            continue
        yield str(f.relative_to(ROOT)), f.read_text(errors="replace")


def mask_rows():
    rows = []
    for rel, t in sources():
        for n, ln in enumerate(t.split("\n"), 1):
            s = ln.strip()
            if s.startswith(("/*", "*", "//")) or (rel, s) in REVIEWED:
                continue
            for rx, macro in MASKS:
                if rx.search(s):
                    rows.append((rel, n, macro, s))
                    break
    return rows


def split_args(t, i):
    """the two arguments of the call whose '(' is just before t[i], and the index after it"""
    d, j, comma = 1, i, None
    while d:
        c = t[j]
        if c in "([":
            d += 1
        elif c in ")]":
            d -= 1
        elif c == "," and d == 1 and comma is None:
            comma = j
        j += 1
    return " ".join(t[i:comma].split()), " ".join(t[comma + 1:j - 1].split()), j


def sends():
    fn_rx = re.compile(r"^(?!\s)(?:KH1_V0\(\w+\)\s*|[A-Za-z_][\w \t\*]*?)\b(func_[0-9a-f]{8}|\w+)\s*\([^;{]*\)\s*\{", re.M)
    out = []
    for rel, t in sources():
        fns = [(m.start(), m.group(1), m.end()) for m in fn_rx.finditer(t)]
        for m in re.finditer(r"\bPlatDmaSend\s*\(", t):
            if t[:m.start()].rstrip().endswith(("define", "void")):
                continue
            ch, src, _ = split_args(t, m.end())
            fn = [x for x in fns if x[0] < m.start()]
            name, body = (fn[-1][1], t[fn[-1][2]:m.start()]) if fn else ("?", "")
            line = t.count("\n", 0, m.start()) + 1
            out.append((rel, line, name, ch, src, classify(src, body)))
    return out


def classify(src, body):
    n = re.search(r"D_([0-9A-F]{8})", src)
    if n:
        return "static %s D_%s" % ("bss" if int(n.group(1), 16) >= 0x00494080 else "data", n.group(1))
    v = [x for x in re.findall(r"[A-Za-z_]\w*", src) if x not in ("void", "u32", "s32", "u8", "s8", "M2C_FIELD")]
    var = v[0] if v else ""
    sets = " ".join(re.findall(r"\b%s\s*=[^=;][^;]*;" % re.escape(var), body)) if var else ""
    # one step back: the buffer the sent pointer was made from
    for w in set(re.findall(r"\b(buf|base|p|b|q)\b", sets)) - {var}:
        sets += " " + " ".join(re.findall(r"\b%s\s*=[^=;][^;]*;" % w, body))
    if any(s in sets or s in src for s in SPR_FRAMES):
        return "scratchpad frame"
    if re.search(r"\barg\d\b|M2C_FIELD|->", src + " " + sets):
        return "pointer (parameter / field)"
    return "pointer (local / caller buffer)"


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--list", action="store_true", help="list every PlatDmaSend call and its chain's source")
    ap.add_argument("--tsv", type=Path, help="write the --list table as TSV")
    a = ap.parse_args()
    rows = mask_rows()
    for rel, n, macro, s in rows:
        print("%s:%d\t%s\t%s" % (rel, n, macro, s))
    ss = sends()
    if a.list:
        for rel, line, fn, ch, src, kind in ss:
            print("%s:%d\t%s\t%s\t%s\t%s" % (rel, line, fn, ch, src, kind))
    kinds = {}
    for s in ss:
        k = s[5].split(" D_")[0]
        kinds[k] = kinds.get(k, 0) + 1
    print("# %d hand-built DMA addresses; %d PlatDmaSend calls in %d files (%s)" % (
        len(rows), len(ss), len({s[0] for s in ss}), ", ".join("%s %d" % kv for kv in sorted(kinds.items()))),
        file=sys.stderr)
    if a.tsv:
        a.tsv.parent.mkdir(parents=True, exist_ok=True)
        a.tsv.write_text("call\tfunction\tchannel\tchain\tsource\n" + "".join(
            "%s:%d\t%s\t%s\t%s\t%s\n" % s for s in ss))
    return 1 if rows else 0


if __name__ == "__main__":
    sys.exit(main())
