/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK func_001f2e98(s32 *, s32 *);
M2C_UNK func_002499f0();
M2C_UNK sceGsExecLoadImage(void *, s32);
M2C_UNK sceGsSetDefLoadImage(void *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);

void func_002393d8(void) {
    s32 sp[28];
    func_001f2e98(&M2C_FIELD(sp, s32 *, 0x60), &M2C_FIELD(sp, s32 *, 0x64));
    sceGsSetDefLoadImage(sp, 0x3600, 4, 0x14, 0, 0, 0x100, 0x100);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(sp, M2C_FIELD(sp, s32 *, 0x60));
    sceGsSetDefLoadImage(sp, 0x3A00, 1, 0, 0, 0, 0x10, 0x10);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(sp, M2C_FIELD(sp, s32 *, 0x64));
    func_002499f0();
}
