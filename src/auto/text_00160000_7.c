/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00267530(void *, s32, s32);
f32 PlatSqrtf(f32);
f32 func_00267390(void *, void *);

f32 func_00162978(s32 arg0, s32 arg1) {
    s32 sp[4];
    func_00267530(sp, arg0, arg1);
    return PlatSqrtf(func_00267390(sp, sp));
}
