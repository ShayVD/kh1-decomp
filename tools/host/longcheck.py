#!/usr/bin/env python3
"""A `long` literal shifted by 32 or more (phase 5, docs/portability.md rule 5, session 112).

On the EE `long` is 64-bit, so the game's C writes 64-bit GS words as `1UL << 61` and the PS2 build gets
bit 61. Under the host's gcc -m32 (and on the Vita) `long` is 32-bit: the shift is undefined (gcc folds a
constant one to 0) and the census's -w hides gcc's warning. Session 112 found the crossfade's CLD
(`1UL << 61`) and its ZBUF's ZMSK (`1UL << 32`) lost that way in objdraw.nostrict.c, with two object flag
bits there (45, 57) and one in summon.nostrict.c (52). So: every integer literal with an L / UL suffix (not LL) shifted left by a constant of
32 or more, and every `(long)` / `(unsigned long)` cast shifted so, in the C the host compiles (src/ but
src/sdk, host/, include/), comments and `#ifdef KH1_PS2` branches left out. Write `1ULL << n` or
`(u64)1 << n` instead (the same EE code).

    python3 -I tools/host/longcheck.py [--src src] [--host host] [--include include] [--cc gcc]

--cc also compiles each src/ file (but src/sdk) with that compiler under -m32 -fsyntax-only and reports
gcc's "shift count >= width of type": the shifts of 32-bit variables the text check cannot type (session
112: objutil.c func_001375d8's `(u32 << 32) >> 32`, which the EE does in a 64-bit register).

Exit 1 with one line per hit.
"""
import argparse
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from fscheck import strip_ps2  # noqa: E402

SHIFT = re.compile(r"(?:\b(?:0[xX][0-9a-fA-F]+|\d+)(?:[uU][lL]|[lL][uU]?)\b|\(\s*(?:unsigned\s+|signed\s+)?long(?:\s+int)?\s*\)\s*"
                   r"(?:\w+|\([^()]*\)))\s*<<\s*(0[xX][0-9a-fA-F]+|\d+)")


def files(dirs):
    for d in dirs:
        for dp, dn, fn in sorted(os.walk(d)):
            if os.path.relpath(dp, ROOT).replace(os.sep, "/").startswith("src/sdk"):
                dn[:] = []
                continue
            dn.sort()
            for f in sorted(fn):
                if f.endswith((".c", ".h")):
                    yield os.path.join(dp, f)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--src", default=os.path.join(ROOT, "src"))
    ap.add_argument("--host", default=os.path.join(ROOT, "host"))
    ap.add_argument("--include", default=os.path.join(ROOT, "include"))
    ap.add_argument("--cc", help="also compile src/ with this compiler (-m32) for shift-count warnings")
    args = ap.parse_args()
    hits, n = [], 0
    for path in files((args.src, args.host, args.include)):
        n += 1
        text = strip_ps2(open(path, errors="replace").read())
        for m in SHIFT.finditer(text):
            if int(m.group(1), 0) >= 32:
                hits.append("%s:%d: %s: a 32-bit long on the host; write ULL or (u64)" % (
                    os.path.relpath(path, ROOT), text.count("\n", 0, m.start()) + 1, m.group(0)))
    if args.cc:
        cs = [f for f in files((args.src,)) if f.endswith(".c")]

        def one(path):
            p = subprocess.run([args.cc, "-m32", "-malign-double", "-std=gnu89", "-fsyntax-only", "-DKH1_HOST",
                                "-I" + args.include, "-I" + os.path.join(ROOT, "src"), "-I" + args.src,
                                "-Wno-implicit-function-declaration", "-Wno-int-conversion",
                                "-Wno-incompatible-pointer-types", "-Wno-implicit-int", path],
                               capture_output=True, text=True, env=dict(os.environ, LC_ALL="C"))
            return [l for l in p.stderr.splitlines() if "shift count" in l]
        with ThreadPoolExecutor(os.cpu_count() or 4) as ex:
            for ls in ex.map(one, cs):
                hits += [os.path.relpath(l.split(": warning")[0], ROOT) + ": " + l.split("warning: ")[-1]
                         for l in ls]
    for h in hits:
        print("longcheck: " + h)
    print("longcheck: %d files, %d shifts of 32 or more%s" % (n, len(hits), " (gcc too)" if args.cc else ""))
    sys.exit(1 if hits else 0)


if __name__ == "__main__":
    main()
