/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK sceRead(s32, s32, s32, s32);
extern M2C_UNK D_0003DF51;
s32 func_00f221b0(s32, s32, s32 *, s32);
s32 sceOpen(s32, s32, ...);

s32 func_00f234e8(s32 arg0, s32 arg1, s32 arg2, s32 *arg3, s32 arg4) {
    FlushCache(0);
    if (*(s8 *)((s8 *)(s8 *)&D_0003DF51 + arg4) != 0) {
        return func_00f221b0(arg1, arg2, arg3, arg4);
    }
    sceRead(arg0, arg2, arg1, arg4);
    *arg3 = 0;
    return 1;
}

s32 func_00f27eb0(s32 arg0) {
    return sceOpen(arg0, 0x8001);
}
