# Session 21 notes (matching track)

## s21m1: 00265608 sceGsDefDispEnv 7 -> 4w; 001fd858 stays 1w (no matches)

| function | mode | before | after | draft |
|---|---|---|---|---|
| 00265608 | sdk/gcc991111 | 7 (s18m2) | **4** | s21m1__00265608_4w_pins.c (drafts.tsv updated) |
| 001fd858 | hand/nostrict | 1 flagged / 25 natural (s13w3) | 1 / 25 | - |

Counts are true DP LCS words (sc6_s12.py with a FN override, since the function is named sceGsDefDispEnv).

### 00265608: 7 -> 4 (OR order fixed by two more pins)
- In both h0!=1 blocks the display value is written as statements in the original's pairing,
  `XH = X | HH; MW = M | W; disp->display = (MW | XH) | Y;`, with `M = (u64)(magh-1) << 23` pinned to v0
  (`register u64 M asm("$2")`) and `X = (u64)((ox + dx*magh) & 0xfff)` pinned to a1 (HH stays in a3).
  Every OR (or a1,a1,a3 / or v0,v0,a0 / or v0,v0,a1 / or v0,v0,v1) now matches. All 64 subsets of pins on
  M, X, W, Y, XH, MW: 48 give 4, none below; without pins the tree gives 19 (combine re-pairs it).
- 600 random statement orders x 4 pin sets: floor 4.
- Left (2 words in each block): `addiu a3,s2,-1` / `dsll32 a3,a3,0xc` issue after the two off[] loads instead
  of right after the div. sched2 (-fsched-verbose-5 dump): t=1 w+2559 and the trap_if; t=2 the div and lw a1.
  The loads anti-depend on the trap (ready t=2) and have priority 10 and 9 against 7 for the addiu. With the
  original's OR tree, X's chain (lw, daddiu, daddu, andi) is always 3 longer than H's (addiu, dsll32) into the
  same OR, so priority cannot flip it; the original needs the loads not ready at t=2 (a dependence on the div
  or on the addiu). Since the final registers and insns are now the original's, the sched2 dependence graph is
  fixed; nothing in plain C found changes it.
- Tried without effect (all 4): volatile reads of off[0]/off[1]; pinning the off[0] load or ox to a1/v1/a2/a0
  (dissolved copies); every gcc991111 mode (_01, nf, as296); -fsched-spec-load, -fno-sched-interblock.
  Worse: -mcpu= r4000/r4600/r5000/r8000/orion/r4100/r4300 (43-56), -fno-schedule-insns (104), an empty
  `__asm__ volatile("")` at three positions (6-39; not acceptable anyway).

### 001fd858: stays 1w (flagged) / 25w (natural)
- The pin lever does not apply: the last word is reorg's annul decision (bnezl at 0x654), which needs v0 in
  opposite_needed. find_dead_or_set_registers walks the fallthrough `b L170 -> b done -> jal fe408` and the
  call kills v0; a pin cannot add a v0 reader without emitting code.
- A v0 reader via `{ register s32 vz asm("$2"); __asm__("" : : "r"(vz)); }` after `o->d0 = max;` (either copy
  or both) breaks the function (size 2056, 281-300w), so even the hint form does not work.
- Read of the dbr dump (scratch only): the merged tail at 0x668 (`bnez v0,done`) is shared by the d6<0 and
  d6>0 smoothing paths (each predecessor keeps its own slt v0 in a slot: 0x5dc and 0x658), and the dead
  nops at 0x5d4/0x664 are where those slts stood. Same in ours. Closed unless the original's reorg saw a
  different fallthrough path (s13w4/s15 analysis stands).

### Tools (scratch, not committed)
- A copy of lro6_s12/sc6_s12 that takes the mode from MODEREL=src/<mode>/x.c, the function name from FN and
  extra cc1 flags from EXTRA, so drafts can be scored in any mode without placing them under src/.
