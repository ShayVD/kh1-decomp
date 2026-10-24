/* Matrix and vector helpers of the model code, default flags
 * (docs/modules.md "Session 52"): func_00162978, func_001629b0.  The VU0
 * routines between them stay in src/hand/vu0.c.  Read from the code, not proved by a boot. */
#include "m2c.h"

/* func_00162978 (from auto/text_00160000_7.c). */
M2C_UNK func_00267530(void *, s32, s32);
f32 PlatSqrtf(f32);
f32 func_00267390(void *, void *);
f32 func_00162978(s32 arg0, s32 arg1) {
    s32 sp[4];
    func_00267530(sp, arg0, arg1);
    return PlatSqrtf(func_00267390(sp, sp));
}

/* func_001629b0 (from auto/text_00160000_5.c). */
#define func_00267390 ((M2C_UNK (*)(void *, void *)) func_00267390)
void func_001629b0(s32 arg0, s32 arg1) {
    s32 sp[4];
    func_00267530(sp, arg0, arg1);
    func_00267390(sp, sp);
}
#undef func_00267390

