#!/usr/bin/env python3
"""Translate one inline VU0 asm statement to C on the VU0 register file.

Phase 5 (docs/vita-port-plan.md section 5.1).  The long hand-written VU0
routines (src/ppp/kemdl.nostrict.c, keshpdtt.nostrict.c ...) keep values in
VU0 registers from one asm statement to the next, so their off-EE side is the
same instructions, one C call each, on include/platform/vu.h's PlatVu0
register file (host/port/vu0.c has the operations).  The output is the
#else side for the statement; shorter sequences have readable C written by
hand instead (vu.h's PlatVu0Dot3, PlatVu0Normalize3 ...).

    python3 -I tools/host/vu2c.py FILE LINE [--reg '$6=p' ...]

LINE is the line of the `__asm__`.  %N operands become their C expressions
("m" operands their address); a GPR the asm names directly (a register-pinned
local, KH1_REG) needs --reg; other GPRs become u64 locals gN.  Branches become
gotos (with the delay slot under .set noreorder: the instruction after a
branch runs before it, the condition taken first; branch-likely runs it only
when taken).  A VU0 or MIPS instruction it does not know stops it with the
instruction, so the output is never silently partial.
"""
import argparse
import re
import sys

FIELD = {"x": 8, "y": 4, "z": 2, "w": 1}
BC = {"x": 0, "y": 1, "z": 2, "w": 3}
FMAC = {"add": "ADD", "sub": "SUB", "mul": "MUL", "madd": "MADD", "msub": "MSUB", "max": "MAX", "mini": "MINI"}


def stmt(s, i):
    j = s.index("(", i)
    d = 0
    for k in range(j, len(s)):
        if s[k] == "(":
            d += 1
        elif s[k] == ")":
            d -= 1
            if d == 0:
                return s[j + 1:k]
    raise SystemExit("unbalanced asm statement")


def parse(body):
    body = body.replace("\\\n", "\n")
    parts = re.split(r'(?<!\\)"', body)
    tmpl, k = [], 0
    for k in range(len(parts)):
        if k % 2 == 0 and ":" in parts[k]:
            break
        if k % 2:
            tmpl.append(parts[k])
    insns = [x.strip() for x in re.split(r"\\n|\\t", "".join(tmpl)) if x.strip()]
    rest = '"'.join(parts[k:])
    secs = re.split(r":(?![^(]*\))", rest)
    ops = []
    for sec in secs[1:3]:
        for m in re.finditer(r'"([^"]*)"\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)', sec):
            ops.append((m.group(1), m.group(2).strip()))
    return insns, ops


def mask(f):
    return sum(FIELD[c] for c in f)


def vfnum(r):
    m = re.fullmatch(r"\$vf(\d+)([xyzw]*)", r)
    if not m:
        raise ValueError(r)
    return int(m.group(1)), m.group(2)


