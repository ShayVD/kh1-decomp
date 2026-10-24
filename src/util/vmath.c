/* Small maths and memory helpers (docs/modules.md "Session 48"),
 * 0x001be758-0x001bfac8, after the Gummi ship code and before the task
 * slots (src/util/task.c):
 *
 * - a 16-deep stack of 128-bit words with a handler per level
 *   (func_001be758 push, func_001be798 pop, func_001be7d8 calls the top
 *   handler with the top word), an align-up func_001be800 and the memory
 *   clear func_001be820(p, n) (bytes up to an 8-byte boundary, then
 *   doublewords) that the game calls everywhere;
 * - matrices: func_001be8a8 a camera matrix from three points turned by
 *   Euler angles (rot[0..2] about x, y, z), func_001bebd0 a model's four
 *   matrices, func_001becb8 a frame whose z axis is a direction,
 *   func_001bf0e8 the position and Euler angles of a matrix;
 *   vectors: the lerp func_001be988 (num / den), the angle wraps
 *   func_001be9f0 / func_001bea58, normalise func_001bedd0, the distance
 *   func_001bee80 and its square func_001beef8;
 * - two string copies (func_001bef40 joins two, func_001bef98 copies one)
 *   and func_001befc8, a linear key interpolation over {t, v} pairs ended by
 *   t < 0;
 * - quaternions (x, y, z, w): identity func_001bf290, product func_001bf2b0,
 *   inverse func_001bf360, to a matrix (func_001bf3e8 into a 4x4,
 *   func_001bf548 into a 3x3 of a 4x4), from an axis and an angle
 *   func_001bf698, slerp func_001bf710 and from a matrix func_001bf888;
 *   func_001bf048 / func_001bf098 copy a matrix and its 3x3.
 *
 * The libvu0 calls use their names (docs/sdk.md "Session 45").  Read from
 * the code, not proved by a boot. */
#include "common.h"
#include "data/types/shared.h"
#include "data/types/fvec.h"
#include "m2c.h"

typedef FVec4 V4;
typedef f32 Mtx[4][4];
typedef union { u128 q; u8 c[16]; } Q16;
typedef struct {
    Q16 q[16];      /* 0x000 */
    s32 val[16];    /* 0x100: each level's handler */
    s32 cur;        /* 0x140: the top level's handler */
    Q16 *top;       /* 0x144 */
    s32 n;          /* 0x148 */
} QStack;
typedef struct { s32 t; f32 v; } Key;
typedef struct { f32 v[4][4]; f32 pos[4]; f32 rot[4]; } Xf;
typedef struct { f32 x, y, z, w; } Q;

double asin(double);
double cos(double);
double atan2(double, double);
f32 acosf(f32);
f32 sinf(f32);
f32 sqrtf(f32);
f32 cosf(f32);
void sceVu0ApplyMatrix(f32 *, Mtx, f32 *);
void sceVu0UnitMatrix(Mtx);
void sceVu0MulMatrix(Mtx, Mtx, Mtx);
void sceVu0CopyMatrix(Mtx, Mtx);
void sceVu0TransMatrix(Mtx, Mtx, f32 *);
void sceVu0RotMatrix(Mtx, Mtx, f32 *);
void sceVu0RotMatrixX(Mtx, Mtx, f32);
void sceVu0RotMatrixY(Mtx, Mtx, f32);
void sceVu0RotMatrixZ(Mtx, Mtx, f32);
void sceVu0CameraMatrix(Mtx, f32 *, f32 *, f32 *);
void func_001be8a8(Mtx, f32 *, f32 *, f32 *, f32 *);
void func_001bf290(f32 *q);

void func_001be758(QStack *s, s32 v, u128 q) {
    s32 i = s->n;
    s->val[i] = v;
    s->q[i].q = q;
    s->cur = v;
    s->top = &s->q[s->n];
    s->n++;
}

