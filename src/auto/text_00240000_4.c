/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

void *func_00241b60(M2C_UNK, s32);
void *func_00245f58(s32);

void func_00241c00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *temp_v0;

    temp_v0 = func_00241b60(3, arg4);
    M2C_FIELD(temp_v0, s32 *, 0xA88) = arg0;
    M2C_FIELD(temp_v0, s32 *, 0xA8C) = arg1;
    M2C_FIELD(temp_v0, s32 *, 0xA90) = arg2;
    M2C_FIELD(temp_v0, s32 *, 0xA94) = arg3;
}

void func_00245f90(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = func_00245f58(arg1);
    if (M2C_FIELD(temp_v0, s32 *, 0) == 0) {
        M2C_FIELD(temp_v0, s32 *, 8) = arg0;
        M2C_FIELD(temp_v0, s32 *, 0xC) = arg1;
        M2C_FIELD(temp_v0, s32 *, 0) = 1;
        M2C_FIELD(temp_v0, f32 *, 4) = 1.0f;
    }
}

s32 func_00246cf0(s32 arg0, s32 *arg1) {
    s32 *var_a1;
    s32 temp_lo;
    s32 var_s0;
    s32 var_t9;

    var_s0 = 5;
    var_t9 = 0;
    temp_lo = arg0 / 10000;
    M2C_FIELD(arg1, s32 *, 0) = temp_lo;
    M2C_FIELD(arg1, s32 *, 4) = (s32) ((s32) (arg0 % 10000) / 1000);
    M2C_FIELD(arg1, s32 *, 8) = (s32) ((s32) (arg0 % 1000) / 100);
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (arg0 % 100) / 10);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) (arg0 % 10);
    if (temp_lo == 0) {
        var_a1 = arg1;
loop_2:
        var_t9 += 1;
        var_a1 += 1;
        var_s0 -= 1;
        if (var_t9 < 4) {
            if (*var_a1 == 0) {
                goto loop_2;
            }
        }
    }
    return var_s0;
}

void func_002492d0(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    M2C_FIELD(arg0, f32 *, 0) = fparg0;
    M2C_FIELD(arg0, f32 *, 4) = fparg1;
    M2C_FIELD(arg0, f32 *, 0xC) = fparg2;
    M2C_FIELD(arg0, f32 *, 8) = fparg3;
}
