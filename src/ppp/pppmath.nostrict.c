/* atan2 for ppp, -fno-strict-aliasing (docs/modules.md "Session 49"):
 * func_001a8d88 writes the angle of (v[0], v[1]) to *out and returns 0 for
 * the zero vector.  Nothing calls it directly (a class table entry or
 * unused).  Read from the code, not proved by a boot. */
#include "common.h"

double atan(double);

s32 func_001a8d88(f32 *v, f32 *out) {
    f32 x = v[0];
    f32 y = v[1];
    f32 r = x * y;

    if (0.0f < r) {
        r = 0.0f;
        if (!(0.0f < x))
            r = -3.1415926f;
        r = r + atan(y / x);
    } else if (r < 0.0f) {
        r = 1.5707963f;
        if (!(0.0f < y))
            r = -1.5707963f;
        r = r - atan(x / y);
    } else if (x != 0.0f) {
        r = 0.0f < x ? 0.0f : 3.1415926f;
    } else {
        if (y == 0.0f)
            return 0;
        r = !(0.0f < y) ? -1.5707963f : 1.5707963f;
    }
    *out = r;
    return 1;
}
