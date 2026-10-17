/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_003F5980;
extern s32 D_003F59C0;
extern s32 D_003F5E58;

s32 func_0021ade8(s32 arg0) {
    s32 *var_a2;
    s32 temp_v1;
    s32 var_v0;
    u32 var_a1;

    var_a1 = 0;
    var_a2 = &D_003F5980;
loop_1:
    temp_v1 = *var_a2;
    var_a2 += 1;
    var_v0 = 1;
    if (temp_v1 == arg0) {
        return var_v0;
    }
    var_a1 += 1;
    if (var_a1 >= 2U) {
        var_v0 = 0;
    } else {
        goto loop_1;
    }
    return var_v0;
}

s32 func_0021b170(s32 arg0) {
    s32 *var_a2;
    s32 temp_v1;
    s32 var_v0;
    u32 var_a1;

    var_a1 = 0;
    var_a2 = &D_003F59C0;
loop_1:
    temp_v1 = *var_a2;
    var_a2 += 1;
    var_v0 = 1;
    if (temp_v1 == arg0) {
        return var_v0;
    }
    var_a1 += 1;
    if (var_a1 >= 2U) {
        var_v0 = 0;
    } else {
        goto loop_1;
    }
    return var_v0;
}

s32 func_0021e898(s32 arg0) {
    s32 *var_a2;
    s32 temp_v1;
    s32 var_v0;
    u32 var_a1;

    var_a1 = 0;
    var_a2 = &D_003F5E58;
loop_1:
    temp_v1 = *var_a2;
    var_a2 += 1;
    var_v0 = 1;
    if (temp_v1 == arg0) {
        return var_v0;
    }
    var_a1 += 1;
    if (var_a1 >= 2U) {
        var_v0 = 0;
    } else {
        goto loop_1;
    }
    return var_v0;
}
