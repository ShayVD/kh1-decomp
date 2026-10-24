/* Vector and angle helpers: lengths and distances (func_00120bf8,
 * func_00120c18, func_00121748), an angle wrapped to -pi..pi
 * (func_00120c88), rotation matrices from angles (func_00120cf8,
 * func_00120c38), a point through a matrix (func_00120ef0), func_00121000
 * whether eight points project inside the 4096 x 4096 screen, the closest
 * points of two lines (func_00121550), func_001213a0 (a spline's
 * derivatives, a guess), the angles of a vector (func_00121a78, asinf /
 * atan2f) and small helpers. Flag mode: default (the other modes are in the
 * sibling files). Read from the code, not proved by a boot (docs/modules.md
 * "Session 54"). */
#include "common.h"
#include "platform/vu.h"
#include "platform/math.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/types/text_00110000_h4_p.h"
#include "m2c.h"
#include "actor.h"
#include "data/bss_004F.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004E.h"
#include "data/types/text_00110000_h30.h"
#include "data/pieces/D_002C5910.h"
#include "data/pieces/D_002BC140.h"
#include "data/types/text_00110000_h30_p.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002C5C48.h"
#include "data/types/text_00110000_h53_p.h"

/* func_00120bf8 (from hand/text_00110000_h4.c). */
f32 func_00120bf8(void *a) {
    return PlatSqrtf(PlatVu0InnerProduct(a, a));
}

/* func_00120c38 (from auto/text_00120000_3.c). */
void func_00120c38(s32 arg0, s32 arg1, void *arg2) {
    PlatVu0RotMatrixZ(arg0, arg1, M2C_FIELD(arg2, f32 *, 8));
    PlatVu0RotMatrixX(arg0, arg0, M2C_FIELD(arg2, f32 *, 0));
    PlatVu0RotMatrixY(arg0, arg0, M2C_FIELD(arg2, f32 *, 4));
}

/* func_00120c88 (from hand/text_00110000_h4.c). */
f32 func_00120c88(f32 a) {
    s32 i;
    for (i = 0; i < 1024; i++) {
        if (a > 3.1415928f) a -= 6.2831856f;
        else if (a < -3.1415928f) a += 6.2831856f;
        else break;
    }
    return a;
}

/* func_00120cf8 (from hand/text_00120000_s12_s12w13.c). */
f32 sinf(f32);
f32 cosf(f32);
void func_00120cf8(f32 *axis, f32 m[4][4], f32 angle) {
    f32 t[3][4];
    f32 s[4];
    f32 c;
    s32 i, j, n;
    for (i = 0; i < 3; i++) {
        m[i][3] = m[3][i] = 0.0f;
    }
    m[3][3] = 1.0f;
    PlatVu0ScaleVector(s, axis, sinf(angle));
    c = cosf(angle);
    for (i = 0; i < 3; i++) PlatVu0ScaleVector(t[i], axis, axis[i]);
    for (i = 0; i < 3; i++) {
        n = 3;
        for (j = 0; j < 3; j++) {
            s32 e = n;
            if (i == j) {
                m[i][j] = c;
            } else {
                s32 k = i - j + 3;
                f32 v = s[3 - i - j];
                if (k % n == 1) { m[i][j] = -v; } else { m[i][j] = v; }
            }
            n = e;
        }
    }
    c = 1.0f - c;
    for (i = 0; i < 3; i++) PlatVu0ScaleVector(t[i], t[i], c);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) m[i][j] += t[i][j];
    }
}

/* func_00120ef0 (from auto/text_00120000_5.c). */
f32 func_00120ef0(f32 *arg0, s32 arg1, void *arg2) {
    f32 *var_v0;
    f32 temp_f20;
    s32 var_v1;

    M2C_FIELD(arg2, f32 *, 0xC) = 1.0f;
    PlatVu0ApplyMatrix(arg0, arg1, arg2);
    temp_f20 = 1.0f / M2C_FIELD(arg0, f32 *, 0xC);
    var_v0 = arg0;
    var_v1 = 2;
    do {
        var_v1 -= 1;
        *var_v0 *= temp_f20;
        var_v0 += 1;
    } while (var_v1 >= 0);
    M2C_FIELD(arg0, f32 *, 0xC) = 1.0f;
    return temp_f20;
}

/* func_00120f70 (from hand/text_00110000_h4.c). */
typedef Vec4_2c5c80 Vec4;
void func_00121fc4(Vec4 *, Vec4 *);
void func_00120f70(Vec4 *pts, Vec4 *out) {
    Vec4 d[2];
    s32 i;
    for (i = 0; i < 2; i++) PlatVu0SubVector(&d[i], &pts[i + 1], &pts[i]);
    d[1].w = d[0].w = 1.0f;
    PlatVu0OuterProduct(out, &d[0], &d[1]);
    func_00121fc4(out, out);
}

