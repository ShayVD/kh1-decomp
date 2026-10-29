#!/usr/bin/env python3
"""Translate the VU1 microprograms in the user's SLPS_251.98 to C (session 137v).

  python3 -I tools/vu/vu1_translate.py ELF OUT.c [--stats]

The C is #included by host/port/vu1.c (KH1_VU1_TR) and runs a program in place of the interpreter
when micro memory holds that program's exact words. It is derived from the user's own ELF at build
time and lands in out/gen/: never commit it (README: no game data in this repository).

What it does, per program (docs/vita-build.md "The 3D path"):
  * every pair becomes straight-line C on the interpreter's own state (vf, vi, acc, mem, i_reg,
    clip_last ...) and helpers (fin, fo, fout, qop, pop, kick), so the arithmetic is the same code;
  * the timing the interpreter keeps at run time (stalls, the 4-cycle flag FIFO, Q / P latencies,
    the VI backup a branch reads) is worked out here instead.  A run starts drained (vu1.c's
    settle()), so from each entry the timing state at every pair is known statically; a pair reached
    with different states is emitted once per state.  A flag, Q or P read then names the very
    instruction whose result it sees, and that instruction keeps its result in a local;
  * MAC flags are computed only by the instructions some FMAND / FMEQ / FMOR (or the run's end) can
    see; the status flag is not kept (no KH1 program reads it: FSAND / FSEQ / FSOR are unused).
A program the translator cannot follow (an unknown opcode, a branch in a delay slot, a branch out of
the program, a pair reached in too many states) is left to the interpreter, and said so.
"""
from __future__ import annotations

import argparse
import importlib.util
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
_spec = importlib.util.spec_from_file_location("find_vu1", HERE / "find_vu1.py")
fv = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(fv)

MICRO_N = 0x800
MAX_VERSIONS = 64  # states one pair may be emitted in
FIELDS = "xyzw"

K_ADD, K_SUB, K_MADD, K_MSUB, K_MAX, K_MINI, K_MUL = range(7)
OPC = {K_ADD: "+", K_SUB: "-", K_MUL: "*"}


class Unsupported(Exception):
    pass


def s11(w: int) -> int:
    v = w & 0x7FF
    return v - 0x800 if v & 0x400 else v


def fields(m: int):
    return [f for f in range(4) if m >> (3 - f) & 1]


# ---------------------------------------------------------------- decode --------
# Mirrors host/port/vu1.c's upper() / lower() / upper_stall() / lower_stall() case for case.

class Up:
    """An upper instruction: kind, dest mask, target ('vf', n) / ('acc',) / None, operands."""

    def __init__(self, hi: int):
        o, dest, ft, fs, fd = hi & 63, hi >> 21 & 15, hi >> 16 & 31, hi >> 11 & 31, hi >> 6 & 31
        self.dest, self.fs, self.ft = dest, fs, ft
        self.op = None      # 'fmac', 'itof', 'ftoi', 'abs', 'clip', 'nop'
        self.k = None
        self.tsrc = None    # ('bc', f) / ('vf',) / ('q',) / ('i',) / ('op',)
        self.to = None      # VF number, 32 = ACC
        self.setmac = False
        self.reads = []     # (reg, mask) for the stall
        if o < 0x1C:
            self.op, self.k = "fmac", [K_ADD, K_SUB, K_MADD, K_MSUB, K_MAX, K_MINI, K_MUL][o >> 2]
            self.tsrc, self.to = ("bc", o & 3), fd
            self.setmac = self.k not in (K_MAX, K_MINI)
            self.reads = [(fs, dest), (ft, 8 >> (o & 3))]
            return
        if o < 0x30:
            kq = [K_MUL, K_MAX, K_MUL, K_MINI, K_ADD, K_MADD, K_ADD, K_MADD, K_SUB, K_MSUB, K_SUB, K_MSUB,
                  K_ADD, K_MADD, K_MUL, K_MAX, K_SUB, K_MSUB, -1, K_MINI]
            k = kq[o - 0x1C]
            self.op, self.to = "fmac", fd
            if k < 0:  # opmsub
                self.k, self.tsrc, self.dest = K_MSUB, ("op",), dest & 0xE
                self.setmac = True
                self.reads = [(fs, 0xE), (ft, 0xE)]
                return
            self.k = k
            self.setmac = k not in (K_MAX, K_MINI)
            if o >= 0x28:
                self.tsrc = ("vf",)
                self.reads = [(fs, dest), (ft, dest)]
            else:
                self.tsrc = ("q",) if o in (0x1C, 0x20, 0x21, 0x24, 0x25) else ("i",)
                self.reads = [(fs, dest)]
            return
        if o < 0x3C:
            raise Unsupported(f"upper {hi:08x}")
        x = fd << 2 | (o & 3)
        if x == 0x2F:
            self.op = "nop"
            return
        if x < 0x10 or 0x18 <= x <= 0x1B:
            self.op, self.k = "fmac", [K_ADD, K_SUB, K_MADD, K_MSUB, 0, 0, K_MUL][x >> 2]
            self.tsrc, self.to, self.setmac = ("bc", x & 3), 32, True
            self.reads = [(fs, dest), (ft, 8 >> (o & 3))]
            return
        if 0x10 <= x <= 0x17:
            self.op, self.k, self.to = ("itof" if x < 0x14 else "ftoi"), x & 3, ft
            self.reads = [(fs, dest)]
            return
        if x == 0x1D:
            self.op, self.to = "abs", ft
            self.reads = [(fs, dest)]
            return
        if x == 0x1F:
            self.op = "clip"
            self.reads = [(fs, 0xE), (ft, 1)]
            return
        if x in (0x1C, 0x1E) or 0x20 <= x <= 0x27:
            kk = [K_MUL, -1, K_MUL, -1, K_ADD, K_MADD, K_ADD, K_MADD, K_SUB, K_MSUB, K_SUB, K_MSUB]
            self.op, self.k, self.to, self.setmac = "fmac", kk[x - 0x1C], 32, True
            self.tsrc = ("q",) if x in (0x1C, 0x20, 0x21, 0x24, 0x25) else ("i",)
            self.reads = [(fs, dest)]
            return
        if x in (0x28, 0x29, 0x2A, 0x2C, 0x2D):
            self.op, self.k = "fmac", {0x28: K_ADD, 0x29: K_MADD, 0x2A: K_MUL, 0x2C: K_SUB, 0x2D: K_MSUB}[x]
            self.tsrc, self.to, self.setmac = ("vf",), 32, True
            self.reads = [(fs, dest), (ft, dest)]
            return
        if x == 0x2E:  # opmula
            self.op, self.k, self.tsrc, self.to, self.setmac = "fmac", K_MUL, ("op",), 32, True
            self.dest = dest & 0xE
            self.reads = [(fs, 0xE), (ft, 0xE)]
            return
        raise Unsupported(f"upper {hi:08x}")


FLAG_OPS = range(0x10, 0x1D)  # FCEQ ... FCGET: no VI backup (vu1.c run())


