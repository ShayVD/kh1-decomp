/* xs_dumbo.x func_00f21ef0: matched by hand. */
#include "ovl.h"

f32 cosf(f32);
f32 sinf(f32);
void func_00f21ef0(OvlVec *p, s32 n, s32 m, f32 r0, f32 r1, f32 h) {
    s32 i, j;
    f32 ang, a, c, s;
    f32 y, r;
    f32 dh, dr, d;
    ang = 6.28318500518798828125 / n;
    y = 0.0f;
    d = r1 - r0;
    r = r0;
    dr = d / m;
    dh = h / m;
    for (j = 0; j <= m; j++) {
        for (i = 0; i < n; i++) {
            a = i * ang;
            c = cosf(a);
            s = sinf(a);
            (*p)[2] = y;
            (*p)[3] = 1.0f;
            (*p)[0] = c * r;
            (*p)[1] = s * r;
            p++;
        }
        y += dh;
        r += dr;
    }
}
