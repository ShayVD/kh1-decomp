/* Matrix and vector helpers of the model code, default flags
 * (docs/modules.md "Session 52"): func_00162978, func_001629b0.  The VU0
 * routines between them stay in src/hand/vu0.c.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "platform/vu.h"

/* func_00162978 (from auto/text_00160000_7.c). */
f32 PlatSqrtf(f32);
f32 func_00162978(s32 arg0, s32 arg1) {
    s32 sp[4];
    PlatVu0SubVector(sp, arg0, arg1);
    return PlatSqrtf(PlatVu0InnerProduct(sp, sp));
}

/* func_001629b0 (from auto/text_00160000_5.c). */
f32 func_001629b0(s32 arg0, s32 arg1) {
    s32 sp[4];
    PlatVu0SubVector(sp, arg0, arg1);
    return PlatVu0InnerProduct(sp, sp);
}

