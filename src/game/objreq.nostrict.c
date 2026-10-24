/* Load and spawn requests: the 128 load records D_00531B70 and the load task
 * list D_00531F70 (func_00146a68 queues a file and calls back when it is
 * in), the busy flags D_00532B80 / D_00532B90, and the effect entries
 * spawned by id with their sound (func_00146bd0, func_001473a8,
 * func_00146ff0). Flag mode: nostrict (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "common.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0053.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00140000_h33.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_0035C710.h"
#include "data/types/nostrict_text_00130000_b03_p3.h"
#include "data/pieces/D_002C58B0.h"
#include "data/types/nostrict_text_00130000_b03_p2.h"
#include "data/types/nostrict_text_00130000_b03.h"
#include "data/pieces/D_00304DB0.h"
#include "data/pieces/D_002C58D0.h"
#include "data/types/nostrict_text_00130000_b03_p.h"

/* func_00146998 (from hand/nostrict/text_00140000_h33.c). */
typedef struct { u8 pad[0x10]; s16 h10; s16 st; LdHdr *hdr; void (*cb)(s32); s32 arg; } LdTask;
s32 func_0011e248(s32);
void func_001ed658(s32, u8 *, s32);
s32 func_001ed220(s32, u8 *, s32);
s32 func_001ecfd8(void);
s32 func_00146998(LdTask *t) {
    u8 *p;
    switch (t->st) {
    case 0:
        if (func_0011e248(0) == 0) {
            p = t->hdr->data;
            if (t->hdr->n0) {
                func_001ed658(t->h10, p, t->hdr->n0);
                p += t->hdr->n4;
            }
            func_001ed220(t->h10, p, t->hdr->n8);
            t->st++;
        }
        return 8;
    case 1:
        if (func_001ecfd8() == 0) {
            if (t->cb) t->cb(t->arg);
            return 4;
        }
        return 8;
    }
    return 8;
}

/* func_00146a68 (from hand/nostrict/text_00140000_h33.c). */
extern LdEnt D_00531B70[128];
extern s32 D_00532B80;
LdTask *func_0011f090(u8 *, s32, s32 (*)(LdTask *));
s32 func_00146a68(LdHdr *h, s32 id, void (*cb)(s32), s32 arg) {
    s32 i;
    LdTask *t;
    for (i = 0; i < 128; i++) {
        if (D_00531B70[i].id == id && D_00531B70[i].h == h) {
            cb(arg);
            return 1;
        }
    }
    for (i = 0; i < 128; i++) {
        if (D_00531B70[i].h == 0) {
            D_00531B70[i].id = id;
            D_00531B70[i].h = h;
            break;
        }
    }
    t = func_0011f090(D_00531F70, 0, func_00146998);
    t->arg = arg;
    t->h10 = id;
    t->hdr = h;
    t->cb = cb;
    t->st = 0;
    {
        s32 *pc = &D_00532B80;
        (*pc)++;
    }
    return 1;
}

/* func_00146bd0 (from hand/nostrict/text_00140000_h33.c). */
extern Ent32 D_00532B90[128];
extern s32 D_00533B90;
void func_00147338(s32, s32);
Ent32 *func_00146bd0(s32 n, s32 id) {
    s32 i;
    Ent32 *e;
    if (n <= 0) return 0;
    if (id > 0) {
        func_00147338(n, id);
    } else {
        s32 *pc = &D_00533B90;
        id = (*pc)++;
    }
    e = D_00532B90;
    for (i = 0; i < 128; i++, e++) {
        if (!(e->u.w.lo & 1)) {
            e->n = n;
            e->u.f.used = 1;
            e->u.f.b1 = 1;
            e->u.f.b2 = 0;
            e->u.w.id = id;
            return e;
        }
    }
    return 0;
}

