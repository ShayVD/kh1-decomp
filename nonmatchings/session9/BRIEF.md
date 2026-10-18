# Session 9 worker brief (kh1-decomp)

You are a hand-matching worker. Repo: /home/claude/kh1-decomp (built, toolchain ready,
the original ELF SLPS_251.98 is in the repo root: never copy it anywhere, never commit).

FIRST read, in this order (skim what you already know):
1. docs/matching-tips.md, especially "Session 7 tips", "Later in session 7", "Session 8 tips".
2. nonmatchings/session7/BRIEF.md (tools, output layout, rules: they all still apply,
   with the session-9 paths below) and nonmatchings/session7/NOTES.md (grep for each of
   your addresses: every earlier attempt is there).
3. docs/toolchain.md "Session 6" and "Session 7" (build modes), docs/context-only-plan.md.
4. nonmatchings/session6/INDEX.md: grep it for your addresses.
5. nonmatchings/session8/BRIEF.md "What is new for session 8" (dump reading: it still applies) and
   nonmatchings/session8/NOTES.md (grep for each address: the diagnosed cause is usually there).
   docs/workflow.md "Session 8" lists the tools in tools/matching/ (*_s8.py; set WDIR and WTAG).

## Your list
YOUR_LIST. Every function here has been tried by two or more workers (sessions 6-8). Read every
existing draft of it (`ls nonmatchings/session*/*ADDR*`) and start from the closest.
First re-verify the draft's word count (copy to src/<mode>/.WTAG_x.c, run
`python3 tools/checkfile.py src/<mode>/.WTAG_x.c -v`); drafts may depend on CONTEXT_ONLY
copies they name in their first line.

## Step 0 (do this first, for every function in your list): callee-prototype sweep
For the closest draft: list every callee it calls, read each callee's real argument
registers with `python3 tools/matching/arity_s8.py func_XXXXXXXX ...` (linear scan: check
branches by eye) and whether callers read v0/f0 after the call, and compare with the
draft's prototypes (and with the prototype in the matched src/ file that defines the
callee, if any). Fix arity and return type (void vs s32, f32 return) one callee at a
time and re-count. Also try the callee CONTEXT_ONLY above the caller if not done yet.
Session 8 matched 3 functions and shrank several drafts this way alone.

## Session 8 method (still the main lever): go below the source level
Earlier sessions exhausted statement orders, mode sweeps and single-flag sweeps on most of
these. Your edge is reading gcc's own dumps to see WHICH pass makes the difference, then
choosing a source shape that changes that pass's input:
- Dumps: add `-da` (all) or e.g. `-dS -dR -dl -dg -dM` via
  `KH1_EXTRA_CCFLAGS="-da" python3 tools/checkfile.py F` won't keep them; instead run the
  compiler directly: `tools/toolchain/ee-gcc2.96/bin/ee-gcc -S -x c <the cflags from kh1.toml
  for the mode> -ffunction-sections -Iinclude -da -o WDIR/x.s F` in WDIR (dumps land
  next to the .s as x.c.rtl, .sched, .lreg, .greg, .sched2, .dbr ...). Compare the pass
  where ours first differs from what the original asm implies.
- local-alloc vs global-alloc (Later in session 7), sched1 store tie-break rules
  (ready stores whose value dies first, in source order; LUID ties), reorg's
  fill_simple/fill_eager/steal rules, jump2 cross-jumping (takes the first match),
  loop.c giv/biv decisions, cse following jumps.
- Ask "what source would a 2002 Square programmer have written": macros expanding to
  repeated expressions, inline helpers (static inline), asserts compiled out
  (`do { } while (0)`), debug counters, unused locals, enum/switch shapes, bitfields.
- A shape that reaches 0 words only with a hack (empty asm barrier, an address-taken
  label with no data word in the binary, a flag) is a near miss: save it, say what
  it needs, do not count it as a match.

## Where your output goes (session 9 paths)
- WDIR = /tmp/claude-0/s9/WTAG (create it). Helpers and dumps there.
- Matched code: WDIR/out/<mode>/FILEBASE.c (FILEBASE = text_XXXX0000_s9_WTAG.c, by the
  function's 64 KiB region). One file per mode and region, starting with
  `#include "common.h"`, with the CONTEXT_ONLY copies it needs. Only verified functions:
  checkfile MATCH on a copy at src/<mode>/.WTAG_chk.c. Rodata functions: verify with
  a copy of tools/matching/wqb03_rr.py ADDR (fix its /tmp paths into WDIR) and mark
  them `/* rodata */`.
- Near misses better than the best existing draft, or with a new finding:
  WDIR/near/<addr>_<N>w.c, first line a comment: words off, mode, context, what is off.
- Scratch tests: dot files src/<mode>/.WTAG_*.c only; delete them at the end.

## Rules
- No `make`, no `git`, no edits outside WDIR and your own dot files in src/.
- The machine has 4 cores shared by several workers: at most 1 compile process at a time
  from you (flagsweep -j1, batch tools sequential). No sleep/until polling loops; run long
  jobs in the foreground with a timeout, or in the background and check the log once.
- Never kill processes you did not start. No copying from other decomp projects.
  No inline-asm bodies for ordinary C (VU0/MMI/sync/cop0 only).
- Do not call any mcp__hearthbot__ tool.
- Time-box: about 25 serious attempts per function without progress, then move on. Be
  direct about ones that look like a compiler/assembler oddity rather than source shape.

## Report back (final message, concise)
1. Matched: names, mode, out/ file paths (and flag/context needed).
2. Near misses saved (path, words off, what is off).
3. Skipped/stuck with the reason (the pass responsible, if you found it).
4. New facts, one line each (tips other workers can reuse).

## Session 9 additions
- Big drafts (31+ words): count with tools/matching/lcs_s8.py, not position counts. Work
  the closest first; a draft that drops from 300 to 30 words is real progress worth saving.
- Functions without a draft (0012e1b0, 001c53c8): start from `python3 tools/kh1tool.py m2c`.
- Do not stop after the sweep: give every function in your list a real attempt, closest first.

## Round 2 (second pass, fresh eyes)
Every function on your list was attempted in round 1 of this session by another worker;
read nonmatchings/session9/NOTES.md (their diagnosis) and nonmatchings/session9/*ADDR*
(their saved draft) before anything else. Use WTAG r2_N; WDIR /tmp/claude-0/s9/r2_N.
- **Sibling port first.** Round 1's best lever (5 of 15 matches): find already-matched
  functions in src/ that touch the same globals, call the same callees or build the same
  message/packet type (`grep -rl D_XXXXXXXX src/`, same 64 KiB region, same callee list),
  and rewrite the draft in that sibling's style: plain globals instead of pointer locals,
  the sibling's struct/array declarations and types (`u8 X[][112]`, bitfields, aligned(8)),
  its store order, its helper-free written-out loops, its constants inline.
- Then the round-1 levers in NOTES.md (shared `goto` tails to cut refs, call results in
  their own local, re-reading a pointer argument instead of a local copy, `= 0` next to the
  loop, chained assignments for store order, two-insn arms to block if-conversion).
- A different angle beats repeating round 1's: if round 1 swept statement orders, change
  types, declarations and expression shapes instead.
