#include "common.h"
typedef struct { f32 x, y, z, w; } V4f;
typedef struct { u8 pad[4]; f32 x4; f32 x8; f32 xc; f32 x10; } E30s;
typedef struct {
    u32 flags;
    u8 pad4[0x20 - 4];
    V4f x20;
    u8 pad30[0x6c - 0x30];
    E30s *x6c;
    s32 x70;
    u8 pad74[0x3d0 - 0x74];
    s32 x3d0;
} E30o;
typedef struct {
    u32 flags;
    u8 pad4[0xC];
    V4f pos;
    V4f v20;
    V4f v30;
    u8 pad40[0x150 - 0x40];
    f32 f150;
} O2cf0;
void func_002675a8(V4f *, V4f *);
void func_00267530(V4f *, V4f *, V4f *);
void func_00121fc4(V4f *, V4f *);
f32 func_00121840(V4f *, V4f *);
void func_00121860(V4f *, V4f *, V4f *, f32);
f32 atan2f(f32, f32);
void func_00137688(O2cf0 *, f32);
CONTEXT_ONLY f32 func_00142cf0(O2cf0 *o, V4f *tg, f32 spd, f32 r) {
    V4f t;
    f32 d;
    func_00267530(&t, tg, &o->pos);
    if (!(o->flags & 0x10)) t.y = 0;
    func_00121fc4(&t, &t);
    if (r == 0.0f) {
        f32 k;
        r = func_00121840(&o->v30, &t);
        k = t.w / spd * 0.3f;
        if (k > 1.0f) r /= k;
    }
    d = t.w;
    if (d < spd) spd = d;
    func_00121860(&o->v30, &t, &t, r);
    o->f150 = atan2f(t.x, t.z);
    func_00137688(o, o->f150);
    t.w = spd;
    func_002675a8(&o->v20, &t);
    return d;
}
void func_002673b8(V4f *);
void func_00267560(V4f *, V4f *, f32);
s32 func_00142b30(E30o *, V4f *);
CONTEXT_ONLY s32 func_00142c80(E30o *o, V4f *v) {
    V4f t;
    func_002673b8(&t);
    func_00267560(&t, &t, 2.0f * *(f32 *)((u8 *)o + 0x2c0));
    t.y = -o->x6c->x10;
    t.w = o->x6c->x10 * 0.7f;
    return func_00142b30(o, &t);
}
/* func_00142e30: needs CONTEXT_ONLY func_00142cf0 and func_00142c80 above (plain beq/bnezl slots).
   One shared `end: return d;` (no return-value local): d has 3 refs, so z (0.0f) wins f21. */
