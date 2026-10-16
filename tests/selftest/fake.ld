ENTRY(_start)
SECTIONS {
  . = 0x00100000;
  .text : { *(.text) }
  .data : { *(.data) *(.rodata*) }
  .bss : { *(.bss) *(.sbss) *(COMMON) }
  /DISCARD/ : { *(.reginfo) *(.mdebug*) *(.pdr) *(.comment) }
}
