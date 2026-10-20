/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern void *D_00615E60;
void *func_00182588(void *, s32, M2C_UNK);

void func_00184cb8(s32 arg0, void *arg1, void *arg2) {
    s32 temp_v0;
    s32 temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *var_a2;

    temp_v0 = M2C_FIELD(arg1, s32 *, 0xC);
    if (temp_v0 != -1) {
        var_a2 = NULL;
        temp_v0_2 = M2C_FIELD(D_00615E60, s32 *, 0x80) + (temp_v0 * 0x10);
        if (temp_v0_2 != 0) {
            var_a2 = func_00182588(D_00615E60, temp_v0_2, 0);
            M2C_FIELD(var_a2, s32 *, 4) = arg0;
        }
        temp_v0_3 = var_a2 + M2C_FIELD(arg1, s32 *, 0x10);
        temp_v0_4 = temp_v0_3 + 0xA0;
        M2C_FIELD(temp_v0_3, f32 *, 0xA0) = (f32) M2C_FIELD(arg2, s16 *, 0);
        M2C_FIELD(temp_v0_4, f32 *, 4) = (f32) M2C_FIELD(arg2, s16 *, 2);
        M2C_FIELD(temp_v0_4, f32 *, 8) = (f32) M2C_FIELD(arg2, s16 *, 4);
    }
}
#include "data/bss_0061_mixed.h"