void func_001be798(QStack *s, u128 q) {
    s->n--;
    s->q[s->n - 1].q = q;
    s->top = &s->q[s->n - 1];
    s->cur = s->val[s->n - 1];
}

void func_001be7d8(QStack *s) {
    ((void (*)(Q16 *))s->cur)(s->top);
}

s32 func_001be800(u32 arg0, u32 arg1) {
    return arg0 + (arg1 - (arg0 % arg1));
}

void func_001be820(u8 *p, u32 n) {
    u32 i;
    for (i = (u32)p & 7; i != 0; i--) {
        *p++ = 0;
        n--;
    }
    while (n >= 8) {
        *(u64 *)p = 0;
        n -= 8;
        p += 8;
    }
    while (n != 0) {
        *p++ = 0;
        n--;
    }
}

void func_001be8a8(Mtx m, f32 *pos, f32 *zd, f32 *yd, f32 *rot) {
    struct { Mtx r; f32 z[4]; f32 y[4]; f32 p[4]; } t;
    sceVu0UnitMatrix(t.r);
    sceVu0RotMatrixX(t.r, t.r, rot[0]);
    sceVu0RotMatrixY(t.r, t.r, rot[1]);
    sceVu0RotMatrixZ(t.r, t.r, rot[2]);
    sceVu0ApplyMatrix(t.z, t.r, zd);
    sceVu0ApplyMatrix(t.y, t.r, yd);
    sceVu0ApplyMatrix(t.p, t.r, pos);
    sceVu0CameraMatrix(m, t.p, t.z, t.y);
}

void func_001be988(f32 *out, f32 *a, f32 *b, s32 num, s32 den) {
    f32 t = (f32)num / (f32)den;
    s32 i;
    for (i = 0; i < 4; i++) out[i] = (b[i] - a[i]) * t + a[i];
}

void func_001be9f0(f32 *arg0) {
    f32 *var_a0;
    f32 temp_f0;
    f32 var_f1;
    s32 var_v0;

    var_a0 = arg0;
    var_v0 = 3;
    do {
        var_f1 = *var_a0;
        if (var_f1 < -3.141592503f) {
            temp_f0 = var_f1 + 6.28318501f;
            *var_a0 = temp_f0;
            var_f1 = temp_f0;
        }
        var_v0 -= 1;
        if (var_f1 > 3.141592503f) {
            *var_a0 = var_f1 - 6.28318501f;
        }
        var_a0 += 1;
    } while (var_v0 >= 0);
}

void func_001bea58(f32 *a, f32 *b) {
    s32 i;
    for (i = 0; i < 4; i++) {
        f32 x = a[i], y = b[i];
        f32 xa = x, ya = y;
        double d;
        f32 d1;
        if (x < 0.0f) xa = x + 6.2831850051879883f;
        if (y < 0.0f) ya = y + 6.2831850051879883f;
        d = ya - xa;
        if (d < 0.0) d = 0.0 - d;
        d1 = d;
        d = y - x;
        if (d < 0.0) d = 0.0 - d;
        if (d1 < (f32)d) { a[i] = xa; b[i] = ya; }
        else { a[i] = x; b[i] = y; }
    }
}

void func_001bebd0(Mtx *o, Xf *x, Mtx *p) {
    Mtx t, r, s;
    sceVu0UnitMatrix(t);
    sceVu0RotMatrix(r, t, x->rot);
    sceVu0MulMatrix(o[1], p[1], r);
    sceVu0TransMatrix(t, t, x->pos);
    sceVu0MulMatrix(r, r, t);
    func_001be8a8(s, x->v[0], x->v[1], x->v[2], x->v[3]);
    sceVu0MulMatrix(o[2], s, r);
    sceVu0MulMatrix(o[3], p[0], o[2]);
    sceVu0CopyMatrix(o[0], p[2]);
}

