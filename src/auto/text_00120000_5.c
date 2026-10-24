/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_002672f8();

f32 func_00120ef0(f32 *arg0, s32 arg1, void *arg2) {
    f32 *var_v0;
    f32 temp_f20;
    s32 var_v1;

    M2C_FIELD(arg2, f32 *, 0xC) = 1.0f;
    func_002672f8();
    temp_f20 = 1.0f / M2C_FIELD(arg0, f32 *, 0xC);
    var_v0 = arg0;
    var_v1 = 2;
    do {
        var_v1 -= 1;
        *var_v0 *= temp_f20;
        var_v0 += 1;
    } while (var_v1 >= 0);
    M2C_FIELD(arg0, f32 *, 0xC) = 1.0f;
    return temp_f20;
}
