# Session 6 worker brief (kh1-decomp)

You are a hand-matching worker. Repo: /home/claude/kh1-decomp (built, toolchain ready,
the original ELF SLPS_251.98 is in the repo root; never copy it anywhere).

FIRST read, in this order:
1. docs/worker-brief.md  (job, tools, rules, ~300 matching tricks; its /tmp/claude-0/s/...
   tool paths from session 5 are GONE; the surviving copies are in tools/matching/,
   see tools/matching/README.md; some have hard-coded /tmp paths: copy a script into your
   own dir and fix its paths before using it)
2. docs/matching-tips.md (summary)
3. nonmatchings/session5/INDEX.md  (grep it for each of your addresses: it says which
   callee must be defined above a caller, and how far off each draft was)

## Your list
YOUR_LIST (columns: name, instruction count, segment, flags, session-5 draft files for
that address if any). Drafts were found by address suffix; also
`ls nonmatchings/session5 | grep <last 4 hex digits>` yourself. A draft is a starting
point: many are 2-20 words off.

Work in list order, but do the ones with a draft or under ~200 instructions first if you
like. Give each function a fair try (~15 attempts without progress, then move on; huge
functions get proportionally more). Be direct about hopeless ones (inline VU0 asm
renderers, hand-written asm): flag and skip.

## NEW in session 6: CONTEXT_ONLY (callee-earlier effect solved)
gcc 2.96 changes a caller's code (bnel->bne, beqzl->beqz, register choice) when the
callee is defined ABOVE it in the same file. You can now put a copy of the callee above
the caller without it being placed in the build:

    CONTEXT_ONLY s32 func_00123456(s32 a) { ...callee body... }   /* from common.h */
    void func_00123500(void) { ... func_00123456(1) ... }        /* the real match */

- The CONTEXT_ONLY copy is compiled but never placed; calls resolve to the original
  address. The copy may be a matched function from another src/ file (copy its body and
  types) or an unmatched callee's closest draft; only its register usage matters. Never
  make it static.
- `python3 tools/autodecomp.py try NAME --file F --out-dir D --diff` and
  `python3 tools/checkfile.py F [-v]` both handle CONTEXT_ONLY callees (no more
  "relocation truncated"). checkfile prints MATCH/FAIL for every non-ctx function.
- Several session-5 callers are waiting on exactly this (INDEX.md "needs X above").
  Their matching code from session 5 was lost, so re-derive it.

## Where your output goes (IMPORTANT, differs from docs/worker-brief.md)
- Your own directory: WDIR (create it). Keep helpers there.
- Final matched code: WDIR/out/<mode>/FILEBASE.c, where <mode> is one of
  `hand`, `hand/nostrict`, `hand/nofill`, `hand/nostrict_nofill` (the build-flag
  directory under src/ it matched in). One file per mode; start each with
  `#include "common.h"`. Include CONTEXT_ONLY copies the file needs.
  Only verified functions go in (checkfile MATCH on a copy at src/<mode>/.WTAG_chk.c).
  Rodata functions (jump tables, float/double/string constants) count when
  tools/matching/wqb03_rr.py (rodata placed at its real address) says MATCH; mark them
  `/* rodata */` above the function.
- Scratch tests: dot files src/<mode>/.WTAG_*.c only (the build ignores dot files).
  Delete yours at the end. Never touch other workers' dot files.
- Near misses worth keeping: WDIR/near/<addr>_<N>w.c with a first-line comment saying
  what is still off and which mode/context it needs.

## Rules
- No `make`, no `git`, no edits outside WDIR and your own dot files in src/. Other
  workers share this repo and machine (4 cores): at most 2 compiles in parallel.
- Never kill processes you did not start (no pkill/killall).
- No copying from other decomp projects. No inline-asm bodies for ordinary C (VU0/MMI/
  sync/cop0 instructions only).
- Do not call any mcp__hearthbot__ tool.

## Report back (final message, concise)
1. Matched: names, and the out/ file paths.
2. Near misses saved (path, words off, what is off).
3. Skipped with a short reason (asm/VU0, too big, etc.).
4. New tricks or facts (new nostrict/nofill regions, struct layouts, layout splits:
   "symbol X is really two functions at A and B"), one line each.

## Added during session 6
- Two more build modes: `hand/nogcse` (-fno-gcse) and `hand/nostrict_nogcse`. Sign: the
  original repeats a load (or a constant held across branches) that gcse merges.
  func_0014b550 matches only there. Possible region 0x142e30-0x14b550; the script VM
  func_001ca368 also matched with -fno-gcse in session 5.
- Probe EVERY callee for the callee-above effect (stub each one above the caller), not
  just the call right before the bad branch: the effect can reach branches before the call.
- Two more modes: `hand/n32` and `hand/n32_nogcse`: -mabi=n32 -DKH1_N32 on the C->asm
  step only. Use them around 0x20dd38-0x2173xx when the original keeps
  `lui; addiu; addu` for a symbol added to a register (D_003F2C40, D_003E3D70 groups)
  where we get one `la`-style macro. func_002114f0/00214130/00214290 match there.
- Also `hand/n32_nostrict` (n32 + -fno-strict-aliasing). func_001f9e48 and func_001fa8b0 (0x1f9xxx-0x1faxxx) show the same unfolded table base; try n32 modes there.
