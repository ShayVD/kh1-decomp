#!/usr/bin/env python3
"""Flip near-miss drafts' callee return types between void and s32.

    python3 tools/ovl/retflip.py OVL draft.c... [--out DIR]

A call whose result is ignored still sets v0 when the callee returns a value, and register allocation then
treats v0 as busy right after the call (docs/overlays.md, "v0 after a call"). So a prototype declared void
when the real function returns int moves registers around the call. For each draft, every `void f(...);` or
`s32 f(...);` prototype of a function the draft calls as a statement is flipped in turn (s32 -> void only
when the result is never used) and kept when the hand.py try score drops. Prints each kept flip and a
`RESULT ovl draft before after` line; with --out DIR the improved draft is written to DIR/<draft name>.
"""
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def score(ovl: str, func: str, text: str, name: str) -> int:
    with tempfile.TemporaryDirectory() as d:
        p = Path(d) / name
        p.write_text(text)
        r = subprocess.run([sys.executable, "tools/ovl/hand.py", "try", ovl, func, str(p)], cwd=ROOT,
                           capture_output=True, text=True)
    out = r.stdout + r.stderr
    if " MATCH " in out:
        return 0
    m = re.search(r"score (\d+)", out)
    return int(m.group(1)) if m else 99999


def flip(ovl: str, path: Path):
    name = path.name
    func = re.match(r"func_[0-9a-f]{8}", name).group(0)
    t = path.read_text()
    base = best = score(ovl, func, t, name)
    kept = []
    for full, rt, fn in re.findall(r"^((void|s32) (\w+)\([^)]*\);)$", t, re.M):
        if fn == func or not re.search(r"^\s*%s\(" % re.escape(fn), t, re.M):
            continue
        if rt == "s32" and re.search(r"[=(,!]\s*%s\(" % re.escape(fn), t.replace(full, "")):
            continue
        nt = t.replace(full, ("s32" if rt == "void" else "void") + full[len(rt):], 1)
        sc = score(ovl, func, nt, name)
        if sc < best:
            best, t = sc, nt
            kept.append((fn, rt))
            print(name, fn, rt, "->", "s32" if rt == "void" else "void", sc, flush=True)
    return base, best, t, kept


def main() -> int:
    args = sys.argv[1:]
    out = None
    if "--out" in args:
        i = args.index("--out")
        out = Path(args[i + 1])
        del args[i:i + 2]
    if len(args) < 2:
        sys.exit(__doc__)
    ovl = args[0]
    for a in args[1:]:
        p = Path(a).resolve()
        base, best, text, _ = flip(ovl, p)
        if out and best < base:
            out.mkdir(parents=True, exist_ok=True)
            (out / p.name).write_text(text)
        print("RESULT", ovl, p.name, base, best, flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
