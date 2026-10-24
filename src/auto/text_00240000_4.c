/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

void *func_00241b60(M2C_UNK, s32);

void func_00241c00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *temp_v0;

    temp_v0 = func_00241b60(3, arg4);
    M2C_FIELD(temp_v0, s32 *, 0xA88) = arg0;
    M2C_FIELD(temp_v0, s32 *, 0xA8C) = arg1;
    M2C_FIELD(temp_v0, s32 *, 0xA90) = arg2;
    M2C_FIELD(temp_v0, s32 *, 0xA94) = arg3;
}
