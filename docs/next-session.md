# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 11, 2026-10-19)

- **6,962 / 6,988 functions matched**: 99.63% of functions, 97.23% of code bytes. All are byte-identical and objdiff 100% (docs/progress.md).
  - Game: 6,241 / 6,266.
  - SDK: 721 / 722.
- Session 11 matched 46 with about 75 workers (5 at a time restarted the container twice; run at most 3, see docs/workflow.md "Resource limit"). See docs/workflow.md "Session 11", docs/matching-tips.md "Session 11 tips" and "Session 11, later levers". Every worker finding is in nonmatchings/session11/NOTES.md; the brief is nonmatchings/session11/BRIEF.md. Best drafts are in nonmatchings/session11/ (newest), then session10/9/8/7/6. Drafts of matched functions were removed.
- **23 matches are flagged**: they use a dead store, a dead float test (`if ((f32)x < 0.0f) v = 0;`), identical if/else arms or a never-true test with duplicated arms that the compiler deletes. They are byte-identical but probably not the original source; the list is in docs/workflow.md "Session 11". Whether to keep counting them is the user's call.
- 001bd090 is a real match: no compiler-difference suspects remain (docs/toolchain.md "Session 11 correction").
- 00200038 matches with an unusual but plain-C shape: strip-loop stores through `s32 *p = &blk[i].v[11].x;` with negative indices (gives loop.c's blk+416 base). It is counted as natural; the file comment says so.
- Main levers this session, latest first: memory-dependence typing in strict mode (one-field structs for MEM_IN_STRUCT, 4-byte enum fields for a private alias set, one-member unions for alias set 0; matched 00105288, 00106ed0, 00107548), large functions section by section / case by case (001e1838, 001f5fe0, 00200038; tools/matching/jt_s11.py, tlcs_s11.py), haifa flushes pending memory lists at the 33rd memory ref in a block (store floods split into fixed chunks), alias sets (u64 bitfields, struct-member globals, union fields; a "nostrict" function can be strict with unions), dead sets in another block to steer gcse PRE/CPROP and combine, dead float tests for allocator refs / global pseudos / live ranges / block splits, call-value-first, fresh hill-climbs from index order after fixing the head of a flood, strict f32 blocks keep source order.
- Known quirk: `make rank` lists libc statics (00251600, 00252370 as `wip`; 00253b10, 00253cd0) as unmatched; they are matched and placed.

## What is left (23 functions, plus the libc statics)

Run `make rank` for the list (status `wip` in out/rank.tsv). Counts are LCS words from the best draft (NOTES.md has the diagnosis for each).

1. **1-2 words**: 001cfc28 (1, sched2 LUID tie), 001f2630 (1, nofill store order), 001f1fc8 (2, nofill), 001f18e8 (2, nofill li order, flagged test).
2. **4-11 words**: 00120cf8 (4), 0021e120 (3, w61 draft), 0019f1f0 (2, w57 draft: li.s placement in a shared tail), 00125240 (6, w60 draft), 001eddc0 (2, w64 draft: needs one interblock sched1 region, see s11w67), 0024c950 (8, nofill), 00265608 (9, SDK gcc991111: dead float tests don't work there), 001ba520 (10), 001137f8 (11).
3. **17-60 words**: 00192958 (17), 00166570 (21), 00216890 (13, w58 draft), 00200e28 (25, w74 draft), 001db718 (40), 001c62a0 (56, w64 draft).
4. **Large**: 00110618 (158), 0010d470 (196 true LCS, w73 draft), 001636d0 (~420), 001fd858 (452).

## Session 12 plan

1. Decide with the user whether flagged matches count; if not, move them back to nonmatchings/.
2. Try the memory-dependence typing lever (strict mode; struct / enum-field / union typing per access) and the 33-ref flush chunking on every remaining draft first, then the older session-11 sweeps (dead-set and dead float test insertion, strict re-measure). Helpers are described in nonmatchings/session11/NOTES.md (worker helper dirs under /tmp do not survive the session).
3. Then the 1-11 word list, closest first, then the larger ones. Run at most 3 workers at once.
4. End with `make progress-update SESSION=12`, commit, open a PR, and refresh this prompt.
