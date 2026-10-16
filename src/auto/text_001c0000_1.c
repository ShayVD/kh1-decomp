/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_002C5958;

s32 func_001cfe98(void) {
    D_002C5958 &= ~8;
    return 2;
}

s32 func_001cfeb8(void) {
    D_002C5958 |= 8;
    return 2;
}

s32 func_001cff08(void) {
    D_002C5958 |= 4;
    return 2;
}
