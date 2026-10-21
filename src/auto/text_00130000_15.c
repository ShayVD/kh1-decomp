/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

#include "data/pieces/D_00304BE8.h"
extern s32 D_00308CDC;

void func_0013c1b8(s32 arg0) {
    s32 temp_a0;
    void *temp_a1;

    temp_a0 = (arg0 * 4) + 0xD0;
    temp_a1 = ((s32)D_00304BE8) + 4;
    M2C_FIELD(temp_a1, u8 *, 6) = (u8) (M2C_FIELD(temp_a1, u8 *, 6) + *(M2C_UNK *)((s32) D_00308CDC + (s32) temp_a0));
    M2C_FIELD(temp_a1, u8 *, 7) = (u8) (M2C_FIELD(temp_a1, u8 *, 7) + M2C_FIELD((D_00308CDC + temp_a0), u8 *, 1));
    M2C_FIELD(temp_a1, u8 *, 4) = (u8) (M2C_FIELD(temp_a1, u8 *, 4) + M2C_FIELD((D_00308CDC + temp_a0), u8 *, 2));
    M2C_FIELD(temp_a1, u8 *, 3) = (u8) (M2C_FIELD(temp_a1, u8 *, 3) + M2C_FIELD((D_00308CDC + temp_a0), u8 *, 2));
    M2C_FIELD(temp_a1, u8 *, 5) = (u8) (M2C_FIELD(temp_a1, u8 *, 5) + M2C_FIELD((D_00308CDC + temp_a0), u8 *, 3));
}
