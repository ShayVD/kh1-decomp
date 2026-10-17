/* Link script for the patch-in-place build. Every decompiled function gets
 * its own output section at its original address (out/gen/functions.ld);
 * every other symbol resolves to its original address (out/gen/symbols.ld).
 * Anything else a source file emits (string literals, jump tables, data) lands
 * in .orphan far outside the game image, so code that references it cannot
 * match until that data is declared as an extern D_xxxxxxxx instead. */
INCLUDE out/gen/symbols.ld

SECTIONS
{
  INCLUDE out/gen/functions.ld

  .orphan 0x40000000 : {
    *(.text .text.* .gnu.linkonce.t.*)
    *(.rodata .rodata.* .gnu.linkonce.r.*)
    *(.data .data.* .sdata .sdata.* .lit4 .lit8 .gnu.linkonce.d.*)
    *(.sbss .sbss.* .bss .bss.* .scommon COMMON)
  }

  /* CONTEXT_ONLY bodies (include/common.h): compiled so callers below them
   * match, never placed or patched. Kept below 0x10000000 so their own jal
   * instructions reach the game's code; outside the game image. */
  .ctx 0x0f000000 : { *(.ctx .ctx.*) }

  /DISCARD/ : {
    *(.reginfo) *(.mdebug*) *(.pdr) *(.comment) *(.gnu.attributes)
    *(.MIPS.abiflags) *(.note*) *(.gcc_compiled*)
  }
}
