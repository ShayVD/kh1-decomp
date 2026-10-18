# Session 11 worker brief (kh1-decomp)

You are a hand-matching worker. Repo: /home/claude/kh1-decomp (built, toolchain ready in
tools/toolchain, the original ELF SLPS_251.98 is in the repo root: never copy it anywhere,
never commit it).

FIRST read (skim what you already know):
1. nonmatchings/session10/BRIEF.md and nonmatchings/session9/BRIEF.md: tools, dump reading,
   output layout and rules. They still apply, with the session-11 paths below.
2. docs/matching-tips.md, from "Session 6 tips" to the end ("Session 10 tips" is the newest).
3. nonmatchings/session10/NOTES.md, then session9/8/7 NOTES.md and session6/INDEX.md: grep each
   for every address on your list. Every earlier diagnosis is there. Do not repeat a sweep a
   note says was already done; change angle.
4. docs/toolchain.md "Session 6", "Session 7", "Session 10 correction"; docs/context-only-plan.md.

## Already done this session (do not redo)
- nonmatchings/session11/ctxsweep.txt: tools/matching/ctxsweep_s10.py (CONTEXT_ONLY `{}` stub
  per callee, all, all-but-one; void<->s32 callee returns) over the best draft of every function.
  No new matches. 00152928 drops 25 -> 20 with a stub of func_00152648 (hand mode).
- nonmatchings/session11/modesweep.txt: tools/matching/modesweep_s11.py re-measured every draft
  in strict/nostrict x fill/nofill x {-, -fno-gcse, -fno-sched-interblock} (LCS words). Better
  than recorded: 001c3b10 2 in plain hand (strict; was 4 in nostrict), 001cf960 3 (hand),
  00120cf8 5, 001f1fc8 4 (nofill), 00152928 9 (nostrict), 0019f1f0 7 (nostrict, rodata),
  001137f8 11, 001eddc0 9, 001fbcd8 17, 00217000 8 (nostrict). Use the best mode as your start.

## Your list
YOUR_LIST. Closest first. For each: read every draft (`ls nonmatchings/session*/*ADDR*`), start
from the closest, re-verify its count (tools/matching/lchk_s10.py or mchk_s10.py on a copy in
src/<mode>/.WTAG_x.c; checkfile.py can take minutes under load).

## Levers, in this order (session 10's matches came from these)
1. Types for alias sets: the real struct type a callee takes for a global, bitfield structs for
   packed words, split punning unions into plain structs (union member access is alias set 0),
   f32-typed zero fields (`= 0.0f`). Check matched siblings' declarations of the same globals
   (`grep -rl D_XXXXXXXX src/`).
2. Write `goto` tails out as duplicated statements in every arm (jump2 re-merges them, refs
   stay); identical `if (c) {X} else {X}` arms to make pseudos global (flag it in a comment).
3. Block-local reloads (`{ T *m = e->next; ... }` instead of reassigning a long-lived local),
   static inline helpers (copy of a matched sibling's body), GNU C nested inline helpers.
4. Dead global reads for gcse PRE placement; CONTEXT_ONLY data definitions for slot fills.
5. Then dumps (session 8 method: find the pass that differs, change its input) and the
   hill-climbs (hl2_s10.py, hcf_s10.py, hl_s9.py) on small blocks only.

## Where your output goes (session 11 paths)
- WDIR = /tmp/claude-0/s11/WTAG (create it). Helpers and dumps there.
- Matched code: WDIR/out/<mode>/text_XXXX0000_s11_WTAG.c (by the function's 64 KiB region).
  One file per mode and region, starting with `#include "common.h"`, with the CONTEXT_ONLY
  copies it needs. Only verified functions: tools/checkfile.py MATCH on a copy at
  src/<mode>/.WTAG_chk.c (rodata functions: tools/matching/lchkro_s10.py with RO set, or
  wqb03_rr.py --file ... --out-dir src/<mode>; mark them `/* rodata */`).
- Near misses better than the best existing draft, or with a new finding:
  WDIR/near/<addr>_<N>w.c, first line a comment: LCS words off, mode, context, what is off.
- Scratch tests: dot files src/<mode>/.WTAG_*.c only; delete them at the end.

## Rules
- No `make`, no `git`, no edits outside WDIR and your own dot files in src/.
- 4 cores shared by 5 workers: at most 1 compile process at a time from you. No sleep/until
  polling loops; run long jobs in the foreground with a timeout (max ~10 minutes each).
- Never kill processes you did not start. No copying from other decomp projects.
  No inline-asm bodies for ordinary C (VU0/MMI/sync/cop0 only).
- Do not call any mcp__hearthbot__ tool.
- A shape that reaches 0 words only with a hack (asm barrier, `.p2align`, an `__asm__` symbol
  alias, struct cast over other locals, a flag no other function needs, an assembler post-pass)
  is a near miss: save it, say what it needs; do not count it as a match.
- Time-box: about 25 serious attempts per function without progress, then move on. Be direct
  about ones that look like a compiler/assembler oddity rather than source shape.

## Report back (final message, concise)
1. Matched: names, mode, out/ file paths (and context needed).
2. Near misses saved (path, LCS words off, what is off).
3. Stuck, with the reason (the pass responsible, if found), and the levers tried.
4. New facts, one line each.

## Found so far in session 11 (s11w1: 5 matches in 0x1c0000)
- u64 flags words as bitfields placed directly in the owning struct (`u64 b0:1, b1:1, rest:62;`)
  instead of a punning union: the store gets the struct's alias set (001cf960, 001c99a8). Old
  "FP local-alloc / LUID tie" diagnoses were really union alias-set-0 accesses.
- A pointer into the middle of a word block as a different symbol (`extern s32 D_002C5950[];
  fl = &D_002C5950[2];` for D_002C5958) makes a different RTL address, so gcse does not share
  it with a direct access (001c2ec8).
- Identical arms of one store each merge before register allocation (no refs gained); arms of
  two stores survive to jump2.
- Re-measure in strict mode: 001c3b10 was a strict function all along.
