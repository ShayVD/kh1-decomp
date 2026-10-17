# Context-only bodies (CONTEXT_ONLY), implemented in session 6

## Why
gcc 2.96 records the registers a function really clobbers when it compiles it, and uses
that when it later compiles a caller in the same file. A caller whose callee was defined
above it in the original source file gets plain `beq`/`bne` (with a useful delay slot)
where a prototype-only callee gives `beql`/`bnel`, and sometimes different register
choices. So some callers only match with the callee's body above them, even when the
callee itself is matched in another file or not matched at all.

## How to use it
```c
#include "common.h"

CONTEXT_ONLY s32 func_0019bbf0(Obj *o, s32 k) { ...callee body... }

void func_0019cb88(...) { ... func_0019bbf0(o, 1) ... }   /* the real match */
```
`CONTEXT_ONLY` (include/common.h) is `__attribute__((weak, section(".ctx")))`.

- The copy is compiled, so gcc knows its register use, but it is never placed or patched
  and does not count as decompiled. Calls to it resolve to the original address
  (symbols.ld), or to the real definition when another file has one, so a matched
  function can have CONTEXT_ONLY copies in any number of files.
- Only the register use matters: a matched body copied from another file, or an
  unmatched callee's closest draft, both work. A `{}` stub is enough for probing.
- Never `static`: ee-as 2.10 turns calls to a global defined in another section of the
  same object into relocations against the section symbol; `weak` keeps them against
  the function symbol. fix-obj rejects a .text/.rodata/.data relocation against a .ctx
  section (that is what a static CONTEXT_ONLY function would produce).

## Build plumbing (tools/kh1tool.py, kh1.ld)
- `fix_object` -> `strip_context_only`: every GLOBAL/WEAK symbol defined in `.ctx` or
  `.ctx.*` becomes an undefined GLOBAL (shndx 0, value 0, size 0).
- `split_rodata`: constants and jump tables of a function compiled in `.ctx` go to
  `.ctx.rodata.<fn>[.n]`, so rodata inference never sees them.
- kh1.ld: `.ctx 0x0f000000 : { *(.ctx .ctx.*) }`. Below 0x10000000 so the copies' own
  `jal`s still reach game code (R_MIPS_26 needs the same 256 MB region); outside the
  image, so nothing is patched. Not /DISCARD/: their jump tables relocate against .ctx.
- link-script, patch, verify, progress and objdiff work from placements, and a ctx
  function has no defined STT_FUNC after fix-obj, so it is never placed or counted.
- `decompiled_addrs` (rank) counts a CONTEXT_ONLY definition as `wip`.
- tools/checkfile.py and `autodecomp.py try` link `.ctx` at 0x0f000000 too, so
  `try` now works for a caller with a CONTEXT_ONLY callee above it (before, a callee
  in the same file failed with "relocation truncated").

## First uses
src/hand/nostrict/text_00190000_ctx.c (func_0019cb88 below CONTEXT_ONLY copies of
func_0019baf8, func_0019bb40 and the unmatched func_0019bbf0) and
src/hand/nostrict/text_001a0000_ctx.c (func_001a0628 below func_0019f100, func_0019f148
and the unmatched func_0019f1f0).
