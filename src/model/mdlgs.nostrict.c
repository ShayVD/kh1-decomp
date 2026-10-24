/* The model renderer's DMA and GS side, without strict aliasing
 * (docs/modules.md "Session 52"): the two double-buffered packet lists
 * (D_00551D90, D_00559DC0; func_0015ec68 sets them up and registers the
 * tasks func_0015eb78 and func_0015eea0), the GS uploads through libdma's
 * channels D_0055C640 / D_0055C644 (func_0015f018 ... func_0015ff78).  Read from the code, not proved by a boot. */
#include "common.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00140000_s6_07.h"
#include "platform/math.h"
#include "data/pieces/D_00351BC8.h"
#include "data/types/nostrict_text_00150000_h36.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_003519E0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/types/nostrict_text_00140000_b04.h"
#include "data/pieces/D_00304BE8_s.h"

/* func_0015ea98 (from hand/nostrict/text_00140000_s6_07.c). */
extern Nea98 *D_00551D80;
extern volatile s32 D_00559DB8;
extern volatile s32 D_00559DB4;
s32 func_00265bc0(s32, s32);
s32 func_0015ea98(void) {
    s32 r;

    while (func_00265bc0(1, 0) != 0) {
    }
    while (D_00551D80 != 0) {
        D_00559DB8++;
        r = D_00551D80->xc(D_00551D80);
        if (!(r & 0x20)) {
            D_00551D80->x0 = 0;
            D_00551D80 = D_00551D80->x8;
        } else {
            D_00559DB8--;
        }
        if (r & 2) return 1;
    }
    D_00559DB4 = 0;
    return 0;
}

/* func_0015eb78 (from hand/nostrict/text_00140000_s6_07.c). */
extern Beb78 D_00551D90[];
extern Beb78 * D_00559DB0;
extern volatile s32 D_00559DBC;
extern  s32 D_00351BD0;
void func_002583e0(s32);
s32 func_00258d10(s32);
void func_00258d78(s32);
s32 func_0015eb78(void) {
    s32 idx;
    Beb78 *cur;
    Beb78 *p;

    func_002583e0(0);
    D_00551D80 = D_00559DB0->x8;
    idx = D_00351BD0 ^ 1;
    D_00559DB4 = 1;
    D_00559DBC = 0;
    D_00559DB8 = D_00559DBC;
    D_00351BD0 = idx;
    D_00559DB0 = p = &D_00551D90[idx];
    p->x8 = 0;
    p->xc = 0;
    while (func_00265bc0(1, 0) != 0) {
    }
    func_00258d10(2);
    func_00258d10(1);
    *(volatile s32 *)0x1000e010 = 6;

    if (func_0015ea98()) {
        func_00258d78(2);
        func_00258d78(1);
    }
    return 0;
}

/* func_0015ec68 (from hand/nostrict/text_00150000_h36.c). */
typedef struct { u16 h0; s16 h2; } TaskReg;
TaskReg *func_0011ef10(s32, void *);
typedef struct GsTask { u16 h0; u8 pad2[6]; struct GsTask *next; s32 (*cb)(struct GsTask *); } GsTask;
typedef struct { u8 pad[8]; GsTask *x8; s32 xC; u8 data[0x4000]; } GsBuf;
typedef struct { u8 pad[8]; GsTask *x8; s32 xC; u8 data[0x1000]; } GsBuf2;
GsBuf2 D_00559DC0[0x2] ALIGNED(64);
extern GsBuf2 *D_0055BDE0;
s32 FlushCache(s32);
void func_0011efa8(void *, void *, s32, s32);
s32 func_0015eea0();
extern GsBuf D_00551D90_0015ec68[] __asm__("D_00551D90");
#define D_00551D90 D_00551D90_0015ec68
#define D_00559DB0 ((GsBuf *) D_00559DB0)
void func_0015ec68(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        func_0011efa8(&D_00551D90[i], D_00551D90[i].pad + 16, 32, 512);
        func_0011efa8(&D_00559DC0[i], D_00559DC0[i].data, 32, 128);
    }
    D_00559DB0 = D_00551D90;
    D_00351BD0 = 0;
    D_0055BDE0 = D_00559DC0;
    func_0011ef10(0x9C40, func_0015eb78)->h2 = -1;
    func_0011ef10(0x27CB8, func_0015eea0)->h2 = -1;
    (*(void **)&D_00351BC8) = FlushCache;
}
#undef D_00551D90
#undef D_00559DB0

