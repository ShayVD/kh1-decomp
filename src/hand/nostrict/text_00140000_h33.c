#include "common.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0053.h"
/* Hand-matched functions near 0x13C000-0x149000 (worker 33).
 * Built without strict aliasing (several of these need the reloads). */
#include "data/pieces/D_002C58A0.h"
typedef FVec4 V4f;

/* ---- save data (D_00304BE8), shared with h7 ---- */
typedef W606Mem_304be8 W7Member;

typedef Save_304be8 W7Save;

/* ---- actor object ---- */
typedef struct Eff154 { u8 pad[0x10]; u8 *p10; u32 w14; } Eff154;
typedef struct S130 { u8 pad[0x5C]; u8 b5c; } S130;
typedef struct {
    u8 pad[0x30];
    u64 d30;
    u8 pad38[8];
    V4f p;
    f32 f50;
    f32 f54;
    u8 pad58[4];
    s32 w5c;
    u8 pad60[0x40];
    V4f va0;
    f32 fb0;
    f32 fb4;
    f32 fb8;
    f32 fbc;
    u8 padc0[0x154 - 0xC0];
    Eff154 *p154;
    f32 f158;
} Sub148;
typedef struct {
    u32 flags;
    s32 w4;
    u8 pad8[0x8];
    V4f pos;
    u8 pad20[0x88 - 0x20];
    u32 w88;
    u8 pad8c[0x130 - 0x8C];
    S130 *p130;
    u8 pad134[0x148 - 0x134];
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
    u8 pad316[0x39E - 0x316];
    u8 b39e;
    u8 pad39f[0x3C4 - 0x39F];
    f32 f3c4;
} ObjF3;

/* ---- level/stat block (o->p6c) ---- */

/* ---- misc ---- */
typedef struct { u8 x0, x1, x2; } Item;
typedef struct { u32 type:8; u32 id:16; u32 hi:8; s32 w4; } Cmd;
typedef struct { u8 id; u8 pad[3]; s32 w4; s32 w8; } Cmd8;
typedef struct { f32 x, y, z; s32 w; } V4;
typedef struct { u8 pad[0x54]; s8 b54; } Sub130;
typedef struct { u8 pad[0x130]; Sub130 *p130; } Obj130;
#include "data/types/nostrict_text_00140000_h33.h"

/* ---- data ---- */
extern u32 D_002C5958;
#include "data/pieces/D_002C5960.h"
extern u32 D_002C5AD4;
extern f32 D_002BBDFC;
#include "data/pieces/D_002E27C8.h"
u8 D_00531F80[0xc00] ALIGNED(64);
u8 D_0054C160[0x50] ALIGNED(32);

/* ---- functions ---- */
Item *func_00147840(s32);
s32 func_00133000(ObjF3 *, s32);
void func_00130340(ObjF3 *, s32, f32);
void func_00130578(ObjF3 *, s32, f32);
void func_001333e0(ObjF3 *, s32, s32 *);
void func_0014cce0(ObjF3 *, f32);
void func_00267560(V4f *, V4f *, f32);
void func_00137330(s32, ObjF3 *, s32);
u16 *func_001478c8(s32);
s32 func_0012f040(s32, s32);
void func_0013ecf8(s32, s32 *, V4 *);
void func_002675a8(V4f *, V4f *);
void func_0013e1f8(Obj130 *, V4f *);
s32 func_001375d8(Obj130 *);
s32 func_0013f108(Obj130 *);
void func_001271b0(Obj130 *, V4f *);
void func_00159978(Obj130 *, V4f *);
void func_001707d0(Obj130 *, V4f *);
void func_002673b8(V4f *, V4f *);
void func_0013e558(Obj130 *, V4f *);
void func_00267530(V4f *, V4f *, V4f *);
void func_00121fc4(V4f *, V4f *);
s32 func_001375f0(ObjF3 *);
s32 func_0013f478(ObjF3 *, s32);
void func_0014f658(ObjF3 *, s32);
s32 func_0013f330(ObjF3 *, s32);
void func_00130398(ObjF3 *, s32, f32);
void func_00267518(V4f *, V4f *, V4f *);
void func_0014cc88(ObjF3 *, f32);

s32 func_0013c9e0(s32 item, u32 who) {
    if (item & 0x400) return 255;
    if (who < 10) {
        W7Member *m = &D_00304BE8->m[who];
        if (func_00147840(item)->x2 == 0) {
            s32 k;
            for (k = 0; k < m->sub.x21; k++) {
                if (m->sub.x22[k] == 0) {
                    m->sub.x22[k] = item;
                    return who;
                }
            }
        }
    }
    if (D_00304BE8->items[item] < 99) {
        D_00304BE8->items[item]++;
        return 12;
    }
    return 255;
}

