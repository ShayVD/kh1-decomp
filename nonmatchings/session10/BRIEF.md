# Session 10 worker brief (kh1-decomp)

You are a hand-matching worker. Repo: /home/claude/kh1-decomp (built, toolchain ready in
tools/toolchain, the original ELF SLPS_251.98 is in the repo root: never copy it anywhere,
never commit it).

FIRST read (skim what you already know):
1. nonmatchings/session9/BRIEF.md: tools, dump reading, output layout and rules. They all
   still apply, with the session-10 paths below.
2. docs/matching-tips.md, from "Session 6 tips" to the end (Session 9 tips are the newest).
3. nonmatchings/session9/NOTES.md, then session8/NOTES.md, session7/NOTES.md and
   session6/INDEX.md: grep each for every address on your list. Every earlier diagnosis is there.
4. docs/toolchain.md "Session 6" and "Session 7" (build modes), docs/context-only-plan.md.

## Your list
YOUR_LIST. Every function here has been tried by several workers in sessions 6-9. Read every
existing draft (`ls nonmatchings/session*/*ADDR*`) and start from the closest (session9 newest).
First re-verify its word count: copy to src/<mode>/.WTAG_x.c and run
`python3 tools/checkfile.py src/<mode>/.WTAG_x.c -v`, or for 31+ word drafts
tools/matching/lcs_s8.py (LCS words). Drafts may need CONTEXT_ONLY copies named in their first line.

## Step 0 for every function: sibling-port sweep (session 9's best lever)
Before any dump reading or hill-climb:
- `grep -rl D_XXXXXXXX src/` for every global the draft touches, `grep -rl func_XXXXXXXX src/`
  for every callee, and look at matched functions in the same 64 KiB region that build the same
  packet/message type or call the same callee sequence.
- Rewrite the draft in the sibling's style: its extern declarations and types (arrays like
  `u8 X[][112]`, bitfields, aligned(8), flat `s32 D[]`), plain globals instead of pointer
  locals, its store order, its loop shape, its constants inline, its helper macros.
- Then the callee-prototype check (tools/matching/arity_s8.py on every callee; void vs s32 return).
Write one line per function in your report saying which siblings you tried, even if nothing helped.

## Then the session 8/9 levers
Plain index order for store floods; shared `goto` tails to cut refs; reusing an existing
long-lived local; one counter for two loops; compiled-out `do { } while (0)` asserts as block
boundaries; chained assignments for store order; two-insn arms to block if-conversion; reading
gcc's dumps to find the pass that differs (session 8 method). Change angle from what NOTES.md
says earlier workers already swept.

## Where your output goes (session 10 paths)
- WDIR = /tmp/claude-0/s10/WTAG (create it). Helpers and dumps there.
- Matched code: WDIR/out/<mode>/text_XXXX0000_s10_WTAG.c (by the function's 64 KiB region).
  One file per mode and region, starting with `#include "common.h"`, with the CONTEXT_ONLY
  copies it needs. Only verified functions: checkfile MATCH on a copy at src/<mode>/.WTAG_chk.c.
  Rodata functions: verify with tools/matching/wqb03_rr.py --file ... --out-dir src/<mode>
  and mark them `/* rodata */`.
- Near misses better than the best existing draft, or with a new finding:
  WDIR/near/<addr>_<N>w.c, first line a comment: words off (LCS for big ones), mode, context,
  what is off.
- Scratch tests: dot files src/<mode>/.WTAG_*.c only; delete them at the end.

## Rules
- No `make`, no `git`, no edits outside WDIR and your own dot files in src/.
- The machine has 4 cores shared by many workers: at most 1 compile process at a time from you.
  No sleep/until polling loops; run long jobs in the foreground with a timeout.
- Never kill processes you did not start. No copying from other decomp projects.
  No inline-asm bodies for ordinary C (VU0/MMI/sync/cop0 only).
- Do not call any mcp__hearthbot__ tool.
- A shape that reaches 0 words only with a hack (asm barrier, `.p2align`, struct cast over
  other locals, a flag no other function needs, an assembler post-pass) is a near miss: save
  it and say what it needs; do not count it as a match.
- Time-box: about 25 serious attempts per function without progress, then move on. Be direct
  about ones that look like a compiler/assembler oddity rather than source shape.

## Report back (final message, concise)
1. Matched: names, mode, out/ file paths (and context needed).
2. Near misses saved (path, words off, what is off).
3. Stuck, with the reason (the pass responsible, if found), and the siblings tried.
4. New facts, one line each.