/* func_0015eea0 (from hand/nostrict/text_00150000_h36.c). */
s32 sceGsSyncPath(s32, u16);
s32 func_0015eea0(void) {
    GsTask *t = D_0055BDE0->x8;
    FlushCache(0);
    sceGsSyncPath(0, 0);
    while (t) {
        if (!(t->cb(t) & 0x20)) {
            t->h0 = 0;
            t = t->next;
        }
        sceGsSyncPath(0, 0);
    }
    D_0055BDE0->x8 = 0;
    D_0055BDE0->xC = 0;
    D_0055BDE0 = &D_00559DC0[D_00351BD0];
    return 0;
}

/* func_0015f018 (from hand/nostrict/text_00150000_h36.c). */
DmaChcr *func_00266c08(s32);
void func_00266f38(void *, void *);
extern u8 D_00278680[];
extern u8 D_00272C70[];
void func_00162500(void);
void func_0015f018(void) {
    DmaChcr *c;
    sceGsSyncPath(0, 0);
    *(volatile u32 *)0x10003820 = 6;
    c = func_00266c08(0);
    c->dir = 1;
    c->mod = 1;
    c->asp = 0;
    c->tte = 1;
    c->tie = 0;
    func_00266f38(c, D_00278680);
    *(volatile u32 *)0x10003C20 = 6;
    c = func_00266c08(1);
    c->dir = 1;
    c->mod = 1;
    c->asp = 0;
    c->tte = 1;
    c->tie = 0;
    func_00266f38(c, D_00272C70);
    sceGsSyncPath(0, 0);
    func_00162500();
}

