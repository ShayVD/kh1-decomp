# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 13, 2026-10-19)

- **6,972 / 6,988 functions matched**: 99.77% of functions, 98.27% of code bytes (docs/progress.md). Game 6,251 / 6,266, SDK 721 / 722. No new matches in session 13 (4 matching workers, one at a time).
- **Shiftable build: M0, M1 and M2 pass statically** (docs/shiftable-plan.md, the three "Session 13" sections; docs/workflow.md "Session 13").
  - `make shift` links a fresh ELF (no patching, no PROVIDE inside the image) from our objects, symbolic asm, `shift/unmatched/*.s` (the 16 unmatched functions, symbolic asm, not counted), `shift/aliases.ld` and the data blob cut from my ELF into out/ at build time. M0 is byte-identical except 2 words of the `KH1_SHIFTABLE` func_00171078 variant (`SHIFT_VARIANTS=0` for strict).
  - `make shift SHIFT_MODE=m1` rotates all code; `m2` moves data and bss by 0x1000. tools/shift/shift_cmp.py (inverse-map comparator) passes both.
  - `data_relocs.tsv` (addresses and names only): 9,330 accepted pointers, DMA chains walked, 0 ambiguous words left; reviewed overrides in tools/shift/data_reloc_overrides.tsv. Not reviewed one by one: 649 lone function-start words and 423 string pointers.
  - tools/shift/scan_overlay.py FILE.x lists an overlay's references into the main ELF.
- **Runtime (PCSX2 on my Mac, 2026-10-19)**: M0, M1 and M2 all boot to the title screen and, through New Game and the opening movie, to the Station of Awakening. M1/M2 needed load-time overlay fixups (tools/shift/overlay_relocs.py, shift/ovl_fixup.c, proof in tools/shift/ovl_proof.py): the 12 disc overlays call the main ELF by absolute address, 7,658 fields patched on load, 67 ambiguous ones left alone (out/shift/<mode>/ovl_report.txt). See docs/shiftable-plan.md "Session 13: overlay fixups" and "PCSX2 runs with overlay fixups".
  - How to test: `make shift SHIFT_MODE=m1`, then `tools/shift/patch_iso.py MY.iso out/shift/m1/kh1-shift.elf KH1_M1.iso` and boot the ISO (booting a bare ELF crashes even for retail). `tools/shift/extract_kingdom.py MY.iso --overlays --out out/overlays` pulls the overlays for the fixup table. Only 2-6 KB of the ELF's disc slot is left.
  - If a later area crashes, the debugger variable `kh1_ovl_status` holds {hash, result, entries, loads fixed}; result -3 means that overlay was left unpatched.
- Matching findings: nonmatchings/session13/NOTES.md, docs/matching-tips.md "Session 13 tips"; gdb tracers in tools/matching/gdb_s13/ (edit hard-coded paths).

## What is left (16 functions)

Best drafts in nonmatchings/session13/ (newest), then session12/11/10/9/8/7. LCS words.

1. **1-5 words**: 001fd858 (1, flagged: bnezl at 0x654 is a reorg liveness decision proven unreachable from this layout), 001cfc28 (1), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 001f18e8 (2), 001eddc0 (2), 0021e120 (3), 00125240 (5 flagged; 8 natural).
2. **9-56 words**: 00265608 (9, SDK gcc991111: trap_if scheduling), 00192958 (17), 00166570 (21), 00200e28 (24), 001c62a0 (56).
3. **Large**: 00110618 (93), 0010d470 (179: copy-loop invariant registers, WD base must not take a3), 001636d0 (410).

## Session 14 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Runtime**: play further into M1/M2 (Destiny Islands, Traverse Town, a world map / gummi load, Load and Special Movie) and fix what crashes; review the 67 ambiguous overlay fields; plan room on the disc for a bigger ELF.
2. **Shiftable, next**: review the 649 lone function-start and 423 string rows; an `out/shift` build of each near-miss draft swapped in for its asm export (static diff only); then M1+M2 combined.
3. **Matching (1 worker)**: 0010d470 and 00110618 section by section; the rest only with a new angle not in NOTES.
4. **Phase 3 start (1 worker, if time)**: document VU1 microcode programs and GS modes as a renderer spec in docs/ (not matching code).
5. End with `make progress-update SESSION=14`, commit, open a PR, and refresh this prompt.
