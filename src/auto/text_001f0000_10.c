/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001f31a8(M2C_UNK *, s32);
extern M2C_UNK D_003E9630;
s32 func_002366d8(M2C_UNK, M2C_UNK);

void func_001f35d8(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(&D_003E9630, s32 *, 0) = arg1;
    M2C_FIELD(&D_003E9630, s32 *, 8) = arg0;
    func_001f31a8(&D_003E9630, arg2);
}

void func_001f3608(s32 arg0, s32 arg1) {
    M2C_FIELD(&D_003E9630, s32 *, 0) = arg1;
    M2C_FIELD(&D_003E9630, s32 *, 8) = arg0;
    func_001f31a8(&D_003E9630, func_002366d8(4, 0x36) + 1);
}
