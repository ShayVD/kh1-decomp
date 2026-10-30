# The EE overlays: matching build (phase 2, vita-port-plan 5.2)

KH1 loads 12 MIPS overlays from KINGDOM.IMG into the area at 0x00F20000 (one at a time):
dkmovie, dktitle, gb, wm, xl_limit, xs_bambi, xs_dh_break, xs_dumbo, xs_genie, xs_mushu,
xs_simba, xs_tink. They are game code that is not in SLPS_251.98, so they are matched
against the user's own overlay files the same way the main ELF is matched against the ELF.
Session 131b (2026-10-26) built this; dktitle.x is left to the phase 5 session that takes it.

## Files

| Path | What | Committed |
|---|---|---|
| `out/overlays/NAME.x` | the user's overlay files, from their own disc (`tools/shift/extract_kingdom.py`, or copied; `KH1_OVERLAYS` points elsewhere) | never |
| `ovl/overlays.tsv` | size and SHA-256 pin of each file (like kh1.toml's pin of the ELF) | yes |
| `ovl/NAME/layout.tsv` | the overlay's functions (addr, end, size, name), first written by `tools/ovl/build.py layout NAME`; hand edits allowed | yes |
| `ovl/NAME/functions.tsv` | optional names for the overlay's own functions and data, merged over the main functions.tsv | yes |
| `ovl/NAME/**/*.c` | matched C (`auto/` from autodecomp, hand files anywhere under the directory) | yes |
| `out/ovl/NAME.elf` | the overlay wrapped as an ELF (one PT_LOAD at 0x00F20000) by `build.py wrap` | never |
| `out/ovl/NAME/` | the overlay's build: objects, link, patched copy, objdiff units, sigs, rank, autodecomp reports | never |

## Commands

```sh
make ovl                       # every overlay with sources: build, link, patch, byte-compare
make ovl OVL="xs_bambi gb"     # just these
make ovl-report                # objdiff-cli report per overlay (every match must say 100%)
make ovl-progress              # matched / functions per overlay

# the main tools on an overlay: set KH1_OVL
KH1_OVL=gb python3 tools/kh1tool.py asm func_00f20108
KH1_OVL=gb python3 tools/kh1tool.py m2c func_00f20108
KH1_OVL=gb python3 tools/sigs.py && KH1_OVL=gb python3 tools/kh1tool.py rank --limit 0
KH1_OVL=gb python3 tools/autodecomp.py batch --segment all --max-insns 100000 \
    --report out/ovl/gb/autodecomp.tsv --write          # matches into ovl/gb/auto/
KH1_OVL=gb python3 tools/autodecomp.py try func_00f20108 --diff
```

`KH1_OVL=NAME` (tools/kh1tool.py) switches the sources to `ovl/NAME/`, the layout to
`ovl/NAME/layout.tsv`, the original to `out/ovl/NAME.elf` and the output to `out/ovl/NAME/`.
Everything else is the main pipeline: `gen`, `split-rodata`, `fix-obj`, `link-script` (rodata
inferred from the %hi/%lo pairs), `patch`, `verify`, `objdiff`. `tools/ovl/ovl.mk` is the
overlay's Makefile (kh1.ld with its INCLUDE paths pointed at `out/ovl/NAME/gen/`).

Names: overlay functions are `func_00f2xxxx`, overlay data `D_00F2xxxx`, calls into the main ELF
keep the main names (`func_00137330`, `sceVu0CopyVector`). In overlay mode the asm printer
names main-ELF code addresses `func_` too. sigs.py merges the main ELF's guessed prototypes
(out/sigs.tsv) with the overlay's, so m2c knows the argument counts of main-ELF callees.
The same address means different code in each overlay, so these names collide across
overlays; the shiftable pass (phase 4) and the Vita link must prefix them per overlay
(for example `gb_00f20108`), each overlay being its own module.

## Layout finder (tools/ovl/inventory.py `find_functions`)

Starts: the entry (first byte), every jal target, and what follows an unconditional transfer
when no branch reaches past it. The code ends after the last `jr ra`; then it grows over
(1) a function that a call or tail call (`j`) from the code reaches right after that end
(only nop padding between), and (2) a function right after the end that sets up a frame and
saves ra (reached only by pointer). Case (1) is xs_bambi's last function (0x00F20838, reached
by a tail call), case (2) the last functions of xl_limit, xs_dumbo, xs_mushu and xs_tink.
The data after the code starts with GIF tags in every overlay (checked by eye). A leaf
function reached only by pointer after the end would still be missed; fix layout.tsv by hand.

