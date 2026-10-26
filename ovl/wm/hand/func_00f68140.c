/* wm.x func_00f68140: the twin of gb.x func_00f41048 (tools/ovl/twins.py). */
/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00F707F8;
extern s32 D_00FB49E8;
void func_0024bc08(s32, s32);

s32 func_00f68140(s32 arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (arg0 < 0) {
        return var_v0;
    }
    var_v0 = M2C_FIELD(((arg0 * 0x48) + D_00FB49E8), s32 *, 0x14) != 0;
    return var_v0;
}

