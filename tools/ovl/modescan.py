#!/usr/bin/env python3
"""Score near-miss drafts under other build modes.

    python3 tools/ovl/modescan.py OVL [DIR...] [--modes nofill,norlo,nostrict]

For every func_*.c draft in each DIR (default nonmatchings/session141/OVL), scores the draft with hand.py try
under its own mode (from a draft.<mode>.c name, or none) and under each listed mode (kh1.toml `mode` names;
the default is nofill, norlo, nostrict, nostrict_nofill and nogcse). Prints `func file score best_mode
best_score` for each draft that another mode improves, and `MATCH` when a mode matches. A better mode is
applied by renaming the draft to func_X.<mode>.c. In round 44 it improved 11 session141 drafts (gb and wm twins
of one function want the same mode).
"""
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def score(ovl: str, func: str, body: str, mode: str) -> int:
    with tempfile.TemporaryDirectory() as d:
        p = Path(d) / (f"{func}.{mode}.c" if mode else f"{func}.c")
        p.write_text(body)
        r = subprocess.run([sys.executable, "tools/ovl/hand.py", "try", ovl, func, str(p)], cwd=ROOT,
                           capture_output=True, text=True)
    out = r.stdout + r.stderr
    if " MATCH " in out:
        return 0
    m = re.search(r"score (\d+)", out)
    return int(m.group(1)) if m else 99999


def main() -> int:
    args = sys.argv[1:]
    modes = ["nofill", "norlo", "nostrict", "nostrict_nofill", "nogcse"]
    if "--modes" in args:
        i = args.index("--modes")
        modes = args[i + 1].split(",")
        del args[i:i + 2]
    if not args:
        sys.exit(__doc__)
    ovl, dirs = args[0], args[1:] or [f"nonmatchings/session141/{args[0]}"]
    for d in dirs:
        for p in sorted((ROOT / d).glob("func_*.c")):
            func = re.match(r"func_[0-9a-f]{8}", p.name).group(0)
            own = p.suffixes[-2][1:] if len(p.suffixes) > 1 else ""
            body = p.read_text()
            base = score(ovl, func, body, own)
            res = {m: score(ovl, func, body, m) for m in modes if m != own}
            if own:
                res[""] = score(ovl, func, body, "")
            best = min(res, key=res.get)
            if base == 99999 and res[best] == 99999:
                print(func, f"{d}/{p.name}", "ERR (no score in any mode; is out/ovl/%s.elf built?)" % ovl, flush=True)
            elif res[best] < base:
                print(func, f"{d}/{p.name}", base, best or "(none)", "MATCH" if res[best] == 0 else res[best],
                      flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
