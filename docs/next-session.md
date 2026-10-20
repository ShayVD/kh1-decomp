# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it).

## Where we stopped (end of session 21, 2026-10-20)

- **6,978 / 6,988 functions matched**: 99.86% of functions, 98.83% of code bytes (docs/progress.md). Session 21 matched nothing new. 00265608 (sceGsDefDispEnv) is now 4 words with two more register pins; the 2 words left in each block are a sched2 dependence that plain C did not change. 001fd858 stays at 1 word (nonmatchings/session21/NOTES.md).
- **The Agrabah wall bug is fixed**: the session 20 float build (Q4000) reached the world map and warped to Agrabah, but Sora walked through the walls. Bisection isolated D_002A6274. func_00105288 reads D_002A6278 as `((s32 *)&D_002A6274)[1]`, which assembles as `%lo(D_002A6274+4)`, so floating the base alone broke the read. The new **tools/shift/addend_check.py** keeps both names of every such pair (72 names). Details: docs/shiftable-plan.md "Session 21".
- **reach_check is less conservative** (worker s21r1): countdown bounds, stored joins (`cond ? A : B`), arg-join and block bounds, plus two coverage fixes (`D[i]` as lui+addu+%lo, and switch case bodies). It keeps 1,832 names instead of 1,928. **keep_check.py** fails the float build if any of the 35 names found by bisection would float.
- **The default float build now floats 721 data names and 118 bss runs** (1,230 variables). Budgets 0x6000 (852 data names, `_end` 0x693464) and 0x8000 (870, `_end` 0x6951E4; 0xE1C left below the arena) build and link. Their ELFs are KH1_F21_RA0x6000/0x8000 in Downloads/kh1-test/s21.
- **Not booted yet**: the combined default build (KH1_F21_RA, already appended to KH1_BIG.iso) and the two larger budgets. The PCSX2 game window was minimised during the session and could not be restored from computer use.
- **Test memcard**: save 05 is Traverse Town and save 06 is in Agrabah. The load menu's cursor starts on save 06. The walk test is to walk Sora into a wall.

## What is left (10 functions)

Best drafts are in nonmatchings/session21/ and older. Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill; pins exhausted), 001f1fc8 (2, nofill; pins exhausted), 00125240 (3; two `lui`s in sched1 order), 00265608 (4, sched2 dependence).
2. **16-24 words**: 001c62a0 (16, global-alloc order), 00200e28 (24).
3. **Large**: 00110618 (93), 0010d470 (170 natural), 001636d0 (400).

## Session 22 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot KH1_F21_RA** (the default build) in PCSX2. Load save 06 in Agrabah, do the walk test and a fight, then load save 05 and check the world map. Then boot 0x6000 and 0x8000 the same way. If one fails, bisect with `SHIFT_FLOAT_ONLY_DATA`. Also try turning off reach_check's new relaxations (`--no-countdown`, `--no-join`, ...) one at a time.
2. **Raise the default budget** to the largest one that plays. With the four records found statically now, check whether their float_keep.txt group can go.
3. **Float the kept records as wholes** (merge_pieces.py on the four object/table records and the staging arena). Then try floating the pointer-table-only names with their table, bisecting D_0048F700 ... for the missing digit.
4. **Phase 4**: D_0046A688 (needs D_0046A6A4 out of C) and types for the 1,229 untyped pieces.
5. **Matching (1 worker)**: 00125240 (3w) or 001c62a0 (16w).
6. End with `make progress-update SESSION=22`, commit, open a PR, and refresh this prompt.
