#!/usr/bin/env python3
"""Callee return-type sweep over overlay near-miss drafts (session 141, wwm1 rounds 28-29).

    python3 tools/ovl/rettype.py [--out DIR] [--list] [--no-reverse] [OVL ...]   # default: every overlay
    python3 tools/ovl/rettype.py [--out DIR] OVL:draft.c [OVL:draft.c ...]       # the given drafts

gcc schedules around a call differently when the callee returns a value (a call_value insn sets v0) than
when it is declared void, and the delay slots fill differently too. wm func_00f23018 and func_00f42f20
matched in round 28 once func_00f29aa0 (and func_0011ef10) were declared s32; drafts often declare a
callee void because its value is not used.

For each draft (nonmatchings/session141/OVL/func_*.c, plus every draft an ovl/OVL/drafts.tsv lists, scored
from a copy and never written) it scores the draft with hand.py try, then:
  1. known:   each callee the draft declares void whose matched definition (ovl/OVL/hand, src/) or a
              matched file's prototype returns a value, switched to that type (s32, or void * for pointers);
  2. single:  every other void-declared func_X callee switched to s32, one at a time;
  3. pairs:   every pair of the switches that scored better than or equal to the base (best eight),
              and all of the improving ones together;
  4. reverse: each callee the draft declares s32/int/u32 whose result is never used (every call is a bare
              statement), switched to void (skip with --no-reverse).
Candidates are tried in the order the target asm suggests: a call whose v0 is read after the jal (before
it is written) or written in its delay slot comes first. A callee with a body in the draft (inline or
CONTEXT_ONLY) is skipped. Only gains are printed:

    GAIN OVL FILE BASE -> NEW  change[, change]  (written to DIR/OVL/FILE)

--out (default out/rettype) holds the improved copies; the drafts themselves are never changed, so apply
a gain by copying the file over the draft after checking it. --list only prints the candidates.
TLIM=seconds stops after that long, JOBS=n (default 1) scores n drafts at a time.
"""
from __future__ import annotations

import glob
import itertools
import os
import re
import subprocess
import sys
import tempfile
import threading
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TLIM = float(os.environ.get("TLIM", "0"))
JOBS = int(os.environ.get("JOBS", "1"))
T0 = time.time()
PROTO = re.compile(r"^(?:extern\s+)?([A-Za-z_][\w \*]*?)\s*\b(func_[0-9a-f]{8})\s*\(", re.M)
VOIDDECL = r"^void(\s+%s\s*\([^;{]*\)\s*;)"
INTDECL = r"^(?:s32|int|u32)(\s+%s\s*\([^;{]*\)\s*;)"
lock = threading.Lock()


def overlays() -> list[str]:
    return sorted(p.parent.name for p in (ROOT / "ovl").glob("*/layout.tsv"))


def known_types(ovl: str) -> dict[str, str]:
    """{callee: non-void return type} from matched overlay files and src/."""
    out: dict[str, str] = {}
    for p in glob.glob(str(ROOT / "ovl/*/hand/func_*.c")) + glob.glob(str(ROOT / "src/**/*.c"), recursive=True):
        own = "/ovl/" in p and p.split("/ovl/")[1].split("/")[0]
        for m in PROTO.finditer(open(p, errors="replace").read()):
            t, n = m.group(1).strip(), m.group(2)
            if t.startswith("static") or "CONTEXT_ONLY" in t or t in ("return", "else", "void"):
                continue
            if int(n[5:], 16) >= 0xF00000 and own != ovl:
                continue  # an overlay address names another function in another overlay
            if "M2C" in t:
                continue
            out.setdefault(n, "void *" if "*" in t else "s32")
    return out


def target_hints(ovl: str, func: str) -> dict[str, int]:
    """{callee: 2 if v0 is read after a jal to it, or written in its delay slot; 1 if clobbered unread; 0}."""
    r = subprocess.run([sys.executable, "tools/kh1tool.py", "asm", func], cwd=ROOT, capture_output=True,
                       text=True, env=dict(os.environ, KH1_OVL=ovl))
    ins = []
    for ln in r.stdout.splitlines():
        m = re.match(r"\s*/\* [0-9A-F]+ [0-9A-F]+ \*/\s+(\S+)\s*(.*)", ln)
        if m:
            ins.append((m.group(1), m.group(2)))
    hint: dict[str, int] = {}
    for i, (op, args) in enumerate(ins):
        if op != "jal":
            continue
        callee = args.strip()
        h = 0
        if i + 1 < len(ins) and re.match(r"\$v0,", ins[i + 1][1]) and not ins[i + 1][0].startswith("s"):
            h = 2
        for op2, a2 in ins[i + 2:i + 12]:
            regs = re.findall(r"\$\w+", a2)
            if not regs:
                continue
            writes = op2 not in ("sw", "sd", "sh", "sb", "sq", "swc1", "beq", "bne", "beqz", "bnez", "jr", "jalr") \
                and not op2.startswith("b") and regs[0] == "$v0"
            reads = "$v0" in (regs[1:] if writes else regs)
            if reads:
                h = 2
                break
            if writes:
                h = max(h, 1)
                break
            if op2 in ("jal", "jalr"):
                break
        hint[callee] = max(hint.get(callee, 0), h)
    return hint


def score(ovl: str, func: str, path: str) -> int:
    r = subprocess.run([sys.executable, "tools/ovl/hand.py", "try", ovl, func, path], cwd=ROOT,
                       capture_output=True, text=True)
    out = r.stdout + r.stderr
    if " MATCH " in out:
        return 0
    m = re.search(r"score (\d+)", out)
    return int(m.group(1)) if m else 1 << 30


