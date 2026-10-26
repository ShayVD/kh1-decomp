/* wm.x func_00f66990: the twin of gb.x func_00f3f898 (tools/ovl/twins.py). */
/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern f32 D_0108EEC8;
extern f32 D_0108EECC;
extern f32 D_0108EED0;
extern f32 D_0108EED4;

void func_00f66990(s32 arg0, s32 arg1, void *arg2) {
    f32 temp_f0;

    temp_f0 = (f32) arg0;
    D_0108EEC8 = (f32) arg1;
    D_0108EECC = temp_f0;
    D_0108EED4 = (temp_f0 * M2C_FIELD(arg2, f32 *, 0x28)) + M2C_FIELD(arg2, f32 *, 0x38);
    D_0108EED0 = 1.0f / temp_f0;
}
