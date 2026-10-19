# Session 15 notes (matching track)

## s15m1: 1-5 word group (001fd858, 001cfc28, 001f2630, 001f1fc8, 001f18e8, 001eddc0, 0021e120, 00125240)

No matches. One improvement: 00125240 5w (flagged, wrong size 184) -> 3w (flagged, right size 180),
nonmatchings/session15/func_00125240.c. Counts are true DP LCS words (tools/matching/sc6_s12.py).
Work was done in a scratch git worktree (since removed).

Baselines re-verified: 001fd858 1w (s13w3 flagged), 001cfc28 1w (s11 w6), 001f2630 1w (s11 w32, nofill),
001f1fc8 2w (s11 w32, nofill, RO=00490a80), 001f18e8 2w (s11 w52, nofill), 001eddc0 2w (s11 w64),
0021e120 3w (s11 w61, nostrict), 00125240 5w flagged / 8w natural (s12w3 / s12w17).

### Angle 1: other compilers on the best drafts (closed)
- ee-gcc2.9-991111a and 991111-01 on all 9 drafts (same mode flags): 001fd858 320w, 001cfc28 39w,
  001f2630 183w, 001f1fc8 198w, 001f18e8 242w, 0021e120 171w, 00125240 18-25w; 001eddc0 does not link
  (991111 calls `fptoui` for the u32 conversion; 2.96 inlines the fixuns diamond, so the original is 2.96).
  The game code here is not a 991111 build.

### Angle 2: flags not in the session 7/13 sweeps (closed)
- cc1 `-g`, `-g1`, `-g2`, `-g3`, `-ggdb`, `-gstabs` (stabs really emitted): byte-identical code on all 9 drafts.
  So "nofill = built with -g" (s10) costs nothing at the C level: -g only changes the assembler.
- No gain (equal or worse on all 9): -ffast-math, -ffloat-store, -fno-common, -fpcc-struct-return,
  -freg-struct-return, -membedded-data, -mmemcpy, -msingle-float, -mips3, -mips4,
  -fno-omit-frame-pointer, -fno-math-errno, -finline-functions, -fbranch-probabilities, -mno-check-zero-division,
  -mcheck-range-division, -Os, -fno-builtin, -mno-mips-tfile, -mmad, -mno-mad, -fvolatile, -fshort-enums,
  -fno-peephole2, -mabi=eabi, -mlong64, -mint64, -mfp64, -mfp32, -fsingle-precision-constant.
  (-mfused-madd, -mno-branch-likely, -fno-guess-branch-probability, -fno-trapping-math, -fno-alias-check:
  rejected by this cc1; -mgp32 ICEs on all but 001eddc0.) Helper: tools/matching/sweepcc_s15.py.

### 00125240: 5w -> 3w flagged (right size)
- Random search (tools/matching/srch125_s15.py: statement order of the 9 stores after `p->x = 0.0f` x
  position x form of one dead no-else FP test; ~30k compiles over 8 seeds and 10 test forms; all floors are 3w) on the s12w17 natural body.
  Best: `p->x = 0; p->w = 1; 2790.w = 1; 27A4 = p->x; 2790.x = p->x; p->y = -1e4; 2790.y = p->x;
  p->z = 1e4; 2790.z = p->x; if (p[-1].w < p[-1].x) y = 0; D_004F77E0 = p->x;` (also 3w with
  `p[-1].y < p[-1].x`). x becomes global (used after the split) so all FP regs match (1e4 f0, x f1, -1e4 f2,
  1.0 f3) and, unlike s12w3, the two 1.0 stores share one pseudo (no mov.s, size 180).
- Left (3 words): the D_004F77E0 HIGH is local to the post-test block, where p is dead, so it takes v0 and
  issues after the p->w store (anti dep on v0); the original has lui a1 at 0x38 and stores 77E0 at 0x60 with
  2790.z in the jal slot. The original allocation p v0, 2790 v1, 27A4 a0, 77E0 a1 is birth order with all
  four HIGHs local to one block (as in the natural 8w draft), so the split must not make any base global.
- Tried, worse: 77E0 store before the test with 2790.z (7w, 2790 base global loses v1 to the 77E0 HIGH),
  2790.x/y/z or p->w after the test (7w), `f32 *q = &D_004F77E0` early + `*q = x` after (full address
  hoisted, 184 bytes), tests that read D_004F77E0 (gcse hoists the whole lui+addiu address: 15-65w),
  `(f32)*(s32 *)&D_004F77E0` test (15w), arms reading x or 77E0 (`y = p->x`, `y = D_004F77E0`, else arms:
  11-21w), inline `vset(V4f *, x, y, z, w)` helpers (9-21w). On the natural s12w17 order a test at the end
  whose arm reads x (`y = x`, else `y = x`, `y = x + 1.0f`) keeps every GPR right (77E0 HIGH a1) but x stays
  local (8-9w): life1 deletes the dead arm set, so only a real use of x after the split makes x global.

