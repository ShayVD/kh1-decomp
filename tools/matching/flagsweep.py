#!/usr/bin/env python3
"""Sweep single gcc 2.96 flags over near-miss drafts (session 7).

  tools/matching/flagsweep.py [-j4] [--modes hand,hand/nostrict] DRAFT.c ...

Each draft is copied to src/<mode>/.fs_<addr>_<n>.c (dot files: the build
skips them) and checked with tools/checkfile.py, once as is and once per
extra C -> asm flag (KH1_EXTRA_CCFLAGS). The function is the one whose
address is in the file name. Modes default to the ones the draft's first
line names (`hand/nostrict` ...), else hand and hand/nostrict. Prints one
line per draft: baseline words off and every flag that does better;
MATCH means byte-identical (rodata functions can never reach 0 here:
compare against the baseline)."""
import argparse, os, re, subprocess, sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
FLAGS = """-fno-sched-interblock -fno-sched-spec -fsched-spec-load -fno-schedule-insns
-fno-schedule-insns2 -fno-rerun-cse-after-loop -fno-rerun-loop-opt -fno-expensive-optimizations
-fno-caller-saves -fno-force-mem -fforce-addr -fno-regmove -fno-cse-follow-jumps
-fno-cse-skip-blocks -fno-peephole -fno-thread-jumps -fno-strength-reduce -funroll-loops -O1
-O3 -fno-defer-pop -fno-optimize-sibling-calls -fno-function-cse -fno-reorder-blocks
-fno-gcse-lm -fno-gcse-sm -fno-inline -fargument-noalias -fno-branch-count-reg
-fmove-all-movables -freduce-all-givs -fssa -fno-delayed-branch -funsigned-char
-fno-delete-null-pointer-checks""".split()
MODES = ["hand", "hand/nostrict", "hand/nofill", "hand/nostrict_nofill", "hand/nogcse",
         "hand/nostrict_nogcse", "hand/n32", "hand/n32_nogcse", "hand/n32_nostrict"]


def check(path: Path, addr: str, flag: str):
    env = dict(os.environ, KH1_EXTRA_CCFLAGS=flag)
    r = subprocess.run([sys.executable, str(ROOT / "tools/checkfile.py"), str(path)],
                       capture_output=True, text=True, env=env, cwd=ROOT, timeout=900)
    for l in r.stdout.splitlines():
        if l.startswith(addr):
            if "MATCH" in l:
                return 0, l
            m = re.search(r"(\d+) words differ", l)
            sz = re.search(r"FAIL (\d+) vs (\d+)", l)
            pen = 0 if sz and sz.group(1) == sz.group(2) else 1000
            return (int(m.group(1)) + pen if m else 9999), l
    return 99999, "error"


def modes_for(text: str):
    first = text.splitlines()[0] if text else ""
    found = [m for m in sorted(MODES, key=len, reverse=True) if re.search(r"\b" + re.escape(m) + r"\b", first)]
    seen = []
    for m in found:
        if not any(m in s for s in seen):
            seen.append(m)
    return seen or ["hand", "hand/nostrict"]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("-j", type=int, default=4)
    ap.add_argument("--modes", default="")
    ap.add_argument("--flags", default="")
    ap.add_argument("drafts", nargs="+")
    a = ap.parse_args()
    flags = a.flags.split(",") if a.flags else FLAGS
    jobs = []
    n = 0
    for d in a.drafts:
        m = re.search(r"([0-9a-f]{8})", Path(d).name)
        if not m:
            continue
        addr = m.group(1)
        text = Path(d).read_text(errors="replace")
        if "common.h" not in text:
            text = '#include "common.h"\n' + text
        for mode in (a.modes.split(",") if a.modes else modes_for(text)):
            n += 1
            p = ROOT / "src" / mode / f".fs_{addr}_{n}.c"
            p.write_text(text)
            for fl in [""] + flags:
                jobs.append((d, addr, mode, p, fl))
    res = {}
    with ThreadPoolExecutor(a.j) as ex:
        futs = {ex.submit(check, p, addr, fl): (d, addr, mode, p, fl) for d, addr, mode, p, fl in jobs}
        for f, k in futs.items():
            res[k] = f.result()
    for p in {k[3] for k in res}:
        p.unlink(missing_ok=True)
    by = {}
    for (d, addr, mode, p, fl), (score, line) in res.items():
        by.setdefault(d, []).append((score, mode, fl or "(none)", line))
    for d, rs in by.items():
        base = {m: s for s, m, fl, _ in rs if fl == "(none)"}
        better = sorted((s, m, fl) for s, m, fl, _ in rs if fl != "(none)" and s < base.get(m, 1e9))
        tag = "MATCH " if any(s == 0 for s, _, _ in better) or 0 in base.values() else ""
        print(f"{tag}{Path(d).name}: base {base}; better: {better[:6]}", flush=True)


if __name__ == "__main__":
    main()
