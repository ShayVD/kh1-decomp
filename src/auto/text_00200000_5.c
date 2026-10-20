/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK func_001f9010(M2C_UNK);
M2C_UNK func_001f94f0(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK, M2C_UNK);
extern s32 D_002BC140;
extern s32 D_002BC144;
extern s32 D_003F34A4;
extern s32 D_003F6E30;
extern s32 D_00640E2C;
extern s32 D_00640E30;
extern s8 D_003F3530;
void *func_001ef8f8();
void func_00142000(void);
void func_0020a1d8(void);

void func_0020a6c0(s32 arg0) {
    s32 var_a1;
    void *temp_a0;
    void *temp_v1;

    temp_a0 = M2C_FIELD(func_001ef8f8(), void **, 0x14C);
    var_a1 = 0;
    temp_v1 = &D_003F3530 + (arg0 * 0xD0);
    M2C_FIELD(temp_v1, s32 *, 0x50) = -1;
    if (temp_a0 != NULL) {
        var_a1 = M2C_FIELD(temp_a0, s32 *, 4);
    }
    M2C_FIELD(temp_v1, s32 *, 0x3C) = var_a1;
    M2C_FIELD(temp_v1, s32 *, 0x70) = 0;
}

void func_0020a728(s32 arg0) {
    void *temp_v0;

    temp_v0 = &D_003F3530 + (arg0 * 0xD0);
    M2C_FIELD(temp_v0, s32 *, 0x50) = 0;
    M2C_FIELD(temp_v0, s32 *, 0x3C) = 0;
}

void func_0020d2a0(void) {
    D_003F34A4 = 0;
    if (D_003F6E30 == 0) {
        func_0020a1d8();
    }
    func_00142000();
    D_002BC144 = D_00640E2C;
    D_002BC140 = D_00640E30;
}

void func_0020eb20(void *arg0) {
    s32 temp_s1;

    temp_s1 = M2C_FIELD(arg0, s32 *, 0x40);
    if (temp_s1 != 0) {
        func_001f9010(0x17);
        func_001f94f0(arg0, 0, 0xAE, 0xC, temp_s1, 0x11, 0x80C87850);
    }
}
