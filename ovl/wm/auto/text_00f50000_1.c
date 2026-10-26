/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001bb658(s32);
M2C_UNK func_001bbf38(s32, s32);
M2C_UNK func_001bfac8();
M2C_UNK func_00f50548(M2C_UNK);
M2C_UNK func_00f50568(M2C_UNK);
M2C_UNK func_00f50578(M2C_UNK);
M2C_UNK func_00f50610(M2C_UNK);
M2C_UNK func_00f55298();
M2C_UNK func_00f55330(M2C_UNK);
M2C_UNK func_00f55378(M2C_UNK);
M2C_UNK func_00f66f78(M2C_UNK, s32);
M2C_UNK sceVu0MulMatrix(s32, void *, s32);
M2C_UNK sceVu0UnitMatrix(void *);
extern M2C_UNK D_0108CF10;
extern s32 D_00F9B540;
extern s32 D_00FA5B2C;
extern s32 D_0108CD40;
extern s32 D_0108D184;
extern s32 D_0108D188;
s32 func_00f4e0b0(s32, M2C_UNK, M2C_UNK);
s32 func_00f55518(M2C_UNK, M2C_UNK, u8, s32);
s32 func_00f66ac8(s32);
s32 func_00f66ae0(s32);
s32 sceVu0CopyMatrix(s32, s32);
void func_001c0078(s32);
void func_001c0688(M2C_UNK);
void func_00f4fd68();
void func_00f5ad68(M2C_UNK);
void func_00f681b0();

void func_00f505a8(s32 arg0) {
    if (arg0 != 0) {
        func_00f50610(0x80);
    } else {
        func_00f50610(0x46);
    }
    func_00f50578(0x80);
    func_00f50568(0x80);
    func_00f50548(0x80);
    D_0108CD40 = 1;
    D_00FA5B2C = -1;
}

void func_00f55310(void) {
loop_1:
    func_00f55298();
    func_001bfac8();
    goto loop_1;
}

void func_00f55398(void) {
    func_00f55330(0x80);
    func_00f55378(0x80);
}

void func_00f55880(s32 *arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    temp_v0 = func_00f66ac8(*arg0);
    *arg0 = temp_v0;
    temp_v0_2 = func_00f4e0b0(temp_v0, 0, 0);
    *arg0 = temp_v0_2;
    temp_v0_3 = func_00f55518(0x1F, 0x3C, M2C_FIELD((arg1 + D_00F9B540), u8 *, 0x10EC), temp_v0_2);
    *arg0 = temp_v0_3;
    func_00f66f78(0x2B71, func_00f66ae0(temp_v0_3));
}

u8 func_00f58128(s32 arg0) {
    return *(M2C_UNK *)((s32) D_00F9B540 + (s32) ((arg0 & 7)));
}

void func_00f59820(u32 arg0, s32 arg1) {
    if (arg0 < 0x10U) {
        *(M2C_UNK *)((s8 *)(s8 *)&D_0108CF10 + (arg0 * 4)) = arg1;
    }
}

void func_00f5ae10(s32 arg0, s32 arg1) {
    s32 sp[16];
    s32 temp_s0;

    temp_s0 = arg1 * 0xC;
    func_001bb658(M2C_FIELD((temp_s0 + D_00F9B540), u16 *, 0x114) - 1);
    sceVu0UnitMatrix(sp);
    func_001bbf38(arg0, D_00F9B540 + temp_s0 + 0x110);
    sceVu0MulMatrix(arg0, sp, arg0);
}

void func_00f5c8a8(void) {
    func_001c0688(1);
    if (D_0108D184 != 0) {
        func_001c0078(D_0108D188);
    }
    func_001c0688(2);
    D_0108D184 = 0;
    func_00f4fd68();
    func_00f681b0();
    func_00f5ad68(-1);
}

void func_00f5dcf8(s32 arg0, s32 arg1) {
    if (arg1 == 0x8C) {
        M2C_FIELD(arg0, s32 *, 0) = 0;
        M2C_FIELD(arg0, s32 *, 4) = 0;
        M2C_FIELD(arg0, s32 *, 8) = 0;
        M2C_FIELD(arg0, s32 *, 0xC) = 0;
        M2C_FIELD(arg0, s32 *, 0x10) = 0;
        M2C_FIELD(arg0, s32 *, 0x14) = 0;
        M2C_FIELD(arg0, s32 *, 0x18) = 0;
        M2C_FIELD(arg0, s32 *, 0x1C) = 0;
        M2C_FIELD(arg0, s32 *, 0x20) = 0;
        M2C_FIELD(arg0, s32 *, 0x24) = 0;
        M2C_FIELD(arg0, s32 *, 0x28) = 0;
        M2C_FIELD(arg0, s32 *, 0x2C) = 0;
        M2C_FIELD(arg0, f32 *, 0x30) = 1.0f;
        M2C_FIELD(arg0, f32 *, 0x34) = 1.0f;
        M2C_FIELD(arg0, f32 *, 0x38) = 1.0f;
        M2C_FIELD(arg0, f32 *, 0x3C) = 1.0f;
        return;
    }
    sceVu0CopyMatrix(arg0, D_00F9B540 + 0x1090);
}
