/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern f32 D_00F82708;
extern f32 D_00F8270C;
extern f32 D_00F82710;
extern f32 D_00F82714;

void func_00f3f898(s32 arg0, s32 arg1, void *arg2) {
    f32 temp_f0;

    temp_f0 = (f32) arg0;
    D_00F82708 = (f32) arg1;
    D_00F8270C = temp_f0;
    D_00F82714 = (temp_f0 * M2C_FIELD(arg2, f32 *, 0x28)) + M2C_FIELD(arg2, f32 *, 0x38);
    D_00F82710 = 1.0f / temp_f0;
}
