/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

#include "data/pieces/D_002C58B0.h"
s32 func_00130340(s32, s32, f32);
s32 func_00130578(s32, s32, f32);
s32 func_002675a8(s32, s32);
void func_001373f8(s32, f32);
void func_001541a8(s32, s32, s32);
void func_00156260(s32, s32);

void func_00154548(s32 arg0, s32 arg1) {
    s32 sp[4];
    func_00130340(arg0, 0x0100006A, 0.0f);
    func_00130578(arg0, 0x4000002D, 0.0f);
    func_001373f8(arg0, 3e+01f);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), f32 *, 0xB0) = 0.0f;
    func_002675a8((s32) (M2C_FIELD(arg0, void **, 0x148) + 0xA0), (s32) ((M2C_UNK *)&D_002C58B0));
    func_001541a8(arg0, arg1, (s32) sp);
    func_00156260(arg0, (s32) sp);
}
