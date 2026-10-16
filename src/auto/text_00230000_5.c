/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_00237600(void *arg0) {
    s32 temp_v1;
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;

    temp_v1 = 1 << M2C_FIELD(arg0, s32 *, 0);
    var_s1 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_v1 > 0) {
        var_s0 = temp_v1;
        var_a0 = var_s1;
        do {
            var_s0 -= 1;
            memset(var_a0, 0, 8);
            var_s1 += 8;
            var_a0 = var_s1;
        } while (var_s0 != 0);
    }
}
