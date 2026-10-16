/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001f1fc8(s32, s32, s32, s32, s32, s32);
M2C_UNK func_001f31a8(M2C_UNK *, M2C_UNK);
extern M2C_UNK D_003E9630;
s32 func_001efbb8(s32);

void func_001f1f58(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_001f1fc8(arg0, arg1, arg2, arg3, func_001efbb8(arg4), arg5);
}

void func_001f35a8(s32 arg0, s32 arg1) {
    M2C_FIELD(&D_003E9630, s32 *, 0) = arg1;
    M2C_FIELD(&D_003E9630, s32 *, 8) = arg0;
    func_001f31a8(&D_003E9630, 6);
}