/* func_00121000 (from hand/text_00110000_h30.c). */
s32 func_00121000(V4 *m, V4 *pts) {
    V4 v;
    s32 i;
    for (i = 0; i < 8; i++) {
        PlatVu0ApplyMatrix(v, m, *pts++);
        if (v[3] < 1.0f) return 0;
        v[0] /= v[3];
        v[1] /= v[3];
        if (v[0] < 0.0f || v[0] > 4095.0f || v[1] < 0.0f || v[1] > 4095.0f) return 0;
    }
    return 1;
}

/* func_001210f0 (from auto/text_00120000_2.c). */
void func_001210f0(void *arg0, void *arg1, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0) = (f32) (M2C_FIELD(arg1, f32 *, 0) * fparg0);
    M2C_FIELD(arg0, f32 *, 4) = (f32) M2C_FIELD(arg1, f32 *, 4);
    M2C_FIELD(arg0, f32 *, 8) = (f32) (M2C_FIELD(arg1, f32 *, 8) * fparg0);
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) M2C_FIELD(arg1, f32 *, 0xC);
}

/* func_00121120 (from hand/text_00110000_h4.c). */
s32 func_00121120(Vec4 *v) {
    s32 r = 0;
    if (v->z < 0.0f || PlatVu0ClipScreen(v)) r = 1;
    return r;
}

/* func_00121168 (from hand/text_00110000_h53.c). */
#define func_00121fc4 ((void (*)(V53 *, V53 *)) func_00121fc4)
s32 func_00121168(V53 *out, V53 *a, V53 *b, f32 t) {
    V53 q, d1, d2, x, y;
    PlatVu0SubVector(&d1, &a[1], &a[0]);
    PlatVu0SubVector(&d2, &b[1], &b[0]);
    PlatVu0ScaleVector(&x, &d1, ((b->y - a->y) + d2.y * (b->x - a->x)) / (d2.x * d1.y - d2.y * d1.x));
    PlatVu0AddVector(&x, &x, a);
    PlatVu0SubVector(&d1, a, &x);
    func_00121fc4(&d1, &d1);
    PlatVu0SubVector(&d2, b, &x);
    func_00121fc4(&d2, &d2);
    PlatVu0InterVector(&q, &d2, &d1, t);
    PlatVu0Normalize(&q, &q);
    PlatVu0ScaleVector(&y, &q, d1.w + (d2.w - d1.w) * t);
    PlatVu0AddVector(&out[0], &x, &y);
    out[0].w = 1.0f;
    PlatVu0SubVector(&d1, &a[1], &x);
    func_00121fc4(&d1, &d1);
    PlatVu0SubVector(&d2, &b[1], &x);
    func_00121fc4(&d2, &d2);
    PlatVu0InterVector(&q, &d2, &d1, t);
    PlatVu0Normalize(&q, &q);
    PlatVu0ScaleVector(&y, &q, d1.w + (d2.w - d1.w) * t);
    PlatVu0AddVector(&out[1], &x, &y);
    out[1].w = 1.0f;
    return 1;
}
#undef func_00121fc4

/* func_001213a0 (from hand/text_00110000_h30.c). */
void func_001213a0(f32 *y, s32 n, f32 *d) {
    f32 h[32];
    s32 i;
    d[0] = d[n - 1] = 0.0f;
    for (i = 0; i < n - 1; i++) h[i + 1] = y[i + 1] - y[i];
    d[1] = h[2] - h[1] - d[0];
    h[1] = 4.0f;
    for (i = 1; i < n - 2; i++) {
        f32 t = 1.0f / h[i];
        d[i + 1] = h[i + 2] - h[i + 1] - d[i] * t;
        h[i + 1] = 4.0f - t;
    }
    d[n - 2] -= d[n - 1];
    for (i = n - 2; i > 0; i--) d[i] = (d[i] - d[i + 1]) / h[i];
}

/* func_001214e0 (from hand/text_00110000_h4.c). */
f32 func_001214e0(f32 *a, f32 *b, f32 t) {
    s32 i = (s32)t;
    f32 f = t - (f32)i;
    return ((((b[i + 1] - b[i]) * f + b[i] * 3.0f) * f + ((a[i + 1] - a[i]) - (b[i] * 2.0f + b[i + 1]))) * f) + a[i];
}

/* func_00121620 (from hand/text_00110000_h4.c). */
void func_00121620(Vec4 *m, void *a1, f32 x, f32 y, f32 z, f32 w) {
    PlatVu0DropShadowMatrix(m, a1, x, y, z, 0);
    PlatVu0ScaleVectorXYZ(&m[3], &m[3], w);
}

