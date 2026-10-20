# Session 22 notes (matching track)

## s22m1: 00125240 MATCHED; 001c62a0 16 -> 15w

| function | mode | before | after | file |
|---|---|---|---|---|
| 00125240 | hand | 3 (s20m1) | **match** | src/hand/text_00120000_s22_s22m1.c |
| 001c62a0 | hand/nostrict | 16 (s19m1) | **15** | s22m1__001c62a0_15w_cbody.c (drafts.tsv updated) |

Counts are true DP LCS words (sc6_s12.py with ROOT patched to the worktree). `make -j2`: byte-identical,
6,979 functions; objdiff report 100% for func_00125240.

### 00125240: matched (flagged: three FP constant pins, as in s20m1)
- The lever: `f32 *q = &D_002E27A4;` declared at the top, store written `*q = x;`. The 27A4 HIGH is
  now emitted with the declaration (low LUID). cse keeps `(mem (reg q))`, and combine folds the LO_SUM
  into the swc1, so the output is still `lui a0` + `swc1 %lo(D_002E27A4)(a0)`. The HIGH's position is
  now independent of where the store sits. The s20 conflict (27A4 HIGH first in sched1 vs. its life
  being no longer than 77E0's) goes away: the 3w draft with this change is 1w (only the 27A4 store one
  slot late). Then pclimb_s15 over the 15 body statements (seed 1, ~2000 steps) found 0.
- Without the three FP pins (k f0, m f2, one f3) the same body is 9w and a 2500-step climb gives 8, so
  the pins stay.
- This differs from the pinned full address (`register f32 *q asm("$4")`, s15/s20), where the HIGH goes
  into a pseudo and the LO_SUM into a0, and combine dissolves the a0 set. Here the pointer is an ordinary
  local, and what matters is its HIGH's LUID, not its register. General tip: to move a symbol's `lui`
  earlier in sched1 ties without moving its store, set a pointer local to the address early and store
  through it later.

### 001c62a0: 16 -> 15
- 15w: a function-level `Cam *c;` set at the top of the loop body (`c = &D_0037A380;` right after the
  `Ent *e` declaration; after the c0 or v[2]-44 statement gives the same result) and the pinned d written
  as `d = &c->e.x;`. The D.n loop test must stay `D_0037A380.n` (`c->n`: 21-22w).
  Spellings with the same count: `d = (f32 *)c; d += 20;`, `(u8 *)c + 80`, `i++; b += 224;`.
  `i = 0` in the declaration: 16.
- What the original's preheader says (from the registers): t6 = v1+240 is a hoisted &D+240 constant
  rewritten by cse2 against the prologue pseudo. s1 is a separate &D register: lk0 = s1+448,
  b = `move s4,s1`, t5 = s1+288, and d = s1+80 inside the loop. Two cse facts decide this:
  - use_related_value tries the bare symbol's own class first. So d = X+80 needs a register holding
    &D in cse1's table before d's init. Otherwise the oldest related constant is used, which is
    &D+240 from `e`, giving t6-160.
  - make_regs_eqv makes a new register the class's first_reg when it lives outside the EBB and its last
    use is later. So once a user `c = &D` copy exists in the preheader before the hoisted insns, cse2
    rewrites t6 as c+240 (s1+240), not v1+240.
- Shape-only finding (154w, size 1140; kept as s22m1__001c62a0_154w_selfcopy_shape.c). Set `c = &D;
  b = (u8 *)c;` after the guard, add a gcse self-copy in the body (`Cam *c2 = c;` after the e
  declaration, `c = c2;` after `b += 224;`), then `d = &c->e.x;` and `while (i < c->n)`. Without the
  self-copy, gcse copy-propagates c to the prologue pseudo and PRE hoists `c + 80` to the prologue,
  where reload rematerialises it as `lui t2; addiu t2,-23600` (156-178w, size 1140). With it, d =
  `addiu t2,s1,80` in the loop, and c s1, b s4, lk0 t8 are all the original's registers. Still wrong:
  - t6 = s1+240 (the make_regs_eqv rule above);
  - the prologue &D is in t2;
  - the hoisted HIGH keeps t9, so there is no `lui s6` remat (the size gap), and every temp shifts.
  The i/c/b init placements give 154-159, all at size 1140.
- Worse, for the record:
  - Inner loop with d indexed (`(&D.e.x)[j]` or `(&c->e.x)[j]`, with c at the top or after the guard):
    179-190w, size 1120-1148. Indexed v is the same as `*v++` (16).
  - b as an in-loop giv (`b = &D + i*224` at the top, after c0, after v[2]-44, or at v; with `*224`,
    `(i*7)<<5`, `(i<<5)*7`, `i*112*2`, `(u32)i`, `ent + i`, or an `s32` offset): 163w, size 1140. The
    `(i<<8)-(i<<5)` spelling gives 181w, size 1164. cse turns b into t4 + &D and loop.c never reduces it
    (the k1 dump shows b's &D is cse1's related value `reg(&D+240) - 240`).
  - Top-level `Cam *c = &D_0037A380;` with d via c (pinned or not), with or without `c->n`: 156-181,
    because PRE hoists `c + 80`.
  - e-> spelling for c0, v[2]-44 and the cpm destinations: 19-200.

### Tools (scratch, not committed)
- var.py: applies a dict of string-replacement variants (each old string must occur exactly once) to a
  base draft and scores each with sc6_s12.py. rtlsum.py: one line per insn of an RTL dump (uid, the
  set, its notes), for comparing passes.
