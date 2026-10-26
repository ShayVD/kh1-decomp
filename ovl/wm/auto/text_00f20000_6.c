/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00f2c910(s32, s16);
M2C_UNK sceVu0MulMatrix(s32, s32, void *);
M2C_UNK sceVu0RotMatrixX(void *, void *, f32);
M2C_UNK sceVu0UnitMatrix(void *);
f32 func_00f2c7d8();

void func_00f2cb08(void *arg0) {
    s32 sp[16];
    s32 temp_s1;

    temp_s1 = arg0 + 0x20;
    func_00f2c910(temp_s1, M2C_FIELD(arg0, s16 *, 4));
    M2C_FIELD(arg0, f32 *, 0x60) = 1.0f;
    M2C_FIELD(arg0, f32 *, 0x64) = 1.0f;
    M2C_FIELD(arg0, f32 *, 0x68) = 1.0f;
    M2C_FIELD(arg0, f32 *, 0x6C) = func_00f2c7d8();
    if ((M2C_FIELD(arg0, u8 *, 1) == 0) && ((u32) (M2C_FIELD(arg0, u16 *, 0xC) - 0x1B) < 2U)) {
        sceVu0UnitMatrix(sp);
        sceVu0RotMatrixX(sp, sp, 3.141592503f);
        sceVu0MulMatrix(temp_s1, temp_s1, sp);
    }
}
