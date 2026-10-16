/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0014f658(void *, M2C_UNK);
M2C_UNK func_001528f0(void *);
M2C_UNK func_002675a8(s32);

void func_00152ba8(void *arg0, void *arg1, f32 fparg0) {
    func_002675a8(arg0 + 0x3C0);
    M2C_FIELD(arg0, f32 *, 0x3CC) = 1.0f;
    M2C_FIELD(arg0, f32 *, 0x3B4) = fparg0;
    M2C_FIELD(arg0, s32 *, 0x3B0) = 0;
    M2C_FIELD(arg0, f32 *, 0x3B8) = (f32) (-M2C_FIELD(arg1, f32 *, 4) / fparg0);
    func_0014f658(arg0, 3);
    func_001528f0(arg0);
}
