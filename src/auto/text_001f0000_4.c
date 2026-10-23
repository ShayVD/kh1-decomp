/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
extern f32 D_002BBDFC;
s32 func_001f86e0(s32, s32, s32, s32, s32);
void func_001f5fe0(s32);
void func_001f9438(s32, s32, s32, s32, s32, s32, s32);
void func_001fefc8(s32, s32, s32, s32, s32);

void func_001f8120(s32 arg0) {
    M2C_FIELD(arg0, f32 *, 0x9C) = (f32) (M2C_FIELD(arg0, f32 *, 0x9C) + D_002BBDFC);
    func_001f5fe0(arg0);
}

void func_001f8ee0(s32 arg0) {
    func_001f86e0(arg0, 0, (s32) (M2C_FIELD(arg0, u16 *, 0xC0) << 0x10) >> 0x14, 0x200, (((s32) (M2C_FIELD(arg0, u16 *, 0xC4) << 0x10) >> 0x14) * M2C_FIELD(arg0, s16 *, 0xCE)) - ((s32) (M2C_FIELD(arg0, u16 *, 0xC8) << 0x10) >> 0x14));
}

void func_001f9270(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u32 temp_v0;

    temp_v0 = 0x14 - arg4;
    func_001f9438(arg0, arg1, arg2, ((s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1) + 2, arg3, arg4, arg5);
}

void func_001fd5e0(s32 arg0, s32 arg1) {
    s16 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0xD8);
    M2C_FIELD(arg0, s16 *, 0xCC) = (s16) ((s32) ((arg1 + temp_v1) - 1) / temp_v1);
    M2C_FIELD(arg0, s16 *, 0xCA) = (s16) arg1;
}

void func_001fef40(s32 arg0) {
    s32 temp_v0;
    s32 temp_v1;

    if (M2C_FIELD(arg0, s16 *, 0xCC) != 0) {
        temp_v0 = (s32) (M2C_FIELD(arg0, u16 *, 0xC2) << 0x10) >> 0x14;
        temp_v1 = (s32) (M2C_FIELD(arg0, u16 *, 0xC4) << 0x10) >> 0x14;
        func_001fefc8(arg0, (s32) (M2C_FIELD(arg0, s16 *, 0xBE) + (M2C_FIELD(arg0, s16 *, 0xDA) * temp_v0)) >> 4, (s32) (M2C_FIELD(arg0, s16 *, 0xC0) + (M2C_FIELD(arg0, s16 *, 0xD2) * temp_v1)) >> 4, temp_v0 - ((s32) (M2C_FIELD(arg0, u16 *, 0xC6) << 0x10) >> 0x14), temp_v1 - ((s32) (M2C_FIELD(arg0, u16 *, 0xC8) << 0x10) >> 0x14));
    }
}
#include "data/pieces/D_002BBDFC.h"