void func_001becb8(f32 (*m)[4], f32 *v, s32 neg) {
    f32 ny, l, a, b;
    if (neg) {
        v[0] = -v[0];
        v[1] = -v[1];
        v[2] = -v[2];
    }
    ny = -v[1];
    l = sqrtf(1.0f - v[1] * v[1]);
    a = v[0] / l;
    b = v[2] / l;
    m[1][1] = l;
    m[0][1] = 0;
    m[0][3] = 0;
    m[1][3] = 0;
    m[0][2] = -a;
    m[1][0] = a * ny;
    m[0][0] = b;
    m[1][2] = b * ny;
    m[2][0] = v[0];
    m[2][1] = v[1];
    m[2][2] = v[2];
    m[3][3] = 1.0f;
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[2][3] = 0;
}

f32 func_001bedd0(f32 *v) {
    f32 l = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if (l == 0.0f) return l;
    v[0] /= l;
    v[1] /= l;
    v[2] /= l;
    return l;
}

f32 func_001bee80(f32 *a, f32 *b) {
    f32 d[3];
    d[0] = a[0] - b[0];
    d[1] = a[1] - b[1];
    d[2] = a[2] - b[2];
    return sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
}

f32 func_001beef8(void *arg0, void *arg1) {
  f32 temp_f0;
  f32 new_var[2];
  temp_f0 = (*((f32 *) (0 + ((s8 *) arg0)))) - (*((f32 *) (((s8 *) arg1) + 0)));
  new_var[0] = (*((f32 *) (((s8 *) arg0) + 4))) - (*((f32 *) (((s8 *) arg1) + 4)));
  new_var[1] = (*((f32 *) (((s8 *) arg0) + 8))) - (*((f32 *) (((s8 *) arg1) + 8)));
  return ((temp_f0 * temp_f0) + (new_var[0] * new_var[0])) + (new_var[1] * new_var[1]);
}

void func_001bef40(char *d, char *s, char *t) {
    while (*s) *d++ = *s++;
    while (*t) *d++ = *t++;
    *d = 0;
}

void func_001bef98(char *d, char *s) {
    while (*s) *d++ = *s++;
    *d = 0;
}

f32 func_001befc8(s32 t, Key *k) {
    s32 pt = 0;
    f32 pv = 0.0f;
    for (; k->t >= 0; k++) {
        if (t == k->t) return k->v;
        if (t < k->t) return (k->v - pv) * ((f32)(t - pt) / (f32)(k->t - pt)) + pv;
        pv = k->v;
        pt = k->t;
    }
    return 0.0f;
}

void func_001bf048(Mtx d, Mtx s) {
    if (d != s) {
        sceVu0CopyMatrix(d, s);
    }
    d[3][3] = 1.0f;
    d[1][3] = 0.0f;
    d[2][3] = 0.0f;
    d[3][0] = 0.0f;
    d[3][1] = 0.0f;
    d[3][2] = 0.0f;
    d[0][3] = 0.0f;
}

void func_001bf098(Mtx d, Mtx s) {
    d[0][0] = s[0][0];
    d[0][1] = s[0][1];
    d[0][2] = s[0][2];
    d[1][0] = s[1][0];
    d[1][1] = s[1][1];
    d[1][2] = s[1][2];
    d[2][0] = s[2][0];
    d[2][1] = s[2][1];
    d[2][2] = s[2][2];
}

void func_001bf0e8(V4 *pos, V4 *rot, f32 *m) {
    f32 rx, ry, rz = 0.0f, c;
    pos->x = m[12];
    pos->y = m[13];
    pos->z = m[14];
    pos->w = 1.0f;
    ry = -asin(m[2]);
    c = cos(ry);
    if (c > -0.0009999999310821295f && c < 0.0009999999310821295f) {
        rx = rz;
        rz = acosf(m[5]);
    } else {
        rx = atan2(m[6], m[10]);
        rz = asin(m[1] / c);
        if (m[0] < 0.0f) rz = 3.1415925621986389f - rz;
    }
    rot->x = rx;
    rot->y = ry;
    rot->z = rz;
    rot->w = 1.0f;
}

