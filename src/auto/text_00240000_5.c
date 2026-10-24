/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

void func_0024b058(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_a4;

    temp_a1 = (arg1 * 0x10) + 0x7000;
    temp_a2 = (arg2 * 0x10) + 0x7400;
    temp_a4 = ((arg2 + arg4) * 0x10) + 0x7400;
    temp_a3 = ((arg1 + arg3) * 0x10) + 0x7000;
    M2C_FIELD(arg0, s32 *, 0xA0) = temp_a1;
    M2C_FIELD(arg0, s32 *, 0xA4) = temp_a2;
    M2C_FIELD(arg0, s32 *, 0xA8) = -0x100;
    M2C_FIELD(arg0, s32 *, 0xAC) = 0;
    M2C_FIELD(arg0, s32 *, 0xB0) = temp_a1;
    M2C_FIELD(arg0, s32 *, 0xB4) = temp_a4;
    M2C_FIELD(arg0, s32 *, 0xB8) = -0x100;
    M2C_FIELD(arg0, s32 *, 0xBC) = 0;
    M2C_FIELD(arg0, s32 *, 0xC0) = temp_a3;
    M2C_FIELD(arg0, s32 *, 0xC4) = temp_a2;
    M2C_FIELD(arg0, s32 *, 0xC8) = -0x100;
    M2C_FIELD(arg0, s32 *, 0xCC) = 0;
    M2C_FIELD(arg0, s32 *, 0xD0) = temp_a3;
    M2C_FIELD(arg0, s32 *, 0xD4) = temp_a4;
    M2C_FIELD(arg0, s32 *, 0xD8) = -0x100;
    M2C_FIELD(arg0, s32 *, 0xDC) = 0;
}
#include "data/data_0045.h"
