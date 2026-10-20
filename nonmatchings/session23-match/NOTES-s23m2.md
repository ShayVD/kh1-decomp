# Session 23 notes (matching track, worker s23m2)

## s23m2: 001c62a0 and 00200e28 (no matches)

| function | mode | before | after | file |
|---|---|---|---|---|
| 001c62a0 | hand/nostrict | 15 (s22m1) | 15 (best unchanged); new 35w shape | s23m2__001c62a0_35w_cfirst_cn.c |
| 00200e28 | hand | 24 (s12w14) | 24 | - (reviewed only, no new angle) |

Counts are true DP LCS words (sc6_s12.py with ROOT patched to the worktree). shift/drafts.tsv is unchanged
(no draft got fewer words).

### 001c62a0: what the RTL says (new)
- **Why d is hoisted in the 15w draft**: in loop pass 1 the d init (`222 = 103 - 160`) is the last use of
  reg 103 (&D+240, movable insn 52), so force_movables links it ("move-insn forces 52") and move_movables
  moves it regardless of the threshold (the `m->forces->done && n_times_set == 1` rule). It is later
  spilled and rematerialised as `lui t2; addiu t2,-23600`.
- **Why d is 103-160 at all**: cse1's PLUS associate rule in fold_rtx (`lookup_as_function (c, PLUS)`).
  c is set after `e = &D.ent[i]`, so cse1 writes c as `(plus 103 -240)`; then `c + 80` folds to
  `(plus 103 -160)`. It is not use_related_value (that never relates a bare symbol that has no
  table entry).
- **Fix for both, at a price** (35w file): set `c = &D_0037A380;` before `e = &D_0037A380.ent[i];` and
  test `while (i < c->n)`. c is then a plain lo_sum, d stays `c + 80`, and since c's last use is the loop
  test the d insn is not forced: "savings 1 life 1, not desirable", so d is `addiu t2,base,80` in the
  outer loop like the original. Adding `i = 0;` as the first statement of the function then makes the
  whole prologue identical (`move s0,zero` second insn, sd order) and the size right: 40 -> 35w.
- **What that costs**: with c in cse1's table first, every other &D+X constant in the body becomes
  c-relative (v[3..9] addresses `base+304..` instead of `t6+64..`, 103 = base+240) and global-alloc gives
  b s1, base t5, 103 t8, lk0 s4 (orig base s1, 103 t6, lk0 t8, b s4). The original therefore has a base
  register that cse1 does not know is &D inside the body (so d = base+80 survives and the v[k] relate to
  103), yet that PRE cannot hoist base+80 out of the loop. That is exactly s22m1's self-copy shape (154w);
  its remaining gaps are cse2 (t6 = s1+240) and a local-alloc shift (p in t0, the prologue &D in t2), not
  the loop structure.
- Global-alloc in the 15w draft (lreg/greg): callee-saved regs go s0, s1, s2, s3, s4 in priority order:
  i 9/224, b 9/226, set 4/115, add 4/116, c 6/220 (refs/live length). The original's order
  (i, base, set, add, b) needs base >= 8 refs and b <= 7.
- Tried, no gain: flag sweep of the 15w draft over 35 single flags (none below 15; -fno-gcse 27),
  b as an in-loop giv of c (`b = (u8 *)c + i*224` in 7 spellings, at the top or after e): 168-184, size
  1136-1152 (the giv has benefit 2, minus add_cost 2 = 0, "not worth while"; i*224 is shared with e);
  pins c=$17 / b=$20 on 15w and on the 35w shape: 23-169; a function-level `Cam *c = &D` (or set after the
  guard) without the self-copy: 156-189, size 1140 (PRE); c set again at the bottom of the body: 166-168;
  an early `dd = &c->e.x` copied into the pinned d: dd is a user var with life 13 and is hoisted (181);
  the else-branch spellings of `&ent[i]` / `&ent[i-1]` (15, identical); on the self-copy shape: the c2
  copy at all 27 body positions (156-161), test `D.n` (180, size right: the HIGH copy is hoisted again but
  lands in t9), c2 before e, `i = 0` before the guard or at the top (156-160).
- Closed for this session: no single change moves the 15w draft; the 35w and 154w shapes each fix one
  half (cse1/loop vs global-alloc) and break the other.

### 00200e28: stays 24
- Reread s10-s20 notes: inline vertex helpers (477-488), decl order (no effect), types, pins on every
  header constant (25-132), sched dependence analysis. No angle that those notes do not already close;
  not reworked.

