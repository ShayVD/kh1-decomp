/* The room's object lists: D_00525298 and the lists D_005252C8 / D_005252F8
 * / D_00525328 (func_00132c70 builds a room's list for the world / room /
 * area D_002BC128 / D_002BC130 / D_002BC134, func_00131e40 loads its objects
 * one by one, func_001320a8 finds a record by id, func_00132040 walks the
 * live entries), and the callbacks D_00525290 (defined here) and D_00525364.
 * Flag mode: nostrict (the other modes are in the sibling files). Read from
 * the code, not proved by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/pieces/D_00308CDC.h"
#include "data/bss_004F.h"
#include "data/bss_0052.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/nostrict_text_00120000_h54.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_00304AD8.h"
#include "data/pieces/D_00304B84.h"
#include "data/types/nostrict_text_00120000_b02.h"
#include "data/pieces/D_002E26C0.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002C58B0.h"
#include "data/types/nostrict_text_00120000_h54_p.h"
#include "data/pieces/D_002E2F28.h"

/* func_001323a0 (from hand/nostrict/text_00120000_h54.c). */
typedef struct { s32 f0; s32 o[5]; } Hdr16;
typedef struct { u8 p[8]; f32 f8; f32 fc; } Sub16;
typedef struct {
    u8 p0[6]; u8 f6; u8 p7[0x68 - 7];
    void *f68;
    u8 p6c[0x134 - 0x6c];
    Sub16 *f134;
    u8 p138[0x154 - 0x138];
    void *f154; s32 f158; s32 f15c;
    u8 p160[0x1d0 - 0x160];
    void *f1d0; s32 f1d4; s32 f1d8;
    u8 p1dc[0x370 - 0x1dc];
    u64 f370;
} E16;
extern void func_001238c0(E16 *, f32, f32);
extern void func_00162070(void *, s32 *, s32 *, s32 *);
extern void func_001623d0(void *, s32 *);
extern s32 func_0013b9c8(E16 *);
extern s32 func_001559a8(Hdr16 *);
extern void func_00132260(E16 *, Hdr16 *, s32);
s32 func_001323a0(E16 *e, Hdr16 *h) {
    Sub16 *s;
    switch (e->f6) {
    case 5:
    case 10:
        e->f154 = (u8 *)h + h->o[0];
        e->f1d0 = 0;
        if (h->o[2] - h->o[1] > 0) {
            s = (Sub16 *)((u8 *)h + h->o[1]);
            e->f134 = s;
            func_001238c0(e, s->fc, s->f8);
        }
        if (h->o[3] - h->o[2] > 0) e->f68 = (u8 *)h + h->o[2];
        e->f370 |= 0x8000LL << 24;
        break;
    case 4:
    case 8:
    case 9:
        if (h->o[1] - h->o[0] > 0) {
            e->f154 = (u8 *)h + h->o[0];
            func_00162070(e->f154, &e->f158, &e->f1d4, &e->f15c);
        } else {
            e->f154 = 0;
        }
        if (h->o[2] - h->o[1] > 0) {
            e->f1d0 = (u8 *)h + h->o[1];
            func_001623d0(e->f1d0, &e->f1d4);
        } else {
            e->f1d0 = 0;
        }
        e->f1d8 = 0;
        if (h->o[3] - h->o[2] > 0) {
            s = (Sub16 *)((u8 *)h + h->o[2]);
            e->f134 = s;
            func_001238c0(e, s->fc, s->f8);
        }
        if (h->o[4] - h->o[3] > 0) e->f68 = (u8 *)h + h->o[3];
        break;
    case 7:
        return func_0013b9c8(e);
    default:
        func_00132260(e, h, func_001559a8(h));
        break;
    }
}

/* func_00132790 (from hand/nostrict/text_00120000_b02.c). */
typedef struct { s32 off[64]; } Hd10;
typedef struct {
    u8 p0[2];
    u8 kind;
    u8 p3[5];
    u8 *f8;
    u8 *fc;
    u8 p10[0x54 - 0x10];
    s8 f54;
    u8 p55;
    s8 f56;
    u8 p57[0x60 - 0x57];
    s32 f60;
    s32 f64;
    u8 p68[0x78 - 0x68];
} En10;
typedef struct {
    Hd10 *f0;
    s32 *f4;
    s32 *f8;
    s32 fc;
    En10 *f10;
    u8 *f14;
    u8 *f18;
    u8 *f1c;
    u8 *f20;
    u8 *f24;
    u8 *f28;
} Ou10;
extern void func_00132678(u8 *);
extern void func_00132718(u8 *);
#define SECT(h, n) (((h)->off[(n) + 1] - (h)->off[n] > 0) ? (u8 *)(h) + (h)->off[n] : 0)
void func_00132790(Hd10 *f, s32 idx, Ou10 *o) {
    Hd10 *e;
    Hd10 *g;
    u8 *a3;
    En10 *en;
    s32 i;
    s32 *p;

    o->f0 = f;
    if (f->off[2] - f->off[1] > 0) {
        o->f4 = (s32 *)((u8 *)f + f->off[1]);
        for (i = 0; i < o->f4[0]; i++) func_00132678((u8 *)o->f4 + o->f4[i + 1]);
    } else {
        o->f4 = 0;
    }
    if (f->off[3] - f->off[2] > 0) {
        o->f8 = (s32 *)((u8 *)f + f->off[2]);
        for (i = 0; i < o->f8[0]; i++) func_00132718((u8 *)o->f8 + o->f8[i + 1]);
    } else {
        o->f8 = 0;
    }
    e = (Hd10 *)((u8 *)f + f->off[7 + idx]);
    p = (s32 *)((u8 *)e + e->off[1]);
    o->fc = p[0];
    o->f10 = (En10 *)(p + 1);
    o->f14 = SECT(e, 2);
    o->f18 = SECT(e, 3);
    if (e->off[5] - e->off[4] > 0) {
        o->f1c = (u8 *)e + e->off[4];
    } else {
        g = (Hd10 *)((u8 *)f + f->off[32]);
        if (g->off[5] - g->off[4] > 0) o->f1c = (u8 *)g + g->off[4];
        else o->f1c = 0;
    }
    a3 = (u8 *)f + f->off[6];
    en = o->f10;
    for (i = 0; i < o->fc; i++, en++) {
        switch (en->kind) {
        case 4:
        case 8:
        case 9:
            en->f8 = (u8 *)o->f4 + o->f4[en->f56 + 1];
            break;
        case 5:
        case 10:
            en->f8 = (u8 *)o->f8 + o->f8[en->f56 + 1];
            break;
        case 6:
        case 7:
            break;
        }
        if (en->f54 < 0) { s32 k = en->f54; en->fc = ((e->off + 2)[-k] - *((1 - k) + e->off) > 0) ? (u8 *)e + e->off[1 - k] : 0; }
        en->f60 = (s32)(a3 + en->f60 * 32);
        en->f64 = (s32)(a3 + en->f64 * 32);
    }
    o->f20 = SECT(f, 3);
    o->f24 = SECT(f, 4);
    o->f28 = SECT(f, 5);
}
#undef SECT

