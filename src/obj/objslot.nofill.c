/* Object data slots, without delay-slot filling (docs/modules.md "Session
 * 52"): func_001559f0.  Read from the code, not proved by a boot. */
#include "m2c.h"

/* func_001559f0 (from hand/nofill/text_00150000.c). */
extern M2C_UNK D_00550400;
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

