/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001bb7c8(M2C_UNK *, M2C_UNK *);
M2C_UNK func_001efaf0();
M2C_UNK func_001efb18(s32, s32);
M2C_UNK sceVu0CopyMatrix(M2C_UNK *, s32);
extern M2C_UNK D_00F8AA88;
extern M2C_UNK D_00F8C290;
extern M2C_UNK D_00FB6D88;
extern f32 D_00F8511C;
extern s32 *D_00F85160;
extern s32 D_00F850D8;
extern s32 D_00F8C23C;
extern s32 D_00FBA800;
extern s32 D_00FBAA10;
extern s32 D_00FBB574;
extern s32 D_00FBB578;
s32 func_0010a0d8(void);
s32 func_001efbb8(s32);
s32 func_00f65bb8(s32, s32, s32, s32);
s32 func_00f67420(s32, s32, s32, s32);
void func_0010a320(void);
void func_00176c60(s32);
void func_001bfac8(void);
void func_00242b68(s32);
void func_00248b00(void);
void func_00f21c48();
void func_00f2abe8(M2C_UNK, s8);
void func_00f680a0(void);

void func_00f201c0(void) {
    func_00248b00();
    func_00242b68(4);
    func_00f680a0();
    if (D_00F8C23C == 0) {
        func_0010a0d8();
        func_0010a320();
    }
    func_00176c60(0);
    D_00FBA800 = 1;
    for (;;) {
        func_001bfac8();
    }
}

void func_00f20328(void) {
    func_00f21c48();
    D_00F850D8 = D_00FBAA10;
    func_00f2abe8(0x19, (s8) D_00F850D8);
}

f32 func_00f20ad8(void) {
    return D_00F8511C;
}

void func_00f29500(s32 arg0, s32 arg1, s32 arg2) {
    *D_00F85160 = func_00f67420(arg0, arg1, arg2, *D_00F85160);
    func_00f65bb8(arg1, arg2, 0, 0);
}

void func_00f2b7e0(void) {
    func_001bb7c8(&D_00FB6D88, &D_00F8AA88);
}

s32 func_00f2b8f0(s32 arg0) {
    s32 temp_s0;

    func_001efb18(D_00FBB574, D_00FBB578);
    temp_s0 = func_001efbb8(arg0);
    func_001efaf0();
    return temp_s0;
}

void func_00f2c310(s32 arg0) {
    sceVu0CopyMatrix(&D_00F8C290, arg0);
}
