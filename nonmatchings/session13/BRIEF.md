# Session 13 worker brief: matching track (kh1-decomp)

You are a hand-matching worker. Repo: /home/claude/kh1-decomp (built with `make`, toolchain ready
in tools/toolchain, the original ELF SLPS_251.98 is in the repo root: never copy it anywhere,
never commit it). 16 functions are left; all have been tried for several sessions, so read the
earlier diagnosis before touching anything.

FIRST read (skim what you already know):
1. nonmatchings/session12/BRIEF.md (rules, output layout; still apply with the session-13 paths
   below), then session11/BRIEF.md for tool usage.
2. docs/matching-tips.md "Session 12 tips" (newest), then "Session 11 ..." sections.
3. nonmatchings/session12/NOTES.md, then session11/10/9/8/7 NOTES.md: grep each for every address
   on your list. Do not repeat a sweep a note says was done.
4. The header comments of tools/matching/la4_s12.py / la3f_s12.py (local-alloc simulators), osrch_s12.py
   (minimal sched1-order change for a target allocation), tools/matching/gdb_s12/.

## Your list
YOUR_LIST. Closest first. For each: read every draft (`ls nonmatchings/session*/*ADDR*`), start
from the closest, re-verify its count (tools/matching/lchk_s10.py / mchk_s10.py, or
tools/matching/tlcs_s11.py for big ones) on a copy in src/<mode>/.WTAG_x.c.

## Levers (session 12's, in order)
1. Register-allocator analysis: dump .lreg, simulate with la4_s12.py (GPR) / la3f_s12.py (FP),
   find which qty gets the wrong register and why (priority = refs*... / live length, LUID ties),
   then osrch_s12.py for the minimal sched1-order change that reaches the target allocation, and
   find a source shape that produces that order.
2. Shapes that worked in session 12: base-pointer local set first (wins sched1 LUID ties), an
   invariant written at its use inside a loop (hoisted to the end of the preheader), a variable
   set twice is never local-alloc'd, temps made function-level leave local-alloc, header constants
   in u64 variables (li order), array index instead of a pointer local (spill-slot order),
   builtin abs(), pointer local set after a call.
3. Flagged tricks (dead stores, dead float tests, identical arms, never-true tests, empty
   `do {} while (0)` barriers) COUNT as matches (user decision, session 12). Prefer natural; if
   only a flagged trick reaches 0, put `/* FLAGGED: <trick> */` at the top of the function.

## Where your output goes
- WDIR = /tmp/claude-0/s13/WTAG (create it). Helpers and dumps there.
- Matched code: WDIR/out/<mode>/text_XXXX0000_s13_WTAG.c (by the function's 64 KiB region), one
  file per mode and region, starting with `#include "common.h"`, with any CONTEXT_ONLY copies it
  needs. Only verified functions: tools/checkfile.py MATCH on a copy at src/<mode>/.WTAG_chk.c
  (rodata functions: tools/matching/lchkro_s10.py with RO set, mark them `/* rodata */`).
- Near misses better than the best existing draft, or with a new finding:
  WDIR/near/<addr>_<N>w.c, first line a comment: words off, mode, context, what is off.
- Scratch tests: dot files src/<mode>/.WTAG_*.c only; delete them at the end.

## Rules
- No `make`, no `git`, no edits outside WDIR and your own dot files in src/. Two other workers
  are building a "shiftable" link in their own git worktrees at the same time; ignore them.
- **Resource limit**: 4 cores and 16 GB shared by 3 workers. At most 1 compile or hill-climb
  process at a time from you, in the foreground with a timeout (max ~10 minutes each). No
  background jobs, no sleep/until polling loops. Check /proc/loadavg before a long climb.
- **Never name a helper after a stdlib module** (glob.py, json.py, re.py, ...); run helpers with
  `python3 -I`.
- Never kill processes you did not start. No copying from other decomp projects (e.g.
  ethteck/kh1). No inline-asm bodies for ordinary C (VU0/MMI/sync/cop0 only).
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
4. New facts, one line each (they go into nonmatchings/session13/NOTES.md).
