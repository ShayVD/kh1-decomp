/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00FCC550;
s32 sceVu0CopyVector(s32, s32);

void func_00f324d0(s32 arg0) {
    sceVu0CopyVector(arg0, (s32) &D_00FCC550);
}
