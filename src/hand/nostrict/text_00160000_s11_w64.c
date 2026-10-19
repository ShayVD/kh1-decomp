/* func_00169688 (hand/nostrict), rodata jtbl_0048E870 (verify with wqb03_rr.py 0048E870), s11w64. Natural, no flagged code.
   From session9 w3's 4w draft; new: case 10 as two paths that each load p = o->x148 and jump to one
   shared block: `if (!(D & 1)) { p = o->x148; if (hi & 1) goto c10b; goto r1; } p = o->x148; c10b: B; r1: return 1;`
   The hi path's `goto c10b` is not a jump to the next insn (the D path's p load sits between), so it
   survives jump2 and reorg fills it from c10b (`b L+4; ld v1,48(a2)`); the bnez to the D path gets the hi
   path's p load in its slot and is redirected past the duplicate load. r1 sits after B's fall-through, so
   jump.c does not hoist `li v0,1` above the hi test (the test keeps v0). */
#include "common.h"
typedef struct { f32 x, y, z, w; } Vec;
typedef struct { f32 a, b, c; } Lim;
typedef struct {
    u8 pad0[0x30];
    union { u64 x; struct { u64 lo:32; u64 hi:32; } b; } x30;
    u8 pad38[0xc0 - 0x38];
    Vec xc0;
} O148;
typedef struct {
    u8 pad0[8];
    s32 x8;
    u8 padc[4];
    Vec x10;
    u8 pad20[0x70 - 0x20];
    s32 x70;
    u8 pad74[0x90 - 0x74];
    s64 x90;
    u8 pad98[0x148 - 0x98];
    O148 *x148;
    u8 pad14c[0x3cc - 0x14c];
    f32 x3cc;
} Obj;
typedef struct {
    s32 x0;
    Lim *x4;
    u8 pad8[0x38 - 8];
    union { s64 x; s32 i; } x38;
    u8 pad40[0x58 - 0x40];
    s32 x58;
    u32 x5c;
    u8 pad60[0x68 - 0x60];
    f32 x68;
    u8 pad6c[0x90 - 0x6c];
    s32 x90;
    s32 x94;
    u8 pad98[0xb0 - 0x98];
    Vec xb0;
    u8 padc0[0x120 - 0xc0];
    Vec x120;
} Wk;
extern s32 D_002C5958;
extern s32 D_0035BD40;
extern Vec D_00575020[];
void func_0013dfb8(Obj *, Vec *);
void func_0014cce0(Obj *, f32);
void func_0014f658(Obj *, s32);
s32 func_00162a88(Vec *);
f32 func_00162c20(Vec *);
s32 func_00168618(Obj *, Wk *);
void func_00171790(Obj *, Wk *);
f32 func_00267390(Vec *, Vec *);
void func_00267530(Vec *, Vec *, Vec *);
void func_00267560(Vec *, Vec *, f32);
void func_002675a8(Vec *, Vec *);

#define GETDIR(o, w, v, r) \
    if ((D_002C5958 & 1) && w->x90 != 0 && w->x94 >= 0 && !(w->x38.i & 1)) { \
        func_002675a8(v, &w->xb0); \
        r = 1; \
        w->x38.x &= ~0x400; \
    } else { \
        func_002675a8(v, &D_00575020[w->x0]); \
        r = 0; \
        w->x38.x |= 0x400; \
    } \
    func_00267530(v, v, &o->x10);

static inline void Tail(Obj *o, Wk *w) {
    if (o->x70 != 2) {
        func_0013dfb8(o, &w->x120);
    }
}

