# Session 23 notes, worker s23m1 (small four: 00265608, 001f2630, 001f1fc8, 001fd858)

No matches, no better drafts. Counts are true DP LCS words (sc6_s12.py copy with ROOT patched to the
worktree, plus CCX=<ee-gcc path> to override the compiler, MODEREL=<mode dir>/x.c for the flags and FN=
for sceGsDefDispEnv). Best drafts are unchanged and drafts.tsv needs no edit.

| function | mode | before | after | best draft (unchanged) |
|---|---|---|---|---|
| 00265608 sceGsDefDispEnv | sdk/gcc991111 | 4 | 4 | session21/s21m1__00265608_4w_pins.c |
| 001f2630 | hand/nofill | 1 | 1 | session11/w32__001f2630_1w.c |
| 001f1fc8 | hand/nofill, RO=00490a80 | 2 | 2 | session11/w32__001f1fc8_2w.c |
| 001fd858 | hand/nostrict | 1 flagged / 25 natural | same | session13/s13w3__001fd858_1w_flagged.c |

## New compiler checked: plain ee-gcc 2.9-ee-991111 (closed)
- decomp.me also ships `ee-gcc2.9-991111.tar.xz` (not in tools/toolchains.tsv; `991111b`, 2.95.x and dtls
  builds return 404). Its cc1 differs from 991111a's and 991111-01's (four distinct cc1s with 990721).
- sceGsDefDispEnv with it: 4w, the same output as 991111a and 991111-01. 990721: 18w (size 876).
  So no installed or downloadable compiler changes the sched2 order there.

## 00265608: what the original's sched2 must have seen (reasoning from -fsched-verbose-5)
- gcc991111 writes the sched2 trace into the `-dR` dump file (`x.c.sched2`), sched1's to stderr.
- h2==2, h0!=1 block (ours): t=1 `w+2559` (338, alu) + trap_if (342, unit none); t=2 div (339) + lw off[0]
  (346, prio 10); t=3 lw off[1] (380) + H addiu (331, prio 7). Both loads depend on the trap only (TRAP_IF
  flushes the pending memory lists, so every later memory ref depends on it, cost 1).
- The original's asm order (trap, div, addiu a3, lw, dsll32, lw) means the trap was still at t=1 and the div
  at t=2 (an RTL trap after the div would print after it), so at t=2 the loads were not ready. They needed a
  dependence on an insn issued at t=2 (the div or the addiu) or a cost-2 dependence on the trap. Register deps
  are fixed now that every register matches, and no store sits in the block, so nothing in C supplies it.
  Moving the loads RTL-before the trap makes them ready at t=1 (they would issue before the div). Closed.

## 001f2630 / 001f1fc8: climbs with per-store volatile (closed)
- New climber (scratch vclimb.py): random moves of the statements between /*P*/ and /*Q*/ (def-before-use kept)
  combined with toggling `*(volatile __typeof__(g->f) *)&g->f = v;` on each store. 001f2630: 2500 steps,
  plateau at 1 (never 0). 001f1fc8 (RO=00490a80): 3000 steps, plateau at 2. One volatile store alone changes
  nothing (volatile orders only against other volatiles).
- 001f2630 with 0x8000 pinned (`register s32 k8 asm("$5"); k8 = 0x8000; g->x2c = k8;`) inside the block,
  climbed with order + volatile (4000 steps): 22 -> 3, no better than the 1w draft.
- Position sweep of a volatile x2c store over the block: 1w at best (positions 6-9), as s15 found.

## 001fd858
- Re-read only; no new angle beyond s13w4/s15/s21 (reorg's annul decision needs v0 live on the fallthrough,
  and the final code has no v0 reader before the fe408 call). Not attempted.

## Verdict
All four are stuck on a pass (sched2 dependence graph, sched1/local-alloc coupling of the store floods,
reorg liveness) with the final registers already right. I found no C-level lever and none of the
downloadable compilers differs. Further time on them is unlikely to pay off unless a new compiler build
or a new class of source trick appears.