/* func_0015f128 (from hand/nostrict/text_00140000_s6_07.c). */
typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct {
    u64 NLOOP : 15;
    u64 EOP : 1;
    u64 pad16 : 16;
    u64 id : 14;
    u64 PRE : 1;
    u64 PRIM : 11;
    u64 FLG : 2;
    u64 NREG : 4;
    u64 REGS0 : 4;
    u64 REGS1 : 4;
    u64 REGS2 : 4;
    u64 REGS3 : 4;
    u64 REGS4 : 4;
    u64 REGS5 : 4;
    u64 REGS6 : 4;
    u64 REGS7 : 4;
    u64 REGS8 : 4;
    u64 REGS9 : 4;
    u64 REGS10 : 4;
    u64 REGS11 : 4;
    u64 REGS12 : 4;
    u64 REGS13 : 4;
    u64 REGS14 : 4;
    u64 REGS15 : 4;
} GifTag;
typedef struct DmaTag {
    u16 qwc;
    u8 mark;
    u8 id;
    struct DmaTag *next;
    u32 p[2];
} DmaTag;
typedef struct {
    GifTag gif;
    u64 ad[8];
    GifTag img;
    u8 pad[32];
} Pk1;
typedef struct {
    DmaTag call;
    DmaTag end;
    GifTag gif;
    u64 ad[18];
} Pk2;
extern u8 D_00573AC0[];
extern Pk1 D_00573AD0[7];
extern u64 D_00573E40[];
static inline void setTag(DmaTag *t, s32 qwc, s32 id, DmaTag *next) {
    t->id = id;
    t->next = next;
    t->qwc = qwc;
}
static inline void setGif(GifTag *g, s32 nloop, s32 nreg) {
    *(u128 *)g = 0;
    g->NLOOP = nloop;
    g->EOP = 1;
    g->NREG = nreg;
}
#define D_00573AC0 (*(DmaTag (*)) &D_00573AC0)
#define D_00573E40 (*(Pk2 (*)) &D_00573E40)
void func_0015f128(void) {
    s32 i;
    Pk1 *p;
    u128 z = 0;

    for (i = 0; i < 7; i++) {
        p = &D_00573AD0[i];
        *(u128 *)&p->gif = 0;
        *(u128 *)&p->img = 0;

        p->gif.NLOOP = 4;
        p->gif.NREG = 1;
        p->gif.REGS0 = 0xe;
        p->ad[1] = 0x50;
        p->ad[3] = 0x51;
        p->ad[5] = 0x52;
        p->ad[7] = 0x53;
        p->ad[6] = 0;
        p->img.EOP = 1;
        p->img.FLG = 2;
    }
    setTag(&D_00573E40.call, 0, 0x50, &D_00573AC0);
    setTag(&D_00573E40.end, 10, 0x70, 0);
    setGif(&D_00573E40.gif, 9, 1);
    D_00573E40.gif.REGS0 = 0xe;
    D_00573E40.ad[0] = 0;
    D_00573E40.ad[1] = 0x3f;
    D_00573E40.ad[2] = 0x2006e005dd313600ULL;
    D_00573E40.ad[3] = 6;
    D_00573E40.ad[4] = 0x60;
    D_00573E40.ad[5] = 0x14;
    D_00573E40.ad[6] = 0x5080b;
    D_00573E40.ad[7] = 0x47;
    D_00573E40.ad[8] = 0x800000002aULL;
    D_00573E40.ad[9] = 0x42;
    D_00573E40.ad[10] = 0x31000070;
    D_00573E40.ad[11] = 0x4e;
    D_00573E40.ad[12] = 0;
    D_00573E40.ad[13] = 0x3d;
    D_00573E40.ad[14] = 0x800d0;
    D_00573E40.ad[15] = 0x4c;
    D_00573E40.ad[16] = 5;
    D_00573E40.ad[17] = 8;
}
#undef D_00573AC0
#undef D_00573E40

/* func_0015f388 (from hand/nostrict/text_00150000_h36.c). */
extern DmaChcr *D_0055C644;
s32 func_0015f388(void) {
    u64 *p;
    __asm__ volatile("sync");
    p = (u64 *)((u32)D_00573E40 | 0x20000000);
    p[12] = 0x5080B;
    p[14] = (128LL << 32) | 0x2A;
    p[18] = (s64)D_002BC0F0.s2BC0F0_2.x10 | ((s64)D_002BC0F0.s2BC0F0_2.x14 << 8) | ((s64)D_002BC0F0.s2BC0F0_2.x18 << 16);
    p[16] = 0x31000070;
    p[20] = 0x800D0;
    p[22] = 5;
    __asm__ volatile("sync");
    D_0055C644->mod = 1;
    D_0055C644->asp = 0;
    D_0055C644->tte = 0;
    D_0055C644->tie = 0;
    __asm__ volatile("sync");
    func_00266f38((void *)D_0055C644, &D_00573E40[2]);
    return 2;
}

