/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_0046AEDC;
extern s32 D_0046AF10;
extern s32 D_0046AF14;
extern s32 D_0046C208;
s32 CreateSema(M2C_UNK *);
s32 func_0025f7d0();
void Deci2Call(s32, s32);
void LoadExecPS2(s32, s32, s32);
void WaitSema(s32);
void func_0025b198();
void func_0025f8e8();

s32 func_0025b1e8(void) {
    func_0025b198();
    WaitSema(D_0046AEDC);
    return 0;
}

void func_0025f398(void) {
    s32 sp[16];
    M2C_FIELD(sp, s32 *, 0x4) = 1;
    M2C_FIELD(sp, s32 *, 0x8) = 1;
    M2C_FIELD(sp, s32 *, 0x24) = 1;
    M2C_FIELD(sp, s32 *, 0x28) = 1;
    D_0046AF10 = CreateSema(sp);
    D_0046AF14 = CreateSema(&M2C_FIELD(sp, M2C_UNK *, 0x20));
}

void func_0025f960(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = func_0025f7d0();
    func_0025f8e8();
    LoadExecPS2(temp_s0, arg1, D_0046C208 + 4);
}

void func_0025ff88(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    M2C_FIELD(sp, s32 *, 0x4) = arg1;
    M2C_FIELD(sp, s32 *, 0x8) = arg2 & 0xFFFF;
    M2C_FIELD(sp, s32 *, 0x0) = arg0;
    Deci2Call(-5, (s32) sp);
}

void func_0025ffc0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    M2C_FIELD(sp, s32 *, 0x4) = arg1;
    M2C_FIELD(sp, s32 *, 0x8) = arg2 & 0xFFFF;
    M2C_FIELD(sp, s32 *, 0x0) = arg0;
    Deci2Call(-6, (s32) sp);
}
