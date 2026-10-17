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


# EE kernel syscall stubs (`li v1, N; syscall`) pass their arguments to the
# kernel, so the scan sees no reads. Integer argument counts from the public
# ps2sdk kernel.h prototypes.
SYSCALL_ARGS = {
    "ResetEE": 1, "SetGsCrt": 3, "Exit": 1, "LoadExecPS2": 3, "ExecPS2": 4,
    "AddIntcHandler": 3, "AddIntcHandler2": 3, "RemoveIntcHandler": 2, "AddDmacHandler": 3,
    "AddDmacHandler2": 3, "RemoveDmacHandler": 2, "_EnableIntc": 1, "_DisableIntc": 1,
    "_EnableDmac": 1, "_DisableDmac": 1, "_iEnableIntc": 1, "_iDisableIntc": 1, "_iEnableDmac": 1,
    "_iDisableDmac": 1, "CreateThread": 1, "DeleteThread": 1, "StartThread": 2, "ExitThread": 0,
    "ExitDeleteThread": 0, "TerminateThread": 1, "iTerminateThread": 1, "DisableDispatchThread": 0,
    "EnableDispatchThread": 0, "ChangeThreadPriority": 2, "iChangeThreadPriority": 2,
    "RotateThreadReadyQueue": 1, "iRotateThreadReadyQueue": 1, "ReleaseWaitThread": 1,
    "iReleaseWaitThread": 1, "GetThreadId": 0, "ReferThreadStatus": 2, "iReferThreadStatus": 2,
    "SleepThread": 0, "WakeupThread": 1, "iWakeupThread": 1, "CancelWakeupThread": 1,
    "iCancelWakeupThread": 1, "SuspendThread": 1, "iSuspendThread": 1, "ResumeThread": 1,
    "iResumeThread": 1, "SetupThread": 5, "SetupHeap": 2, "EndOfHeap": 0, "CreateSema": 1,
    "DeleteSema": 1, "SignalSema": 1, "iSignalSema": 1, "WaitSema": 1, "PollSema": 1, "iPollSema": 1,
    "ReferSemaStatus": 2, "iReferSemaStatus": 2, "SetOsdConfigParam": 1, "GetOsdConfigParam": 1,
    "GetGsHParam": 4, "GetGsVParam": 4, "SetGsHParam": 4, "SetGsVParam": 4, "FlushCache": 1,
    "iFlushCache": 1, "GsGetIMR": 0, "iGsGetIMR": 0, "GsPutIMR": 1, "iGsPutIMR": 1,
    "SetPgifHandler": 1, "SetVSyncFlag": 2, "SetSyscall": 2, "sceSifDmaStat": 1, "isceSifDmaStat": 1,
    "sceSifSetDma": 2, "isceSifSetDma": 2, "sceSifSetDChain": 0, "isceSifSetDChain": 0,
    "sceSifSetReg": 2, "sceSifGetReg": 1, "ExecOSD": 2, "Deci2Call": 2, "PSMode": 0,
    "MachineType": 0, "GetMemorySize": 0,
}


def analyse(cfg) -> dict[int, tuple[int, int, str]]:
    import mips
    funcs = disassemble(cfg)
    sig = {a: (0, 0, "void", False) for a in funcs}
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
    ARGSET = set(INT_ARGS) | set(FLT_ARGS)
    CLOBBER = frozenset({"v0", "v1", "$f0", "ra"} | set(INT_ARGS) | {f"$f{n}" for n in range(0, 20)})
    elf = K.require_orig(cfg)
    graphs = {a: _graph(a, insns, elf.read) for a, insns in funcs.items()}
    variadic = {a: v for a, insns in funcs.items() if (v := _variadic(insns))}
    syscalls = {a: SYSCALL_ARGS[n] for n, a in K.load_registry().items() if n in SYSCALL_ARGS and a in funcs}
    for _ in range(8):
        changed = False
        for a, insns in funcs.items():
            nodes, calls = graphs[a]
            live_in = _liveness(nodes, calls, sig, ARGSET, CLOBBER)
            if a in variadic:  # the named arguments only; the rest are spilled for va_arg
                live_in = set(INT_ARGS[:variadic[a][0]] + FLT_ARGS[:variadic[a][1]])
            ints = {r for r in live_in if r in INT_ARGS}
            flts = {r for r in live_in if r in FLT_ARGS}
            ret = set()
            tail = None
            for (mn, ops, w) in insns:
                rd, wr = rw(mn, ops)
                ret |= {r for r in wr if r in ("v0", "$f0")}
            for k, (t, is_tail) in calls.items():
                if is_tail:
                    tail = sig.get(t, (0, 0, "s32"))[2]
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
            if a in syscalls:
                ni, nf = syscalls[a], 0
            new = (ni, nf, rt, a in variadic)
            if new != sig[a]:
                sig[a] = new
                changed = True
        if not changed:
            break
    return sig


def _variadic(insns) -> tuple[int, int] | None:
    """Variadic functions spill the unnamed argument registers to their own
    frame in the prologue (`sd t3, N(sp)`, `swc1 f19, N(sp)`). Returns the
    number of named (int, float) arguments: the ones not spilled."""
    spilled_i, spilled_f = set(), set()
    for mn, ops, w in insns[:40]:
        if (w >> 21) & 31 != 29:
            continue
        o, r = w >> 26, (w >> 16) & 31
        if o in (0x2B, 0x3F) and 4 <= r <= 11:
            spilled_i.add(r - 4)
        elif o == 0x39 and 12 <= r <= 19:
            spilled_f.add(r - 12)
    if 7 not in spilled_i:
        return None
    ni = min(spilled_i)
    if spilled_i != set(range(ni, 8)) or ni > 5:  # one or two: a normal function out of saved registers
        return None
    nf = min(spilled_f) if 7 in spilled_f and spilled_f == set(range(min(spilled_f), 8)) else 0
    return ni, nf


