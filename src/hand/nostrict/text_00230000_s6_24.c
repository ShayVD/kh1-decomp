#include "common.h"
#include "data/bss_0064.h"
#include "data/bss_0065.h"

/* ---- f399.c */
void func_0024ae00(void *);
void func_0024af00(void *);
void func_00239860(void *, void *, s32, s32, f32, s32, void *, s32);

/* ---- q7.c */
#include "data/types/nostrict_text_00230000_s6_24.h"
#include "data/types/nostrict_text_00230000_s6_24_p2.h"

/* ---- p_ok2.c */
#include "data/types/nostrict_text_00230000_s6_24_p.h"
/* D_00449908: St570 above */
void func_00239a80(s32 a, void *b, void *c, void *d, s32 e, s32 g, void *col, f32 h);

void func_0024ae00(void *);
void func_0024af00(void *);
void func_00239860(void *, void *, s32, s32, f32, s32, void *, s32);
CONTEXT_ONLY void func_00239a80(s32 a, void *b, void *c, void *d, s32 e, s32 g, void *col, f32 h) {
    if (a) {
        func_0024ae00(b);
        if (c) func_0024ae00(c);
    }
    func_0024af00(b);
    if (c) func_0024af00(c);
    func_00239860(b, d, e, g, h, 0, col, 0);
    if (c) func_00239860(b, d, e, g, h, 0, col, 0);
}

/* ---- hc4.c */
extern Slot D_00651310[10];
extern B192 *D_00651300; /* src/data/bss_0065.c: u8 *D_00651300 */
Slot *func_0023c228(void);

/* ---- c3.c */
s32 func_0023c4d8(P8 *a0, s32 a1, s32 a2, s32 a3) {
    Slot *e = func_0023c228();
    if (e == 0) return -1; { B192 *s = D_00651300; e->x8 = a1; e->blk = *s; } e->xd0 = a2; e->xd4 = a3; e->xd8 = *a0;
    return e - D_00651310;
}

/* ---- e4_3.c */
typedef struct { s32 x, y, z, w; } I4b;
I4b *func_0023d208(s32 *, s32 *, f32, I4b *);
#define D208(a,b,c,f) func_0023d208(a,b,f,c)
s32 func_0023d1e0(f32);

I4b *func_0023e160(s32 *c, s32 *r, s32 *col, I4b *d, f32 a0, f32 a1, f32 al) {
    I4b *h;
    I4b *e;
    s32 i, n, m;
    ((u64 *)d)[0] = 0x1000000000008001ULL;
    ((u64 *)d)[1] = 1;
    d++;
    d->x = col[0];
    d->y = col[1];
    d->z = col[2];
    d->w = (u32)(col[3] * al);
    d++;
    h = d;
    d++;
    d->x = r[0];
    d->y = r[1];
    d->z = 0;
    d->w = 0;
    d = h + 2;
    d->x = c[0];
    d->y = c[1];
    d->z = 0;
    d->w = 0;
    d = D208(c, r, h + 3, a0);
    i = func_0023d1e0(a0) + 1;
    m = func_0023d1e0(a1);
    for (; i <= m; i++) {
        d = D208(c, r, d, i * 0.785398081f);
    }
    d = D208(c, r, d, a1);
    n = (d - h) - 1;
    ((u64 *)h)[0] = (n / 2) | 0x8000 | (0x82BBULL << 46);
    ((u64 *)h)[1] = 0x53;
    return d;
}

/* ---- k6.c */
typedef struct { u64 lo, hi; } QW;
typedef struct { s32 v[48]; } __attribute__((aligned(8))) Spr;
#include "data/pieces/D_004268B0.h"
typedef Tex_4268b0 Tex;
typedef struct {
    s32 unk0;
    s32 unk4;
    Spr *unk8[7];
    s32 unk24;
    Spr *unk28[4];
    s32 unk38;
    u8 pad3c[0x6C - 0x3C];
    Tex *unk6C;
    u8 pad70[0xA18 - 0x70];
    s32 unkA18;
    f32 unkA1C;
    u8 padA20[0xA94 - 0xA20];
    s32 unkA94;
} Obj;
void func_0023d528(Obj *, s32 *, s32 *);
QW *func_0023d700(Spr *, Tex *, s32, s32, QW *, f32);
QW *func_0023e5b0(Obj *, QW *);
QW *func_0023e330(Obj *, QW *);
QW *func_0023e8f0(Obj *, QW *);
QW *func_0023ec88(Obj *, QW *);

typedef union {
    u64 v;
    struct { u64 tbp0:14, tbw:6, psm:6, tw:4, th:4, tcc:1, tfx:2, cbp:14, cpsm:4, csm:1, csa:5, cld:3; } b;
} Tex0;

CONTEXT_ONLY QW *func_0023e330(Obj *o, QW *r) { return r; }
CONTEXT_ONLY QW *func_0023e8f0(Obj *o, QW *r) { return r; }
QW *func_0023ee80(Obj *o, QW *r) {
    s32 a[4];
    s32 b[2];
    s32 i, x, y;
    u64 t;
    Tex0 tx;
    func_0023d528(o, a, b);
    x = b[0];
    y = b[1];
    for (i = 0; i < o->unk38; i++) {
        r = func_0023d700(o->unk28[i], &D_004268B0, x, y, r, o->unkA1C);
    }
    for (i = 0; i < o->unk24; i++) {
        if (((o->unkA18 == 0 && o->unk0 == 0) || (o->unk0 == 3 && o->unkA94 == 0)) && i == 5) continue;
        r = func_0023d700(o->unk8[i], o->unk6C, x, y, r, o->unkA1C);
    }
    r->lo = 0x2000000000008001;
    r->hi = 0xEE;
    r++;
    t = o->unk6C->tb.unk18;
    tx.v = t;
    tx.b.csa = 0;
    tx.b.cld = 1;
    tx.b.psm = 0x13;
    r->lo = tx.v;
    r->hi = 6;
    r++;
    r->lo = t;
    r->hi = 6;
    r++;
    switch (o->unk0) {
    case 3:
        r = func_0023e5b0(o, r);
        if (o->unkA94) r = func_0023e330(o, r);
        break;
    case 0:
    case 1:
    case 2:
    case 4:
        r = func_0023ec88(o, func_0023e8f0(o, r));
        break;
    }
    return r;
}

/* ---- ih.c */
typedef struct { s32 x0, x4, x8, xc; } S4A20;
extern S4A20 D_00454A20;
typedef struct { u8 pad[0x3C]; s32 x3c; s32 x40; } St6C;
typedef struct { u8 pad[0x6C]; St6C *x6c; } Ow4;
typedef struct { s32 x0; Ow4 *x4; } Ob810;

/* ---- i_ok.c */
s32 func_00240810(Ob810 *o) {
    s32 r;
    St6C *p;
    if (o->x0 == 4) {
        r = 0;
        if (D_00454A20.x4 != 0) {
            if ((f32)D_00454A20.x4 < (f32)D_00454A20.xc * 0.3f) r = 1;
        }
    } else {
        r = 0;
        if (o->x0 != 3) {
            p = o->x4->x6c;
            if (p->x3c > 0) {
                r = p->x3c < 9;
                if (p->x40 >= 45) {
                    if ((f32)p->x3c / (f32)p->x40 < 0.199999988079071044921875f) r = 1;
                    else r = 0;
                }
            }
        }
    }
    return r;
}
#include "data/data_0044.h"
