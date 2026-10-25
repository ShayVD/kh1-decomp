#!/usr/bin/env python3
"""The camera matrices of func_00110618: the PS2 function's code against host/port/view.c (session 91).

  python3 -I tools/host/viewcheck.py [--elf SLPS_251.98] [--scrz 300,600,1000] [--fog 3000,20000]
                                     [--round zero|nearest] [--wide 960:544] [-v]

func_00110618 (display.c func_00110a48's six matrices, docs/renderer-spec.md 5.4) is still a
non-match, so the host and the port use the C twin in host/port/view.c.  This runs the original's
268 instructions from the user's own ELF in a small interpreter (the integer moves, the stack, the
FPU's single-precision ops, and the two library calls sceVu0UnitMatrix / sceVu0MulMatrix done in
Python, the latter as libvu0's m0 = m1 x m2), with func_00110a48's arguments and a few scrz / fog
far values, builds view.c with the host's gcc -m32 into a scratch directory and runs it on the
same arguments, and compares the 96 floats.  The EE's FPU rounds toward zero (--round zero, the
default; nearest for IEEE), so a few last-place differences are expected: the check passes when
every float agrees to 4 ulp (or 1e-30 absolute) and prints the worst.

--wide W:H also runs view.c with the hor+ factor (kh1_view_init) and prints what changes: only
m1[0][0] and m3[0][0] (the two frustums' x scale, divided by W/H / (4/3)) should.

Reads the ELF only at run time and prints numbers: nothing from it is written to the repo.
"""
from __future__ import annotations

import argparse
import math
import os
import shutil
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from elf32 import Elf  # noqa: E402

FUNC, SIZE = 0x00110618, 1072
UNIT, MUL = 0x00267620, 0x00267328  # functions.tsv: sceVu0UnitMatrix, sceVu0MulMatrix
# func_00110a48's constants after scrz (display.c:290): ax, ay, cx, cy, zmin, zmax, near, far; fog last
ARGS = (0.7999999523162842, 0.839999854564666748046875, 2048.0, 2048.0, 1.0, 16777000.0, 1.0, 400000000.0)
NAMES = ("m0 D_002BBE20", "m1 D_002BBE60", "m2 D_002BBEA0", "m3 D_002BBEE0", "m4 D_002BBF20", "m5 D_002BBF60")


def f32(x: float) -> float:
    return struct.unpack("<f", struct.pack("<f", x))[0]


def bits(x: float) -> int:
    return struct.unpack("<I", struct.pack("<f", x))[0]


def unbits(b: int) -> float:
    return struct.unpack("<f", struct.pack("<I", b & 0xFFFFFFFF))[0]


