/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0014f658(void *, M2C_UNK);
M2C_UNK func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, s32);
M2C_UNK func_002675a8(s32);
extern M2C_UNK func_0014c400;
extern M2C_UNK func_0014c428;
extern M2C_UNK func_0014c5c8;
extern M2C_UNK func_0014c6c0;
extern M2C_UNK func_0014c850;
extern M2C_UNK func_0014ca38;
extern M2C_UNK func_0014dc08;
extern M2C_UNK func_0014dc90;
extern M2C_UNK func_0014dd48;
extern M2C_UNK func_0014df60;
extern M2C_UNK func_0014e160;
extern M2C_UNK func_0014e400;
s32 func_00147c98(s32, s32, s32);
s32 func_001484c8(s32, s32, s32, f32);

s32 func_00148768(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = func_00147c98(arg0, arg1, 0x4E20);
    if (temp_v0 != 0) {
        temp_v0_2 = func_001484c8(temp_v0, arg2, arg3, fparg0);
        if ((temp_v0_2 != 0) && (arg1 & 0x800)) {
            M2C_FIELD(temp_v0_2, s16 *, 6) = -1;
        }
    }
    return temp_v0;
}

void func_0014cb38(void) {
    func_0014f830(0x15, 5, &func_0014c400, &func_0014c428, &func_0014c6c0, &func_0014c850, &func_0014ca38, &func_0014c5c8, 0);
}

void func_0014d428(void *arg0, void *arg1, f32 fparg0, f32 fparg1) {
    f32 temp_f0;
    f32 temp_f20;

    func_002675a8(arg0 + 0x3C0);
    M2C_FIELD(arg0, f32 *, 0x3CC) = fparg0;
    temp_f20 = fparg1 * 0.5f;
    M2C_FIELD(arg0, s32 *, 0x3B0) = 0;
    temp_f0 = (2.0f * M2C_FIELD(arg1, f32 *, 4)) / (temp_f20 * temp_f20);
    M2C_FIELD(arg0, f32 *, 0x3B8) = temp_f20;
    M2C_FIELD(arg0, f32 *, 0x3B4) = temp_f0;
    M2C_FIELD(arg0, f32 *, 0x3C4) = (f32) (-temp_f0 * temp_f20);
    if (M2C_FIELD(arg0, s32 *, 0x70) == 4) {
        func_0014f658(arg0, 5);
        M2C_FIELD(arg0, f32 *, 0x3BC) = (f32) M2C_FIELD(arg0, f32 *, 0x3D4);
    } else {
        func_0014f658(arg0, 3);
    }
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xFFFEFFFF);
}

void func_0014e4b8(void) {
    func_0014f830(8, 0x76, &func_0014dc08, &func_0014dc90, &func_0014df60, &func_0014e160, &func_0014e400, &func_0014dd48, 0);
}
