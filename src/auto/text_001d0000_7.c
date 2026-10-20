/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00104300(M2C_UNK);
M2C_UNK func_001043f8(M2C_UNK);
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
M2C_UNK func_00120748(M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK);
M2C_UNK func_00141b10(s32, void *);
M2C_UNK func_0022dee0(M2C_UNK);
extern M2C_UNK D_0038D170;
extern M2C_UNK D_0039A580;
extern M2C_UNK D_00490620;
extern M2C_UNK D_0062A630; /* src/data/bss_0062.c: u8 D_0062A630[0x10] */
extern M2C_UNK D_00F20000;
extern M2C_UNK func_001c1df8;
extern M2C_UNK func_001d09a0;
extern M2C_UNK func_001d9d48;
extern M2C_UNK func_001dd5c0;
extern f32 D_002BBE00;
extern s32 D_0029B410;
extern s32 D_0029B414;
extern s32 D_002C5958;
extern s32 D_0037A378;
extern s32 D_0038CCC4;
extern s64 D_00389C90[];
void *func_0011f090(M2C_UNK *, M2C_UNK, M2C_UNK *);
void func_001763f0(s32);
void func_001c19f8(s32, s32);

s32 func_001d07a8(void) {
    func_00104300(1);
    D_00389C90[1551] = (s64) (D_00389C90[1551] | 1);
    return 2;
}

s32 func_001d07e0(void) {
    func_001043f8(1);
    D_00389C90[1551] = (s64) (D_00389C90[1551] & ~1);
    return 2;
}

s32 func_001d09d8(void) {
    func_00120748(&D_00490620, &D_00F20000, &func_001d09a0, 0);
    D_00389C90[1551] = (s64) (D_00389C90[1551] | 0x2000);
    return 2;
}

void func_001d3160(void) {
    s8 *var_a4;
    s32 temp_v0;
    s32 temp_v0_2;
    void *temp_a3;

    if (D_0038CCC4 == 0) {
        var_a4 = &D_0038D170;
    } else {
        var_a4 = &D_0039A580;
    }
    temp_a3 = var_a4 + 4;
    temp_v0 = M2C_FIELD(var_a4, s32 *, 0x180) + 1;
    M2C_FIELD(var_a4, s32 *, 0x180) = temp_v0;
    M2C_FIELD(((temp_v0 * 4) + temp_a3), s32 *, 0x180) = 1;
    temp_v0_2 = M2C_FIELD(var_a4, s32 *, 0x180) + 1;
    M2C_FIELD(var_a4, s32 *, 0x180) = temp_v0_2;
    M2C_FIELD(((temp_v0_2 * 4) + temp_a3), s32 *, 0x180) = 0;
    func_001c19f8((s32) var_a4, 2);
}

s32 func_001d64f8(void *arg0) {
    s32 sp[60];
    s32 temp_s1;

    temp_s1 = arg0 + 4;
    func_00141b10(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180), sp);
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = M2C_FIELD(sp, M2C_UNK *, 0x3C);
    return 2;
}

s32 func_001d6558(void *arg0) {
    s32 sp[60];
    s32 temp_s1;

    temp_s1 = arg0 + 4;
    func_00141b10(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180), sp);
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = M2C_FIELD(sp, M2C_UNK *, 0x44);
    return 2;
}

s32 func_001d87b8(void) {
    D_00389C90[1551] = (s64) (D_00389C90[1551] | 1);
    return 2;
}

s32 func_001d87d8(void) {
    D_00389C90[1551] = (s64) (D_00389C90[1551] & ~1);
    D_0037A378 &= ~1;
    D_002BBE00 = 1.0f;
    D_002C5958 &= ~0x400;
    return 2;
}

s32 func_001d9d90(void) {
    func_0011ef10(0xC352, &func_001d9d48);
    D_00389C90[1551] = (s64) (D_00389C90[1551] | 4);
    return 2;
}

s32 func_001d9dd0(void) {
    D_00389C90[1551] = (s64) (D_00389C90[1551] & ~4);
    return 2;
}

void func_001daca8(void) {
    D_00389C90[1551] = (s64) (D_00389C90[1551] & ~0x20);
}

s32 func_001dbb20(void) {
    D_00389C90[1551] = (s64) (D_00389C90[1551] & ~0x80);
    return 2;
}

s32 func_001dbb40(void) {
    D_00389C90[1551] = (s64) (D_00389C90[1551] | 0x80);
    return 2;
}

void func_001dbcb8(void) {
    D_00389C90[1551] = (s64) (D_00389C90[1551] & ~0x100);
}

void func_001dbd90(s32 arg0, s32 arg1, s32 arg2) {
    func_001763f0(arg2);
    D_00389C90[1551] = (s64) (D_00389C90[1551] & ~0x200);
}

s32 func_001dca00(void) {
    func_0022dee0(0xFFFF);
    func_0011ef10(0xC351, &func_001c1df8);
    D_00389C90[1551] = (s64) (D_00389C90[1551] | 0x1000);
    return 6;
}

s32 func_001dd148(void) {
    func_0011f130(&D_0062A630, 0);
    return 0;
}

s32 func_001dfaa0(void *arg0) {
    void *temp_v0;

    if ((D_0029B410 != 0) && (D_0029B414 != 0)) {
        temp_v0 = func_0011f090(&D_0062A630, 0, &func_001dd5c0);
        M2C_FIELD(temp_v0, s32 *, 0x2C) = 0xB;
        M2C_FIELD(temp_v0, s32 *, 0x28) = (s32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}
#include "data/data_0029.h"
