/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

#include "data/pieces/D_00304BE8.h"

s32 func_001dba30(void *arg0) {
    s32 temp_a0;
    s32 var_a0;
    s32 var_a2;
    u16 *var_v1;
    u16 temp_v0;

    var_a2 = 0;
    var_a0 = 0x32;
    var_v1 = ((s32)D_00304BE8) + 0x7D8;
    do {
        temp_v0 = *var_v1;
        var_v1 += 1;
        var_a0 -= 1;
        var_a2 += temp_v0;
    } while (var_a0 >= 0);
    temp_a0 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_a0;
    M2C_FIELD(((temp_a0 * 4) + arg0), s32 *, 0x184) = var_a2;
    return 2;
}