/* func_0015f488 (from hand/nostrict/text_00140000_b04.c). */
typedef struct { u16 x0; u8 x2; u8 x3; u16 x4; u16 x6; s32 x8; } B4Tx;
typedef struct { u8 pad[0xc]; s32 xc; } B4Tc;
typedef struct { u8 pad[0xd]; u8 xd; u8 pade[2]; B4Tx *x10; B4Tc *x14; } B4Rec;
typedef struct {
    u64 x0; u64 x8; u8 pad10[4]; u32 x14; u8 pad18[0x2c - 0x18]; u8 x2c; u8 pad2d[3]; u32 x30; u32 x34; u32 x38;
    u8 pad3c[4]; s32 x40;
} B4Src;
typedef union { struct { u8 pad[0x10]; B4Tx *x10[1]; } a; struct { u8 pad[0x14]; B4Tc *x14[1]; } b; } B4Tbl;
typedef struct { B4Src *x0; u8 pad4; s8 x5; s8 x6; u8 x7; } B4Drw;
typedef struct { u8 pad[0x40]; u64 x40; u8 pad48[0x60 - 0x48]; u64 x60; u8 pad68[8]; u64 x70; u8 pad78[8]; u64 x80; u8 pad88[8]; u64 x90; u8 pad98[8]; u64 xa0; u8 pada8[8]; u64 xb0; } B4Gs;
typedef struct { u16 x0; u8 x2; u8 x3; u16 x4; u16 x6; u16 x8; s16 xa; s32 xc; B4Drw *x10; } B4Rq;
extern B4Pk *D_0055C648;
extern B4Rq D_0055C680;
extern u8 D_00573E40_0015f488[] __asm__("D_00573E40");
#define D_00573E40 D_00573E40_0015f488
void func_0015f488(B4Drw *a) {
    u32 tbl;
    B4Tx *t;
    B4Tc *c;
    B4Gs *q;
    B4Rec *r;
    u8 k;
    tbl = a->x0->x14;
    r = (B4Rec *)(a->x7 * 4 + tbl);
    c = ((B4Tbl *)tbl)->b.x14[a->x7];
    t = r->x10;
    D_0055C648->x3 = 16;
    D_0055C648->x4 = 0;
    D_0055C648->x0 = 6;
    D_0055C648->x20 = (u64)0x9b80 << 33;
    D_0055C648->x30 = 0;
    D_0055C648->x40 = ((u64)16 << 32) | 16;
    D_0055C648->x60.b.lo = 64;
    D_0055C648->x73 = 48;
    D_0055C648->x74 = c->xc;
    D_0055C648->x70 = 64;
    D_0055C648++;
    D_0055C648->x3 = 16;
    D_0055C648->x4 = 0;
    D_0055C648->x0 = 6;
    D_0055C648->x20 = (u64)0x13043600 << 32;
    D_0055C648->x60.b.lo = t->x0;
    D_0055C648->x30 = 0;
    D_0055C648->x40 = t->x4 | ((u64)t->x6 << 32);
    D_0055C648->x73 = 48;
    D_0055C648->x74 = t->x8;
    D_0055C648->x70 = t->x0;
    D_0055C648++;
    D_0055C648->x3 = 96;
    D_0055C648->x4 = 0;
    D_0055C648->x0 = 0;
    q = (B4Gs *)((u32)D_00573E40 | 0x20000000);
    q->x40 = ((u64)t->x2 << 26) | ((u64)t->x3 << 30) | 0x2006E00401313600ULL;
    k = a->x0->x2c;
    if (a->x5) {
        q->x60 = ((u64)k << 4) | 0x50005;
        q->x70 = ((u64)128 << 32) | 0x44;
        q->x80 = a->x0->x0 | ((u64)1 << 32);
    } else {
        if (k > 120) k = 120;
        q->x70 = ((u64)128 << 32) | 0x44;
        q->x60 = ((u64)k << 4) | 0x5800b;
        q->x80 = a->x0->x0;
        q->x90 = a->x0->x30 | ((u64)a->x0->x34 << 8) | ((u64)a->x0->x38 << 16);
    }
    q->xa0 = a->x0->x8;
    q->xb0 = 5;
    __asm__ volatile("sync");
    if (a->x0->x40) {
        D_0055C680.x0 = 0x3600;
        D_0055C680.x2 = 4;
        D_0055C680.x3 = 19;
        D_0055C680.x4 = t->x4;
        D_0055C680.x6 = t->x6;
        D_0055C680.x8 = 0x3700;
        D_0055C680.xa = ((B4Rec *)(a->x7 * 4 + tbl))->xd;
        D_0055C680.xc = a->x6;
        D_0055C680.x10 = a;
    }
}
#undef D_00573E40

