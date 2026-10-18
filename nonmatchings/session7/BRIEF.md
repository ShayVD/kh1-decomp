# Session 7 worker brief (kh1-decomp)

You are a hand-matching worker. Repo: /home/claude/kh1-decomp (built, toolchain ready,
the original ELF SLPS_251.98 is in the repo root; never copy it anywhere).

FIRST read, in this order:
1. docs/matching-tips.md (tricks; "Session 6 tips" at the end)
2. docs/worker-brief.md "Tools" and "Rules" sections, and "Session 6: facts and tricks"
   (skip the long batch log unless you need it; grep it for your addresses)
3. docs/toolchain.md "Session 6: more build modes" and docs/context-only-plan.md
4. nonmatchings/session6/INDEX.md and NOTES.md: grep them for each of your addresses.

## Your list
YOUR_LIST (columns: words off by session 6, instructions, address, name, session-6 draft,
session-5 draft). Drafts are in nonmatchings/session6/ and nonmatchings/session5/; the first
line of each says what is still off and which build mode / CONTEXT_ONLY callees it needs.
Rows without a draft start from `python3 tools/kh1tool.py m2c NAME`.

These drafts already resisted mode sweeps, callee stubs, return-type sweeps and the
permuter in session 6. Spend your effort on things session 6 did NOT do:
- **Single-flag sweep** (new): `python3 tools/matching/flagsweep.py -j2 DRAFT.c` checks a
  draft under every build mode it names with each of ~35 gcc flags added
  (-fno-sched-interblock, -fno-schedule-insns, -fno-regmove, -fno-rerun-cse-after-loop, ...).
  The lead already swept every draft as it was at the start; re-run it on YOUR improved
  drafts (a draft that gets closer can start matching under one flag). A match that needs
  a flag is reported, not kept silently: say which flag(s) reach 0.
  `KH1_EXTRA_CCFLAGS="-fno-regmove" python3 tools/checkfile.py F` does one check.
- **Brute-force statement orders** with tools/matching/perm.py / hill4.py / popt.py
  (copy into your dir and fix their /tmp paths): independent statements, declaration
  order of locals (it sets spill slots and allocation priority), store order.
- **Callee prototypes**: return types (void/s32/u8/pointer) and argument counts of every
  callee, unprototyped `f()` declarations, and CONTEXT_ONLY copies of every callee above.
- **Types**: signedness and width of every field and local; struct vs array vs pointer
  temporaries for the same address (`T *p = &D[i];` changes whether `lui; addiu; addu`
  stays split or folds into `lw sym(reg)`).
- **Equivalent control flow**: for vs while vs do-while, early returns vs nested ifs,
  `goto` shared tails, switch vs if chains, `!x` vs `x == 0`.

## Facts found at the start of session 7 (by the lead)
- The n32 "mixed addressing" functions (0x212cc0, 0x2134c8, 0x217000) are NOT a different
  compiler: eight other period ee-gcc builds (2.9-991111, 991111b, 991111-01-dtls13010,
  SN 2.95.2-273a/274, 2.95.3-107) fail all six functions that match in src/hand/n32 under
  2.96 -mabi=n32. In 0x212cc0 the remaining split `la; addiu 64; addu` site
  (D_003E3D70[k].x40) reads like a pointer temporary in the source, not an ABI effect.
- The first sweep matched 4 drafts with one extra flag; they now have build modes:
  `hand/nosi` (-fno-sched-interblock: func_001c1718), `hand/nogcse_nosi`
  (func_0010ec08), `hand/nogcse_nosib` (-fno-gcse -fno-optimize-sibling-calls:
  func_0010cf38), `hand/faddr` (-fforce-addr: func_00231ea0). -fno-sched-interblock also
  brought func_001d0380 to 6 words, func_00144d08 to 15 and func_00240910 to 17: when sched1
  hoists an instruction across a branch where the original does not, try it.