def _graph(a: int, insns, read=None):
    """Per-instruction CFG with MIPS delay slots: [(reads, writes, succs)]
    and {node: (callee, is_tail)} for nodes after which a call happens."""
    import mips
    n = len(insns)
    end = a + 4 * n
    nodes = []
    calls: dict[int, tuple[int, bool]] = {}
    for k, (mn, ops, w) in enumerate(insns):
        rd, wr = rw(mn, ops)
        nodes.append([set(rd), set(wr), [k + 1] if k + 1 < n else []])
    # block starts not reached by fall-through (jump-table cases)
    unreached = set()
    for k, (mn, ops, w) in enumerate(insns):
        i = mips.Insn(a + 4 * k, w)
        d = k + 1  # delay slot
        if d >= n:
            continue
        if i.is_branch:
            t = (i.branch_target - a) // 4
            likely = mips.op(w) in (0x14, 0x15, 0x16, 0x17) or (mips.op(w) == 1 and mips.rt(w) in (2, 3, 0x12, 0x13)) \
                or (mips.op(w) in (0x11, 0x12) and (w >> 17) & 1)
            tgt = [t] if 0 <= t < n else []
            if (w >> 16) == 0x1000:  # b (beq zero, zero): no fall-through
                nodes[d][2] = tgt
                unreached.add(k + 2)
            elif likely:
                nodes[k][2] = [d] + ([k + 2] if k + 2 < n else [])
                nodes[d][2] = tgt
            else:
                nodes[d][2] = tgt + ([k + 2] if k + 2 < n else [])
        elif i.is_j:
            t = i.jump_target
            if a <= t < end:
                nodes[d][2] = [(t - a) // 4]
            else:
                nodes[d][2] = []
                calls[d] = (t, True)
            unreached.add(k + 2)
        elif i.is_jal:
            calls[d] = (i.jump_target, False)
        elif i.is_jalr:
            calls[d] = (-1, False)
        elif i.is_jr:
            if w == mips.JR_RA:
                nodes[d][2] = []
            else:
                nodes[d][2] = _jump_table(a, insns, k, read) or "jtbl"
            unreached.add(k + 2)
    cases = sorted(x for x in unreached if x < n)
    for nd in nodes:
        if nd[2] == "jtbl":
            nd[2] = cases
    return nodes, calls


def _jump_table(a: int, insns, k: int, read) -> list[int] | None:
    """Case targets (instruction indexes) of the jump-table `jr` at k:
    `lui b,%hi(T)` ... `lw r,%lo(T)(b)` (b indexed), bounded by `sltiu`."""
    import struct
    if read is None:
        return None
    w = insns[k][2]
    reg = (w >> 21) & 31
    lo = base = hi = count = None
    for j in range(k - 1, max(k - 14, -1), -1):
        x = insns[j][2]
        if lo is None and x >> 26 == 0x23 and (x >> 16) & 31 == reg:
            lo, base = x & 0xFFFF, (x >> 21) & 31
        elif lo is not None and hi is None and x >> 26 == 0x0F and (x >> 16) & 31 == base:
            hi = x & 0xFFFF
        elif x >> 26 == 0x0B and count is None:
            count = x & 0xFFFF
    if lo is None or hi is None:
        return None
    table = ((hi << 16) + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF
    n, out = len(insns), []
    for e in range(count or 512):
        blob = read(table + 4 * e, 4)
        if blob is None:
            break
        (t,) = struct.unpack("<I", blob)
        if not (a <= t < a + 4 * n) or t % 4:
            break
        out.append((t - a) // 4)
    return sorted(set(out)) or None


def _liveness(nodes, calls, sig, argset, clobber):
    n = len(nodes)
    live = [set() for _ in range(n)]
    changed = True
    while changed:
        changed = False
        for k in range(n - 1, -1, -1):
            rd, wr, succ = nodes[k]
            out = set()
            for s_ in succ:
                out |= live[s_]
            if k in calls:
                t, is_tail = calls[k]
                if t >= 0:
                    ni, nf = sig.get(t, (0, 0))[:2]
                    callee = set(INT_ARGS[:ni] + FLT_ARGS[:nf])
                else:
                    callee = set()
                out = callee | (set() if is_tail else out - clobber)
            new = (out - wr) | rd
            if new != live[k]:
                live[k] = new
                changed = True
    return live[0] if n else set()


def prototype(name: str, s: tuple) -> str:
    ni, nf, rt = s[:3]
    params = ["s32"] * ni + ["f32"] * nf
    if len(s) > 3 and s[3]:
        params.append("...")
    return f"{rt} {name}({', '.join(params) or 'void'});"


def write(cfg) -> dict[int, tuple[int, int, str]]:
    sig = analyse(cfg)
    names = {a: s for s, a in K.load_registry().items()}
    K.OUT.mkdir(exist_ok=True)
    SIGS_TSV.write_text("addr\tint_args\tfloat_args\treturn\tvariadic\n" +
                        "".join(f"{a:08x}\t{s[0]}\t{s[1]}\t{s[2]}\t{int(s[3])}\n" for a, s in sorted(sig.items())))
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
        a, ni, nf, rt, *var = line.split("\t")
        out[int(a, 16)] = (int(ni), int(nf), rt, bool(var and var[0] == "1"))
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
