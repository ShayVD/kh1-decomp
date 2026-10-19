#!/usr/bin/env python3
"""Build the KH1_SHIFTABLE variants of sources for the shiftable build.

  python3 -I tools/shift/variants.py build [--out-dir out/shift/variants] [--define NAME ...]

A source that hard-codes an address for matching (e.g. func_00171078's
`((s32 *)0x35BD40)[i]`, docs/portability.md) keeps the literal in the
normal build and uses the symbol under `#ifdef KH1_SHIFTABLE`. This compiles
every such source again with -DKH1_SHIFTABLE, with the exact rule the
normal build uses (out/gen/objects.mk), into OUT_DIR/<object path>, and
prints one `--subst-obj OBJ=VARIANT` argument per object for shift_ld.py.
`--define NAME` (repeatable) also defines NAME and builds the sources that
mention it: KH1_OVL_FIXUPS (the overlay fixup hook in the loader, M1/M2
only, because it makes two functions longer than their M0 slot).
Nothing is written outside out/."""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import kh1tool as K  # noqa: E402

DEFINE = "KH1_SHIFTABLE"


def rules() -> dict[str, str]:
    """object -> its compile command (one line, make variables unexpanded)."""
    text = (K.GEN / "objects.mk").read_text()
    out = {}
    for m in re.finditer(r"^(\S+\.o): \S+.*\n(?:\t.*\n)*?\t@(\S*ee-gcc .*|\$\(AS\) .*)$", text, re.M):
        out[m.group(1)] = m.group(2)
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=("build", "list"))
    ap.add_argument("--out-dir", type=Path, default=K.OUT / "shift" / "variants")
    ap.add_argument("--define", action="append", default=[], help="also define NAME (and build what mentions it)")
    a = ap.parse_args()
    cfg = K.load_config()
    defines = [DEFINE] + [d for d in a.define if d != DEFINE]
    srcs = [p for p in K.iter_sources() if p.suffix in (".c", ".cpp", ".cc")
            and any(d in p.read_text(errors="ignore") for d in defines)]
    if a.cmd == "list":
        print("\n".join(p.relative_to(K.ROOT).as_posix() for p in srcs))
        return 0
    rl = rules()
    env = {"$(TOOLCHAIN)": "tools/toolchain", "$(INCLUDES)": "-Iinclude -Isrc",
           "$(KH1)": f"{sys.executable} -I tools/kh1tool.py"}
    args = []
    for src in srcs:
        obj = K.obj_for(src).relative_to(K.ROOT).as_posix()
        if obj not in rl:
            sys.exit(f"error: no compile rule for {obj} in out/gen/objects.mk")
        new = (a.out_dir / obj).relative_to(K.ROOT) if a.out_dir.is_absolute() else a.out_dir / obj
        new.parent.mkdir(parents=True, exist_ok=True)
        cmd = rl[obj].replace("$(@:.o=.s)", str(new.with_suffix(".s"))).replace("$@", str(new))
        for k, v in env.items():
            cmd = cmd.replace(k, v)
        # define it for the C compile step (`ee-gcc -S`)
        cmd = cmd.replace("ee-gcc -S ", "ee-gcc -S " + "".join(f"-D{d} " for d in defines), 1)
        if "$(" in cmd:
            sys.exit(f"error: unexpanded make variable in the rule for {obj}: {cmd}")
        subprocess.run(cmd, shell=True, check=True, cwd=K.ROOT)  # always: cheap, and headers may change
        args.append(f"--subst-obj {obj}={new}")
    print(" ".join(args))
    return 0


if __name__ == "__main__":
    sys.exit(main())
