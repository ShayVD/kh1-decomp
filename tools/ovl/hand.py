#!/usr/bin/env python3
"""Hand-matching helpers for the overlays (docs/overlays.md "Hand matching").

  python3 tools/ovl/hand.py show NAME func_X          # original asm + autodecomp's closest draft
  python3 tools/ovl/hand.py try NAME func_X draft.c   # compile draft.c (include/ovl.h first), diff
  python3 tools/ovl/hand.py keep NAME func_X draft.c  # try, and on a match save ovl/NAME/hand/func_X.c
  python3 tools/ovl/hand.py todo NAME                 # functions not matched yet (after `make ovl`)
  python3 tools/ovl/hand.py perms NAME func_X draft.c # try every order of the lines between
                                                      # `//{` and `//}` in draft.c (store order)

A draft named NAME.<mode>.c (x.nofill.c) is compiled with that kh1.toml flag mode and kept
as func_X.<mode>.c. A draft is plain C without includes: include/ovl.h (common.h, platform/vu.h, m2c.h and the
OvlVec / OvlMtx types) is put in front. One function per file; declare what it uses.
"""
from __future__ import annotations

import itertools
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


MODE = ""  # a kh1.toml flag mode, from the draft's name (draft.nofill.c)


def env(name: str) -> dict:
    return dict(os.environ, KH1_OVL=name, KH1_MODE=MODE)


def try_code(name: str, func: str, code: str, diff: bool = True) -> tuple[bool, str]:
    with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False) as fh:
        fh.write('#include "ovl.h"\n' + code)
        path = fh.name
    try:
        r = subprocess.run([sys.executable, "tools/autodecomp.py", "try", func, "--file", path]
                           + (["--diff"] if diff else []), cwd=ROOT, capture_output=True, text=True, env=env(name))
    finally:
        os.unlink(path)
    lines = [ln for ln in r.stdout.splitlines() if " MATCH " in ln or " FAIL " in ln or "!=" in ln]
    return any(" MATCH " in ln for ln in lines), "\n".join(lines) or r.stderr.strip()


def keep(name: str, func: str, code: str) -> Path:
    out = ROOT / "ovl" / name / "hand" / (f"{func}.{MODE}.c" if MODE else f"{func}.c")
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(f"/* {name}.x {func}: matched by hand. */\n#include \"ovl.h\"\n\n{code.strip()}\n")
    return out


def main() -> int:
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    cmd, name = sys.argv[1], sys.argv[2]
    if cmd == "todo":
        lay = [ln.split("\t") for ln in (ROOT / "ovl" / name / "layout.tsv").read_text().splitlines()
               if ln[:1] in "0123456789abcdef"]
        pl = ROOT / "out" / "ovl" / name / "gen" / "placements.tsv"
        done = {ln.split("\t")[0] for ln in pl.read_text().splitlines()[1:]} if pl.exists() else set()
        for a, _e, size, _n in lay:
            if a not in done:
                print(f"func_{a}\t{size}")
        return 0
    func = sys.argv[3]
    if cmd == "show":
        subprocess.run([sys.executable, "tools/kh1tool.py", "asm", func], cwd=ROOT, env=env(name))
        fail = ROOT / "out" / "ovl" / name / "autodecomp" / "fail" / f"{func[5:]}.c"
        if fail.exists():
            print(fail.read_text())
        return 0
    global MODE
    draft = Path(sys.argv[4])
    MODE = draft.suffixes[-2][1:] if len(draft.suffixes) > 1 else ""
    code = draft.read_text()
    if cmd == "try":
        print(try_code(name, func, code)[1])
        return 0
    if cmd == "keep":
        ok, out = try_code(name, func, code)
        print(out)
        if ok:
            print(f"kept {keep(name, func, code).relative_to(ROOT)}")
        return 0 if ok else 1
    if cmd == "perms":
        m = re.search(r"^[ \t]*//\{[^\n]*\n(.*?)^[ \t]*//\}[^\n]*\n", code, re.M | re.S)
        if not m:
            sys.exit("no //{ ... //} block")
        lines = m.group(1).splitlines(keepends=True)
        for p in itertools.permutations(lines):
            c = code[: m.start()] + "".join(p) + code[m.end():]
            ok, out = try_code(name, func, c, diff=False)
            if ok:
                print(out)
                print("".join(p))
                return 0
        print("no order matches")
        return 1
    sys.exit(__doc__)


if __name__ == "__main__":
    sys.exit(main())
