/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
M2C_UNK func_0014cc38();

f32 func_0014cc88(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x3B8) = fparg0;
    M2C_FIELD(arg0, f32 *, 0x3BC) = (f32) (fparg0 * fparg0 * -0.48469386f * 0.5f);
    func_0014cc38();
    return -M2C_FIELD(arg0, f32 *, 0x3BC);
}
