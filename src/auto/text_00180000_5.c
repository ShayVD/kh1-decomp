/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "ppp.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK func_0024edf0(void *, s32);
M2C_UNK func_002672f8(s32, s32, s32);
M2C_UNK func_00267328(void *, M2C_UNK *, M2C_UNK *);
M2C_UNK sceGsExecLoadImage(void *, void *);
M2C_UNK sceGsSetDefLoadImage(void *, s16, s16, s16, s16, s16, s16, s16);
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);
#include "data/pieces/D_002BBFA0.h"
extern M2C_UNK D_00615E70;
extern s32 D_00615E64;
extern s32 D_00615E68;
extern s32 D_00616214;
void func_00183a00(s32, s32, s32);
void memset(s32, s32, s32);

void func_001812d0(void *arg0) {
    s32 sp[16];
    func_00267328(sp, (M2C_UNK *)&D_002BBFA0, &D_00615E70);
    func_0024edf0(sp, M2C_FIELD(arg0, s32 *, 0x8C));
}

void func_00182840(s32 arg0) {
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x94);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x14) = 0;
        memset(arg0, 0, 0xC0);
    }
}

void func_00182e78(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_00615E64 = arg0;
    if (arg1 != 0) {
        M2C_FIELD(arg0, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0x18);
        M2C_FIELD(arg0, s32 *, 0x18) = (s32) M2C_FIELD(arg1, s32 *, 0x1C);
    }
    func_00183a00(arg0, arg2, arg3);
}

void pppParMatrixFrame(void *arg0) {
    s32 temp_a0;

    temp_a0 = D_00615E68 + 0x40;
    func_002672f8(temp_a0, M2C_FIELD(arg0, s32 *, 4) + 0x10, temp_a0);
}

void pppDrawMatrixWoodFn14(void) {

}

void pppSMatrixFrame(s32 arg0, s32 arg1, void *arg2) {
    D_00616214 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC) + 0xA0;
}
#include "data/bss_0061_mixed.h"
