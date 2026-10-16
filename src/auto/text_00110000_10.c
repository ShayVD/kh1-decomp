/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"


void func_0011efa8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_a1;
    s32 var_a3;

    var_a1 = arg1;
    var_a3 = arg3;
    M2C_FIELD(arg0, s16 *, 0) = (s16) arg2;
    M2C_FIELD(arg0, s16 *, 2) = (s16) var_a3;
    M2C_FIELD(arg0, s32 *, 4) = var_a1;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    if (var_a3 > 0) {
        do {
            var_a3 -= 1;
            M2C_FIELD(var_a1, s16 *, 0) = 0;
            M2C_FIELD(var_a1, s16 *, 2) = 0;
            var_a1 += arg2;
        } while (var_a3 != 0);
    }
}
