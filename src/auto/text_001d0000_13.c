/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

s32 func_001e98d0(s32, s32);
void func_001315c0(s32, s32, s32, f32);
void func_0014f9b0(s32, s32, f32);

s32 func_001d2b58(s32 arg0) {
    s32 sp[4];
    s32 temp_s0;
    s32 temp_v1;

    temp_s0 = arg0 + 4;
    temp_v1 = func_001e98d0((s32) ((s64) (M2C_FIELD(arg0, s64 *, 0x328) << 0x1B) >> 0x20) & 1, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s0), s32 *, 0x17C));
    if ((M2C_FIELD(arg0, s32 *, 4) != 0) && (temp_v1 != 0)) {
        func_001315c0(M2C_FIELD(temp_v1, s32 *, 4), 0, (s32) sp, 0.0f);
        func_0014f9b0(M2C_FIELD(arg0, s32 *, 4), (s32) sp, 2.0f * (f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s0), s32 *, 0x180));
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 2);
    return 2;
}
