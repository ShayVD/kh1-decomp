# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp (Kingdom Hearts PS2 matching decomp, target Kingdom Hearts
Final Mix, retail `SLPS_251.98`, SHA-256 1993a4da…). Read README.md and
everything in docs/ first; they are the only notes carried between sessions.
My own `SLPS_251.98` is in my Downloads folder (never commit it).

Where we stopped (end of session 2, 2026-10-16):
- 1,254 / 6,331 functions matched (19.8% of functions, 3.2% of code bytes),
  all byte-identical and objdiff 100% (docs/progress.md).
- Tools (docs/workflow.md): `make rank` ranks functions by difficulty;
  `kh1tool.py asm`/`m2c` print a function's asm / m2c draft;
  `tools/autodecomp.py batch` matches m2c output in bulk and writes
  src/auto/text_XXXX0000*.c (provisional files grouped by address, using
  `M2C_FIELD`/`M2C_UNK` placeholders from include/m2c.h).
- Rodata works: each function's strings, constants and jump tables are placed
  at the original address, inferred from its %hi/%lo pairs. Switches and
  string literals can be written naturally.
- layout.tsv is now 6,331 functions (switch case labels no longer counted;
  syscall stubs and code after a final `jr ra` split out).
- SDK: 110 functions named in functions.tsv with evidence (syscall stubs,
  sceGs*/sceDbc* error strings, sceCd*, sceMcInit, sceSif*Rpc); docs/sdk.md.
- Open question: game code calls 0x00F20000, outside the ELF (runtime-loaded
  module); see docs/elf-notes.md.

Session 3 (phase 2 continues):
1. Hand-match the near misses: rerun `tools/autodecomp.py batch --max-insns 60`
   without --write to get the report, then fix the 1-3-word mismatches and
   the gcc compile errors (pointer/int clashes in m2c output) first.
2. Teach autodecomp a few automatic permutations (swap declaration order,
   s32 vs u32, `void` vs value returns) and rerun on everything ≤100 insns.
3. Start recovering structs: pick the most-used M2C_FIELD base (e.g. the
   object/actor struct) and replace offsets with named fields in
   include/, keeping every match.
4. Name more SDK functions (libpad2, libvib, libpc, libipu, libc string
   functions) and the libkernl printf (`func_00259cc0`, probably scePrintf).
5. End with `make progress-update`, commit, open a PR, and refresh this prompt.
