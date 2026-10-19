# Session 12 worker brief (kh1-decomp)

You are a hand-matching worker. Repo: /home/claude/kh1-decomp (built, toolchain ready in
tools/toolchain, the original ELF SLPS_251.98 is in the repo root: never copy it anywhere,
never commit it).

FIRST read (skim what you already know):
1. nonmatchings/session11/BRIEF.md, then session10/BRIEF.md and session9/BRIEF.md: tools, dump
   reading, output layout and rules. They still apply, with the session-12 paths below.
2. docs/matching-tips.md "Session 11 tips", "Session 11, later levers" and "Session 11, final
   levers" (newest), then Session 6-10 tips as needed.
3. nonmatchings/session11/NOTES.md, then session10/9/8/7 NOTES.md: grep each for every address on
   your list. Every earlier diagnosis is there. Do not repeat a sweep a note says was done.
4. docs/toolchain.md "Session 6", "Session 7", "Session 10/11 correction"; docs/context-only-plan.md.

## Your list
YOUR_LIST. Closest first. For each: read every draft (`ls nonmatchings/session*/*ADDR*`), start
from the closest, re-verify its count (tools/matching/lchk_s10.py / mchk_s10.py, or
tools/matching/tlcs_s11.py for big ones) on a copy in src/<mode>/.WTAG_x.c.

## Levers, in this order (the session-12 plan)
1. **Memory-dependence typing in strict mode** (session 11's last lever; matched 00105288,
   00106ed0, 00107548), applied per access: one-field structs (`typedef struct { f32 f; } F1;`)
   to make an access MEM_IN_STRUCT, a 4-byte enum field for a private alias set, one-member
   unions for alias set 0. Re-measure nostrict/nofill drafts in strict mode with these types.
   Read which loads wait on which stores in the original's sched1/sched2 order.
2. **33-ref flush**: haifa flushes its pending memory lists at the 33rd memory reference in a
   block; split store floods into those fixed chunks and climb within chunks.
3. Older session-11 sweeps: dead sets in another block (gcse PRE/CPROP, combine), strict
   re-measure, call-value-first, fresh climbs from index order, interblock region limits
   (10 blocks / 100 insns).
4. **Dead float tests / dead stores / identical arms**: "flagged" levers. The user decided in
   session 12 that flagged matches count. Prefer a natural shape; if only a flagged trick reaches
   0, it is a match: put `/* FLAGGED: <trick> */` at the top of the function and report it as
   flagged.

## Where your output goes (session 12 paths)
- WDIR = /tmp/claude-0/s12/WTAG (create it). Helpers and dumps there.
- Matched code: WDIR/out/<mode>/text_XXXX0000_s12_WTAG.c (by the function's 64 KiB region).
  One file per mode and region, starting with `#include "common.h"`, with the CONTEXT_ONLY copies
  it needs. Only verified functions: tools/checkfile.py MATCH on a copy at src/<mode>/.WTAG_chk.c
  (rodata functions: tools/matching/lchkro_s10.py with RO set, mark them `/* rodata */`).
- Near misses better than the best existing draft, or with a new finding:
  WDIR/near/<addr>_<N>w.c, first line a comment: words off, mode, context, what is off.
- Scratch tests: dot files src/<mode>/.WTAG_*.c only; delete them at the end.

## Rules
- No `make`, no `git`, no edits outside WDIR and your own dot files in src/.
- **Resource limit**: 4 cores and 16 GB shared by 3 workers. At most 1 compile or hill-climb
  process at a time from you, in the foreground with a timeout (max ~10 minutes each). No
  background jobs, no sleep/until polling loops. Check /proc/loadavg before a long climb.
- **Never name a helper after a stdlib module** (glob.py, json.py, re.py, ...); run your helpers
  with `python3 -I` (session 11 lost the container twice to a `glob.py`).
- Never kill processes you did not start. No copying from other decomp projects.
  No inline-asm bodies for ordinary C (VU0/MMI/sync/cop0 only).
- Do not call any mcp__hearthbot__ tool.
- A shape that reaches 0 words only with a hack (asm barrier, `.p2align`, an `__asm__` symbol
  alias, struct cast over other locals, a flag no other function needs, an assembler post-pass)
  is a near miss: save it, say what it needs; do not count it as a match.
- Time-box: about 25 serious attempts per function without progress, then move on. Be direct
  about ones that look like a compiler/assembler oddity rather than source shape.

## Report back (final message, concise)
1. Matched: names, mode, out/ file paths (context needed), natural or FLAGGED (which trick).
2. Near misses saved (path, words off, what is off).
3. Stuck, with the reason (the pass responsible, if found), and the levers tried.
4. New facts, one line each.
