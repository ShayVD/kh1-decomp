/* 3w (hand/nostrict_nogcse, CONTEXT_ONLY func_00142cf0 above): this shape (early 'return z', no inner 'return d') fixes the bc1t at 0x142eec but beq/bnezl at 0x142efc/0x142f0c differ. Learned: the original keeps 'mov.s f0,f22' in the beq slot as a real copy; in all our shapes with an inner 'return d' gcc drops that copy (f0 still holds the call result d), which is why bc1t becomes bc1tl. The original must have something (a label/join or a different value in f0) that makes the fall-through block recopy d into f0 before the x70 test. Session-6 draft (2w) is still the closest. */
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
extern f32 D_002BBDFC;
s32 func_00142c80(E30o *o, V4f *v);
void func_0014cce0(E30o *o, f32 f);
void func_00130398(E30o *o, s32 k, f32 f);
void func_0014f658(E30o *o, s32 k);
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
f32 func_00142e30(E30o *o, V4f *tg, s32 mode) {
    s32 an = -1;
    f32 spd;
    f32 z;
    f32 d;
    f32 r;
    s32 n;
    switch (mode & 0xffff) {
    case 0:
        an = 1;
        spd = o->x6c->x4;
        break;
    case 1:
        an = 2;
        spd = o->x6c->x8;
        break;
    case 2:
        spd = o->x6c->xc;
        break;
    default:
        spd = 0.0f;
        break;
    }
    z = 0.0f;
    d = func_00142cf0((O2cf0 *)o, tg, spd, z);
    if (d < spd * D_002BBDFC) return z;
    if (o->x70 != 2) {
        if (!(o->flags & 0x100)) {
        n = func_00142c80(o, &o->x20);
        if (n > 0) {
            if (n >= 3) {
                if (n == 3) return -1.0f;
            } else {
                if (mode & 0x10000) return -1.0f;
                an = -1;
                func_0014cce0(o, o->x6c->x10);
                func_00130398(o, (o->x3d0 + 4) | 0x10000, z);
                func_0014f658(o, 2);
            }
        }
        if (an >= 0) func_00130398(o, an, 8.0f);
        }
    }
    return d;
}