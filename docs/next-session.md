# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp (Kingdom Hearts PS2 matching decomp, target Kingdom Hearts
Final Mix, retail `SLPS_251.98`, SHA-256 1993a4da…). Read README.md and
everything in docs/ first; they are the only notes carried between sessions.
My own `SLPS_251.98` is in my Downloads folder (never commit it).

Where we stopped (end of session 3, 2026-10-16):
- 1,793 / 6,331 functions matched (28.3% of functions, 6.1% of code bytes),
  all byte-identical and objdiff 100% (docs/progress.md).
- autodecomp (docs/workflow.md, "Session 3") now feeds m2c EABI register
  names and guessed prototypes (`tools/sigs.py`, out/sigs.h), fixes
  constants/float literals/dropped parameters, then runs a greedy
  permutation search (`tools/permute.py`: volatile, store rotation and
  reordering, signedness, casts, temps, if-return). m2c runs in-process; a
  pass over everything ≤100 instructions takes ~8 minutes on 4 cores.
  Closest failing drafts land in out/autodecomp/fail/ (regenerate with a
  batch run; out/ is not committed).
- `try func_X --diff` shows original vs ours; `try func_X --file my.c`
  tests a hand candidate. Hand matches go in src/hand/.
- Structs: `tools/structs.py` groups functions by a0 passed through calls;
  `Actor` (include/actor.h, 90 fields by offset, docs/structs.md) is used
  by 23 matched functions.
- SDK: 149 names in functions.tsv; session 3 added newlib libc (memcpy,
  strlen, printf, malloc, rand…), scePrintf, libpad2/libvib/libpc/libipu
  basics (docs/sdk.md lists what is still unnamed).
- Progress history now has a session column: `make progress-update SESSION=4`.

Session 4 (phase 2 continues):
1. Rerun `tools/autodecomp.py batch --max-insns 100` (no --write) to
   regenerate the fail drafts, then hand-match the score 1-3 queue
   (~150). Turn every pattern that repeats into a permute.py rule (the
   open ones are listed at the end of "Session 3" in docs/workflow.md:
   dropped store offsets on struct-returning calls, lost delay-slot
   returns after calls, 64-bit narrowing casts).
2. Teach autodecomp the `sp` struct-copy case (m2c `--stack-structs`, or a
   local struct declared in the draft): it is the largest group of the 580
   compile errors.
3. Try decomp-permuter (simonlindholm/decomp-permuter) on the 61-150
   instruction near misses; it supports ee-gcc via a compile script.
4. Grow `Actor`: union for the 64-bit flags at +0x160/+0x164, follow the
   `+0x98` pointer (same struct), and name fields where behaviour makes
   their meaning clear. Recover a second struct (the `arg0 + *(arg1+0xC)`
   component family around 0x00190000-0x001A5000 is a good candidate).
5. Identify the block 0x0026AD60-0x00270B40 between libcdvd and libmc, and
   the remaining libpad2 functions.
6. End with `make progress-update SESSION=4`, commit, open a PR, and
   refresh this prompt.
