/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

u32 func_001ee708();
u32 func_001ef7a0();

s32 func_0022edc0(s32 arg0) {
    u32 temp_s0;

    temp_s0 = func_001ee708();
    return (func_001ef7a0() >= temp_s0) ? arg0 : -1;
}
