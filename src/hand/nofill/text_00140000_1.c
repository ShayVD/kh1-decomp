/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00304E40;
extern M2C_UNK D_00533BA0;

void *func_00144e88(s32 arg0) {
    return (s8 *)&D_00304E40 + (arg0 * 0xD);
}

void *func_001477c8(s32 arg0) {
    return (s8 *)&D_00533BA0 + arg0;
}
