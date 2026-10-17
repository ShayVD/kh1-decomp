/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern f32 D_003DAD3C;
extern f32 D_003DAD40;
extern s32 D_003DAD44;

s32 func_001e2678(void) {
    s32 temp_v1;

    temp_v1 = D_003DAD44 - 1;
    D_003DAD44 = temp_v1;
    D_003DAD3C += D_003DAD40;
    return (temp_v1 > 0) ? 0 : 4;
}
