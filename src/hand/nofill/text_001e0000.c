/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

f32 PlatSqrtf(f32);

f32 func_001edc50(void *arg0) {
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f2;

    temp_f0 = M2C_FIELD(arg0, f32 *, 0);
    temp_f2 = M2C_FIELD(arg0, f32 *, 4);
    temp_f1 = M2C_FIELD(arg0, f32 *, 8);
    return PlatSqrtf((temp_f0 * temp_f0) + (temp_f2 * temp_f2) + (temp_f1 * temp_f1));
}
