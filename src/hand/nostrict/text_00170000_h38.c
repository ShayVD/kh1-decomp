/* Hand-matched functions, 0x001742b0..0x00176ba8 (worker 38) that need
 * -fno-strict-aliasing. The rest are in ../text_00170000_h38.c. */
#include "common.h"

typedef struct { f32 x, y, z; } V3;

/* --- actor state handlers (Wk = owner, Ob = actor) --- */
typedef struct Prm {
    s32 x0;         /* 0x00 */
    u8 pad4[0x10];
    f32 x14;        /* 0x14 */
    f32 x18;        /* 0x18 */
    f32 x1c;        /* 0x1C */
    f32 x20;        /* 0x20 */
} Prm;
typedef struct { u8 pad[0xc]; Prm *xc; } P160;

typedef struct Ob {
    u8 pad0[0x38];
    u64 flags;      /* 0x38 */
    void *x40;      /* 0x40 */
    u8 pad44[4];
    s32 x48;        /* 0x48 */
    s32 x4c;        /* 0x4C */
    u8 pad50[0x68 - 0x50];
    f32 x68;        /* 0x68 */
    u8 pad6c[0x90 - 0x6c];
    s32 x90;        /* 0x90 */
    u8 pad94[0xc0 - 0x94];
    V3 xc0;         /* 0xC0 */
    u8 padcc[0x120 - 0xcc];
    f32 x120, x124, x128, x12c; /* 0x120 */
    u8 pad130[0x160 - 0x130];
    P160 *x160;     /* 0x160 */
    s32 x164;       /* 0x164: sub-state */
} Ob;

typedef struct Wk {
    u8 pad0[0x160];
    s32 x160;       /* 0x160 */
    s32 x164;       /* 0x164 */
} Wk;

s32 func_00171118(s32, s32);
void func_00171790(Wk *, Ob *);
void func_00130340(Wk *, s32, f32);
void func_00267e90(f32, f32 *, V3 *);
f32 func_00162c20(f32 *);

void func_001742b0(Wk *w, Ob *o) {
    f32 v[3];
    Prm *q = o->x160->xc;
    if (!func_00171118(o->x90, -1)) {
        o->x48 = 0;
        return;
    }
    o->flags |= 0x100000;
    func_00171790(w, o);
    if (o->x164 == 0) return;
    if (o->x164 != 1) return;
    if (o->x68 < 0.0f) o->x48 = 0;
    o->flags |= 0x1000;
    func_00267e90(q->x20, v, &o->xc0);
    o->x124 = v[1];
    v[1] = 0.0f;
    o->x12c = func_00162c20(v);
    o->x120 = v[0];
    o->x128 = v[2];
}

s32 func_00174b90(Wk *w, Ob *o, s32 a2) {
    s32 r = 0;
    switch (a2) {
    case 1:
        switch (o->x164) {
        case 0:
            if (!(w->x160 & 1)) {
                if (w->x164 != 202) r = 1;
            }
            break;
        case 1:
            if (!(w->x160 & 1)) {
                if (w->x164 != o->x4c) r = 1;
            }
            break;
        }
        break;
    case 2:
        r = o->x48 == 0;
        break;
    }
    if (r == 1) {
        o->x48 = 0;
        o->flags &= ~0x800;
        o->flags &= ~0x200;
        o->flags |= 0x20000;
        if (w->x164 == 202 || w->x164 == o->x4c) func_00130340(w, 0x40000075, 8.0f);
    }
    return r;
}

void func_00174ca8(Wk *w, Ob *o) {
    f32 v[3];
    Prm *q = o->x160->xc;
    if (!func_00171118(o->x90, -1)) {
        o->x48 = 0;
        return;
    }
    o->flags |= 0x100000;
    func_00171790(w, o);
    if (o->x164 == 0) return;
    if (o->x164 != 1) return;
    if (o->x68 < 0.0f) o->x48 = 0;
    o->flags |= 0x1000;
    o->flags |= 0x200;
    func_00267e90(q->x20, v, &o->xc0);
    o->x124 = v[1];
    v[1] = 0.0f;
    o->x12c = func_00162c20(v);
    o->x120 = v[0];
    o->x128 = v[2];
}

