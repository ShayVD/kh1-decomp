/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

s32 func_0014d778(void *arg0, s32 arg1) {
    if ((M2C_FIELD(arg0, f32 *, 0x3C4) >= 0.0f) && ((M2C_FIELD(arg0, f32 *, 0x3D4) <= M2C_FIELD(arg0, f32 *, 0x3BC)) || (arg1 == 0))) {
        return 4;
    }
    return M2C_FIELD(arg0, s32 *, 0x70);
}

s32 func_0014f828(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x70);
}
#include "data/data_0030.h"
