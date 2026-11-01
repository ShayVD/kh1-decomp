#!/usr/bin/env python3
"""Translate the user's IOP sound driver (LIBSSL.IRX, from their own disc) to C at build time.

  python3 -I tools/host/iop_translate.py LIBSSL.IRX OUT.c [--stats]

The C is #included by host/port/iop.c (KH1_IOP_REC) and runs a driver function in place of the
interpreter when the module's relocated text is exactly the one translated (an FNV-1a of it, checked at
load).  It is derived from the user's own disc at build time and lands in out/gen/: never commit it
(README: no game data in this repository).  docs/sound-spec.md "The driver as C" has the details.

What it does:
  * loads and relocates the IRX at host/port/iop.c's base, as iop.c's loader does, and finds its import
    stubs (the library and number of each);
  * finds the functions: every `jal` target, plus code pointers built with lui / addiu (the timer
    handler, the threads, the RPC function) that start right after a `jr ra`'s delay slot;
  * follows each one's branches (and its jump tables: the code pointers in the module's data that fall
    inside the function) and writes it as one C function over the interpreter's state: the registers it
    uses in locals, the delay slots in place, the same memory helpers (rd32 ... wr8: the same bounds
    checks and alignment) and the same instruction count (kh1_iop_insns: each block adds its length);
  * a call to another translated function is a C call; to an import, iop.c's hle(); to anything else
    (or through a register), the interpreter, nested;
  * leaves to the interpreter every function that can block its thread (WaitSema, DelayThread, the RPC
    loop, directly or through a call), and any it cannot follow (an unknown opcode, a branch in a delay
    slot, a delay slot that changes $ra under a `jr ra`).
"""
from __future__ import annotations

import argparse
import struct
import sys

BASE = 0x00040000  # host/port/iop.c KH1_IOP_BASE
RAM_SIZE = 0x200000

# imports that can block the calling thread (iop.c's hle(): block())
BLOCKING = {("thbase", 0x21), ("thsemap", 8), ("sifcmd", 0x16)}


class Unsupported(Exception):
    pass


def le32(b, o):
    return struct.unpack_from("<I", b, o)[0]


def fnv1a(b: bytes) -> int:
    h = 2166136261
    for x in b:
        h = ((h ^ x) * 16777619) & 0xFFFFFFFF
    return h


