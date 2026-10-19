# Session 16 notes

## s16m1: 00166570 MATCHED (hand/nostrict); 00200e28, 00192958 unchanged
- MATCH 00166570 (21w -> 0): src/hand/nostrict/text_00160000_s16_s16m1.c, from s7 w7's draft. Three
  changes: m0/m40/m80 become one array `G2Mtx mm[3]` (same frame offsets 0/64/128); the bone-chain loop
  uses mm[1]/mm[2] directly (s11w37's preheader, no pa/pb); `mp = mm;` (a `G2Mtx *`) set after
  `bones = (*o->p0)->bones;`, and the second post-loop call reads `func_00267e60(mm[0][0], mp[2][0],
  mp[1][0], f)`. Not flagged: plain C, no dead code. Size went 4168 -> 4176 with step 2+3; then 20w
  (s1/s2 swap of pos and the D_00574F20 base in the prologue) with mp set at the top of the function;
  moving `mp = mm;` anywhere between the first PlatSqrtf and the outer loop's first statement gives 0.
  Both post-loop operands must go through mp (only one: 24w; mp in the m0[3]/m80[3]/m40[3] call too: 9w).
- Why it works: mp is `(set mp (reg $fp))`, a REG copy of a hard register. gcse does not hash a REG
  source as an expression and CPROP does not propagate hard registers, so the post-loop (plus mp 128) /
  (plus mp 64) are not PRE-redundant with the pre-loop (plus $fp 64/128) the CopyMatrix calls computed.
  The pre-loop address pseudos then die at the preheader copies (`move s6,s2; move s2,s0`). mp has
  REG_EQUIV $fp (.lreg), gets no hard register, and reload puts sp in its place: the original's
  `addiu a1,sp,128; addiu a2,sp,64` after the loop.
- Lever (new): to keep gcse from linking two occurrences of a frame address (or any $fp-based
  expression), compute one of them from a pointer local set to the frame base (`T *p = arr;` where arr is
  at frame offset 0). It costs nothing in the output (rematerialised as sp) but hides the equivalence until
  after gcse. cse1/cse2 still fold it inside one extended basic block, so the set must be in another block.
- 00200e28 stays 24w (s12w14 draft). New angles, all no change or worse: (a) types: `const`/`volatile`/
  complete `[8][16]` on D_003F2BD8 and on e (24, byte-identical: the flood loads already conflict with the
  alias-set-0 union stores, and RTX_UNCHANGING is not set through a pointer); indexing D_003F2BD8[type][k]
  directly (300+: the address is rebuilt per use); `const u32 *C` (24); param types: u32 for any param 24,
  u16/u8/s16/s8 add extensions (25-164). (b) structure: a static inline vertex helper (`SetV(V48 *v, ...)`
  or `SetV(PQ *p, s32 i, ...)`): 477-488, integrate keeps each &v[i] in its own pseudo and loop/cse hoist
  them as addiu chains; inlining is out for this flood. (c) local declaration order: 150 random orders all
  exactly 24 (pseudo numbering does not touch this single-block local-alloc).
- 00192958 stays 17w (s10 w11 draft). (a) types: FlarePkt fields as unions {u128 q; struct {GsX v; u64 a;}}
  stored through `.q` (17, identical), xy/sc as union pointers (17), volatile packet (97); in nostrict a
  store-only header block has no alias decision for MEM attributes to change. TI constants in u128 locals
  set at the top in 400 random orders: 37-46 (zero splits into two pseudos). Decl order: no effect
  expected (local-alloc), not swept.
- Facts: in 00166570 scalar declaration order changes the result a lot (21-127w over 200 orders, none
  better; arrays kept fixed so the frame stays): pseudo numbers decide global-alloc ties there. In
  00200e28 it changes nothing. FRAME_POINTER_REGNUM is reg 1 (`at`) in ee-gcc 2.96 dumps.
- Housekeeping: shift/unmatched/func_00166570.s removed by tools/shift/export_unmatched.py (15 left),
  its shift/drafts.tsv line removed, old drafts nonmatchings/session7/w7__00166570_27w.c and
  session11/w37__00166570_56w_finding.c deleted; `make -j2`: byte-identical, 6973 functions.
