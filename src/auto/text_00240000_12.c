/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

s32 sceGsSyncPath(s32, s32, s32, s32, s32, s32, s32, s32);
void func_00237018(s32, s32, s32);

void func_002499f0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 sp[12];
    sceGsSyncPath(0, 0, arg2, arg3, arg4, arg5, arg6, arg7);
    M2C_FIELD(sp, s64 *, 0x10) = ((s64) 0x10000000 << 0x20) | 0x8001;
    M2C_FIELD(sp, s64 *, 0x18) = 0xE;
    M2C_FIELD(sp, s64 *, 0x28) = 0x3F;
    M2C_FIELD(sp, s64 *, 0x20) = 0;
    func_00237018((s32) sp, 3, 1);
}
