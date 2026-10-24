/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "ppp.h"

s32 *func_001803b8();

s32 * func_001804d0(s32 arg0, s32 arg1) {
    s32 *var_v1;
    s32 temp_v0;
    s32 var_a0;
    s32 var_a1;

    var_v1 = func_001803b8();
    var_a1 = 4;
    do {
        temp_v0 = *var_v1;
        var_v1 += 1;
        if (temp_v0 > 0) {
            var_a0 = temp_v0;
            do {
                var_a0 -= 1;
                *var_v1 += arg1;
                var_v1 += 1;
            } while (var_a0 != 0);
        }
        var_a1 -= 1;
    } while (var_a1 >= 0);
    return var_v1;
}

void func_00180e80(void *arg0) {
    M2C_FIELD(arg0, s8 *, 8) = -1;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 9) = 0;
    M2C_FIELD(arg0, s8 *, 0xA) = 0;
}
