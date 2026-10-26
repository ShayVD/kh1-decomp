/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001c0da0(s32, M2C_UNK, void *);
M2C_UNK func_001c0e80(s32, M2C_UNK, void *);
M2C_UNK sceVu0ApplyMatrix(M2C_UNK *, void *, s32);
M2C_UNK sceVu0CameraMatrix(s32, M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK sceVu0RotMatrixX(void *, void *, f32);
M2C_UNK sceVu0RotMatrixY(void *, void *, f32);
M2C_UNK sceVu0UnitMatrix(void *);
extern M2C_UNK D_0108FA98;
extern f32 D_00FB5BCC;
extern f32 D_00FB5BD0;
extern s32 D_00FB4C00;
extern s32 D_00FB4C04;
extern s32 D_00FB4D7C;
extern s32 D_00FB4D80;
extern s32 D_00FB4D84;
extern s32 D_00FB5BB0;
extern s32 D_00FB5EAC;
extern s32 D_00FB6164;
extern s32 D_0108F188;
extern s32 D_0108F194;
extern s32 D_0108F198;
extern s32 D_0108F1A0;
extern s32 D_0108F1B8;
extern s32 D_0108F308;
extern s32 D_0108F6B0;
extern u32 D_00FB4D78;
s32 func_001f4390(s32);
void func_001f3840(s32);
void func_001f8f30(void);
void func_00203788(s32, s32, s32, s32, s32);

void func_00f70770(s32 arg0) {
    if (M2C_FIELD(arg0, s16 *, 0xD8) >= 2) {
        func_00203788(arg0, D_00FB4C00, 6, D_00FB4C00 + D_00FB4C04, D_00FB4D78 | (D_00FB4D84 << 0x18) | ((D_00FB4D80 << 0x10) | (D_00FB4D7C << 8)));
    }
    func_001f8f30();
    if ((func_001f4390(arg0) != 0) && (D_0108F188 != 0)) {
        func_001f3840(arg0);
    }
}

s32 func_00f71b58(void) {
    return D_0108F308;
}

void func_00f749b8(s32 arg0, s32 arg1, s32 arg2) {
    D_0108F194 = arg0;
    D_0108F198 = arg1;
    D_0108F1A0 = arg2;
}

void func_00f78680(s32 arg0) {
    D_0108F1B8 = arg0;
}

void func_00f78828(s32 arg0) {
    D_0108F6B0 = arg0;
}

void func_00f78bb0(s32 arg0) {
    D_00FB5BB0 = arg0;
}

s32 func_00f792b8(void) {
    return D_00FB5EAC;
}

void func_00f7bd10(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp[28];
    sceVu0UnitMatrix(sp);
    sceVu0RotMatrixX(sp, sp, M2C_FIELD(arg1, f32 *, 0));
    sceVu0RotMatrixY(sp, sp, M2C_FIELD(arg1, f32 *, 4));
    sceVu0ApplyMatrix(&M2C_FIELD(sp, M2C_UNK *, 0x50), sp, arg3);
    sceVu0ApplyMatrix(&M2C_FIELD(sp, M2C_UNK *, 0x60), sp, arg4);
    sceVu0ApplyMatrix(&M2C_FIELD(sp, M2C_UNK *, 0x40), sp, arg2);
    sceVu0CameraMatrix(arg0, &M2C_FIELD(sp, M2C_UNK *, 0x40), &M2C_FIELD(sp, M2C_UNK *, 0x50), &M2C_FIELD(sp, M2C_UNK *, 0x60));
}

s32 func_00f7c828(s32 arg0) {
    return *(M2C_UNK *)((s8 *)(s8 *)&D_0108FA98 + (arg0 * 4));
}

void func_00f7c840(s32 arg0) {
    *(M2C_UNK *)((s8 *)(s8 *)&D_0108FA98 + (arg0 * 4)) = 2;
}

void func_00f7c860(s32 arg0) {
    *(M2C_UNK *)((s8 *)(s8 *)&D_0108FA98 + (arg0 * 4)) = 1;
}

f32 func_00f7d060(f32 fparg0) {
    f32 var_f0;

    var_f0 = fparg0;
    if (var_f0 < D_00FB5BCC) {
        var_f0 = D_00FB5BCC;
    }
    if (D_00FB5BD0 < var_f0) {
        var_f0 = D_00FB5BD0;
    }
    return var_f0;
}

s32 func_00f7d098(void) {
    return D_00FB6164;
}

s8 func_00f7f5d8(s32 arg0) {
    s32 sp[4];
    func_001c0da0(arg0 + 0x2F0, 1, sp);
    return M2C_FIELD(sp, M2C_UNK *, 0x0);
}

void func_00f7f600(s32 arg0, s8 arg1) {
    s32 sp[4];
    M2C_FIELD(sp, s8 *, 0x0) = arg1;
    func_001c0e80(arg0 + 0x2F0, 1, sp);
}
