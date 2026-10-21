/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK func_0010c4b0();
M2C_UNK func_0010ed20(s32, s32, s32, s32, void *);
M2C_UNK func_00121ee0(void *);
M2C_UNK sceGsExecLoadImage(M2C_UNK *, s32);
M2C_UNK sceGsSetDefLoadImage(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);
extern M2C_UNK D_002BC1B0;
extern M2C_UNK D_002BC210;
#include "data/pieces/D_002B677C.h"
void *func_00121e28(M2C_UNK, void *);

void func_0010eee0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];
    M2C_FIELD(sp, void * *, 0x0) = func_00121e28(0x2C, sp);
    func_0010c4b0();
    M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) = 0U;
    M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) = (u8) (M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) | 4);
    func_0010ed20(arg0, arg1, arg2, arg3, M2C_FIELD(sp, void * *, 0x0));
    func_00121ee0(M2C_FIELD(sp, void * *, 0x0));
}
