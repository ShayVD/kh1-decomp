/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0062.h"
extern s32 D_0037A128;
s32 D_00621318 ALIGNED(8);
s32 func_001ba458(s32);
s32 func_001ba9a8();

s32 func_001ba1e0(void) {
    return 0xB040;
}

void func_001ba358(s32 arg0, s32 arg1) {
    s32 var_v0;
    u8 *temp_s2;
    u8 temp_s1;

    temp_s2 = func_001ba9a8() + arg0;
    temp_s1 = *temp_s2;
    if (func_001ba458(arg0) < (temp_s1 + arg1)) {
        var_v0 = func_001ba458(arg0);
    } else {
        var_v0 = *temp_s2 + arg1;
    }
    *temp_s2 = (u8) var_v0;
}

s32 func_001ba848(void) {
    return 0;
}

f32 func_001ba850(void) {
    return 0.0f;
}

f32 func_001ba860(void) {
    return 0.0f;
}

void func_001ba910(s32 arg0) {
    D_00621318 = arg0;
}

s32 func_001ba920(void) {
    return D_00621318;
}

void func_001bb428(s32 arg0) {
    D_0037A128 = arg0;
}
#include "data/data_0037.h"
