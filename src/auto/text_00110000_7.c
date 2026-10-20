/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00100ae0();
M2C_UNK func_0011c7c0(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0011e8d0(M2C_UNK, s32, s32, s32, M2C_UNK, s32);
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
extern M2C_UNK func_00112ad8;
extern s32 D_002BBE1C;
extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_002BC134;
extern s32 D_002BCDA8;
extern s32 D_002C1364;
extern void *D_002BCB60;
f32 func_0011c7a8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_00111660(s32, s32);
void func_00116368(s32, s32);

void func_00111830(void) {
    s32 temp_a0;
    s32 temp_v0;

    D_002BBE1C = 1;
    temp_a0 = M2C_FIELD(D_002BCB60, s32 *, 0x40);
    D_002BC128 = temp_a0;
    temp_v0 = M2C_FIELD(D_002BCB60, s32 *, 0x44);
    D_002BC130 = temp_v0;
    D_002BC134 = func_00111660(temp_a0, temp_v0);
    D_002BCDA8 = M2C_FIELD(D_002BCB60, s32 *, 0x48);
}

void func_00112b18(void) {
    func_00100ae0();
    func_0011ef10(0x2E630, &func_00112ad8);
}

void func_001178b8(s32 arg0) {
    func_00116368(arg0, 0);
}

void func_0011e4d0(void) {
    func_0011c7c0(1, 0, 0x2D0);
    func_0011c7a8(0, 0, 0x3000, 0x1E0, 1, 0xF0);
    D_002C1364 = 0;
}

void func_0011e9d8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_0011e8d0(1, arg0, arg1, arg2, 0, arg3);
}
#include "data/data_002B.h"
#include "data/data_002C.h"
