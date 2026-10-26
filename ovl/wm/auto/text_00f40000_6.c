/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00FB7370;
extern M2C_UNK D_00FB7378;
extern M2C_UNK D_01080908;
extern M2C_UNK func_00f49c40;
extern M2C_UNK func_00f4cda8;
extern s32 D_00F9B510;
extern s32 D_00F9B640;
extern s32 D_01080988;
extern s32 D_0108098C;
extern s32 D_01080994;
extern s32 D_01080998;
extern s32 D_01080C50;
extern s32 D_0108BCA0;
s32 func_001bb7c8(s32, s32);
s32 func_001c01b0(s32, s32, ...);
void *func_00f2c848();
void *func_00f2c878();
void func_001b9bb0(s32, s32);
void func_001b9ec0(void);
void func_001ba708(s32);
void func_001be9f0(f32 *);
void func_001bef40(s32, s32, s32);
void func_001bf098(M2C_UNK *, M2C_UNK *);
void func_001bfac8();
void func_00f2c858(f32 *);
void func_00f2c888(f32 *);
void func_00f4ccc0(void);
void func_00f4cf40(void);
void sceVu0RotMatrix(M2C_UNK *, M2C_UNK *, f32 *);
void sceVu0UnitMatrix(M2C_UNK *);

void func_00f43dd0(s32 arg0, s32 arg1) {
    s32 sp[24];
    func_001bef40((s32) sp, arg1, (s32) &D_00FB7370);
    func_001bef40((s32) &M2C_FIELD(sp, M2C_UNK *, 0x20), (s32) &D_00FB7378, (s32) sp);
    func_001bb7c8((s32) &M2C_FIELD(sp, M2C_UNK *, 0x20), arg0);
}

s32 func_00f43e30(s32 arg0) {
    switch (arg0) {
    case 0x40:
        return D_01080988;
    case 0x41:
        return D_0108098C;
    case 0x42:
        return 0;
    case 0x43:
        return D_01080994;
    case 0x44:
        return D_01080998;
    default:
        return *(M2C_UNK *)((s8 *)(s8 *)&D_01080908 + (arg0 * 4));
    }
}

void func_00f456b0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, M2C_UNK *arg4) {
    s32 sp[40];    f32 temp_f21;
    f32 temp_f3;
    s32 var_s0;

    sceVu0UnitMatrix(&M2C_FIELD(sp, M2C_UNK *, 0x20));
    func_001bf098(&M2C_FIELD(sp, M2C_UNK *, 0x20), arg4);
    var_s0 = 0;
    M2C_FIELD(sp, f32 *, 0x10) = (f32) arg1 * 0.017453291f;
    M2C_FIELD(sp, f32 *, 0x1C) = 1.0f;
    M2C_FIELD(sp, f32 *, 0xC) = 1.0f;
    M2C_FIELD(sp, f32 *, 0x14) = (f32) arg2 * 0.017453291f;
    M2C_FIELD(sp, f32 *, 0x18) = (f32) arg3 * 0.017453291f;
    if (arg0 > 0) {
        temp_f21 = (f32) arg0;
        do {
            temp_f3 = (f32) var_s0;
            M2C_FIELD(sp, f32 *, 0xC) = 1.0f;
            var_s0 += 1;
            M2C_FIELD(sp, f32 *, 0x0) = (((M2C_FIELD(sp, f32 *, 0x10) - 0.0f) * temp_f3) / temp_f21) + 0.0f;
            M2C_FIELD(sp, f32 *, 0x4) = (((M2C_FIELD(sp, f32 *, 0x14) - 0.0f) * temp_f3) / temp_f21) + 0.0f;
            M2C_FIELD(sp, f32 *, 0x8) = (((M2C_FIELD(sp, f32 *, 0x18) - 0.0f) * temp_f3) / temp_f21) + 0.0f;
            func_001be9f0(sp);
            sceVu0RotMatrix(&M2C_FIELD(sp, M2C_UNK *, 0x60), &M2C_FIELD(sp, M2C_UNK *, 0x20), sp);
            func_001bf098(arg4, &M2C_FIELD(sp, M2C_UNK *, 0x60));
            func_001bfac8();
        } while (var_s0 < arg0);
    }
    sceVu0RotMatrix(&M2C_FIELD(sp, M2C_UNK *, 0x60), &M2C_FIELD(sp, M2C_UNK *, 0x20), &M2C_FIELD(sp, f32 *, 0x10));
    func_001bf098(arg4, &M2C_FIELD(sp, M2C_UNK *, 0x60));
}