s32 func_0013cae8(u32 who, s32 item) {
    if (who < 10) {
        W7Member *m = &D_00304BE8->m[who];
        s32 k;
        for (k = 0; k < m->sub.x21; k++) {
            if (m->sub.x22[k] == item) {
                m->sub.x22[k] = 0;
                return who;
            }
        }
    }
    if (D_00304BE8->items[item] != 0) {
        D_00304BE8->items[item]--;
        return 12;
    }
    return 255;
}

void func_0013e978(ObjF3 *o, Cmd *c) {
    u8 t = *(u8 *)c;
    if (t != 0) {
        if (t == 2) {
            if (func_00133000(o, c->id) == 0) return;
            if (c->id == 0) {
                f32 z = 0.0f;
                func_00130340(o, 0x1000083, z);
                func_00130578(o, 0x8A, z);
            } else {
                func_00130340(o, (c->id + 0x83) | 0x1000000, 0.0f);
            }
            func_00130578(o, 0x40000006, 8.0f);
            func_001333e0(o, c->id, &c->w4);
            func_0014cce0(o, (*(Cfg_308cdc **)&D_00308CDC)->fe8);
            func_00267560((V4f *)((u8 *)o + 0x3C0), (V4f *)((u8 *)o + 0x3C0), (*(Cfg_308cdc **)&D_00308CDC)->ff0);
            return;
        }
        func_00137330(c->w4, o, t);
    }
}

void func_0013ed88(s32 o, Cmd8 *c, V4 *v) {
    if (*func_001478c8(c->id) & 2) {
        if (func_0012f040(c->w4, c->w8)) {
            func_0013ecf8(o, &c->w4, v);
            return;
        }
        if (v->x == 0.0f && v->z == 0.0f) {
            func_002675a8((V4f *)v, (V4f *)(o + 0x30));
        }
        v->w = 0;
    }
}

void func_0013f198(Obj130 *o) {
    V4f a, b;
    func_0013e1f8(o, &a);
    if (!func_001375d8(o) && !func_0013f108(o)) {
        if (o->p130->b54 == 0) {
            func_001271b0(o, &a);
        } else if ((D_002C5958 >> 17) & 1) {
            func_00159978(o, &a);
        } else if (!(((*(u32 *)&D_002C5960) >> 3) & 1)) {
            func_001707d0(o, &a);
        } else if (D_002C5AD4 & 0x8000) {
            func_001271b0(o, &a);
        }
    }
    func_002675a8(&b, &a);
    b.y = 0;
    func_002673b8(&b, &b);
    b.y = a.y;
    b.w = a.w;
    func_0013e558(o, &b);
}

void func_0013f358(ObjF3 *o) {
    V4f t;
    func_002675a8(&o->p148->p, &o->v2f0);
    o->p148->f50 = o->f300;
    o->p148->f54 = o->p148->p.y + o->f304;
    o->p148->w5c = o->h314;
    func_00267530(&t, &o->v2f0, &o->pos);
    t.y = 0;
    func_00121fc4(&t, &t);
    func_00267560(&t, &t, o->p148->f50 + o->f2c0);
    o->pos.x = o->p148->p.x - t.x;
    o->pos.z = o->p148->p.z - t.z;
    o->flags |= 0x200000;
    o->w1cc &= ~1;
}

s32 func_0013f510(ObjF3 *o, s32 a) {
    if (func_001375f0(o) && func_0013f478(o, a)) {
        f32 lim;
        o->p148->f50 += D_002BBDFC;
        lim = 12.0f;
        if (!(o->f300 > 25.0f)) lim = 6.0f;
        if (lim < o->p148->f50) {
            f32 z;
            z = 0.0f;
            func_0014f658(o, 13);
            func_00130398(o, func_0013f330(o, 28) | 0x1000000, z);
            func_00130578(o, func_0013f330(o, 27) | 0x40000000, z);
            return 1;
        }
        return 0;
    }
    o->p148->f50 = 0.0f;
    return 0;
}

void func_0013f770(ObjF3 *o, V4f *v) {
    V4f t;
    f32 s;
    u32 fl = 0;
    if (v->y < 0.0f) {
        s = 20.0f;
        func_00130398(o, 5, 0.0f);
        func_00130578(o, 6, 0.0f);
    } else if (v->w > 0.0f) {
        s = 15.0f;
        func_00130398(o, 5, 0.0f);
        func_00130578(o, 6, 0.0f);
    } else {
        s = 5.0f;
        fl = 0x10000;
        func_00130398(o, 6, 12.0f);
    }
    v->y = 0.0f;
    func_00267560(&t, (V4f *)((u8 *)o + 0x30), -1.0f);
    func_00267518(v, v, &t);
    func_002673b8(v, v);
    v->w = 2.0f;
    func_0014cc88(o, s);
    o->flags |= fl;
}

/* func_00141468 and func_00141540 only match with func_00141448 defined
 * above them. */
#include "data/bss_0053_mixed.h"
#include "data/data_002B.h"
#include "data/data_0030.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDFC.h"
