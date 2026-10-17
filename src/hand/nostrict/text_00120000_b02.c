#include "common.h"

/* needs make: uses rodata */
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
