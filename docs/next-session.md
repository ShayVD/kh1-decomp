# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 8, 2026-10-18)

- **6,876 / 6,988 functions matched**: 98.4% of functions, 91.0% of code bytes. All are byte-identical and objdiff 100% (docs/progress.md).
  - Game: 6,159 / 6,266.
  - SDK: 717 / 722.
- Session 8 matched 40 by reading gcc's dumps for the pass that differs (docs/workflow.md "Session 8", docs/matching-tips.md "Session 8 tips"). Every worker finding is in nonmatchings/session8/NOTES.md; the worker brief is nonmatchings/session8/BRIEF.md.
- Main levers: reused generic function-level variables (or block-local in one branch), parameter copies/order/int-cast params, callee arity and return types (tools/matching/arity_s8.py), scheduler tie-breaks (priority, INSN_REG_WEIGHT, forward-dependence count, LUID), plain structs instead of u8-array unions, reading nostrict load/store order off the asm, separate case bodies (loop latches).
- New tools in tools/matching/: lcs_s8.py, sbs_s8.py, cc_s8.py, dump_s8.py, rtl_s8.py, prio_s8.py, arity_s8.py, hill_s8.py (set WDIR and WTAG).
- Known quirk: `make rank` lists four libc statics (00251600, 00252370, 00253b10, 00253cd0) as unmatched; they are matched and placed.

## What is left (112 functions)

Run `make rank` for the full list (status `wip`/`asm`). Drafts are in nonmatchings/session8/, session7/ and session6/ with the word count in the file name (session-8 large drafts are counted by LCS).

1. **Within 1-5 words** (all are allocator or scheduler ties diagnosed in NOTES): 00101bb8, 00142e30, 001502e8, 001e32d8, 0025a560 (2w); 00166248, 001e3a00, 001e6038, 001f2630, 0025f338 DIntr (3w); 0010ed20, 00169688, 001e0ab0 / 001e0d98 / 001e10f8 (4w, the reorg `li v0,4` steal); 001f1fc8, 0024bce8 (5w).
2. **6-30 words**: 0025b2f0, 00105d88, 00115758, 00120cf8, 001ca0f8, 001cf960, 00202678, 00212cc0, 0010ea70, 00113e28, 00125240, 0021b4c8, 0011b220, 00177488, 001b9f78, 001c99a8, 001fe1b8, 001c5ee8, 0010c720, 00152928, 001fa8b0, 00249718, 00266380 sceGsExecStoreImage, 001eddc0, 00110e68, 001c95f8, 00260610, 001166e8 (16w, right size), 00176c60, 001cd2d8, 001f31a8, 00219598, 001cfc28, 00103c48, 001ba520, 001fbcd8, 0021e120, the 22w group (0010b390, 001137f8, 00116368, 00149c80, 00214a68), 00199ac8 / 0019ab38 (24w), 00217000, 0010a780, 00166570, 001ff488, 00102118, 0019f1f0, 00107c48, 00219f98.
3. **Large or far** (31+ words): 001edfb8, 0010ba98, 00135a68, 002376c8, 0023a968, 001db718, 0024c950, 00192958, 00105288, 00169f28, 0016ea58, 00265608, 001bd090, 001ca368, 001fb428, 00237b30, 001c3b10, 00106ed0, 00200e28, 001f18e8, 00216890, 00197cf8 Tail3XDraw, 0024be88, 001bc530, 001c2ec8, 001e1838, 001ffb30, 00200648, 00110618, 001c62a0, 00107548, 00191248 Tail3Draw, 001f5fe0, 00200038, 002106b8, 001fd858, 001636d0, 0010d470; no draft: 0012e1b0, 001c53c8.
4. **Suspected compiler differences**: func_00171078 and 0010a780 (a `la` split after jump2 with the slot filled), 0025b2f0, 001bd090.

## Session 9 plan

1. Run the callee-prototype sweep (arity_s8.py + return types) over every draft once more, then work the 1-5 word list with the session-8 levers.
2. Then the 6-30 word list, starting from the session-8 drafts.
3. Attempt the large functions, closest by LCS first.
4. End with `make progress-update SESSION=9`, commit, open a PR, and refresh this prompt.
