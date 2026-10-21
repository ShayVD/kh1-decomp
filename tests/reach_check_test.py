#!/usr/bin/env python3
"""Self-test for tools/shift/reach_check.py's analysis on synthetic code (no game data).

  python3 -I tests/reach_check_test.py

Covers the session 21 rules: a pointer walk capped by a decrementing counter (func_00232ad0's
clears) or by an up-counter, a join of two addresses that is stored (`o->p = c ? A : B`), an
argument joined with an unrelated value, D[i] built as lui + addu + %lo, and a switch whose jump
table is read. Each rule's switch (countdown=False, ...) must bring back the old answer.
"""
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools" / "shift"))
sys.path.insert(0, str(ROOT / "tools"))
import mips  # noqa: E402
import reach_check as R  # noqa: E402

V0, V1, A0, A1, A2, S0, S1, RA = 2, 3, 4, 5, 6, 16, 17, 31


def lui(rt, v): return (0x0F << 26) | (rt << 16) | v
def addiu(rt, rs, v): return (0x09 << 26) | (rs << 21) | (rt << 16) | (v & 0xFFFF)
def slti(rt, rs, v): return (0x0A << 26) | (rs << 21) | (rt << 16) | (v & 0xFFFF)
def sltiu(rt, rs, v): return (0x0B << 26) | (rs << 21) | (rt << 16) | (v & 0xFFFF)
def lw(rt, rs, v): return (0x23 << 26) | (rs << 21) | (rt << 16) | (v & 0xFFFF)
def sw(rt, rs, v): return (0x2B << 26) | (rs << 21) | (rt << 16) | (v & 0xFFFF)
def sq(rt, rs, v): return (0x1F << 26) | (rs << 21) | (rt << 16) | (v & 0xFFFF)
def addu(rd, rs, rt): return (rs << 21) | (rt << 16) | (rd << 11) | 0x21
def sll(rd, rt, sa): return (rt << 16) | (rd << 11) | (sa << 6)
def bgtz(rs, off): return (0x07 << 26) | (rs << 21) | (off & 0xFFFF)
def bne(rs, rt, off): return (0x05 << 26) | (rs << 21) | (rt << 16) | (off & 0xFFFF)
def beq(rs, rt, off): return (0x04 << 26) | (rs << 21) | (rt << 16) | (off & 0xFFFF)
def jr(rs): return (rs << 21) | 0x08


JR_RA, NOP = jr(RA), 0
BASE = 0x00200000


def run(words, read_word=None, **kw):
    insns = mips.decode(BASE, struct.pack(f"<{len(words)}I", *words))
    labels = {i.branch_target for i in insns if i.is_branch}
    return list(R.analyse(insns, labels, args=True, read_word=read_word, **kw))


def idx_end(evs, base):
    ends = [e[2] for e in evs if e[0] != "argmem" and len(e) == 5 and e[4] == "idx" and e[1] == base]
    assert ends, evs
    return None if None in ends else max(ends)


# 1. clr(D_003F8380, 5824): li v1,N; loop: addiu v1,-1; sq $0,0(v0); bgtz v1,loop; addiu v0,16
clear = [lui(V0, 0x0040), addiu(V1, 0, 5824), addiu(V0, V0, -31872),
         addiu(V1, V1, -1), sq(0, V0, 0), bgtz(V1, -3), addiu(V0, V0, 16), JR_RA, NOP]
ev = run(clear)
assert idx_end(ev, 0x003F8380) == 5823 * 16, idx_end(ev, 0x003F8380)  # the last qword ends at +0x16C00
assert idx_end(run(clear, countdown=False), 0x003F8380) is None
assert R.back_edges("gtz", 1, 1) == 0 and R.back_edges("gtz-slot", 1, 1) == 1 and R.back_edges("nez", 5, 1) == 4

# 2. for (i = 0; i < 2; i++) f(*p++): the up-counter caps the walk
up = [lui(S1, 0x002A), addiu(S0, 0, 0), addiu(S1, S1, 0x3F50),
      lw(A0, S1, 0), addiu(S1, S1, 4), addiu(S0, S0, 1), slti(V0, S0, 2), bne(V0, 0, -5), NOP, JR_RA, NOP]
ev = run(up)
assert idx_end(ev, 0x002A3F50) == 4, idx_end(ev, 0x002A3F50)

# 3. o->p = c ? A : B: two exact addresses stored, no index from the lower one
join = [lw(V1, A1, 0), lui(V0, 0x0047), beq(V1, 0, 3), addiu(V0, V0, 0x2160),
        lui(V0, 0x0047), addiu(V0, V0, -0x1EE0), sw(V0, A0, 16), JR_RA, NOP]
stored = sorted(e[1] for e in run(join) if len(e) == 5 and e[4] == "stored")
assert stored == [0x0046E120, 0x00472160], [hex(x) for x in stored]
assert not [e for e in run(join, joins=False) if len(e) == 5 and e[4] == "stored"]

# 4. a0 reused on one path (p = cond ? arg : other): the argument is not walked
reuse = [beq(A1, 0, 2), NOP, lw(A0, A2, 0), lw(V0, A0, 8), JR_RA, NOP]
assert ("argwide", 0) not in run(reuse)
assert ("argwide", 0) in run(reuse, arg_join=False)

# 5. D[i] as lui + addu + lw %lo(D): an indexed access from D, bounded by andi
hix = [(0x0C << 26) | (A0 << 21) | (V0 << 16) | 0x1C,  # andi v0,a0,0x1c
       lui(V1, 0x0049), addu(V1, V1, V0), lw(V1, V1, 0x1310), JR_RA, NOP]
