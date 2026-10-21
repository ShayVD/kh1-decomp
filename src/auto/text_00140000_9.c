/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

#include "data/pieces/D_00350D88.h"

void func_0014f830(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0) {
    void *temp_a0;

    temp_a0 = (s8 *)&D_00350D88 + (arg0 << 5);
    M2C_FIELD(temp_a0, s32 *, 0) = arg1;
    M2C_FIELD(temp_a0, s32 *, 4) = arg2;
    M2C_FIELD(temp_a0, s32 *, 8) = arg3;
    M2C_FIELD(temp_a0, s32 *, 0xC) = arg4;
    M2C_FIELD(temp_a0, s32 *, 0x10) = arg5;
    M2C_FIELD(temp_a0, s32 *, 0x14) = arg6;
    M2C_FIELD(temp_a0, s32 *, 0x18) = arg7;
    M2C_FIELD(temp_a0, s32 *, 0x1C) = arg_sp0;
}
