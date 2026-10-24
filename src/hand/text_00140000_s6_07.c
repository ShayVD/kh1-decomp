#include "common.h"

#include "platform/math.h"
#include "data/bss_0054.h"

void func_00121fc4(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void func_0014d570(f32 *v, f32 lo, f32 hi, f32 max, f32 g) {
    f32 h;
    f32 a;
    f32 c;
    f32 t;
    f32 b;
    f32 k;

    h = -v[1];
    v[1] = 0.0f;
    func_00121fc4(v, v);
    k = 0.5f;
    a = g * k;
    c = a * 4.0f * h;
    t = MIN(MAX(lo, v[3] / max), hi);
    b = (-g * t) * k;
    t = (PlatSqrtf(b * b - c) - b) / (a + a);
    func_00267560(v, v, MIN(v[3] / t, max));
    v[1] = b;
}

#include "data/pieces/D_002E31B0.h"
f32 func_0012ec60(struct Actor *, s32, f32 *);
void func_001315c0(void *, s32, f32, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
f32 func_00121748(f32 *, f32 *);
f32 func_00120c18(f32 *);

void func_0014d988(void *o, s32 unused, f32 *v, f32 r, f32 off, f32 scale, f32 lim) {
    f32 p[4];
    f32 d[4];
    f32 h;
    f32 s;
    f32 y;
    f32 z;
    f32 t;

    z = 0.0f;
    h = func_0012ec60(D_002E31B0.f0, D_002E31B0.f4, d);
    func_001315c0(o, 0x8003, z, p);
    func_00267530(d, d, p);
    if (r < func_00121748(d, v)) {
        s = (func_00120c18(d) - h - off) * scale;
        if (z < s) {
            y = d[1] / s * v[3];
            if (y < -lim) t = -lim; else if (lim < y) t = lim; else t = y;
            v[1] = t;
        }
    }
}

#include "data/pieces/D_00350D78.h"
extern s32 D_0054F44C;
typedef struct { u8 x[20]; } Col20;
typedef struct { u8 pad[5]; u8 n; u8 pad6[0xe]; Col20 *cols; } ColSet;
typedef struct { u8 pad[0x134]; ColSet *cs; } Ob88;
typedef struct { f32 a[4]; f32 b[4]; } Cap88;
void func_0015bad0(Ob88 *, Col20 *, void *);
void func_00267518(f32 *, f32 *, f32 *);
s32 func_0014ee08(f32 *, f32 *, f32 *);

s32 func_0014ee88(Ob88 *o) {
    Cap88 cap;
    f32 lo[4];
    f32 hi[4];
    f32 q[4];
    s32 i;
    s32 m;
    Box57_f1b8 *b;
    ColSet *cs;

    if (!D_00350D78 || !o || !(cs = o->cs) || !cs->n) return 0;
    i = 0;
    m = 0;
    func_0015bad0(o, cs->cols, &cap);
    q[0] = q[2] = cap.a[1];
    q[1] = cap.a[2];
    func_00267530(lo, cap.b, q);
    func_00267518(hi, cap.b, q);
    b = D_00350D78->box;
    for (; i < D_00350D78->n; i++, b++) {
        if ((b->u.flags & 0x200) || func_0014ee08(lo, hi, (f32 *)b)) m |= 1 << (b->u.c.id - 1);
    }
    return m & D_0054F44C;
}

typedef struct { u8 pad[0x70]; s32 x70; u8 pad74[0x164 - 0x74]; s32 x164; } A3e80;
CONTEXT_ONLY void func_00153d88(A3e80 *a) { a->x70 = 0; }

typedef struct { s8 id; u8 n; u8 x2; u8 x3; u8 pad[0x44 - 4]; s32 x44; } E5878;
extern E5878 D_00550400[]; /* src/data/bss_0055.c: E550400 D_00550400[0x34] */

CONTEXT_ONLY void func_00155be0(s32 a) { D_00550400[a].x3 = 0; }
