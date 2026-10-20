/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0049.h"
#include "data/bss_004D.h"

M2C_UNK func_002672f8(void *, s32, void *);
M2C_UNK func_00267620(void *);
extern f32 D_002BBDFC;
extern f32 D_00494898;
extern s32 D_002A6204;
extern s32 D_002A6238;
extern s32 D_002B6480;
extern s32 D_002BC070;
extern s32 D_002BC0BC;
extern s32 D_002BC734;
extern s32 D_002BC738;
extern s32 D_00494894;
extern s32 D_00494A88; /* src/data/bss_0049.c: f32 D_00494A88 */
extern s32 D_00494A90;
extern s32 D_00494A94;
extern s32 D_00494A98;
extern s32 D_00494A9C;
extern s32 D_004D9240;
s32 func_00121e28(M2C_UNK, s32 *);

void func_00102d20(s32 arg0, void *arg1, s32 *arg2, s32 *arg3) {
    func_002672f8(arg1, arg0, arg1);
    *arg2 = (s32) ((M2C_FIELD(arg1, f32 *, 0) * 16.0f) + 4096.0f);
    *arg3 = (s32) ((M2C_FIELD(arg1, f32 *, 4) * 16.0f) + 3072.0f);
}

void func_00103828(void) {
    D_002BC734 = 0;
}

s32 func_00103838(void) {
    s32 temp_f1;

    temp_f1 = (s32) ((f32) D_00494894 - D_002BBDFC);
    D_00494894 = temp_f1;
    if (temp_f1 <= 0) {
        D_002A6204 = 0xFF;
        return 4;
    }
    D_002A6204 = (s32) (255.0f - (D_00494898 * (f32) temp_f1));
    return 0;
}

s32 func_00103920(void) {
    s32 temp_f1;

    temp_f1 = (s32) ((f32) D_00494894 - D_002BBDFC);
    D_00494894 = temp_f1;
    if (temp_f1 <= 0) {
        D_002A6204 = 0;
        return 4;
    }
    D_002A6204 = (s32) (D_00494898 * (f32) temp_f1);
    return 0;
}

void func_00104288(void) {
    D_002BC738 = 0;
}

void func_00104480(s32 arg0, void *arg1) {
    func_00267620(arg1);
    M2C_FIELD(arg1, s32 *, 0x60) = arg0;
}

void func_001044b8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x60) = arg0;
}

void func_00104fa8(s32 arg0, f32 *arg1) {
    *arg1 = M2C_FIELD(((arg0 * 0x14) + D_002A6238), f32 *, 0xC);
}

s32 func_001063c8(void) {
    s32 var_a1;

    var_a1 = 0;
    if ((D_002BC070 == 0) || (D_002BC0BC == 0x80)) {
        var_a1 = 1;
    }
    return var_a1;
}

void func_001066f8(void) {
    D_00494A88 = 0;
}

void func_00106910(void) {
    D_002B6480 = 0;
}

s32 func_00106920(void *arg0) {
    f32 temp_f2;

    temp_f2 = M2C_FIELD(arg0, f32 *, 0x10) + D_002BBDFC;
    M2C_FIELD(arg0, f32 *, 0x10) = temp_f2;
    if (M2C_FIELD(arg0, f32 *, 0x18) <= temp_f2) {
        D_002BC0BC = 0x80;
        return 4;
    }
    D_002BC0BC = (s32) (M2C_FIELD(arg0, f32 *, 0x14) * temp_f2);
    return 0;
}

s32 func_00106a08(void *arg0) {
    f32 temp_f2;

    temp_f2 = M2C_FIELD(arg0, f32 *, 0x10) - D_002BBDFC;
    M2C_FIELD(arg0, f32 *, 0x10) = temp_f2;
    if (temp_f2 <= 0.0f) {
        D_002BC0BC = 0;
        return 4;
    }
    D_002BC0BC = (s32) (M2C_FIELD(arg0, f32 *, 0x14) * temp_f2);
    return 0;
}

void func_00106c10(void) {
    D_00494A98 = 0;
    D_00494A9C = 0;
    D_00494A90 = func_00121e28(0x2000, &D_00494A90);
    D_00494A94 = func_00121e28(0x8000, &D_00494A94);
}

void func_0010fe80(void) {
    D_004D9240 = 0;
}

void func_0010fe90(void) {
    D_004D9240 = 1;
}
