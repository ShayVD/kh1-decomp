#include "common.h"
/* func_00140960 (s7 w34): MATCH with wqb03_rr.py 0048e1f0 (rodata jtbl 0x48e1f0). Fix: the k=3/4 cross product goes through a function-level f32 c that the d-block cross product also assigns (a pseudo used in two blocks is not tied by local-alloc, so the sub.s result gets f0). */
typedef struct { f32 x, y, z, w; } V4f;
typedef struct { f32 x; f32 x4; f32 z; u8 padc[0x14 - 0xc]; f32 f14; u8 pad18[0x24 - 0x18]; f32 f24; } P96;
typedef struct {
    u32 flags;
    u8 pad4[0xc];
    V4f x10;
    V4f x20;
    u8 pad30[0x148 - 0x30];
    P96 *p148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x164 - 0x154];
    s32 x164;
    u8 pad168[4];
    f32 x16c;
    u8 pad170[0x1cc - 0x170];
    u32 x1cc;
    u8 pad1d0[0x490 - 0x1d0];
    V4f x490;
} O96;
extern f32 D_002BBDFC;
f32 atan2f(f32, f32);
void func_00130398(O96 *, s32, f32);
s32 func_001375d8(O96 *);
f32 func_0013fd88(f32);
s32 func_00140838(O96 *, V4f *);
void func_00267370(V4f *, void *, void *);
void func_00267530(V4f *, V4f *, V4f *);
void func_002675a8(V4f *, V4f *);
/* rodata */
void func_00140960(O96 *o, V4f *v) {
    V4f tmp;
    V4f d;
    f32 r;
    f32 t;
    f32 c;
    u32 k;
    P96 *p;
    if (o->flags & 4) {
        if (o->x164 == 19) {
        t = o->x16c;
        if (t < 15.0f) {
            v->x = 0.0f;
            v->y = -1.0f;
            v->z = 0.0f;
            v->w = (o->x10.y - (o->p148->f14 + (o->p148->f24 - o->p148->f14) * (t / 15.0f))) / D_002BBDFC;
            func_002675a8(&o->x20, v);
        }
        } else {
            v->w = 0.0f;
        }
        return;
    }
    if (func_001375d8(o)) v->y = 0.0f;
    k = 0;
    r = func_0013fd88(o->x10.y);
    if (o->x20.y != 0.0f) {
        if (o->x20.y < 0.0f) {
            if (fabsf(r - func_0013fd88(o->x10.y - (D_002BBDFC + D_002BBDFC))) < 0.5f) k = 1;
        } else {
            if (fabsf(r - func_0013fd88(o->x10.y + (D_002BBDFC + D_002BBDFC))) < 0.5f) k = 2;
        }
    }
    if (k == 0) {
        if (v->y == 0.0f) {
            if (v->w > 0.0f) {
                c = o->p148->x * v->z - v->x * o->p148->z; if (c < 0.0f) k = 3;
                else k = 4;
                v->y = 0.0f;
                v->w = 1.5f;
            } else if (r > 0.5f) {
                o->x10.y += (1.0f - r) * 66.66666412353516f;
            } else {
                o->x10.y -= r * 66.66666412353516f;
            }
        } else {
            k = func_00140838(o, v);
        }
    }
    switch (k) {
    case 0:
        v->y = 0.0f;
        v->w = 0.0f;
        break;
    case 1:
        v->x = 0.0f;
        v->y = -1.0f;
        v->w = 2.0f;
        v->z = 0.0f;
        func_00130398(o, 21, v->x);
        break;
    case 2:
        v->x = 0.0f;
        v->y = 1.0f;
        v->w = 2.0f;
        v->z = 0.0f;
        func_00130398(o, 22, v->x);
        break;
    case 3:
    case 4:
        break;
    }
    func_00267370(&tmp, v, o->p148);
    func_00267370(&o->x20, o->p148, &tmp);
    o->x20.w = v->w;
    o->x150 = atan2f(-o->p148->x, -o->p148->z);
    func_00267530(&d, &o->x10, &o->x490);
    if (d.y == 0.0f) {
        if (d.x == 0.0f && d.z == 0.0f) {
            if (!(o->x1cc & 0x100000)) func_00130398(o, 17, 8.0f);
        } else {
            c = o->p148->x * d.z - d.x * o->p148->z; if (c < 0.0f) func_00130398(o, 24, 0.0f);
            else func_00130398(o, 23, 0.0f);
        }
    }
}

/* func_00168618 (s7 w34): MATCH hand/nostrict. From w31 4w draft: the e->b8 = 1 tails as `t = e->u.w; t |= 0x100; e->u.w = t;` with a function-level u64 t (global pseudo: no local-alloc tie, so the 256 constant gets v0 first). */
#include "data/pieces/D_002BBDFC.h"
