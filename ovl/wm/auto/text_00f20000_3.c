/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00f64b88();
extern M2C_UNK D_00FBB5D4;
extern s32 D_002BC148[];
extern s32 D_00F8508C;
extern s32 D_00F85090;
extern s32 D_00F87048;
extern s32 D_00F87310[];
extern s32 D_00FBA800;
extern s32 D_00FBB570;
extern s32 D_00FBB574;
extern s32 D_00FBB578;
extern s8 D_00FBDFB8;
s32 func_0010a0d8(void);
s32 func_001bb4f0(void);
s32 func_00f2ab98(s32);
s32 func_00f2b348(s32);
s32 func_00f2b808();
s32 func_00f2cae8();
s32 func_00f3b4e0(s32);
s32 func_00f68770(s32, s32, s32, s32, s32);
s32 sceVu0CopyVector(s32, s32);
s32 sceVu0Normalize();
u32 func_00f64c38(M2C_UNK, s32);
void func_0010a3c0(void);
void func_00113028();
void func_00176c60(s32);
void func_001becb8(s32, s32, s32);
void func_001bf098(s32, s32);
void func_001bfac8(void);
void func_001efaf0();
void func_00248b00(void);
void func_00f680a0(void);

void func_00f20228(s32 arg0) {
    s16 temp_a0;
    s16 temp_a1;
    void *temp_v0;

    func_00248b00();
    func_00f680a0();
    func_0010a0d8();
    func_0010a3c0();
    func_00176c60(0);
    temp_v0 = func_00f2b348(arg0);
    temp_a0 = M2C_FIELD(temp_v0, s16 *, 0);
    temp_a1 = M2C_FIELD(temp_v0, s16 *, 4);
    D_002BC148[3] = (s32) temp_a1;
    D_002BC148[2] = (s32) temp_a0;
    func_001efaf0();
    func_00113028(func_001bb4f0());
    D_00FBA800 = 3;
    for (;;) {
        func_001bfac8();
    }
}

s32 func_00f24f50(s32 arg0) {
    switch (arg0) {
    case 8:
        return 0x12;
    case 4:
        return 0x13;
    case 2:
        return 0x14;
    case 16:
        return 0x15;
    case 11:
        return 0x16;
    case 9:
        return 0x17;
    case 10:
        return 0x18;
    case 15:
        return 0x19;
    case 12:
    case 17:
        return 0x1A;
    case 13:
        return 0x1B;
    case 3:
        return 0x1C;
    case 5:
        return 0x1D;
    default:
        return 0x1C;
    }
}

s32 func_00f2b1e8(s32 arg0) {
    s32 var_a0;
    s32 var_v0;

    var_a0 = -1;
    switch (arg0) {
    case 3:
        var_a0 = 0xF;
        break;
    case 4:
        var_a0 = 0x10;
        break;
    case 5:
        var_a0 = 0x12;
        break;
    case 8:
        var_a0 = 0x13;
        break;
    case 9:
        var_a0 = 0x15;
        break;
    case 10:
        var_a0 = 0x14;
        break;
    case 11:
        var_a0 = 0x11;
        break;
    case 13:
        var_a0 = 0x16;
        break;
    case 15:
        var_a0 = 0x17;
        break;
    case 16:
        var_a0 = 0x18;
        break;
    }
    var_v0 = 0;
    if (var_a0 >= 0) {
        var_v0 = func_00f2ab98(var_a0);
    }
    return var_v0;
}

s32 func_00f2b2f8(s32 arg0) {
    switch (arg0) {
    case 17:
    case 18:
        return 0x11;
    case 13:
    case 27:
        return 0xD;
    case 19:
    case 20:
        return 0x12;
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
        return -1;
    default:
        return arg0;
    }
}

void func_00f2b870(s32 arg0) {
    func_00f64b88(arg0);
    D_00FBB570 = func_00f64c38(0, arg0);
    D_00FBB578 = func_00f64c38(1, arg0);
    D_00FBB574 = func_00f64c38(2, arg0);
}

s32 func_00f2b9a0(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_v0;

    temp_v0 = func_00f2b808(arg0, arg1);
    var_v0 = 0;
    if (temp_v0 < 0) {
        return var_v0;
    }
    var_v0 = D_00FBB570 + (temp_v0 * 0x48) + 8;
    return var_v0;
}

void func_00f2c108(u32 arg0, s32 arg1) {
    s32 *temp_a1;
    s32 *temp_a2;

    if (arg0 < 0x100U) {
        if (arg1 == 0) {
            temp_a2 = &D_00FBDFB8 + (arg0 * 4);
            *temp_a2 = (*temp_a2 + 1) | 0x80000000;
            D_00F8508C += 1;
            D_00F87310[0] = (s32) (D_00F87310[0] + 1);
            return;
        }
        temp_a1 = &D_00FBDFB8 + (arg0 * 4);
        *temp_a1 += 1;
        D_00F85090 += 1;
        D_00F87310[1] = (s32) (D_00F87310[1] + 1);
    }
}

void func_00f2dfc0(s32 arg0) {
    s32 sp[20];    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = func_00f2cae8(arg0);
    temp_v0_2 = M2C_FIELD(temp_v0, s32 *, 0x80);
    if (temp_v0_2 >= 0) {
        temp_v0_3 = *(M2C_UNK *)((s8 *)(s8 *)&D_00FBB5D4 + (temp_v0_2 << 5));
        if (temp_v0_3 >= 0) {
            temp_v0_4 = func_00f3b4e0(temp_v0_3);
            if (temp_v0_4 != 0) {
                temp_s0 = temp_v0 + 0x20;
                sceVu0CopyVector(&M2C_FIELD(sp, f32 *, 0x40), temp_v0_4 + 0x50);
                M2C_FIELD(sp, f32 *, 0x40) -= M2C_FIELD(temp_v0, f32 *, 0x50);
                M2C_FIELD(sp, f32 *, 0x44) -= M2C_FIELD(temp_v0, f32 *, 0x54);
                M2C_FIELD(sp, f32 *, 0x48) -= M2C_FIELD(temp_v0, f32 *, 0x58);
                M2C_FIELD(sp, f32 *, 0x4C) = 1.0f;
                sceVu0Normalize(&M2C_FIELD(sp, f32 *, 0x40), &M2C_FIELD(sp, f32 *, 0x40));
                func_001becb8(sp, &M2C_FIELD(sp, f32 *, 0x40), 1);
                func_001bf098(temp_s0, sp);
                func_00f68770(0x45, 0x7D0, temp_s0, 0, D_00F87048);
            }
        }
    }
}
