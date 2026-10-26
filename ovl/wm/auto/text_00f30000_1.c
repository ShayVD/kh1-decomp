/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001bf048(void *, void *);
M2C_UNK func_00f36330();
M2C_UNK func_00f3dd60(s32, M2C_UNK *);
M2C_UNK func_00f3f8d0(s32, M2C_UNK *);
M2C_UNK func_00f3fb28(s32, M2C_UNK *);
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK sceVu0ApplyMatrix(M2C_UNK *, void *, void *);
M2C_UNK sceVu0TransMatrix(M2C_UNK *, M2C_UNK *, void *);
M2C_UNK sceVu0TransposeMatrix(void *, void *);
M2C_UNK sceVu0UnitMatrix(M2C_UNK *);
extern M2C_UNK *D_00FDFFD8;
extern M2C_UNK D_00FCE390;
extern M2C_UNK D_00FDF390;
extern M2C_UNK D_00FDF7D8;
extern M2C_UNK D_00FDFFE0;
extern s32 D_00F8C2F0;
extern s32 D_00F9A530;
extern s32 D_00F9A534;
extern s32 D_00F9A538;
extern void *D_00F864C0;
extern volatile M2C_UNK D_00F86A58;
extern volatile M2C_UNK D_00F87E60;
extern volatile M2C_UNK D_00FB7240;
extern volatile M2C_UNK D_00FB7250;
s32 func_00f3b530(s32, s32);
s32 func_00f3b6d0(s32, s32);
s32 func_00f3b850(s32, s32);
s32 func_00f40c98();
s32 func_00f62b98(s32, s32);
void func_001be820(s32, s32);
void func_001bef40(M2C_UNK *, M2C_UNK *, s32);

void func_00f3a510(void) {
    s32 sp[4];
    D_00F8C2F0 = 0;
    memset(&D_00FCE390, 0, 0x11000);
    M2C_FIELD(sp, f32 *, 0x0) = -1.6e+03f;
    M2C_FIELD(sp, f32 *, 0x4) = 1.6e+03f;
    M2C_FIELD(sp, f32 *, 0x8) = -1.6e+03f;
    M2C_FIELD(sp, f32 *, 0xC) = 1.0f;
    sceVu0UnitMatrix(&D_00FDF390);
    sceVu0TransMatrix(&D_00FDF390, &D_00FDF390, sp);
    func_00f36330();
}

void func_00f3b418(void) {
    D_00F9A530 = 0;
    D_00FDFFD8 = &D_00FDFFE0;
    D_00F9A534 = 0;
    D_00F9A538 = 0;
    func_001be820((s32) &D_00FDF7D8, 0x800);
}

void func_00f3b860(s32 arg0, s32 arg1) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg1, s32 *, 0x10);
    switch (temp_v1) {                              /* irregular */
    case 7:
        func_00f3b530(arg0, arg1);
        return;
    case 19:
        func_00f3b6d0(arg0, arg1);
        return;
    case 9:
        func_00f3b850(arg0, arg1);
        return;
    }
}

void func_00f3e030(void *arg0, s32 arg1) {
    s32 sp[20];
    M2C_FIELD(arg0, f32 *, 0) = (f32) (M2C_FIELD(arg0, f32 *, 0) - M2C_FIELD(D_00F864C0, f32 *, 0x30));
    M2C_FIELD(arg0, f32 *, 4) = (f32) (M2C_FIELD(arg0, f32 *, 4) - M2C_FIELD(D_00F864C0, f32 *, 0x34));
    M2C_FIELD(arg0, f32 *, 8) = (f32) (M2C_FIELD(arg0, f32 *, 8) - M2C_FIELD(D_00F864C0, f32 *, 0x38));
    func_001bf048(sp, D_00F864C0);
    sceVu0TransposeMatrix(sp, sp);
    sceVu0ApplyMatrix(&M2C_FIELD(sp, M2C_UNK *, 0x40), sp, arg0);
    func_00f3dd60(arg1, &M2C_FIELD(sp, M2C_UNK *, 0x40));
}

s32 func_00f3f260(s32 arg0, s32 arg1) {
    if (func_00f40c98() < 2) {
        return func_00f62b98(arg0, arg1);
    }
    return 0;
}

void func_00f3fcc0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[16];
    func_001bef40(sp, &D_00FB7240, arg1);
    func_001bef40(&M2C_FIELD(sp, M2C_UNK *, 0x20), &D_00FB7250, *(M2C_UNK *)((s8 *)(s8 *)&D_00F87E60 + (arg2 * 4)));
    *(M2C_UNK *)((s8 *)(s8 *)&D_00F86A58 + (arg0 * 0x590)) = -1;
    func_00f3f8d0(arg0, &M2C_FIELD(sp, M2C_UNK *, 0x20));
    func_00f3fb28(arg0, sp);
}
