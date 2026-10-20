/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_00615E68;
extern void *D_00615E60;
void func_00267328(s32, void *, s32);
void func_00267620(void *);

void pppChrSclXYZMatrixFrame(s32 arg0, void *arg1) {
    s32 sp[16];    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f2;
    f32 temp_f3;
    s32 temp_a0;

    func_00267620(sp);
    temp_f3 = M2C_FIELD(arg1, f32 *, 4);
    temp_f0 = M2C_FIELD(D_00615E60, f32 *, 0x40);
    temp_f2 = M2C_FIELD(arg1, f32 *, 8);
    temp_f0_2 = temp_f0 + (temp_f0 * temp_f3);
    M2C_FIELD(sp, f32 *, 0x0) = temp_f0_2;
    if (temp_f2 < temp_f0_2) {
        M2C_FIELD(sp, f32 *, 0x0) = temp_f2;
    }
    M2C_FIELD(sp, f32 *, 0x28) = M2C_FIELD(sp, f32 *, 0x0);
    temp_f1 = M2C_FIELD(D_00615E60, f32 *, 0x44);
    temp_f1_2 = temp_f1 + (temp_f1 * temp_f3);
    M2C_FIELD(sp, f32 *, 0x14) = temp_f1_2;
    if (temp_f2 < temp_f1_2) {
        M2C_FIELD(sp, f32 *, 0x14) = temp_f2;
    }
    temp_a0 = D_00615E68 + 0x10;
    func_00267328(temp_a0, sp, temp_a0);
}

void pppChrSclXZMatrixFrame(s32 arg0, void *arg1) {
    s32 sp[16];    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f2;
    s32 temp_a0;

    func_00267620(sp);
    temp_f0 = M2C_FIELD(D_00615E60, f32 *, 0x40);
    temp_f2 = M2C_FIELD(arg1, f32 *, 8);
    temp_f0_2 = temp_f0 + (temp_f0 * M2C_FIELD(arg1, f32 *, 4));
    M2C_FIELD(sp, f32 *, 0x0) = temp_f0_2;
    if (temp_f2 < temp_f0_2) {
        M2C_FIELD(sp, f32 *, 0x0) = temp_f2;
    }
    M2C_FIELD(sp, f32 *, 0x28) = M2C_FIELD(sp, f32 *, 0x0);
    temp_a0 = D_00615E68 + 0x10;
    func_00267328(temp_a0, sp, temp_a0);
}

void pppChrSclYMatrixFrame(s32 arg0, void *arg1) {
    s32 sp[16];    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f2;
    s32 temp_a0;

    func_00267620(sp);
    temp_f0 = M2C_FIELD(D_00615E60, f32 *, 0x44);
    temp_f2 = M2C_FIELD(arg1, f32 *, 8);
    temp_f0_2 = temp_f0 + (temp_f0 * M2C_FIELD(arg1, f32 *, 4));
    M2C_FIELD(sp, f32 *, 0x14) = temp_f0_2;
    if (temp_f2 < temp_f0_2) {
        M2C_FIELD(sp, f32 *, 0x14) = temp_f2;
    }
    temp_a0 = D_00615E68 + 0x10;
    func_00267328(temp_a0, sp, temp_a0);
}
#include "data/bss_0061_mixed.h"
