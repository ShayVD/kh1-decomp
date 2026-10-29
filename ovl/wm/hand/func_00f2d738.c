/* wm.x func_00f2d738: matched by hand. */
#include "ovl.h"

#include "platform/math.h"
void sceVu0Normalize(f32 *, f32 *);
void sceVu0OuterProduct(f32 *, f32 *, f32 *);
f32 sceVu0InnerProduct(f32 *, f32 *);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
f32 acosf(f32);
void func_001bf290(f32 *);
void func_001bf698(f32 *, f32 *, f32);
void func_001bf3e8(f32 (*)[4], f32 *);

f32 func_00f2d738(f32 (*m)[4], f32 *t, f32 lim, f32 spd, f32 unused) {
    f32 r[4][4];
    f32 d[4];
    f32 z[4];
    f32 c[4];
    f32 q[4];
    f32 dist;
    f32 cs;
    f32 a;

    d[0] = t[0] - m[3][0];
    d[1] = t[1] - m[3][1];
    d[2] = t[2] - m[3][2];
    d[3] = 1.0f;
    dist = PlatSqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
    sceVu0Normalize(d, d);
    z[0] = m[2][0];
    z[1] = m[2][1];
    z[2] = m[2][2];
    z[3] = 1.0f;
    sceVu0Normalize(z, z);
    sceVu0OuterProduct(c, z, d);
    sceVu0Normalize(c, c);
    cs = sceVu0InnerProduct(z, d) / PlatSqrtf((d[0] * d[0] + d[1] * d[1] + d[2] * d[2]) * (z[0] * z[0] + z[1] * z[1] + z[2] * z[2]));
    if (cs > 0.999f && cs < 1.001f) goto end;
    if (cs < -0.999f && cs > -1.001f) goto end;
    if (cs > -0.001f && cs < 0.001f) {
        a = 1.5707963f;
    } else {
        a = acosf(cs);
    }
    while (a > 3.141592503f) {
        a -= 6.283185006f;
    }
    while (a < -3.141592503f) {
        a += 6.283185006f;
    }
    if (a < 0.0f) {
        if (a < -lim) {
            a = -lim;
        }
    } else {
        if (lim < a) {
            a = lim;
        }
    }
    func_001bf290(q);
    func_001bf698(q, c, a);
    func_001bf3e8(r, q);
    z[0] = m[3][0];
    z[1] = m[3][1];
    z[2] = m[3][2];
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    sceVu0MulMatrix(m, r, m);
    m[3][0] = z[0];
    m[3][1] = z[1];
    m[3][2] = z[2];
end:
    if (dist > 5000.0f) {
        return spd;
    }
    return spd - spd * 0.8f * (5000.0f - dist) / 5000.0f;
}
