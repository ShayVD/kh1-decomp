/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_00640DD8;
s32 func_001fd538();

s32 func_001f4378(s32 arg0) {
    return D_00640DD8 == arg0;
}

s32 func_001fd548(void *arg0) {
    return (((s32) (M2C_FIELD(arg0, s16 *, 0xD2) + M2C_FIELD(arg0, s16 *, 0xD0) + 8) >> 4) * M2C_FIELD(arg0, s16 *, 0xD8)) + func_001fd538();
}
#include "data/bss_0064_mixed.h"