/* func_0015f798 (from hand/nostrict/text_00150000_h36.c). */
extern DmaChcr *D_0055C640;
extern u32 D_00272CF0[];
extern u32 D_00272DE4[];
extern u32 D_00272DA4[];
extern u32 D_00272D94[];
typedef struct { u8 pad[4]; u32 *data; } S798b;
typedef struct { u8 pad[0x10]; S798b *x10; u8 pad14[0xC]; u32 x20, x24, x28, x2C; u8 pad30[0xC]; u32 x3C; u8 pad40[8]; s8 x48; } S798e;
typedef struct { S798e *e; u32 w4; } S798a;
typedef struct { u8 pad[0x10]; S798a *x10; } S798;
void func_0015f798(S798 *o) {
    S798e *e = o->x10->e;
    u32 *d;
    if (e->x48 & 1) {
        u32 *s = e->x10->data;
        s32 i;
        d = (u32 *)((u32)D_00272DA4 | 0x20000000);
        for (i = 0; i < 16; i++) *d++ = *s++;
    } else {
        d = (u32 *)((u32)D_00272D94 | 0x20000000);
        d[0] = e->x20;
        d[1] = e->x24;
        d[2] = e->x28;
        d[3] = e->x2C;
    }
    d = (u32 *)((u32)D_00272DE4 | 0x20000000);
    d[3] = e->x3C;
    __asm__ volatile("sync");
    D_0055C640->dir = 1;
    D_0055C640->mod = 1;
    D_0055C640->asp = 0;
    D_0055C640->tte = 1;
    D_0055C640->tie = 0;
    __asm__ volatile("sync");
    func_00266f38((void *)D_0055C640, D_00272CF0);
}

/* func_0015f8c8 (from hand/nostrict/text_00150000_h59.c). */
typedef union {
    u128 q;
    struct {
        u64 nloop : 15;
        u64 eop : 1;
        u64 pad16 : 16;
        u64 id : 14;
        u64 pre : 1;
        u64 prim : 11;
        u64 flg : 2;
        u64 nreg : 4;
        u64 regs : 4;
        u64 regs_hi : 60;
    } b;
} GT59;
typedef struct { u64 d, a; } AD59;
typedef struct { u16 qwc; u8 b2; u8 id; u32 addr; u32 pad[2]; } DT59;
typedef struct { DT59 dma; GT59 tag; AD59 ad[4]; GT59 img; DT59 ref; } Pk59;
typedef struct { u8 x0, x1; u8 pad[2]; u16 w, h; } Img59;
typedef struct { u8 pad[4]; u8 n; u8 pad5[3]; u32 data[4]; Img59 *img[4]; } Src59;
#define D_0055C648 ((Pk59 *) D_0055C648)
void func_0015f8c8(Src59 *s, s32 k) {
    s32 i;
    for (i = 0; i < (s->n & 7); i++) {
        u32 d = s->data[i];
        Img59 *im = s->img[i];
        s32 n;
        if (d == 0 || im == 0) continue;
    n = im->w * im->h;
    D_0055C648->dma.id = 0x10;
    D_0055C648->dma.addr = 0;
    n = n / 16;
    D_0055C648->dma.qwc = 6;
    D_0055C648->ad[0].d = (u64)0x13043600 << 32;
        D_0055C648->img.b.nloop = (u32)n;
        D_0055C648->ad[1].d = (u64)im->x0 << 32 | (u64)im->x1 << 48;
        D_0055C648->ad[2].d = im->w | (u64)im->h << 32;
        D_0055C648->ref.id = 0x30;
        D_0055C648->ref.addr = d + n * k * 16;
        D_0055C648->ref.qwc = n;
        D_0055C648++;
    }
}
#undef D_0055C648

