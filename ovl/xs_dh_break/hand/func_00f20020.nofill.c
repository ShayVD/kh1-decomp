/* xs_dh_break.x func_00f20020: matched by hand. */
#include "ovl.h"

extern u32 D_00F311C0;

f32 func_00f20020(void) {
    D_00F311C0 = D_00F311C0 * 69069 + 1;
    return (f32)D_00F311C0 * 2.3283064365386963e-10f;
}