class Cpu:
    """just enough of the EE for func_00110618: GPR moves, the stack, COP1 single-precision"""

    def __init__(self, code: bytes, rnd: str):
        self.code, self.rnd = code, rnd
        self.r = [0] * 32
        self.f = [0.0] * 32
        self.mem = {}  # word address -> u32

    def op(self, x: float) -> float:
        if math.isinf(x) or math.isnan(x):
            raise ValueError("inf / nan")
        n = f32(x)
        if self.rnd == "zero" and abs(n) > abs(x):  # one step back toward 0
            b = bits(n)
            n = unbits(b - 1)
        if n != 0 and abs(n) < 1.1754943508222875e-38:
            n = 0.0  # no denormals on the EE
        return n

    def lw(self, a: int) -> int:
        return self.mem.get(a & ~3, 0)

    def sw(self, a: int, v: int) -> None:
        self.mem[a & ~3] = v & 0xFFFFFFFF

    def mtx(self, a: int) -> list[list[float]]:
        return [[unbits(self.lw(a + 16 * i + 4 * j)) for j in range(4)] for i in range(4)]

    def put_mtx(self, a: int, m) -> None:
        for i in range(4):
            for j in range(4):
                self.sw(a + 16 * i + 4 * j, bits(m[i][j]))

    def call(self, target: int) -> None:
        a0, a1, a2 = self.r[4], self.r[5], self.r[6]
        if target == UNIT:
            self.put_mtx(a0, [[1.0 if i == j else 0.0 for j in range(4)] for i in range(4)])
        elif target == MUL:  # m0[i] = m2[i].x m1[0] + ... + m2[i].w m1[3] (vmula / vmadd, one rounding each)
            m1, m2 = self.mtx(a1), self.mtx(a2)
            r = []
            for i in range(4):
                row = []
                for k in range(4):
                    acc = 0.0
                    for j in range(4):
                        acc = self.op(acc + self.op(m2[i][j] * m1[j][k]))
                    row.append(acc)
                r.append(row)
            self.put_mtx(a0, r)
        else:
            raise ValueError("call to %08x" % target)

    def run(self) -> None:
        pc, delay = FUNC, None
        steps = 0
        while True:
            steps += 1
            if steps > 10000:
                raise RuntimeError("runaway")
            w = struct.unpack_from("<I", self.code, pc - FUNC)[0]
            nxt = delay if delay is not None else pc + 4
            delay = None
            done = self.step(w, pc)
            if isinstance(done, tuple):  # a jump: run the delay slot first
                kind, target = done
                slot = struct.unpack_from("<I", self.code, pc + 4 - FUNC)[0]
                self.step(slot, pc + 4)
                if kind == "jr":
                    return
                self.r[31] = pc + 8
                self.call(target)
                pc = pc + 8
                continue
            pc = nxt

    def step(self, w: int, pc: int):
        r, f = self.r, self.f
        op, rs, rt = w >> 26, w >> 21 & 31, w >> 16 & 31
        rd, imm = w >> 11 & 31, w & 0xFFFF
        simm = imm - 0x10000 if imm & 0x8000 else imm

        def setr(i: int, v: int) -> None:
            if i:
                r[i] = v & 0xFFFFFFFFFFFFFFFF

        if w == 0:
            return None
        if op == 0:
            fn = w & 63
            if fn in (0x2D, 0x21, 0x25):  # daddu / addu / or (move)
                setr(rd, r[rs] + r[rt] if fn != 0x25 else r[rs] | r[rt])
            elif fn == 0x08:
                return ("jr", r[rs])
            elif fn == 0x00:
                setr(rd, (r[rt] << (w >> 6 & 31)) & 0xFFFFFFFF)
            else:
                raise ValueError("%08x: special %02x" % (pc, fn))
        elif op == 0x03:
            return ("jal", (pc & 0xF0000000) | (w & 0x3FFFFFF) << 2)
        elif op == 0x09:
            setr(rt, (r[rs] + simm) & 0xFFFFFFFF)
        elif op == 0x0D:
            setr(rt, r[rs] | imm)
        elif op == 0x0F:
            setr(rt, imm << 16)
        elif op == 0x2B:
            self.sw(r[rs] + simm, r[rt])
        elif op == 0x23:
            setr(rt, self.lw(r[rs] + simm))
        elif op == 0x3F:  # sd
            a = (r[rs] + simm) & 0xFFFFFFFF
            self.sw(a, r[rt])
            self.sw(a + 4, r[rt] >> 32)
        elif op == 0x37:  # ld
            a = (r[rs] + simm) & 0xFFFFFFFF
            setr(rt, self.lw(a) | self.lw(a + 4) << 32)
        elif op == 0x31:
            f[rt] = unbits(self.lw(r[rs] + simm))
        elif op == 0x39:
            self.sw(r[rs] + simm, bits(f[rt]))
        elif op == 0x11:
            fs, fd = rd, w >> 6 & 31
            if rs == 0x04:
                f[fs] = unbits(r[rt])
            elif rs == 0x00:
                setr(rt, bits(f[fs]))
            elif rs == 0x10:
                fn, ft = w & 63, rt
                if fn == 0:
                    f[fd] = self.op(f[fs] + f[ft])
                elif fn == 1:
                    f[fd] = self.op(f[fs] - f[ft])
                elif fn == 2:
                    f[fd] = self.op(f[fs] * f[ft])
                elif fn == 3:
                    f[fd] = f32(f[fs] / f[ft])  # the EE's divider rounds to nearest (an assumption)
                elif fn == 6:
                    f[fd] = f[fs]
                elif fn == 7:
                    f[fd] = -f[fs]
                else:
                    raise ValueError("%08x: cop1.s %02x" % (pc, fn))
            else:
                raise ValueError("%08x: cop1 rs %02x" % (pc, rs))
        else:
            raise ValueError("%08x: op %02x" % (pc, op))
        return None