class Lo:
    """A lower instruction, decoded as vu1.c's lower() reads it."""

    def __init__(self, lo: int, pc: int):
        o, dest = lo >> 25, lo >> 21 & 15
        it, is_, id_ = lo >> 16 & 31, lo >> 11 & 31, lo >> 6 & 31
        self.raw, self.o, self.dest, self.it, self.is_, self.id = lo, o, dest, it, is_, id_
        self.name = None
        self.reads = []         # VF (reg, mask) for the stall
        self.branch = None      # ('b', target) / ('bal', target) / ('jr',) / ('jalr',) / ('cond', target)
        self.vi_reads_br = []   # VI the branch reads (through the backup)
        self.vfw = None         # (reg, mask) a VF write
        self.flag = o in FLAG_OPS
        self.x = None
        if o == 0x40:
            fn = lo & 63
            if fn < 0x3C:
                self.name = {0x30: "iadd", 0x31: "isub", 0x32: "iaddi", 0x34: "iand", 0x35: "ior"}.get(fn)
                if not self.name:
                    raise Unsupported(f"lower {lo:08x}")
                return
            x = id_ << 2 | (lo & 3)
            self.x = x
            self.fsf, self.ftf = lo >> 21 & 3, lo >> 23 & 3
            fsm, ftm = 8 >> self.fsf, 8 >> self.ftf
            names = {0x30: "move", 0x31: "mr32", 0x34: "lqi", 0x36: "lqd", 0x35: "sqi", 0x37: "sqd",
                     0x38: "div", 0x39: "sqrt", 0x3A: "rsqrt", 0x3B: "waitq", 0x3C: "mtir", 0x3D: "mfir",
                     0x3E: "ilwr", 0x3F: "iswr", 0x40: "rnext", 0x41: "rget", 0x42: "rinit", 0x43: "rxor",
                     0x64: "mfp", 0x68: "xtop", 0x69: "xitop", 0x6C: "xgkick", 0x7B: "waitp"}
            self.name = names.get(x)
            if x >= 0x70 and x != 0x7B:
                if not ((0x70 <= x <= 0x73) or x == 0x76 or 0x78 <= x <= 0x7A or 0x7C <= x <= 0x7E):
                    raise Unsupported(f"lower {lo:08x}")
                self.name = "efu"
            if not self.name:
                raise Unsupported(f"lower {lo:08x}")
            if self.name == "move" and lo == 0x8000033C:
                self.name = "nop"
            n = self.name
            if n == "move": self.reads = [(is_, dest)]
            elif n == "mr32": self.reads = [(is_, 0xF)]
            elif n in ("sqi", "sqd"): self.reads = [(is_, dest)]
            elif n in ("div", "rsqrt"): self.reads = [(is_, fsm), (it, ftm)]
            elif n == "sqrt": self.reads = [(it, ftm)]
            elif n == "mtir": self.reads = [(is_, fsm)]
            elif n in ("rinit", "rxor"): self.reads = [(is_, fsm)]
            elif n == "efu": self.reads = [(is_, 0xF)]
            if n in ("move", "mr32", "lqi", "lqd", "mfir", "rnext", "rget", "mfp") and it:
                self.vfw = (it, dest)
            return
        main = {0x00: "lq", 0x01: "sq", 0x04: "ilw", 0x05: "isw", 0x08: "iaddiu", 0x09: "isubiu",
                0x10: "fceq", 0x11: "fcset", 0x12: "fcand", 0x13: "fcor", 0x15: "fsset",
                0x18: "fmeq", 0x1A: "fmand", 0x1B: "fmor", 0x1C: "fcget",
                0x20: "b", 0x21: "bal", 0x24: "jr", 0x25: "jalr", 0x28: "ibeq", 0x29: "ibne",
                0x2C: "ibltz", 0x2D: "ibgtz", 0x2E: "iblez", 0x2F: "ibgez"}
        self.name = main.get(o)
        if not self.name:  # FSEQ / FSAND / FSOR read the status flag, which is not kept
            raise Unsupported(f"lower {lo:08x}")
        n = self.name
        tgt = (pc + 1 + s11(lo)) & (MICRO_N - 1)
        if n == "lq":
            if it: self.vfw = (it, dest)
        elif n == "sq": self.reads = [(is_, dest)]
        elif n == "b": self.branch = ("b", tgt)
        elif n == "bal": self.branch = ("bal", tgt)
        elif n == "jr": self.branch, self.vi_reads_br = ("jr",), [is_ & 15]
        elif n == "jalr": self.branch, self.vi_reads_br = ("jalr",), [is_ & 15]
        elif n in ("ibeq", "ibne"): self.branch, self.vi_reads_br = ("cond", tgt), [it & 15, is_ & 15]
        elif n.startswith("ib"): self.branch, self.vi_reads_br = ("cond", tgt), [is_ & 15]

    def vi_write(self):
        """The VI this instruction writes (vu1.c's set_vi), or None."""
        n, it, is_, id_ = self.name, self.it & 15, self.is_ & 15, self.id & 15
        r = None
        if n in ("iadd", "isub", "iand", "ior"): r = id_
        elif n in ("iaddi", "iaddiu", "isubiu", "ilw", "mtir", "ilwr", "xtop", "xitop", "fmeq", "fmand", "fmor"):
            r = it
        elif n in ("lqi", "lqd"): r = is_
        elif n in ("sqi", "sqd"): r = it
        elif n in ("fceq", "fcand", "fcor"): r = 1
        elif n == "fcget": r = it
        elif n in ("bal", "jalr"): r = it
        return r or None


def decode(words):
    out = []
    for pc, (lo, hi) in enumerate(words):
        up = Up(hi)
        lw = None if hi >> 31 & 1 else Lo(lo, pc)
        out.append((lo, hi, up, lw))
    return out


# ---------------------------------------------------------------- the timing state --------
# Everything relative to the pair about to issue.  Producers are named by pc (a pair's result is kept
# in a local named after it); None is the value the run started with (the global).

