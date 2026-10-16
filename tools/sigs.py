#!/usr/bin/env python3
"""Guess every function's signature from the original machine code.

For each function in layout.tsv: which argument registers it reads before
writing them (a0-a3, t0-t3 are int args 1-8 under the EE ABI; f12-f19 are
float args, numbered independently), and whether it returns a value in v0
or f0. Calls count as reads of the callee's arguments, so the analysis is
iterated to a fixpoint. The scan is linear (it ignores control flow), so it
is a heuristic: good enough to tell m2c how many arguments a callee takes,
not a recovered prototype.

Writes out/sigs.tsv and out/sigs.h (prototypes, m2c --context). Used by
tools/autodecomp.py; `tools/sigs.py func_00123456` prints one guess.
"""
from __future__ import annotations

import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kh1tool as K  # noqa: E402

SIGS_TSV = K.OUT / "sigs.tsv"
SIGS_H = K.OUT / "sigs.h"
INT_ARGS = ["a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3"]
FLT_ARGS = [f"$f{n}" for n in range(12, 20)]
LINE_RE = re.compile(r"^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(\S+)\s*(.*)$")
REG_RE = re.compile(r"\$?\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|\$f\d+|f\d+)\b")
READS_ALL = re.compile(r"^(s[bhwdq]|s[wd][lr]|swc1|sdc1|sqc2|b\w*|jr|mt(hi|lo)[01]?|mtsa|c\.\w+|teq|tne|cache|sync)$")
WRITES_SECOND = {"mtc1", "ctc1", "dmtc1"}  # mtc1 rt, fs: reads rt, writes fs


def norm(r: str) -> str:
    r = r.lstrip("$")
    return "$" + r if r.startswith("f") and r[1:].isdigit() else r


def rw(mn: str, ops: str) -> tuple[list[str], list[str]]:
    """(read, written) registers of one objdump instruction."""
    regs = [norm(m.group(1)) for m in REG_RE.finditer(ops.split("<")[0])]
    if mn in ("jal", "j", "nop", "syscall", "break", "eret"):
        return [], []
    if mn == "jalr":
        return regs[-1:], ["ra"]
    if READS_ALL.match(mn):
        return regs, []
    if mn in WRITES_SECOND:
        return regs[:1], regs[1:2]
    if mn in ("mult", "multu", "div", "divu", "mult1", "multu1", "div1", "divu1", "madd", "maddu") and len(regs) == 2:
        return regs, []
    return regs[1:], regs[:1]


def disassemble(cfg) -> dict[int, list[tuple[str, str]]]:
    layout = K.load_layout()
    start, end = layout[0].addr, layout[-1].end
    out = subprocess.run([f"{K.BINUTILS}objdump", "-D", "-z", "-m", "mips:5900", "-EL", "-M", "gpr-names=32",
                          f"--start-address=0x{start:x}", f"--stop-address=0x{end:x}", str(K.orig_path(cfg))],
                         check=True, capture_output=True, text=True).stdout
    insns: dict[int, tuple[int, str, str]] = {}
    for line in out.splitlines():
        m = LINE_RE.match(line)
        if m:
            insns[int(m.group(1), 16)] = (int(m.group(2), 16), m.group(3), m.group(4))
    funcs = {}
    for f in layout:
        funcs[f.addr] = [(insns[a][1], insns[a][2]) + (insns[a][0],) for a in range(f.addr, f.end, 4) if a in insns]
    return funcs


