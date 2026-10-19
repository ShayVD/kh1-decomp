# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 12, 2026-10-19)

- **6,972 / 6,988 functions matched**: 99.77% of functions, 98.27% of code bytes. All are byte-identical and objdiff 100% (docs/progress.md).
  - Game: 6,251 / 6,266. SDK: 721 / 722.
- Session 12 matched 10 with 19 workers, at most 3 at a time (docs/workflow.md "Resource limit"): 001db718, 00216890, 001137f8, 0024c950, 001ba520, 001f94f0, 00208458, 001e1c20 (natural); 0019f1f0, 00120cf8 (flagged). Brief: nonmatchings/session12/BRIEF.md; every finding: nonmatchings/session12/NOTES.md; short version: docs/matching-tips.md "Session 12 tips".
- **Flagged matches count** (user decision in session 12). Each keeps a comment naming its trick; docs/workflow.md "Session 12" lists them.
- Main levers this session: register-allocator analysis. tools/matching/la4_s12.py (GPR, handles mult/div) / la3f_s12.py (FP) simulate local-alloc exactly from a .lreg dump; osrch_s12.py finds the minimal sched1-order change that reaches a target allocation. Then: base-pointer local set first (wins sched1 LUID ties), invariant written at its use inside a loop (hoisted to the end of the preheader), a variable set twice is never local-alloc'd, temps made function-level leave local-alloc, the 3-qty hand-sort bug, header constants in u64 variables (li order), array index instead of pointer local (spill-slot order). gdb tracers in tools/matching/gdb_s12/.
- `make rank` status `asm` means "no C placed", not "in src/asm"; session 11's list missed 3 never-drafted functions (all three now matched). For the true list compare layout.tsv with out/gen/placements.tsv.
- **docs/shiftable-plan.md**: plan for a relinkable build that boots in PCSX2 (the road to the Vita port). Milestones M0 (symbolic relink at original addresses, byte-identical), M1 (code moved), M2 (data moved) are testable in the container; booting is on my machine. Main risk: the title-screen/movie overlays (dktitle.x, dkmovie.x) may call the main ELF by absolute address.

## What is left (16 functions)

Best drafts are in nonmatchings/session12/ (newest), then session11/10/9/8/7. Counts are LCS words (true LCS for the large ones).

1. **1-5 words**: 001cfc28 (1, sched2 LUID tie: li.s has no in-block predecessor), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 001f18e8 (2, flagged), 001eddc0 (2, flagged), 0021e120 (3), 00125240 (5 flagged; 8 natural with every GPR right).
2. **9-56 words**: 00265608 (9, SDK gcc991111), 00192958 (17, reload spill rotation), 00166570 (21, gcse PRE of call-arg addresses), 00200e28 (24), 001c62a0 (56).
3. **Large**: 00110618 (93), 001fd858 (112), 0010d470 (179), 001636d0 (410, registers/spill slots only).

## Session 13 plan (two tracks, at most 3 workers)

1. **Matching (1 worker at a time)**: closest first with the session-12 allocator tools; then the large ones section by section.
2. **Shiftable build (2 workers)**, following docs/shiftable-plan.md: step 1 (`asm_export.py --symbolic`, the patch-in-place build must stay byte-identical), steps 2-3 (asm export of the unmatched functions into src/shift/, alias table, no PROVIDE fallback inside the image), steps 6-7 (`kh1-shift.ld`, ELF writer, `make shift`) to reach **M0**. Keep the shift build separate from `make`; never commit game data (the data blob is extracted from my ELF at build time into out/).
3. If time allows, the `scan-overlay` tool so I can check dktitle.x / dkmovie.x from my own disc.
4. End with `make progress-update SESSION=13`, commit, open a PR, and refresh this prompt.
