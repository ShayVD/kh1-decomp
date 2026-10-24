/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0052.h"
#include "data/pieces/D_002E26A0.h"
f32 atan2f(f32, f32);
s32 func_001375f0(s32);
s32 func_0013daa8();
s32 func_0013f330(s32, s32);
s32 func_0013f478(s32, s32);
void func_00130398(s32, s32, f32);
void func_00130578(s32, s32, f32);
void func_0014f658(s32, s32);
void func_002675a8(s32, s32);

s32 func_0013daf8(void) {
    s32 temp_v0;
    s32 var_v0;

    temp_v0 = func_0013daa8();
    var_v0 = 0;
    if (temp_v0 < 0) {
        return var_v0;
    }
    var_v0 = ((M2C_UNK *)&D_002E26A0)[temp_v0];
    return var_v0;
}

s32 func_0013f618(s32 arg0, s32 arg1) {
    if ((func_001375f0(arg0) != 0) && (func_0013f478(arg0, arg1) != 0)) {
        func_0014f658(arg0, 0xD);
        func_00130398(arg0, func_0013f330(arg0, 0x1D) | 0x01000000, 0.0f);
        func_00130578(arg0, func_0013f330(arg0, 0x1B) | 0x40000000, 0.0f);
        M2C_FIELD(arg0, f32 *, 0x2C) = 0.0f;
        return 1;
    }
    return 0;
}

void func_0013f6d0(s32 arg0, s32 arg1) {
    func_00130398(arg0, func_0013f330(arg0, 0x23) | 0x01000000, 8.0f);
    func_00130578(arg0, 0x40000000, 0.0f);
    func_002675a8(arg1, arg0 + 0x30);
    M2C_FIELD(arg1, f32 *, 0xC) = 0.0f;
    M2C_FIELD(arg0, f32 *, 0x150) = atan2f(M2C_FIELD(arg1, f32 *, 0), M2C_FIELD(arg1, f32 *, 8));
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xFFDFFFFF);
}

void func_0013f8a8(s32 arg0, s32 arg1, void *arg2) {
    f32 temp_f1;

    temp_f1 = M2C_FIELD(arg2, f32 *, 0xC);
    if (temp_f1 > 0.0f) {
        if ((M2C_FIELD(arg2, f32 *, 4) > 0.0f) && (temp_f1 > 0.8f)) {
            M2C_FIELD(arg2, f32 *, 0xC) = 12.0f;
            return;
        }
        M2C_FIELD(arg2, f32 *, 0xC) = 2.0f;
    }
}
