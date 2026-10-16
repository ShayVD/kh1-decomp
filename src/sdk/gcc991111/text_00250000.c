/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK Deci2Call(M2C_UNK, void *);
M2C_UNK GetOsdConfigParam(u32 *);
M2C_UNK SetOsdConfigParam(u32 *);
M2C_UNK func_00260ac0();
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_0066DA68;
extern M2C_UNK D_0066DD28;
extern s32 D_0046AE54;
extern s32 D_0046AED8;
extern s32 D_0046AEDC;
extern s32 D_0046AEE0;
extern s32 D_0046AEE4;
extern s32 D_0046AEEC;
s32 *func_00265180();
s32 CreateSema(void *);
s32 func_0025c628(s32, s32);
void func_00259380(s32);
void func_00260398();

s32 func_00258820(void) {
    *func_00265180() = 5;
    return -1;
}

s32 func_00258960(void) {
    *func_00265180() = 5;
    return -1;
}

s32 func_00258988(void) {
    *func_00265180() = 5;
    return -1;
}

void func_00258e88(void *arg0) {
    void *temp_a0;

    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 1);
    temp_a0 = M2C_FIELD(arg0, void **, 0xC) + 1;
    M2C_FIELD(arg0, void **, 0xC) = temp_a0;
    if (temp_a0 == (arg0 + (M2C_FIELD(arg0, s32 *, 0) + 0x10))) {
        M2C_FIELD(arg0, void **, 0xC) = (void *) (arg0 + 0x10);
    }
}

void func_00258ec8(void *arg0) {
    void *temp_a0;

    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) - 1);
    temp_a0 = M2C_FIELD(arg0, void **, 8) + 1;
    M2C_FIELD(arg0, void **, 8) = temp_a0;
    if (temp_a0 == (arg0 + (M2C_FIELD(arg0, s32 *, 0) + 0x10))) {
        M2C_FIELD(arg0, void **, 8) = (void *) (arg0 + 0x10);
    }
}

void func_00259468(s32 arg0) {
    if (arg0 == 0xA) {
        func_00259380(0xD);
        func_00259380(0xA);
        return;
    }
    func_00259380(arg0);
}

void func_00259ec0(void) {
    func_00260398();
    D_0046AE54 = 0;
}

void func_00259f90(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) (M2C_FIELD(arg0, s32 *, 0x10) & 0xFFFFFFFE);
}

s32 func_0025a750(void *arg0) {
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0);
    if ((temp_a1 == NULL) || (M2C_FIELD(arg0, s32 *, 4) != M2C_FIELD(temp_a1, s32 *, 0x18)) || !(M2C_FIELD(temp_a1, s32 *, 0x10) & 1)) {
        return 0;
    }
    return 1;
}

void func_0025ac80(void) {
    s32 sp[8];
    if (D_0046AEE0 == -1) {
        M2C_FIELD(sp, s32 *, 0x8) = 1;
        M2C_FIELD(sp, s32 *, 0x14) = 0;
        M2C_FIELD(sp, s32 *, 0x4) = 1;
        D_0046AEE0 = CreateSema(sp);
        D_0046AEE4 = CreateSema(sp);
    }
}

void func_0025b198(void) {
    s32 sp[8];
    if (D_0046AEDC == -1) {
        M2C_FIELD(sp, s32 *, 0x8) = 1;
        M2C_FIELD(sp, s32 *, 0x14) = 0;
        M2C_FIELD(sp, s32 *, 0x4) = 1;
        D_0046AEDC = CreateSema(sp);
    }
}

s32 func_0025b550(void) {
    D_0046AED8 = 0;
    memset(&D_0066DA68, 0, 4);
    return 0;
}

s32 func_0025daf0(s32 arg0) {
    return func_0025c628(arg0, 0x15);
}

s32 func_0025e4b8(void) {
    D_0046AEEC = -1;
    memset(&D_0066DD28, 0, 4);
    return 0;
}

s32 func_0025f3f0(s32 *arg0, s32 *arg1, u32 arg2) {
    s32 *var_a0;
    s32 *var_a1;
    s32 temp_v1;
    u32 temp_a2;
    u32 var_a3;

    var_a0 = arg0;
    var_a1 = arg1;
    temp_a2 = arg2 >> 2;
    var_a3 = 0;
    if (temp_a2 != 0) {
        do {
            temp_v1 = *var_a1;
            var_a3 += 1;
            var_a1 += 1;
            *var_a0 = temp_v1;
            var_a0 += 1;
        } while (var_a3 < temp_a2);
    }
    return 0;
}

s32 func_0025f620(s32 *arg0, s32 *arg1, u32 arg2) {
    s32 *var_a0;
    s32 *var_a1;
    s32 temp_v1;
    u32 temp_a2;
    u32 var_a3;

    var_a0 = arg0;
    var_a1 = arg1;
    temp_a2 = arg2 >> 2;
    var_a3 = 0;
    if (temp_a2 != 0) {
        do {
            temp_v1 = *var_a1;
            var_a3 += 1;
            var_a1 += 1;
            *var_a0 = temp_v1;
            var_a0 += 1;
        } while (var_a3 < temp_a2);
    }
    return 0;
}

s32 func_0025f668(void) {
    s32 sp[4];
    GetOsdConfigParam(sp);
    M2C_FIELD(sp, u32 *, 0x4) = (M2C_FIELD(sp, M2C_UNK *, 0x0) & 0xFFFF1FFF) | 0x2000;
    SetOsdConfigParam(&M2C_FIELD(sp, u32 *, 0x4));
    GetOsdConfigParam(&M2C_FIELD(sp, u32 *, 0x4));
    SetOsdConfigParam(sp);
    return ((M2C_FIELD(sp, u32 *, 0x4) >> 0xD) & 7) == 0;
}

s32 func_0025f790(u8 *arg0, u8 *arg1, u32 arg2) {
    u32 var_a3;
    u8 *var_a0;
    u8 *var_a1;
    u8 temp_v1;

    var_a0 = arg0;
    var_a1 = arg1;
    var_a3 = 0;
    if (arg2 != 0) {
        do {
            temp_v1 = *var_a1;
            var_a3 += 1;
            var_a1 += 1;
            *var_a0 = temp_v1;
            var_a0 += 1;
        } while (var_a3 < arg2);
    }
    return 0;
}

void func_0025f8e8(void) {
    func_00260ac0();
}

s32 func_0025fa40(s32 *arg0, s32 *arg1, u32 arg2) {
    s32 *var_a0;
    s32 *var_a1;
    s32 temp_v1;
    u32 temp_a2;
    u32 var_a3;

    var_a0 = arg0;
    var_a1 = arg1;
    temp_a2 = arg2 >> 2;
    var_a3 = 0;
    if (temp_a2 != 0) {
        do {
            temp_v1 = *var_a1;
            var_a3 += 1;
            var_a1 += 1;
            *var_a0 = temp_v1;
            var_a0 += 1;
        } while (var_a3 < temp_a2);
    }
    return 0;
}

void func_0025ff08(s32 arg0) {
    s32 sp[4];
    M2C_FIELD(sp, s32 *, 0x0) = arg0;
    Deci2Call(2, sp);
}

void func_0025ff60(s32 arg0) {
    s32 sp[4];
    M2C_FIELD(sp, s32 *, 0x0) = arg0;
    Deci2Call(4, sp);
}