def ps2(code: bytes, scrz: float, fog: float, rnd: str) -> list:
    cpu = Cpu(code, rnd)
    sp = 0x01F00000
    cpu.r[29] = sp
    outs = [0x01000000 + 0x100 * i for i in range(6)]
    for i, reg in enumerate((4, 5, 6, 7, 8, 9)):  # EABI: a0-a3, t0, t1
        cpu.r[reg] = outs[i]
        cpu.put_mtx(outs[i], [[unbits(0x7F7FFFFF)] * 4] * 4)  # FLT_MAX: a store the code missed shows
    vals = (scrz,) + ARGS[:7]
    for i, v in enumerate(vals):  # $f12-$f19
        cpu.f[12 + i] = f32(v)
    cpu.sw(sp + 0, bits(f32(ARGS[7])))  # the stack arguments, 8 bytes apart: far, fog
    cpu.sw(sp + 8, bits(f32(fog)))
    cpu.r[31] = 0xDEAD0000
    cpu.run()
    return [cpu.mtx(a) for a in outs]


HARNESS = r"""
#include <stdio.h>
#include <stdlib.h>
typedef float f32;
typedef f32 Mtx[4][4] __attribute__((aligned(16)));
float D_00469F90[4] = { 1792, 1856, 0, 1 }, D_00469FA0[4] = { 2304, 2240, 0, 4e8 };
extern f32 kh1_view_wide;
void kh1_view_init(f32);
void func_00110618(Mtx, Mtx, Mtx, Mtx, Mtx, Mtx, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void sceVu0UnitMatrix(Mtx m) { int i, j; for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) m[i][j] = i == j; }
void sceVu0MulMatrix(Mtx m0, Mtx m1, Mtx m2) {
    Mtx r; int i, j, k;
    for (i = 0; i < 4; i++) for (k = 0; k < 4; k++) {
        f32 a = 0; for (j = 0; j < 4; j++) a += m2[i][j] * m1[j][k]; r[i][k] = a; }
    for (i = 0; i < 4; i++) for (k = 0; k < 4; k++) m0[i][k] = r[i][k];
}
int main(int argc, char **argv) {
    static Mtx m[6]; int i, j, k;
    if (argc > 4) kh1_view_init(atof(argv[4]));
    func_00110618(m[0], m[1], m[2], m[3], m[4], m[5], atof(argv[1]), %s, atof(argv[2]));
    for (i = 0; i < 6; i++) for (j = 0; j < 4; j++) for (k = 0; k < 4; k++) printf("%%a\n", m[i][j][k]);
    printf("%%a %%a\n", D_00469F90[0], D_00469FA0[0]);
    return 0;
}
"""


def build_host(work: Path) -> Path:
    args = ", ".join("(f32)%.17g" % a for a in ARGS)
    (work / "h.c").write_text(HARNESS % args)
    exe = work / "viewcheck"
    subprocess.run(["gcc", "-m32", "-O1", "-ffloat-store", "-DKH1_HOST", "-I", str(ROOT / "include"), "-o", str(exe),
                    str(work / "h.c"), str(ROOT / "host/port/view.c"), "-w"], check=True)
    return exe


