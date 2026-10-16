/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_00304BE8;
void *func_00123488(u8);

s32 func_001d4690(void *arg0) {
    s32 temp_s1;
    void *temp_v0;

    temp_s1 = arg0 + 4;
    temp_v0 = func_00123488(M2C_FIELD((M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) + D_00304BE8), u8 *, 0x48E));
    if (temp_v0 != NULL) {
        M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = (s32) (M2C_FIELD(temp_v0, f32 *, 0x16C) * 0.5f);
    }
    return 2;
}