/* func_00146c98 (from hand/nostrict/text_00130000_b03.c). */
extern u32 D_002C5958;
typedef struct {
    union { u64 x; struct { s32 lo; s32 x4; } s; } x0;
    u16 x8;
    u8 pada[2];
    B3Ob *xc;
} B3Se;
extern B3SeRow D_00306850[];
extern s32 D_002BC128;
extern s32 D_002C5C4C;
s32 func_001063c8(void);
s32 func_0012bd30(B3Ob *);
s32 func_00137450(s32);
s32 func_00105bc0(s32, s32);
void func_001473a8(s32, s32, f32 *);
s32 func_00147240(s32, s32);
void func_0011d1e0(s32, s32, f32 *, s32);
static inline u8 b3next(B3Ob *o) { u8 c = o->x39c; o->x39c = (c + 1) & 3; return c; }
#define func_00146bd0 ((B3Se *(*)(s32, s32)) func_00146bd0)
void func_00146c98(B3Ob *o, u32 k) {
    B3SeRow *tb;
    u32 id;
    s32 t, n, m, b;
    u8 c;
    B3Se *p;

    if ((D_002C5958 >> 10) & 1) return;
    if (o->x9c & 1) return;
    if (func_001063c8()) return;
    if (((s32)(o->x370 >> 37) & 3) != 2 && !(o->x0 & 1)) return;
    t = o->x130->x4c;
    if (t >= 21) return;
    if (t >= 3) switch (t) {
    case 4:
        t = 1;
        break;
    case 17:
        t = 2;
        break;
    default:
        t = 3;
        break;
    }
    tb = &D_00306850[D_002BC128 * 4 + t];
    id = 15;
    if (!D_002C5C4C) {
        id = o->x39e;
        switch (k) {
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
            if (!func_0012bd30(o)) return;
            if ((k & 1) != (o->x39c & 1)) b3next(o);
            k = (k & ~3) + b3next(o);
            break;
        case 14: case 15: case 16:
            if (o->x2de != 0xffff) {
                id = func_00105bc0(-1, o->x2de);
            } else if (o->x30c != 0xffff) {
                id = func_00105bc0(-1, o->x30c);
            } else {
                return;
            }
            break;
        case 17:
            id = func_00105bc0(func_00137450(o->x148->x94), o->x148->x90);
            break;
        case 18: case 19: case 20: case 21: case 22: case 23:
            id = func_00105bc0(-1, o->x148->x5c);
            break;
        case 26: case 27: case 28: case 29:
            n = tb->x[13];
            if (!n) return;
            k = k * 2 + (o->x39c & 1) - 52;
            b3next(o);
            func_001473a8(n + k, o->x4 + 1, o->x10);
            return;
        }
    }
    if (!id) return;
    n = (tb->x - 1)[id];
    if (!n) return;
    id = o->x4 + 1;
    if (k - 21 < 2 || k == 24) {
        k += n;
        if (func_00147240(k, id)) return;
        p = func_00146bd0(k, id);
    } else if (D_002C5C4C && k - 14 < 2) {
        p = func_00146bd0(k + n, id);
    } else {
        goto call;
    }
    if (p) {
        func_0011d1e0(p->x8, p->x0.s.x4, o->x10, 0);
        p->x0.x |= 4;
        p->xc = o;
    }
    goto end;
call:
    func_001473a8(n + k, id, o->x10);
end:;
}
#undef func_00146bd0

/* func_00146ff0 (from hand/nostrict/text_00140000_h56.c). */
typedef struct { u8 pad[0xa0]; f32 va0[3]; f32 fac; f32 fb0; f32 fb4; f32 fb8; } Cam148;
typedef struct {
    u32 flags;
    u8 pad4[0x88 - 4];
    u32 w88;
    u8 pad8c[0x148 - 0x8c];
    Cam148 *c148;
    u8 pad14c[0x2d4 - 0x14c];
    f32 f2d4;
    u8 pad2d8[0x39e - 0x2d8];
    u8 b39e;
    u8 pad39f[0x3c0 - 0x39f];
    f32 v3c0[4];
} Pk;
typedef struct { u64 d0; u32 w8; void *pc; } Fx;
typedef struct {
    u32 flags;
    s32 w4;
    u8 pad8[0x50 - 8];
    f32 v50[4];
    u8 pad60[0x9c - 0x60];
    u32 w9c;
    u8 padA0[0x370 - 0xa0];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 hi:25; } b; } u370;
    u8 pad378[0x39e - 0x378];
    u8 b39e;
} Pf;
extern s8 D_0030884F[];
void func_00146fb8(Pf *, s32, s32);
#define func_00146c98 ((void (*)(Pk *, s32)) func_00146c98)
#define func_001063c8 ((s32 (*)(Pf *)) func_001063c8)
#define func_001473a8 ((Fx *(*)(s32, s32, f32 *)) func_001473a8)
void func_00146ff0(Pf *o, s32 kind, s32 arg, s32 bit) {
    Fx *fx;
    s32 n;

    if ((D_002C5958 >> 9) & 1) return;
    if (o->w9c & (1 << bit)) return;
    if (func_001063c8(o)) return;
    if (o->u370.b.kind != 2 && !(o->flags & 1)) return;
    switch (kind) {
    case 0:
        fx = func_001473a8(arg, o->w4 + 1, o->v50);
        if (fx) {
            fx->pc = o;
            fx->d0 |= 4;
        }
        break;
    case 25:
        func_00146fb8(o, o->w4 + 1, arg);
        break;
    default:
        arg = D_0030884F[kind];
        if (arg < 0) break;
        if (arg == 10 && (u8)(o->b39e - 11) < 2) break;
        func_00146c98((Pk *)o, arg);
        break;
    }
}
#undef func_001473a8
#undef func_00146c98
#undef func_001063c8

