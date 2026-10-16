/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00137688(void *, f32);
M2C_UNK func_00267530(void *, s32, s32);
f32 func_001376e8(void *, void *);

s32 func_0013fba0(void *arg0, s32 arg1) {
    s32 sp[4];
    s32 var_v0;

    if ((arg1 != 0) || (var_v0 = 0, (M2C_FIELD(arg0, f32 *, 0x24) <= 0.0f))) {
        func_00267530(sp, M2C_FIELD(arg0, s32 *, 0x148) + 0x40, arg0 + 0x10);
        func_00137688(arg0, func_001376e8(arg0, sp));
        var_v0 = M2C_FIELD(arg0, s32 *, 0x70);
    }
    return var_v0;
}
