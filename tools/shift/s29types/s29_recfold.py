#!/usr/bin/env python3
"""Fold a record view of D_00304BE8 that indexes the save block's member records
from the block's start (session 29).

  python3 -I tools/shift/s29types/s29_recfold.py FILE.c TYPE [--sub SUBTYPE] [--map f=g ...]

TYPE is a 0x74-byte struct whose record k is read as ((TYPE *)D_00304BE8)[k]: it
starts 4 bytes before the member record m[k] of Save_304be8.  Steps: (--sub: the
file's own type of the member's 0x70-byte sub record is retyped to Sub_304be8
first), TYPE is retyped to W606Mem_304be8 with s29_retype --shift 4, then
`&((TYPE *)D_00304BE8)[X]` / `((TYPE *)D_00304BE8)[X]` / `((TYPE *)D_00304BE8)`
become `&D_00304BE8->m[X]` / `D_00304BE8->m[X]` / `D_00304BE8->m`.  The file is
kept only if its -S is identical to HEAD's (else it is restored).
"""
import subprocess, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "s27types"))
import s27lib as L  # noqa: E402
import s29_retype as R  # noqa: E402

D = "D_00304BE8"
HDR = "data/pieces/D_00304BE8_s.h"


def bracket_end(t, i):
    """t[i] == '[': index after the matching ']'"""
    d = 0
    for k in range(i, len(t)):
        if t[k] == "[":
            d += 1
        elif t[k] == "]":
            d -= 1
            if d == 0:
                return k + 1
    raise ValueError("unbalanced [")


def uncast(t, T):
    pat = f"(({T} *){D})"
    out, i = [], 0
    while True:
        j = t.find(pat, i)
        if j < 0:
            out.append(t[i:])
            break
        out.append(t[i:j])
        k = j + len(pat)
        if k < len(t) and t[k] == "[":
            e = bracket_end(t, k)
            out.append(f"{D}->m{t[k:e]}")
            i = e
        else:
            out.append(f"{D}->m")
            i = k
    return "".join(out)


def run(argv):
    return subprocess.run([sys.executable, "-I", str(Path(R.__file__))] + argv,
                          capture_output=True, text=True).stdout


def main(argv):
    rel, T = argv[0], argv[1]
    sub = None
    maps = []
    if "--sub" in argv:
        sub = argv[argv.index("--sub") + 1]
    if "--map" in argv:
        maps = argv[argv.index("--map") + 1:]
    p = L.ROOT / rel
    orig = p.read_text()
    try:
        if sub:
            o = run([rel, sub, "--shared", "Sub_304be8", "--header", HDR, "--apply"])
            print(o.strip().splitlines()[-1] if o.strip() else "?")
            if "applied" not in o:
                raise RuntimeError("sub step failed:\n" + o)
        o = run([rel, T, "--shared", "W606Mem_304be8", "--header", HDR, "--shift", "4", "--force"]
                + (["--map"] + maps if maps else []))
        print(o.strip())
        if "written" not in o:
            raise RuntimeError("record step failed")
        t = uncast(p.read_text(), T)
        p.write_text(t)
        asm, diags = L.compile_s(rel)
        hasm, _ = L.head_compile(rel)
        if asm is None or not L.same_asm(asm, hasm):
            raise RuntimeError("-S differs" if asm else f"does not compile: {diags[:4]}")
        print("SAME: kept")
        return 0
    except RuntimeError as e:
        print("FAIL:", e)
        p.write_text(orig)
        return 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
