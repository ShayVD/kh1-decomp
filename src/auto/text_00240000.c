/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0066.h"

M2C_UNK func_00149c80(u16, M2C_UNK *);
M2C_UNK func_002401f0(s32, s32);
M2C_UNK func_0024a588(void *, void *);
M2C_UNK func_0024b7a0(s32, s32, M2C_UNK);
M2C_UNK func_0024e0f0();
extern M2C_UNK D_0046A620;
#include "data/pieces/D_0046A628.h"
extern M2C_UNK D_0046A640;
#include "data/pieces/D_0046A650.h"
extern M2C_UNK D_0046A660;
extern M2C_UNK func_0024f008;
extern s32 D_0046A53C;
extern s32 D_0046A60C;
extern s32 D_0046A67C;
extern s32 D_00669A38;
extern s32 D_00669A3C;
extern u32 D_002C5AD8;
extern u32 D_002C5AE0;
extern void *D_0066AA84; /* src/data/bss_0066.c: s32 *D_0066AA84 */
s32 func_0023feb8();
s32 func_0023ff38(void *, s32);
s32 func_00240170();
s32 func_0024b778();
s32 func_0024f4f0(s32);
s32 func_0026aaa0();
void *func_00240910();

s32 func_00240118(void *arg0, s32 arg1) {
    if (*M2C_FIELD(arg0, f32 **, 0xA88) != 0.0f) {
        return func_0023ff38(arg0, func_0023feb8());
    }
    return arg1;
}

void func_002403d0(s32 arg0) {
    func_002401f0(arg0, func_00240170());
}

void func_00240978(void) {
    void *temp_v0;

    temp_v0 = func_00240910();
    if ((temp_v0 != NULL) && (M2C_FIELD(temp_v0, s32 *, 0x9D0) == 0)) {
        M2C_FIELD(temp_v0, s32 *, 0x9D0) = 1;
    }
}

void func_002409b0(void) {
    void *temp_v0;

    temp_v0 = func_00240910();
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x9D4) = 1;
    }
}

void func_00242b00(void) {
    void *temp_v0;

    temp_v0 = func_00240910();
    if ((temp_v0 != NULL) && (M2C_FIELD(temp_v0, s32 *, 0x770) == 0)) {
        M2C_FIELD(temp_v0, s32 *, 0x770) = 1;
    }
}

void func_00242b38(void) {
    void *temp_v0;

    temp_v0 = func_00240910();
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x774) = 1;
    }
}

s32 func_00249da0(s32 arg0) {
    return arg0 + 0x10;
}

s32 func_0024a1c0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x74);
}

void func_0024ac08(void *arg0, void *arg1) {
    if ((M2C_FIELD(arg0, s64 *, 0x60) & 0x14) == 0x14) {
        func_0024a588(arg0, arg1);
        return;
    }
    M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0);
    M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 4);
    M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 8);
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0xC);
}

void func_0024b760(void) {
    func_0024e0f0();
}

void func_0024b958(s32 arg0) {
    func_0024b7a0(arg0, func_0024f4f0(func_0024b778()), 1);
}

void func_0024ba00(s32 arg0) {
    D_00669A38 = arg0;
    D_00669A3C = func_0026aaa0();
}

s32 func_0024be58(void) {
    return D_002C5AD8 | (((u32) D_002C5AD8 >> 0x18) & 0xF0);
}

s32 func_0024be70(void) {
    return D_002C5AE0 | (((u32) D_002C5AE0 >> 0x18) & 0xF0);
}

s32 func_0024d490(void) {
    return D_0046A53C;
}

s32 func_0024d4a0(void) {
    return D_0046A60C;
}

M2C_UNK *func_0024d8a0(void) {
    return &D_0046A620;
}

M2C_UNK *func_0024d8b0(void) {
    return (M2C_UNK *)&D_0046A628;
}

M2C_UNK *func_0024d8c0(void) {
    return &D_0046A640;
}

M2C_UNK *func_0024d8d0(void) {
    return (M2C_UNK *)&D_0046A650;
}

M2C_UNK *func_0024d8e0(void) {
    return &D_0046A660;
}

s32 func_0024e078(void) {
    return D_0046A67C;
}

void func_0024f070(void) {
    func_00149c80(M2C_FIELD(D_0066AA84, u16 *, 0x4C), &func_0024f008);
}
#include "data/data_0046.h"
