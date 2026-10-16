/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK sceSifCallRpc(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK, s32);
extern M2C_UNK D_003E3C88;
extern M2C_UNK D_00633640;

s32 func_001ed978(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(&D_00633640, s32 *, 0) = arg0;
    M2C_FIELD(&D_00633640, s32 *, 4) = arg1;
    M2C_FIELD(&D_00633640, s32 *, 8) = arg2;
    M2C_FIELD(&D_00633640, s32 *, 0xC) = arg3;
    sceSifCallRpc(&D_003E3C88, 0x19, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return M2C_FIELD(&D_00633640, s32 *, 0);
}

s32 func_001eda90(s32 arg0, s32 arg1) {
    M2C_FIELD(&D_00633640, s32 *, 0) = arg0;
    M2C_FIELD(&D_00633640, s32 *, 4) = arg1;
    sceSifCallRpc(&D_003E3C88, 0x32, 0, &D_00633640, 0x2000, &D_00633640, 0x2000, 0, 0);
    return M2C_FIELD(&D_00633640, s32 *, 0);
}
