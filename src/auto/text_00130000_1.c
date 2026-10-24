/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00304BE8.h"

void func_0013c270(s32 arg0, s8 arg1) {
    M2C_FIELD((arg0 + ((s32)D_00304BE8)), s8 *, 0x844) = arg1;
}

s8 func_0013c288(s32 arg0) {
    return M2C_FIELD((arg0 + ((s32)D_00304BE8)), s8 *, 0x844);
}

s32 func_0013c6a8(u32 arg0) {
    return M2C_FIELD((((arg0 >> 2) * 4) + ((s32)D_00304BE8)), s32 *, 0x5CC) & (1 << (arg0 & 3));
}
