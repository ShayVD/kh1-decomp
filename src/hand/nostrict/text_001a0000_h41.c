#include "common.h"

/* ---- func_001a8780 ---- */
typedef struct { s32 w[4]; } Q4;
typedef struct Hdr8 {
    s32 w0, w4, w8, wc;
    struct Hdr8 *self; s32 w14; s32 w18; s16 h1c; u8 b1e; u8 p1f;
    s16 h20; u8 p22; u8 b23; u8 p24[4]; s32 w28; u8 p2c[8];
    s16 h34; u8 b36; u8 b37; s16 h38; u8 p3a[2]; s16 h3c; s16 h3e;
    u8 p40[12]; f32 f4c; u8 p50[8]; s32 w58;
} Hdr8;
typedef struct { Hdr8 *h; u8 n; } Bld8;

void func_001a8780(Bld8 *b) {
    Hdr8 *h = b->h;
    Q4 *q;
    h->h3e = 0;
    h->self = h;
    h->b37 = b->n;
    h->f4c = 1.0f;
    h->w18 = 0;
    h->h34 = 0;
    h->b36 = 0;
    h->h3c = 0;
    h->h38 = 0;
    h->b23 = 112;
    q = (Q4 *)h->p40 + h->b37 * 3;
    h->h20 = h->b37 * 3 + 2;
    h->b1e = 0;
    h->w14 = 0;
    h->w28 = 0x040000B0;
    h->w4 = 0;
    h->w0 = 0;
    h->wc = 0;
    h->w8 = 0;
    h->w58 = 0;
    h->h1c = 0;
    q->w[1] = 0x11000000;
    q->w[3] = 0x11000000;
    q->w[2] = 0x14000000;
    q->w[0] = 0;
}

/* ---- func_001a8c40 ---- */
typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct Nd { struct Nd *next; } Nd;
typedef union { u128 q; struct { u16 qwc; u8 b2; u8 id; } s; } Tag;
typedef struct { s32 a; Nd *n; u8 *end; s32 c; s32 b; u64 *flag; s64 d; s64 e; } Ctx;
s32 func_00266c08(s32);
s32 sceGsSyncPath(s32, s32);
void FlushCache(s32);
void func_00266f38(s32, void *);
s32 func_001a7718(Ctx *);

void func_001a8c40(Nd **list, s32 a, s32 b, s32 c, u8 **buf, s64 d, s64 e) {
    Ctx x;
    s32 ch = func_00266c08(2);
    Nd *n = *list;
    Tag *t;
    x.c = c;
    x.a = a;
    x.b = b;
    x.d = d;
    x.e = e;
    sceGsSyncPath(0, 0);
    for (; n; n = n->next) {
        x.n = n;
        x.end = *buf + 16;
        if (func_001a7718(&x)) {
            t = (Tag *)*buf;
            t->q = 0;
            t->s.id = 0x70;
            *x.flag |= 0x8000;
            t->s.qwc = (u32)(x.end - *buf) / 16 - 1;
            FlushCache(0);
            func_00266f38(ch, t);
            sceGsSyncPath(0, 0);
        }
    }
}
