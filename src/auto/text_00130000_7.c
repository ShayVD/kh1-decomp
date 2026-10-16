/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0013c458(s32, s32);

void func_0013c548(s32 arg0) {
    s32 var_a0;
    s32 var_s0;

    var_s0 = 0;
    var_a0 = 0;
    do {
        var_a0 = var_s0;
        var_s0 += 1;
        func_0013c458(var_a0, arg0);
    } while (var_s0 < 0xA);
}
