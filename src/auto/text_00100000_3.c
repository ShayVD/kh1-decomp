/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0049.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK SignalSema(s32);
M2C_UNK WaitSema(s32);
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_001f1ed8(M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK);
M2C_UNK sceGsExecLoadImage(M2C_UNK *, s32);
M2C_UNK sceGsSetDefLoadImage(M2C_UNK *, s16, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);
extern M2C_UNK D_002B75A0;
extern M2C_UNK D_002BC1B0;
extern M2C_UNK func_00103058;
extern M2C_UNK func_001032b0;
extern M2C_UNK func_00109e20;
extern M2C_UNK func_0010a378;
extern f32 D_00495184;
extern s32 D_002A3F48;
extern s32 D_002A6254;
extern s32 D_002A6258;
extern s32 D_002BC138;
extern s32 D_002BC13C;
extern s32 D_002BCDBC;
extern s32 D_002C5BB8;
extern s32 D_00494A90;
extern s32 D_00494A94;
extern s32 D_00495188;
extern s32 D_00495260;
extern s32 D_004D5B00;
extern s32 D_004D5B08;
extern void *D_002A6238;
extern volatile s32 D_002C5968;
extern volatile s32 D_00495258;
s32 func_00104ae0(s32, s32);
s32 func_0011aa18(s32, s32, s32);
s32 func_001efc10(M2C_UNK);
s32 func_002675a8(s32, s32);
void func_00104f10(s32, s32);
void func_0011a978(s32, s32, s32);
void func_00121ee0(s32);

void func_00100d18(s32 arg0, s16 arg1) {
    sceGsSetDefLoadImage(&D_002BC1B0, arg1, 1, 0, 0, 0, 8, 2);
    FlushCache(0);
    sceGsExecLoadImage(&D_002BC1B0, arg0);
    sceGsSyncPath(0, 0);
}

void func_00100d90(s32 arg0, s16 arg1) {
    sceGsSetDefLoadImage(&D_002BC1B0, arg1, 1, 0, 0, 0, 0x10, 0x10);
    FlushCache(0);
    sceGsExecLoadImage(&D_002BC1B0, arg0);
    sceGsSyncPath(0, 0);
}

void func_00100e08(s32 arg0, s16 arg1) {
    sceGsSetDefLoadImage(&D_002BC1B0, arg1, 8, 0x14, 0, 0, 0x200, 0x100);
    FlushCache(0);
    sceGsExecLoadImage(&D_002BC1B0, arg0);
    sceGsSyncPath(0, 0);
}

void func_00100e80(s32 arg0, s16 arg1) {
    sceGsSetDefLoadImage(&D_002BC1B0, arg1, 4, 0x13, 0, 0, 0x100, 0x100);
    FlushCache(0);
    sceGsExecLoadImage(&D_002BC1B0, arg0);
    sceGsSyncPath(0, 0);
}

void func_00100ef8(s32 arg0, s16 arg1) {
    sceGsSetDefLoadImage(&D_002BC1B0, arg1, 4, 0x1B, 0, 0, 0x100, 0x400);
    FlushCache(0);
    sceGsExecLoadImage(&D_002BC1B0, arg0);
    sceGsSyncPath(0, 0);
}

void func_00101660(void) {
    D_002BC138 = -1;
    D_002BC13C = -1;
    D_002BCDBC = 0;
}

void func_00103258(void) {
    func_0011ef10(0x280A2, &func_00103058);
}

void func_001037e8(void) {
    func_0011ef10(0x280A4, &func_001032b0);
}

void func_00104fd0(s32 arg0, void *arg1) {
    s32 temp_a0;

    temp_a0 = arg0 * 0x10;
    M2C_FIELD(arg1, f32 *, 0) = (f32) M2C_FIELD((temp_a0 + D_002A6254), f32 *, 4);
    M2C_FIELD(arg1, f32 *, 4) = (f32) M2C_FIELD((temp_a0 + D_002A6254), f32 *, 8);
    M2C_FIELD(arg1, f32 *, 8) = (f32) M2C_FIELD((temp_a0 + D_002A6254), f32 *, 0xC);
    M2C_FIELD(arg1, f32 *, 0xC) = 1.0f;
}

