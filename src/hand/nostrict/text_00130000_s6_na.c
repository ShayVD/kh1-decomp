#include "common.h"

typedef struct { f32 x, y, z, w; } V4f;
typedef struct { V4f p; V4f d; V4f hit; s16 h30; s32 w34; u8 pad38[8]; } Ray;
void func_00267560(V4f *, V4f *, f32);
s32 func_00119688(Ray *);
void func_00118648(Ray *);
void func_00118608(Ray *);
void func_002675a8(V4f *, V4f *);

s32 func_001429f8(V4f *a, V4f *b, V4f *c) {
    Ray r;
    f32 x, y, z;
    f32 one;
    x = a->x;
    one = 1.0f;
    y = a->y + b->y;
    z = a->z;
    r.p.x = x;
    r.p.z = z;
    r.p.y = y;
    r.p.w = one;
    func_00267560(&r.d, b, 1.5f);
    r.d.w = one;
    r.d.y = 0;
    if (func_00119688(&r) >= 0) return 3;
    func_00118648(&r);
    if (r.h30 >= 0) return 3;
    r.p.x += b->x;
    r.p.z += b->z;
    r.d.x = 0;
    r.d.y = b->w - b->y;
    r.d.z = 0;
    func_00118608(&r);
    if (r.h30 < 0) return 3;
    func_002675a8(c, &r.hit);
    func_00118648(&r);
    if (r.h30 >= 0 && r.hit.y < c->y) return 3;
    return 0;
}

typedef struct { u8 pad[0xb0]; f32 fb0; } S148;
typedef struct { u8 pad[0xc]; void *cb; } Ev;
typedef struct {
    u32 flags;
    u8 pad4[0x14 - 4];
    f32 x14;
    u8 pad18[0x148 - 0x18];
    S148 *p148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x310 - 0x154];
    u16 x310;
} O4810;
f32 atan2f(f32, f32);
void func_00105a30(s32, s32, V4f *);
f32 func_00121748(V4f *, V4f *);
void func_00130398(O4810 *, s32, f32);
Ev *func_00130578(O4810 *, s32, f32);
f32 func_00144378(O4810 *);
void func_0014f658(O4810 *, s32);
void func_001447a0();
s32 func_00144810(O4810 *o, V4f *v) {
    V4f t;
    f32 z = 0.0f;
    u16 id;
    f32 d;
    if (v->w == z) goto r0;
    if (o->p148->fb0 > z) goto r0;
    id = o->x310;
    if (id == 0xffff) {
r0:
        return 0;
    }
    d = func_00144378(o);
    if (fabsf(d) > 5.0f) return 0;
    func_00105a30(-1, id, &t);
    if (func_00121748(&t, v) > -0.7f) return 0;
    o->x14 -= d;
    o->x150 = atan2f(-t.x, -t.z);
    func_00130398(o, 0x1000031, 8.0f);
    func_00130578(o, 0x40000006, z)->cb = func_001447a0;
    func_0014f658(o, 16);
    return 1;
}

typedef struct { f32 x, y, z, w; } V4_9d;
typedef struct { u8 pad[0x10]; V4_9d pos; } Act9d;
extern Act9d *D_00575894; /* src/data/bss_0057.c: void *D_00575894 */
extern V4_9d D_005758D0; /* src/data/bss_0057.c: f32 D_005758D0[4] */
extern V4_9d D_005758E0; /* src/data/bss_0057.c: f32 D_005758E0[4] */
extern f32 D_002E27A0;
extern f32 D_00362520;
extern f32 D_002BBDFC;
void func_001315c0(Act9d *, s32, V4_9d *, f32);
void func_00267530(V4_9d *, V4_9d *, V4_9d *);
f32 func_00121840(V4_9d *, V4_9d *);
void func_002674f0(V4_9d *, V4_9d *, V4_9d *, f32);

void func_00179d30(void) {
    V4_9d a, b, c;
    f32 z, lim, ang, af;
    z = 0.0f;
    func_001315c0(D_00575894, 0x8003, &a, z);
    lim = D_002E27A0;
    lim *= 3.14159251f;
    lim /= 180.0f;
    func_00267530(&b, &D_005758E0, &D_005758D0);
    func_00267530(&c, &D_00575894->pos, &D_005758D0);
    ang = func_00121840(&b, &c);
    af = fabsf(ang);
    lim *= 0.5f;
    if (lim < af) {
        D_00362520 += D_002BBDFC;
        if (40.0f < D_00362520) D_00362520 = 40.0f;
    } else if (af < lim * 0.7999999523162842f) {
        D_00362520 -= D_002BBDFC + D_002BBDFC;
        if (D_00362520 < z) D_00362520 = z;
    }
    if (0.0f < D_00362520) {
        f32 r = D_00362520 / 40.0f;
        func_002674f0(&D_005758E0, &a, &D_005758E0, r * 0.7999999523162842f);
    }
}

typedef union { u64 x; struct { u32 lo; u32 x32:3; u32 b35:1; u32 hi:28; } b; } F370d;
typedef struct { u32 f0; u8 p4[0xd0-4]; u8 fd0[0x154-0xd0]; s32 f154; u8 p158[0x370-0x158]; F370d f370; } Ob8;
extern u32 D_002BC0A8;
extern void func_00135df0(Ob8 *, f32 *);
extern s32 func_00114a38(void *, s32, s32, f32 *);
extern void func_00128218(Ob8 *, f32);
void func_001369e8(Ob8 *o) {
    f32 v[4];
    s32 i;
    if (!(o->f0 & 1)) return;
    if (!(D_002BC0A8 & 1)) return;
    func_00135df0(o, v);
    for (i = 0; i < 4; i++) v[i] *= 0.0078125f;
    { u64 m = 0x800000000ULL;
    func_00114a38(o->fd0, o->f154, v[3] < 1.0f ? 0xc35a : 0x9c40, v);
    o->f370.x |= m; }
    if (o->f0 & 2) func_00128218(o, 1.0f);
}

typedef struct { void *p; s32 n; } Arg7;
typedef union { u64 x; struct { u32 lo; u32 b32:1; u32 x33:15; u32 b48:1; u32 hi:15; } b; } F370c;
typedef struct Ob7 Ob7;
struct Ob7 { u8 pad[0x144]; void *f144; u8 p148[0x370-0x148]; F370c f370; u8 p378[0x4a0-0x378]; s32 (*f4a0)(Ob7 *, s32, s32); };
extern s32 func_0012bce0(void *, s32, s32, Arg7 *, s32 *);
extern s32 func_001c4ed0(Ob7 *, s32, s32);
s32 func_00137330(Ob7 *o, s32 a, s32 b) {
    Arg7 args[2];
    s32 r;
    if (o == 0 || !o->f370.b.b32) return 0;
    r = 0;
    if (o->f370.b.b48 && o->f144) {
        args[0].n = 4;
        args[0].p = &a;
        args[1].p = &b;
        args[1].n = 4;

        func_0012bce0(o->f144, 1, 2, args, &r);
        return r;
    }
    if (o->f4a0) r = o->f4a0(o, a, b);
    else r = func_001c4ed0(o, a, b);
    return r;
}

#include "data/data_002E.h"
#include "data/data_0036.h"
