#!/usr/bin/env python3
"""Each include/data/pieces header new since a git ref compiles on its own (session 26).

  python3 -I tools/shift/s26types/s26_hdrcheck.py [REF]   (default origin/main)
"""
import subprocess, sys, tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
ref = sys.argv[1] if len(sys.argv) > 1 else "origin/main"
out = subprocess.run(["git", "diff", "--name-only", "--diff-filter=A", ref, "--", "include/data"], cwd=ROOT,
                     capture_output=True, text=True).stdout.split()
GCC = ROOT / "tools/toolchain/ee-gcc2.96/bin/ee-gcc"


def one(h):
    inc = h[len("include/"):]
    with tempfile.NamedTemporaryFile("w", suffix=".c", dir="/tmp", delete=False) as f:
        f.write(f'#include "{inc}"\n')
    r = subprocess.run([str(GCC), "-fsyntax-only", "-x", "c", "-O2", "-G0", "-Iinclude", "-Isrc", f.name],
                       cwd=ROOT, capture_output=True, text=True)
    Path(f.name).unlink()
    return h, r.returncode, r.stderr.strip()


bad = 0
with ThreadPoolExecutor(3) as ex:
    for h, rc, err in ex.map(one, [x for x in out if x.endswith(".h")]):
        if rc or err:
            print(f"BAD {h}: {err[:300]}")
            bad += 1
print(f"{len(out)} new headers, {bad} bad")
sys.exit(1 if bad else 0)
