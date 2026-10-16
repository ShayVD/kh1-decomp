/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001224c8(s32, M2C_UNK *, M2C_UNK *, f32);
M2C_UNK func_0013c548(s32);
M2C_UNK func_00247468(void *, s32);
M2C_UNK func_002675a8(void *, s32);
extern M2C_UNK D_002C5C60;
extern M2C_UNK func_00122768;

void func_0012adf0(void *arg0) {
    func_001224c8(M2C_FIELD(arg0, s32 *, 0), &D_002C5C60, &func_00122768, M2C_FIELD(arg0, f32 *, 4));
}

void func_0012b5e8(void *arg0) {
    s32 sp[4];
    func_002675a8(sp, M2C_FIELD(arg0, s32 *, 0));
    M2C_FIELD(sp, f32 *, 0xC) = 1.0f;
    func_00247468(sp, M2C_FIELD(arg0, s32 *, 4));
    func_0013c548(M2C_FIELD(arg0, s32 *, 4));
}