class St:
    __slots__ = ("vfr", "fq", "mac", "clip", "q", "qp", "p", "pp", "vib", "delay", "ending")

    def __init__(self):
        self.vfr = {}      # (reg, field) -> cycles until written (> 0)
        self.fq = ()       # ((rel, has, pc), ...) in push order, not yet visible
        self.mac = None    # the visible MAC flag's producer
        self.clip = None   # the visible clip flag's producer ('fcset', pc) or pc
        self.q = None      # Q's producer
        self.qp = None     # (rel, pc) a DIV on its way
        self.p = None
        self.pp = None
        self.vib = None    # the VI the pair before wrote with an integer instruction
        self.delay = None  # the branch whose delay slot this pair is: ('t', target) / ('c', target) / ('j',)
        self.ending = False

    def key(self):
        return (tuple(sorted(self.vfr.items())), self.fq, self.mac, self.clip, self.q, self.qp, self.p, self.pp,
                self.vib, self.delay, self.ending)

    def copy(self):
        s = St()
        s.vfr, s.fq, s.mac, s.clip = dict(self.vfr), self.fq, self.mac, self.clip
        s.q, s.qp, s.p, s.pp, s.vib, s.delay, s.ending = self.q, self.qp, self.p, self.pp, self.vib, self.delay, self.ending
        return s

    def advance(self, n: int):
        if n <= 0:
            return
        self.vfr = {k: v - n for k, v in self.vfr.items() if v - n > 0}
        self.fq = tuple((r - n, h, pc) for r, h, pc in self.fq)
        if self.qp: self.qp = (self.qp[0] - n, self.qp[1])
        if self.pp: self.pp = (self.pp[0] - n, self.pp[1])

    def commit(self):
        """What is visible now: flags pushed 4 or more cycles back, a finished DIV / EFU (vu1.c's
        flags_at / q_at at this cycle, done eagerly: the same, as visibility only grows)."""
        keep = []
        for r, h, pc in self.fq:
            if r <= 0:
                if h & 1: self.mac = pc
                if h & 2: self.clip = pc
            else:
                keep.append((r, h, pc))
        self.fq = tuple(keep)
        if self.qp and self.qp[0] <= 0: self.q, self.qp = self.qp[1], None
        if self.pp and self.pp[0] <= 0: self.p, self.pp = self.pp[1], None

    def slot(self, pc: int, kind: str):
        """Where a new result goes: the lowest local of its kind (fm, fc, qv, pv [k]) the state does not
        still hold (visible or on its way).  Slots, not producers, name the state, and node() renumbers
        them in a fixed order, so paths that differ only in which pair produced a value meet again."""
        if kind == "mac":
            held = {self.mac} | {p for _, h, p in self.fq if h & 1}
        elif kind == "clip":
            held = {self.clip} | {p for _, h, p in self.fq if h & 2}
        elif kind == "q":
            held = {self.q} | ({self.qp[1]} if self.qp else set())
        else:
            held = {self.p} | ({self.pp[1]} if self.pp else set())
        k = 0
        while k in held:
            k += 1
        return k

    def canon(self):
        """The state with its slots renumbered (the visible one 0, then those on their way in order) and the
        moves (array, new, old) that take the locals there."""
        s, moves = self.copy(), []

        def order(first, rest):
            seq = ([first] if first is not None else []) + list(rest)
            return {old: new for new, old in enumerate(seq)}
        mm = order(self.mac, [p for _, h, p in self.fq if h & 1])
        cm = order(self.clip, [p for _, h, p in self.fq if h & 2])
        qm = order(self.q, [self.qp[1]] if self.qp else [])
        pm = order(self.p, [self.pp[1]] if self.pp else [])
        s.mac = mm.get(self.mac)
        s.clip = cm.get(self.clip)
        s.fq = tuple((r, h, (mm if h & 1 else cm)[p]) for r, h, p in self.fq)
        s.q = qm.get(self.q)
        s.qp = (self.qp[0], qm[self.qp[1]]) if self.qp else None
        s.p = pm.get(self.p)
        s.pp = (self.pp[0], pm[self.pp[1]]) if self.pp else None
        for arr, m in (("fm", mm), ("fc", cm), ("qv", qm), ("pv", pm)):
            moves += [(arr, new, old) for old, new in m.items() if old != new]
        return s, tuple(moves)

    def stall(self, reads) -> int:
        t = 0
        for r, m in reads:
            if not r:
                continue
            for f in fields(m):
                t = max(t, self.vfr.get((r, f), 0))
        return t


# ---------------------------------------------------------------- the translator --------

