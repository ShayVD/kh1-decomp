/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00123760(M2C_UNK *);
extern M2C_UNK D_002C64A0;

s32 func_00123790(void) {
    s8 *var_s0;
    s32 var_s1;

    var_s0 = &D_002C64A0;
    var_s1 = 0x5F;
    do {
        if ((M2C_FIELD(var_s0, s64 *, 0x370) & ((s64) 0x800002 << 0x20)) == ((s64) 0x8000 << 0x12)) {
            func_00123760(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x4B0;
    } while (var_s1 >= 0);
    return 0;
}
