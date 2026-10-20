# Session 20 notes

## s20m1: 001c62a0, 00200e28, 00125240 (no matches)

Counts are true DP LCS words (sc6_s12.py with ROOT patched to the worktree).

| function | mode | before | after | draft |
|---|---|---|---|---|
| 001c62a0 | hand/nostrict | 16 | 16 | - (one same-count change below) |
| 00200e28 | hand | 24 | 24 | - |
| 00125240 | hand | 3 (flagged: dead FP test) | 3 (flagged: pins, natural body) | s20m1__00125240_3w_pins.c |

drafts.tsv is unchanged: no draft got fewer words.

### 00125240: natural body + FP constant pins, 3w (same count, no dead test)
- s12w17's 8w natural draft had every GPR and insn right; only x and 10000.0f swapped f0/f1. With the
  constants pinned (`register f32 k asm("$f0")`, m in $f2, one in $f3): k alone 5w, k+m or k+one 6w, all three 4w.
  These are constants, so the pins hold. Pinning x (a load) to $f1 makes it worse (10-15w).
- pclimb_s15 over the 13 body statements (several seeds, ~30k steps in total, with and without `p->x = 0` and
  `y = 53.0f` in the region): 4 -> 3. Every FP and GPR is right now (p v0, 2790 v1, 27A4 a0, 77E0 a1).
- Left (3 words): the 77E0 HIGH issues before the 27A4 HIGH, and the 27A4 store is one slot late. From the
  sched/lreg dumps: sched2 breaks the lui tie by sched1 order, so the 27A4 HIGH must come first in sched1.
  But then local-alloc gives 27A4 a1 unless its sched1 life is no longer than 77E0's (equal priority, so qty
  order decides). The EE model issues one ALU insn per cycle, so the two HIGHs always have a memory-unit insn
  between them (the 53.0 f12 load or a store). The two stores issue next to each other: both kill a HIGH, so
  both rank first. So when 27A4 is first, its life is always one insn longer.
- Closed for pins: pinned full addresses (`register f32 *q asm("$4"); q = &D_002E27A4; *q = x;`, also 77E0 in
  $5, both, a pinned &D_002E2790) are dissolved (3w, output identical). Moving the y, 27A4 and 77E0 lines through
  every position pair gives 4w at best.

### 001c62a0 stays 16
- Same count, closer shape: `i++; b += 224;` (b's increment after i's) puts `addiu s4,s4,224` where the
  original has it (after slt, like a giv increment). Still 16w.
- Diagnosis from the -da dumps (base_m1 = s19 draft + that change): the remaining three-register permutation
  (orig base s1, b s4, &ent[0].lk t8; ours b s1, base t8, lk s4) is global-alloc order. Priority order is
  b (89) > lk0 (272) > base (104, the loop.c hoist of &D). Pass 0 of find_reg only reuses registers that are already
  in use, so the first two get s1/s4 and the last gets t8. The original needs base > b > lk0.
- The original's prologue says b is a reduced GIV of i, not a biv: its init `move s4,s1` copies the
  loop-hoisted base and sits among the giv inits (t4, t7, s4, t5). Ours is a user biv, whose init comes before
  the hoist, so the hoist copies b instead. In-loop forms `b = &D + i*224` (top of the body or at v, with
  0-6 rd1 wraps removed, or an int offset) are never reduced. b is computed as `t4 + base` each iteration:
  122-187w, size 1124-1144.
- d: cse1's use_related_value starts at the oldest related constant in the body, which is &D+240 (insn 52,
  ent[i].c0). That is why d = t6-160. Every way to write d = base+80 (user base, pinned base in s1, with
  or without the n reload through base) loses 2 insns (size 1140, 155-178w), and base folds back into the
  `lui/addiu` constant.
- Also tried, no gain: i = 0 before the guard (18; i then s1), for/while forms (18-25), declaration order (no
  effect), b pinned to s4 with these (20-23), &ent[0].lk pinned to t8 (16), b init placements.

### 00200e28 stays 24 (closed)
- Pins on top of the 24w draft: 832 in v1 31w, C[0] load in v1 35w (size +8), e[0] in a1 24w (dissolved).
  The same 832 pin on s11w59's 26w draft (whose leftovers are listed as local-alloc only): 27w. As in
  s18m2/s19m1, the leftovers are sched1 issue order inside the single flood block.

### Tools
- No new committed tools. In the scratchpad I used var20.py, which applies a dict of string-replacement variants
  and scores each with sc6_s12.py. Beware: it replaces the first match, so the header comment of a draft can
  swallow the replacement. Strip line 1 first. pos2.py puts two lines at every position pair.