## Where your output goes
- Your own directory: WDIR (create it). Keep helpers there.
- Final matched code: WDIR/out/<mode>/FILEBASE.c, where <mode> is the build-flag
  directory under src/ it matched in (`hand`, `hand/nostrict`, `hand/nofill`,
  `hand/nostrict_nofill`, `hand/nogcse`, `hand/nostrict_nogcse`, `hand/n32`,
  `hand/n32_nogcse`, `hand/n32_nostrict`; SDK: `sdk/gcc991111`, `sdk/libc`, ...
  see kh1.toml). One file per mode; start each with `#include "common.h"`. Include the
  CONTEXT_ONLY copies the file needs. Only verified functions go in (checkfile MATCH on a
  copy at src/<mode>/.WTAG_chk.c). A match that needs an extra flag goes in
  WDIR/out/flag/<flag-without-dashes>/<mode>/FILEBASE.c.
  Rodata functions (jump tables, float/double/string constants) count when
  tools/matching/wqb03_rr.py ADDR (rodata placed at its real address) says MATCH (copy it
  to your dir and fix its /tmp paths first; it is not safe to run two at once in one dir);
  mark them `/* rodata */` above the function.
- Scratch tests: dot files src/<mode>/.WTAG_*.c only (the build ignores dot files).
  Delete yours at the end. Never touch other workers' dot files.
- Near misses worth keeping: WDIR/near/<addr>_<N>w.c with a first-line comment saying
  what is still off and which mode/context/flag it needs. Only write one when you got
  closer than the session-6 draft or learned something new.

## Rules
- No `make`, no `git`, no edits outside WDIR and your own dot files in src/. Other
  workers share this repo and machine (4 cores): at most 2 compiles in parallel
  (flagsweep -j2).
- Never kill processes you did not start (no pkill/killall).
- No copying from other decomp projects. No inline-asm bodies for ordinary C (VU0/MMI/
  sync/cop0 instructions only). Hand-written assembly: flag it and skip.
- Do not call any mcp__hearthbot__ tool.
- Give each function a fair try (~20 attempts without progress, then move on); work the
  list in order (smallest words-off first). Be direct about hopeless ones.

## Report back (final message, concise)
1. Matched: names, mode, and the out/ file paths (and the flag, if one was needed).
2. Near misses saved (path, words off, what is off).
3. Skipped with a short reason.
4. New facts (regions, flags, struct layouts, layout splits), one line each.

## Added during session 7 (from finished workers)
- Rows without a session-6 draft may still have a session-5 draft (column 6) or none:
  start from `kh1tool.py m2c` then. Rows of 0x25xxxx-0x272xxx are SDK: use the sdk/ modes.
- sched1 moves instructions across blocks only in functions with <= 10 basic blocks:
  writing a shared tail in both branches adds blocks and stops the motion (jump2 merges
  the copies again, so the size does not change). Source-level alternative to
  -fno-sched-interblock (func_001d0380).
- `bnez; move v0,zero; li v0,1` epilogues: a `goto r1;` to a shared `r1: return 1;`
  label stops if-conversion to sltiu (func_00135bb0).
- Index loops `f(&p->items[d[5 - n + i]])` beat pointer walks `q = d - n + 5; do..while`
  (func_00245b08). Moving `x++` into a later `else if (++x >= n)` changes sched1 order.
- Writing an inline helper's body out in place, with function-level locals, changes the
  argument registers (func_0018e348). Ternary min helper vs if-clamp changes FP regs.
- Returning a callee's result instead of void keeps v0 live (func_0023fad0). A constant
  local as s32 instead of u64 changes s-register allocation (func_0020b6a8).
- Mode `hand/nostrict_norcse` (-fno-strict-aliasing -fno-rerun-cse-after-loop) exists now
  (func_0012d468).
- Never write sleep/until polling loops: they stop on a permission prompt while the user is away. Run long jobs with run_in_background and wait for the notification, or check a log once with tail and keep working.
