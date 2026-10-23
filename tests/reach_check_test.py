#!/usr/bin/env python3
"""Self-test for tools/shift/reach_check.py's analysis on synthetic code (no game data).

  python3 -I tests/reach_check_test.py

Covers the session 21 rules: a pointer walk capped by a decrementing counter (func_00232ad0's
clears) or by an up-counter, a join of two addresses that is stored (`o->p = c ? A : B`), an
argument joined with an unrelated value, D[i] built as lui + addu + %lo, and a switch whose jump
table is read; session 27-34 rules below. Each rule's switch (countdown=False, ...) must bring back the old answer.
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
assert not [e for e in run(join, joins=False, stored_idx=False) if len(e) == 5 and e[4] == "stored"]
# (session 31, stored-idx: without joins the store is of the lowest address + an index, which stores that base;
# session 32, multi-base: the index carries the other address too, so both are stored)
assert [e[1] for e in run(join, joins=False, multi_base=False) if len(e) == 5 and e[4] == "stored"] == [0x0046E120]
assert [e[1] for e in run(join, joins=False) if len(e) == 5 and e[4] == "stored"] == [0x0046E120, 0x00472160]

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

# 10. end-ptr (session 28): func_00123810's `p = *G + 1200; if (p >= &D_002E26A0) ...` (sltu against the next
# name's address) is an end use of 0x002E26A0; `p - &N` (an index into N) and `p == &N` for an unknown p are not
def sltu(rd, rs, rt): return (rs << 21) | (rt << 16) | (rd << 11) | 0x2B
def subu(rd, rs, rt): return (rs << 21) | (rt << 16) | (rd << 11) | 0x23
A3 = 7
ends = lambda ev: sorted((e[1], e[4]) for e in ev if len(e) == 5 and str(e[4]).startswith("end-"))
endp = [lui(A2, 0x002E), lui(A3, 0x002E), addiu(A2, A2, 0x26AC), addiu(A3, A3, 0x26A0), lw(S0, A2, 0),
        addiu(V0, S0, 1200), sltu(V1, V0, A3), bne(V1, 0, 2), sw(V0, A2, 0), sw(0, A2, 0), JR_RA, NOP]
assert ends(run(endp)) == [(0x002E26A0, "end-lt")], ends(run(endp))
assert ends(run(endp, end_ptr=False)) == []
idxsub = [lw(V0, A0, 20), lui(V1, 0x0051), addiu(V1, V1, 0x4F20), subu(V0, V0, V1), JR_RA, NOP]
assert ends(run(idxsub)) == []
same = [lw(V0, A0, 0), lui(V1, 0x0051), addiu(V1, V1, 0x4F20), beq(V0, V1, 2), NOP, NOP, JR_RA, NOP]
assert ends(run(same)) == []
walk = [lui(V0, 0x0051), lui(V1, 0x0051), addiu(V0, V0, 0x4F00), addiu(V1, V1, 0x4F20),
        sw(0, V0, 0), addiu(V0, V0, 4), bne(V0, V1, -3), NOP, JR_RA, NOP]
assert ends(run(walk)) == [(0x00514F20, "end-eq")], ends(run(walk))

# 11. nest-carry (session 29): func_00103a70's 4x4 copy. t5 counts 16 across both loops (never reset); t6 is
# stepped once per outer iteration. The store through t5 reaches at most +60.
def bgez(rs, off): return (0x01 << 26) | (rs << 21) | (0x01 << 16) | (off & 0xFFFF)
T3, T4, T5, T6, T7 = 11, 12, 13, 14, 15
nest = [lui(S0, 0x0049), addiu(S0, S0, -0x3520), addiu(T5, 0, 0), addiu(T7, 0, 0), addiu(T6, 0, 0),
        sll(T3, T6, 2), addiu(T4, 0, 3),
        sll(V0, T5, 2), addu(V1, V0, S0), addiu(T4, T4, -1), addiu(T5, T5, 1), sw(0, V1, 0), bgez(T4, -6),
        addiu(T3, T3, 4),
        addiu(T7, T7, 1), slti(V0, T7, 4), bne(V0, 0, -12), addiu(T6, T6, 4), JR_RA, NOP]
assert idx_end(run(nest), 0x0048CAE0) == 60, idx_end(run(nest), 0x0048CAE0)
assert idx_end(run(nest, nest_carry=False), 0x0048CAE0) is None

# 12. path-step (session 30): the step proved over the paths of the body. (a) func_0011e248: the counter steps in a
# likely branch's slot on the path that loops, the other path returns; (b) func_001269d8: the counter steps in both
# arms (a blezl slot and the fall-through); (c) func_00111510: the pointer walks through a copy (a1 = a0; a0 = a1 + 4)
def bnel(rs, rt, off): return (0x15 << 26) | (rs << 21) | (rt << 16) | (off & 0xFFFF)
def blezl(rs, off): return (0x16 << 26) | (rs << 21) | (off & 0xFFFF)
def lbu(rt, rs, v): return (0x24 << 26) | (rs << 21) | (rt << 16) | (v & 0xFFFF)
T0 = 8
likely_ = [lui(S0, 0x004E), addiu(S0, S0, 0x39F8), addiu(V1, 0, 0),
           lw(V0, S0, 0), bnel(V0, A1, 3), addiu(V1, V1, 1), JR_RA, NOP,
           slti(V0, V1, 4), bne(V0, 0, -7), addiu(S0, S0, 8), JR_RA, NOP]
assert idx_end(run(likely_), 0x004E39F8) == 24, idx_end(run(likely_), 0x004E39F8)  # i < 4: entries 0..3
assert idx_end(run(likely_, path_step=False), 0x004E39F8) is None
arms = [lui(S0, 0x002E), addiu(S0, S0, 0x27C0), addiu(T0, 0, 0),
        lbu(V0, S0, 1), blezl(V0, 2), addiu(T0, T0, 1), addiu(T0, T0, 1),
        sltiu(V0, T0, 4), bne(V0, 0, -6), addiu(S0, S0, 2), JR_RA, NOP]
assert idx_end(run(arms), 0x002E27C0) == 7, idx_end(run(arms), 0x002E27C0)  # +6, a byte at +1
assert idx_end(run(arms, path_step=False), 0x002E27C0) is None
copy_ = [lui(A0, 0x002C), addiu(A0, A0, -0x3480), addiu(A2, 0, 0),
         addu(A1, A0, 0), lw(V0, A1, 0), addiu(A2, A2, 1), slti(V0, A2, 39), bne(V0, 0, -5), addiu(A0, A1, 4),
         JR_RA, NOP]
assert idx_end(run(copy_), 0x002BCB80) == 152, idx_end(run(copy_), 0x002BCB80)  # 39 words
assert idx_end(run(copy_, path_step=False), 0x002BCB80) is None
# a path that loops without the step proves nothing
skip = [lui(S0, 0x004E), addiu(S0, S0, 0x39F8), addiu(V1, 0, 0),
        lw(V0, S0, 0), bne(V0, A1, 2), NOP, addiu(V1, V1, 1),
        slti(V0, V1, 4), bne(V0, 0, -6), addiu(S0, S0, 8), JR_RA, NOP]
assert idx_end(run(skip), 0x004E39F8) is None

# 13. wr-span (session 30): `sw $0,-4(v1)` with v1 = &D + (a0 & 0x1c) writes [D - 4, D + 0x1c); the old count
# added the displacement twice and ended at D + 0x18
andi_ = lambda rt, rs, v: (0x0C << 26) | (rs << 21) | (rt << 16) | v
neg = [andi_(V0, A0, 0x1C), lui(V1, 0x0037), addiu(V1, V1, 0x0140), addu(V1, V1, V0), sw(0, V1, -4), JR_RA, NOP]
wrs = lambda ev: [e[1:] for e in ev if e[0] == "wr"]
assert wrs(run(neg)) == [(0x0037013C, 0x20)], wrs(run(neg))
assert wrs(run(neg, wr_span=False)) == [(0x0037013C, 0x1C)]

# 14. arg-bound (session 30): func_001130a0(i, out) reads D_004D92F0[i] (16 bytes each): the access is argument 0
# times 16 (an "argidx" event, bounded later by the callers), unless a0 may hold something else (a join)
argx = [sll(A0, A0, 4), lui(V0, 0x004E), addiu(V0, V0, -0x6D10), addu(V1, A0, V0), lw(A3, V1, 12), JR_RA, NOP]
aev = lambda ev: [e[2:] for e in ev if e[0] == "argidx"]
assert aev(run(argx)) == [(0x004D92F0, 0, 16, 12, 4)], aev(run(argx))  # D + a0 * 16 + 12, 4 bytes
assert aev(run(argx, arg_bound=False)) == [] and idx_end(run(argx, arg_bound=False), 0x004D92F0) is None
joined = [beq(A1, 0, 2), NOP, lw(A0, A2, 0)] + argx  # a0 = cond ? *a2 : a0
assert aev(run(joined)) == [] and idx_end(run(joined), 0x004D92F0) is None
# the bounds over the call sites: F2 is called with 5 and 2, F1 with 3 and F2's a0 + 1; F3 is not called directly;
# F4 calls itself with a0 + 1 (no fixpoint); F5 is called with -1
F1, F2, F3, F4, F5 = 0x1000, 0x2000, 0x3000, 0x4000, 0x5000
rest = (None,) * 7
calls = {F1: {0x3010: (3,) + rest, 0x2010: (("arg", 0, 1),) + rest}, F2: {0x3020: (5,) + rest, 0x3030: (2,) + rest},
         F5: {0x3040: (-1,) + rest}}
cof = lambda pc: pc & ~0xFFF
ubs = R.arg_bounds({F1, F2, F3, F5}, calls, lambda f: f in calls, cof)
assert ubs[F1][0] == 6 and ubs[F2][0] == 5 and ubs[F3][0] is None and ubs[F5][0] is None and ubs[F1][1] is None, ubs
calls[F4] = {0x3050: (0,) + rest, 0x4010: (("arg", 0, 1),) + rest}
assert R.arg_bounds({F4}, calls, lambda f: f in calls, cof)[F4][0] is None

# 15. arg-keep (session 31): func_00122dc8's `if (!buf) buf = &D[...]`: a1 is the argument on one path and an address
# on the other. The arg-join keeps the argument and dropped the address, so the load through the join at index 4
# was seen only when the address's path was visited first. A shadow visit reports it in every order.
import random  # noqa: E402
keep = [beq(A0, 0, 6), NOP, NOP, NOP, lw(V0, A1, 8), JR_RA, NOP, lui(A1, 0x004F), beq(0, 0, -5), addiu(A1, A1, 0x7150)]
hit = lambda ev: (BASE + 16, 0x004F7150, 8, 4, "mem") in ev
assert hit(run(keep)), run(keep)
assert not hit(run(keep, arg_keep=False))  # the old answer in the default (last pushed first) order
orders = [hit(run(keep, arg_keep=False, visit_rng=random.Random(sd))) for sd in range(16)]
assert True in orders and False in orders, orders  # ... and it depended on the order
assert all(hit(run(keep, visit_rng=random.Random(sd))) for sd in range(16))
assert ("argmem", 1, 8, 4) in run(keep)  # the argument's own reach is still counted
# join-keep: the same for a join with an unknown value. p = cond ? &D : a1; while (*p++) ...: at the loop head a1 and
# a1 + 4 join to unknown (a walk of the argument), and the address's path joined into that was dropped. The shadow
# visits follow &D around the loop (D, D + 4, D + 8, then D + unknown: the walk is unbounded, and it terminates).
walk_ = [beq(A0, 0, 7), NOP, lw(V0, A1, 0), addiu(A1, A1, 4), bne(V0, 0, -3), NOP, JR_RA, NOP,
         lui(A1, 0x004F), beq(0, 0, -8), addiu(A1, A1, 0x7150)]
assert all(idx_end(run(walk_, visit_rng=random.Random(sd)), 0x004F7150) is None for sd in range(16))
assert not [e for e in run(walk_, join_keep=False) if len(e) == 5 and e[4] == "idx"]

# 16. stored-idx (session 31): func_001c5ee8's `ent[i - 1].lk.next = &ent[i]`: storing base + an index stores the base.
# Before, only an exact address counted, and the store was seen with exact values only when the loop's later states
# were not joined before the point was visited (they were, in the default order: no `stored` at all)
sti = [andi_(V0, A0, 0x1C), lui(V1, 0x0037), addiu(V1, V1, 0x0140), addu(V1, V1, V0), sw(V1, A1, 0), JR_RA, NOP]
assert [e[1] for e in run(sti) if len(e) == 5 and e[4] == "stored"] == [0x00370140]
assert not [e for e in run(sti, stored_idx=False) if len(e) == 5 and e[4] == "stored"]

# 17. multi-base (session 32): func_00219f98's `p = c ? D_003F4C68 : D_003F4C78; p[k * 2 + 1]` with k loaded: the SET
# + an unknown index kept only the lower base, so B's unbounded index (B tied to its next name) was seen only in the
# orders that visited the join point with B alone first. The IDX carries both bases, in every order.
mb = [lw(S1, A2, 0), beq(A0, 0, 3), lui(V0, 0x003F), beq(0, 0, 2), addiu(V0, V0, 0x4C68), addiu(V0, V0, 0x4C78),
      sll(V1, S1, 3), addu(A1, V1, V0), lw(V0, A1, 4), JR_RA, NOP]
ibases = lambda ev: sorted({e[1] for e in ev if len(e) == 5 and e[4] == "idx" and e[2] is None})
assert ibases(run(mb)) == [0x003F4C68, 0x003F4C78], [hex(x) for x in ibases(run(mb))]
assert all(ibases(run(mb, visit_rng=random.Random(sd))) == [0x003F4C68, 0x003F4C78] for sd in range(16))
assert ibases(run(mb, multi_base=False)) == [0x003F4C68]  # the old answer in the default order
# the same through a join of two indexed values (each path indexes its own table): both bases, the store too
mj = [lw(S1, A2, 0), sll(V1, S1, 3), beq(A0, 0, 4), lui(V0, 0x003F), addiu(V0, V0, 0x4C68), beq(0, 0, 3),
      addu(A1, V1, V0), addiu(V0, V0, 0x4C78), addu(A1, V1, V0), lw(V0, A1, 4), sw(A1, A3, 0), JR_RA, NOP]
assert all(ibases(run(mj, visit_rng=random.Random(sd))) == [0x003F4C68, 0x003F4C78] for sd in range(16))
assert sorted(e[1] for e in run(mj) if len(e) == 5 and e[4] == "stored") == [0x003F4C68, 0x003F4C78]
assert ibases(run(mj, multi_base=False)) == [0x003F4C68]
# a join elsewhere of a walk's position with the walk's bounded range (an intermediate state some orders visit) is
# not a choice either: p = c ? &D[k & 7] : &D[4]; *p: D + 16 is inside D + [0, 28], no second base
mw = [andi_(V1, A1, 0x1C), lui(V0, 0x003F), beq(A0, 0, 3), addiu(V0, V0, 0x4C68), beq(0, 0, 2), addu(A1, V0, V1),
      addiu(A1, V0, 0x10), lw(V0, A1, 0), JR_RA, NOP]
assert all({e[1] for e in run(mw, visit_rng=random.Random(sd)) if len(e) == 5 and e[4] == "idx"} == {0x003F4C68}
           for sd in range(16))
# a loop head's join is a walk (D, D + 16, ...), not a choice: the walk's steps are not bases
assert {e[1] for e in run(clear, countdown=False) if len(e) == 5 and e[4] == "idx"} == {0x003F8380}

# 18. sign-prune (session 32): func_00169f28's `best = -1; ...; if (best >= 0) f(&D[best])`: a bltz on an exact -1 does
# not fall through, so &D[-1] is never passed (an order that reached the test before the loop's states were joined
# passed it and pinned the name before D)
def bltz(rs, off): return (0x01 << 26) | (rs << 21) | (off & 0xFFFF)
sp = [addiu(S0, 0, -1), bltz(S0, 5), sll(A1, S0, 4), lui(V0, 0x0057), addiu(V0, V0, 0x5090), addu(A1, V0, A1),
      lw(V1, A1, 0), JR_RA, NOP]
assert not [e for e in run(sp) if len(e) == 5 and e[1] == 0x00575080]
assert (BASE + 24, 0x00575080, 0, 4, "mem") in run(sp, sign_prune=False)

# 19. widen-bases (session 32): func_0021d348 leaves one of several state words' addresses in a1 at a call, each joined
# with an unknown value (join-keep shadows). After SHADOW_MAX values the shadow is widened to the lowest base + an
# unknown index, which kept only the lowest base; now it keeps every base, so an unbounded `passidx` (the callee may
# index it) comes from each address in every order that widens
mw5 = [lw(A1, A2, 0)]
for k_ in range(5):
    mw5 += [beq(S0 + k_ % 2, 0, 3), NOP, lui(A1, 0x003F), addiu(A1, A1, 0x34DC + 8 * k_)]
mw5 += [jal(0x00207830), NOP, JR_RA, NOP]
five = {0x003F34DC + 8 * k_ for k_ in range(5)}
unb = lambda ev: {e[3] for e in ev if e[0] == "passidx" and e[4] is None}
for sd in range(8):
    ev = run(mw5, visit_rng=random.Random(sd))
    assert {e[3] for e in ev if e[0] == "passidx"} == five and unb(ev) in (set(), five), (sd, unb(ev))
assert any(unb(run(mw5, widen_bases=False, visit_rng=random.Random(sd))) not in (set(), five) for sd in range(8))

# 20. termination (session 32): func_0025632c (memchr)'s byte loop `while (n-- != -1) if (*p++ == c) ...` with v1 =
# 0xFFFFFFFF. --visit-seed 4 and 6 never ended: each shadow of 0xFFFFFFFF (not an image address: shadow-image) carried
# a new offset of the argument walk, and the walk's two offsets joined to nothing while the next arrival came back as
# the argument (arg-drop caps that at ARG_DROP_MAX). Every order ends, with the default order's events.
def ori(rt, rs, v): return (0x0D << 26) | (rs << 21) | (rt << 16) | v
def move(rd, rs): return (rs << 21) | (rd << 11) | 0x2D
mc = [sltiu(V0, A2, 16), bne(V0, 0, 10), NOP, move(7, A0),  # n < 16: bytes; a3 = p
      lw(V0, 7, 0), bne(V0, 0, 7), move(A0, 7),  # 16 bytes at a time while no hit (seeds 4, 22, 25, 28 did not end)
      addiu(A2, A2, -16), sltiu(V0, A2, 16), beq(V0, 0, -6), addiu(7, 7, 16), move(A0, 7), NOP,
      lui(V0, 0xFFFF), addiu(A2, A2, -1), ori(V0, V0, 0xFFFF), beq(A2, V0, 8), NOP, lui(V1, 0xFFFF), ori(V1, V1, 0xFFFF),
      lbu(V0, A0, 0), beq(V0, A1, 4), addiu(A2, A2, -1), bne(A2, V1, -4), addiu(A0, A0, 1), JR_RA, NOP, JR_RA, NOP]
nam = lambda ev: sorted(str(e) for e in ev if e[0] != "argmem")  # (an argument walk's offsets differ: it is argwide)
want = nam(run(mc))
assert ("argwide", 0) in run(mc) and all(nam(run(mc, visit_rng=random.Random(sd))) == want for sd in range(32))
assert R._addressy(0xFFFFFFFF) and not R._addressy(0xFFFFFFFF, True) and R._addressy(0x003F4C68, True)

# 21. idx-span (session 33): main() pins every name before a bounded index's end, but only up to the end that the
# `tight` analysis gives (bounds from loops and compares against constants). (a) func_0021cfc8: D_003F5C18[i] for i < 6
# keeps its bound (+20, through D_003F5C2C); (b) a byte load's range (D_003F3150[x48e[i]], a party slot: 0..9 or 0xFF)
# and (c) a mask are no tight bound; (d) a byte compared against a constant first is (func_00266d10 rereads it: none)
up6 = [lui(A0, 0x003F), addiu(A0, A0, 0x5C18), addiu(A1, 0, 0), lw(V0, A0, 0), addiu(A0, A0, 4), addiu(A1, A1, 1),
       slti(V0, A1, 6), bne(V0, 0, -5), NOP, JR_RA, NOP]
assert idx_end(run(up6), 0x003F5C18) == 20 and idx_end(run(up6, tight=True), 0x003F5C18) == 20
tbl = lambda ix: ix + [sll(V1, V1, 2), lui(V0, 0x003F), addiu(V0, V0, 0x3150), addu(V0, V0, V1), lw(V1, V0, 0),
                       JR_RA, NOP]
assert idx_end(run(tbl([lbu(V1, A0, 0x48E)])), 0x003F3150) == 0x3FC
assert idx_end(run(tbl([lbu(V1, A0, 0x48E)]), tight=True), 0x003F3150) is None
assert idx_end(run(tbl([andi_(V1, A0, 0xFF)])), 0x003F3150) == 0x3FC
assert idx_end(run(tbl([andi_(V1, A0, 0xFF)]), tight=True), 0x003F3150) is None
cmp10 = tbl([lbu(V1, A0, 0), sltiu(V0, V1, 10), beq(V0, 0, 6), NOP])
assert idx_end(run(cmp10), 0x003F3150) == 36 and idx_end(run(cmp10, tight=True), 0x003F3150) == 36

# 22. likely-slot (session 34): func_001497c8 `for (i = 0; i < 3; i++) if (D_0054C1B0[i].x10 == a) return i;` loads
# +0x10 before the loop and again in the bnezl's slot, after a3 += 0x20: the slot runs only when the back edge is
# taken (runs 0 and 1 of 3), so the loads end at +0x54 (the last at +0x50), not at the header cap + 0x20 (+0x70)
bnezl = lambda rs, off: (0x15 << 26) | (rs << 21) | (off & 0xFFFF)
f97 = [lui(V0, 0x0055), move(A2, 0), addiu(V0, V0, -15952), addiu(7, V0, 16), lw(V1, 7, 0), NOP,
       addiu(7, 7, 32), move(V0, A2), addiu(A2, A2, 1), beq(V1, A0, 6), slti(A1, A2, 3), NOP, NOP,
       bnezl(A1, -8), lw(V1, 7, 0), addiu(V0, 0, -1), JR_RA, NOP]
assert idx_end(run(f97), 0x0054C1C0) == 0x40, idx_end(run(f97), 0x0054C1C0)
assert idx_end(run(f97, likely_slot=False), 0x0054C1C0) == 0x60
assert idx_end(run(f97, tight=True), 0x0054C1C0) == 0x40
assert all(idx_end(run(f97, visit_rng=random.Random(sd)), 0x0054C1C0) == 0x40 for sd in range(8))
# func_0021cfc8's shape: the step a0 += 4 before the back branch (in a beqz's slot), the load in the bnezl's slot: six
# words (+0x14), not seven
cf = [lui(A0, 0x003F), addiu(A0, A0, 0x5C18), move(A1, 0), lw(V0, A0, 0), beq(V0, 0, 2), addiu(A0, A0, 4), NOP,
      addiu(A1, A1, 1), slti(V0, A1, 6), bnezl(V0, -6), lw(V0, A0, 0), JR_RA, NOP]
assert idx_end(run(cf), 0x003F5C18) == 0x14 and idx_end(run(cf, likely_slot=False), 0x003F5C18) == 0x18
# the step in the slot itself: `bnezl t,loop; addiu p,p,4` after `lw v0,0(p)` in the body: the body's loads see
# p up to the header cap (6 words), and the slot's step adds nothing to them
ss = [lui(A0, 0x003F), addiu(A0, A0, 0x5C18), move(A1, 0), lw(V0, A0, 0), addiu(A1, A1, 1), slti(V0, A1, 6),
      bnezl(V0, -4), addiu(A0, A0, 4), JR_RA, NOP]
assert idx_end(run(ss), 0x003F5C18) == 0x14 and idx_end(run(ss, likely_slot=False), 0x003F5C18) == 0x14

# 23. widen-heads (session 34): func_002705f8 (atanf) sets id to -1, 0, 1, 2 or 3 on five paths that meet at one point,
# then reads atanhi[id] (D_00493F38, 4 floats). A bound that grew three times there was widened away in the orders
# that saw the values in ascending order (the default among them); widening is for loop heads, so every order keeps
# the bound; with widen_heads=False some order loses it
def b_(off): return beq(0, 0, off)
fj = [beq(A0, 0, 9), NOP, beq(A1, 0, 9), NOP, beq(A2, 0, 9), NOP, beq(7, 0, 9), NOP,
      b_(9), addiu(V1, 0, 3), b_(7), addiu(V1, 0, -1), b_(5), addiu(V1, 0, 0), b_(3), addiu(V1, 0, 1),
      b_(1), addiu(V1, 0, 2), bltz(V1, 7), sll(V1, V1, 2), lui(V0, 0x0049), addiu(V0, V0, 0x3F38), addu(V0, V0, V1),
      lw(V0, V0, 0), NOP, NOP, JR_RA, NOP]
assert idx_end(run(fj), 0x00493F38) == 12
assert all(idx_end(run(fj, visit_rng=random.Random(sd)), 0x00493F38) == 12 for sd in range(16))
assert any(idx_end(run(fj, widen_heads=False, visit_rng=random.Random(sd)), 0x00493F38) is None for sd in range(16))
# a loop head still widens: an unbounded walk (no counter) ends unbounded
walk = [lui(V0, 0x0049), addiu(V0, V0, 0x3F38), lw(V1, V0, 0), bne(V1, 0, -2), addiu(V0, V0, 4), JR_RA, NOP]
assert idx_end(run(walk), 0x00493F38) is None

# 24. align-end (session 34): a bounded access wider than a byte ends at its largest offset rounded down to its width.
# func_0014a398: `p < &D_0054F440` (p walks D_0054C440 in 192-byte steps), `ld 0(p)`: p <= END - 1, but the last
# doubleword starts at END - 8, so the walk ends at END, not END + 7; a byte load is not rounded
assert R.aligned_end(0x0054C440, 0x0054F43F - 0x0054C440, 8) == 0x0054F440
assert R.aligned_end(0x0054C440, 0x0054F43F - 0x0054C440, 8, align=False) == 0x0054F447
assert R.aligned_end(0x0054C440, 0x2FFF, 1) == 0x0054F440 and R.aligned_end(0x003F5C18, 0x15, 4) == 0x003F5C30
assert R.aligned_end(0x003F5C18, 0x14, 4) == 0x003F5C30 and R.aligned_end(0x00200000, 0x1F, 16) == 0x00200020

# 25. hix-join (session 34): atanf reads atanhi[id] as `lui at,0x49; addu at,at,v0; lwc1 $f2,%lo(D_00493F38)(at)`, a
# lui + index (HIX). Two of them joined to nothing, and join-keep's shadows widened the fourth bound to unbounded;
# they now join to the larger bound (with widen-heads: the default order keeps +12; either switch loses it)
def lwc1(ft, rs, v): return (0x31 << 26) | (rs << 21) | (ft << 16) | (v & 0xFFFF)
AT = 1
# (the values in the order the default visits them, as in atanf: the fall-through path first, then the branches
# from the last one back)
fh = fj[:8] + [b_(9), addiu(V1, 0, -1), b_(7), addiu(V1, 0, 3), b_(5), addiu(V1, 0, 2), b_(3), addiu(V1, 0, 1),
               b_(1), addiu(V1, 0, 0), bltz(V1, 7), sll(V0, V1, 2), lui(AT, 0x0049), addu(AT, AT, V0),
               lwc1(2, AT, 0x3F38), NOP, NOP, NOP, JR_RA, NOP]
assert idx_end(run(fh), 0x00493F38) == 12
assert all(idx_end(run(fh, visit_rng=random.Random(sd)), 0x00493F38) == 12 for sd in range(16))
assert idx_end(run(fh, hix_join=False), 0x00493F38) is None and idx_end(run(fh, widen_heads=False), 0x00493F38) is None

# 26. neg-keep (session 34): func_001571a8 keeps k = -1 until it finds a free slot, then writes &D_00551608[k]
# unchecked. The -1 path's state was joined with the other one (an upper bound, nothing below zero) before it was
# visited in the default order, so the write at D_00551608 - 34 was seen only in some orders; now a dropped small
# negative constant gets a shadow visit, with the other negatives from the same side (k and 16 * k go together)
S3 = 19
nk = [beq(A0, 0, 3), addiu(S3, 0, -1), addiu(S3, 0, 2), NOP, sll(V1, S3, 4), addu(V1, V1, S3), sll(V1, V1, 1),
      lui(V0, 0x0055), addiu(V0, V0, 0x1608), addu(V0, V0, V1), sw(0, V0, 0), JR_RA, NOP]
below = lambda ev: {e[1] for e in ev if len(e) == 5 and e[4] in ("mem", "idx") and e[1] < 0x00551608}
assert below(run(nk)) == {0x00551608 - 34} and not below(run(nk, neg_keep=False))
assert all(below(run(nk, visit_rng=random.Random(sd))) == {0x00551608 - 34} for sd in range(8))

print("reach_check_test: PASS")