/* func_00147138 (from hand/nostrict/text_00140000_h33.c). */
typedef FVec4 V4f;
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
extern u16 D_00307226[];
extern u16 D_003085D8[];
#define func_001473a8 ((s32 (*)(s32, s32, V4f *)) func_001473a8)
s32 func_00147138(ObjF3 *o, s32 v) {
    u32 k = o->p130->b5c;
    if (v == 4) {
        v = D_003085D8[k];
        if (v == 0) return 0;
    } else {
        u16 t = D_00307226[o->b39e + (D_002BC128 * 8 + k) * 15];
        if (t == 0) return 0;
        v += t;
    }
    return func_001473a8(v, o->w4 + 1, &o->pos);
}
#undef func_001473a8

/* func_001474a0 (from hand/nostrict/text_00140000_h56.c). */
typedef struct {
    u8 pad0[0x88];
    u32 w88;
    u8 pad8c[0x164 - 0x8c];
    s32 w164;
} Tgt;
typedef struct {
    union { u64 d; struct { u32 w; s32 w4; } s; } u;
    u16 h8;
    u16 ha;
    Tgt *tgt;
    u8 pad10[0x10];
} Snd32;
s32 func_0011d6f0(u16, s32);
s32 func_00122ff8(Tgt *);
void func_00147300(Snd32 *);
void func_00146778(Snd32 *, s32);
s32 func_0011f130(void *, s32);
extern Snd32 D_00532B90_001474a0[] __asm__("D_00532B90");
#define D_00532B90 D_00532B90_001474a0
#define func_00147338 ((void (*)(u16, s32)) func_00147338)
s32 func_001474a0(void) {
    Snd32 *p = D_00532B90;
    s32 i;
    s32 f;

    for (i = 0; i < 128; i++, p++) {
        if (!(p->u.s.w & 1)) continue;
        if ((s32)(p->u.d >> 1) & 1) {
            p->u.d = (p->u.d & ~2) | 8;
            if ((s32)(p->u.d >> 2) & 1) {
                p->ha = p->tgt->w164;
            }
        } else if ((s32)(p->u.d >> 3) & 1) {
            p->u.d &= ~8;
        } else if (!func_0011d6f0(p->h8, p->u.s.w4)) {
            func_00147338(p->h8, p->u.s.w4);
        } else {
            f = 0;
            if ((D_002C5958 >> 14) & 1) f = 1;
            if ((s32)(p->u.d >> 2) & 1) {
                if (!func_00122ff8(p->tgt) || p->ha != p->tgt->w164) {
                    func_00147300(p);
                } else if (p->tgt->w88 & 1) {
                    f = 1;
                }
            }
            func_00146778(p, f);
        }
    }
    D_00532B80 = func_0011f130(D_00531F70, 0);
    return 0;
}
#undef D_00532B90
#undef func_00147338

/* func_00147628 (from hand/nostrict/text_00140000_h33.c). */
typedef struct { s16 h0; s16 h2; } Prc;
u8 D_00531F80[0xc00] ALIGNED(64);  /* moved from hand/nostrict/text_00140000_h33.c (session 53) */
void func_00146928(s32);
void func_0011efa8(u8 *, u8 *, s32, s32);
s32 func_0011ef38(void (*)(void));
Prc *func_0011ef10(s32, void (*)(void));
void func_00147628(void) {
    s32 i;
    for (i = 0; i < 128; i++) D_00532B90[i].u.f.used = 0;
    for (i = 127; i >= 0; i--) D_00531B70[i].h = 0;
    func_00146928(-3);
    func_00146928(-4);
    func_00146928(-5);
    func_00146928(-6);
    func_00146928(-7);
    D_00533B90 = 1;
    func_0011efa8(D_00531F70, D_00531F80, 32, 96);
    D_00532B80 = 0;
    if (!func_0011ef38(func_001474a0)) {
        func_0011ef10(0x23668, func_001474a0)->h2 = -1;
    }
}

