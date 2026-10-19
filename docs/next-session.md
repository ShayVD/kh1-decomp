# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 15, 2026-10-19)

- **6,972 / 6,988 functions matched**: 99.77% of functions, 98.27% of code bytes (docs/progress.md). No new matches in session 15; 00125240 went 5 -> 3 words flagged, right size (nonmatchings/session15/NOTES.md). Closed: other ee-gcc builds, -g variants, ~30 more flags.
- **Shiftable build plays in PCSX2 in M1, M2, M12, M12 with SHIFT_DRAFTS, and a 3.93 MB M12 booted from an appended ELF** (docs/shiftable-plan.md "Session 15").
  - Played in session 15: save loading, area changes, world map, warp drive, Agrabah fights, summons (Simba in M12, Genie in the drafts build), game over and Continue, Halloween Town. Shay judged that enough; Trinity Limit skipped. Traverse Town not reached (world-map cursor route unknown).
  - **Disc room solved**: `tools/shift/patch_iso.py --append` writes the ELF after the end of the volume (ISO 9660 record + PVD size, UDF anchor copied, retail slot zeroed). `make shift SHIFT_MODE=m12 SHIFT_DATA_SHIFT=0x21000` builds a test ELF 128 KB over the old slot; it boots.
  - How to test: `make shift SHIFT_MODE=m12`, then `tools/shift/patch_iso.py MY.iso out/shift/m12/kh1-shift.elf KH1_BIG.iso --append` (add `--in-place` on an existing copy) and boot it in PCSX2. Test ISOs, save card, keys and PCSX2 quirks: docs/workflow.md "Session 14" and "Session 15".
- **Phase 3**: tools/vu/gsdump.py summarises a PCSX2 GS dump (GIF formats, GS state per draw, uploads, display registers); findings in docs/renderer-spec.md. Still open: the mesh file formats (VIF data is not in a GS dump: needs a VIF/DMA capture or a breakpoint at func_00108d90 / func_0015ff78), P10/P19/P20 triggers, P21 rotation order.

## What is left (16 functions)

Best drafts in nonmatchings/session15/, session14/ and session13/ (newest), then older. LCS words.

1. **1-5 words**: 001fd858 (1, flagged reorg liveness), 001cfc28 (1), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 001f18e8 (2), 001eddc0 (2), 0021e120 (3), 00125240 (3 flagged, right size; 8 natural).
2. **9-56 words**: 00265608 (9, SDK gcc991111), 00192958 (17), 00166570 (21), 00200e28 (24), 001c62a0 (56).
3. **Large**: 00110618 (93), 0010d470 (170 natural; 129 with an unnatural byte-offset probe), 001636d0 (410).

## Session 16 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Phase 4 (shiftable cleanup) begins**: the build no longer depends on the original layout at runtime, and the disc slot is gone. Start replacing absolute-address idioms in gameplay C (D_XXXXXXXX externs for tables that only one module uses become real definitions in C; first one source file end to end, then a plan for the rest) without breaking `make` (the matching build stays byte-identical).
2. **Phase 3**: capture the VIF side of one field mesh and one character mesh (PCSX2 debugger breakpoint, or a memory dump at the DMA kick) and describe the model file headers in docs/structs.md; close the renderer spec's open questions with the GS dump findings.
3. **Matching (1 worker, only with a new angle)**: the 9-56 word group (00192958, 00166570, 00200e28).
4. Runtime: only for new shiftable changes (Traverse Town if the map route is found).
5. End with `make progress-update SESSION=16`, commit, open a PR, and refresh this prompt.