def host(exe: Path, scrz: float, fog: float, aspect: float | None = None):
    argv = [str(exe), repr(scrz), repr(fog), "x"] + ([repr(aspect)] if aspect else [])
    out = subprocess.run(argv, capture_output=True, text=True, check=True).stdout.split()
    v = [float.fromhex(x) for x in out[:96]]
    return [[v[16 * i + 4 * j:16 * i + 4 * j + 4] for j in range(4)] for i in range(6)], \
        (float.fromhex(out[96]), float.fromhex(out[97]))


def ulps(a: float, b: float) -> int:
    if a == b:
        return 0
    if abs(a - b) < 1e-30:
        return 0
    ia, ib = bits(a), bits(b)
    ia = ia if ia < 0x80000000 else 0x80000000 - ia
    ib = ib if ib < 0x80000000 else 0x80000000 - ib
    return abs(ia - ib)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--elf", type=Path, default=ROOT / "SLPS_251.98")
    ap.add_argument("--scrz", default="300,512,700,1000")
    ap.add_argument("--fog", default="2000,8000,30000")
    ap.add_argument("--round", choices=("zero", "nearest"), default="zero")
    ap.add_argument("--wide", help="also the hor+ view, W:H (960:544)")
    ap.add_argument("-v", action="store_true", help="print the matrices")
    a = ap.parse_args()
    elf = Elf.load(a.elf)
    code = elf.read(FUNC, SIZE)
    if not code:
        sys.exit("viewcheck: %s holds no func_00110618" % a.elf)
    if not shutil.which("gcc"):
        sys.exit("viewcheck: no gcc")
    worst, bad = (0, None), 0
    with tempfile.TemporaryDirectory() as d:
        exe = build_host(Path(d))
        for scrz in map(float, a.scrz.split(",")):
            for fog in map(float, a.fog.split(",")):
                p = ps2(code, scrz, fog, a.round)
                h, _ = host(exe, scrz, fog)
                for i in range(6):
                    for j in range(4):
                        for k in range(4):
                            u = ulps(p[i][j][k], h[i][j][k])
                            if u > worst[0]:
                                worst = (u, (scrz, fog, NAMES[i], j, k, p[i][j][k], h[i][j][k]))
                            if u > 4:
                                bad += 1
                if a.v:
                    print("# scrz %g fog %g" % (scrz, fog))
                    for i in range(6):
                        print("  %s" % NAMES[i])
                        for j in range(4):
                            print("    ps2 " + " ".join("%14.7g" % x for x in p[i][j]) +
                                  "   host " + " ".join("%14.7g" % x for x in h[i][j]))
        n = len(a.scrz.split(",")) * len(a.fog.split(","))
        print("viewcheck: %d argument sets x 96 floats, rounding %s: %d over 4 ulp; worst %d ulp%s" % (
            n, a.round, bad, worst[0], "" if not worst[1] else
            " (scrz %g fog %g %s [%d][%d]: ps2 %.9g host %.9g)" % worst[1]))
        if a.wide:
            wv, hv = (float(x) for x in a.wide.split(":"))
            scrz, fog = float(a.scrz.split(",")[0]), float(a.fog.split(",")[0])
            h0, b0 = host(exe, scrz, fog)
            h1, b1 = host(exe, scrz, fog, wv / hv)
            print("viewcheck: --wide %s (k = %.4f), scrz %g fog %g: the floats that change" % (
                a.wide, wv / hv * 3 / 4, scrz, fog))
            for i in range(6):
                for j in range(4):
                    for k in range(4):
                        if h0[i][j][k] != h1[i][j][k]:
                            print("\t%s [%d][%d]: %.7g -> %.7g (x %.4f)" % (
                                NAMES[i], j, k, h0[i][j][k], h1[i][j][k], h1[i][j][k] / h0[i][j][k]))
            print("\tmarkers' x bounds D_00469F90 / D_00469FA0: %.1f / %.1f -> %.1f / %.1f" % (b0 + b1))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