/* --- GS packets --- */
typedef struct { s32 a, b, c, d; } V16;
typedef struct { u64 a, b; } Q16;
typedef struct Pkt {
    u16 x0;
    u8 x2;
    u8 x3;
    s32 x4;
    u8 pad8[0x68 - 8];
    u64 x68;
    u8 pad70[8];
    u64 x78;
    u8 pad80[0xf0 - 0x80];
    u64 xf0;
    u8 padf8[8];
    u64 x100;
} Pkt;
typedef struct { u64 *x0; } P10;
typedef struct Spr {
    u8 pad0[0xa];
    u16 xa;
    u8 padc[4];
    P10 *x10;
} Spr;
typedef struct { s32 a, b; u8 *c; u8 *d; } Hd16;
typedef struct Fil {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xc;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1c;
    s32 x20;
} Fil;
typedef struct { s32 x0; s32 x4; s32 x8; s32 xc; } Sub;

extern Q16 D_0035C430;
extern Q16 D_0035C450;
extern Pkt D_0035C4A0;
extern Pkt D_0035C550;
Hd16 D_005757A0 ALIGNED(16);
V16 D_00575790 ALIGNED(16);
extern s32 D_0035C420;
extern u8 *D_0035C424;
extern s32 D_0035C428;
extern u8 *D_0035C42C;
extern u8 D_0035C440[];
extern u8 D_0035C460[];
extern u8 D_0035C490[];

s32 func_00266c08(s32);
void func_00266f38(s32, Pkt *);
s32 sceGsSyncPath(s32, s32);
void func_0015fa20(void *);
void func_001623f8(void *, s32, V16 *);
void func_002675a8(void *, void *);

s32 func_00175600(Spr *s) {
    Pkt *p;
    if ((u16)(s->xa - 3) >= 2) return 0;
    func_00266f38(func_00266c08(2), &D_0035C4A0);
    p = (Pkt *)((u32)&D_0035C550 | 0x20000000);
    if (s->xa == 4) {
        p->x68 = D_0035C430.a;
        p->x78 = D_0035C430.b;
    } else {
        p->x68 = D_0035C450.a;
        p->x78 = D_0035C450.b;
    }
    p->xf0 = s->x10->x0[0];
    p->x100 = s->x10->x0[1];
    sceGsSyncPath(0, 0);
    func_0015fa20(&D_005757A0);
    sceGsSyncPath(0, 0);
    func_00266f38(func_00266c08(2), &D_0035C550);
    return 0;
}

void func_00175708(void *a0, Fil *f) {
    Sub *s;
    D_005757A0 = *(Hd16 *)((u8 *)f + f->x8);
    D_005757A0.c = (u8 *)f + f->x10;
    D_005757A0.d = (u8 *)f + f->x18;
    s = (Sub *)((u8 *)f + f->x20);
    D_0035C420 = s->x0;
    D_0035C424 = (u8 *)s + s->x4;
    D_0035C428 = s->x8;
    D_0035C42C = (u8 *)s + s->xc;
    func_001623f8(a0, 16, &D_00575790);
    func_002675a8(D_0035C440, D_0035C490);
    func_002675a8(D_0035C460, D_0035C490);
    D_0035C4A0.x0 = 10;
    D_0035C550.x0 = 16;
    D_0035C550.x4 = 0;
    D_0035C550.x3 = 112;
    D_0035C4A0.x3 = 112;
    D_0035C4A0.x4 = 0;
}

/* --- 44-byte records at D_005757B0 built from a type-20 header --- */
typedef struct { s32 type; s32 x4; s32 off[2]; s32 x10[2]; } H20;
typedef struct { u8 *a; u8 *b; s32 c; s32 d; s32 e; } E20;
typedef struct { H20 *h; E20 e[2]; } S44;
extern S44 D_005757B0[]; /* src/data/bss_0057.c: T44 D_005757B0[0x2] */
void *memset(void *, s32, u32);

void func_00176ba8(H20 *h, s32 i) {
    S44 *s;
    s32 j;
    E20 *e;
    if (h->type != 20) return;
    s = &D_005757B0[i];
    memset(s, 0, 44);
    s->h = h;
    for (j = 0, e = s->e; j < 2; j++, e++) {
        e->a = e->b = (u8 *)(h->off[j] + (s32)h);
        e->c = h->x10[j];
        e->d = 0;
        e->e = 0;
    }
}
#include "data/data_0035.h"