/* func_0015fa20 (from hand/nostrict/text_00150000_h59.c). */
typedef struct { u16 n; u8 pad2[2]; u16 w, h; u32 data; u32 clut; } Tex59;
#define D_0055C648 ((Pk59 *) D_0055C648)
void func_0015fa20(Tex59 *t) {
    __asm__ volatile("sync");
    D_0055C648 = (Pk59 *)((u32)D_00573AC0 | 0x20000000);
    D_0055C648->dma.id = 0x10;
    D_0055C648->dma.addr = 0;
    D_0055C648->dma.qwc = 6;
    D_0055C648->ad[0].d = (u64)0x9b80 << 33;
    D_0055C648->ad[1].d = 0;
    D_0055C648->ad[2].d = (16LL << 32) | 16;
    D_0055C648->img.b.nloop = 64;
    D_0055C648->ref.id = 0x30;
    D_0055C648->ref.addr = t->clut;
    D_0055C648->ref.qwc = 64;
    D_0055C648++;
    D_0055C648->dma.id = 0x10;
    D_0055C648->dma.addr = 0;
    D_0055C648->dma.qwc = 6;
    D_0055C648->ad[0].d = (u64)0x13043600 << 32;
    D_0055C648->img.b.nloop = t->n;
    D_0055C648->ad[1].d = 0;
    D_0055C648->ad[2].d = t->w | (u64)t->h << 32;
    D_0055C648->ref.id = 0x30;
    D_0055C648->ref.addr = t->data;
    D_0055C648->ref.qwc = t->n;
    D_0055C648++;
    D_0055C648->dma.id = 0x70;
    D_0055C648->dma.addr = 0;
    D_0055C648->dma.qwc = 0;
    __asm__ volatile("sync");
    D_0055C644->mod = 1;
    D_0055C644->asp = 0;
    D_0055C644->tte = 0;
    D_0055C644->tie = 0;
    __asm__ volatile("sync");
    func_00266f38(D_0055C644, D_00573AC0);
}
#undef D_0055C648

/* func_0015fc00 (from hand/nostrict/text_00150000_s6_08.c). */
typedef struct { u8 pad[0x48]; s8 x48; } O48;
typedef struct { O48 *o; u32 fl; } E10;
typedef struct { u8 pad[0x10]; E10 *e; } A0;
extern u8 D_00277E40[];
extern u8 D_00278210[];
extern void *D_00351BE0[];
void func_0015fc00(A0 *a) {
    E10 *e = a->e;
    s32 v;
    u32 fl;
    D_0055C640->dir = 1;
    D_0055C640->mod = 1;
    D_0055C640->asp = 0;
    D_0055C640->tte = 1;
    D_0055C640->tie = 0;
    __asm__ volatile("sync");
    fl = e->fl;
    v = e->o->x48;
    if (fl & 8) {
        if (v & 0x10) {
            func_00266f38(D_0055C640, D_00277E40);
            return;
        }
        func_00266f38(D_0055C640, D_00278210);
        return;
    }
    if (!((fl >> 4) & 2)) v &= ~4;
    if ((u8)((fl >> 4) & 1)) v |= 2; else v &= ~2;
    func_00266f38(D_0055C640, D_00351BE0[v]);
}

/* func_0015fd20 (from hand/nostrict/text_00150000_h59.c). */
#define QCOPY4(d, s) __asm__ volatile( \
    "lq $8, 0(%1)\n\tlq $9, 16(%1)\n\tlq $10, 32(%1)\n\tlq $11, 48(%1)\n\t" \
    "sq $8, 0(%0)\n\tsq $9, 16(%0)\n\tsq $10, 32(%0)\n\tsq $11, 48(%0)" \
    : : "r"(d), "r"(s) : "$8", "$9", "$10", "$11", "memory")
