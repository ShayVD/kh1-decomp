# Session 23 notes (matching track)

Three workers (s23m1 small four, s23m2 001c62a0 + 00200e28, s23m3 large three). **No new matches**:
6,979 / 6,988 still. Detail per worker in NOTES-s23m1.md, NOTES-s23m2.md, NOTES-s23m3.md.

| function | before | after | best draft |
|---|---|---|---|
| 00265608 sceGsDefDispEnv | 4 | 4 (closed: sched2 trap_if dependence) | session21/s21m1__00265608_4w_pins.c |
| 001f2630 | 1 | 1 | session11/w32__001f2630_1w.c |
| 001f1fc8 | 2 | 2 | session11/w32__001f1fc8_2w.c |
| 001fd858 | 1 flagged / 25 | not attempted (no new angle) | session13/s13w3__001fd858_1w_flagged.c |
| 001c62a0 | 15 | 15 (new 35w shape fixes the cse1/loop half) | session22/s22m1__001c62a0_15w_cbody.c |
| 00200e28 | 24 | 24 (natural-type draft climbed 38 -> 25) | session12/s12w14__00200e28_24w_tlcs.c |
| 00110618 | 93 | 93 (FP register permutation only) | session12/s12w6__00110618_93w_tlcs.c |
| 0010d470 | 170 natural | 170 | session12 / s14m probe 129 |
| 001636d0 | 400 | **394** | session23-match/s23m3__001636d0_394w_b2.c |

shift/drafts.tsv still points 001636d0 at the 400w draft (left to the float thread); the new row would be
`func_001636d0	nonmatchings/session23-match/s23m3__001636d0_394w_b2.c	src/hand/nostrict/	394`.

## Findings worth keeping
- 001636d0 is a gcse build (the shared `&pm` in a beq delay slot only appears with gcse); no-gcse gives
  414-419. Spill slots 352-376 follow declaration order (an, i, flg, j, trow, pp, bn). `IkBone *b2 =
  &bn[2];` in the hit block (-5) and a block-local row counter in the inner case-2 copy loop (-1).
- 001c62a0: cse1 writes c as reg103-240 and folds d = c+80 into 103-160; that is 103's last use, so
  force_movables hoists it and reload rematerialises lui/addiu. The 35w draft (c = &D before e, `while
  (i < c->n)`, `i = 0;` first) keeps d in the loop with the right prologue and size 1148, but every other
  &D+X then hangs off c. Six two-step combinations with s22's self-copy: 35-160.
- 00200e28: all 24 words are in the packet header and first vertex (~14 sched, ~10 knock-on regalloc);
  C[k] really is reloaded at every use (locals: 205-335).
- 0010d470: the case 24/25 PUT cross-jump is jump2 merging two complete copies with identical registers;
  sharing PUT in source over-merges (219-220w). The s14m probe already reproduces cases 24/25.
- 00265608: gcc991111's sched2 trace goes to the `-dR` dump file (x.c.sched2), not stderr. Plain
  `ee-gcc2.9-991111` from decomp.me = same 4w as 991111a/-01; 990721 gives 18.