## Compiler

The game's own (ee-gcc 2.96, `-O2 -G0`, the kh1.toml default) matches the overlays: the first
autodecomp pass matched about 40% of the functions of the eight small overlays straight
from m2c. Two kh1.toml flag modes are used by a few overlay functions (session 131b):

- `nofill` (delay slots not filled): dkmovie's DMA register writers, gb func_00f4d880, the
  xs_dh_break random float (the main ELF's rand.nofill.c).
- `nosib` (`-fno-optimize-sibling-calls`, new): wm's sound helpers func_00f2fe40,
  func_00f2fe88, func_00f454b0 end in `jal` + return where -O2 would tail-call.

A hand file named `func_X.<mode>.c` is compiled with that mode (`KH1_MODE=<mode>` for
autodecomp; hand.py and twins.py pass it on from the draft's or the source's name).

## Hand matching (session 131b)

```sh
python3 tools/ovl/hand.py show gb func_00f3bab0          # asm + autodecomp's closest draft
python3 tools/ovl/hand.py try  gb func_00f3bab0 d.c      # compile a draft (ovl.h prepended), diff
python3 tools/ovl/hand.py keep gb func_00f3bab0 d.c      # on a match: ovl/gb/hand/func_00f3bab0.c
python3 tools/ovl/hand.py perms gb func_00f3bab0 d.c     # every order of the lines between //{ and //}
python3 tools/ovl/twins.py [NAME...]                     # copy matched C to same-shape functions
python3 tools/ovl/drafttwins.py --apply                  # port near-miss drafts between wm and gb twins
```

twins.py: gb and wm share most of their code (and the summons share helpers), so every
match is tried on the functions with the same instructions (symbols, call targets and
labels masked; large literals masked as a fallback) in every overlay. Run it after each
`make ovl`.

drafttwins.py (`python3 tools/ovl/drafttwins.py [--apply] [--dir nonmatchings/session141] [wm gb]`)
does the same for near misses that do not match yet. It pairs each draft in DIR/A with each
draft in DIR/B whose target has the same mnemonic sequence. It scores both drafts with
`hand.py try`, ports the better one onto the other with port.py, and prints the port's score.
With `--apply`, each improving port that has no unmapped symbols replaces its twin's draft:
a new header line comes first, then the twin's old header. Each replacement is committed on
its own, with `$COMMIT_TAIL` appended to the commit message. A port that matches is only
written and reported, so promote it with `hand.py keep`.

In round 41 the first run improved 31 gb and 6 wm drafts, for example wm func_00f55d78
from 223 to 27 and gb func_00f51360 from 11 to 3. Rerun it after a draft improves, so the
gain reaches its twin.

autodecomp's variants (tools/permute.py) added for the overlays: `callee_stubs` (overlay
callees at lower addresses as empty `CONTEXT_ONLY` definitions: callee defined above
changes gcc's branch-likely and slot choices), `data_defs` (overlay data as `CONTEXT_ONLY`
zero-initialised definitions: gcc then fills slots with %lo loads), `float_args` (bit
patterns passed as float literals, also any pattern in a libvu0 float parameter),
`merge_splits` (m2c's var_a3 / var_a3_2 as one variable), `sort_stores` (runs of global
stores in address order), `void_self` (m2c's `Duplicate return node`: the function is
void), and `pad_frame` (an unused aligned local to reach the original frame size).

What the hand matches needed, most often first:

- Real types: structs with pad arrays instead of M2C_FIELD, `OvlVec` / `OvlMtx` locals,
  the PlatVu0* wrappers. dkmovie's big movie work struct (fields at 0x3DD48..0x3DF5x) shows up
  in m2c as `&D_0003DF44 + arg0`; it is a struct pointer.
- Store order: m2c's statement order is the scheduled order, not the source's. Fields in
  struct order, chained `a = b = c = 10.0f;`, or `hand.py perms`.
- Loops: m2c's countdown do-while with a pointer is `for (i = 0; i < N; i++) arr[i]...`;
  `E *e = &arr[i];` and `arr[i].f` compile differently (try both).
- Returns: void functions (m2c returns a leftover $v0), a missing return in an s32
  function, a pointer returned where a bool is tested, `if (x & 1) return 1; return 0;`
  versus `return (x & 1) != 0;` (the first keeps `sltu`), a narrower callee return type
  that blocks a tail call.
