"""Just enough R5900 (PS2 EE) instruction decoding to classify functions.

Not a disassembler: it answers questions like "is this a call", "is this a
branch and where to", "does this touch the FPU / VU0 / 128-bit MMI". Use
mips-linux-gnu-objdump -m mips:5900 for real disassembly.
"""
from __future__ import annotations

from dataclasses import dataclass

JR_RA = 0x03E00008
NOP = 0

# Primary opcodes.
OP_SPECIAL, OP_REGIMM, OP_J, OP_JAL = 0x00, 0x01, 0x02, 0x03
OP_BRANCH = {0x04, 0x05, 0x06, 0x07, 0x14, 0x15, 0x16, 0x17}  # beq bne blez bgtz + likely
OP_COP0, OP_COP1, OP_COP2 = 0x10, 0x11, 0x12
OP_MMI = 0x1C
OP_LQ, OP_SQ = 0x1E, 0x1F
OP_LOADS = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x1A, 0x1B, 0x37, 0x31, 0x35}
OP_STORES = {0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x3F, 0x39, 0x3D}
OP_FPU_MEM = {0x31, 0x39, 0x35, 0x3D}  # lwc1 swc1 ldc1 sdc1
OP_VU_MEM = {0x36, 0x3E}  # lqc2 sqc2
OP_LUI = 0x0F


def op(w: int) -> int:
    return w >> 26


def rs(w: int) -> int:
    return (w >> 21) & 31


def rt(w: int) -> int:
    return (w >> 16) & 31


def rd(w: int) -> int:
    return (w >> 11) & 31


def funct(w: int) -> int:
    return w & 63


def imm(w: int) -> int:
    v = w & 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


@dataclass(frozen=True)
class Insn:
    addr: int
    word: int

    @property
    def is_jal(self) -> bool:
        return op(self.word) == OP_JAL

    @property
    def is_jalr(self) -> bool:
        return op(self.word) == OP_SPECIAL and funct(self.word) == 0x09

    @property
    def is_j(self) -> bool:
        return op(self.word) == OP_J

    @property
    def is_jr(self) -> bool:
        return op(self.word) == OP_SPECIAL and funct(self.word) == 0x08

    @property
    def is_jr_ra(self) -> bool:
        return self.word == JR_RA

    @property
    def jump_target(self) -> int | None:
        if op(self.word) in (OP_J, OP_JAL):
            return ((self.addr + 4) & 0xF0000000) | ((self.word & 0x3FFFFFF) << 2)
        return None

    @property
    def is_branch(self) -> bool:
        o = op(self.word)
        if o in OP_BRANCH:
            return True
        if o == OP_REGIMM:
            return rt(self.word) in (0x00, 0x01, 0x02, 0x03, 0x10, 0x11, 0x12, 0x13)
        if o in (OP_COP1, OP_COP2) and rs(self.word) == 0x08:  # bc1x / bc2x
            return True
        return False

    @property
    def branch_target(self) -> int | None:
        return self.addr + 4 + imm(self.word) * 4 if self.is_branch else None

    @property
    def is_load(self) -> bool:
        return op(self.word) in OP_LOADS

    @property
    def is_store(self) -> bool:
        return op(self.word) in OP_STORES

    @property
    def is_fpu(self) -> bool:
        return op(self.word) == OP_COP1 or op(self.word) in OP_FPU_MEM

    @property
    def is_vu0(self) -> bool:
        """COP2 (VU0 macro mode) instructions and lqc2/sqc2."""
        return op(self.word) == OP_COP2 or op(self.word) in OP_VU_MEM

    @property
    def is_mmi(self) -> bool:
        """128-bit multimedia instructions, lq/sq, and pextlw-style MMI ops.
        mult/madd/plzcw also live under opcode 0x1C, as do mult1/div1
        (pipeline 1), which gcc emits rarely and which are still unusual."""
        o = op(self.word)
        return o in (OP_MMI, OP_LQ, OP_SQ)

    @property
    def is_cop0(self) -> bool:
        return op(self.word) == OP_COP0

    @property
    def is_syscall(self) -> bool:
        return op(self.word) == OP_SPECIAL and funct(self.word) in (0x0C, 0x0D)  # syscall, break

    @property
    def is_sync(self) -> bool:
        return op(self.word) == OP_SPECIAL and funct(self.word) == 0x0F

    @property
    def stack_adjust(self) -> int | None:
        """N for `addiu sp,sp,N` / `daddiu sp,sp,N`."""
        if op(self.word) in (0x09, 0x19) and rs(self.word) == 29 and rt(self.word) == 29:
            return imm(self.word)
        return None


def decode(addr: int, blob: bytes) -> list[Insn]:
    import struct
    n = len(blob) // 4
    return [Insn(addr + i * 4, w) for i, w in enumerate(struct.unpack(f"<{n}I", blob[: n * 4]))]