void func_00105760(s32 arg0, s32 arg1) {
    s32 var_a3;
    void *var_a2;

    var_a3 = D_002A6258;
    if (var_a3 > 0) {
        var_a2 = D_002A6238;
        do {
            var_a3 -= 1;
            if (M2C_FIELD(var_a2, u8 *, 0xB) == arg0) {
                M2C_FIELD(var_a2, s32 *, 0x10) = (s32) ((M2C_FIELD(var_a2, s32 *, 0x10) & 0xFFC3FFFF) | ((arg1 & 0xF) << 0x12));
            }
            var_a2 += 0x14;
        } while (var_a3 != 0);
    }
}

void func_00105a30(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == -1) {
        func_00104f10(arg1, arg2);
        return;
    }
    func_0011a978(arg0, arg1, arg2);
}

s32 func_00105ad0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == -1) {
        return func_00104ae0(arg1, arg2);
    }
    return func_0011aa18(arg0, arg1, arg2);
}

void func_00105c70(s32 arg0, s32 arg1) {
    func_002675a8(arg1, D_002A3F48 + (arg0 * 0x10));
}

void func_00105fc8(void) {
    func_001f1ed8(0x80C0612C, 0x140, 0x194, func_001efc10(0xF), 0xF);
}

void func_00106c78(void) {
    func_00121ee0(D_00494A94);
    func_00121ee0(D_00494A90);
}

void func_001089f8(s32 arg0, s32 arg1) {
    s32 var_a2;
    void *var_a0;

    var_a0 = arg0 + 0x4C;
    var_a2 = 1;
    do {
        var_a2 -= 1;
        M2C_FIELD(var_a0, s32 *, -0x1C) = (s32) M2C_FIELD(arg1, s32 *, 0x80);
        M2C_FIELD(var_a0, s32 *, -0x18) = (s32) (M2C_FIELD(arg1, s32 *, 0x84) + arg1);
        M2C_FIELD(var_a0, s32 *, -0x14) = (s32) M2C_FIELD(arg1, s32 *, 0x88);
        M2C_FIELD(var_a0, s32 *, -0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x8C);
        M2C_FIELD(var_a0, s32 *, -0xC) = (s32) M2C_FIELD(arg1, s32 *, 0x90);
        M2C_FIELD(var_a0, s32 *, -8) = (s32) (M2C_FIELD(arg1, s32 *, 0x94) + arg1);
        M2C_FIELD(var_a0, s32 *, -4) = (s32) M2C_FIELD(arg1, s32 *, 0x98);
        M2C_FIELD(var_a0, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0x9C);
        var_a0 += 0x60;
    } while (var_a2 >= 0);
}

void func_00109f48(s32 arg0) {
    D_00495188 = 0;
    D_00495184 = (f32) (arg0 * 2);
    func_0011ef10(0x2E630, &func_00109e20);
}

void func_0010a3c0(void) {
    func_0011ef10(0x2E630, &func_0010a378);
}

void func_0010b170(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    M2C_FIELD(arg0, f32 *, 0x3C) = 1.0f;
    M2C_FIELD(arg0, f32 *, 0x5C) = 1.0f;
    M2C_FIELD(arg0, f32 *, 0x58) = 1.0f;
}

void func_0010c240(void) {
    s8 *var_v0;
    s32 var_v1;

    var_v1 = 1;
    var_v0 = &D_002B75A0;
    do {
        var_v1 -= 1;
        M2C_FIELD(var_v0, s32 *, 0) = 0;
        M2C_FIELD(var_v0, s32 *, 4) = 0;
        M2C_FIELD(var_v0, s32 *, 8) = 0;
        var_v0 += 0xC;
    } while (var_v1 >= 0);
}

void func_0010c348(void) {
    SignalSema(D_00495260);
    WaitSema(D_00495258);
}

void func_0010c438(s16 arg0, s32 arg1) {
    sceGsSetDefLoadImage(&D_002BC1B0, arg0, 1, 0, 0, 0, 8, 2);
    sceGsSyncPath(0, 0);
    FlushCache(0);
    sceGsExecLoadImage(&D_002BC1B0, arg1);
}

s32 func_0010cf20(void) {
    if ((D_002C5BB8 & 1) != 0) {
        return 1;
    }
    return 0;
}

void func_0010f8a0(void) {
    D_004D5B00 = D_002C5968;
}

void func_0010f8b8(void) {
    D_004D5B08 = D_002C5968;
}
