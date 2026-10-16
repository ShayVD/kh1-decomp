/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00115940();

void func_001162f8(s32 arg0, u8 *arg1) {
    u64 wide;
    wide = *arg1;

    if ((wide >> 4) == 9) {
        func_00115940();
    }
}
