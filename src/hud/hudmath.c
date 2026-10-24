/* The HUD's math helpers (docs/modules.md "Session 46"), 0x002492d0-0x002499f0
 * (func_00249618 is in hudmath.nogcse.c).  A fade value and its speed
 * (func_002492d0 sets them, func_002492e8 steps them by dt and returns 2 /
 * 1 at 0 / 128), rotation and translation matrices on libvu0
 * (func_00249370 z, x then y; func_002493c0; func_00249420 a look-at
 * rotation with D_00491830 as up; func_00249518 a scale), the screen offset
 * of a GS position (func_00249558), a clip test of a point
 * (func_00249580), cubic Hermite segments (func_002495c8 the coefficients,
 * func_00249718 a point on three of them), vector moves, an angle wrap by
 * 2 pi (func_002498a0), a clamp (func_00249950) and a lerp
 * (func_00249988). */
#include "common.h"
#include "platform/vu.h"
#include "data/types/text_00240000_h50.h"
#include "data/types/text_00240000_h50_p.h"
#include "data/types/shared.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002E26C0.h"
#include "data/pieces/D_00491830.h"

typedef struct { f32 val; f32 speed; } Fade;
typedef struct { f32 val; f32 speed; f32 b; f32 a; } Fade4;
typedef union { f32 m[4][4]; u128 q[4]; } M44;
typedef struct { f32 c[4]; } Seg;
typedef struct { Seg s[3]; } Seg3;
typedef struct { f32 v[4]; } V4f;
typedef struct { s32 x, y; } XY;
extern u8 D_00469F90[], D_00469FA0[];

void func_002492d0(Fade4 *p, f32 val, f32 speed, f32 a, f32 b) {
    p->val = val;
    p->speed = speed;
    p->a = a;
    p->b = b;
}

s32 func_002492e8(Fade *p, s32 dt) {
    if (p->speed != 0.0f) {
        if (!((*(u32 *)&D_002C5960) & 1)) p->val += p->speed * (f32)dt;
        if (p->val <= 0.0f) {
            p->val = 0.0f;
            p->speed = 0.0f;
            return 2;
        }
        if (p->val >= 128.0f) {
            p->val = 128.0f;
            p->speed = 0.0f;
            return 1;
        }
    }
    return 0;
}

void func_00249370(void *out, void *in, V4 *rot) {
    PlatVu0RotMatrixZ(out, in, rot->z);
    PlatVu0RotMatrixX(out, out, rot->x);
    PlatVu0RotMatrixY(out, out, rot->y);
}

void func_002493c0(void *out, V4 *pos, V4 *rot) {
    M44 m;
    PlatVu0UnitMatrix(&m);
    func_00249370(&m, &m, rot);
    PlatVu0TransMatrix(out, &m, pos);
}

void func_00249420(M44 *m, V4 *dir) {
    V4 x, y, z, up;
    up = D_00491830;
    PlatVu0Normalize(&z, dir);
    PlatVu0OuterProduct(&x, &up, &z);
    PlatVu0OuterProduct(&y, &z, &x);
    PlatVu0Normalize(&x, &x);
    PlatVu0Normalize(&y, &y);
    m->m[0][0] = x.x; m->m[0][1] = x.y; m->m[0][2] = x.z; m->m[0][3] = 0;
    m->m[1][0] = y.x; m->m[1][1] = y.y; m->m[1][2] = y.z; m->m[1][3] = 0;
    m->m[2][0] = z.x; m->m[2][1] = z.y; m->m[2][2] = z.z; m->m[2][3] = 0;
    m->q[3] = KH1_Q(0);
    m->m[3][3] = 1.0f;
}

void func_00249518(M44 *m, f32 s) {
    PlatVu0UnitMatrix(m);
    m->m[2][2] = s;
    m->m[1][1] = s;
    m->m[0][0] = s;
}

void func_00249558(XY *o, XY *gs) {
    o->x = (gs->x - 0x7000) >> 4;
    o->y = (gs->y - 0x7400) >> 4;
}

s32 func_00249580(V4 *v) {
    V4 t;
    PlatVu0CopyVector(&t, v);
    return PlatVu0ClipAll(D_00469F90, D_00469FA0, D_002E26C0, &t, 1) != 0;
}

void func_002495c8(Seg *o, f32 p0, f32 p1, f32 t0, f32 t1) {
    o->c[3] = p0;
    o->c[2] = t0;
    o->c[1] = p0 * -3.0f + p1 * 3.0f - 2.0f * t0 - t1;
    o->c[0] = 2.0f * p0 - 2.0f * p1 + t0 + t1;
}

/* FLAGGED dead set: `if (t < 0) t2 = 0;` is a one-path set of t2 that the
 * real `t2 = t * t;` overwrites; life1 deletes it so it costs no code.
 * Without it the function is 11 words off (6 with an integer test on o). */
void func_00249718(V4f *o, Seg3 *s, f32 t) {
    f32 t2, t3;
    if (t < 0) t2 = 0; /* dead set (flagged) */
    t2 = t * t;
    t3 = t2 * t;
    o->v[0] = s->s[0].c[0] * t3 + s->s[0].c[1] * t2 + s->s[0].c[2] * t + s->s[0].c[3];
    o->v[1] = s->s[1].c[0] * t3 + s->s[1].c[1] * t2 + s->s[1].c[2] * t + s->s[1].c[3];
    o->v[2] = s->s[2].c[0] * t3 + s->s[2].c[1] * t2 + s->s[2].c[2] * t + s->s[2].c[3];
    o->v[3] = 1.0f;
}

void func_002497b8(V4 *out, V4 *dir, f32 s) {
    V4 t, u;
    PlatVu0CopyVector(&t, dir);
    *(s32 *)&t.w = 0;
    PlatVu0ScaleVectorXYZ(&u, &t, s);
    PlatVu0AddVector(out, out, &u);
}

void func_00249820(s32 *d, s32 *s) {
    s32 i = 0;
    do {
        d[i] = s[i];
        i++;
    } while (i < 4);
}

void func_00249858(V4 *o, u8 *p) {
    PlatVu0CopyVector(o, p + 0x20);
}

void func_00249870(V4 *o, V4 *v) {
    PlatVu0CopyVector(o, v);
}

void func_00249888(V4 *o, u8 *p) {
    PlatVu0CopyVector(o, p + 0x10);
}

void func_002498a0(f32 *a) {
    f32 v = *a;
    f32 t;
    if (v < 3.141592503f) {
        t = v + 6.28318501f;
        *a = t;
        v = t;
    }
    if (v > 3.141592503f) {
        *a = v + -6.28318501f;
    }
}

void func_00249900(V4 *a, V4 *b) {
    V4 t;
    PlatVu0CopyVector(&t, a);
    PlatVu0CopyVector(a, b);
    PlatVu0CopyVector(b, &t);
}

f32 func_00249950(f32 *p, f32 lo, f32 hi) {
    f32 v = *p;
    if (v < lo) {
        *p = lo;
        v = lo;
    }
    if (hi < v) {
        *p = hi;
        v = hi;
    }
    return v;
}

void func_00249988(V4 *out, V4 *a, V4 *b, f32 t) {
    V4 d;
    PlatVu0SubVector(&d, b, a);
    PlatVu0ScaleVectorXYZ(&d, &d, t);
    PlatVu0AddVector(out, a, &d);
}
