# Session 23 notes, worker s23m3 (large holdouts): no matches, no new best drafts

| function | mode | before | after | draft |
|---|---|---|---|---|
| 00110618 | hand | 93 (s12w6) | 93 | - |
| 0010d470 | hand, RO=48cdf0 | 170 natural (s14m) | 170 | - |
| 001636d0 | hand/nostrict | 400 (s18w) | 400 | - |

Counts are true DP LCS words (sc6_s12.py with ROOT patched to the worktree). All three baselines re-verified
first (93 / 170 / 400). Roughly 1.5 h of effort; none of the new angles moved a count, so these stay closed for
the levers below. The analyses are recorded so the next attempt does not repeat them.

### 00110618 stays 93
- Mode sweep: the 93w draft in every src/hand/* and src/sdk/* mode directory. Every 2.96 mode gives exactly 93
  (pure FP code: strict/nofill/gcse/si flags change nothing); n32 207, gcc991111 variants 191-213. Not a mode
  problem.
- clb6 statement-order climb from the 93w draft with annealing (TEMP=1.5, 20,000 iterations, seed 23): best
  stays 93. The s12w6 order is a local optimum of this move set.
- Small fact: the original rematerialises 1.0f six times (`lui 0x3f80; mtc1` next to each use: m2 shares one
  load for [3][2] and [2][3]); the 93w draft loads it seven times because its hill-climbed order separates
  m2[3][2] and m2[2][3] (one extra lui/mtc1 in the m2 block).

### 0010d470 stays 170
- Case 25 byte read: `{ u8 c3 = str[pos]; ... }` (block-local) gives the same 170 and the same registers as
  the shared c2: the byte still takes a1 and n<<4 a2 (orig n<<4 a1, byte a3, the 59E4 HIGH a2). So the a3 in
  the original cannot come from local-alloc of a block-local byte (local-alloc would take a1, as here); it
  needs a global byte pseudo (the shared c2) allocated after n<<4 has a1 and with a2 unavailable. This
  confirms the s13w4 global-priority reading.
- `code = (c << 8) + str[pos] + 0xE0` without c2: 171. `switch (str[pos])` without `c2 =` in cases 11, 13
  and 15 (one at a time and together): 170, 170, 172, 172; with the case 25 change: 172-173.
- Where the 52 extra words are (aligned diff): ours keeps case 24's whole PUT (0xd38-0xe04: the `+ 0.0f`
  path, the 59E4 != 0 path and the tail). The original keeps only the c == 0x20 path in case 24 and jumps
  into case 25's copies for the other two (`bne t0,v0` / `bnez v0` to case 25's labels): a jump2
  cross-jump, possible only when both copies use the same registers (n<<4 in a1).

### 001636d0 stays 400
- Original spill-slot layout: 352 an, 356 i, 360 flg, 364 j, 368 trow, 372 pp, 376 bn. This is the
  draft's declaration order (params, then locals), i.e. spill slots in regno order, so j and pp really are
  user pseudos that were spilled (not loop.c or reload temporaries).
- The j slot holds s6 (the i*64 offset register) and is stored in both arms of the `k == 0x3FF` if/else
  (0x128 in the then arm, in the jal delay slot at 0x194 in the else arm); case 1 reads it for
  x150[j].t / .a[0] / .r[0], the default case for x154[j].
- Tried, all byte-identical output (400): x150[j] instead of x150[i] in both arms; `j = i;` moved into each
  arm; both together; `u32 j`. cse1 and gcse cprop remove j whatever the placement. Under nostrict_nogcse
  the j store at 364 appears (417 with the 400w draft, `inarm` 415), but the entry changes: the original
  sets the `~0x02000000` mask (lui/ori a0) in each arm of the x20/x10 if/else and cross-jumps only the
  `addiu -4; lw; and; sw` tail, and it reloads `*o->mdl` (`lw a0,0(s4); lw v0,0(a0)`) after it. A
  nogcse re-tune of the entry is the one direction not explored yet; it would also explain the missing
  `(s2 & 3)` PRE share (s12w7). gcc 2.95.3's gcse_main skips the whole pass only for setjmp calls or
  <= 1 basic block (the 3.0 size limits need ~50 MB of bitmaps), so a skipped pass does not come from
  function size.
- pp: the original passes pp (not pos) to the call in all four arms (arm 1 `move a2,v1` with v1 = the pp
  value, arm 2 reloads 372, arms 3/4 a0 = the stored value). Passing pp in arms 1, 3, 4 (every subset):
  identical output (400). pp keeps REG_EQUIV sp+16; the stores need a set with no REG_EQUAL note.
- Default case: `sw s7,368(sp)` (trow) in both the original and ours; not a difference.

### Tools (scratch, not committed)
- varrun.py: base draft + a python dict of string-replacement variants (each old string once), scored with
  sc6 in a chosen mode directory (DST). Same job as var.py (s22) / var_s11.py.

## s23m3, second round: 001636d0 400 -> 394 (draft); 00110618 stays 93

| function | mode | before | after | draft |
|---|---|---|---|---|
| 001636d0 | hand/nostrict | 400 | **394** | s23m3__001636d0_394w_b2.c (size 4264 vs 4248) |
| 00110618 | hand | 93 | 93 | - |

### 001636d0: the no-gcse direction is ruled out; two small structural fixes
- Per-segment comparison (instructions between calls, LCS per segment; scratch segcmp.py): the
  nostrict_nogcse build is 6 words short at the entry and loses in the hit block (segment 0x644: 34 words
  off vs 8 with gcse). There the original keeps `addiu v1,sp,80` (&pm) in the `beq` delay slot and shares
  it across the if/else, which gcse PRE/cse gives and -fno-gcse loses. The TU is a gcse build. Entry
  variants under nogcse (a k/n temp for x20/x10, nested if, `==` first, `x = x & m`, literal mask, a
  pointer temp) give 414-419. None helps.
- The j slot is not a cprop problem. In the gcse build ours also has the j*64 copy (`move s3,s6` in the
  then arm), but it keeps s3 and `par` is spilled (to 372). The original has par in s3 (`addiu s3,...`
  for D_00573F10 / &D_00351E10[k]) and spills the j*64 copy to 364. It is a global-alloc priority swap
  between those two pseudos. Moving `j = i` (top of the body, after f, after s2, in each arm, first in
  each arm) gives the same output; the copy is folded at once. Replacing j by i in some uses changes the
  count (all uses: 372, but then there is no j slot at all, unlike the original), so j's uses stay.
- 400 -> 395: the hit block reads bn[2] through `IkBone *b2 = &bn[2];`. The original computes
  `addiu v0,bn,96` once and loads `32(v0)` twice; it also has the alignment nop after the `b` on the
  bc1f path, which this now reproduces. Size 4256 -> 4264: the nop is real, and the other +16 bytes
  are the known missing spill and alloc differences. `f32 *b2 = bn[2].u.t` gives 395 at size 4272;
  `(bn + 2)->` gives 400.
- 395 -> 394: inner case 2 copy loop with a block-local row counter `r` (column counter stays s0).
  Fresh r and c: 397. Fresh c only: 395.
- Biggest segments left (words off): entry 42 (par/j swap, then every s-reg and slot after it), the
  hit block 34, the case 2/3 bone search loop 24 (orig `beqzl` + rotated loop with k in a2, ours `beqz`
  + nop, k in a1), the inner copy loop 23 (orig k t0, count a3), the case 2/3 prologue 21.

### 00110618 stays 93: structural re-read
- No control flow (one block), and every value is f32. The spill set of the 93w draft is the original's
  exactly (px/py/pz 64-72, l 76, r 80, -r*n 84, r-l 88, 2n 92), apart from fb: the original loads fb
  (256(sp)) once into f24 and ours reads it three times. The 4-word size gap is those reloads.
  Parameter mapping (scrz, ax, ay, cx, cy, zmin, zmax, nearz, farz) follows libvu0 ViewScreenMatrix, and
  the 2.0f*scrz -> n+n, the shared fa-n/fb-n denominators and the CSE'd fb*n*-2/(fb-n) between m1 and m4
  are all present. Nothing structural is missing; it is FP register permutation only.
- The natural-order draft (w21, size-correct 1072) now measures 155. A clb6 anneal from it (TEMP=0.7,
  40,000 iterations, seed 7) reaches only 150. On the natural draft: sx2 = sxd shared 158 (size 1092),
  early fbn 173, both 153. The climbed 93w draft stays best.

### Tools (scratch, not committed)
- segcmp.py: splits the original and any number of builds at each `jal`/`jr` and prints words off per
  segment (LCS), to see which region a variant helps or hurts. segshow.py: those segments side by side.

## s23m3, third round: 0010d470 case 24/25 cross-jump (stays 170 natural / 129 probe)

- Source-level sharing over-merges. Each variant on the 170w natural draft:
  - case 24 ends `goto put;`, with the label before case 25's PUT: 220w, size 3856.
  - cases 24-31 merged as one case with an `if (c == 24)` head and one PUT: 219w, size 3864.
  - case 25-31 placed before case 24: 182w (orig-unmatched), size 4120.

  The original is 3968: case 24 keeps the code computation and its whole c == 0x20 path inline (0xce8-0xd6c,
  ending `b L290`). Only its `+ 0.0f` path (bne -> L258) and its D_004D59E4 != 0 path (bnez -> L2A0) jump into
  case 25's copy. A single shared PUT in the source cannot give that partial copy. It is jump2
  cross-jumping two complete, register-identical PUT copies (inside case 25, the c == 0x20 path is
  cross-jumped into the `+ 0.0f` tail at L280 the same way).
- The s14m 129w probe (s14m__0010d470_129w_finding.c) already reproduces 0xce8-0xeac (case 24 and case 25)
  word for word, with no source change to those cases: n<<4 = a1, byte = a3, 59E4 HIGH = a2 in case 25.
  So the 52 words are purely the allocation knock-on of the copy loop (the probe's `c2 = sub[k]` and the off
  biv). Its 119 words left are all in one segment (0x838-0xee0, the case 14 copy loop and the PUT tails
  around it), the loop.c giv split documented in s14m/s18w.
- Case 25 spellings on the natural draft, with no effect (170, registers unchanged: n<<4 a2, byte a1, HIGH a1):
  - `pos++` before `c -= 25`
  - `code = c2 + (c << 8) + 0xE0`
  - `((c << 8) | c2) + 0xE0`
  - `(c << 8) + (c2 + 0xE0)`
  - a `(u16)` cast

  Reading the byte as `str[pos + 1]` first gives 194.
- Not tried: PUT as a static inline. It changes x, w and n, so it needs pointer parameters, which put those
  locals in memory. And the probe already shows that the macro shape is enough once the registers are right.
