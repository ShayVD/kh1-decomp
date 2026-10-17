Context-only bodies: findings (session ended before the feature was implemented)

VERIFIED
1. __attribute__((section(".ctx"))) and __attribute__((weak, section(".ctx"))) on the
   callee both give the same caller asm (labels normalized) as a plain definition:
   - func_0019cb88: beq (body above, matches) vs beql (prototype only)
   - func_001a0628: beq vs beql, same pattern
   Test files: cb_full/cb_ctx/cb_w.c (cb_w uses weak) and a_*.c in this directory.
2. ee-as 2.10 rewrites a call to a GLOBAL function defined in another section of the
   same object as a relocation against the SECTION symbol:
   `R_MIPS_26 .ctx` + addend. So renaming or undefining the symbol in fix-obj is NOT
   enough without weak. With `weak`, the relocation stays against the symbol
   (`R_MIPS_26 func_0019bbf0`).
   => Spelling: #define CONTEXT_ONLY __attribute__((weak, section(".ctx")))

PLANNED DESIGN (not done)
- include/common.h: the CONTEXT_ONLY macro above.
- fix_object(): every symbol defined in .ctx / .ctx.* becomes an undefined GLOBAL
  (shndx=0, value=0, size=0). Callers then resolve through the PROVIDE in symbols.ld
  to the original address, or to the real matched definition when another file has
  one (for example func_0019baf8 in vu0.c, so duplicates are fine). Fail if a non-ctx
  section has a relocation against the .ctx section symbol (a static ctx function).
- split_rodata(): rodata owned by a ctx function goes into .ctx.rodata.<fn>[.n], so
  infer_rodata ignores it (no warnings, never placed). partial.diff holds this part
  (it is reverted in the repo). It still needs an is_ctx_section(name) helper:
  name == ".ctx" or name.startswith(".ctx.").
- kh1.ld: add *(.ctx .ctx.*) to .orphan. Do not use /DISCARD/: the jump tables in
  ctx rodata relocate against .ctx, and discarding it causes "discarded section"
  errors.
- link-script, patch, verify, progress, function_status and objdiff: they work only
  from placements, and a ctx function has no defined STT_FUNC, so it is never placed
  or counted. No change needed.
- decompiled_addrs() (rank/autodecomp): a definition that has CONTEXT_ONLY before it
  should count as 'wip', not 'src'.
- tools/checkfile.py: add .ctx* to its .other section (optional).
- Landing: src/hand/nostrict/text_00190000_ctx.c with CONTEXT_ONLY copies of
  baf8/bb40 (already matched in vu0.c / h12.c), a CONTEXT_ONLY bbf0 (bbf0p.c body),
  cb88, then CONTEXT_ONLY f100/f148 + f1f0 (f1f0n.c body), then a0628. Struct
  typedefs differ between the two test files (MgKey vs MgKey2 etc.), so check for
  name clashes.
