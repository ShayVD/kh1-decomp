/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00137308(void *, void *);
M2C_UNK func_0014f658(void *, M2C_UNK);
M2C_UNK func_00151cd0(void *);
M2C_UNK func_002675a8(void *, void *);
extern f32 D_002BBDFC;
f32 atan2f(f32, f32);
f32 fabsf(f32);
s32 func_0014f600(void *);
s32 func_00151e28();

void func_00151fa0(void *arg0) {
    s32 sp[4];    f32 temp_f0;
    f32 temp_f0_2;
    f32 var_f12;
    f32 var_f13;
    void *temp_a0;
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x144);
    if (func_00151e28() != 0) {
        temp_f0 = M2C_FIELD(temp_s1, f32 *, 4) + D_002BBDFC;
        M2C_FIELD(temp_s1, f32 *, 4) = temp_f0;
        if (temp_f0 > 12.0f) {
            func_00137308(arg0, M2C_FIELD(arg0, void **, 8));
            func_002675a8(sp, M2C_FIELD(arg0, void **, 8) + 0x30);
            var_f12 = M2C_FIELD(sp, f32 *, 0x0);
            var_f13 = M2C_FIELD(sp, f32 *, 0x8);
            if (fabsf(var_f13) < fabsf(var_f12)) {
                var_f13 = 0.0f;
                M2C_FIELD(sp, f32 *, 0x8) = 0.0f;
            } else {
                var_f12 = 0.0f;
                M2C_FIELD(sp, f32 *, 0x0) = 0.0f;
            }
            M2C_FIELD(M2C_FIELD(arg0, void **, 8), f32 *, 0x150) = atan2f(var_f12, var_f13);
            func_0014f658(M2C_FIELD(arg0, void **, 8), 0x1B);
        }
    } else {
        M2C_FIELD(temp_s1, f32 *, 4) = 0.0f;
    }
    temp_a0 = M2C_FIELD(arg0, void **, 8);
    if ((temp_a0 != NULL) && (func_0014f600(temp_a0) != 0)) {
        temp_f0_2 = M2C_FIELD(temp_s1, f32 *, 0xC) + D_002BBDFC;
        M2C_FIELD(temp_s1, f32 *, 0xC) = temp_f0_2;
        if (temp_f0_2 >= 1.2e+02f) {
            func_00151cd0(arg0);
        }
    } else {
        M2C_FIELD(temp_s1, f32 *, 0xC) = 0.0f;
    }
}
