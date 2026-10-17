/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

s32 func_001a1158(s32, s32);

s32 pppRyjDrawKekotoFrame(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = arg0 + M2C_FIELD(M2C_FIELD(arg2, void **, 0xC), s32 *, 8);
    if (!(*(M2C_UNK *)arg1 == M2C_FIELD(arg0, s32 *, 0xC))) {
        return temp_v0;
    }
    return func_001a1158(arg1, temp_v0 + 0xA0);
    return temp_v0;
}
