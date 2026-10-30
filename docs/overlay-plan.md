# Plan: match every overlay function (phase 2, from session 141)

Session 141 (2026-10-28) starts a continuous push on the 12 EE overlays (docs/overlays.md).
This file is the plan and the running ledger; update the table at the end of each batch.

## Where it starts

`make ovl-progress` at the start of session 141 (every overlay byte-identical, `make ovl`):

| Overlay | Matched / functions | Left | Left "hard" (VU0 / MMI / 128-bit) | Left by size: <=50 / 51-150 / 151-400 / >400 insns |
|---|---|---|---|---|
| dkmovie | 96 / 122 | 26 | 6 | 6 / 9 / 9 / 2 |
| dktitle | 60 / 71 | 11 | 1 | 0 / 3 / 6 / 2 |
| gb | 367 / 533 | 166 | 19 | 10 / 70 / 67 / 19 |
| wm | 747 / 1109 | 362 | 51 | 25 / 163 / 144 / 30 |
| xl_limit | 74 / 76 | 2 | 0 | 0 / 2 / 0 / 0 |
| xs_bambi | 13 / 13 | 0 | 0 | done |
| xs_dh_break | 5 / 9 | 4 | 0 | 0 / 2 / 2 / 0 |
| xs_dumbo | 48 / 54 | 6 | 0 | 0 / 4 / 2 / 0 |
| xs_genie | 58 / 64 | 6 | 0 | 0 / 5 / 1 / 0 |
| xs_mushu | 22 / 24 | 2 | 0 | 0 / 1 / 1 / 0 |
| xs_simba | 29 / 33 | 4 | 0 | 0 / 0 / 4 / 0 |
| xs_tink | 13 / 14 | 1 | 0 | 0 / 1 / 0 / 0 |
| total | 1532 / 2122 | 590 | 77 | |

(docs/progress.md said 1,537 of 2,131 before; 2,122 is what the layouts hold today.)

wm's matched functions are only 92,776 of its 391,196 code bytes: what is left is mostly
large. The easy part is gone; session 131b's notes say the rest is mostly register
allocation, scheduling and big functions.

## Order of work

1. **Re-run autodecomp** over every unmatched overlay function with a larger search budget
   (`--budget 120`), for the reports' scores (the queue) and any free matches. Then twins.py.
2. **Small overlays first** (xs_tink, xs_mushu, xl_limit, xs_genie, xs_dumbo, xs_simba,
   xs_dh_break: 25 functions), so whole overlays close.
3. **dktitle and dkmovie** (37): drafts already exist (ovl/dktitle/drafts.tsv,
   nonmatchings/session13x/); permuter on the 1-6 word ones.
4. **gb, then wm**, closest first by autodecomp score. Every gb match is tried on wm and the
   summons by twins.py (they share most of their code), so gb goes first.
5. **Hard functions** (VU0 macro code, 128-bit copies) last: inline asm where it is clearly
   hand-written; flag the rest in the ledger rather than burning hours.

Rules: a function counts only when `make ovl` is byte-identical and `make ovl-report` says
100% for it. PRs go up in batches (one per overlay group or every ~25 matches), each with
`make ovl` and `make` (main ELF) still byte-identical. Near misses keep their best draft in
`nonmatchings/session141/OVERLAY/` with the words left.

## Ledger

