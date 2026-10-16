/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_0066E6D8[];

s32 func_002603d0(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = D_0066E6D8[5];
    D_0066E6D8[6] = arg1;
    D_0066E6D8[5] = arg0;
    return temp_v0;
}

s32 func_002603e8(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = D_0066E6D8[3];
    D_0066E6D8[4] = arg1;
    D_0066E6D8[3] = arg0;
    return temp_v0;
}
