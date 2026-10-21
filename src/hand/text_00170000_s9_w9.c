#include "common.h"

/* func_00171078: the table is read through a hard-coded address, not the
   D_0035BD40 symbol. gcc emits `lw $2,3521856($3)`; gas expands the large
   constant offset itself (lui v0; addu v0,v0,v1; lw v0,lo(v0)) and, since the
   last insn carries no relocation, moves it into the empty `j $31` slot. With
   the symbol the %lo fixup stops gas from filling the slot (nop).
   KH1_SHIFTABLE (the shiftable build, tools/shift/variants.py): use the
   symbol so the table can move; 4 bytes longer (the nop), which still fits
   before func_00171098. */
#ifdef KH1_SHIFTABLE
#include "data/pieces/D_0035BD40.h"
#endif
s32 func_00171078(s32 a, s32 *b) {
#ifdef KH1_SHIFTABLE
    return D_0035BD40.i_2[*b ^ 3];
#else
    return ((s32 *)0x35BD40)[*b ^ 3];
#endif
}