#define QCOPY7(d, s) __asm__ volatile( \
    "lq $8, 0(%1)\n\tlq $9, 16(%1)\n\tlq $10, 32(%1)\n\tlq $11, 48(%1)\n\t" \
    "sq $8, 0(%0)\n\tsq $9, 16(%0)\n\tsq $10, 32(%0)\n\tsq $11, 48(%0)\n\t" \
    "lq $9, 64(%1)\n\tlq $10, 80(%1)\n\tlq $11, 96(%1)\n\t" \
    "sq $9, 64(%0)\n\tsq $10, 80(%0)\n\tsq $11, 96(%0)" \
    : : "r"(d), "r"(s) : "$8", "$9", "$10", "$11", "memory")
u32 *func_0015fd20(u32 *p, u8 *src, s32 f1, s32 f2, s32 base) {
    p += 4;
    if (f2 & 2) {
        for (;;) {
            switch (p[0]) {
            case 0: {
                u32 i = p[1];
                p += 4;
                QCOPY4((u32)p | 0x20000000, (i + base) * 64 + (u32)src);
                p += 16;
                break;
            }
            case 1:
                p = (u32 *)((u8 *)p + p[1]);
                break;
            case 0x8000:
                if (p[1] == 0) goto done;
                p = (u32 *)((u8 *)p + p[1]);
                break;
            case 2:
                p = (u32 *)((u8 *)p + p[1]);
                break;
            }
        }
    } else if (f1 & 1) {
        for (;;) {
            switch (p[0]) {
            case 0: {
                u32 i = p[1];
                p += 4;
                QCOPY7((u32)p | 0x20000000, (i + base) * 128 + (u32)src);
                p += 28;
                break;
            }
            case 1:
                p = (u32 *)((u8 *)p + p[1]);
                break;
            case 0x8000:
                if (p[1] == 0) goto done;
                p = (u32 *)((u8 *)p + p[1]);
                break;
            case 2:
                p = (u32 *)((u8 *)p + p[1]);
                break;
            }
        }
    } else {
        for (;;) {
            switch (p[0]) {
            case 0: {
                u32 i = p[1];
                p += 4;
                QCOPY4((u32)p | 0x20000000, (i + base) * 64 + (u32)src);
                p += 28;
                break;
            }
            case 1:
                p = (u32 *)((u8 *)p + p[1]);
                break;
            case 0x8000:
                if (p[1] == 0) goto done;
                p = (u32 *)((u8 *)p + p[1]);
                break;
            case 2:
                p = (u32 *)((u8 *)p + p[1]);
                break;
            }
        }
    }
done:
    return p;
}
#undef QCOPY4
#undef QCOPY7