def analyse(cfg) -> dict[int, tuple[int, int, str]]:
    import mips
    funcs = disassemble(cfg)
    sig = {a: (0, 0, "void") for a in funcs}
    # Return values: a callee returns something if a caller reads v0 (or f0)
    # after the call before writing it.
    used_ret: dict[int, str] = {}
    callers: dict[int, int] = {}
    for a, insns in funcs.items():
        for k, (mn, ops, w) in enumerate(insns):
            i = mips.Insn(a + 4 * k, w)
            if not i.is_jal:
                continue
            t = i.jump_target
            callers[t] = callers.get(t, 0) + 1
            for mn2, ops2, w2 in insns[k + 2:]:
                j = mips.Insn(0, w2)
                rd, wr = rw(mn2, ops2)
                hit = next((r for r in ("v0", "$f0") if r in rd), None)
                if hit:
                    used_ret.setdefault(t, hit)
                    break
                if j.is_jal or j.is_jr or j.is_j or "v0" in wr or "$f0" in wr:
                    break
    for _ in range(6):
        changed = False
        for a, insns in funcs.items():
            written: set[str] = set()
            ints, flts = set(), set()
            ret = set()
            tail = None
            k = 0
            seq = []
            # Put each delay-slot instruction before its jump/branch.
            while k < len(insns):
                cur = insns[k]
                w = cur[2]
                i = mips.Insn(a + 4 * k, w)
                if (i.is_jal or i.is_j or i.is_jr or i.is_jalr or i.is_branch) and k + 1 < len(insns):
                    seq.append((a + 4 * k + 4, insns[k + 1]))
                    seq.append((a + 4 * k, cur))
                    k += 2
                else:
                    seq.append((a + 4 * k, cur))
                    k += 1
            for addr, (mn, ops, w) in seq:
                i = mips.Insn(addr, w)
                if i.is_jal or (i.is_j and not a <= i.jump_target < a + 4 * len(insns)):
                    t = i.jump_target
                    ni, nf, r = sig.get(t, (0, 0, "s32"))
                    reads = INT_ARGS[:ni] + FLT_ARGS[:nf]
                    for r_ in reads:
                        if r_ not in written:
                            (ints if r_ in INT_ARGS else flts).add(r_)
                    if i.is_j:
                        tail = r
                    else:
                        written |= {"v0", "v1", "$f0", "ra"} | set(INT_ARGS) | {f"$f{n}" for n in range(0, 20)}
                    continue
                rd, wr = rw(mn, ops)
                for r_ in rd:
                    if r_ not in written:
                        if r_ in INT_ARGS:
                            ints.add(r_)
                        elif r_ in FLT_ARGS:
                            flts.add(r_)
                for r_ in wr:
                    written.add(r_)
                    if r_ in ("v0", "$f0"):
                        ret.add(r_)
            ni = max((INT_ARGS.index(r) + 1 for r in ints), default=0)
            nf = max((FLT_ARGS.index(r) + 1 for r in flts), default=0)
            if a in used_ret:
                rt = "f32" if used_ret[a] == "$f0" else "s32"
            elif "$f0" in ret and "v0" not in ret:
                rt = "f32"
            elif ret and not callers.get(a):
                rt = "s32"
            else:
                rt = "void" if callers.get(a) else (tail or "void")
            new = (ni, nf, rt)
            if new != sig[a]:
                sig[a] = new
                changed = True
        if not changed:
            break
    return sig


def prototype(name: str, s: tuple[int, int, str]) -> str:
    ni, nf, rt = s
    params = ["s32"] * ni + ["f32"] * nf
    return f"{rt} {name}({', '.join(params) or 'void'});"


def write(cfg) -> dict[int, tuple[int, int, str]]:
    sig = analyse(cfg)
    names = {a: s for s, a in K.load_registry().items()}
    K.OUT.mkdir(exist_ok=True)
    SIGS_TSV.write_text("addr\tint_args\tfloat_args\treturn\n" +
                        "".join(f"{a:08x}\t{s[0]}\t{s[1]}\t{s[2]}\n" for a, s in sorted(sig.items())))
    lines = ["typedef signed int s32;", "typedef float f32;"]
    lines += [prototype(names.get(a, f"func_{a:08x}"), s) for a, s in sorted(sig.items())
              if re.match(r"^[A-Za-z_]\w*$", names.get(a, f"func_{a:08x}"))]
    SIGS_H.write_text("\n".join(lines) + "\n")
    return sig


def load() -> dict[int, tuple[int, int, str]]:
    if not SIGS_TSV.exists():
        return write(K.load_config())
    out = {}
    for line in SIGS_TSV.read_text().splitlines()[1:]:
        a, ni, nf, rt = line.split("\t")
        out[int(a, 16)] = (int(ni), int(nf), rt)
    return out


def main() -> int:
    cfg = K.load_config()
    sig = write(cfg)
    names = {a: s for s, a in K.load_registry().items()}
    for fn in sys.argv[1:]:
        f = K.find_func(fn)
        print(prototype(names.get(f.addr, f"func_{f.addr:08x}"), sig[f.addr]))
    if not sys.argv[1:]:
        print(f"wrote {SIGS_TSV.relative_to(K.ROOT)} and {SIGS_H.relative_to(K.ROOT)} ({len(sig)} functions)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
