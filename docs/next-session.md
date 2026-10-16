# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp (Kingdom Hearts PS2 matching decomp, target Kingdom Hearts
Final Mix, retail `SLPS_251.98`, SHA-256 1993a4da…). Read README.md and
everything in docs/ first; they are the only notes carried between sessions.
My own `SLPS_251.98` is in my Downloads folder (never commit it).

Where we stopped (end of session 4, 2026-10-16):
- 2,570 / 6,911 functions matched (37.2% of functions, 9.4% of code bytes),
  all byte-identical and objdiff 100% (docs/progress.md). The function count
  grew from 6,331 because `make layout` now ends a function at a tail call
  (580 functions had been glued to the one before them).
- docs/workflow.md "Session 4": two asm-export bugs fixed (`%hi` kept across
  calls, `rt` misread from `jal`/FPU instructions), which caused most
  session 3 near misses; `sp` stack locals (m2c's outgoing-argument area
  disabled, locals as `s32 sp[N]`); new permute rules (64-bit shifted
  constants, global arrays, store order taken from the original with
  rebased sub-struct stores, widened loads, returned arrays, volatile
  restarts).
- `tools/permuter.py` drives decomp-permuter (import / run / batch with
  verified acceptance). 5 of the 40 closest 61-150 instruction drafts
  matched in 2 minutes each.
- Structs (docs/structs.md): `Actor` has unions for its 64-bit words
  (+0x000, +0x160) and `+0x98` is `Actor *` (29 functions). New `CompClass`
  (include/compclass.h): ~224 component class records of 0x28 bytes, nine
  callback slots plus `s32 *offsets` at +0xC; 99 functions take it.
- SDK (docs/sdk.md): 0x0026AD60-0x00270AD4 is newlib libm (fdlibm), and
  0x00262F50-0x002634E0 is libgcc soft-float (fp-bit) plus the 64-bit
  divide family; 71 new names, including scePad2Read/GetState/GetButtonProfile.

Session 5 (phase 2 continues):
1. Rerun `tools/autodecomp.py batch --max-insns 100` (no --write) to
   regenerate out/autodecomp/fail/, then work the 91 drafts with score 1-3.
   The open patterns are listed at the end of "Session 4" in
   docs/workflow.md (jr-ra delay slot vs `%lo`-indexed loads, values kept
   in `s0`, inline `sqrt.s`, too few guessed arguments). Turn each one
   that repeats into a permute.py rule.
2. Run `tools/permuter.py batch` longer (5-10 minutes each) on the 471
   drafts scoring ≤8, and on the 61-150 instruction drafts scoring ≤8.
3. The 280 drafts gcc rejects: group the errors (pointer/int clashes,
   `invalid type argument of unary *`) and fix the common ones in
   permute.preprocess. Also 246 functions where m2c's output is unusable:
   find out why (jump tables? `M2C_ERROR`?).
4. Fix tools/sigs.py where it guesses too few arguments (`func_0021cb88`
   passes a 6th one in `t1`).
5. CompClass: work out what the nine slots do (look at who calls through
   them, and which slots are filled for which classes) and name them;
   find what `base` is. Name Actor fields where behaviour makes their
   meaning clear (position/velocity floats at 0x280-0x290?).
6. Start on the SDK segment (0/720): libm and the libgcc soft-float
   routines are plain C and should go through autodecomp the same way
   (`--segment sdk`); check their flags first (docs/toolchain.md: "Flags
   (SCE libraries): not checked yet").
7. End with `make progress-update SESSION=5`, commit, open a PR, and
   refresh this prompt.