void func_00f459b0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[12];    f32 temp_f20;
    f32 temp_f3;
    s32 var_s0;
    void *temp_v0;

    temp_v0 = func_00f2c848();
    var_s0 = 0;
    M2C_FIELD(sp, f32 *, 0x10) = M2C_FIELD(temp_v0, f32 *, 0);
    M2C_FIELD(sp, f32 *, 0x14) = M2C_FIELD(temp_v0, f32 *, 4);
    M2C_FIELD(sp, f32 *, 0x18) = M2C_FIELD(temp_v0, f32 *, 8);
    M2C_FIELD(sp, f32 *, 0x0) = (f32) arg1 * 1e+02f;
    M2C_FIELD(sp, f32 *, 0x4) = (f32) arg2 * 1e+02f;
    M2C_FIELD(sp, f32 *, 0x8) = (f32) arg3 * 1e+02f;
    if (arg0 > 0) {
        temp_f20 = (f32) arg0;
        do {
            temp_f3 = (f32) var_s0;
            var_s0 += 1;
            M2C_FIELD(sp, f32 *, 0x2C) = 1.0f;
            M2C_FIELD(sp, f32 *, 0x20) = (((M2C_FIELD(sp, f32 *, 0x0) - M2C_FIELD(sp, f32 *, 0x10)) * temp_f3) / temp_f20) + M2C_FIELD(sp, f32 *, 0x10);
            M2C_FIELD(sp, f32 *, 0x24) = (((M2C_FIELD(sp, f32 *, 0x4) - M2C_FIELD(sp, f32 *, 0x14)) * temp_f3) / temp_f20) + M2C_FIELD(sp, f32 *, 0x14);
            M2C_FIELD(sp, f32 *, 0x28) = (((M2C_FIELD(sp, f32 *, 0x8) - M2C_FIELD(sp, f32 *, 0x18)) * temp_f3) / temp_f20) + M2C_FIELD(sp, f32 *, 0x18);
            func_00f2c858(&M2C_FIELD(sp, f32 *, 0x20));
            func_001bfac8();
        } while (var_s0 < arg0);
    }
    func_00f2c858(sp);
}

void func_00f45b18(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[12];    f32 temp_f20;
    f32 temp_f3;
    s32 var_s0;
    void *temp_v0;

    temp_v0 = func_00f2c878();
    var_s0 = 0;
    M2C_FIELD(sp, f32 *, 0x10) = M2C_FIELD(temp_v0, f32 *, 0);
    M2C_FIELD(sp, f32 *, 0x14) = M2C_FIELD(temp_v0, f32 *, 4);
    M2C_FIELD(sp, f32 *, 0x18) = M2C_FIELD(temp_v0, f32 *, 8);
    M2C_FIELD(sp, f32 *, 0x0) = (f32) arg1 * 0.017453291f;
    M2C_FIELD(sp, f32 *, 0x4) = (f32) arg2 * 0.017453291f;
    M2C_FIELD(sp, f32 *, 0x8) = (f32) arg3 * 0.017453291f;
    if (arg0 > 0) {
        temp_f20 = (f32) arg0;
        do {
            temp_f3 = (f32) var_s0;
            var_s0 += 1;
            M2C_FIELD(sp, f32 *, 0x2C) = 1.0f;
            M2C_FIELD(sp, f32 *, 0x20) = (((M2C_FIELD(sp, f32 *, 0x0) - M2C_FIELD(sp, f32 *, 0x10)) * temp_f3) / temp_f20) + M2C_FIELD(sp, f32 *, 0x10);
            M2C_FIELD(sp, f32 *, 0x24) = (((M2C_FIELD(sp, f32 *, 0x4) - M2C_FIELD(sp, f32 *, 0x14)) * temp_f3) / temp_f20) + M2C_FIELD(sp, f32 *, 0x14);
            M2C_FIELD(sp, f32 *, 0x28) = (((M2C_FIELD(sp, f32 *, 0x8) - M2C_FIELD(sp, f32 *, 0x18)) * temp_f3) / temp_f20) + M2C_FIELD(sp, f32 *, 0x18);
            func_001be9f0(&M2C_FIELD(sp, f32 *, 0x20));
            func_00f2c888(&M2C_FIELD(sp, f32 *, 0x20));
            func_001bfac8();
        } while (var_s0 < arg0);
    }
    func_001be9f0(sp);
    func_00f2c888(sp);
}

void func_00f4d138(s32 arg0, s32 arg1) {
    switch (arg0) {                                 /* irregular */
    case 0:
        func_00f4ccc0();
        func_001b9ec0();
        D_00F9B640 = 1;
        if (arg1 == 2) {
            func_00f4cf40();
            return;
        }
        return;
    case 1:
        D_00F9B640 = 0;
        func_001b9bb0(0, 1);
        func_001ba708(0);
        func_001c01b0(-1, &func_00f49c40, 0, &func_00f4cda8);
        return;
    case 2:
        D_00F9B510 = arg1;
        break;
    }
}

s32 func_00f4d218(s32 arg0) {
    s32 var_v0;

    var_v0 = 1;
    if (arg0 == 0) {
        return var_v0;
    }
    if (D_0108BCA0 != 0) {
        if (D_0108BCA0 == D_01080C50) {
            D_0108BCA0 = 0;
            return 1;
        }
        return 0;
    }
    var_v0 = 0;
    D_0108BCA0 = D_01080C50 + (arg0 * 2);
    /* Duplicate return node #6. Try simplifying control flow for better match */
    return var_v0;
    return var_v0;
}