### Tools (scratch, not committed)
- var.py (string-replacement variants scored with sc6_s12; strips the header comment first),
  scoredir.py (scores every .c in a directory in a given src/ mode), fsw.py (single-flag sweep through
  lro6_s12's `extra`).

## s23m2, second round (coordinator follow-up): 00200e28 reworked, 001c62a0 two-step combos (no matches)

### 00200e28: stays 24 (s12w14 draft), natural stays 38 (s11w12)
- **Where the 24 words come from** (word-by-word re-diff, all in the header and the first flood vertex;
  the rest of the 1556-byte block is identical):
  - *Scheduling, ~14 words*: li 6 and the 0x7bf8001400000 chain issue right after the eeeee li (orig: 6 after
    the d4 chain, d8 after the d6 chain); sd 80 / sd 48 swapped; `sll w` + `slti` issue late (orig between
    sd 8 and sd 64, ours right before the movn); li 832 early; `sw t0,60` early, li 872 late.
  - *Register allocation, ~10 words* that follow from that order: 6 t7 (orig t5), d8 t5 (orig t0), slti a1
    (orig a0), C[0] a0 (orig v1), e[0] a0 (orig a1).
  - No structural block: prologue, the three calls, the 24 flood vertices and the tail match.
- Experiments, all 24 or worse:
  - clamp/shift spellings (ternary, `W` temp, `<= 831`, `832 > w`, clamp moved to X3, `{ }` else): 24;
    `w *= 16` or a block-local shift temp: 41.
  - PH field types: every Z64/u64 mix of d2/d5/d8 (8 combos) 24-44, all-plain u64 header 37 (the
    current mix is the minimum).
  - single-flag sweep (34 flags): none below 24 (-fno-optimize-sibling-calls 26, -fno-delayed-branch 28).
  - C[0..3] read into locals (as 00200648 does with its colour calls) at 5 positions: 205-335 at size
    1476-1524. The original reloads C[k] at each use, so the colours really are `C[k]` loads after the
    aliasing stores.
  - pclimb_s15 over the 24w header region (40 lines, seed 1): base 24, BEST 24. On the natural 38w draft,
    header + temps + first vertex (32 lines, nostrict): see below.
- Reading: the sibling 00200648 matched in this exact natural shape, so the source is almost certainly
  the 38w natural one. The leftovers are sched1/sched2 tie-breaks inside one 390-insn block. With every
  register and insn already right, only a different dependence graph could flip them, and no type or
  statement order found gives one.

### 001c62a0: two-step combinations of the 35w cfirst_cn shape and the s22 self-copy
On the 35w file (early in-loop `c = &D`, test `c->n`, `i = 0` at the top):
- pre-loop `c = &D; b = (u8 *)c;`, self-copy `Cam *c2 = c;` at the top and `c = c2;` after `b += 224`
  (the in-loop `c = &D` removed): 160, size 1140.
- same, with `c2 = c; c = c2;` both at the top: 156, size 1140.
- the in-loop `c = &D` kept and copied (`c = &D; c2 = c;`), `c = c2;` at the bottom: 135, size 1160.
- `Cam *c2 = &D; c = c2;` at the top (c is a copy of a lo_sum): 35 (identical to the base).
- pre-loop `c = &D` plus `c2 = c; c = &D;` at the top and `c = c2;` at the bottom: 145, size 1192.
- Any version where gcse sees c modified in the loop loses the in-loop HIGH (size 1140); any version
  where c is a lo_sum in the loop gets c-relative constants. Not combinable with these statement levers.
- pclimb_s15 on the natural 38w draft (32 lines from `ub` through the first vertex's `v` store, nostrict,
  seed 3, 3000 steps): 38 -> 25, kept as s23m2__00200e28_25w_natural_climb.c. One word behind the 24w, but
  it uses the sibling's plain u64 types (no unions, no k-vars). A second climb from it (seed 4, 4000
  steps): 25. Its leftovers are the same family as the 24w's (li eeeee/66/6 order, sd 48/56, `sll w` +
  `slti` late with slti in a1, C[0]/e[0] registers).
- Verdict: closed for statement order and types. The next thing to try would be a gdb/sched-verbose read of
  why `sll w` is not ready early in sched2 on the 25w natural draft (its dependence on the a0/a1 occupant).
