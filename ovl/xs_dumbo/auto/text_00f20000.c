/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0012cc38(M2C_UNK, M2C_UNK);
M2C_UNK func_00f229c8(s32, s32, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK);
M2C_UNK func_00f22e68(void *);
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK sceVu0ApplyMatrix(s32, void *, s32);
M2C_UNK sceVu0InversMatrix(void *);
extern M2C_UNK *D_00304B6C;
extern M2C_UNK D_002C58A0;
extern M2C_UNK D_00F23220;
extern M2C_UNK D_00F27670;
extern M2C_UNK D_00F3CA90;
extern M2C_UNK D_00F44A90;
extern M2C_UNK func_00f202b8;
extern M2C_UNK func_00f20920;
extern M2C_UNK func_00f212c8;
extern s32 D_00F23200;
extern s32 D_00F23204;
extern s32 D_00F23208;
extern s32 D_00F23214;
extern s32 D_00F44AA0;
extern void *D_00F3CA88;
f32 func_00135800(s32, f32, f32);
f32 func_0014cc88(s32, f32);
s32 func_0011ef38(M2C_UNK *);
s32 func_0012cab8(s32);
s32 func_00130340(s32, s32, f32);
s32 func_00130578(s32, s32, f32);
s32 func_00147ed8(s32, s32, s32, s32);
s32 func_0014f658(s32, s32);
s32 sceVu0CopyVector(s32, s32);
void *func_00147d18(M2C_UNK *);
void func_001315c0(s32, s32, s32, f32);
void func_00137318(s32);
void func_00f21970(void);
void func_00f22e88(s32);

void func_00f200b0(s32 arg0, f32 fparg0) {
    func_00130340(D_00F23200, arg0, fparg0);
    func_00130340(D_00F23204, arg0, fparg0);
}

void func_00f20100(s32 arg0, f32 fparg0) {
    func_00130578(D_00F23200, arg0, fparg0);
    func_00130578(D_00F23204, arg0, fparg0);
}

void func_00f20150(s32 arg0) {
    s32 sp[4];
    if (arg0 == 0x64) {
        func_0014f658(D_00F23200, 0x22);
        func_001315c0(D_00F23204, 0x8003, (s32) sp, 0.0f);
        M2C_FIELD(sp, f32 *, 0x4) += -38.5f;
        func_00147ed8(D_00F23208, 0xA, 0x4E20, (s32) sp);
        func_00130340(D_00F23204, 0xCB, 0.0f);
        func_00135800(D_00F23204, 0.0f, 3e+01f);
        *(M2C_UNK *)D_00F23204 = (s32) (*(M2C_UNK *)D_00F23204 | 8);
        func_00137318(D_00F23204);
        func_00f21970();
        func_0012cab8(0);
    }
    func_00f22e88(arg0);
}

void func_00f203a0(void) {
    M2C_FIELD(func_00147d18(&func_00f202b8), s32 *, 0x14) = 0;
}

void func_00f20770(void) {
    func_0012cc38(0, 0x46);
}

s32 func_00f20900(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 == 0x46) {
        D_00F23214 = 1;
    }
    return 0;
}

void func_00f209b8(void) {
    D_00304B6C = &func_00f20920;
}

void func_00f20a60(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = (s32) ((M2C_FIELD(arg0, s32 *, 0) & 0xFCFFFF7F) | 2);
    *M2C_FIELD(D_00F3CA88, s8 **, 0x10) = 1;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), f32 *, 0xCC) = 0.19634955f;
}

s32 func_00f20fd8(s32 arg0) {
    func_0014cc88(arg0, 0.0f);
    return sceVu0CopyVector(arg0 + 0x3C0, (s32) &D_002C58A0);
}

void func_00f21128(void) {
    D_00F44AA0 = 0;
}

s32 func_00f213d0(void) {
    return func_0011ef38(&func_00f212c8) != 0;
}

void func_00f217e8(s32 arg0, s32 arg1) {
    memset(&D_00F44A90, 0, 0x10);
    func_00f229c8(arg0, arg1, &D_00F23220, &D_00F27670, &D_00F3CA90, 0x800);
    func_00f22e68((s8 *)&D_00F44A90 + 4);
}

void func_00f21c60(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[16];
    sceVu0InversMatrix(sp);
    sceVu0ApplyMatrix(arg0, sp, arg2);
}

s32 func_00f23140(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_hi;
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 8);
    temp_hi = (s32) ((M2C_FIELD(arg0, s32 *, 0xC) - arg1) + temp_v1) % temp_v1;
    M2C_FIELD(arg0, s32 *, 0x10) = temp_hi;
    return sceVu0CopyVector(arg2, M2C_FIELD(arg0, s32 *, 0) + (temp_hi * 0x10));
}