def load(irx: bytes):
    """The module image at BASE as iop.c's kh1_iop_load leaves it before find_imports: (ram, text, text_size,
    code_ptrs) where code_ptrs are the R_MIPS_32-relocated words outside .text that point into it."""
    if irx[:4] != b"\x7fELF":
        raise SystemExit("not an ELF")
    shoff = le32(irx, 0x20)
    shnum = struct.unpack_from("<H", irx, 0x30)[0]
    ram = bytearray(RAM_SIZE)
    text = text_size = 0
    for i in range(shnum):
        name, typ, flags, addr, off, sz = struct.unpack_from("<6I", irx, shoff + i * 40)
        if not flags & 2:
            continue
        if typ == 1:
            ram[BASE + addr:BASE + addr + sz] = irx[off:off + sz]
            if flags & 4:
                text, text_size = BASE + addr, sz
    if not text:
        raise SystemExit("no .text")
    words32 = []
    for i in range(shnum):
        name, typ, flags, addr, off, sz = struct.unpack_from("<6I", irx, shoff + i * 40)
        if typ != 9:
            continue
        hi_pend = []
        for k in range(sz // 8):
            r_off, r_info = struct.unpack_from("<2I", irx, off + 8 * k)
            at = BASE + r_off
            t = r_info & 0xFF
            w = le32(ram, at)
            if t == 2:
                struct.pack_into("<I", ram, at, (w + BASE) & 0xFFFFFFFF)
                words32.append(at)
            elif t == 4:
                struct.pack_into("<I", ram, at, (w & 0xFC000000) | ((((w & 0x03FFFFFF) << 2) + BASE) >> 2 & 0x03FFFFFF))
            elif t == 5:
                if len(hi_pend) < 64:
                    hi_pend.append(at)
            elif t == 6:
                lo = w & 0xFFFF
                slo = lo - 0x10000 if lo & 0x8000 else lo
                for h in hi_pend:
                    hw = le32(ram, h)
                    v = (((hw & 0xFFFF) << 16) + slo + BASE) & 0xFFFFFFFF
                    struct.pack_into("<I", ram, h, (hw & 0xFFFF0000) | (((v + 0x8000) >> 16) & 0xFFFF))
                hi_pend = []
                struct.pack_into("<I", ram, at, (w & 0xFFFF0000) | ((lo + BASE) & 0xFFFF))
            elif t == 0:
                pass
            else:
                raise SystemExit("relocation type %d not handled" % t)
    code_ptrs = sorted({le32(ram, a) for a in words32
                        if not text <= a < text + text_size and text <= le32(ram, a) < text + text_size})
    return ram, text, text_size, code_ptrs


def find_imports(ram, text, size):
    """iop.c's find_imports: {stub address: (library, number)}"""
    stubs = {}
    a = text
    nlib = 0
    while a + 20 <= text + size:
        if le32(ram, a) != 0x41E00000 or nlib == 16:
            a += 4
            continue
        nlib += 1
        name = bytes(ram[a + 12:a + 20]).split(b"\0")[0].decode("latin-1")
        p = a + 20
        while p + 8 <= text + size and len(stubs) < 128:
            w0, w1 = le32(ram, p), le32(ram, p + 4)
            if w0 != 0x03E00008 or (w1 & 0xFFFF0000) != 0x24000000:
                break
            stubs[p] = (name, w1 & 0xFFFF)
            p += 8
        a = p + 4
    return stubs


# ---------------------------------------------------------------- decode --------

def s16(x):
    return x - 0x10000 if x & 0x8000 else x


class Ins:
    __slots__ = ("pc", "op", "kind", "rs", "rt", "rd", "sa", "imm", "target", "reads", "writes")

    def __init__(self, pc, op):
        self.pc, self.op = pc, op
        self.rs, self.rt, self.rd, self.sa = (op >> 21) & 31, (op >> 16) & 31, (op >> 11) & 31, (op >> 6) & 31
        self.imm = op & 0xFFFF
        self.target = None
        self.kind = "op"
        self.reads, self.writes = set(), set()


SPECIAL = {0: "sll", 2: "srl", 3: "sra", 4: "sllv", 6: "srlv", 7: "srav", 8: "jr", 9: "jalr", 12: "syscall",
           13: "break", 16: "mfhi", 17: "mthi", 18: "mflo", 19: "mtlo", 24: "mult", 25: "multu", 26: "div",
           27: "divu", 32: "add", 33: "add", 34: "sub", 35: "sub", 36: "and", 37: "or", 38: "xor", 39: "nor",
           42: "slt", 43: "sltu"}
MAIN = {2: "j", 3: "jal", 4: "beq", 5: "bne", 6: "blez", 7: "bgtz", 8: "addi", 9: "addi", 10: "slti", 11: "sltiu",
        12: "andi", 13: "ori", 14: "xori", 15: "lui", 16: "cop0", 32: "lb", 33: "lh", 34: "lwl", 35: "lw", 36: "lbu",
        37: "lhu", 38: "lwr", 40: "sb", 41: "sh", 42: "swl", 43: "sw", 46: "swr"}
BRANCHES = {"beq", "bne", "blez", "bgtz", "bltz", "bgez", "bltzal", "bgezal"}
JUMPS = {"j", "jal", "jr", "jalr"}


def decode(ram, pc) -> Ins:
    op = le32(ram, pc)
    i = Ins(pc, op)
    prim = op >> 26
    if prim == 0:
        name = SPECIAL.get(op & 63)
    elif prim == 1:
        name = {0: "bltz", 1: "bgez", 0x10: "bltzal", 0x11: "bgezal"}.get(i.rt)
    else:
        name = MAIN.get(prim)
    if name is None:
        raise Unsupported("unknown instruction 0x%08x at +0x%x" % (op, pc - BASE))
    i.kind = name
    if name in ("beq", "bne"):
        i.reads = {i.rs, i.rt}
    elif name in ("blez", "bgtz", "bltz", "bgez"):
        i.reads = {i.rs}
    elif name in ("bltzal", "bgezal"):
        i.reads, i.writes = {i.rs}, {31}
    if name in BRANCHES:
        i.target = (pc + 4 + (s16(i.imm) << 2)) & 0xFFFFFFFF
    elif name in ("j", "jal"):
        i.target = ((pc + 4) & 0xF0000000) | ((op & 0x03FFFFFF) << 2)
        if name == "jal":
            i.writes = {31}
    elif name == "jr":
        i.reads = {i.rs}
    elif name == "jalr":
        i.reads, i.writes = {i.rs}, {i.rd}
    elif name in ("sll", "srl", "sra"):
        i.reads, i.writes = {i.rt}, {i.rd}
    elif name in ("sllv", "srlv", "srav", "add", "sub", "and", "or", "xor", "nor", "slt", "sltu"):
        i.reads, i.writes = {i.rs, i.rt}, {i.rd}
    elif name in ("mfhi", "mflo"):
        i.writes = {i.rd}
    elif name in ("mthi", "mtlo"):
        i.reads = {i.rs}
    elif name in ("mult", "multu", "div", "divu"):
        i.reads = {i.rs, i.rt}
    elif name in ("addi", "slti", "sltiu", "andi", "ori", "xori"):
        i.reads, i.writes = {i.rs}, {i.rt}
    elif name == "lui":
        i.writes = {i.rt}
    elif name == "cop0":
        i.writes = {i.rt} if i.rs == 0 else set()
    elif name in ("lb", "lh", "lw", "lbu", "lhu"):
        i.reads, i.writes = {i.rs}, {i.rt}
    elif name in ("lwl", "lwr"):
        i.reads, i.writes = {i.rs, i.rt}, {i.rt}
    elif name in ("sb", "sh", "sw", "swl", "swr"):
        i.reads = {i.rs, i.rt}
    i.reads.discard(0)
    i.writes.discard(0)
    return i


def is_uncond(i: Ins) -> bool:
    return (i.kind == "beq" and i.rs == 0 and i.rt == 0) or (i.kind == "bgez" and i.rs == 0)


# ---------------------------------------------------------------- functions --------

class Func:
    def __init__(self, start):
        self.start = start
        self.ins = {}          # pc -> Ins (the slots included)
        self.leaders = {start}
        self.calls = set()     # jal / tail-j targets
        self.imports = set()   # stub addresses called
        self.tables = {}       # jr pc -> [targets]
        self.why = None        # why it is left to the interpreter
        self.blocks = False


def discover(ram, text, size, stubs, code_ptrs):
    starts = set()
    for a in range(text, text + size, 4):
        if a in stubs or a - 4 in stubs:
            continue
        i_op = le32(ram, a)
        if i_op >> 26 == 3:
            t = ((a + 4) & 0xF0000000) | ((i_op & 0x03FFFFFF) << 2)
            if text <= t < text + size and t not in stubs:
                starts.add(t)
    # code pointers made with lui + addiu (callbacks handed to the kernel), right after a function's end
    for a in range(text, text + size - 4, 4):
        w = le32(ram, a)
        if w >> 26 != 15:
            continue
        rt = (w >> 16) & 31
        for b in range(a + 4, min(a + 24, text + size), 4):
            w2 = le32(ram, b)
            if w2 >> 26 == 9 and (w2 >> 21) & 31 == rt:
                t = (((w & 0xFFFF) << 16) + s16(w2 & 0xFFFF)) & 0xFFFFFFFF
                if text < t < text + size and t % 4 == 0 and le32(ram, t - 8) == 0x03E00008 and t not in stubs:
                    starts.add(t)
                break
    return sorted(starts)


def follow(ram, text, size, stubs, starts_sorted, start_set, code_ptrs, f: Func):
    nxt = [s for s in starts_sorted if s > f.start]
    end_guess = nxt[0] if nxt else text + size
    work = [f.start]
    seen = set()
    while work:
        pc = work.pop()
        while True:
            if pc in seen:
                break
            if not text <= pc < text + size or pc in stubs:
                raise Unsupported("runs out of the text at +0x%x" % (pc - BASE))
            seen.add(pc)
            i = decode(ram, pc)
            f.ins[pc] = i
            if i.kind in BRANCHES or i.kind in JUMPS:
                slot = decode(ram, pc + 4)
                if slot.kind in BRANCHES or slot.kind in JUMPS:
                    raise Unsupported("a branch in a delay slot at +0x%x" % (pc + 4 - BASE))
                f.ins[pc + 4] = slot
                seen.add(pc + 4)
                if i.kind in BRANCHES:
                    if i.kind in ("bltzal", "bgezal"):
                        raise Unsupported("bltzal / bgezal at +0x%x" % (pc - BASE))
                    f.leaders.add(i.target)
                    work.append(i.target)
                    if is_uncond(i):
                        break
                    f.leaders.add(pc + 8)
                    pc += 8
                    continue
                if i.kind == "jal":
                    if i.target in stubs:
                        f.imports.add(i.target)
                    else:
                        f.calls.add(i.target)
                    f.leaders.add(pc + 8)
                    pc += 8
                    continue
                if i.kind == "jalr":
                    f.leaders.add(pc + 8)
                    pc += 8
                    continue
                if i.kind == "j":
                    if i.target in stubs:
                        f.imports.add(i.target)
                        break
                    if i.target in start_set and i.target != f.start:
                        f.calls.add(i.target)
                        break
                    f.leaders.add(i.target)
                    work.append(i.target)
                    break
                if i.kind == "jr":
                    if i.rs == 31:
                        if 31 in slot.writes:
                            raise Unsupported("the slot of a jr ra writes ra at +0x%x" % (pc + 4 - BASE))
                        break
                    tg = [t for t in code_ptrs if f.start <= t < end_guess]
                    f.tables[pc] = tg
                    for t in tg:
                        f.leaders.add(t)
                        work.append(t)
                    break
            pc += 4  # (a syscall / break is a fault: the C reports it and returns)
    return f


# ---------------------------------------------------------------- emit --------

def R(n):
    return "0u" if n == 0 else "r%d" % n


def emit_op(i: Ins, fn_of, out):
    """C for one non-control instruction"""
    k, rs, rt, rd, sa = i.kind, R(i.rs), R(i.rt), i.rd, i.sa
    imm = "0x%xu" % (s16(i.imm) & 0xFFFFFFFF)
    immu = "0x%xu" % i.imm
    pc = "0x%x" % i.pc

    def setr(n, expr):
        if n:
            out.append("r%d = %s;" % (n, expr))

    if k == "sll":
        if i.op:
            setr(rd, "%s << %d" % (R(i.rt), sa))
    elif k == "srl":
        setr(rd, "%s >> %d" % (R(i.rt), sa))
    elif k == "sra":
        setr(rd, "(u32)((s32)%s >> %d)" % (R(i.rt), sa))
    elif k == "sllv":
        setr(rd, "%s << (%s & 31)" % (rt, rs))
    elif k == "srlv":
        setr(rd, "%s >> (%s & 31)" % (rt, rs))
    elif k == "srav":
        setr(rd, "(u32)((s32)%s >> (%s & 31))" % (rt, rs))
    elif k == "mfhi":
        setr(rd, "hi")
    elif k == "mflo":
        setr(rd, "lo")
    elif k == "mthi":
        out.append("hi = %s;" % rs)
    elif k == "mtlo":
        out.append("lo = %s;" % rs)
    elif k == "mult":
        out.append("{ s64 p_ = (s64)(s32)%s * (s32)%s; lo = (u32)p_; hi = (u32)((u64)p_ >> 32); }" % (rs, rt))
    elif k == "multu":
        out.append("{ u64 p_ = (u64)%s * %s; lo = (u32)p_; hi = (u32)(p_ >> 32); }" % (rs, rt))
    elif k == "div":
        out.append("REC_DIV(%s, %s);" % (rs, rt))
    elif k == "divu":
        out.append("REC_DIVU(%s, %s);" % (rs, rt))
    elif k == "add":
        setr(rd, "%s + %s" % (rs, rt))
    elif k == "sub":
        setr(rd, "%s - %s" % (rs, rt))
    elif k == "and":
        setr(rd, "%s & %s" % (rs, rt))
    elif k == "or":
        setr(rd, "%s | %s" % (rs, rt))
    elif k == "xor":
        setr(rd, "%s ^ %s" % (rs, rt))
    elif k == "nor":
        setr(rd, "~(%s | %s)" % (rs, rt))
    elif k == "slt":
        setr(rd, "(u32)((s32)%s < (s32)%s)" % (rs, rt))
    elif k == "sltu":
        setr(rd, "(u32)(%s < %s)" % (rs, rt))
    elif k == "addi":
        setr(i.rt, "%s + %s" % (rs, imm))
    elif k == "slti":
        setr(i.rt, "(u32)((s32)%s < (s32)%s)" % (rs, imm))
    elif k == "sltiu":
        setr(i.rt, "(u32)(%s < %s)" % (rs, imm))
    elif k == "andi":
        setr(i.rt, "%s & %s" % (rs, immu))
    elif k == "ori":
        setr(i.rt, "%s | %s" % (rs, immu))
    elif k == "xori":
        setr(i.rt, "%s ^ %s" % (rs, immu))
    elif k == "lui":
        setr(i.rt, "0x%xu" % (i.imm << 16))
    elif k == "cop0":
        if i.rs == 0:
            setr(i.rt, "0")
    elif k in ("lb", "lh", "lw", "lbu", "lhu"):
        ex = {"lb": "(u32)(s32)(s8)rd8(%s, %s)", "lh": "(u32)(s32)(s16)rd16(%s, %s)", "lw": "rd32(%s, %s)",
              "lbu": "rd8(%s, %s)", "lhu": "rd16(%s, %s)"}[k] % ("%s + %s" % (rs, imm), pc)
        if i.rt:
            out.append("r%d = %s;" % (i.rt, ex))
        else:
            out.append("(void)%s;" % ex)
    elif k in ("lwl", "lwr"):
        out.append("{ u32 ad_ = %s + %s, sh_ = (ad_ & 3) * 8, w_ = rd32(ad_, %s); " % (rs, imm, pc)
                   + ("%s;" % ("r%d = (r%d & (0x00FFFFFFu >> sh_)) | (w_ << (24 - sh_))" % (i.rt, i.rt) if k == "lwl"
                               else "r%d = (r%d & (0xFFFFFF00u << (24 - sh_))) | (w_ >> sh_)" % (i.rt, i.rt))
                      if i.rt else "(void)w_;") + " }")
    elif k in ("sb", "sh", "sw"):
        out.append("wr%s(%s + %s, %s, %s);" % ({"sb": "8", "sh": "16", "sw": "32"}[k], rs, imm, rt, pc))
    elif k == "swl":
        out.append("{ u32 ad_ = %s + %s, sh_ = (ad_ & 3) * 8, w_ = rd32(ad_, %s); "
                   "wr32(ad_, (w_ & (0xFFFFFF00u << sh_)) | (%s >> (24 - sh_)), %s); }" % (rs, imm, pc, rt, pc))
    elif k == "swr":
        out.append("{ u32 ad_ = %s + %s, sh_ = (ad_ & 3) * 8, w_ = rd32(ad_, %s); "
                   "wr32(ad_, (w_ & (0x00FFFFFFu >> (24 - sh_))) | (%s << sh_), %s); }" % (rs, imm, pc, rt, pc))
    elif k in ("syscall", "break"):
        out.append("SPILL(); REC_FAULT(%s); return;" % pc)
    else:
        raise Unsupported("no C for %s at +0x%x" % (k, i.pc - BASE))


def gen_func(f: Func, rec_idx, stub_idx, out):
    regs = set()
    hilo = False
    for i in f.ins.values():
        regs |= i.reads | i.writes
        if i.kind in ("mfhi", "mflo", "mthi", "mtlo", "mult", "multu", "div", "divu"):
            hilo = True
    if any(i.kind in ("jal", "jalr", "bltzal", "bgezal") for i in f.ins.values()):
        regs.add(31)
    regs = sorted(regs)
    name = "rec_%05x" % (f.start - BASE)
    out.append("static void %s(IopCtx *c) {" % name)
    if regs:
        out.append("    u32 %s;" % ", ".join("r%d = c->r[%d]" % (r, r) for r in regs))
    out.append("    u32 hi = c->hi, lo = c->lo, n_ = 0;" if hilo else "    u32 n_ = 0;")
    spill = " ".join("c->r[%d] = r%d;" % (r, r) for r in regs) + (" c->hi = hi; c->lo = lo;" if hilo else "")
    spill += " kh1_iop_insns += n_; n_ = 0;"
    reload = " ".join("r%d = c->r[%d];" % (r, r) for r in regs) + (" hi = c->hi; lo = c->lo;" if hilo else "")
    out.append("#undef SPILL\n#define SPILL() do { %s } while (0)" % spill)
    out.append("#undef RELOAD\n#define RELOAD() do { %s } while (0)" % reload)

    order = sorted(f.ins)
    # a slot is emitted with its branch; it gets a label of its own only if something jumps to it
    slots = {pc + 4 for pc, i in f.ins.items() if i.kind in BRANCHES or i.kind in JUMPS}
    main = [pc for pc in order if pc not in slots or pc in f.leaders]
    # the instruction count: each leader's straight run up to and including the first control
    # instruction's slot (or the next leader)
    def run_len(pc):
        n = 0
        while pc in f.ins:
            i = f.ins[pc]
            n += 1
            if i.kind in BRANCHES or i.kind in JUMPS:
                return n + 1
            pc += 4
            if pc in f.leaders:
                return n
        return n

    def call_to(t, retpc, tail=False):
        """a call to t (jal, or a j to another function)"""
        if t in stub_idx:
            s = "n_++; SPILL(); c->pc = 0x%x; REC_IMPORT(%d); RELOAD();" % (t, stub_idx[t])  # the stub's jr ra counts one, as in run()
        elif t in rec_idx:
            s = "SPILL(); rec_%05x(c); RELOAD();" % (t - BASE)
        else:
            s = "SPILL(); rec_interp(c, 0x%x); RELOAD();" % t
        if not tail:
            s += " if (r31 != 0x%xu) REC_BADRET(0x%x);" % (retpc, retpc)
        return s

    for idx, pc in enumerate(main):
        i = f.ins[pc]
        body = []
        if pc in f.leaders:
            body.append("L_%x: n_ += %d;" % (pc, run_len(pc)))
        nxt = main[idx + 1] if idx + 1 < len(main) else None
        falls_to = None
        if pc in slots:
            # a delay slot something branches to: run it alone, then on to the instruction after it
            emit_op(i, None, body)
            falls_to = pc + 4
        elif i.kind in BRANCHES:
            s = f.ins[pc + 4]
            cond = {"beq": "%s == %s" % (R(i.rs), R(i.rt)), "bne": "%s != %s" % (R(i.rs), R(i.rt)),
                    "blez": "(s32)%s <= 0" % R(i.rs), "bgtz": "(s32)%s > 0" % R(i.rs),
                    "bltz": "(s32)%s < 0" % R(i.rs), "bgez": "(s32)%s >= 0" % R(i.rs)}[i.kind]
            sl = []
            emit_op(s, None, sl)
            if is_uncond(i):
                body.append("%s goto L_%x;" % (" ".join(sl), i.target))
            else:
                body.append("{ int t_ = %s; %s if (t_) goto L_%x; }" % (cond, " ".join(sl), i.target))
                falls_to = pc + 8
        elif i.kind == "jal":
            sl = []
            emit_op(f.ins[pc + 4], None, sl)
            body.append("r31 = 0x%xu; %s %s" % (pc + 8, " ".join(sl), call_to(i.target, pc + 8)))
            falls_to = pc + 8
        elif i.kind == "jalr":
            sl = []
            emit_op(f.ins[pc + 4], None, sl)
            body.append("{ u32 t_ = %s; %s%s SPILL(); rec_call_ind(c, t_); RELOAD(); if (r31 != 0x%xu) REC_BADRET(0x%x); }"
                        % (R(i.rs), ("r%d = 0x%xu; " % (i.rd, pc + 8)) if i.rd else "", " ".join(sl), pc + 8, pc + 8))
            falls_to = pc + 8
        elif i.kind == "j":
            sl = []
            emit_op(f.ins[pc + 4], None, sl)
            if i.target in f.leaders and i.target in f.ins and not (i.target in stub_idx):
                body.append("%s goto L_%x;" % (" ".join(sl), i.target))
            else:
                body.append("%s %s return;" % (" ".join(sl), call_to(i.target, 0, tail=True)))
        elif i.kind == "jr":
            sl = []
            emit_op(f.ins[pc + 4], None, sl)
            if i.rs == 31:
                body.append("%s SPILL(); return;" % " ".join(sl))
            else:
                cases = " ".join("case 0x%xu: goto L_%x;" % (t, t) for t in f.tables.get(pc, []))
                body.append("{ u32 t_ = %s; %s switch (t_) { %s default: SPILL(); rec_jump_out(c, t_); return; } }"
                            % (R(i.rs), " ".join(sl), cases))
        else:
            emit_op(i, None, body)
            falls_to = pc + 4
        out.append("    " + " ".join(body))
        if falls_to is not None and falls_to != nxt:
            if falls_to in f.ins:
                if falls_to not in f.leaders:
                    raise Unsupported("internal: falls to a non-leader +0x%x" % (falls_to - BASE))
                out.append("    goto L_%x;" % falls_to)
            else:
                raise Unsupported("falls off its end at +0x%x" % (falls_to - BASE))
    out.append("}")
    return name


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("irx")
    ap.add_argument("out")
    ap.add_argument("--stats", action="store_true")
    a = ap.parse_args()
    irx = open(a.irx, "rb").read()
    ram, text, size, code_ptrs = load(irx)
    h = fnv1a(bytes(ram[text:text + size]))
    stubs = find_imports(ram, text, size)
    starts = discover(ram, text, size, stubs, code_ptrs)
    start_set = set(starts)
    funcs = {}
    for s in starts:
        f = Func(s)
        try:
            follow(ram, text, size, stubs, starts, start_set, code_ptrs, f)
            # a leader past a slot must exist as an instruction
            for l in list(f.leaders):
                if l not in f.ins:
                    f.leaders.discard(l)
        except Unsupported as e:
            f.why = str(e)
        funcs[s] = f
    # blocking, through calls (a call to a function we do not know is taken as not blocking)
    for f in funcs.values():
        if any(stubs[t] in BLOCKING for t in f.imports):
            f.blocks = True
    changed = True
    while changed:
        changed = False
        for f in funcs.values():
            if not f.blocks and any(funcs[t].blocks for t in f.calls if t in funcs):
                f.blocks = changed = True
    for f in funcs.values():
        if f.blocks and not f.why:
            f.why = "can block its thread"
    rec = [s for s in starts if not funcs[s].why]
    # try to emit each; one that fails is left to the interpreter (its callers call it through rec_interp)
    stub_list = sorted({t for s in rec for t in funcs[s].imports})
    stub_idx = {t: k for k, t in enumerate(stub_list)}
    while True:
        rec_idx = {s: k for k, s in enumerate(rec)}
        bodies = []
        bad = None
        for s in rec:
            try:
                o = []
                gen_func(funcs[s], rec_idx, stub_idx, o)
                bodies.append(o)
            except Unsupported as e:
                bad = (s, str(e))
                break
        if not bad:
            break
        funcs[bad[0]].why = bad[1]
        rec.remove(bad[0])

    out = ["/* Generated by tools/host/iop_translate.py from the user's own LIBSSL.IRX: never commit (out/gen/). */",
           "#define REC_TEXT_OFF 0x%xu" % (text - BASE), "#define REC_TEXT_SIZE 0x%xu" % size,
           "#define REC_HASH 0x%08xu" % h, "#define REC_N %d" % len(rec), "#define REC_NSTUBS %d" % len(stub_list),
           "static const u32 rec_stub_addr[REC_NSTUBS + 1] = { %s0 };" % "".join("0x%xu, " % t for t in stub_list)]
    for s in rec:
        out.append("static void rec_%05x(IopCtx *c);" % (s - BASE))
    for b in bodies:
        out.extend(b)
    out.append("#undef SPILL\n#undef RELOAD")
    out.append("static const struct { u32 addr; void (*fn)(IopCtx *c); } rec_table[REC_N + 1] = {")
    for s in rec:
        out.append("    { 0x%xu, rec_%05x }," % (s, s - BASE))
    out.append("    { 0, 0 } };")
    with open(a.out, "w") as fo:
        fo.write("\n".join(out) + "\n")
    left = [f for f in funcs.values() if f.why]
    print("iop_translate: %d of %d driver functions as C (%d left to the interpreter: %d can block)"
          % (len(rec), len(funcs), len(left), sum(1 for f in left if f.blocks)))
    if a.stats:
        for f in sorted(left, key=lambda f: f.start):
            print("  +0x%05x %s" % (f.start - BASE, f.why))


if __name__ == "__main__":
    main()
