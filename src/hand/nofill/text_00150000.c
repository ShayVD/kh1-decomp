/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00550400; /* src/data/bss_0055.c: E550400 D_00550400[0x34] */
extern M2C_UNK D_00FE0000;

void *func_001559f0(s32 arg0, s32 arg1) {
    s32 var_a1;
    void *var_v0;

    var_a1 = arg1;
    var_v0 = (s8 *)&D_00550400 + (arg0 * 0x48);
    if (var_a1 > 0) {
        do {
            var_a1 -= 1;
            M2C_FIELD(var_v0, s8 *, 0) = -1;
            M2C_FIELD(var_v0, s8 *, 2) = 0;
            var_v0 += 0x48;
        } while (var_a1 != 0);
    }
    return (s8 *)&D_00FE0000 + (arg0 << 0x12);
}
