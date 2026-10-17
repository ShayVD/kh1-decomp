/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

void func_00122f58(s32, f32, f32, f32);

s32 func_001d1f48(s32 arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_v0 != 0) {
        func_00122f58(temp_v0, (f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184), 0.0f, 1.0f);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d1fb0(s32 arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_v0 != 0) {
        func_00122f58(temp_v0, (f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184), 0.0f, 2.0f);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001d2018(s32 arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_v0 != 0) {
        func_00122f58(temp_v0, (f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184), 0.0f, 3.0f);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}
