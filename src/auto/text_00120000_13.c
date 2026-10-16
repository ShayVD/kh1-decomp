/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"


void func_0012a8c0(void *arg0) {
    u64 wide;
    u64 *temp_a1;

    temp_a1 = M2C_FIELD(arg0, u64 **, 0);
    wide = M2C_FIELD(arg0, u32 *, 4);
    *temp_a1 = (*temp_a1 & ~0x3000) | ((wide & 3) << 0xC);
}
