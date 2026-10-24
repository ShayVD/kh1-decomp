/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"
M2C_UNK func_0024ffa4(s32, s32, u32);

u32 func_0013cf78(void *arg0, s32 arg1) {
    u32 temp_s0;
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 8);
    temp_s0 = M2C_FIELD(temp_v0, u32 *, -4);
    func_0024ffa4(arg1, (temp_v0 - ((temp_s0 >> 2) * 4)) - 4, temp_s0);
    return temp_s0;
}
#include "data/data_0048.h"
