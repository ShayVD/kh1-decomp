# Session 17 notes

## s17m1: 001c62a0 56w -> 39w (draft, not matched); 00200e28, 00110618 unchanged
- Lever check (session 16 frame-pointer copy): it does not apply to any of the three as written.
  00200e28 is one basic block (the cmove is made at expand; the gcse dump shows no substitutions), and
  cse1 folds a `p = arr` copy inside one extended basic block anyway. 00110618 is a single-block FP
  register-allocation puzzle with no $fp-based address pair. In 001c62a0 the value gcse links is the
  symbol HIGH `(high D_0037A380)` (PRE replaces the in-loop lui with a copy from a reaching reg), not
  an $fp expression, so a frame-base pointer has nothing to hide.
- 001c62a0, new best nonmatchings/session17/s17m1__001c62a0_39w.c (TL 39/39, size 1148 = original,
  hand/nostrict; shift/drafts.tsv updated, `drafts.py build` compiles it). Flagged, like the old draft:
  the c4 probe store and a dead `i = 0;` after the final call (without it the call becomes a sibcall
  `j`: 60w). What moved it from 55:
  (1) integer offsets for the per-entry float block and link: `s32 off = i*224 + 432; f32 *f =
  (f32 *)((u8 *)&D + off);` and the same with 448 for `struct Lk *l`. This alone reproduces the f / lk /
  else-branch shape exactly (kept as s17m1__001c62a0_176w_finding.c: the shape is right, the rest is
  not yet).
  (2) `static inline s32 *rd1(f32 *f, s32 *p)` for each float read. The inlined param/return copies
  vanish from the output but count as insns when loop.c runs; see the threshold fact below.
  (3) a pointer biv `u8 *b` (init &D, `b += 224` per entry) with `v = (f32 *)(b + 336)`. It gives the
  s4 giv and raises pressure so the HIGH pseudo spills and reload rematerialises it (`lui s6`, as in the
  original).
  (4) do-while with an explicit `if (D.n > 0)` guard, so b's init is in its own block.
  Still different: b is `move s1,v1` and the base copy `move t8,s1` (original: base s1, b `move s4,s1`);
  i's `move s0,zero` comes after the guard (original: in the prologue); d is t6-160 (original s1+80);
  &ent[0].lk is in s4 (original t8); t3/t4 swapped.
- 001c62a0 dead ends this session (all worse than 39): a `Cam *` pointer for d/v (180w); in-loop
  `b = &D + i*224` and `(i<<5)*7` forms, with &D or a Cam base, combined with rd1/plain/rd2 count knobs
  (best 109/106; fold rebuilds the address); a toggle climb over 20+ sites (decl order, rd1 vs plain per
  float, guard form, b placement) settled at 39.
- 00200e28 stays 24w (s12w14) and 00110618 stays 93w (s12w6): the lever was the assigned new angle and
  does not apply (above); no other angle not already closed in the NOTES was found. The small ones
  (001fd858, 001cfc28, 001f2630, 001f1fc8, 001f18e8, 001eddc0, 0021e120) were not attempted: no new angle.
- Facts:
  - loop.c hoists an invariant only if `threshold * savings * lifetime >= insn_count`, and threshold drops
    with each move. So the loop's insn count at loop pass 2 decides how many invariants are hoisted. In
    001c62a0: 122 insns hoists 3 (right); 117 hoists 4, and v[3] joins the t5 giv group (wrong).
    Volatile reads change the grouping; inline helpers fix it.
  - Count-tuning lever (new): inline helpers add param/return copy insns before loop.c that are gone
    from the final code. Use them to tune the loop insn count without changing the output.
  - gcse PRE in 2.96 replaces an in-loop `(high SYM)` with a copy from a reaching reg. cprop pass 2
    propagates copies only across blocks. lo_sum is not CONSTANT_P, so it is not const-propagated. loop.c
    does not hoist reg copies when "savings 1, life 1" fails the threshold.
  - A spilled pseudo with REG_EQUIV (high SYM) is rematerialised by reload as a fresh lui.
  - Here an unused local, or the declaration order, changes pseudo numbering and so the global-alloc ties
    (a stray unused `struct Lk *l;` moved the score). Declare a variable only in the variants that use it.
- Tools (tools/matching/, run with `python3 -I`): sc_s17.py (score drafts with a true DP LCS; -d diff,
  -o disassembly), var_s17.py (score a dict of string-replacement variants), tog_s17.py (toggle climb
  over \x01alt0\x03alt1\x02 template sites; env CHECK rejects invalid instances), mktpl_s17.py (builds
  the 001c62a0 template), dump_s17.sh (-da RTL dumps).
