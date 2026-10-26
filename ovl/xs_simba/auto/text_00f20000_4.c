/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001224c8(s32, M2C_UNK *, M2C_UNK *, f32);
extern M2C_UNK D_002C5C60;
extern M2C_UNK func_00122768;
extern s32 D_00FA6A90;

void func_00f20188(void) {
    if (D_00FA6A90 != 0) {
        func_001224c8(D_00FA6A90, &D_002C5C60, &func_00122768, 30.0f);
        D_00FA6A90 = 0;
    }
}
