#include "common.h"

typedef struct { f32 x, y, z, w; } V4f;
typedef struct { u8 pad[0x30]; u64 d30; u8 pad38[8]; V4f p; f32 f50; f32 f54; u8 pad58[4]; s32 w5c; u8 pad60[0x40]; V4f va0; f32 fb0; f32 fb4; f32 fb8; f32 fbc; } Sub148;
typedef struct {
    u32 flags;
    u8 pad4[0xC];
    V4f pos;
    u8 pad20[0x88 - 0x20];
    u32 w88;
    u8 pad8c[0x148 - 0x8C];
    Sub148 *p148;
    u8 pad14c[0x1CC - 0x14C];
    u32 w1cc;
    u8 pad1d0[0x2A0 - 0x1D0];
    V4f v2a0;
    V4f v2b0;
    f32 f2c0;
    u8 pad2c4[0x2D0 - 0x2C4];
    u32 w2d0;
    u8 pad2d4[0x2F0 - 0x2D4];
    V4f v2f0;
    f32 f300;
    f32 f304;
    u8 pad308[0x314 - 0x308];
    u16 h314;
    u8 pad316[0x3C4 - 0x316];
    f32 f3c4;
} ObjF3;
#include "data/pieces/D_002E27C8.h"
void func_00130398(ObjF3 *, s32, f32);
void func_00130578(ObjF3 *, s32, f32);
void func_002675a8(V4f *, V4f *);
void func_00121fc4(V4f *, V4f *);
void func_00267560(V4f *, V4f *, f32);

extern V4f D_002C58A0;
f32 func_0013fe80(f32);
s32 func_001186a8(V4f *);
void func_00267518(V4f *, V4f *, V4f *);
s32 func_0015bcb8(ObjF3 *, V4f *);


/* func_00140838: the failure tail (flag set + return 0) written once per failing test; jump2 cross-jumps the copies into one block but the register choice follows the per-path copies. */
s32 func_00140838(ObjF3 *o, V4f *v) {
    V4f t;
    s32 r;
    func_002675a8(&o->v2a0, &o->pos);
    o->v2a0.y = func_0013fe80(o->pos.y);
    o->v2a0.w = 1.0f;
    func_002675a8(&o->v2b0, &D_002C58A0);
    if (v->y < 0.0f) {
        r = 1;
        o->v2a0.y -= 66.66666412353516f;
    } else {
        r = 2;
        o->v2a0.y += 66.66666412353516f;
    }
    if (func_001186a8(&o->v2a0) == 0xFFFF) {
        o->p148->d30 |= (u64)0x8000 << 17;
        return 0;
    }
    func_00267518(&t, &o->pos, &o->v2b0);
    if (func_0015bcb8(o, &t)) {
        o->p148->d30 |= (u64)0x8000 << 17;
        return 0;
    }
    return r;
}


/* func_00141608: matches in hand/nostrict and hand. The three return-xbe tests as one || chain (one shared return label): cse then keeps the x4c reload for the index and gcse turns it into a copy of the first load (move a0,v1), with no folding of m[0]. */
typedef struct { u8 pad[0x70]; u8 bits; u8 r[3]; } W7Mem;
typedef struct { u8 pad[4]; W7Mem m[10]; } W7Save;
extern W7Save *D_00304BE8;
typedef struct { u8 pad[0x38]; s16 x38; } T16c8;
typedef struct { u8 pad[0x44]; s32 x44; s32 x48; u8 pad4c[0xbe - 0x4c]; u16 xbe; u8 padc0[8]; T16c8 *xc8; } T16s;
typedef struct { u8 pad[0x4c]; u16 x4c; } T16i;
typedef struct { u8 pad[0x6c]; T16s *x6c; u8 pad70[0x130 - 0x70]; T16i *info; } T16o;
#include "data/pieces/D_00304C70.h"
extern u32 D_002C5958;
s32 func_00141540(T16o *o, s32 a);
s32 func_00141608(T16o *o, s32 n) {
    T16s *s = o->x6c;
    u16 id;
    s32 v, max;
    s32 t;
    if (s == 0 || s == ((T16s *)&D_00304C70)) return 0;
    if (((D_002C5958 >> 11) & 1) || o->info->x4c >= 10 || (o->info->x4c == 0 && D_00304BE8->m[o->info->x4c].bits == 0)) return s->xbe;
    v = s->xbe + n;
    max = s->x48 * 30;
    if (v < 0) {
        if (s->x44 > 0) {
            v += s->x44 * 30;
            func_00141540(o, -1);
        } else {
            v = 0;
        }
    } else if (v > max) {
        v = max;
    }
    s->xbe = v;
    if (s->xc8) s->xc8->x38 = v;
    return v;
}


/* func_00144d08 (hand/nostrict): the call func_00130398(o, k, 0.0f) and the fbc store written in each branch of the inner if/else. cse then reuses the 0.0f of the fb0 test for the f12 argument (mtc1 zero,$f12 at entry), and jump2 cross-jumps the two tails back into one. With only the call duplicated, a (use (const_int 0)) left by the sibcall pass after the else-branch call blocks the cross-jump. */
s32 func_00144d08(ObjF3 *o) {
    V4f t;
    if (o->p148->fb0 <= 0.0f) {
        s32 k;
        f32 a, s;
        if ((D_002E27C8 >> 6) & 1) {
            k = 48;
            o->p148->fb0 = 75.0f;
            a = 45.0f;
            s = 12.0f;
            o->p148->fb4 = a;
            func_00130398(o, k, 0.0f);
            o->p148->fbc = 4.0f;
        } else {
            k = 47;
            o->p148->fb0 = 45.0f;
            a = 30.0f;
            s = 9.0f;
            o->p148->fb4 = a;
            func_00130398(o, k, 0.0f);
            o->p148->fbc = 4.0f;
        }
        func_00130578(o, 46, 16.0f);
        func_002675a8(&t, &o->p148->va0);
        t.y = 0;
        func_00121fc4(&t, &t);
        if (t.w == 0.0f) func_002675a8(&t, (V4f *)((u8 *)o + 0x30));
        func_00267560(&o->p148->va0, &t, s);
        o->p148->fb8 = s;
    }
    return 0;
}
#include "data/pieces/D_002C5958.h"