void func_001bf290(f32 *q) {
    q[3] = 1.0f;
    q[1] = 0.0f;
    q[2] = 0.0f;
    q[0] = 0.0f;
}

void func_001bf2b0(Q *d, Q *a, Q *b) {
    Q r;
    r.x = a->w * b->x + b->w * a->x + (a->y * b->z - a->z * b->y);
    r.y = a->w * b->y + b->w * a->y + (a->z * b->x - a->x * b->z);
    r.z = a->w * b->z + b->w * a->z + (a->x * b->y - a->y * b->x);
    r.w = a->w * b->w - (a->x * b->x + a->y * b->y + a->z * b->z);
    d->x = r.x;
    d->y = r.y;
    d->z = r.z;
    d->w = r.w;
}

void func_001bf360(void *arg0, void *arg1) {
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f3;

    temp_f1 = M2C_FIELD(arg1, f32 *, 0);
    temp_f2 = M2C_FIELD(arg1, f32 *, 0xC);
    temp_f3 = M2C_FIELD(arg1, f32 *, 4);
    temp_f0 = M2C_FIELD(arg1, f32 *, 8);
    temp_f2_2 = (temp_f2 * temp_f2) + (temp_f1 * temp_f1) + (temp_f3 * temp_f3) + (temp_f0 * temp_f0);
    M2C_FIELD(arg0, f32 *, 0) = (f32) (-temp_f1 / temp_f2_2);
    M2C_FIELD(arg0, f32 *, 4) = (f32) (-M2C_FIELD(arg1, f32 *, 4) / temp_f2_2);
    M2C_FIELD(arg0, f32 *, 8) = (f32) (-M2C_FIELD(arg1, f32 *, 8) / temp_f2_2);
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) (M2C_FIELD(arg1, f32 *, 0xC) / temp_f2_2);
}

void func_001bf3e8(f32 m[4][4], V4 *q) {
    m[0][0] = 1.0f - 2.0f * (q->y * q->y + q->z * q->z);
    m[1][0] = 2.0f * (q->x * q->y - q->w * q->z);
    m[2][0] = 2.0f * (q->x * q->z + q->w * q->y);
    m[3][0] = 0.0f;
    m[0][1] = 2.0f * (q->x * q->y + q->w * q->z);
    m[1][1] = 1.0f - 2.0f * (q->x * q->x + q->z * q->z);
    m[2][1] = 2.0f * (q->y * q->z - q->w * q->x);
    m[3][1] = 0.0f;
    m[0][2] = 2.0f * (q->x * q->z - q->w * q->y);
    m[1][2] = 2.0f * (q->y * q->z + q->w * q->x);
    m[2][2] = 1.0f - 2.0f * (q->x * q->x + q->y * q->y);
    m[3][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;
}

void func_001bf548(void *arg0, void *arg1) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f2;

    temp_f0 = M2C_FIELD(arg1, f32 *, 4);
    temp_f1 = M2C_FIELD(arg1, f32 *, 8);
    M2C_FIELD(arg0, f32 *, 0) = (f32) (1.0f - (2.0f * ((temp_f0 * temp_f0) + (temp_f1 * temp_f1))));
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) (2.0f * ((M2C_FIELD(arg1, f32 *, 0) * M2C_FIELD(arg1, f32 *, 4)) - (M2C_FIELD(arg1, f32 *, 0xC) * M2C_FIELD(arg1, f32 *, 8))));
    M2C_FIELD(arg0, f32 *, 0x20) = (f32) (2.0f * ((M2C_FIELD(arg1, f32 *, 0) * M2C_FIELD(arg1, f32 *, 8)) + (M2C_FIELD(arg1, f32 *, 0xC) * M2C_FIELD(arg1, f32 *, 4))));
    M2C_FIELD(arg0, f32 *, 4) = (f32) (2.0f * ((M2C_FIELD(arg1, f32 *, 0) * M2C_FIELD(arg1, f32 *, 4)) + (M2C_FIELD(arg1, f32 *, 0xC) * M2C_FIELD(arg1, f32 *, 8))));
    temp_f0_2 = M2C_FIELD(arg1, f32 *, 0);
    temp_f1_2 = M2C_FIELD(arg1, f32 *, 8);
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) (1.0f - (2.0f * ((temp_f0_2 * temp_f0_2) + (temp_f1_2 * temp_f1_2))));
    M2C_FIELD(arg0, f32 *, 0x24) = (f32) (2.0f * ((M2C_FIELD(arg1, f32 *, 4) * M2C_FIELD(arg1, f32 *, 8)) - (M2C_FIELD(arg1, f32 *, 0xC) * M2C_FIELD(arg1, f32 *, 0))));
    M2C_FIELD(arg0, f32 *, 8) = (f32) (2.0f * ((M2C_FIELD(arg1, f32 *, 0) * M2C_FIELD(arg1, f32 *, 8)) - (M2C_FIELD(arg1, f32 *, 0xC) * M2C_FIELD(arg1, f32 *, 4))));
    M2C_FIELD(arg0, f32 *, 0x18) = (f32) (2.0f * ((M2C_FIELD(arg1, f32 *, 4) * M2C_FIELD(arg1, f32 *, 8)) + (M2C_FIELD(arg1, f32 *, 0xC) * M2C_FIELD(arg1, f32 *, 0))));
    temp_f0_3 = M2C_FIELD(arg1, f32 *, 0);
    temp_f2 = M2C_FIELD(arg1, f32 *, 4);
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, f32 *, 0x28) = (f32) (1.0f - (2.0f * ((temp_f0_3 * temp_f0_3) + (temp_f2 * temp_f2))));
}