class T:
    def __init__(self, ops, regs):
        self.ops = ops
        self.regs = regs
        self.locals = set()
        self.out = []
        self.noreorder = False
        self.numlabels = {}

    def gpr(self, r):
        r = r.strip()
        m = re.fullmatch(r"%(\d+)", r)
        if m:
            return self.ops[int(m.group(1))][1]
        if r == "$0":
            return "0"
        if r in self.regs:
            return self.regs[r]
        m = re.fullmatch(r"\$(\d+)", r)
        if not m:
            raise ValueError("register " + r)
        self.locals.add(int(m.group(1)))
        return "g%s" % m.group(1)

    def addr(self, a):
        a = a.strip()
        m = re.fullmatch(r"(-?\w*)\((%\d+|\$\d+)\)", a)
        if m:
            off = int(m.group(1), 0) if m.group(1) else 0
            base = self.gpr(m.group(2))
            return "(u8 *)(%s) + %d" % (base, off) if off else "(void *)(%s)" % base
        m = re.fullmatch(r"%(\d+)", a)
        if m:
            c, e = self.ops[int(m.group(1))]
            if "m" in c:
                return "&(%s)" % e
        raise ValueError("address " + a)

    def label(self, name):
        if re.fullmatch(r"\d+[fb]", name):
            n = name[:-1]
            k = self.numlabels.get(n, 0)
            return "L%s_%d" % (n, k if name[-1] == "f" else k - 1)
        return name.lstrip(".")

    def emit(self, c):
        self.out.append(c)

    def vu(self, op, args):
        a = [x.strip() for x in args.split(",")] if args else []
        m = re.fullmatch(r"v(add|sub|madd|msub|mul|max|mini)(a?)([xyzwq]?)\.([xyzw]+)", op)
        if m and not (m.group(1) in ("max", "mini") and m.group(2)):
            base, acc, bc, dest = m.groups()
            if acc:
                d = "PLAT_VU0_ACC"
                s, t = a[1], a[2]
            else:
                d = str(vfnum(a[0])[0])
                s, t = a[1], a[2]
            sn = vfnum(s)[0]
            if bc == "q":
                tn, b = 0, "PLAT_VU0_BC_Q"
            elif bc:
                tn, b = vfnum(t)[0], str(BC[bc])
            else:
                tn, b = vfnum(t)[0], "-1"
            return "PlatVu0Fmac(PLAT_VU0_%s, %s, %d, %d, %d, %s);" % (FMAC[base], d, mask(dest), sn, tn, b)
        m = re.fullmatch(r"vmove\.([xyzw]+)", op)
        if m:
            return "PlatVu0Move(%d, %d, %d);" % (vfnum(a[0])[0], mask(m.group(1)), vfnum(a[1])[0])
        m = re.fullmatch(r"v(ftoi|itof)(0|4|12|15)\.([xyzw]+)", op)
        if m:
            fn = "Ftoi" if m.group(1) == "ftoi" else "Itof"
            return "PlatVu0%s(%d, %d, %d, %s);" % (fn, vfnum(a[0])[0], mask(m.group(3)), vfnum(a[1])[0], m.group(2))
        if op == "vdiv":
            s, sf = vfnum(a[1])
            t, tf = vfnum(a[2])
            return "PlatVu0Div(%d, %d, %d, %d);" % (s, BC[sf], t, BC[tf])
        if op == "vsqrt":
            t, tf = vfnum(a[1])
            return "PlatVu0SqrtQ(%d, %d);" % (t, BC[tf])
        if op == "vopmula.xyz":
            return "PlatVu0Opmula(%d, %d);" % (vfnum(a[1])[0], vfnum(a[2])[0])
        if op == "vopmsub.xyz":
            return "PlatVu0Opmsub(%d, %d, %d);" % (vfnum(a[0])[0], vfnum(a[1])[0], vfnum(a[2])[0])
        if op in ("vnop", "vwaitq", "nop"):
            return None
        if op == "lqc2":
            return "PlatVu0Lq(%d, %s);" % (vfnum(a[0])[0], self.addr(",".join(a[1:])))
        if op == "sqc2":
            return "PlatVu0Sq(%d, %s);" % (vfnum(a[0])[0], self.addr(",".join(a[1:])))
        if op == "qmtc2":
            return "PlatVu0Qmtc2(%d, %s);" % (vfnum(a[1])[0], self.gpr(a[0]))
        if op == "qmfc2":
            return "%s = PlatVu0Qmfc2(%d);" % (self.gpr(a[0]), vfnum(a[1])[0])
        if op == "cfc2":
            reg = {"$vi16": "PlatVu0.stat", "$vi17": "PlatVu0.mac", "$vi18": "PlatVu0.clip",
                   "$vi22": "PlatVu0Bits(PlatVu0.q)"}[a[1]]
            return "%s = %s;" % (self.gpr(a[0]), reg)
        if op == "ctc2" and a[1] == "$vi16":
            return "PlatVu0.stat = %s;" % self.gpr(a[0])
        return self.mips(op, a)

    def mips(self, op, a):
        g = self.gpr
        imm = lambda x: int(x, 0)
        if op == "lui":
            v = imm(a[1]) << 16
            v = v - (1 << 32) if v & 0x80000000 else v
            return "%s = (u64)(s64)(s32)0x%08x;" % (g(a[0]), v & 0xffffffff)
        if op == "ori":
            return "%s = %s | 0x%x;" % (g(a[0]), g(a[1]), imm(a[2]))
        if op == "andi":
            return "%s = %s & 0x%x;" % (g(a[0]), g(a[1]), imm(a[2]))
        if op == "dsll":
            return "%s = (u64)%s << %d;" % (g(a[0]), g(a[1]), imm(a[2]))
        if op in ("addi", "addiu"):
            return "%s = (u64)(s64)(s32)(%s + %d);" % (g(a[0]), g(a[1]), imm(a[2]))
        if op in ("add", "addu") and g(a[1]) == "0" and g(a[2]) == "0":
            return "%s = 0;" % g(a[0])
        if op in ("add", "addu"):
            return "%s = (u64)(s64)(s32)(%s + %s);" % (g(a[0]), g(a[1]), g(a[2]))
        if op == "and":
            return "%s = %s & %s;" % (g(a[0]), g(a[1]), g(a[2]))
        if op == "move":
            return "%s = %s;" % (g(a[0]), g(a[1]))
        if op == "li":
            return "%s = %d;" % (g(a[0]), imm(a[1]))
        if op == "lb":
            return "%s = (u64)(s64)*(s8 *)(%s);" % (g(a[0]), self.addr(a[1]))
        if op == "lw":
            return "%s = (u64)(s64)*(s32 *)(%s);" % (g(a[0]), self.addr(a[1]))
        raise ValueError("instruction %s %s" % (op, ", ".join(a)))

    def branch(self, op, a):
        g = self.gpr
        if op in ("b", "j"):
            return "1", self.label(a[0]), False
        if op in ("bnez", "bnezl"):
            return "%s != 0" % g(a[0]), self.label(a[1]), op.endswith("l")
        if op in ("beqz", "beqzl"):
            return "%s == 0" % g(a[0]), self.label(a[1]), op.endswith("l")
        if op in ("beq", "beql", "bne", "bnel"):
            c = "==" if op.startswith("beq") else "!="
            return "%s %s %s" % (g(a[0]), c, g(a[1])), self.label(a[2]), op.endswith("l")
        if op in ("blez", "blezl", "bgtz", "bgtzl"):
            c = "<=" if op.startswith("blez") else ">"
            return "(s64)%s %s 0" % (g(a[0]), c), self.label(a[1]), op.endswith("l")
        return None

    def run(self, insns):
        i = 0
        while i < len(insns):
            x = insns[i]
            i += 1
            if x == ".set noreorder":
                self.noreorder = True
                continue
            if x == ".set reorder":
                self.noreorder = False
                continue
            m = re.fullmatch(r"([.\w]+):", x)
            if m:
                name = m.group(1)
                if name.isdigit():
                    k = self.numlabels.get(name, 0)
                    self.emit("L%s_%d:;" % (name, k))
                    self.numlabels[name] = k + 1
                else:
                    self.emit("%s:;" % name.lstrip("."))
                continue
            op, _, args = x.partition(" ")
            a = [y.strip() for y in args.split(",")] if args else []
            br = self.branch(op, a)
            if br:
                cond, lab, likely = br
                slot = None
                if self.noreorder and i < len(insns):
                    slot = self.vu(*(insns[i].partition(" ")[::2]))
                    i += 1
                if cond == "1":
                    if slot:
                        self.emit(slot)
                    self.emit("goto %s;" % lab)
                elif likely:
                    self.emit("if (%s) {" % cond)
                    if slot:
                        self.emit("    " + slot)
                    self.emit("    goto %s;" % lab)
                    self.emit("}")
                elif slot:
                    self.emit("{")
                    self.emit("    int c_ = %s;" % cond)
                    self.emit("    " + slot)
                    self.emit("    if (c_)")
                    self.emit("        goto %s;" % lab)
                    self.emit("}")
                else:
                    self.emit("if (%s)" % cond)
                    self.emit("    goto %s;" % lab)
                continue
            c = self.vu(op, args)
            if c:
                self.emit(c)
        body = self.out
        if self.locals:
            body = ["u64 %s;" % ", ".join("g%d" % n for n in sorted(self.locals))] + body
        return ["{"] + ["    " + l if not l.endswith(":;") else l for l in body] + ["}"]


def translate(path, line, regs):
    s = open(path).read()
    pos = sum(len(l) + 1 for l in s.split("\n")[:line - 1])
    i = s.index("__asm__", pos)
    insns, ops = parse(stmt(s, i))
    return "\n".join(T(ops, regs).run(insns))


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("file")
    ap.add_argument("line", type=int)
    ap.add_argument("--reg", action="append", default=[], help="$N=C expression")
    a = ap.parse_args()
    regs = dict(r.split("=", 1) for r in a.reg)
    try:
        print(translate(a.file, a.line, regs))
    except ValueError as e:
        sys.exit("vu2c: %s" % e)


if __name__ == "__main__":
    main()