/* func_0015ff78 (from hand/nostrict/text_00140000_b04.c). */
typedef struct { u32 dir:1; u32 b1:1; u32 mod:2; u32 asp:2; u32 tte:1; u32 tie:1; u32 rest:24; } B4Chcr;
typedef struct { u8 pad[0x18]; s32 x18; } B4Rec2;
typedef struct { u32 x0; } B4X10;
typedef struct {
    u64 x0; u64 x8; B4X10 *x10; u32 x14; s32 x18; u8 pad1c[0x40 - 0x1c]; s32 (*x40)(B4Rq *, s32); s32 x44; s8 x48;
} B4Src2;
typedef struct { B4Src2 *x0; u8 x4; s8 x5; s8 x6; u8 x7; } B4Drw2;
typedef struct { u8 pad[0x10]; B4Drw2 *x10; u32 x14; } B4Dm;
typedef struct { u16 x0; u8 x2; u8 x3; s32 x4; u8 pad8[0x170 - 8]; u64 x170; u8 pad178[8]; u64 x180; } B4Gp;
extern u8 D_00351C40[];
#define CALLFD() do { B4Drw2 *t_ = d->x10; B4Src2 *u_ = t_->x0; func_0015fd20(((B4Rec2 *)(t_->x7 * 4 + u_->x14))->x18, u_->x10->x0, u_->x48, (u64)t_->x4 >> 4, u_->x18); } while (0)
extern u8 D_00573E40_0015ff78[] __asm__("D_00573E40");
#define D_00573E40 D_00573E40_0015ff78
#define D_0055C644 ((B4Chcr *) D_0055C644)
#define D_0055C640 ((B4Chcr *) D_0055C640)
#define func_0015f798 ((void (*)(B4Dm *)) func_0015f798)
#define func_0015fc00 ((void (*)(B4Dm *)) func_0015fc00)
#define func_0015fd20 ((s32 (*)(s32, u32, s32, u64, s32)) func_0015fd20)
#define func_00266f38 ((void (*)(B4Chcr *, void *)) func_00266f38)
#define func_0015f8c8 ((void (*)(B4Drw2 *, s32)) func_0015f8c8)
s32 func_0015ff78(B4Dm *d) {
    B4Drw2 *s;
    B4Drw2 *t;
    B4Gp *g;
    s32 r;
    u32 tb;
    u64 a;
    u64 b;
    u32 x;
    u32 st;
    __asm__ volatile("sync");
    r = 2;
    s = d->x10;
    switch (st = d->x14) {
    case 0:
        func_0015f798(d);
        d->x14 = 1; st = 1;
        break;
    case 1:
        func_0015fc00(d);
        if (!(s->x0->x48 & 4)) {
            d->x14 = 2; st = 2;
            break;
        }
        CALLFD();
        d->x14 = st = 4;
        break;
    case 2:
        if (*(u32 *)&s->x4 & 8) {
            b = s->x0->x0;
            a = s->x0->x8;
            __asm__ volatile("sync");
            g = (B4Gp *)((u32)D_00351C40 | 0x20000000);
            g->x180 = a;
            g->x3 = 112;
            g->x0 = 24;
            g->x170 = b;
            g->x4 = 0;
            __asm__ volatile("sync");
            D_0055C644->mod = 1;
            D_0055C644->asp = 0;
            D_0055C644->tte = 0;
            D_0055C644->tie = 0;
            __asm__ volatile("sync");
            func_00266f38(D_0055C644, D_00351C40);
        } else {
            D_0055C648 = (B4Pk *)((u32)D_00573AC0 | 0x20000000);
            func_0015f488((B4Drw *)s);
            func_0015f8c8(s, 0);
            D_0055C648->x3 = 96;
            D_0055C648->x4 = 0;
            D_0055C648->x0 = 0;
            __asm__ volatile("sync");
            D_0055C644->mod = 1;
            D_0055C644->asp = 0;
            D_0055C644->tte = 0;
            D_0055C644->tie = 0;
            __asm__ volatile("sync");
            func_00266f38(D_0055C644, D_00573E40);
        }
        CALLFD();
        if (s->x0->x40) { d->x14 = 3; st = 3; }
        else { d->x14 = 4; st = 4; }
        break;
    case 3:
        r = s->x0->x40(&D_0055C680, s->x0->x44);
        d->x14 = 4; st = 4;
        break;
    case 4:
        tb = s->x0->x14;
        D_0055C640->dir = 1;
        D_0055C640->mod = 1;
        D_0055C640->asp = 0;
        D_0055C640->tte = 1;
        D_0055C640->tie = 0;
        __asm__ volatile("sync");
        func_00266f38(D_0055C640, (void *)((B4Rec2 *)(((u8 *)s)[7] * 4 + tb))->x18);
        d->x14 = 5; st = 5;
        break;
    case 5:
        do {
            do {
                x = *(volatile u32 *)0x10003c00 & 0x1f000003;
            } while (x);
            __asm__ volatile("cfc2 %0, $vi29" : "=r"(x));
        } while (x & 0x100);
        r = 0;
        d->x14 = 6; st = 6;
        break;
    }
    return st != 5 ? r | 0x20 : r;
}
#undef D_00573E40
#undef D_0055C644
#undef D_0055C640
#undef func_0015f798
#undef func_0015fc00
#undef func_0015fd20
#undef func_00266f38
#undef func_0015f8c8
#undef CALLFD

