/* gb.x func_00f365b8: matched by hand. */
#include "ovl.h"

u64 *func_00f36470(f32 *v0, f32 *v1, u64 tag, f32 (*m)[4], u64 *p);

typedef union { kh1_u128 q; u32 w[4]; } H5d6b0;

u64 *func_00f365b8(s32 x, s32 y, s32 z, u64 tag, f32 (*m)[4], u64 *p) {
    f32 a[4];
    f32 b[4];
    f32 fx, fy, fz;
    u64 *q;
    H5d6b0 *h;
    s32 i, j, k, n;

    fx = x * 200.0f;
    fy = y * 200.0f;
    fz = z * 200.0f;
    a[3] = 1.0f;
    b[3] = 1.0f;
    n = 0;
    h = (H5d6b0 *)p;
    p += 2;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 2; k++) {
                f32 ax = k ? fx : 0.0f;
                f32 ay = i ? fy : 0.0f;
                f32 az = j ? fz : 0.0f;
                f32 bx = k ? ax + -100.0f : ax + 100.0f;
                f32 by = i ? ay + -100.0f : ay + 100.0f;
                f32 bz = j ? az + -100.0f : az + 100.0f;
                a[0] = ax;
                a[1] = ay;
                a[2] = az;
                b[0] = bx;
                b[1] = ay;
                b[2] = az;
                p = func_00f36470(a, b, tag, m, p);
                n++;
                b[0] = ax;
                b[1] = by;
                p = func_00f36470(a, b, tag, m, p);
                n++;
                b[1] = ay;
                b[2] = bz;
                p = func_00f36470(a, b, tag, m, p);
                n++;
            }
        }
    }
    h->q = 0;
    h->w[3] = 0;
    h->w[2] = 1102;
    h->w[1] = 0x3020C000;
    h->w[0] = n | 0x8000;
    return p;
}
