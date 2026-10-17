/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00130c28(void *, f32, f32);
M2C_UNK func_001655e0(s32, s32, s32, f32);
f32 func_00130d20();
f32 func_00130dd0(void *);
s32 func_00130340(s32, s32, f32);
s32 func_0013dbe0(s32, s32);
s32 func_001477c8(s32);
s32 func_0014a408(void);
s32 func_0014a908(s32, s32, s32);
void func_0012c880(s32, s32);
void func_00137448(s32);
void func_001487f8(s32, s32, s32, s32);
void func_00157a30(s32, s32, s32);

s32 func_00130e48(void *arg0, s32 arg1) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f1;
    f32 temp_f20;
    f32 var_f0;
    s32 var_v0;

    var_f0 = func_00130d20();
    if ((var_f0 >= 0.0f) || (var_f0 = func_00130dd0(arg0), var_v0 = 0, (var_f0 >= 0.0f))) {
        temp_f1 = M2C_FIELD(arg0, f32 *, 0x280);
        temp_f20 = temp_f1 * var_f0;
        temp_f12 = M2C_FIELD(arg0, f32 *, 0x16C);
        temp_f0 = temp_f20 - temp_f12;
        if (!(M2C_FIELD(arg0, s32 *, 0x160) & 1) && (temp_f0 > 0.0f) && (temp_f0 < temp_f1)) {
            func_00130c28(arg0, temp_f12, temp_f20);
        }
        M2C_FIELD(arg0, f32 *, 0x16C) = temp_f20;
        func_001655e0(arg1, M2C_FIELD(arg0, s32 *, 0x15C), *(M2C_UNK *)((s32) ((M2C_FIELD(arg0, s32 *, 0x168) * 4)) + (s32) (M2C_FIELD(arg0, s32 *, 0x1D4))), temp_f20);
        var_v0 = 1;
    }
    return var_v0;
}

void func_00135740(s32 arg0, s32 arg1, s32 arg2) {
    func_00137448(arg0);
    M2C_FIELD(arg0, s32 *, 0x3A0) = arg1;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), s16 *, 0x50) = (s16) arg2;
}

s32 func_0013dc10(s32 arg0, s32 arg1) {
    s16 temp_v0_2;
    s32 temp_s0;
    s32 temp_v0_3;
    s8 temp_a1;
    s8 temp_a1_2;
    s8 temp_v1;
    void *temp_a0;
    void *temp_v0;

    temp_v0 = func_0013dbe0(arg0, arg1);
    temp_v0_2 = M2C_FIELD(temp_v0, s16 *, 0);
    if (temp_v0_2 >= 0) {
        func_00130340(arg0, temp_v0_2 | 0x01000000, 0.0f);
    }
    temp_s0 = func_0014a408();
    temp_v0_3 = func_0014a908(arg0, temp_s0, func_001477c8(M2C_FIELD(temp_v0, s32 *, 4)));
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x14C), s32 *, 0x2C) = temp_v0_3;
    M2C_FIELD(temp_v0_3, s64 *, 0) = (s64) (M2C_FIELD(temp_v0_3, s64 *, 0) | 0x400000);
    M2C_FIELD(temp_v0_3, u8 *, 0xA8) = (u8) M2C_FIELD(temp_v0, u8 *, 0xC);
    M2C_FIELD(temp_v0_3, u8 *, 0xA9) = (u8) M2C_FIELD(temp_v0, u8 *, 0xD);
    M2C_FIELD(temp_v0_3, u8 *, 0xAA) = (u8) M2C_FIELD(temp_v0, u8 *, 0xE);
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x14C), s32 *, 0x14) != 0) {
        temp_a1 = M2C_FIELD(temp_v0, s8 *, 2);
        if (temp_a1 >= 0) {
            func_0012c880(arg0, (s32) temp_a1);
        }
        temp_a1_2 = M2C_FIELD(temp_v0, s8 *, 3);
        if (temp_a1_2 >= 0) {
            func_001487f8(M2C_FIELD(M2C_FIELD(arg0, void **, 0x14C), s32 *, 0x14), (s32) temp_a1_2, arg0, 0x30);
        }
    }
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x14C), s8 *, 0x28) = (s8) arg1;
    temp_a0 = M2C_FIELD(arg0, void **, 0x14C);
    M2C_FIELD(temp_a0, s32 *, 0x28) = (s32) (M2C_FIELD(temp_a0, s32 *, 0x28) | 0x10000);
    temp_v1 = M2C_FIELD(temp_v0, s8 *, 0xF);
    if (temp_v1 >= 0) {
        func_00157a30(arg0, (s32) temp_v1, 0);
    }
    return (s32) temp_v0;
}
