/* gb.x func_00f3bfc8: matched by hand. */
#include "ovl.h"

void func_00f3bda8(f32, f32 *, void *);
f32 func_00f3bf80(f32 *, f32 *);

f32 func_00f3bfc8(void *c, f32 t0, f32 len) {
    OvlVec p0;
    OvlVec p1;
    OvlVec a;
    OvlVec b;
    f32 t, step, acc, tt, len2;
    s32 i;
    len2 = len * len;
    t = t0 + len * 0.01f;
    step = len * 0.01 * 0.1f;
    func_00f3bda8(t0, p0, c);
    for (;;) {
        func_00f3bda8(t, p1, c);
        if (len2 < func_00f3bf80(p0, p1))
            break;
        t += step;
    }
    b[0] = p0[0];
    b[1] = p0[1];
    b[2] = p0[2];
    b[3] = 1.0f;
    acc = 0.0f;
    i = 1;
    while (1) {
        if (i >= 257)
            break;
        tt = (t - t0) * i * (1.0f / 256) + t0;
        i++;
        func_00f3bda8(tt, a, c);
        acc += func_00f3bf80(b, a);
        if (len2 < acc)
            break;
        b[0] = a[0];
        b[1] = a[1];
        b[2] = a[2];
    }
    return tt;
}
