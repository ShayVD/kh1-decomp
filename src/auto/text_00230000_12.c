/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

s32 func_001ba3f0(s32);
s32 func_001ba458(s32);
u32 func_001eeaf0();
u32 func_001ef7a0();

s32 func_00230698(s32 arg0) {
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 var_v0;
    u32 temp_s0;

    temp_s0 = func_001eeaf0();
    var_v0 = -1;
    if (func_001ef7a0() >= temp_s0) {
        temp_s0_2 = func_001ba3f0(arg0);
        if (temp_s0_2 == func_001ba458(arg0)) {
            return -2;
        }
        temp_s0_3 = func_001ba3f0(arg0);
        var_v0 = (temp_s0_3 < func_001ba458(arg0)) ? arg0 : -4;
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return var_v0;
    }
    return var_v0;
}

s32 func_00230ec8(s32 arg0) {
    if (arg0 >= 0) {
        return (func_001ef7a0() <= 0x1869EU) ? arg0 : -1;
    }
    return -2;
}
