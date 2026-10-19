/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00175a48();
extern M2C_UNK *D_0061622C;
M2C_UNK D_00575E40[0x8000] ALIGNED(64);
extern M2C_UNK func_00175af0;
extern M2C_UNK func_00175b70;
extern M2C_UNK func_0017f8e0;
extern s32 D_003626B0;
extern s32 D_00574FB4;
extern s32 D_00616230;
extern void *D_00362438;
void *func_0011ef10(M2C_UNK, M2C_UNK *);

s32 func_00170e30(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_00574FB4;
    D_00574FB4 = arg0;
    return temp_v0;
}

s32 func_00170f90(void *arg0, void *arg1) {
    return M2C_FIELD(arg1, s32 *, 0x4C) == M2C_FIELD(arg0, s32 *, 0x164);
}

s32 func_00171f30(void) {
    return 0;
}

void func_00171f38(s32 arg0, s32 *arg1) {
    if ((arg1 != NULL) && (*arg1 == arg0)) {
        *arg1 = 0;
    }
}

void func_00175918(void) {
    M2C_FIELD(func_0011ef10(0x222E0, &func_00175af0), s16 *, 2) = -1;
    M2C_FIELD(func_0011ef10(0x27100, &func_00175b70), s16 *, 2) = -1;
    func_0011ef10(0x2E630, &func_0017f8e0);
    func_00175a48();
}

s32 func_00176528(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC);
}

s32 func_00176620(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x2C), s32 *, 0xA8);
}

s32 func_00176630(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x2C), s32 *, 0x8C);
}

void func_0017d1e0(void) {
    if (!(M2C_FIELD(D_00362438, s32 *, 0x18) & 0x10)) {
        D_003626B0 = 1;
    }
}

void func_0017f910(M2C_UNK *arg0, s32 arg1) {
    if (arg0 != NULL) {
        D_0061622C = arg0;
        D_00616230 = arg1;
        return;
    }
    D_0061622C = &D_00575E40;
    D_00616230 = 0x20000;
}
