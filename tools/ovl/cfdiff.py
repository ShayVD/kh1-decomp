#!/usr/bin/env python3
"""tools/ovl/cfdiff.py (wwm1, session 141 round 34): compare a draft's control flow with the original's.

    python3 tools/ovl/cfdiff.py OVL draft.c [draft.c ...]      # one summary line per draft
    python3 tools/ovl/cfdiff.py -v OVL draft.c [draft.c ...]   # also list each differing stretch
    python3 tools/ovl/cfdiff.py --scan OVL [DIR]               # every func_*.c in DIR (default
                                                               # nonmatchings/session141/OVL), worst first

For each hand.py-style draft (include/ovl.h put in front; a NAME.<mode>.c draft gets that kh1.toml
mode's cflags), it takes the original function's asm (hand.py show) and the draft's `ee-gcc -S`
output (only the draft's own function, between .ent and .end), and reduces each to its sequence of
branches, jumps and calls: b, beqz, bnez, beq, bne, bgez, bltz, blez, bgtz, bc1t, bc1f, jr, jalr and
`jal <callee>`. Likely forms count as the plain branch (bnezl = bnez), `beq r,$0` counts as beqz, and
`j $31` counts as jr. gcc's soft-float names in -S output (dpsub, fptodp, ...) are mapped to the
libgcc names the linked original shows (__subdf3, __extendsfdf2, ...). It then aligns the two
sequences (difflib) and prints `func T/O diff N`: T and O are the lengths and N the number of
entries in the stretches that differ.

Use it before working on registers (round 34): a draft whose branch sequence differs has a
different block layout from the original, and no register tweak fixes that. Typical causes
seen so far:
- an extra `b` in the original: an expression the source writes in the call arguments on both
  sides of an if, recomputed on the path that lacks it (wm f26e80), or an if/else whose arms are
  in the other order (wm f3e988: `if (mode == 0) A; else B;`);
- one call in the original where the draft has two: two per-arm calls merged by jump2
  cross-jumping. Try the draft in nosib mode (docs/overlays.md "Two calls merged into one
  jal"), or write the shared call once (wm f31430);
- `beqz, b` against `bnez`: a branch the original inverts around a likely delay slot.
"""
from __future__ import annotations

import difflib
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))
from gcsebucket import GCC, mode_cflags  # noqa: E402

BRANCHES = {"b", "beq", "bne", "beqz", "bnez", "bgez", "bltz", "blez", "bgtz", "bc1t", "bc1f",
            "jal", "jr", "j", "jalr", "bgezal", "bltzal"}
SOFTFLOAT = {"dpsub": "__subdf3", "dpadd": "__adddf3", "dpmul": "__muldf3", "dpdiv": "__divdf3",
             "dpcmp": "__cmpdf2", "fptodp": "__extendsfdf2", "dptofp": "__truncdfsf2",
             "dptoli": "__fixdfsi", "litodp": "__floatsidf", "dpneg": "__negdf2",
             "fpsub": "__subsf3", "fpadd": "__addsf3", "fpmul": "__mulsf3", "fpdiv": "__divsf3",
             "fpcmp": "__cmpsf2"}


def norm(op: str, args: str) -> str | None:
    if op not in BRANCHES and op.endswith("l") and op[:-1] in BRANCHES:
        op = op[:-1]
    if op not in BRANCHES:
        return None
    if op in ("beq", "bne") and re.search(r",\s*\$(0|zero)\s*,", args):
        op += "z"
    if op == "j" and re.match(r"\s*\$", args):
        op = "jr"
    if op == "jal" and re.match(r"\s*\$", args):
        op = "jalr"  # gcc -S writes jalr as `jal $31,$2`
    if op == "jal":
        m = re.search(r"([A-Za-z_][\w.]*)", args)
        callee = m.group(1) if m else "?"
        return "jal " + SOFTFLOAT.get(callee, callee).lower()
    return op


def target_seq(ovl: str, func: str) -> list[str]:
    out = subprocess.run([sys.executable, str(ROOT / "tools" / "ovl" / "hand.py"), "show", ovl, func],
                         cwd=ROOT, capture_output=True, text=True).stdout
    seq = []
    for ln in out.splitlines():
        m = re.match(r"\s*/\* [0-9A-F]{8} [0-9A-F]{8} \*/\s+(\S+)\s*(.*)", ln)
        if m:
            s = norm(m.group(1), m.group(2))
            if s:
                seq.append(s)
    return seq


def draft_seq(draft: Path, func: str) -> list[str]:
    with tempfile.TemporaryDirectory() as d:
        src = Path(d) / "d.c"
        src.write_text('#include "ovl.h"\n' + draft.read_text())
        r = subprocess.run([str(GCC), "-S", "-x", "c", *mode_cflags(draft), f"-I{ROOT / 'include'}",
                            "-o", "d.s", "d.c"], cwd=d, capture_output=True, text=True)
        if r.returncode:
            raise RuntimeError(r.stderr[-1500:])
        asm = (Path(d) / "d.s").read_text()
    m = re.search(r"\t\.ent\t%s\n(.*?)\t\.end\t%s\n" % (func, func), asm, re.S)
    body = m.group(1) if m else asm
    seq = []
    for ln in body.splitlines():
        m = re.match(r"\t(\S+)(?:\t(.*))?$", ln)
        if m:
            s = norm(m.group(1), m.group(2) or "")
            if s:
                seq.append(s)
    return seq


def compare(ovl: str, draft: Path, verbose: bool) -> tuple[int, str]:
    func = re.match(r"(func_[0-9a-f]+)", draft.name).group(1)
    try:
        t, o = target_seq(ovl, func), draft_seq(draft, func)
    except RuntimeError as e:
        return 1 << 30, f"{func} does not compile: {e}"
    ops = difflib.SequenceMatcher(None, t, o, autojunk=False).get_opcodes()
    n = sum(max(i2 - i1, j2 - j1) for tag, i1, i2, j1, j2 in ops if tag != "equal")
    lines = [f"{func} {len(t)}/{len(o)} diff {n}  ({draft})"]
    if verbose:
        for tag, i1, i2, j1, j2 in ops:
            if tag != "equal":
                lines.append(f"   {tag} target[{i1}] {t[i1:i2]} ours[{j1}] {o[j1:j2]}")
    return n, "\n".join(lines)


def main() -> int:
    args = sys.argv[1:]
    verbose = "-v" in args
    args = [a for a in args if a != "-v"]
    if not args:
        sys.exit(__doc__)
    if args[0] == "--scan":
        ovl = args[1]
        d = Path(args[2]) if len(args) > 2 else ROOT / "nonmatchings" / "session141" / ovl
        res = [compare(ovl, p, verbose) for p in sorted(d.glob("func_*.c"))]
        for _, text in sorted(res, key=lambda r: -r[0]):
            print(text)
        return 0
    ovl = args[0]
    for p in args[1:]:
        print(compare(ovl, Path(p), verbose)[1], flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
