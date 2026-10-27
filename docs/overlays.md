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
```

twins.py: gb and wm share most of their code (and the summons share helpers), so every
match is tried on the functions with the same instructions (symbols, call targets and
labels masked; large literals masked as a fallback) in every overlay. Run it after each
`make ovl`.

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

Near misses and open questions are in the session's notes (docs/next-session.md); two
recurring ones: an endless loop that calls a function without saving $ra (gb
func_00f50db0, wm func_00f77ea8; gcc always saves it, maybe asm), and the angle-wrap
helpers (gb func_00f25a68, wm func_00f35800 / func_00f4cb60, register allocation).

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

## Results

Kept up to date by the session that changes them (`make ovl-progress`).

| Overlay | Functions | Matched | Notes |
|---|---|---|---|
| dkmovie | 122 | 95 | session 131b; f205a4 / f205f4 are hand-written sq/daddiu asm loops; session 134: the front end is native in the port, the player is `PlatMovie*` (docs/native-overlays.md) |
| dktitle | 71 | 60 | session 132: native C in the port (docs/native-overlays.md), notes in nonmatchings/session132/NOTES.md; session 136: func_00f25c40 |
| gb | 533 | 367 | session 131b; most of its code is wm's (twins.py) |
| wm | 1109 | 747 | session 131b |
| xl_limit | 76 | 68 | session 131b |
| xs_bambi | 13 | 13 | complete |
| xs_dh_break | 9 | 5 | session 131b; session 136: native in the port with drafts for the other 4 (docs/native-overlays.md) |
| xs_dumbo | 54 | 48 | session 131b |
| xs_genie | 64 | 58 | session 131b |
| xs_mushu | 24 | 22 | session 131b |
| xs_simba | 33 | 29 | session 131b |
| xs_tink | 14 | 13 | session 131b |

Session 131b (the 11 overlays other than dktitle): 752 -> 1,465 / 2,051, every overlay
byte-identical. Near misses with their drafts are listed in docs/next-session.md ("Session 131b").
