/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_00547BA4;
void *func_00147840();

s32 func_00147860(void) {
    return D_00547BA4 + (M2C_FIELD(func_00147840(), s16 *, 6) * 0x16);
}