class Prog:
    def __init__(self, n: int, words):
        self.n, self.words = n, words
        self.code = decode(words)
        self.nodes = {}      # key -> id
        self.order = []      # (id, pc, St)
        self.succ = {}       # id -> description of the way on
        self.mac_reads = []  # (node, slot)
        self.uses_q, self.uses_p = set(), set()
        self.per_pc = {}
        self.entries = self.find_entries()
        self.links = sorted({pc + 2 for pc, c in enumerate(self.code)
                             if c[3] and c[3].name in ("bal", "jalr")})
        # where a JR through VI r may go: the links BAL / JALR leave in r, and the addresses the program
        # puts in r itself (IADDIU r, vi00, addr: P13's and P14's hand-made returns)
        self.jr_to = {}
        for pc, c in enumerate(self.code):
            lw = c[3]
            if not lw:
                continue
            r = lw.it & 15
            if lw.name in ("bal", "jalr"): v = pc + 2
            elif lw.name == "iaddiu" and not lw.is_ & 15: v = (lw.raw >> 10 & 0x7800) | (lw.raw & 0x7FF)
            elif lw.name == "iaddi" and not lw.is_ & 15: v = lw.id - 32 if lw.id & 16 else lw.id
            else: continue
            if 0 <= v < len(self.code):
                self.jr_to.setdefault(r, set()).add(v)
        self.ahead = self.lookahead()

    def lookahead(self, depth: int = 19):
        """ahead[k][pc]: what the pairs from pc on, k of them along any path, read: VF fields (reg, f) and
        'mac' / 'clip' / 'q' / 'p'.  A pending write nothing reads before it lands changes nothing, so the
        state drops it (node()): fewer states, the same code."""
        n = len(self.code)
        r0, succ = [], []
        for pc, (lo, hi, up, lw) in enumerate(self.code):
            r = set()
            for reg, m in up.reads + (lw.reads if lw else []):
                if reg:
                    r |= {(reg, f) for f in fields(m)}
            if up.op == "fmac" and up.tsrc == ("q",): r |= {"q", "qv"}
            if lw:
                nm = lw.name
                if nm in ("fmeq", "fmand", "fmor"): r.add("mac")
                if nm in ("fceq", "fcand", "fcor", "fcget", "fcset"): r.add("clip")
                if nm in ("div", "sqrt", "rsqrt", "waitq"): r.add("q")
                if nm in ("efu", "waitp", "mfp"): r |= {"p", "q"}
                if nm == "mfp": r.add("pv")
            if pc >= 1 and self.code[pc - 1][1] >> 30 & 1:  # the run's last pair: its end keeps them all
                r |= {"mac", "clip", "qv", "pv"}
            r0.append(r)
            sc = {pc + 1} if pc + 1 < n else set()
            if pc >= 1:
                pl = self.code[pc - 1][3]
                if pl and pl.branch:
                    if len(pl.branch) > 1: sc.add(pl.branch[1])
                    else: sc |= self.jr_to.get(pl.is_ & 15, set())
            succ.append({x for x in sc if 0 <= x < n})
        ahead = [[set() for _ in range(n)]]
        for k in range(1, depth + 1):
            prev = ahead[-1]
            ahead.append([r0[pc].union(*(prev[x] for x in succ[pc])) if succ[pc] else set(r0[pc]) for pc in range(n)])
        # live[pc]: the kinds whose visible value a read (or the run's end) may still see from pc on, before a
        # newer one lands (a pair that writes one: the old stays visible 4 more cycles, so its window counts)
        kills = []
        for pc, (lo, hi, up, lw) in enumerate(self.code):
            k = set()
            if up.op == "fmac" and up.setmac: k.add("mac")
            if up.op == "clip" or (lw and lw.name == "fcset"): k.add("clip")
            if lw and lw.name in ("div", "sqrt", "rsqrt"): k.add("qv")
            if lw and lw.name == "efu": k.add("pv")
            kills.append(k)
        kinds = {"mac", "clip", "qv", "pv"}
        live = [set() for _ in range(n)]
        changed = True
        while changed:
            changed = False
            for pc in range(n - 1, -1, -1):
                v = (r0[pc] & kinds) | ((kinds & ahead[min(depth, 19)][pc]) & kills[pc] if kills[pc] else set())
                for x in succ[pc]:
                    v |= live[x] - kills[pc]
                if v != live[pc]:
                    live[pc] = v
                    changed = True
        self.live = live
        return ahead

    def trim(self, pc: int, s: St) -> St:
        A = self.ahead
        s = s.copy()
        s.vfr = {k: r for k, r in s.vfr.items() if k in A[min(r, len(A) - 1)][pc]}
        for kind, bit in (("mac", 1), ("clip", 2)):
            mine = [e for e in s.fq if e[1] & bit]
            if mine and kind not in A[min(max(e[0] for e in mine), len(A) - 1)][pc]:
                for r, h, p in mine:
                    if bit == 1: s.mac = p
                    else: s.clip = p
                s.fq = tuple(e for e in s.fq if not e[1] & bit)
        if s.qp and "q" not in A[min(s.qp[0], len(A) - 1)][pc]: s.q, s.qp = s.qp[1], None
        if s.pp and "p" not in A[min(s.pp[0], len(A) - 1)][pc]: s.p, s.pp = s.pp[1], None
        # a visible value nothing reads any more is forgotten (named as the run's start value, never read)
        L = self.live[pc]
        for kind, bit, attr in (("mac", 1, "mac"), ("clip", 2, "clip")):
            pend = [e[0] for e in s.fq if e[1] & bit]
            alive = kind in A[min(min(pend), len(A) - 1)][pc] if pend else kind in L
            if not alive: setattr(s, attr, None)
        if s.q is not None and not ("qv" in A[min(s.qp[0], len(A) - 1)][pc] if s.qp else "qv" in L): s.q = None
        if s.p is not None and not ("pv" in A[min(s.pp[0], len(A) - 1)][pc] if s.pp else "pv" in L): s.p = None
        return s

    def find_entries(self):
        ents = {0}
        for pc, (lo, hi, up, lw) in enumerate(self.code):
            if hi >> 30 & 1:  # [E]: the run stops after the next pair, MSCNT may go on there
                if pc + 2 < len(self.code):
                    ents.add(pc + 2)
        return sorted(ents)

    def node(self, pc: int, s: St):
        """The node for pair pc in state s, made if new, and the moves the way there needs: (id, moves)."""
        if not 0 <= pc < len(self.code):
            raise Unsupported(f"pc {pc:#x} outside the program")
        lw = self.code[pc][3]
        if s.vib is not None and not (lw and s.vib in lw.vi_reads_br):
            s = s.copy()
            s.vib = None
        s, moves = self.trim(pc, s).canon()
        k = (pc, s.key())
        if k in self.nodes:
            return self.nodes[k], moves
        self.per_pc[pc] = self.per_pc.get(pc, 0) + 1
        if self.per_pc[pc] > MAX_VERSIONS:
            raise Unsupported(f"pair {pc:#x} reached in more than {MAX_VERSIONS} timing states")
        i = len(self.order)
        self.nodes[k] = i
        self.order.append((i, pc, s))
        self.todo.append(i)
        return i, moves

    def build(self):
        self.todo = []
        self.entry_nodes = {pc: self.node(pc, St())[0] for pc in self.entries}
        while self.todo:
            i = self.todo.pop()
            self.step(i)

    # one pair: the state after it and where it goes (vu1.c run()'s loop body)
    def step(self, i: int):
        _, pc, s0 = self.order[i]
        lo, hi, up, lw = self.code[pc]
        s = s0.copy()
        info = {"pc": pc}
        stall = s.stall(up.reads + (lw.reads if lw else []))
        s.advance(stall)
        s.commit()
        info["stall"] = stall
        info["q_in"] = s.q        # what an upper Q read sees
        info["vib"] = s.vib
        extra = 0
        if lw:
            n = lw.name
            if n in ("div", "sqrt", "rsqrt"):
                if s.qp:
                    extra = max(0, s.qp[0])
                    s.advance(extra)
                    s.commit()
                    if s.qp:  # still busy can't be: advanced to its ready cycle
                        s.q, s.qp = s.qp[1], None
                info["qw"] = s.slot(pc, "q")
                s.qp = (13 if n == "rsqrt" else 7, info["qw"])
            elif n == "waitq":
                if s.qp:
                    extra = max(0, s.qp[0])
                    s.advance(extra)
                    s.commit()
            elif n == "waitp":
                if s.pp:
                    extra = max(0, s.pp[0])
                    s.advance(extra)
                    s.commit()
            elif n == "efu":
                if s.pp:
                    extra = max(0, s.pp[0])
                    s.advance(extra)
                    s.commit()
                info["pw"] = s.slot(pc, "p")
                s.pp = (18, info["pw"])
            elif n == "mfp":
                info["p_in"] = s.p
            elif n in ("fmeq", "fmand", "fmor"):
                info["mac_in"] = s.mac
                if s.mac is not None: self.mac_reads.append((i, s.mac))
            elif n in ("fceq", "fcand", "fcor", "fcget"):
                info["clip_in"] = s.clip
            elif n == "fcset":
                s.fq = tuple((r, h & ~2, p) for r, h, p in s.fq)
                info["fw"], info["fwk"] = s.slot(pc, "clip"), "clip"
                s.clip = info["fw"]
            if lw.vfw:
                r, m = lw.vfw
                for f in fields(m):
                    s.vfr[(r, f)] = 4
        info["extra"] = extra
        if up.op != "nop" and up.to is not None and up.to not in (0, 32):
            for f in fields(up.dest):
                s.vfr[(up.to, f)] = 4
        has = (1 if up.op == "fmac" and up.setmac else 0) | (2 if up.op == "clip" else 0)
        if has:
            info["fwk"] = "mac" if has & 1 else "clip"
            info["fw"] = s.slot(pc, info["fwk"])
            s.fq = s.fq + ((4, has, info["fw"]),)
        # the VI backup for the next pair
        w = lw.vi_write() if lw else None
        s.vib = w if (w and not lw.flag) else None
        info["vibw"] = s.vib
        s.advance(1)
        # where to
        if s0.delay and lw and lw.branch:
            raise Unsupported(f"a branch in the delay slot at {pc:#x}")
        nxt = s.copy()
        nxt.delay, nxt.ending = None, False
        if s0.ending:
            info["way"] = ("end", s0.delay, s)
        elif s0.delay:
            d = s0.delay
            nxt.ending = bool(hi >> 30 & 1)
            if d[0] == "t":
                info["way"] = ("goto", self.node(d[1], nxt))
            elif d[0] == "c":
                info["way"] = ("cond", self.node(d[1], nxt), self.node(pc + 1, nxt))
            else:
                cases = {}
                for t in sorted(self.jr_to.get(d[1], ())):
                    cases[t] = self.node(t, nxt)
                info["way"] = ("jump", cases, s)
        else:
            nxt.ending = bool(hi >> 30 & 1)
            if lw and lw.branch:
                b = lw.branch
                nxt.delay = ("t", b[1]) if b[0] in ("b", "bal") else ("c", b[1]) if b[0] == "cond" else ("j", lw.is_ & 15)
            info["way"] = ("goto", self.node(pc + 1, nxt))
        self.succ[i] = info
        if "qw" in info: self.uses_q.add(info["qw"])
        if "pw" in info: self.uses_p.add(info["pw"])

    # ------------------------------------------------------------ C
    def end_state(self, s: St):
        """The values a run leaves in mac_now / clip_now / q_reg / p_reg: everything landed."""
        mac, clip = s.mac, s.clip
        for _, h, p in s.fq:
            if h & 1: mac = p
            if h & 2: clip = p
        q = s.qp[1] if s.qp else s.q
        p = s.pp[1] if s.pp else s.p
        return mac, clip, q, p

    # ------------------------------------------------------------ values already as the VU writes them
    @staticmethod
    def cbit(r, f):
        return 1 << (r * 4 + f)

    def canon_out(self, pc, cin):
        """The fields (bit r*4+f, r 32 = ACC) that hold a finite non-denormal float after pair pc, given cin
        before it: what fo() / qop() / pop() wrote, or a copy of one.  fin() of those is the value itself."""
        lo, hi, up, lw = self.code[pc]
        c = cin
        B = self.cbit
        if lw:  # the lower runs first (its writes land before the upper's)
            n, d, it, is_ = lw.name, lw.dest, lw.it, lw.is_
            if n in ("move", "mr32") and it:
                src = [0, 1, 2, 3] if n == "move" else [1, 2, 3, 0]
                for f in fields(d):
                    c = (c | B(it, f)) if cin & B(is_, src[f]) else (c & ~B(it, f))
            elif n in ("rnext", "rget", "mfp") and it:
                for f in fields(d): c |= B(it, f)
            elif lw.vfw:
                r, m = lw.vfw
                for f in fields(m): c &= ~B(r, f)
        if up.op in ("fmac", "itof", "abs") and up.to:
            for f in fields(up.dest): c |= B(up.to, f)
        elif up.op == "ftoi" and up.to:
            for f in fields(up.dest): c &= ~B(up.to, f)
        c |= B(0, 0) | B(0, 1) | B(0, 2) | B(0, 3)
        return c

    def canon_in(self):
        """canon[i]: the fields canonical at node i on every path to it (from each entry: only vf00)."""
        start = self.cbit(0, 0) | self.cbit(0, 1) | self.cbit(0, 2) | self.cbit(0, 3)
        full = (1 << (33 * 4)) - 1
        cin = {i: full for i in self.succ}
        for i in self.entry_nodes.values():
            cin[i] = start
        changed = True
        while changed:
            changed = False
            for i, info in self.succ.items():
                out = self.canon_out(info["pc"], cin[i])
                for j, _ in self.edges(info["way"]):
                    v = cin[j] & out
                    if j in self.entry_nodes.values():
                        v &= start
                    if v != cin[j]:
                        cin[j] = v
                        changed = True
        self.canon = cin

    def emit(self) -> str:
        self.canon_in()
        # the ends need their producers kept too
        for i, info in list(self.succ.items()):
            way = info["way"]
            if way[0] in ("end", "jump"):
                mac, _, _, _ = self.end_state(way[-1])
                if mac is not None: self.mac_reads.append((i, mac))
        out = []
        n = self.n
        out.append(f"static int tr_{n}(u32 pc) {{")
        out.append("    u32 cy = 0, np = 0, jt = 0;")
        out.append("    int tk = 0;")
        out.append("    u16 vibo = 0;")
        self.mac_live()
        nm = 1 + max([info["fw"] for info in self.succ.values() if info.get("fwk") == "mac"] + [0])
        nc = 1 + max([info["fw"] for info in self.succ.values() if info.get("fwk") == "clip"] + [0])
        nq, npv = 1 + max(self.uses_q | {0}), 1 + max(self.uses_p | {0})
        out.append(f"    u32 fm[{nm}] = {{ 0 }}, fc[{nc}] = {{ 0 }}, qv[{nq}] = {{ 0 }}, pv[{npv}] = {{ 0 }};")
        out.append("    switch (pc) {")
        for pc, i in self.entry_nodes.items():
            out.append(f"    case {pc:#x}: goto n{i};")
        out.append("    default: return 0;")
        out.append("    }")
        for i, pc, s in self.order:
            out.extend(self.emit_pair(i, pc, s))
        out.append("}")
        return "\n".join(out)

    def qname(self, p):
        return "q_reg" if p is None else f"qv[{p}]"

    def pname(self, p):
        return "p_reg" if p is None else f"pv[{p}]"

    def macname(self, p):
        return "mac_now" if p is None else f"fm[{p}]"

    def clipname(self, p):
        return "clip_now" if p is None else f"fc[{p}]"

    def mac_live(self):
        """The FMAC pairs whose MAC flag some read (an FM* or the run's end) sees: back from each read of slot
        k through the graph to the pairs that last wrote k."""
        preds = {}
        for i, info in self.succ.items():
            for j, moves in self.edges(info["way"]):
                back = {new: old for arr, new, old in moves if arr == "fm"}
                preds.setdefault(j, []).append((i, back))
        self.mac_nodes = set()

        def up(j, k):  # slot k at j's entry: where it was in each predecessor
            return [(p, back.get(k, k)) for p, back in preds.get(j, [])]
        for i, k in self.mac_reads:
            seen, todo = set(), [(i, k)] if self.reads_at_end(i) else up(i, k)
            while todo:
                j, k2 = todo.pop()
                if (j, k2) in seen:
                    continue
                seen.add((j, k2))
                info = self.succ[j]
                if info.get("fwk") == "mac" and info["fw"] == k2:
                    self.mac_nodes.add(j)
                    continue
                todo.extend(up(j, k2))

    @staticmethod
    def edges(way):
        if way[0] == "goto": return [way[1]]
        if way[0] == "cond": return [way[1], way[2]]
        if way[0] == "jump": return list(way[1].values())
        return []

    def reads_at_end(self, i):
        return self.succ[i]["way"][0] in ("end", "jump")

    def emit_pair(self, i, pc, s):
        lo, hi, up, lw = self.code[pc]
        info = self.succ[i]
        o = [f"n{i}: /* {pc:03x} */"]
        o.append(f"    cy += {info['stall'] + info['extra'] + 1}; np++;")
        # the upper into temporaries
        commit = []
        KN = ["K_ADD", "K_SUB", "K_MADD", "K_MSUB", "K_MAX", "K_MINI", "K_MUL"]
        dst = "acc" if up.to == 32 else f"vf[{up.to}]"
        mac = up.op == "fmac" and up.setmac and i in self.mac_nodes
        if up.op == "fmac" and not mac and up.tsrc[0] != "op":
            # four lanes at once (vu1.c's vu_op: NEON on the Vita); an operand already canonical skips fin()
            C, B = self.canon[i], self.cbit
            ca = all(C & B(up.fs, f) for f in range(4))
            cc = all(C & B(32, f) for f in range(4))
            if up.tsrc[0] == "vf":
                cb = all(C & B(up.ft, f) for f in range(4))
                call = f"vu_op(u, {KN[up.k]}, vf[{up.fs}], vf[{up.ft}], acc, {int(not ca)}, {int(not cb)}, {int(not cc)});"
            else:
                cb = (up.tsrc[0] == "bc" and C & B(up.ft, up.tsrc[1])) or up.tsrc[0] == "q"
                if up.tsrc[0] == "bc":  # session 147: the field from the VF's vector (vu1.c vu_opbl)
                    call = (f"vu_opbl(u, {KN[up.k]}, vf[{up.fs}], vf[{up.ft}], {up.tsrc[1]}, acc, {int(not ca)}, "
                            f"{int(not cb)}, {int(not cc)});")
                else:
                    b = {"q": "&" + self.qname(info["q_in"]), "i": "&i_reg"}[up.tsrc[0]]
                    call = f"vu_opb(u, {KN[up.k]}, vf[{up.fs}], {b}, acc, {int(not ca)}, {int(not cb)}, {int(not cc)});"
            direct = up.dest == 0xF and up.to and not self.lower_touches(lw, up.to)
            if direct:  # nothing in the lower reads or writes the target: straight into it
                o.append(f"    {{ u32 *u = {dst}; {call} }}")
            else:
                o.append(f"    {{ u32 u[4]; {call}")
                if up.to:  # session 147: u is NEON's, so NEON merges it (vu1.c vu_put)
                    commit.append(f"    vu_put({dst}, u, {up.dest:#x});")
                commit.append("    }")
        elif up.op in ("itof", "ftoi"):
            o.append(f"    {{ u32 u[4]; vu_{up.op}(u, vf[{up.fs}], {up.k});")
            if up.to:
                commit.append(f"    vu_put({dst}, u, {up.dest:#x});")
            commit.append("    }")
        elif up.op == "fmac" and up.k not in (K_MAX, K_MINI):
            # session 141: the MAC-flag and cross-product (OPMULA / OPMSUB) forms on four lanes too (vu1.c's
            # vu_ope: NEON on the Vita), the scalar form kept for the lanes where NEON's flush to zero could
            # differ from it (vu_ope answers 0; always 0 off ARM)
            o.append("    {")
            o.append("    u32 m = 0, u[4];" if mac else "    u32 u[4];")
            mp = "&m" if mac else "0"
            if up.tsrc[0] == "op":
                o.append(f"    u32 sa[4] = {{ vf[{up.fs}][1], vf[{up.fs}][2], vf[{up.fs}][0], 0 }};")
                o.append(f"    u32 sb[4] = {{ vf[{up.ft}][2], vf[{up.ft}][0], vf[{up.ft}][1], 0 }};")
                o.append(f"    if (!vu_ope(u, {KN[up.k]}, sa, sb, acc, {up.dest:#x}, {mp})) {{")
            elif up.tsrc[0] == "vf":
                o.append(f"    if (!vu_ope(u, {KN[up.k]}, vf[{up.fs}], vf[{up.ft}], acc, {up.dest:#x}, {mp})) {{")
            else:
                if up.tsrc[0] == "bc":
                    o.append(f"    if (!vu_opbel(u, {KN[up.k]}, vf[{up.fs}], vf[{up.ft}], {up.tsrc[1]}, acc, {up.dest:#x}, {mp})) {{")
                else:
                    b = {"q": "&" + self.qname(info["q_in"]), "i": "&i_reg"}[up.tsrc[0]]
                    o.append(f"    if (!vu_opbe(u, {KN[up.k]}, vf[{up.fs}], {b}, acc, {up.dest:#x}, {mp})) {{")
            for f in fields(up.dest):
                a = f"fin(vf[{up.fs}][{f}])" if up.tsrc[0] != "op" else f"fin(vf[{up.fs}][{(1, 2, 0)[f]}])"
                if up.tsrc[0] == "bc": b = f"fin(vf[{up.ft}][{up.tsrc[1]}])"
                elif up.tsrc[0] == "vf": b = f"fin(vf[{up.ft}][{f}])"
                elif up.tsrc[0] == "op": b = f"fin(vf[{up.ft}][{(2, 0, 1)[f]}])"
                elif up.tsrc[0] == "q": b = f"fin({self.qname(info['q_in'])})"
                else: b = "fin(i_reg)"
                if up.k in (K_MADD, K_MSUB):
                    e = f"fin(acc[{f}]) {'+' if up.k == K_MADD else '-'} {a} * {b}"
                else:
                    e = f"{a} {OPC[up.k]} {b}"
                o.append(f"    f32 r{f} = {e};")
                o.append(f"    u[{f}] = " + (f"fout(r{f}, {f}, &m);" if mac else f"fo(r{f});"))
            o.append("    }")
            if mac:
                o.append(f"    {self.macname(info['fw'])} = m;")
            if up.to:
                commit.append(f"    vu_put({dst}, u, {up.dest:#x});")
            commit.append("    }")
        elif up.op == "fmac":
            o.append("    {")
            if mac:
                o.append("    u32 m = 0;")
            for f in fields(up.dest):
                a = f"fin(vf[{up.fs}][{f}])" if up.tsrc[0] != "op" else f"fin(vf[{up.fs}][{(1, 2, 0)[f]}])"
                if up.tsrc[0] == "bc": b = f"fin(vf[{up.ft}][{up.tsrc[1]}])"
                elif up.tsrc[0] == "vf": b = f"fin(vf[{up.ft}][{f}])"
                elif up.tsrc[0] == "op": b = f"fin(vf[{up.ft}][{(2, 0, 1)[f]}])"
                elif up.tsrc[0] == "q": b = f"fin({self.qname(info['q_in'])})"
                else: b = "fin(i_reg)"
                k = up.k
                if k in (K_MAX, K_MINI):
                    cmp = ">" if k == K_MAX else "<"
                    o.append(f"    f32 a{f} = {a}, b{f} = {b};")
                    o.append(f"    u32 u{f} = fo(a{f} {cmp} b{f} ? a{f} : b{f});")
                    continue
                if k in (K_MADD, K_MSUB):
                    e = f"fin(acc[{f}]) {'+' if k == K_MADD else '-'} {a} * {b}"
                else:
                    e = f"{a} {OPC[k]} {b}"
                o.append(f"    f32 r{f} = {e};")
                o.append(f"    u32 u{f} = " + (f"fout(r{f}, {f}, &m);" if mac else f"fo(r{f});"))
            if mac:
                o.append(f"    {self.macname(info['fw'])} = m;")
            if up.to:
                for f in fields(up.dest):
                    commit.append(f"    {dst}[{f}] = u{f};")
            commit.append("    }")
        elif up.op == "abs":
            o.append("    {")
            sc = ["1.0f", "16.0f", "4096.0f", "32768.0f"]
            for f in fields(up.dest):
                if up.op == "itof": e = f"itof(vf[{up.fs}][{f}], {sc[up.k]})"
                elif up.op == "ftoi": e = f"ftoi(vf[{up.fs}][{f}], {sc[up.k]})"
                else: e = f"absf(vf[{up.fs}][{f}])"
                o.append(f"    u32 u{f} = {e};")
            if up.to:
                for f in fields(up.dest):
                    commit.append(f"    vf[{up.to}][{f}] = u{f};")
            commit.append("    }")
        elif up.op == "clip":
            o.append(f"    clip_last = vu_clipw(vf[{up.fs}], vf[{up.ft}]);")
            o.append(f"    {self.clipname(info['fw'])} = clip_last;")
        if hi >> 31 & 1:
            o.append(f"    i_reg = {lo:#x}u;")
        elif lw:
            o.extend(self.emit_lower(pc, lw, info, i))
        o.extend(commit)
        o.extend(self.emit_way(i, pc, info))
        return o

    @staticmethod
    def lower_touches(lw, r):
        if not lw:
            return False
        if r == 32:
            return False  # no lower instruction reads or writes ACC
        return any(x == r for x, _ in lw.reads) or (lw.vfw and lw.vfw[0] == r) or \
            (lw.name in ("move", "mr32", "mfir", "rnext", "rget", "mfp") and lw.it == r)

    @staticmethod
    def store4(dst, src, dest):
        if dest == 0xF:
            return [f"    memcpy({dst}, {src}, 16);"]
        return [f"    {dst}[{f}] = {src}[{f}];" for f in fields(dest)]

    def vi(self, r):
        return f"vi[{r}]"

    def set_vi(self, r, e, i):
        if not r:
            return [f"    (void)({e});"] if "kick" in e else []
        out = []
        if self.backup_needed(i, r):
            out.append(f"    vibo = vi[{r}];")
        out.append(f"    vi[{r}] = (u16)({e});")
        return out

    def backup_needed(self, i, r):
        """Does a branch right after this pair read VI r (and so the value from before this pair)?"""
        way = self.succ[i]["way"]
        nxt = []
        for j, _ in self.edges(way):
            pc = self.order[j][1]
            lw = self.code[pc][3]
            if lw and r in lw.vi_reads_br:
                return True
        return False

    def vib(self, r, info):
        return "vibo" if info["vib"] == r else f"vi[{r}]"

    def emit_lower(self, pc, lw, info, i):
        n, d = lw.name, lw.dest
        it, is_, id_ = lw.it, lw.is_, lw.id
        o = []
        A = lambda e: f"mem[({e}) & (DATA_QW - 1)]"
        if n == "nop": return o
        if n in ("iadd", "isub", "iand", "ior"):
            op = {"iadd": "+", "isub": "-", "iand": "&", "ior": "|"}[n]
            return self.set_vi(id_ & 15, f"vi[{is_ & 15}] {op} vi[{it & 15}]", i)
        if n == "iaddi":
            v = id_ - 32 if id_ & 16 else id_
            return self.set_vi(it & 15, f"vi[{is_ & 15}] + ({v})", i)
        if n in ("move", "mr32"):
            if not it: return o
            src = [0, 1, 2, 3] if n == "move" else [1, 2, 3, 0]
            o.append("    {")
            for f in fields(d): o.append(f"    u32 l{f} = vf[{is_}][{src[f]}];")
            for f in fields(d): o.append(f"    vf[{it}][{f}] = l{f};")
            o.append("    }")
            return o
        if n in ("lqi", "lqd"):
            r = is_ & 15
            if n == "lqd": o.extend(self.set_vi(r, f"vi[{r}] - 1", i))
            if it:
                o.append(f"    {{ u32 *a = {A(f'vi[{r}]')};")
                for f in fields(d): o.append(f"    vf[{it}][{f}] = a[{f}];")
                o.append("    }")
            if n == "lqi": o.extend(self.set_vi(r, f"vi[{r}] + 1", i))
            return o
        if n in ("sqi", "sqd"):
            r = it & 15
            if n == "sqd": o.extend(self.set_vi(r, f"vi[{r}] - 1", i))
            o.append(f"    {{ u32 *a = {A(f'vi[{r}]')};")
            for f in fields(d): o.append(f"    a[{f}] = vf[{is_}][{f}];")
            o.append("    }")
            if n == "sqi": o.extend(self.set_vi(r, f"vi[{r}] + 1", i))
            return o
        if n in ("div", "sqrt", "rsqrt"):
            o.append(f"    {self.qname(info['qw'])} = qop({lw.x:#x}, vf[{is_}][{lw.fsf}], vf[{it}][{lw.ftf}]);")
            return o
        if n in ("waitq", "waitp"): return o
        if n == "mtir": return self.set_vi(it & 15, f"vf[{is_}][{lw.fsf}]", i)
        if n == "mfir":
            if not it: return o
            for f in fields(d): o.append(f"    vf[{it}][{f}] = (u32)(s32)(s16)vi[{is_ & 15}];")
            return o
        if n == "ilwr":
            return self.set_vi(it & 15, f"{A(f'vi[{is_ & 15}]')}[{(fields(d) or [0])[0]}]", i)
        if n == "iswr":
            o.append(f"    {{ u32 *a = {A(f'vi[{is_ & 15}]')};")
            for f in fields(d): o.append(f"    a[{f}] = vi[{it & 15}];")
            o.append("    }")
            return o
        if n in ("rnext", "rget"):
            if n == "rnext": o.append("    r_reg = rnext(r_reg);")
            if it:
                for f in fields(d): o.append(f"    vf[{it}][{f}] = r_reg;")
            return o
        if n == "rinit": return [f"    r_reg = 0x3F800000 | (vf[{is_}][{lw.fsf}] & 0x7FFFFF);"]
        if n == "rxor": return [f"    r_reg = 0x3F800000 | ((r_reg ^ vf[{is_}][{lw.fsf}]) & 0x7FFFFF);"]
        if n == "mfp":
            if not it: return o
            pn = self.pname(info.get("p_in"))
            for f in fields(d): o.append(f"    vf[{it}][{f}] = {pn};")
            return o
        if n == "xtop": return self.set_vi(it & 15, "top", i)
        if n == "xitop": return self.set_vi(it & 15, "itop", i)
        if n == "xgkick": return [f"    kick(vi[{is_ & 15}]);"]
        if n == "efu":
            return [f"    {self.pname(info['pw'])} = pop({lw.x:#x}, vf[{is_}], {lw.fsf});"]
        if n == "lq":
            if not it: return o
            o.append(f"    {{ u32 *a = {A(f'vi[{is_ & 15}] + ({s11(lw.raw)})')};")
            for f in fields(d): o.append(f"    vf[{it}][{f}] = a[{f}];")
            o.append("    }")
            return o
        if n == "sq":
            o.append(f"    {{ u32 *a = {A(f'vi[{it & 15}] + ({s11(lw.raw)})')};")
            for f in fields(d): o.append(f"    a[{f}] = vf[{is_}][{f}];")
            o.append("    }")
            return o
        if n == "ilw":
            return self.set_vi(it & 15, f"{A(f'vi[{is_ & 15}] + ({s11(lw.raw)})')}[{(fields(d) or [0])[0]}]", i)
        if n == "isw":
            o.append(f"    {{ u32 *a = {A(f'vi[{is_ & 15}] + ({s11(lw.raw)})')};")
            for f in fields(d): o.append(f"    a[{f}] = vi[{it & 15}];")
            o.append("    }")
            return o
        imm15 = (lw.raw >> 10 & 0x7800) | (lw.raw & 0x7FF)
        if n == "iaddiu": return self.set_vi(it & 15, f"vi[{is_ & 15}] + {imm15:#x}", i)
        if n == "isubiu": return self.set_vi(it & 15, f"vi[{is_ & 15}] - {imm15:#x}", i)
        c = self.clipname(info.get("clip_in"))
        imm24 = lw.raw & 0xFFFFFF
        if n == "fceq": return self.set_vi(1, f"({c}) == {imm24:#x}u", i)
        if n == "fcand": return self.set_vi(1, f"(({c}) & {imm24:#x}u) != 0", i)
        if n == "fcor": return self.set_vi(1, f"((({c}) | {imm24:#x}u) & 0xFFFFFF) == 0xFFFFFF", i)
        if n == "fcget": return self.set_vi(it & 15, f"({c}) & 0xFFF", i)
        if n == "fcset": return [f"    clip_last = {self.clipname(info['fw'])} = {imm24:#x}u;"]
        if n == "fsset": return []  # the status flag is not kept
        mn = self.macname(info.get("mac_in"))
        if n == "fmeq": return self.set_vi(it & 15, f"(vi[{is_ & 15}] & 0xFFFF) == ({mn} & 0xFFFF)", i)
        if n == "fmand": return self.set_vi(it & 15, f"vi[{is_ & 15}] & {mn}", i)
        if n == "fmor": return self.set_vi(it & 15, f"vi[{is_ & 15}] | {mn}", i)
        tgt = lw.branch[1] if lw.branch and len(lw.branch) > 1 else None
        if n == "b": return []
        if n == "bal": return self.set_vi(it & 15, f"{pc + 2:#x}", i)
        if n == "jr": return [f"    jt = {self.vib(is_ & 15, info)};"]
        if n == "jalr":
            return [f"    jt = {self.vib(is_ & 15, info)};"] + self.set_vi(it & 15, f"{pc + 2:#x}", i)
        a, b = self.vib(it & 15, info), self.vib(is_ & 15, info)
        cond = {"ibeq": f"{a} == {b}", "ibne": f"{a} != {b}", "ibltz": f"(s16){b} < 0", "ibgtz": f"(s16){b} > 0",
                "iblez": f"(s16){b} <= 0", "ibgez": f"(s16){b} >= 0"}[n]
        return [f"    tk = {cond};"]

    def emit_way(self, i, pc, info):
        way = info["way"]
        o = []
        if way[0] == "goto":
            o.append(f"    {self.go(way[1])}")
        elif way[0] == "cond":
            o.append(f"    if (tk) {self.go(way[1])}")
            o.append(f"    {self.go(way[2])}")
        elif way[0] == "jump":
            o.append("    switch (jt & (MICRO_N - 1)) {")
            for t, e in way[1].items():
                o.append(f"    case {t:#x}: {self.go(e)}")
            o.append("    }")
            o.extend(self.emit_end(way[2], "jt & (MICRO_N - 1)", bad=True))
        else:
            _, d, s = way
            if d is None: nxt = f"{pc + 1:#x}"
            elif d[0] == "t": nxt = f"{d[1]:#x}"
            elif d[0] == "c": nxt = f"tk ? {d[1]:#x} : {pc + 1:#x}"
            else: nxt = "jt & (MICRO_N - 1)"
            o.extend(self.emit_end(s, nxt))
        return o

    @staticmethod
    def go(e):
        j, moves = e
        if not moves:
            return f"goto n{j};"
        tmp = " ".join(f"u32 t{k} = {arr}[{old}];" for k, (arr, new, old) in enumerate(moves))
        put = " ".join(f"{arr}[{new}] = t{k};" for k, (arr, new, old) in enumerate(moves))
        return f"{{ {tmp} {put} goto n{j}; }}"

    def emit_end(self, s, tpc, bad=False):
        mac, clip, q, p = self.end_state(s)
        o = []
        if bad:
            o.append("    tr_lost = 1;")
        if mac is not None: o.append(f"    mac_now = {self.macname(mac)};")
        if clip is not None: o.append(f"    clip_now = {self.clipname(clip)};")
        if q is not None: o.append(f"    q_reg = {self.qname(q)};")
        if p is not None: o.append(f"    p_reg = {self.pname(p)};")
        o.append(f"    tpc = ({tpc}) & (MICRO_N - 1);")
        o.append("    st.insns += np; st.cycles += cy;")
        o.append("    return 1;")
        return o


