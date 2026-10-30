"""Regression tests for tools/ovl/hill3.py --check (run: python3 tools/ovl/hill3_test.py).

The volatile case is dkmovie func_00f25978's type 2 path (round 57): hill3 moved the IPU_CMD write
before the IPU_CTRL write, which changes the order of two hardware register stores.
"""
import subprocess
import sys
import tempfile
from pathlib import Path

HILL3 = Path(__file__).resolve().parent / "hill3.py"

HEADER = """#define IPU_CMD (*(volatile s32 *)0x10002000)
#define IPU_CTRL (*(volatile s32 *)0x10002010)
"""

DRAFT = """#include "regs.h"

void func_00f25978(s32 base, s32 qs) {
    s32 a;
    s32 first;
    s32 t;

    first = 1;
    IPU_CTRL = base + 0x1200000;
    a = first << 26;
    first = 0;
    IPU_CMD = a | (qs << 16) | 0x28000000;
    *(volatile u32 *)0x1000B010 = base;
    t = qs + 1;
}
"""

# (description, (from, to) line swaps applied to DRAFT, expected --check result)
CASES = [
    ("IPU_CMD moved before IPU_CTRL (f25978 case 2)",
     ["    IPU_CTRL = base + 0x1200000;\n    a = first << 26;\n    first = 0;\n    IPU_CMD = a | (qs << 16) | 0x28000000;\n",
      "    a = first << 26;\n    first = 0;\n    IPU_CMD = a | (qs << 16) | 0x28000000;\n    IPU_CTRL = base + 0x1200000;\n"], 1),
    ("*(volatile) store moved before IPU_CMD",
     ["    IPU_CMD = a | (qs << 16) | 0x28000000;\n    *(volatile u32 *)0x1000B010 = base;\n",
      "    *(volatile u32 *)0x1000B010 = base;\n    IPU_CMD = a | (qs << 16) | 0x28000000;\n"], 1),
    ("plain local moved past a volatile store",
     ["    *(volatile u32 *)0x1000B010 = base;\n    t = qs + 1;\n",
      "    t = qs + 1;\n    *(volatile u32 *)0x1000B010 = base;\n"], 0),
    ("a = first << 26 moved before IPU_CTRL",
     ["    IPU_CTRL = base + 0x1200000;\n    a = first << 26;\n",
      "    a = first << 26;\n    IPU_CTRL = base + 0x1200000;\n"], 0),
]


def main() -> int:
    fails = 0
    with tempfile.TemporaryDirectory() as d:
        dp = Path(d)
        (dp / "regs.h").write_text(HEADER)
        draft = dp / "func_00f25978.c"
        draft.write_text(DRAFT)
        for desc, (old, new), want in CASES:
            assert old in DRAFT, desc
            cand = dp / "cand.c"
            cand.write_text(DRAFT.replace(old, new))
            r = subprocess.run([sys.executable, str(HILL3), "--check", "func_00f25978", str(draft), str(cand)],
                               capture_output=True, text=True)
            if r.returncode != want:
                fails += 1
                print(f"FAIL {desc}: rc {r.returncode}, want {want}\n{r.stdout}{r.stderr}")
    print(f"{len(CASES) - fails}/{len(CASES)} ok")
    return 1 if fails else 0


if __name__ == "__main__":
    sys.exit(main())
