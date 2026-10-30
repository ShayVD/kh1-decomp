#!/usr/bin/env python3
"""tools/ovl/drafttwins.py (session 141 round 42): port near-miss drafts between twin overlays.

  python3 tools/ovl/drafttwins.py [--apply] [--dir nonmatchings/session141] [A B]   # default A=wm B=gb

twins.py copies *matched* C to same-shape functions. This does the same for drafts that do
not match yet: it pairs every draft in DIR/A with every draft in DIR/B whose target has the
identical mnemonic sequence, scores both with hand.py try, ports the better one onto the
other with port.py and scores the port. Each pair prints one line:

  pair WM_FUNC SCORE GB_FUNC SCORE | port SRC -> DST DST_FUNC BEFORE -> AFTER [unmapped: ...]

With --apply, each improving port with no unmapped symbols overwrites the destination draft
(a new header line, then the destination's old header, then the ported body) and is
committed on its own; a port that does not improve after the rewrite is reverted. A port that
matches is written as a draft and reported; promote it with hand.py keep. The draft's mode
suffix (.nofill.c etc.) is kept, so the score is under the draft's own build mode.
"""
from __future__ import annotations

import glob
import os
import re
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
TAIL = os.environ.get("COMMIT_TAIL", "")


def mnemonics(ovl: str, func: str) -> tuple:
    r = subprocess.run(["python3", "tools/kh1tool.py", "asm", func], cwd=ROOT,
                       env={**os.environ, "KH1_OVL": ovl}, capture_output=True, text=True)
    out = []
    for line in r.stdout.splitlines():
        m = re.match(r"\s*/\* [0-9A-F]+ [0-9A-F]+ \*/\s+(\S+)", line)
        if m:
            out.append(m.group(1))
    return tuple(out)


def score(ovl: str, func: str, path: str) -> int:
    r = subprocess.run(["python3", "tools/ovl/hand.py", "try", ovl, func, path], cwd=ROOT,
                       capture_output=True, text=True)
    out = r.stdout + r.stderr
    if "MATCH" in out and "FAIL" not in out:
        return 0
    m = re.search(r"score (\d+)", out)
    return int(m.group(1)) if m else 99999


def strip_headers(code: str) -> str:
    code = code.lstrip("\n")
    while code.startswith("/*"):
        code = code[code.index("*/") + 2:].lstrip("\n")
    return code


def main() -> None:
    args = sys.argv[1:]
    apply = "--apply" in args
    args = [a for a in args if a != "--apply"]
    d = "nonmatchings/session141"
    if "--dir" in args:
        i = args.index("--dir")
        d = args[i + 1]
        del args[i:i + 2]
    a_ovl, b_ovl = (args + ["wm", "gb"][len(args):])[:2]
    drafts = {}
    for o in (a_ovl, b_ovl):
        for p in sorted(glob.glob(os.path.join(ROOT, d, o, "func_*.c"))):
            f = re.search(r"func_[0-9a-f]{8}", os.path.basename(p)).group(0)
            drafts[(o, f)] = p
    by_shape: dict = {}
    for (o, f), p in drafts.items():
        m = mnemonics(o, f)
        if len(m) > 3:
            by_shape.setdefault(m, []).append((o, f, p))
    tmpdir = tempfile.mkdtemp(prefix="drafttwins_")
    for group in by_shape.values():
        As = [x for x in group if x[0] == a_ovl]
        Bs = [x for x in group if x[0] == b_ovl]
        for (_, af, ap) in As:
            for (_, bf, bp) in Bs:
                sa, sb = score(a_ovl, af, ap), score(b_ovl, bf, bp)
                if sa == sb:
                    print("pair", af, sa, bf, sb, "equal", flush=True)
                    continue
                if sa < sb:
                    so, sf, sp, do, df, dp, before = a_ovl, af, ap, b_ovl, bf, bp, sb
                else:
                    so, sf, sp, do, df, dp, before = b_ovl, bf, bp, a_ovl, af, ap, sa
                suffix = re.search(r"(\.[a-z]+)?\.c$", dp).group(0)
                out = os.path.join(tmpdir, df + suffix)
                r = subprocess.run(["python3", "tools/ovl/port.py", so, sf, do, df, sp, out],
                                   cwd=ROOT, capture_output=True, text=True)
                note = r.stdout.strip()
                if not os.path.exists(out):
                    print("pair", af, sa, bf, sb, "| port failed", note[:100], flush=True)
                    continue
                old = open(dp).read()
                mo = re.match(r"(/\*.*?\*/\n)", old, re.S)
                oldhdr = mo.group(1) if mo else ""
                body = strip_headers(open(out).read())
                open(out, "w").write(oldhdr + body)
                after = score(do, df, out)
                print("pair", af, sa, bf, sb, "| port", so, "->", do, df, before, "->", after,
                      note[:100], flush=True)
                if not apply or after >= before or "unmapped" in note:
                    continue
                hdr = ("/* drafttwins.py: score %d -> %d, port.py of the %s twin %s draft. "
                       "Earlier header below. */\n" % (before, after, so, sf))
                open(dp, "w").write(hdr + oldhdr + body)
                if after == 0:
                    print("MATCH", do, df, "- promote with hand.py keep", flush=True)
                    continue
                rel = os.path.relpath(dp, ROOT)
                subprocess.run(["git", "add", rel], cwd=ROOT, check=True)
                msg = "Overlays: %s %s near miss, score %d -> %d, port of %s %s" % (
                    do, df, before, after, so, sf)
                subprocess.run(["git", "commit", "-q", "-m", msg + TAIL], cwd=ROOT, check=True)


if __name__ == "__main__":
    main()
