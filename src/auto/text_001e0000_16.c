/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK sceGsExecLoadImage(M2C_UNK *, void *);
M2C_UNK sceGsSetDefLoadImage(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);
extern M2C_UNK D_0062F670;
extern M2C_UNK D_00F20000;

void func_001e06c8(s32 arg0) {
    void *temp_s1;

    sceGsSetDefLoadImage(&D_0062F670, 0xE00, 8, 1, 0, 0, 0x200, 0xC0);
    temp_s1 = (s8 *)&D_00F20000 + (arg0 * 0x600);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_0062F670, temp_s1);
    sceGsSetDefLoadImage(&D_0062F670, 0x1400, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_0062F670, temp_s1 + 0x48000);
}
