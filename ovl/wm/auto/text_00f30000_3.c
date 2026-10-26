/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00F9A540;
extern s32 D_00FDF7D0;
void func_00f3bbc0();
void sceVu0UnitMatrix(M2C_UNK *);

void func_00f3cac8(void) {
    sceVu0UnitMatrix(&D_00F9A540);
    D_00FDF7D0 = 0;
    func_00f3bbc0();
}