/* func_00121668 (from hand/text_00110000_h4.c). */
void func_00121668(f32 d[4][4], f32 s[4][4]) {
    d[0][0] = s[0][0]; d[0][1] = s[1][0]; d[0][2] = s[2][0]; d[0][3] = 0.0f;
    d[1][0] = s[0][1]; d[1][1] = s[1][1]; d[1][2] = s[2][1]; d[1][3] = 0.0f;
    d[2][0] = s[0][2]; d[2][1] = s[1][2]; d[2][2] = s[2][2]; d[2][3] = 0.0f;
    d[3][0] = 0.0f; d[3][1] = 0.0f; d[3][2] = 0.0f; d[3][3] = 1.0f;
}

/* func_001216d8 (from hand/text_00110000_h4.c). */
extern f32 D_002BBDFC;
f32 func_001216d8(f32 a, f32 b, f32 c) {
    f32 d = func_00120c88(b - a);
    c *= D_002BBDFC;
    if (d > c) d = c;
    else if (d < -c) d = -c;
    return func_00120c88(a + d);
}

/* func_00121748 (from hand/text_00110000_h30.c). */
#define func_00120bf8 ((f32 (*)(f32 *)) func_00120bf8)
f32 func_00121748(f32 *a, f32 *b) {
    if (PlatVu0InnerProduct(a, b) / (func_00120bf8(a) * func_00120bf8(b)) < -1.0f) return -1.0f;
    if (PlatVu0InnerProduct(a, b) / (func_00120bf8(a) * func_00120bf8(b)) > 1.0f) return 1.0f;
    return PlatVu0InnerProduct(a, b) / (func_00120bf8(a) * func_00120bf8(b));
}
#undef func_00120bf8

/* func_00121840 (from auto/text_00120000.c). */
f32 func_0026b978(f32);
#define func_00121748 ((f32 (*)()) func_00121748)
f32 func_00121840(f32 *a, f32 *b) {
    return func_0026b978(func_00121748(a, b));
}
#undef func_00121748

/* func_00121860 (from hand/text_00110000_h30.c). */
#define func_00121840 ((f32 (*)(f32 *, f32 *)) func_00121840)
#define func_00120cf8 ((void (*)(f32 *, V4 *, f32)) func_00120cf8)
void func_00121860(f32 *from, f32 *to, f32 *out, f32 rate) {
    V4 a, b, ax;
    V4 m[4];
    f32 ang, lim;
    PlatVu0Normalize(a, from);
    PlatVu0Normalize(b, to);
    PlatVu0OuterProduct(ax, a, b);
    PlatVu0Normalize(ax, ax);
    ang = func_00121840(a, b);
    rate *= D_002BBDFC;
    if (rate < ang) ang = rate;
    else if (ang < -rate) ang = -rate;
    func_00120cf8(ax, m, ang);
    PlatVu0CopyVector(out, a);
    out[3] = 0;
    PlatVu0ApplyMatrix(out, m, out);
}
#undef func_00121840
#undef func_00120cf8

/* func_00121958 (from hand/text_00110000_h4.c). */
void func_00121958(Vec4 *d, Vec4 *s, f32 *k) {
    s32 i;
    for (i = 0; i < 3; i++) PlatVu0ScaleVectorXYZ(&d[i], &s[i], *k++);
}

/* func_00121a10 (from auto/text_00120000_2.c). */
f32 func_00120c18();
f32 func_0026b9a8(f32, f32);
void func_00121a10(void *arg0, void *arg1) {
    f32 temp_f0;

    M2C_FIELD(arg1, f32 *, 0) = func_0026b9a8(-M2C_FIELD(arg0, f32 *, 4), func_00120c18(arg0));
    temp_f0 = func_0026b9a8(M2C_FIELD(arg0, f32 *, 0), M2C_FIELD(arg0, f32 *, 8));
    M2C_FIELD(arg1, s32 *, 8) = 0;
    M2C_FIELD(arg1, f32 *, 4) = temp_f0;
    M2C_FIELD(arg1, f32 *, 0xC) = 1.0f;
}

/* func_00121b08 (from auto/text_00120000.c). */
f32 func_00121b08(f32 fparg0) {
    f32 var_f12;

    var_f12 = fparg0;
    if (var_f12 > 0.0f) {
        var_f12 -= D_002BBDFC;
        if (var_f12 < 0.0f) {
            var_f12 = 0.0f;
        }
    }
    return var_f12;
}

/* func_00121b38 (from auto/text_00120000_8.c). */
#define func_00121748 ((f32 (*)(M2C_UNK *, M2C_UNK *)) func_00121748)
f32 func_00121b38(s32 arg0, s32 arg1) {
    s32 sp[8];
    PlatVu0CopyVector(sp, arg0);
    PlatVu0CopyVector(&M2C_FIELD(sp, M2C_UNK *, 0x10), arg1);
    M2C_FIELD(sp, s32 *, 0x4) = 0;
    M2C_FIELD(sp, s32 *, 0x14) = 0;
    return func_00121748(sp, &M2C_FIELD(sp, M2C_UNK *, 0x10));
}
#undef func_00121748

