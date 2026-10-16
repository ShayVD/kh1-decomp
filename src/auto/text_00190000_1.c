/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00183b20(s32, s32);
extern s32 D_00615E64;

void func_0019eef0(s32 arg0, void *arg1) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0;
    temp_v0 = M2C_FIELD(temp_s0, s32 *, 0xC);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0;
    }
    temp_a1 = M2C_FIELD(temp_s0, s32 *, 0x10);
    if (temp_a1 != 0) {
        func_00183b20(D_00615E64, temp_a1);
        M2C_FIELD(temp_s0, s32 *, 0x10) = 0;
    }
    temp_a1_2 = M2C_FIELD(temp_s0, s32 *, 0x14);
    if (temp_a1_2 != 0) {
        func_00183b20(D_00615E64, temp_a1_2);
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0;
    }
}
