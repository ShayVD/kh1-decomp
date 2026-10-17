# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp (Kingdom Hearts PS2 matching decomp, target Kingdom Hearts
Final Mix, retail `SLPS_251.98`, SHA-256 1993a4da…). Read README.md and
everything in docs/ first; they are the only notes carried between sessions.
My own `SLPS_251.98` is in my Downloads folder (never commit it).

Where we stopped (end of session 5, 2026-10-16):
- 3,216 / 6,946 functions matched (46.3% of functions, 14.8% of code
  bytes), all byte-identical and objdiff 100% (docs/progress.md). Game
  segment 2,821 / 6,224; SDK 395 / 722.
- docs/workflow.md "Session 5": sigs.py does CFG liveness (jump tables,
  variadic functions, syscall stubs); new permute rules (integer
  dereferences, inline `sqrt.s` as `PlatSqrtf`, counter loops, void
  callees, early returns, 64-bit masks); the ternary bug in `usable()`;
  decomp-permuter matched 50 of the 172 drafts scoring ≤4.
- docs/structs.md: session 4's CompClass is the ppp effect system
  (include/ppp.h: `PppClass` table `D_00370200`, slots frame/draw/con/
  reset/des named from their callers; `PppEntry`). `Actor +0x98` is `pair`.
- docs/sdk.md "Session 5": SCE libraries are ee-gcc 2.9-991111; newlib is
  2.96 + `-fno-builtin` + no_fill (its assembler never filled delay
  slots). libm, libgcc, the syscall stubs and most of libc match; four
  one-word-off drafts are in nonmatchings/.

Session 6 (phase 2 continues):
1. Permuter: run `tools/permuter.py batch` on the drafts scoring 5-10
   (out/autodecomp/fail/), 5 minutes each; then the 138 drafts the ternary
   fix made scoreable.
2. Game hand work: the score 1-3 drafts the rules do not fix. Look for
   new repeating patterns and turn them into permute.py rules.
3. The ~150 functions m2c cannot type (`?`): try giving m2c the callee
   prototypes from sigs.py / functions.tsv, and the struct headers.
   The ~50 with `ldl/ldr`/`sdl/sdr` pairs: these are unaligned struct
   copies; write them by hand (`__builtin_memcpy` of a packed struct?).
4. SDK leftovers (docs/sdk.md): SCE libraries with 991111 by hand (start
   with libgraph and libpad2, which have names); libc's `_vfprintf_r`,
   `_dtoa_r`; the MMI string functions (decide inline asm vs `.s`).
5. End with `make progress-update SESSION=6`, commit, open a PR, and
   refresh this prompt.