def programs(elf: Path):
    img = fv.Image(elf)
    out = []
    for n, p in enumerate(fv.programs_from_sections(img)):
        words = []
        for c in p["chunks"]:
            for k in range((c["size"] or 0) // 8):
                words.append((img.w(c["lma"] + 8 * k), img.w(c["lma"] + 8 * k + 4)))
        out.append((n, p["chunks"][0]["vma"] // 8, words))
    return out


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("elf", type=Path)
    ap.add_argument("out", type=Path)
    ap.add_argument("--stats", action="store_true")
    a = ap.parse_args()
    parts = ["/* generated by tools/vu/vu1_translate.py from the user's ELF: never commit (README) */"]
    table = []
    for n, vma, words in programs(a.elf):
        if vma != 0:
            print(f"vu1_translate: P{n} at {vma:#x}: only programs at 0 are translated", file=sys.stderr)
            continue
        pr = Prog(n, words)
        try:
            pr.build()
            body = pr.emit()
        except Unsupported as e:
            print(f"vu1_translate: P{n} left to the interpreter: {e}", file=sys.stderr)
            continue
        ws = ", ".join(f"{lo:#x}u, {hi:#x}u" for lo, hi in words)
        parts.append(f"static const u32 trw_{n}[] = {{ {ws} }};")
        parts.append(body)
        table.append((n, len(words)))
        if a.stats:
            print(f"vu1_translate: P{n}: {len(words)} pairs, {len(pr.order)} emitted, entries "
                  f"{','.join(f'{e:#x}' for e in pr.entries)}, {len(pr.mac_nodes)} MAC producers kept", file=sys.stderr)
    parts.append("static const TrProg tr_progs[] = {")
    for n, nw in table:
        parts.append(f"    {{ trw_{n}, {nw}, tr_{n}, {n} }},")
    parts.append("};")
    parts.append(f"#define TR_PROGS {len(table)}")
    a.out.parent.mkdir(parents=True, exist_ok=True)
    a.out.write_text("\n".join(parts) + "\n")
    print(f"vu1_translate: {len(table)} programs -> {a.out}", file=sys.stderr)


if __name__ == "__main__":
    main()
