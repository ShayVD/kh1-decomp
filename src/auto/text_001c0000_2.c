/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001bfac8();
extern s8 D_00389C90;
f32 func_00176850();

void func_001c0688(s32 arg0) {
    s32 var_s0;

    if (arg0 > 0) {
        var_s0 = arg0;
        do {
            var_s0 -= 1;
            func_001bfac8();
        } while (var_s0 != 0);
    }
}

void func_001ca9e8(void) {
    D_00389C90 = 0;
}

s32 func_001ce440(void *arg0) {
    s32 temp_s1;
    s32 temp_s2;

    temp_s2 = arg0 + 4;
    temp_s1 = M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s2), s32 *, 0x180);
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s2), s32 *, 0x180) = (s32) ((func_00176850() * (f32) temp_s1) + 0.5f);
    return 2;
}