def apply(txt: str, changes) -> str:
    for n, t in changes:
        if t == "void":
            txt = re.sub(INTDECL % n, r"void\1", txt, flags=re.M)
        else:
            txt = re.sub(VOIDDECL % n, t + r"\1", txt, flags=re.M)
    return txt


def label(changes) -> str:
    return ", ".join(f"{n} {t}" for n, t in changes)


def candidates(ovl: str, func: str, txt: str, reverse: bool):
    known = known_types(ovl) if ovl not in KNOWN else KNOWN[ovl]
    KNOWN[ovl] = known
    body = set(re.findall(r"^[^\n;]*\b(func_[0-9a-f]{8})\s*\([^;]*\)\s*\{", txt, re.M))
    hints = target_hints(ovl, func)
    out = []
    for m in re.finditer(VOIDDECL % r"(func_[0-9a-f]{8})", txt, re.M):
        n = re.match(r"\s+(func_[0-9a-f]{8})", m.group(1)).group(1)
        if n in body or n == func:
            continue
        out.append(((0 if n in known else 1, -hints.get(n, 0)), (n, known.get(n, "s32"))))
    if reverse:
        for m in re.finditer(INTDECL % r"(func_[0-9a-f]{8})", txt, re.M):
            n = re.match(r"\s+(func_[0-9a-f]{8})", m.group(1)).group(1)
            if n in body or n == func or n in known:
                continue
            # the text before each call on its line: a bare statement leaves only indentation, `else`,
            # or a closed `if (...)` / `do`
            pre = [u for u in re.findall(r"^(.*?)\b%s\s*\(" % n, txt, re.M)
                   if not re.match(r"^\s*(?:extern\s+)?(?:s32|int|u32)\s*$", u)]
            bare = re.compile(r"^\s*(?:\}?\s*else\s*|(?:\}\s*)?(?:else\s+)?if\s*\(.*\)\s*|do\s*)?$")
            if pre and all(bare.match(u) for u in pre):
                out.append(((2, 0), (n, "void")))
    out.sort(key=lambda x: x[0])
    return [c for _, c in out]


KNOWN: dict[str, dict[str, str]] = {}


def sweep(ovl: str, src: str, outdir: Path, reverse: bool, listonly: bool) -> None:
    func = os.path.basename(src).split(".")[0]
    txt = open(src).read()
    cands = candidates(ovl, func, txt, reverse)
    if listonly:
        with lock:
            print(ovl, os.path.relpath(src, ROOT), label(cands) or "-", flush=True)
        return
    if not cands:
        return
    td = tempfile.mkdtemp(prefix="rettype_")
    tp = os.path.join(td, os.path.basename(src))

    def sc(changes) -> int:
        open(tp, "w").write(apply(txt, changes))
        return score(ovl, func, tp)

    base = sc([])
    if base == 0:
        return
    good = []
    best = (base, [])
    for c in cands:
        if TLIM and time.time() - T0 > TLIM:
            break
        s = sc([c])
        if s <= base and s < 1 << 30:
            good.append((s, c))
        if s < best[0]:
            best = (s, [c])
    good.sort(key=lambda x: x[0])
    tops = [c for _, c in good[:8]]
    for a, b in itertools.combinations(tops, 2):
        if TLIM and time.time() - T0 > TLIM:
            break
        s = sc([a, b])
        if s < best[0]:
            best = (s, [a, b])
    gainers = [c for s, c in good if s < base]
    if len(gainers) > 2:
        s = sc(gainers)
        if s < best[0]:
            best = (s, gainers)
    if best[0] < base:
        dst = outdir / ovl / os.path.basename(src)
        dst.parent.mkdir(parents=True, exist_ok=True)
        dst.write_text(apply(txt, best[1]))
        with lock:
            print(f"GAIN {ovl} {os.path.relpath(src, ROOT)} {base} -> {best[0]}  {label(best[1])}  ({dst})",
                  flush=True)


def drafts(ovl: str) -> list[str]:
    out = sorted(glob.glob(str(ROOT / f"nonmatchings/session141/{ovl}/func_*.c")))
    tsv = ROOT / "ovl" / ovl / "drafts.tsv"
    if tsv.exists():
        for ln in tsv.read_text().splitlines():
            f = ln.split("\t")
            if len(f) >= 2 and f[0].startswith("func_") and (ROOT / f[1]).exists():
                p = str(ROOT / f[1])
                if p not in out:
                    out.append(p)
    return out


def main() -> None:
    args = sys.argv[1:]
    outdir = ROOT / "out" / "rettype"
    if "--out" in args:
        i = args.index("--out")
        outdir = Path(args[i + 1]).resolve()
        del args[i:i + 2]
    reverse = "--no-reverse" not in args
    listonly = "--list" in args
    args = [a for a in args if not a.startswith("--")]
    jobs = []
    for a in args or overlays():
        if ":" in a:
            o, p = a.split(":", 1)
            jobs.append((o, str(Path(p).resolve())))
        else:
            jobs += [(a, p) for p in drafts(a)]
    it = iter(jobs)

    def worker() -> None:
        while True:
            with lock:
                j = next(it, None)
            if j is None or (TLIM and time.time() - T0 > TLIM):
                return
            try:
                sweep(j[0], j[1], outdir, reverse, listonly)
            except Exception as e:  # one bad draft should not stop the batch
                with lock:
                    print(f"ERROR {j[0]} {j[1]}: {e}", flush=True)

    ts = [threading.Thread(target=worker) for _ in range(max(1, JOBS))]
    for t in ts:
        t.start()
    for t in ts:
        t.join()
    print("done", len(jobs), "drafts", flush=True)


if __name__ == "__main__":
    main()
