/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"


s32 func_00162390(void *arg0) {
    s32 *var_v1;
    s32 var_a0;
    s32 var_v0;

    var_v1 = M2C_FIELD(arg0, s32 **, 0x30);
    var_v0 = 0;
    if (var_v1 != NULL) {
        var_a0 = 0;
        if (*var_v1 != 0) {
            do {
                var_v1 += 1;
                var_a0 += 1;
            } while (*var_v1 != 0);
        }
        var_v0 = var_a0;
    }
    return var_v0;
}
