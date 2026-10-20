/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00669350; /* src/data/bss_0066.c: u8 D_00669350[0x8] */

s32 func_002485f0(void) {
    s32 temp_a1;
    s32 var_a1;

    var_a1 = 0;
    if (M2C_FIELD(&D_00669350, s32 *, 0) == 1) {
        temp_a1 = M2C_FIELD(M2C_FIELD(&D_00669350, void **, 4), s32 *, 0x20) != 0;
        var_a1 = (M2C_FIELD(M2C_FIELD(&D_00669350, void **, 4), s32 *, 4) != 0) ? (temp_a1 | 2) : temp_a1;
    }
    return var_a1;
}
