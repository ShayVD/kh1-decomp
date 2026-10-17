/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001ee698();
M2C_UNK func_001efc10(M2C_UNK);
M2C_UNK func_002583e0(M2C_UNK);
M2C_UNK func_00265bc0(M2C_UNK, M2C_UNK);
M2C_UNK func_00266f38(s32, M2C_UNK *);
extern M2C_UNK D_00631620;
s32 func_001efd98();
s32 func_001efdb8();
s32 func_00266c08(M2C_UNK);
u8 *func_001478a0(s32);
void *func_00147840();
void *func_00232cc0(M2C_UNK);

s32 func_001e93c8(void) {
    s32 temp_s0;

    temp_s0 = func_00266c08(2);
    func_002583e0(0);
    func_00265bc0(0, 0);
    func_00266f38(temp_s0, &D_00631620);
    return 4;
}

s32 func_001ebe80(void) {
    return M2C_FIELD(func_00232cc0(1), s32 *, 0xDC4) & 1;
}

s32 func_001ebea8(void) {
    return ((u32) M2C_FIELD(func_00232cc0(1), u32 *, 0xDC4) >> 2) & 1;
}

void func_001ebed0(s32 arg0) {
    void *temp_v0;

    temp_v0 = func_00232cc0(1);
    M2C_FIELD(temp_v0, s32 *, 0xDC4) = (s32) ((M2C_FIELD(temp_v0, s32 *, 0xDC4) & ~4) | ((arg0 & 1) * 4));
}

s32 func_001ebf18(void) {
    void *temp_v0;

    temp_v0 = func_00232cc0(1);
    M2C_FIELD(temp_v0, s32 *, 0xDC4) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xDC4) | 4);
    return 2;
}

s32 func_001ebf48(void *arg0) {
    s32 temp_v1;
    void *temp_v0;

    temp_v0 = func_00232cc0(1);
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xDC4) & 1);
    return 2;
}

s32 func_001ebf98(void) {
    void *temp_v0;

    temp_v0 = func_00232cc0(1);
    M2C_FIELD(temp_v0, s32 *, 0xDC4) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xDC4) | 1);
    return 2;
}

s32 func_001ebfc8(void) {
    return ((u32) M2C_FIELD(func_00232cc0(1), u32 *, 0xDC4) >> 1) & 1;
}

s32 func_001ebff0(void *arg0) {
    s32 temp_v1;
    void *temp_v0;

    temp_v0 = func_00232cc0(1);
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) (((u32) M2C_FIELD(temp_v0, u32 *, 0xDC4) >> 1) & 1);
    return 2;
}

void func_001ec0b0(void) {
    void *temp_v0;

    temp_v0 = func_00232cc0(1);
    M2C_FIELD(temp_v0, s32 *, 0xDC4) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xDC4) | 2);
}

u8 func_001ec360(void) {
    return M2C_FIELD(func_00232cc0(1), u8 *, 0xDD0);
}

s32 func_001ec3b0(void *arg0) {
    s32 temp_v1;
    void *temp_v0;

    temp_v0 = func_00232cc0(1);
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) M2C_FIELD(temp_v0, u8 *, 0xDD0);
    return 2;
}

s32 func_001ec468(void *arg0) {
    s32 temp_v1;
    void *temp_v0;

    temp_v0 = func_00232cc0(1);
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) (((u32) M2C_FIELD(temp_v0, u32 *, 0xDC4) >> 3) & 1);
    return 2;
}

void func_001ec4b8(void) {
    void *temp_v0;

    temp_v0 = func_00232cc0(1);
    M2C_FIELD(temp_v0, s32 *, 0xDC4) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xDC4) | 8);
}

void func_001ec4e0(void) {
    void *temp_v0;

    temp_v0 = func_00232cc0(1);
    M2C_FIELD(temp_v0, s32 *, 0xDC4) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xDC4) & ~8);
}

s32 func_001ec510(void) {
    return ((u32) M2C_FIELD(func_00232cc0(1), u32 *, 0xDC4) >> 3) & 1;
}

s32 func_001ec538(s32 arg0) {
    return ((u32) M2C_FIELD(func_00232cc0(1), u32 *, 0xDD4) >> ~arg0) & 1;
}

s32 func_001ec5d8(s32 arg0) {
    return ((s8) M2C_FIELD(func_00232cc0(2), s8 *, 0x1B) >> arg0) & 1;
}

u16 func_001ee708(void) {
    return M2C_FIELD(func_00147840(), u16 *, 8);
}

u16 func_001ee728(void) {
    return M2C_FIELD(func_00147840(), u16 *, 0xA);
}

s16 func_001ee748(void) {
    return M2C_FIELD(func_00147840(), s16 *, 6);
}

u8 func_001ee768(void) {
    return M2C_FIELD(func_00147840(), u8 *, 2);
}

u8 func_001ee788(void) {
    return M2C_FIELD(func_00147840(), u8 *, 3);
}

u16 func_001ee7a8(void) {
    return M2C_FIELD(func_00147840(), u16 *, 0x10);
}

s32 func_001ee7c8(void) {
    return M2C_FIELD(func_00147840(), u16 *, 4) & 1;
}

void func_001eeb88(s32 arg0) {
    if (arg0 != 0) {
        func_001ee698();
        return;
    }
    func_001efc10(0xA7);
}

void func_001eebb0(s32 arg0) {
    if (arg0 != 0) {
        func_001ee698();
        return;
    }
    func_001efc10(0xA7);
}

s32 func_001efe68(void) {
    return func_001efd98() + 1;
}

s32 func_001efe88(void) {
    return func_001efdb8() + 1;
}
