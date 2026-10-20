/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0024b1e8(M2C_UNK *, M2C_UNK *, M2C_UNK);
extern M2C_UNK D_00491878;
extern M2C_UNK D_00491880;

s32 func_0024b178(void *arg0) {
    u32 wide;
    if (M2C_FIELD(arg0, u8 *, 0) != 1) {
        func_0024b1e8(&D_00491878, &D_00491880, 0x3F);
    }
   wide = M2C_FIELD(arg0, u8 *, 1);
    return wide + (M2C_FIELD(arg0, u8 *, 4) << 0x18) + ((M2C_FIELD(arg0, u8 *, 3) << 0x10) + (M2C_FIELD(arg0, u8 *, 2) << 8));
}
#include "data/data_0049.h"
