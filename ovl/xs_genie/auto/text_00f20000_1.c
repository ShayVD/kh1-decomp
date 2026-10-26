/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_00f21530(void *, M2C_UNK, M2C_UNK *);
M2C_UNK func_00f21fc0(s32 *);
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK *D_00304B6C;
extern M2C_UNK D_00FC0D80;
extern M2C_UNK D_00FC0F10;
extern M2C_UNK D_00FC1710;
extern M2C_UNK D_00FC1A60;
extern M2C_UNK D_00FC1CE0;
extern M2C_UNK D_00FC2E20;
extern M2C_UNK func_00f209e8;
extern M2C_UNK func_00f21450;
extern M2C_UNK func_00f218b8;
extern M2C_UNK func_00f218f8;
extern M2C_UNK func_00f229f0;
extern s32 D_00F22E90;
extern s32 D_00FC0E48;
extern s32 D_00FC1DE0;
extern s32 D_00FC2EE8;
extern void *D_00F22E94;
s32 func_0011ef38(M2C_UNK *);
void func_00123030(void *, M2C_UNK, M2C_UNK);
void func_00135870(void *);
void func_0014f658(void *, M2C_UNK);
void func_00f205c8();
void func_00f22b80(M2C_UNK *, M2C_UNK *, M2C_UNK, void *);
void sceVu0CopyVector(void *, M2C_UNK *);

void func_00f20b70(void) {
    s32 sp[4];
    sceVu0CopyVector(sp, D_00F22E90 + 0x10);
    M2C_FIELD(sp, s32 *, 0x4) = 0;
    func_00f22b80(&D_00FC1710, &D_00FC0F10, 0x80, sp);
    sceVu0CopyVector(D_00F22E94 + 0x40, &D_00FC0D80);
    M2C_FIELD(M2C_FIELD(D_00F22E94, void **, 0x6C), f32 *, 0x14) = 0.3f;
    sceVu0CopyVector(D_00F22E94 + 0x10, D_00F22E90 + 0x10);
    M2C_FIELD(D_00F22E94, f32 *, 0x14) = (f32) (M2C_FIELD(D_00F22E94, f32 *, 0x14) + -1e+02f);
    func_0014f658(D_00F22E94, 4);
    func_00135870(D_00F22E94);
    func_00f205c8();
    func_00123030(D_00F22E94, 0, 0);
    D_00304B6C = &func_00f209e8;
}

void func_00f214f8(void) {
    memset(&D_00FC1A60, 0, 0x280);
    func_0011ef10(0x21728, &func_00f21450);
}

void func_00f21a20(void) {
    memset(&D_00FC1CE0, 0, 0x100);
    func_00f21530((s8 *)&D_00FC1CE0 + 0xF0, 0xA, &D_00FC1CE0);
    if (func_0011ef38(&func_00f218b8) == 0) {
        func_0011ef10(0x28487, &func_00f218f8);
    }
}

s32 func_00f22010(void) {
    s32 *var_s0;
    s32 var_s1;
    s32 var_v0;

    var_v0 = 4;
    if (D_00FC0E48 != 0x65) {
        var_s1 = 9;
        var_s0 = &D_00FC1DE0;
        do {
            if (*var_s0 != 0) {
                func_00f21fc0(var_s0);
            }
            var_s1 -= 1;
            var_s0 += 104;
        } while (var_s1 >= 0);
        var_v0 = 0;
    }
    return var_v0;
}

void func_00f22ac0(void) {
    D_00FC2EE8 = 0;
    memset(&D_00FC2E20, 0, 0xC8);
    func_0011ef10(0x21728, &func_00f229f0);
}
