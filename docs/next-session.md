# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp (Kingdom Hearts PS2 matching decomp, target Kingdom Hearts
Final Mix, retail `SLPS_251.98`, SHA-256 1993a4da…). Read README.md and
everything in docs/ first; they are the only notes carried between sessions.
I will put my own `SLPS_251.98` in the repo root (never commit it).

Where we stopped (end of session 1, 2026-10-16):
- Session 1 (toolchain + skeleton) is complete. `make toolchain && make test`
  passes; `make check && make` passes against the pinned retail ELF.
- Compiler locked: ee-gcc 2.96-ee-001003-1, `-O2 -G0`, C. Confirmed by 8
  functions matching at objdiff 100% (src/anon/session1_probes.c).
- layout.tsv: 5,774 functions from the heuristic scan of 0x00100000-0x00272C70.
  Segments: game 0x00100000-0x0024F2E0 (5,204), sdk 0x0024F2E0-0x00272C70 (570).
- Progress: 8/5,774 functions (docs/progress.md).
- Known gaps: layout misses functions reached only by tail `j`; float literals
  in ee-gcc 2.96 can round one ULP off; rodata/jump tables emitted by sources
  land outside the image (kh1.ld), so switch statements and string literals
  need extern D_ symbols for now.
- GitHub: public repo ShayVD/kh1-decomp (check whether it was created and pushed).

Session 2 (phase 2 starts): decompile in bulk, smallest game functions first.
1. Write a tool to rank game-segment functions by size/complexity and list
   leaf functions; start with getters/setters and simple loops.
2. Add rodata support (place a source's .rodata at its original address) so
   switch tables and string literals can match; record it in docs/.
3. Identify and name SDK functions in the sdk segment (match known SCE 2.5.0
   signatures) to give game code real call targets.
4. End with `make progress-update`, commit, and refresh this prompt.