s32 func_00169688(Obj *o, Wk *w) {
    Vec v, t;
    s32 r;
    f32 d, e, len;
    Vec *q;
    O148 *p;

    switch (o->x70) {
    case 13:
        if (o->x8 != 0 && o->x8 == D_0035BD40) {
            Tail(o, w);
            return 1;
        }
        GETDIR(o, w, &v, r);
        w->x120.x = w->x120.z = 0.0f;
        w->x120.w = 10.0f;
        if (v.y < -40.0f) {
            w->x120.y = -10.0f;
        } else if (v.y > 40.0f) {
            if (v.y > 200.0f) {
                w->x120.y = 20.0f;
            } else {
                w->x120.y = 10.0f;
            }
        } else if (D_002C5958 & 1) {
            if (v.y < 0.0f) {
            m10:
                w->x120.y = -10.0f;
            } else {
                w->x38.x |= 0x40000;
                w->x58++;
                Tail(o, w);
            }
        } else {
            w->x120.y = 0.0f;
        }
        return 1;
    case 26:
        Tail(o, w);
        return 1;
    case 10:
        GETDIR(o, w, &v, r);
        w->x120.x = w->x120.z = 0.0f;
        w->x120.w = 10.0f;
        if (v.y < 0.0f) {
            w->x120.y = -10.0f;
        } else {
            w->x120.y = 10.0f;
        }
        if (!(D_002C5958 & 1)) {
            p = o->x148;
            if ((s32)p->x30.b.hi & 1) {
                goto c10b;
            }
            goto r1;
        }
        p = o->x148;
    c10b:
        p->x30.x &= ~0x100000000;
        w->x38.x |= 0x40000;
        w->x58++;
        Tail(o, w);
    r1:
        return 1;
    case 15:
        GETDIR(o, w, &v, r);
        w->x120.y = w->x120.x = w->x120.z = 0.0f;
        w->x120.w = 10.0f;
        if (v.y < 0.0f) {
            goto m10;
        }
        Tail(o, w);
        return 1;
    case 18:
        GETDIR(o, w, &v, r);
        d = func_00267390(&o->x148->xc0, &v);
        func_00267560(&t, &o->x148->xc0, d);
        func_00267530(&v, &v, &t);
        e = func_00267390(&t, &t);
        if (func_00267390(&v, &v) < e) {
            if (o->x70 != 2) {
                func_0013dfb8(o, &w->x120);
            }
            if (d < 0.0f) {
                w->x58++;
            }
            return 1;
        }
        if (v.y > 0.0f && func_00162a88(&v)) {
            Tail(o, w);
            return 1;
        }
        q = &w->x120;
        v.y = 0.0f;
        func_002675a8(q, &v);
        len = func_00162c20(q);
        switch (r) {
        case 0:
            if ((s32)(w->x38.x >> 7) & 1) {
                if (w->x4->a < len) {
                    w->x120.w = 10.0f;
                } else {
                    w->x120.w = 0.0f;
                }
            } else if (w->x38.i & 1) {
                w->x120.w = 20.0f;
            } else if (len <= w->x4->c) {
                w->x120.w = 0.0f;
            } else if (w->x4->b <= len) {
                w->x120.w = 20.0f;
            } else {
                w->x120.w = 10.0f;
            }
            break;
        case 1:
            if (w->x4->b <= len) {
                w->x120.w = 20.0f;
            } else {
                w->x120.w = 10.0f;
            }
            break;
        }
        return 1;
    case 2:
        if (func_00168618(o, w)) {
            return 1;
        }
        if (++w->x5c >= 91) {
            func_0014cce0(o, 20.0f);
            o->x3cc = 20.0f;
            w->x5c = 0;
            w->x58 += 40;
            return 1;
        }
        if ((s32)(w->x38.x >> 18) & 1) {
            return 1;
        }
        break;
    case 25:
        { s32 *pd = &D_002C5958;
        if ((*pd & 1) && w->x90 != 0 && w->x94 >= 0 && !(w->x38.i & 1)) {
            func_00171790(o, w);
        } }
        GETDIR(o, w, &v, r);
        v.y = 0.0f;
        v.w = func_00162c20(&v);
        func_002675a8(&w->x120, &v);
        w->x120.w = 30.0f;
        if (o->x90 != 0 || w->x68 <= 0.0f || v.w < 60.0f) {
            func_0014f658(o, 24);
        }
        return 1;
    }
    return 0;
}
