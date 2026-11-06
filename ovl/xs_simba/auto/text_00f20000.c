/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00176310(s32);
M2C_UNK sceVu0CopyVector(s32, s32);
extern M2C_UNK D_00F21B80;
extern M2C_UNK D_00FA6A88;
extern M2C_UNK D_00FA6F38;
extern s32 D_00F21C34;
extern s32 D_00F21C38;
extern s32 D_00F21C3C;
extern s32 D_00F21C40;
extern s32 D_00F21C44;
extern s32 D_00FA6A10;
extern s32 D_00FA6A90;
extern s32 D_00FA6A94;
extern u8 D_002E3190;
#ifdef KH1_PS2
f32 func_001224c8(s32, s32, s32, f32);
#else /* the definition is void: an x86 caller of an f32 one pops an empty x87 stack */
void func_001224c8(s32, s32, s32, f32);
#endif
#ifdef KH1_PS2
f32 func_00135800(s32, f32, f32);
#else /* the definition is void: an x86 caller of an f32 one pops an empty x87 stack */
void func_00135800(s32, f32, f32);
#endif
f32 func_0014cce0(s32, f32);
s32 func_001226f0(s32, s32, s32);
s32 func_00130340(s32, s32, f32);
s32 func_00130578(s32, s32, f32);
s32 func_0013aac0(s32);
s32 func_00148768(s32, s32, s32, s32, f32);
s32 func_00148968(s32, s32, s32);
s32 func_0014f658(s32, s32);
s32 func_00242ba0(void);
void func_00148068(s32, f32);
void func_00f200a0(s32);
void func_00f202e8(s32);
void func_00f21ad0(s32, s32, s32);

void func_00f20140(void) {
    s32 temp_v0;

    temp_v0 = func_001226f0(1, 9, 0);
    D_00FA6A90 = temp_v0;
    func_001224c8(temp_v0, (s32) &D_00F21B80, 0, 3e+01f);
}

void func_00f20270(void) {
    func_00148068(M2C_FIELD(&D_00FA6A88, s32 *, 0), 3e+01f);
    func_00148068(M2C_FIELD(&D_00FA6A88, s32 *, 4), 3e+01f);
}

void func_00f202b8(void) {
    func_00176310(M2C_FIELD(&D_00FA6A88, s32 *, 0));
    func_00176310(M2C_FIELD(&D_00FA6A88, s32 *, 4));
}

void func_00f20570(s32 arg0) {
    s32 temp_a2;
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0xC);
    if (temp_v0 >= 0) {
        func_00148768(D_00F21C44, temp_v0, D_00F21C34, 0x30, 1.0f);
    }
    temp_a2 = M2C_FIELD(arg0, s32 *, 0x10);
    if (temp_a2 >= 0) {
        func_00148968(D_00F21C38, D_00F21C44, temp_a2);
    }
    D_00F21C3C = arg0;
    D_00F21C40 = 1;
    if (D_00FA6A94 == 0) {
        func_00242ba0();
        D_00FA6A94 = 1;
    }
}

s32 func_00f20ab8(f32 *arg0, f32 *arg1) {
    return (s32) (*arg0 - *arg1);
}

void func_00f20e08(s32 arg0) {
    func_0013aac0(arg0);
    func_00130340(arg0, 0xC8, 8.0f);
    func_00130578(arg0, 0xC9, 0.0f);
    *(M2C_UNK *)arg0 = (s32) (*(M2C_UNK *)arg0 | 0x200000);
    D_00F21C3C = 0;
}

void func_00f20e68(s32 arg0) {
    *(M2C_UNK *)arg0 = (s32) (*(M2C_UNK *)arg0 & 0xFFDFFFFF);
    D_00F21C40 = 0;
    if (D_00FA6A10 == 1) {
        func_00f202e8(2);
    }
}

void func_00f20ec0(s32 arg0) {
    if (((u32) (D_002E3190 - 0x5C) >= 2U) && (M2C_FIELD(arg0, s32 *, 0x164) == 0xC9)) {
        if (D_00F21C40 != 0) {
            func_00f202e8(3);
            return;
        }
        func_00130340(arg0, 0x010000CA, 0.0f);
        func_00130578(arg0, 0x40100000, 0.0f);
        func_0014f658(D_00F21C34, 0);
        func_00f202e8(2);
        return;
    }
    func_00f200a0(arg0);
}

void func_00f20f88(void *arg0) {
    sceVu0CopyVector(arg0 + 0x20, arg0 + 0x30);
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
}

s32 func_00f20fb8(void *arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = 2;
    if (arg1 == 0) {
        var_v0 = M2C_FIELD(arg0, s32 *, 0x70);
    }
    return var_v0;
}

s32 func_00f21080(s32 arg0) {
    s32 temp_v0;

    func_0014cce0(arg0, 3e+02f);
    temp_v0 = *(M2C_UNK *)arg0 & ~0x400;
    *(M2C_UNK *)arg0 = temp_v0;
    return temp_v0;
}

void func_00f210c0(s32 arg0) {
    func_00f21ad0((s32) &D_00FA6F38, 1, arg0 + 0x10);
    func_00130340(arg0, 0x01000007, 0.0f);
    func_00130578(arg0, 0x40000000, 0.0f);
    func_00135800(arg0, 0.0f, 0.0f);
    func_00135800(arg0, 1.0f, 12.0f);
}

void func_00f21898(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 8) = arg2;
    sceVu0CopyVector(arg1, arg3);
}
