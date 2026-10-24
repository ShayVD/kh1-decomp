/* Vector and angle helpers: lengths and distances (func_00120bf8,
 * func_00120c18, func_00121748), an angle wrapped to -pi..pi
 * (func_00120c88), rotation matrices from angles (func_00120cf8,
 * func_00120c38), a point through a matrix (func_00120ef0), func_00121000
 * whether eight points project inside the 4096 x 4096 screen, the closest
 * points of two lines (func_00121550), func_001213a0 (a spline's
 * derivatives, a guess), the angles of a vector (func_00121a78, asinf /
 * atan2f) and small helpers. Flag mode: nofill (the other modes are in the
 * sibling files). Read from the code, not proved by a boot (docs/modules.md
 * "Session 54"). */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_002C5968.h"
#include "data/pieces/D_002C5910.h"
#include "data/pieces/D_002E26A0.h"

/* func_00121550 (from hand/nofill/text_00110000_h30.c). */
double nan();
f32 func_00121550(f32 *out, f32 *p0, f32 *d0, f32 *p1, f32 *d1) {
    f32 a = d1[0];
    f32 b = d1[2];
    f32 den = d0[2] * a - b * d0[0];
    f32 t;
    if (den == 0.0f) return nan();
    t = (a * (p1[2] - p0[2]) + b * (p0[0] - p1[0])) / den;
    PlatVu0ScaleVector(out, d0, t);
    PlatVu0AddVector(out, out, p0);
    return t;
}

