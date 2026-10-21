/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern f32 D_002BBDFC;
void func_0014f658(s32, s32);
void func_002675a8(s32, s32);

void func_0015d7b8(s32 arg0, s32 arg1) {
    func_0014f658(arg0, 0);
    func_002675a8(arg0 + 0x20, M2C_FIELD(arg0, s32 *, 0x148) + 0xC0);
    M2C_FIELD(arg0, f32 *, 0x2C) = (f32) (((M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x134), void **, 0x10), f32 *, 0xC) - 25.0f) + 5.0f) / D_002BBDFC);
    func_002675a8(arg1, M2C_FIELD(arg0, s32 *, 0x148) + 0xC0);
}
#include "data/pieces/D_002BBDFC.h"
