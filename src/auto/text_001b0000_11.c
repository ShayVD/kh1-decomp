/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
s32 func_001ba3f0(M2C_UNK);
s32 func_001ba980();
s32 func_001ba9a8(void);
s32 func_001baad0();

s32 func_001b9e88(void) {
    s32 var_v0;

    var_v0 = 0;
    if (func_001baad0() & 0x80) {
        return var_v0;
    }
    var_v0 = func_001ba3f0(0x31) > 0;
    return var_v0;
}

void func_001ba420(s32 arg0, s32 arg1) {
    *(s8 *)((s32) (func_001ba9a8()) + (s32) arg0) = arg1;
}

void func_001baa58(s32 arg0) {
    s32 temp_a2;
    s32 var_a1;
    u8 *temp_a0;
    u8 temp_v1;

    temp_a2 = func_001ba980();
    var_a1 = 0;
    do {
        temp_a0 = temp_a2 + var_a1;
        temp_v1 = *(M2C_UNK *)((s32) arg0 + (s32) var_a1);
        var_a1 += 1;
        *temp_a0 = temp_v1;
    } while (var_a1 < 8);
}
