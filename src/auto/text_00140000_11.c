/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
M2C_UNK func_001376e8();
M2C_UNK func_002675a8(s32, void *);
M2C_UNK func_00267e90(s32, void *, f32);
extern f32 D_002BBDFC;

void func_0014f6f8(s32 arg0, void *arg1) {
    if (M2C_FIELD(arg1, f32 *, 0xC) > 0.0f) {
        func_001376e8();
    }
    func_002675a8(arg0 + 0x20, arg1);
}

void func_0014f748(void *arg0, s32 arg1) {
    func_00267e90(arg1, arg0 + 0x20, M2C_FIELD(arg0, f32 *, 0x2C) * D_002BBDFC);
}
#include "data/pieces/D_002BBDFC.h"
