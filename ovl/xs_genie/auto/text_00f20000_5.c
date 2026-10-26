/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00f21ab0(M2C_UNK, s32, f32);
M2C_UNK sceVu0CopyVector(s32, s32);
extern s32 D_00F22E98;
s32 *func_00147c98(s32, M2C_UNK, M2C_UNK);

void func_00f221e0(s32 arg0) {
    sceVu0CopyVector(*func_00147c98(D_00F22E98, 0xE, 0x4E20), arg0);
    func_00f21ab0(5, arg0, 100.0f);
}
