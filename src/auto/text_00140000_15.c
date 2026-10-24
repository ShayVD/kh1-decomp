/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/pieces/D_00350D88.h"
f32 PlatSqrtf(f32);
s32 func_0014ee88();
void func_0014cc38(s32);

f32 func_0014cce0(s32 arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x3B8) = PlatSqrtf((2.0f * fparg0) / 0.48469386f);
    M2C_FIELD(arg0, f32 *, 0x3BC) = (f32) -fparg0;
    func_0014cc38(arg0);
    return M2C_FIELD(arg0, f32 *, 0x3B8);
}

s32 func_0014efe0(s32 arg0, s32 arg1) {
    s32 var_v0;

    if (!((arg1 <= 0) || (var_v0 = 1, (((func_0014ee88() >> (arg1 - 1)) & 1) == 0)))) {
        return var_v0;
    }
    var_v0 = 0;
    return var_v0;
}

s32 func_0014f5c8(void *arg0) {
    s32 temp_v1;
    s32 var_v0;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x70);
    var_v0 = 1;
    if (temp_v1 == 0x17) {
        return var_v0;
    }
    var_v0 = (*(M2C_UNK *)((s8 *)(s8 *)&D_00350D88 + (temp_v1 << 5)) & 3) == 2;
    return var_v0;
}
