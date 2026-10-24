/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

void func_001a8d78(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s8 *, 4) = 0;
}

f32 func_001a92f0(s32 arg0, f32 fparg0) {
    f32 var_f0;
    s32 var_a0;

    var_a0 = arg0;
    var_f0 = 1.0f;
    if (var_a0 > 0) {
        do {
            var_a0 -= 1;
            var_f0 *= fparg0;
        } while (var_a0 != 0);
    }
    return var_f0;
}
#include "data/bss_0061_mixed.h"
#include "data/data_0037.h"
