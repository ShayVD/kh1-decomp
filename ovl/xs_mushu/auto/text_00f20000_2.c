/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

s32 sceVu0CopyVector(s32, s32);

s32 func_00f212b0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_hi;
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 8);
    temp_hi = (s32) ((M2C_FIELD(arg0, s32 *, 0xC) - arg1) + temp_v1) % temp_v1;
    M2C_FIELD(arg0, s32 *, 0x10) = temp_hi;
    return sceVu0CopyVector(arg2, M2C_FIELD(arg0, s32 *, 0) + (temp_hi * 0x10));
}
