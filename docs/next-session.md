# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 14, 2026-10-19)

- **6,972 / 6,988 functions matched**: 99.77% of functions, 98.27% of code bytes (docs/progress.md). No new matches in session 14; 0010d470 went 179 -> 170 words (natural), 00110618 stays 93 (nonmatchings/session14/NOTES.md).
- **Shiftable build: M0, M1, M2 and the new M12 (code and data moved together) pass statically AND M1/M2 play in PCSX2** (docs/shiftable-plan.md "Session 14"; docs/workflow.md "Session 14").
  - Played in M1/M2: title, Load, Special Movie, New Game to Dive to the Heart, my save at End of the World, magic, world map (wm.x), gummi flight (gb.x), warp drive, Halloween Town, saving and reloading.
  - Fixed: tools/asm_export.py gave delay slots a fall-through edge, so a lui in a branch-likely delay slot made fake %lo relocations on struct loads (Halloween Town drew untextured in M1/M2). tools/shift/lo16_check.py now fails the build on that class of bug.
  - `SHIFT_DRAFTS=1` (m2/m12) links each near-miss C draft in place of its asm export (static diff). All 1,136 lone data-reloc rows reviewed.
  - Disc room: the minimal ELF leaves 1.9-6.4 KB in its disc slot. Options in docs/shiftable-plan.md; recommended: append the ELF at the end of the ISO (not written yet).
  - How to test: `make shift SHIFT_MODE=m1`, then `tools/shift/patch_iso.py MY.iso out/shift/m1/kh1-shift.elf KH1_M1.iso` (or `--in-place` on an existing copy) and boot the ISO in PCSX2. Test ISOs, my save card and the PCSX2 key map: docs/workflow.md "Session 14".
- **Phase 3 started**: docs/renderer-spec.md (two VU1 renderers, GS modes, per-frame flow, modern-API mapping) and tools/vu/ (find_vu1.py, gs_packets.py, vif_chain.py). Open: mesh file formats and per-mesh GS state (need a capture), triggers for P10/P19/P20, P21 rotation order.

## What is left (16 functions)

Best drafts in nonmatchings/session14/ and session13/ (newest), then older. LCS words.

1. **1-5 words**: 001fd858 (1, flagged reorg liveness), 001cfc28 (1), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 001f18e8 (2), 001eddc0 (2), 0021e120 (3), 00125240 (5 flagged; 8 natural).
2. **9-56 words**: 00265608 (9, SDK gcc991111), 00192958 (17), 00166570 (21), 00200e28 (24), 001c62a0 (56).
3. **Large**: 00110618 (93), 0010d470 (170 natural; 129 with an unnatural byte-offset probe: the sc address folding in loop.c is the blocker), 001636d0 (410).

## Session 15 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Runtime**: test M12 and an M2/M12 build with SHIFT_DRAFTS in PCSX2; reach a fight to test summons (xs_*.x) and a limit (xl_limit.x); visit Traverse Town and one more world.
2. **Disc room**: write `patch_iso.py --append` (ELF at the end of the ISO) and prove it boots, so the ELF can grow.
3. **Phase 3**: a runtime capture (PCSX2 GS dump) of one field and one character draw to close the renderer spec's open questions; start describing the model file formats.
4. **Matching (1 worker, only with a new angle)**: the 1-5 word group first.
5. End with `make progress-update SESSION=15`, commit, open a PR, and refresh this prompt.
