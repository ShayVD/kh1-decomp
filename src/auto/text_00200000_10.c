/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001f1fc8(s32, s32, s32, s32, s32, M2C_UNK);
M2C_UNK func_00200e28(M2C_UNK, s32, s32, s32, void *);
extern M2C_UNK D_003F2C40;

void func_002076b0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    void *temp_s0;

    temp_s0 = (s8 *)&D_003F2C40 + (arg0 * 0x14);
    func_00200e28(2, arg2, arg3, arg4, temp_s0);
    func_001f1fc8(arg1, M2C_FIELD(temp_s0, s32 *, 0x10), arg5, arg3 + 5, arg6, 0xF);
}
