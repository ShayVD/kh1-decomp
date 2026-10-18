#include "common.h"

/* func_00171078: the table is read through a hard-coded address, not the
   D_0035BD40 symbol. gcc emits `lw $2,3521856($3)`; gas expands the large
   constant offset itself (lui v0; addu v0,v0,v1; lw v0,lo(v0)) and, since the
   last insn carries no relocation, moves it into the empty `j $31` slot. With
   the symbol the %lo fixup stops gas from filling the slot (nop). */
s32 func_00171078(s32 a, s32 *b) {
    return ((s32 *)0x35BD40)[*b ^ 3];
}