assert idx_end(run(hix), 0x00491310) == 0x1C
assert not [e for e in run(hix, hi_index=False) if len(e) == 5 and e[4] == "idx"]

# 6. switch(a0) through a jump table read from the image: each case starts from the state at the
# `jr` (a2 = &D), not from the fresh state the code after a `jr` gets without the table
tbl = 0x00491000
sw_ = [lui(A2, 0x0040), addiu(A2, A2, 0x10), sltiu(V0, A0, 2), beq(V0, 0, 13), NOP, sll(V0, A0, 2),
       lui(V1, 0x0049), addu(V1, V1, V0), lw(V1, V1, 0x1000), jr(V1), NOP,
       sw(0, A2, 0), JR_RA, NOP, sw(0, A2, 0x20), JR_RA, NOP]
words = {tbl: BASE + 11 * 4, tbl + 4: BASE + 14 * 4}
mems = lambda ev: sorted(e[1] + e[2] for e in ev if len(e) == 5 and e[4] == "mem")
assert mems(run(sw_, read_word=words.get)) == [0x00400010, 0x00400030], mems(run(sw_, read_word=words.get))
assert mems(run(sw_)) == [], mems(run(sw_))

# 8. counter-cap (session 27): i = 0; v0 = 0; do { lw a1,0(&D + v0); i++; } while (i < 12) with
# v0 = i << 2 in the back branch's delay slot (func_00219870): the index ends at +44, not unbounded
S2, S3 = 18, 19
cnt = [lui(S3, 0x003F), addiu(S2, 0, 0), addiu(S3, S3, 0x4818), sll(V0, S2, 2),
       addu(A0, V0, S3), addiu(S2, S2, 1), lw(A1, A0, 0), slti(V1, S2, 12), bne(V1, 0, -5), sll(V0, S2, 2),
       JR_RA, NOP]
assert idx_end(run(cnt), 0x003F4818) == 44, idx_end(run(cnt), 0x003F4818)
assert idx_end(run(cnt, counter_cap=False), 0x003F4818) is None

# 7. dead-arg (session 27): f(a0) passes a0 on to g and calls h; a1 is never read before it is written,
# a2 only on one path, a3 by a movz that may keep it; an unknown jal reads every argument register
def jal(t): return (0x03 << 26) | ((t >> 2) & 0x3FFFFFF)
def movz(rd, rs, rt): return (rs << 21) | (rt << 16) | (rd << 11) | 0x0A
A3 = 7
G, H, F = 0x00200100, 0x00200200, BASE
dec = lambda a, ws: (a, mips.decode(a, struct.pack(f"<{len(ws)}I", *ws)))
g = dec(G, [lw(V0, A0, 0), JR_RA, NOP])
h = dec(H, [beq(A0, 0, 2), NOP, lw(V0, A2, 0), movz(A3, V0, A0), JR_RA, NOP])
f = dec(F, [addiu(A1, 0, 5), jal(G), NOP, jal(H), NOP, JR_RA, NOP])
live = R.arg_live([g, h, f])
assert live[G] == {A0} and live[H] == {A0, A2, A3} and live[F] == {A0}, live
assert R.arg_live([dec(F, [jal(0x00300000), NOP, JR_RA, NOP])])[F] == R.ALL_ARGS
# li v1,0x64; syscall (FlushCache) reads a0 only; an unknown syscall reads every argument register
sysc = lambda n: dec(F, [addiu(V1, 0, n), 0x0C, JR_RA, NOP])
assert R.arg_live([sysc(0x64)])[F] == {A0} and R.arg_live([sysc(0x3C)])[F] == R.ALL_ARGS

# 9. str-arg, list-arg and dma-chain helpers (session 27) on synthetic bytes
assert R.string_end(b"%s_%d\0\0\0", 0, "fmt") == 6
assert R.string_end(b"50%\0", 0, "fmt") is None  # a lone '%' makes the printer skip the NUL
assert R.string_end(b"\0" * 8, 0, "str") is None  # empty: a buffer, not a literal
assert R.string_end(b"abc\0" + b"\0" * 28, 0, "str") is None  # a long zero tail: a buffer
assert R.string_end(b"a\x0bb\0", 0, "kh") is None and R.string_end(b"a\x0bb\0", 0, "str") == 4
le = lambda *v: b"".join(x.to_bytes(4, "little", signed=True) for x in v)
assert R.list_count(le(8, 9, 10, -1), 4, "m1") == 3 and R.list_count(le(-1, 0), 4, "m1") == 0
assert R.list_count(le(1, 2), 4, "m1") is None and R.list_count(le(1, -1, 5, 0), 4, "m1") is None
mem = {}
for a_, v in zip(range(0x300000, 0x300040, 4), (0x3000000A, 0x2A4900, 0, 0, 0x10000001, 0, 0, 0,
                                                0, 0, 0, 0, 0x70000000, 0, 0, 0)):
    mem[a_] = v
assert R.parse_chain(mem.get, 0x300000, 0x300040) == (0x300040, [(0x2A4900, 0xA0)])  # ref, cnt 1, end 0
assert R.parse_chain(mem.get, 0x300000, 0x300030) is None  # the end tag lies past the object
mem[0x300010] = 0x20000001  # next: not followed
assert R.parse_chain(mem.get, 0x300000, 0x300040) is None

print("reach_check_test: PASS")