void func_001bf698(void *arg0, void *arg1, f32 fparg0) {
    f32 temp_f0;
    f32 temp_f20;

    temp_f20 = fparg0 * 0.5f;
    M2C_FIELD(arg0, f32 *, 0xC) = cosf(temp_f20);
    temp_f0 = sinf(temp_f20);
    M2C_FIELD(arg0, f32 *, 0) = (f32) (M2C_FIELD(arg1, f32 *, 0) * temp_f0);
    M2C_FIELD(arg0, f32 *, 4) = (f32) (M2C_FIELD(arg1, f32 *, 4) * temp_f0);
    M2C_FIELD(arg0, f32 *, 8) = (f32) (M2C_FIELD(arg1, f32 *, 8) * temp_f0);
}

void func_001bf710(f32 *d, f32 *a, f32 *b, f32 t) {
    f32 th, s, sa, sb;
    s32 i;
    th = acosf(a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3]);
    s = sinf(th);
    sa = sinf(th * (1.0f - t));
    sb = sinf(th * t);
    if (s > -0.01f && s < 0.01f) {
        d[0] = a[0];
        d[1] = a[1];
        d[2] = a[2];
        d[3] = a[3];
        return;
    }
    s = 1.0f / s;
    for (i = 0; i < 4; i++) d[i] = (a[i] * sa + b[i] * sb) * s;
}

void func_001bf888(f32 *q, f32 m[4][4]) {
    s32 i, j, k;
    f32 s, t; f32 *p;
    i = 0;
    if (m[1][1] > m[0][0]) i = 1;
    if (m[2][2] > m[i][i]) i = 2;
    j = (i + 1) % 3;
    k = (j + 1) % 3;

    q[i] = s = sqrtf(m[i][i] - m[j][j] - m[k][k] + 1.0f) * 0.5f;
    if (s == 0.0f) {
        func_001bf290(q);
        return;
    }
    t = s * 4.0f;
    q[j] = (m[i][j] + m[j][i]) / t;
    q[k] = (m[i][k] + m[k][i]) / t;
    q[3] = (m[j][k] - m[k][j]) / t;
}
