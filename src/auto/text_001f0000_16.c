/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern void *D_00640DD8; /* src/data/bss_0064.c: s32 D_00640DD8 */

s32 func_001f3d10(void *arg0) {
    if ((arg0 != NULL) && (((u32) (M2C_FIELD(arg0, s32 *, 0x8C) - 4) < 2U) || ((s32) ((u64) ((s64) M2C_FIELD(arg0, u32 *, 0x44) << 0x20) >> 0x20) & 1))) {
        return 1;
    }
    return 0;
}

s32 func_001f40c8(void) {
    s32 var_a0;
    s32 var_v0;
    void *temp_v0;
    void *var_v1;

    var_v0 = 0;
    if (D_00640DD8 == NULL) {
        return var_v0;
    }
    var_v1 = M2C_FIELD(D_00640DD8, void **, 0x18);
    var_a0 = 1;
    if (var_v1 != NULL) {
        do {
            temp_v0 = M2C_FIELD(var_v1, void **, 0x18);
            var_a0 += 1;
            var_v1 = temp_v0;
        } while (temp_v0 != NULL);
    }
    var_v0 = var_a0;
    return var_v0;
}
