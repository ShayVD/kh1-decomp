/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_0000AC20;
s32 func_00232cc0(s32);
void func_001b9b30(void);

void func_001bb218(s32 arg0, s32 arg1) {
    func_001b9b30();
    *(s8 *)((s8 *)&D_0000AC20 + (arg0 + func_00232cc0(4))) = arg1;
}
