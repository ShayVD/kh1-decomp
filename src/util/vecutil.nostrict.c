/* Vector and angle helpers: lengths and distances (func_00120bf8,
 * func_00120c18, func_00121748), an angle wrapped to -pi..pi
 * (func_00120c88), rotation matrices from angles (func_00120cf8,
 * func_00120c38), a point through a matrix (func_00120ef0), func_00121000
 * whether eight points project inside the 4096 x 4096 screen, the closest
 * points of two lines (func_00121550), func_001213a0 (a spline's
 * derivatives, a guess), the angles of a vector (func_00121a78, asinf /
 * atan2f) and small helpers. Flag mode: nostrict (the other modes are in the
 * sibling files). Read from the code, not proved by a boot (docs/modules.md
 * "Session 54"). */
#include "common.h"
#ifndef KH1_PS2
#include "platform/math.h"
#endif
#include "platform/vu.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004E.h"
#include "data/bss_004F.h"
#include "data/types/nostrict_text_00110000_s6_04_p.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002C58B0.h"
#include "data/types/nostrict_text_00110000_s6_04.h"
#include "data/pieces/D_002C5C48.h"

/* func_00120c18 (from hand/nostrict/text_00110000_s6_04.c). */
f32 func_00120c18(f32 *v) {
    f32 r;
    f32 x = v[0] * v[0] + v[2] * v[2];
#ifdef KH1_PS2
    __asm__ volatile(".set noreorder\nsqrt.s %0, %1\n.set reorder" : "=f"(r) : "f"(x));
#else
    r = PlatSqrtf(x);
#endif
    return r;
}

/* func_001219c8 (from hand/nostrict/text_00110000_s6_04.c). */
void func_001219c8(f32 *d, f32 *a, f32 *b) {
    s32 i;
    for (i = 0; i < 3; i++) d[i] = a[i] / b[i];
}

/* func_00121a78 (from hand/nostrict/text_00110000_s6_04.c). */
f32 asinf(f32);
f32 atan2f(f32, f32);
void func_00121a78(f32 m[4][4], f32 *out) {
    f32 t[4][4];
    s32 i;
    for (i = 0; i < 3; i++) PlatVu0Normalize(t[i], m[i]);
    out[0] = atan2f(-t[1][2], t[0][2]);
    out[1] = asinf(-t[2][2]);
    out[2] = atan2f(t[2][1], t[2][0]);
}

