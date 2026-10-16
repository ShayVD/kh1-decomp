/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00141e68(s32);
extern s32 D_002E26A0;

void func_00141eb8(void) {
    s32 *var_s0;
    s32 temp_v0;
    s32 var_s1;

    var_s0 = &D_002E26A0;
    var_s1 = 2;
    do {
        temp_v0 = *var_s0;
        var_s0 += 1;
        if (temp_v0 != 0) {
            func_00141e68(temp_v0);
        }
        var_s1 -= 1;
    } while (var_s1 >= 0);
}