- Arguments m2c lost or added: pass-through arguments, the variadic `func_001c01b0(s32,
  void (*)(), ...)`, an argument computed into a local before the call.
- Float literals: gcc 2.96 reads some decimal spellings one ulp off, and no one length is
  always right: wm func_00f2f188 needs `0.349065810442f` (12 digits), the pi of wm's
  RotMatrixX calls `3.141592503f` (10; `3.14159250259f` is one ulp off), `0.3f` gives the
  target's 0x3E999999. Try a few spellings.
- Frame size: an unused local OvlMtx or array (16 / 64 / 96 bytes too big: OvlVec / OvlMtx).
- Register choice, when nothing else works: a local register variable
  (`register s32 n KH1_REG("s1") = 5;`, include/common.h), with a comment saying why
  (gb func_00f29720, wm func_00f553b8; the main ELF does the same).
- Flag modes: try `nostrict` (a reload after a store through a struct pointer), `norlo`
  (a counted loop gcc would reverse into a countdown), `nofill`, `nosib`.
- Callee results: return a memcpy-like callee's result, or declare a callee non-void, when
  $v0 stays occupied in the original; an unprototyped `void f();` when one function is
  called with 3 and 4 arguments.
- Statement order search: `hand.py perms` for up to 6 lines; the workers' hill-climbing and
  one-line-position scripts for longer runs (session 131b's scratch, not committed).
- Struct copies through ldl/ldr/sdl/sdr are plain assignments of 4-aligned structs; a u128
  written then read by word needs a union.
- `(u32)(x - 1) == 48` keeps a subtraction gcc would fold; `switch (id - 1)` too.
- Address association: `(i*0x590 + 0x540) + base` needs the sum written in two steps;
  a base pointer local (`E *e = D; &e[i].sub`) keeps `base+off` from folding into %lo.

Near misses and open questions are in the session's notes (docs/next-session.md). Session
141 settled the two recurring ones: the "endless loop without $ra" (gb func_00f50db0, wm
func_00f77ea8) was never a function, but case 9 of the main state machine's switch (below),
and gb func_00f25a68 is wm func_00f35800 with gb's own literal (0.17453292f).

### Session 141 additions

- **The layout can split a function at its switch.** A `jr` through a jump table followed by
  more code looks like a function end to the layout finder, so the case blocks after it
  became fake functions (gb func_00f509f8's cases f50be8 / f50c58 / f50cc8 / f50db0, wm
  func_00f77af0's f77ce0..f77ea8). Before hand-matching something odd (no prologue, never
  called, `$ra` not saved), check whether a jump table (`lw` + `jr` with a D_ table) points
  into it; merge it back into layout.tsv.
- **CONTEXT_ONLY callees by hand.** `CONTEXT_ONLY void f(u8 *a0) {}` above the caller changes
  branch-likely and slot choices (dktitle func_00f21068 needed func_00f209b0's). Try each
  callee alone and all together (session 141's ctx.py did that mechanically).
- **Two `li a0,K` arms that share one `jal`** (crossjumping) mean the source calls the
  function in each arm of the if/else or switch: write the call in every case
  (gb func_00f20290, wm func_00f47388).
- **Callee prototypes decide store order and registers.** A callee returning a pointer
  (gb func_00f509f8's `void *func_00f445a8(...)`), or a vtable slot returning s32, fixed the
  order of stack-argument stores and the register holding the result.
- **The rank.tsv "hard" functions** in gb / wm are mostly ordinary C with a few `kh1_u128`
  arguments or copies (`por $aX,$zero,$zero` is a u128 zero argument). Only dkmovie's
  MMI / sq movie routines (ovl/dkmovie/asm/mpeg_mmi.s, tools/asm_export.py --symbolic) were
  hand-written.
- **Porting between gb and wm.** twins.py needs the same instruction shape; when the
  shape differs only in symbols and %hi/%lo data addresses, mapping the symbols by position
  in the asm (lui base + offset included) and recompiling the twin's C ports it (tools/ovl/port.py SRC_OVL SRC_FUNC DST_OVL DST_FUNC in.c
  out.c; tools/ovl/portall.py A B tries every matched function of A on B and keeps matches. It
  gave wm func_00f50968, func_00f55ad8, func_00f781c0).
- autodecomp's `--diff` now runs `objdump -z`: without it runs of zero words (nops) were
  folded out and the side-by-side diff went out of step.
- **sq / lq around a call is a caller-save spill.** gcc keeps a value live across a call in
  a t register and saves it as a whole 128-bit quadword (gb func_00f3e388's t2 / t3 around
  func_00f3f548, gb func_00f24780's grid base). The source is plain C; the work is the
  register allocation.
- **A `v0` set and never read before `jr ra` is a return value** (gb func_00f38408 returns
  `p + 24`; the "unused" `addiu v0,s4,384` was it).
- **Pointer copies change allocation and jump threading.** gb func_00f3e388 matched only when
  the header was read through a copy (`hh = h;` after the first call, every later use through
  `hh`): the stage-1 bound moved from v1 to v0 and the early exit stopped being threaded past
  a reload. The permuter found it (new_var); try it by hand when a loop guard's register is off.
- **An inner loop whose base goes straight into an s register** (no `move s0,t0`) increments
  the pointer itself: `for (i = 0; i < n; i++, e++)`, not `e[i]` (gb func_00f3e388 / f3e0d8).
- **GIF packet builders** (gb func_00f42cf8, func_00f41dc8, func_00f38408): a union of
  `kh1_u128` / `u32 w[4]` / `{u64 lo, hi}` per qword and an inline `ad(q, data, reg)` that
  stores both halves keep the per-qword address registers; incremented-pointer calls
  (`f(o++, ...)`) give the `addiu s7,sp,N` before each `jal`.
- **The permuter's base.c can lose `do {} while (0)`** and some casts (pycparser): check
  that base.c still holds what you gave it.
- **Batch 4 patterns (session 141, workers' notes in nonmatchings/session141/wm/NOTES-wwm*.md):**
  - An unfolded `addiu aN,aM,8` shared by two branches is an index kept in its own local
    (gb func_00f30d80 / func_00f29c40: `k = q * 4 + 8; x = T[k]; z = T[q * 4 + 10];`).
  - `(f >> 8) & 0xF` tests, and `ld; dsrl32; andi 0xffff; andi 0xf` reads, are u16 bitfields
    (`lo:8, kind:4, hi:4`); a u64 member gives the struct the 8-byte alignment for the `ld`.
  - An `lhu` + `andi 1` + `andi 0xffff` flag test is a plain u16 field read as
    `(u16)(flags & 1)`; an `ldl/lwl` struct copy is a 2-byte-aligned (all-u16) struct.
  - Extra register copies that "can't be produced" came from reusing an index variable for
    the next lookup (`j = i; i = g->c[j].t;`, wm func_00f4b1e8 family and its gb twins).
  - A constant kept in its own local before a loop (`u32 ff = 0xFFFFFF;` in wm func_00f68ec0,
    gb func_00f41dc8, wm func_00f792c8) moves its `lui` to where the original has it.
  - Indexing an output array (`D[n]`, `n++`) instead of advancing a pointer reverses which
    `lui` gets the higher pseudo (wm func_00f355a8 / func_00f5e178).
  - Writing a store twice (`xf.pos[3] = 1.0f;` first and last) lets dead-store elimination
    keep the late copy while the scheduler hoists it (wm func_00f606a0).
  - A stray `move a0,...` before a call often means the callee takes fewer arguments than
    m2c guessed (gb func_00f299c8's func_00f291f0, wm func_00f21600's func_00f66240).
- **Batch 5 patterns (session 141):**
  - Hill-climbing statement order (randomly swap or move lines inside chosen blocks, keep a
    change when the differing-word count does not grow) beats plain random orders for
    scheduling-only diffs (wm func_00f43ae0 from 20 words to a match).
  - Runs of independent stores are reordered by the scheduler in no simple pattern; generating
    every order of the block (24 to 144 files) matched wm func_00f21c48 / func_00f5d6b0.
  - Packets whose entry addresses are all computed from the base first (`addiu tN,v0,16k`) come
    from an indexed inline `put(p + 2k, a, b)`; chaining `p += 2` gives stepwise addresses
    (wm func_00f2a4c0). A second packet wants its own pointer local (wm func_00f206f0).
  - `x + -100.0f` loads a stored -100.0f constant where `x - 100.0f` does not (wm func_00f5d6b0);
    a bare `sqrt.s` is `PlatSqrtf` from platform/math.h, not `sqrtf`.
  - A loop written `for (; a = f(), b = g, !(cond);) {...}` gets the bottom test and initial
    jump of a goto loop but keeps the loop notes, so invariants are hoisted (wm func_00f70828).
  - `if (a == at) v = a * 0.5f; else {...; v = a * 0.5f;}` merges into one multiply
    (wm func_00f6a530).

## Branch-likely vs plain branch (session 141, wwm1 round 17)

A conditional branch whose delay slot holds the first insn of its *taken* path (reorg's
fill_slots_from_thread steals it and retargets the branch past it) comes out as a plain
branch (`bltz`, `beq`, `bc1f`) when that insn is harmless on the not-taken path, and as a
branch-likely (`bltzl`, `beql`, `bc1fl`) otherwise. "Harmless" means: the insn cannot
trap, and the register it sets is not in the live set reorg computes for the fallthrough.

How reorg computes that live set (resource.c `mark_target_live_regs`, traced in gdb on
cc1, which has symbols, the way tools/matching/gdb_s13/rg.py does it):

1. It takes the registers live at the start of the extended basic block (back to the
   previous BARRIER) and steps forward to the fallthrough. A register that dies at the branch
   itself (REG_DEAD on the branch) only becomes "pending dead" until the next CODE_LABEL, so
   it still counts as live just after the branch. The branch's own operand (the `k` of
   `if (k >= 0)`) and anything set in the same block stay live this way.
2. Then `find_dead_or_set_registers` scans forward from the fallthrough. It drops registers
   that are set before they are read. **A call kills the call-clobbered registers (v0, v1,
   a0-a3, t0-t9) only when it cannot throw.** gcc 2.96 marks a call `REG_EH_REGION 0`
   (nothrow) only when the callee was already defined earlier in the same file. A call to
   an external function stops that kill, so a v0 / v1 / aN / tN set by the stolen insn stays
   live and the slot has to be annulled.

What this means for a source shape:

- **The original has a plain branch, ours the -likely one, and the slot insn sets a
  call-clobbered register:** look at the first call on the fallthrough path. Its callee was
  defined above the function in the original file. Give it a `CONTEXT_ONLY` definition above
  ours, not just a prototype (include/common.h: `CONTEXT_ONLY void f(OvlMtx a0, s32 a1) {}`).
  The body is irrelevant; an empty one, a non-empty one and an old-style `void f() {}` all
  work. A definition *after* the function, `__attribute__((const))`, `pure` and `noreturn`
  do not; 2.96 ignores `nothrow`. gb func_00f350d0 went from 1 word to a match this way
  (`bltzl v1` -> `bltz v1`, the stolen insn `lw v1,%lo(D_00F56DC0)`, the first fallthrough
  call func_00f33d18).
- The same definition also fixed gb func_00f35a80: three `beqzl` became the original's
  `beqz`, with func_00f357b0 and func_00f358b8 defined above.
- **It works in the other direction too.** In gb func_00f34aa8 the original has a `beql` (case
  44 of a switch, with `move a0,sp` stolen from the case body), and ours had a plain `beq`
  filled from the default path. A CONTEXT_ONLY func_00f33d18, the case body's first call,
  matched it (65 words -> 0; the slot change shifted every later address). So whenever a
  near miss differs in branch-likely use or in a slot near a call, try CONTEXT_ONLY
  definitions of the calls next to the branch, both one at a time and together.
- **The original has the -likely one, ours plain:** the original's fallthrough had a reader of
  that register before its first call, or its first callee was not defined above (the
  session 13 tip in docs/matching-tips.md is the same rule from the other side).
- A callee-saved destination (s0-s8: an `i++` stolen from the loop latch) stays live across
  any call, so that slot is always annulled unless the fallthrough sets it first.
- The slot insn must not trap: a load from `%lo(sym)(reg)` or the stack can go in a plain
  slot, a load through a pointer register cannot (`may_trap_p`), so that one is always
  `-likely`. A volatile access is not moved into any slot.
- Branch prediction (REG_BR_PROB from predict.c, e.g. 9001 for a branch whose fallthrough
  leaves the loop) only decides which thread reorg tries first. It does not decide
  annulled vs plain: in gb func_00f350d0 both versions had the same probabilities.

Minimal check (/tmp/claude-0/s141/wwm1/bl/t1.py):

```c
extern int n; extern short *a; void g(int); void h(int);
void f(void) { int i, k; for (i = 0; i < n; i++) { k = a[i] - 1;
    if (k < 4) { if (k >= 0) { g(i); h(i); return; } } } }
```

With `g` only declared, the first test is `beql ... ; lw $2,%lo(n)`. With `void g(int x) {}`
above `f`, it is `beq ... ; lw $2,%lo(n)`.

To try this mechanically: /tmp/claude-0/s141/wwm1/ctx2.py OVL FUNC draft.c [k] gives every
declared callee (func_*, sce*, any prototype) a CONTEXT_ONLY definition, one at a time, then
all together, then up to k at a time. It is greedy: after an improvement it tries the
remaining callees again on top of it. It keeps the best version. The older ctx.py did only
func_* names.

Round 17 results (every near miss in gb, wm and the small overlays, 258 drafts):

- Matched: gb func_00f350d0, func_00f35a80, func_00f34aa8; wm func_00f5cb78, func_00f31118,
  func_00f3ff98, func_00f3be50 (135 words -> 1 with func_00f3b118 defined, -> 0 with
  func_00f3b370 too), and func_00f5bba0 (68 -> 3 with func_00f5ae10, then gb func_00f34aa8's
  `v[0..3]` store order).
- Closer: wm func_00f3d978 (99 -> 8), func_00f3cdd0 (24 -> 17), func_00f43430 (7 -> 6).
- No change: wm func_00f32770, the other gb drafts, dktitle, dkmovie, xs_* and xl_limit.
  Only the big drafts moved, by a few words.
- Most hits are a sibling defined just above in the original file: an overlay helper at a
  lower address, called first on the path after the branch. If a near miss still differs
  only in branch-likely use, look at the callees at lower addresses than the function.

Round 18:

- It works in both directions. The main ELF's func_001fd858 has a `bnez` where the
  original has `bnezl`, because its draft defines CONTEXT_ONLY func_001fe408 above the
  function. That makes the fe408 call nothrow, so the call kills v0 in reorg's scan. Moving
  the definition below the function (only a prototype above) gives the `bnezl`: 1 -> 0
  difflib words on the flagged draft and 25 -> 24 on the natural one (lro6_s12.check; not
  committed). If a draft has a `b*` where the original has `b*l`, look for definitions
  above the function that should not be there.
- Combined with statement moves: /tmp/claude-0/s141/wwm1/sclimb.py OVL draft.c SECS SEED
  toggles a CONTEXT_ONLY definition per callee and moves statements with climb_s144's
  dependency check. It matched wm func_00f2cfd8 (a stub plus two moves) and func_00f2c330 (one
  store moved). Do not use free line swaps (hill2.py block mode) for this: they reorder
  dependent statements and give low counts for wrong code.
- A k=2 ctx2.py run over every near miss found no further direct match; the gains were in big
  drafts (gb f50550 / wm f77648 253 -> 228, wm f42f20 205 -> 170).

Round 19: wm func_00f4b878 (and its gb twin func_00f24780 by portall) went 202 -> 17 words
with sclimb.py, 4 with the index sum reordered, and 0 when the seven zero locals were
initialized by assignments after the declarations (`x0 = 0; y0 = 0; z0 = 0; first = 0;
x1 = 0; ...`) instead of `s32 x0 = 0, y0 = 0, ...`. No order of the initializer list
gave the target's stack-slot store order (32, 20, 24, 28); one order of plain assignments did.
For a near miss that differs only in which stack slot each spilled zero-initialized local
gets, try assignments in different orders instead of initializers.
For drafts with a size difference, run sclimb.py with `OBJ=score` (hand.py's score). The raw
word count often goes down while the alignment gets worse.

`tools/ovl/i2a.py OVL DRAFT [N]` does the initializer-to-assignment change. It takes the constant
initializers of the declarations at the top of the function body, removes them, and puts
plain assignments after the last declaration. It then runs hand.py try on the source order and
on N random orders (default 40), and writes the best version to `$I2A_DIR/best_OVL_FUNC.c`
(default out/ovl/i2a/). It needs at least two constant initializers, and it reports raw word
counts, so check the best file's hand.py score before you keep it. Starting from the 4-word
f4b878 draft it finds the match.

Round 21: xs_dh_break func_00f20820 had two FP constants (50.0f, 25.0f) in each other's
registers ($f20 / $f21). global-alloc orders pseudos by floor_log2(refs) * refs / live length,
and sched1 had hoisted both constant loads, so changing the order of statements did not help.
Writing the first single-use temp inline matched it:
`s->c[0] = (...) + func_00f20020() * 50.0f - 25.0f;` instead of `a = func_00f20020() * 50.0f;`
on the line before. For a register swap between two long-lived values, try inlining a temp that
is used only once, on the next line (/tmp/claude-0/s141/wwm1/inl.py does it one temp at a time).

## decomp-permuter on an overlay function (session 135)

tools/permuter.py works in overlay mode as it is (KH1_OVL points kh1tool at the overlay's layout,
the directory goes under out/ovl/NAME/permuter/):

```sh
KH1_OVL=dktitle python3 tools/permuter.py import func_00f26710 --file nonmatchings/session132/dktitle/func_00f26710.c
KH1_OVL=dktitle python3 tools/permuter.py run func_00f26710 -j2 --stop-on-zero
KH1_OVL=dktitle python3 tools/autodecomp.py try func_00f26710 --file out/ovl/dktitle/permuter/func_00f26710/output-0-1/source.c
```

A draft named `func_X.<mode>.c` is compiled with that flag mode (session 135). The draft's own
`#include "ovl.h"` is what the preprocessing needs (hand.py's drafts without it need one added).
`static inline` helpers survive (the permuter keeps inline definitions); `register ... KH1_REG`
pins do not parse (session 128's sed recipe). Session 135 ran each of dktitle's 12 drafts and
dkmovie's two for 20 minutes on two threads (about 10 compiles a second): func_00f20258 matched
(the callee func_0011ef10 returns a value: declared void it scheduled the `lui` early), see
nonmatchings/session132/NOTES.md for the rest.

Session 136: func_00f25c40's best output (7 -> 1 word: D_00F27214 stored before D_00F2C904) and one
hand change (the read's wait checks the retry bit before each sceCdSync, as a `for (;;)` with the
check first) matched it. dkmovie func_00f20140: the best output (13 words) only wraps the two packet
stores in `do { } while (0)`; not kept. A draft that includes a header of its own (xs_dh_break's
shard.h) must have it pasted in before `import` (the permuter's copy is compiled elsewhere).

## Batch 7 patterns

### Early return written as an inverted if/else (gb func_00f2c000, wm func_00f530f8)

With `if (D_00F56DC0->x74 & 2) return 0;`, gcc puts the flag load into v1 and the original
puts it into v0. The cause: sched1 hoists the return path's `v0 = 0` above the flag
test, so v0 is busy when local-alloc picks a register for the flag temp, and the temp
goes to v1. Writing the test the other way round keeps the early `v0 = 0` out of the
block:

```c
if (!(D_00F56DC0->x74 & 2)) {
    ... rest of the block ...
} else {
    return 0;
}
```

That one change matched both functions (3 words -> 0).

Round 34 swept every overlay's drafts with this rewrite: each early `if (C) return K;`
(one-line, braced, or a braced block ending in a return, with no else) became
`if (!(C)) { rest of the enclosing block } else { block }`, first each site alone and then
all sites together. The sweeper reproduced the f2c000 match from the old draft. Results:

- 53 drafts had a site and 72 candidates were built. There were no new matches.
- Most candidates compile to exactly the same code as the original draft.
- gb func_00f2c9f8, wm func_00f53af0 and wm func_00f3a640 lose a few words, but they get
  a worse score and a size further from the target.

So this is not a common fix. Try it when a near miss differs only in v0/v1 around an early
`return 0`, or when the return value's `move v0,zero` lands above a load that should use v0.

### Local vs global FP allocation (card-flip family: gb func_00f2eee8, func_00f2f688; wm func_00f55fe0, func_00f56780)

Use gcc's own allocation dumps when callee-saved FP numbering (f20/f21/f22) is wrong:

```sh
tools/toolchain/ee-gcc2.96/bin/ee-gcc -c -x c -O2 -G0 -Iinclude -dl -dg draft.c
```

The command writes `draft.c.19.lreg` (local-alloc) and `draft.c.20.greg` (global). Each
file has a "Register dispositions" table; hard register 32 is f0. What the dumps showed:

- **Local-alloc goes first.** It takes only pseudos that live in one basic block
  (REG_BASIC_BLOCK >= 0) and die exactly once (REG_N_DEATHS == 1). It gives each one the
  lowest free register, so f20 comes first among the callee-saved ones.
- **Global allocation takes everything else.** That is any pseudo that crosses blocks or
  dies twice. It allocates by priority floor_log2(refs) * refs / live_length.
- **sched1 can move FP work across a call** when the result is held in a callee-saved
  pseudo.

In the card-flip loops, the original's fi, r and t all behave as global pseudos. A draft
with a fresh float per loop (fi2, r2, q2) let local-alloc grab f20 first, which gave the
wrong numbering. The fix:

- loop 2 reuses fi and r;
- loop 2 sets `t = 0.0f;` at its top and passes t for its 0.0f arguments;
- loop 1 does `fi = t;` between the two func_00f285e0-type calls.

This gave the original's r=f20, fi=f21, t=f22 (36 -> 33 and 34 -> 25 words); only
scheduling is left. When you see an allocation mismatch, check in the .lreg dump whether
the variable was allocated locally. If it should not be, make it live across blocks or set
it twice.

### Constant kept in the loop by a twice-set temp (gb func_00f2fe38, func_00f30640; wm func_00f56f30, func_00f57738)

loop.c hoists a loop-invariant constant such as 0.017453292f out of the loop unless the
register holding it is set more than once. The original reloads it inside the loop. To
match that, write `q = 0.017453292f; r = c * q; q = r;` so that q is set twice and the
constant stays in the loop. The functions also needed:

- the init order ten / a / ninety / i;
- one accumulator per loop;
- `a4 = 58` at the top of loop 1 (found by the permuter).

The wm twins also needed the wm table addresses (D_00FA5C40 / D_00FA5C90), not the gb ones.

### Session 141 rounds 37-38 (wwm2)

- **A real struct layout for a table indexed with a hand-computed offset (wm func_00f7c078):**
  - The draft read `D[k + a * 24 + 8]` from an `s8 D[]` table. That built the first address as o + base; the original has base + o.
  - Declaring the table as `struct { s8 n[8]; s8 x[8]; s8 y[8]; } D[]` and reading `D[a].x[k]` matched.
  - Plain 2-D arrays (`D[][24]`, `D[][3][8]`) did not help. Neither did rewriting the 9 gb/wm drafts that index colour tables as `D[n * 4 + c]` into `[n][c]`: no score changed.
- **Arithmetic moved into each branch before a shared use (wm func_00f3fd60):**
  - The draft set `v` in an if/else and then read `tbl[v - 1]`. gcc folds the -4 into the table offset; the original keeps a separate `addiu -1`.
  - Writing `v = a - 1;` in one branch and `v = b - 1;` in the other, then reading `tbl[v]`, matched. The register of the loaded value changed with it.
- **Load a global pointer into a local before a read it may alias (wm func_00f22e60, norlo mode):**
  - The draft did `*D_00F85160 = p; if (D_00FBB338 == 0) a -= 12;`. A store through `*D_00F85160` may alias D_00FBB338, so the load of D_00FBB338 has to wait for the store.
  - The original loads the pointer, then D_00FBB338, then stores. `u64 **q = D_00F85160; if (D_00FBB338 == 0) a -= 12; *q = p;` matched, including the movz operand registers.
- **A wait call made once before the loop and again at the end of each pass (wm func_00f5d498, gb func_00f363a0, round 39):**
  - Two signs point to it: the prologue saves ra last, right before the loop's first jal, and a label inside the loop is 8-byte aligned with a nop pad even though no branch jumps back to it.
  - `func_001bfac8(); while (1) { ...; func_001bfac8(); }` matched both menu loops. `while (1) { func_001bfac8(); ... }` did not.
  - A likely reason, not checked in the dumps: the first jal sits in the prologue block, so sched2 keeps sd ra next to it, and the call at the loop end is later folded into the one before the loop.

## Results

Kept up to date by the session that changes them (`make ovl-progress`).

| Overlay | Functions | Matched | Notes |
|---|---|---|---|
| dkmovie | 122 | 95 | session 131b; f205a4 / f205f4 are hand-written sq/daddiu asm loops; session 134: the front end is native in the port, the player is `PlatMovie*` (docs/native-overlays.md) |
| dktitle | 71 | 60 | session 132: native C in the port (docs/native-overlays.md), notes in nonmatchings/session132/NOTES.md; session 136: func_00f25c40 |
| gb | 533 | 367 | session 131b; most of its code is wm's (twins.py) |
| wm | 1109 | 747 | session 131b |
| xl_limit | 76 | 74 | session 131b; session 139: func_00f20ff0; session 140: 5 more (nonmatchings/session140/NOTES.md) |
| xs_bambi | 13 | 13 | complete |
| xs_dh_break | 9 | 5 | session 131b; session 136: native in the port with drafts for the other 4 (docs/native-overlays.md) |
| xs_dumbo | 54 | 48 | session 131b |
| xs_genie | 64 | 58 | session 131b |
| xs_mushu | 24 | 22 | session 131b |
| xs_simba | 33 | 29 | session 131b |
| xs_tink | 14 | 13 | session 131b |

Session 131b (the 11 overlays other than dktitle): 752 -> 1,465 / 2,051, every overlay
byte-identical. Near misses with their drafts are listed in docs/next-session.md ("Session 131b").
