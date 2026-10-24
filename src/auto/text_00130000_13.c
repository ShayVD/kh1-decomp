/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0052.h"
M2C_UNK func_001318e8(void *, u16, void *);
M2C_UNK func_00267328(void *, void *, void *);
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00308CDC.h"
f32 atan2f(f32, f32);
s32 func_00122ff8(void *);
s32 func_001375f0(s32);
s32 func_00138988();
s32 func_001399a8(s32, s32);
s32 func_00139a90(s32, s32);
s32 func_0013daa8();
s32 func_0013f330(s32, s32);
s32 func_0013f478(s32, s32);
s32 func_0014f5c8(s32);
s32 func_0014f600(s32);
void func_00130040(s32, s32);
void func_00130340(s32, s32, f32);
void func_00130398(s32, s32, f32);
void func_00130578(s32, s32, f32);
void func_00138a20(s32, s32, f32);
void func_0014f658(s32, s32);
void func_002675a8(s32, s32);

void func_00136cc0(void *arg0) {
    s32 sp[16];
    void *temp_a0;
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x3A0);
    if ((func_00122ff8(temp_s1) != 0) && ((s32) ((u64) M2C_FIELD(M2C_FIELD(arg0, void **, 0x3A0), u64 *, 0x370) >> 0x2B) & 1)) {
        func_001318e8(temp_s1, M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x50), sp);
        temp_a0 = arg0 + 0xD0;
        func_00267328(temp_a0, sp, temp_a0);
    }
}

s32 func_001389e8(void *arg0) {
    s32 var_v0;

    var_v0 = 1;
    if (!((u32) (M2C_FIELD(arg0, s32 *, 0x164) - 0x48) >= 0x23U)) {
        return var_v0;
    }
    var_v0 = func_00138988() != 0;
    return var_v0;
}

void func_00138d88(s32 arg0, s32 arg1, f32 fparg0) {
    s32 sp[4];
    func_00130040(arg0, 0x4E);
    if (fparg0 < 0.0f) {
        func_00130340(arg0, 0x0100004E, 0.0f);
    } else {
        func_00130340(arg0, 0x0100004F, 0.0f);
    }
    func_00130578(arg0, 6, 8.0f);
    func_002675a8((s32) sp, arg1 + 0x10);
    M2C_FIELD(sp, f32 *, 0xC) = M2C_FIELD((*(void **)&D_00308CDC), f32 *, 0x38) * M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), f32 *, 0xC4);
    func_00138a20(arg0, (s32) sp, 2e+01f);
}

void func_00139b98(s32 arg0, s32 arg1) {
    if (func_0014f5c8(arg0) != 0) {
        func_001399a8(arg0, arg1);
        return;
    }
    if ((func_0014f600(arg0) != 0) || ((s32) ((u64) M2C_FIELD(arg0, u64 *, 0x370) >> 0x3D) & 1)) {
        func_00139a90(arg0, arg1);
        return;
    }
    func_001399a8(arg0, arg1);
}

s32 func_0013daf8(void) {
    s32 temp_v0;
    s32 var_v0;

    temp_v0 = func_0013daa8();
    var_v0 = 0;
    if (temp_v0 < 0) {
        return var_v0;
    }
    var_v0 = ((M2C_UNK *)&D_002E26A0)[temp_v0];
    return var_v0;
}

s32 func_0013f618(s32 arg0, s32 arg1) {
    if ((func_001375f0(arg0) != 0) && (func_0013f478(arg0, arg1) != 0)) {
        func_0014f658(arg0, 0xD);
        func_00130398(arg0, func_0013f330(arg0, 0x1D) | 0x01000000, 0.0f);
        func_00130578(arg0, func_0013f330(arg0, 0x1B) | 0x40000000, 0.0f);
        M2C_FIELD(arg0, f32 *, 0x2C) = 0.0f;
        return 1;
    }
    return 0;
}

void func_0013f6d0(s32 arg0, s32 arg1) {
    func_00130398(arg0, func_0013f330(arg0, 0x23) | 0x01000000, 8.0f);
    func_00130578(arg0, 0x40000000, 0.0f);
    func_002675a8(arg1, arg0 + 0x30);
    M2C_FIELD(arg1, f32 *, 0xC) = 0.0f;
    M2C_FIELD(arg0, f32 *, 0x150) = atan2f(M2C_FIELD(arg1, f32 *, 0), M2C_FIELD(arg1, f32 *, 8));
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xFFDFFFFF);
}

void func_0013f8a8(s32 arg0, s32 arg1, void *arg2) {
    f32 temp_f1;

    temp_f1 = M2C_FIELD(arg2, f32 *, 0xC);
    if (temp_f1 > 0.0f) {
        if ((M2C_FIELD(arg2, f32 *, 4) > 0.0f) && (temp_f1 > 0.8f)) {
            M2C_FIELD(arg2, f32 *, 0xC) = 12.0f;
            return;
        }
        M2C_FIELD(arg2, f32 *, 0xC) = 2.0f;
    }
}