### 001cfc28 (stays 1w)
- `f32 one = 1.0f;` before the call or before `if (r->x4)`: update_equiv_regs moves the li.s next to the
  swc1 (insn 226 before 181 in .lreg) but the 1.0 store is still sched1's first store, so LUID order is
  unchanged and the regs swap (7w).
- Dead no-else FP test as a sched1-only split (flow2 deletes it before sched2, so sched2 sees one block and
  ties go to sched1 order): val before and v[3] after the test, all 2^5 placements of x/type/v0/v1/v2 x 4
  test forms (128 variants, without the identical arms, which would make 11 blocks): best 11w. With v0 before
  the test the 1.0 and c*2 pseudos are in different sched1 blocks, both get f0 and the li.s is serialised
  after swc1 f0; with v0 after, c and b become global and s1/s2 swap (15w+). Climb over all 8 body
  statements + test position + 4 forms (tools/matching/pclimb_s15.py): best 4w (dsll still after li.s).

### 001f2630 (stays 1w)
- `*(volatile s32 *)&` on x14 and x2c with x14 moved next to x2c (x2c's li LUID kept): exact store order,
  but 0x8000/f4/22/f4+288 take t0/a3/a2/a1 instead of a1/t0/a3/a2 (9w), the same rotation as s11's k8
  shape; all-volatile Pg in the original store order 46w (size 1064).

### 0021e120 (stays 3w)
- A separate `Vx *v = (Vx *)(p + 14)` (or buf + 16) instead of `p += 14` (to change the spurious same-base
  output deps between header and Vx stores): 96w (global-alloc moves everything). `v = (Vx *)p` after
  `p += 14`: unchanged 3w.
- Dead no-else FP test (`if (o->sx < o->sy) X = 0;`) inside the header store block: 57-83w at any position
  (the split makes header constants global); a 400-step climb with it found nothing below 3.

### 001fd858 (stays 1w), reasoning only
- In resource.c, find_basic_block returns -1 (all regs live) when the previous BARRIER is more than
  MAX_DELAY_SLOT_LIVE_SEARCH non-note insns back; the fall-through block at 0x5e0-0x654 has ~26 RTL insns,
  under the limit. But even with all regs live, method 2 (find_dead_or_set_registers) still kills v0 at the
  fe408 call two unconditional jumps later (it gives up only after jump_count >= 10, conditional jumps
  cost 5), and the two methods are ANDed. So both a longer block AND >= 2 conditional branches on the
  path before the call would be needed; the final code has neither. Not pursued further.

### 001f1fc8, 001f18e8, 001eddc0
- Only the compiler/flag sweeps above; no new source angle found that the s11-s13 notes had not covered
  (1fc8: constant hoisting family; 18e8: li 63/li 1 sched2 LUID; eddc0: fix scratch v0 vs dbr).

### Facts
- -g does not change ee-gcc 2.96 code generation (all 9 drafts byte-identical).
- 991111 compilers call `fptoui` for float -> u32; 2.96 inlines the c.le.s/trunc diamond.
- A dead no-else FP test whose arm sits right before only the last store makes every value stored after it
  global; for 00125240 that is the cheapest way to make the x pseudo global without splitting the 1.0 pseudo.
- update_equiv_regs places a moved REG_EQUIV constant immediately before its use in the post-sched1 insn
  stream, so it only helps a sched2 LUID tie if the use itself is late in sched1 order.

### Tools (new, tools/matching/)
- lro7_s15.py: lro6_s12 with $KH1_ROOT (default: the repo containing it), $CCOVR (compiler id), $XFL
  (extra cc1 flags).
- vrun_s15.py ADDR MODE RO FILE...: score files (copies them into src/MODE as dot files).
- sweepcc_s15.py LIST [compilers] [flags]: drafts x compilers x extra flags.
- srch125_s15.py SEED N "TEST|TEST": the 00125240 random search (HDR=header file with the types/externs).
- pclimb_s15.py FILE ADDR MODE RO SEED N "TEST|...": random climb of one-statement-per-line order between
  /*P*/ and /*Q*/ markers (def-before-use kept), plus an optional inserted test line.
  All run in-process (~0.02-0.05 s per compile); set WDIR to a scratch dir.