/* func_00132a78 (from hand/nostrict/text_00120000_h54.c). */
typedef struct { s32 f0; u32 f4; u8 p8[0x4c]; s8 f54; u8 p55[0x78 - 0x55]; } Ent17;
typedef struct { u8 p[0xc]; s32 n; Ent17 *base; } Lst17;
extern Lst17 D_00525298;
extern Ent17 *D_00525354;
s32 D_00525358 ALIGNED(8);
#define INC17 { s32 *p17 = &D_00525358; (*p17)++; }
void (*D_00525290)(void) ALIGNED(16);  /* moved from hand/nostrict/text_00120000_h54.c (session 53) */
extern s32 D_002BC134;
extern void func_00157400(void (*)(s32));
extern void func_0014a058(void (*)(s32));
extern void func_00133578(void (*)(s32));
extern s32 func_001560f8(s32, void (*)(s32));
void func_00132a78(s32 a0) {
    switch (D_00525358) {
    case 0:
        INC17;
        func_00157400(func_00132a78);
        break;
    case 1:
        while (D_00525354 < D_00525298.base + D_00525298.n) {
            if (!(D_00525354->f4 & 1) && (D_002BC134 != 25 || D_00525354->f54 != 1)) {
                if (func_001560f8(D_00525354->f0, func_00132a78)) {
                    D_00525354++;
                    return;
                }
            }
            D_00525354++;
        }
        INC17;
    case 2:
        INC17;
        func_00133578(func_00132a78);
        break;
    case 3:
        INC17;
        func_0014a058(func_00132a78);
        break;
    case 4:
        if (D_00525290) D_00525290();
        break;
    }
}
#undef INC17

/* func_00132c70 (from hand/nostrict/text_00120000_h54.c). */
typedef struct { s32 f0; u32 f4; u8 p8[0x40]; s16 f48; u8 p4a[2]; u16 f4c; u8 p4e[6]; s8 f54; s8 f55; s8 f56; u8 p57[0x78 - 0x57]; } Ent18;
typedef struct { u8 p[0xc]; s32 n; Ent18 *base; u8 p14[8]; s32 f1c; } Lst18;
extern s32 D_002BC128;
extern s32 D_002BC130;
s32 D_00525294 ALIGNED(4);
extern void func_001134d8(s32);
extern void *memset(void *, s32, u32);
extern s32 func_0013c6a8(s32);
extern s32 func_0013c2f0(s32);
extern void func_00146928(s32);
#define func_00132790 ((void (*)(s32, s32, Lst18 *)) func_00132790)
void func_00132c70(s32 a0, void (*cb)(void)) {
    Lst18 *l = (Lst18 *)&D_00525298;
    Ent18 *p;
    s32 i = 0, k = -1;
    s32 *pt = &D_002BC134;

    D_00525294 = 0;
    func_00132790(a0, *pt, l);
    func_001134d8(l->f1c);
    memset(&D_002E2F28, 0, 140);
    D_002E2F28.f0 = D_002BC128;
    D_002E2F28.f4 = D_002BC130 + 1;
    D_002E2F28.f8 = *pt;
    p = l->base;
    for (i = 0; i < D_00525298.n; i++, p++) {
        switch (p->f54) {
        case 1:
            if (k < 0) k = p->f55;
            if (p->f4c == D_00304BE8->x48e[1] || p->f4c == D_00304BE8->x48e[2]) {
                p->f55 = k;
                k += p->f56;
            } else {
                p->f4 |= 1;
            }
            break;
        case 8:
            if (func_0013c6a8(p->f48)) p->f4 |= 2;
            break;
        case 12:
            if (func_0013c2f0(p->f48)) p->f4 |= 2;
            break;
        }
    }
    D_00525290 = cb;
    func_00146928(-6);
    D_00525358 = 0;
    D_00525354 = (Ent17 *)D_00525298.base;
    func_00132a78(0);
}
#undef func_00132790

