/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"


void func_001f3680(void *arg0) {
    M2C_FIELD(arg0, s64 *, 0x40) = (s64) (M2C_FIELD(arg0, s64 *, 0x40) | ((s64) 0x8000 << 0x11));
}

void func_001f3698(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x84) = arg1;
    M2C_FIELD(arg0, s64 *, 0x40) = (s64) (M2C_FIELD(arg0, s64 *, 0x40) | ((s64) 0x8000 << 0x11));
}