| Batch | Date | Matched after | Notes |
|---|---|---|---|
| start | 2026-10-28 | 1532 / 2122 | |
| batch 1 | 2026-10-28 | 1590 / 2114 | autodecomp rerun (0 new), dktitle func_00f21068, dkmovie 6 MMI routines as asm, gb/wm main state machine (layout fixed: its switch cases were split off), xs_simba complete (4 by hand), xs_dumbo +4, xs_genie +1, workers: gb +12, wm +8, 12 wm twins via portall.py. Near misses: nonmatchings/session141/. |
| batch 2 | 2026-10-29 | 1662 / 2114 | gb +15 by hand and by the gb worker (each with its wm twin where one exists), wm +50 (two wm workers, twins via portall.py), dkmovie +0 (5 drafts within 7-51 words), xs_mushu func_00f20c58, xs_dh_break +1 (old draft in nostrict mode), xl_limit func_00f20e10, xs_genie +3. gb VU0 / sq functions f3e0d8, f41dc8 (15 words), f24780 left as near misses. |
| batch 3 | 2026-10-29 | 1699 / 2114 | gb +11 (f38408 / f3e388 GIF and skeleton builders by hand, 9 twins of wm matches), wm +21 (f3e388 / f38408 twins, f67928, 18 by the two wm workers), dkmovie +4, dktitle +1 (f25528). New near misses: gb f2d8d8, xs_genie f22078, ~20 wm drafts (nonmatchings/session141/wm/, headers say what's left). gb f41dc8 down to 3 words. |
| batch 4 | 2026-10-29 | 1765 / 2114 | gb +25 (f30d80 / f29c40 / f299c8 by hand via the `k = q * 4 + 8` table index and u16 lock reads, f41dc8 via the f68ec0 `ff` local, worker matches, twins), wm +41 (two workers: u16-bitfield fixes, sprite / grid families via index reuse `j = i; i = g->c[j].t`, f792c8 / f68ec0 packet builders). Workers' tips are in nonmatchings/session141/wm/NOTES-wwm*.md. |
| batch 5 | 2026-10-29 | 1805 / 2114 | gb and wm +40 (gb 448, wm 911: gb twins of wm matches via portall.py / portmap.py, gb f29f10 / f49320, worker matches: packet builders via an indexed `put`, store-order brute force, statement-order hill climbing, f70828 / f757b8 / f6a530 families). Near misses for every drafted function are in nonmatchings/session141/{gb,wm}/ with what was tried in each header. |
| batch 6 | 2026-10-29 | 1853 / 2114 | gb +5, wm +41, dktitle +1 (func_00f20a98), xs_mushu +1 (now complete, 24 / 24). Every remaining overlay function now has a near-miss draft. Two root causes found: callees declared `void` that really return a value (fixes scheduling and load order), and the nothrow rule behind branch-likely vs plain-branch delay slots (a `CONTEXT_ONLY` definition of the callee above the function; docs/overlays.md). Rankings by aligned diff are in nonmatchings/session141/{gb,wm}/RANKING.md. |
| batch 7 | 2026-10-30 | 1873 / 2114 | gb +7, wm +12, xs_dh_break +1 (func_00f20820). The new tools and source patterns: tools/ovl/i2a.py (initializers turned into ordered assignments, for stack-slot store order), a hill-climber ranked by hand.py score that only makes dependency-safe statement moves, tools/ovl/drafttwins.py (ports the better gb/wm draft to its twin), register dispositions read from -dl/-dg dumps to steer live lengths, alias ordering (store through a pointer before a global read it may alias), real struct layouts for tables indexed with a hand-computed offset, arithmetic moved into each branch, loop peeling of a per-pass wait call (padding nops as the clue), and packed GS-word term order. Details are in docs/overlays.md "Batch 7 patterns" and NOTES-wwm1.md / NOTES-wwm2.md. |
| batch 8 | 2026-10-30 | 1893 / 2114 | gb +7, wm +11, dkmovie +1, xs_dumbo +1 (func_00f20570). New levers: a field's declared type as a store-order lever (wm f3ac48), `(x + c) << 4` where gcc would fold `(x + c) * 16`, end-coordinate locals computed before the packet calls (gb f3c1f0), mixed `(u8)` / `& 0xFF` reads of one s8 field (gb f4d930), gcse hash-bucket order (the insn count at gcse time decides which %hi pseudo is numbered first, xs_dumbo f20570), and auditing values before registers: tools/ovl/valaudit.py found two drafts passing the wrong argument (gb f422e8, wm f62440) and tools/ovl/xsym.py lists cross-overlay symbols. Fixed-address stand-ins were replaced by asm-label second names, which still do not count as matches. Details are in docs/overlays.md and NOTES-wwm2.md. |
| batch 9 | 2026-10-30 | 1907 / 2114 | gb +3, wm +7, dkmovie +2, dktitle +2 (func_00f24330, func_00f228c8). Final batch of session 141. New tools: tools/ovl/rettype.py (callee return types tried against matched code and as s32/void), tools/ovl/nothrow.py (CONTEXT_ONLY callee definitions where a plain branch came out branch-likely, with a `kept` check for score-only gains), tools/ovl/cfdiff.py (branch/call skeleton distance), tools/ovl/gcsebucket.py; hill3 now keeps volatile accesses in order. Findings: in C only an earlier definition in the same file makes a call nothrow, so CONTEXT_ONLY gains on main-ELF callees are stand-ins; -fno-optimize-sibling-calls (nosib) merges two per-arm calls into one jal; break vs goto decides loop rotation; a `case 0: default:` balances the case tree. A permuter batch (35 min per draft, outputs rescored with hand.py and reviewed for natural code) matched three gb/wm pairs. wm func_00f3bc48 matches with an asm-label second name for D_01067FE0 whose natural source form is unknown. |

## Stopping point (session 141)

Session 141 stopped at 1,907 / 2,114 by choice: the last rounds averaged about 4 matches an hour, so further matching cost too much per function. What is left, by kind:

- **Register and scheduling ties (score under about 10).** The instruction multiset and the control flow already match, and one or two registers or one slot differ. Examples: gb f425a8 / wm f696a0 (3), wm f436d0 (4), dkmovie f20b48 (2), wm f23550 (2 with a register pin, 5 without), xs_genie f218f8 (3), dktitle f241c8 (3) and f26710 (5). Hand edits, hill3 and 35-minute permuter runs have not broken them. The likeliest way forward is a longer permuter run per draft.
- **Mid-range drafts (score 10 to 150).** Mostly global-alloc priority or loop strength-reduction differences. The levers in docs/overlays.md (field types, value audits, return types, nothrow, nosib, loop shape) have been tried on most of them.
- **Large functions (score over 150).** The gb/wm menus, wm f75d80 and the dkmovie player. Their control flow is mostly right (cfdiff), but they are too big for the search tools.

The per-draft state is in each draft's header comment, nonmatchings/session141/{gb,wm}/RANKING.md, NOTES-wwm1.md and NOTES-wwm2.md. Start a new session with `tools/ovl/cfdiff.py --scan`, `valaudit.py --scan`, `rettype.py` and `nothrow.py --scan` to see where each draft stands.
