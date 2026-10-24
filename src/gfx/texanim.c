/* Texture animations (a guess at the name), 0x00101970-0x00102a48: frame
 * tasks (func_00101bb8, func_00102118) that step a texture's frames
 * (D_0029B420) and upload them, with their GS packets (func_00101fc8,
 * func_00102070) and the set ups func_00101e70 / func_00102978. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "data/pieces/D_002A624C.h"
#include "data/bss_0049.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_002A6274.h"
#include "data/types/text_00100000_h1.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002A3F50.h"
#include "data/pieces/D_002A6208.h"
#include "data/pieces/D_002A6C10.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_0048C6F0.h"
#include "m2c.h"
#include "data/pieces/D_002B75A0.h"
#include "data/types/text_00100000_s6_00.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002A4060.h"
#include "data/pieces/D_002A3F48.h"
#include "data/pieces/D_002A3F3C.h"
#include "data/pieces/D_002A3F30.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_0048CC30.h"
#include "data/types/text_00100000_s11_w3.h"
#include "data/pieces/D_0029B420.h"
#include "data/pieces/D_002B7590.h"
#include "data/pieces/D_002BBAA0.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "data/types/text_00100000_s11_w58.h"
#include "data/types/text_00100000_s11_w58_p.h"
#include "data/pieces/D_002A3E20.h"
#include "data/pieces/D_0037A378.h"
#include "data/types/text_00100000_h28.h"
#include "data/pieces/D_002BC0C0.h"
#include "data/pieces/D_002A6234.h"
#include "data/types/text_00100000_h28_p.h"
#include "data/pieces/D_002B1C60.h"
#include "data/pieces/D_002AA060.h"
#include "data/pieces/D_002A62B0.h"
#include "data/pieces/D_002A3F60.h"
#include "data/pieces/D_002A62D0.h"
#include "data/pieces/D_002BBDE4.h"
#include "data/bss_004D.h"

/* func_00101970 (from hand/text_00100000_h1.c). */
typedef struct { s32 a, b, c, d; } Q4;
typedef struct { Q4 h; s32 n, x, c, d; } DmaHdr;
extern u8 D_002A4160[];
extern u8 D_002A4180[];
/* DMA tag pair built by func_00101970. */
void func_00101970(s32 sel, DmaHdr *q, s32 x) {
    Q4 *q1 = (Q4 *)&q->n;
    q1->d = 0;
    q1->c = 0;
    q->h.d = 0;
    q->h.c = 0;
    if (sel == 0) {
        q->h.a = 0x30000002;
        q->h.b = (s32)D_002A4160;
        q1->a = 4;
    } else {
        q->h.a = 0x30000002;
        q->h.b = (s32)D_002A4180;
        q1->a = 8;
    }
    q->x = x;
}

/* func_001019c8 (from auto/text_00100000_13.c). */
extern s32 D_002A6B84;
void func_00121eb0(s32);
void func_00266f38(s32, s32);
void iFlushCache(M2C_UNK);
s32 func_001019c8(void *arg0) {
    iFlushCache(0);
    func_00266f38(D_002A6B84, M2C_FIELD(arg0, s32 *, 0x10));
    func_00121eb0(M2C_FIELD(arg0, s32 *, 0x10));
    func_00121eb0(M2C_FIELD(arg0, s32 *, 0x14));
    return 2;
}

/* func_00101a18 (from hand/text_00100000_s6_00.c). */
typedef struct { u8 pad0[4]; s32 w4; u8 pad8[8]; u64 q10; u64 q18; s32 arr[8]; u8 pad40[0x60]; } Tex_01a18;
typedef struct { s32 lo; s32 hi; } W2;
typedef union { u64 d; W2 w; } Q;
void func_00101a18(Tex_01a18 *t, u8 k, Q *q) {
/*P*/
    q[0].d = t->q10;
    q[1].d = 0x50;
    q[2].w.lo = t->arr[k];
    q[2].w.hi = t->w4;
    q[3].d = 0x51;
    q[4].d = t->q18;
    q[5].d = 0x52;
    q[6].d = 2;
    q[7].d = 0x53;
/*Q*/
}

/* func_00101bb8 (from hand/text_00100000_s11_w3.c). */
typedef struct { u8 pad[0x10]; union { f32 f10; void *p10; } u10; union { f32 f14; void *p14; } u14; } Obj10;
typedef struct { u8 pad[0x10]; u8 state; u8 idx; u16 prev; u16 frame; u16 max; f32 t; } Anim;
extern f32 D_002BBDFC;
s32 D_004945F0 ALIGNED(16);
Obj10 *func_0015ed80(s32, void (*)(void));
void *func_00121e28(s32, void *);
void func_00101a70(Tex *, u16, u16, void *);
#define func_00101a18 ((void (*)(Tex *, u8, void *)) func_00101a18)
#define func_00101970 ((void (*)(s32, void *, void *)) func_00101970)
s32 func_00101bb8(Anim *o) {
    Obj10 *h;
    void *a, *b;
    switch (o->state) {
    case 0: {
        Tex *x = &D_0029B420[o->idx];
        o->prev = 1;
        o->frame = 0;
        o->t = 0;
        o->max = x->n;
        o->state++;
        break; }
    case 1:
        o->t += D_002BBDFC / D_0029B420[o->idx].spd;
        o->frame = o->t * 0.5f;
        if (o->frame >= o->max) {
            o->frame = 0;
            o->t = 0;
        }
        break;
    }
    switch (D_0029B420[o->idx].type) {
    case 0:
        if (o->frame != o->prev) {
            h = func_0015ed80(D_004945F0++ + 10000, func_001019c8);
            a = func_00121e28(32, &h->u10);
            b = func_00121e28(64, &h->u14);
            h->u10.p10 = a;
            h->u14.p14 = b;
            func_00101a18(&D_0029B420[o->idx], o->frame, b);
            func_00101970(0, a, b);
        }
        break;
    case 1:
    case 2:
        if (o->frame != o->prev) {
            h = func_0015ed80(D_004945F0++ + 10000, func_001019c8);
            a = func_00121e28(32, &h->u10);
            b = func_00121e28(128, &h->u14);
            h->u10.p10 = a;
            h->u14.p14 = b;
            func_00101a70(&D_0029B420[o->idx], o->frame, o->max, b);
            func_00101970(1, a, b);
        }
        break;
    }
    o->prev = o->frame;
    return 0;
}
#undef func_00101a18
#undef func_00101970

/* func_00101e70 (from hand/text_00100000_h1.c). */
typedef struct { u8 pad[16]; u8 b16; u8 b17; } Obj;
extern s32 D_002A3F20;
u8 D_00494420[0x1c0] ALIGNED(32);
extern u8 D_004945E0[];
void func_0011efa8(void *, void *, s32, s32);
void *func_0011f090(void *, s32, void *);
void func_00101e70(void) {
    s32 i;
    func_0011efa8(D_004945E0, D_00494420, 28, 16);
    for (i = 0; i < D_002A3F20; i++) {
        Obj *o = func_0011f090(D_004945E0, 120000, func_00101bb8);
        if (o) {
            o->b16 = 0;
            o->b17 = i;
        }
    }
}

/* func_00101f10 (from auto/text_00100000_9.c). */
M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
#define D_004945E0 (*(M2C_UNK (*)) &D_004945E0)
void func_00101f10(void) {
    func_0011f130(&D_004945E0, 0);
}
#undef D_004945E0

/* func_00101f30 (from auto/text_00100000_13.c). */
s32 func_00101f30(void *arg0) {
    iFlushCache(0);
    func_00266f38(D_002A6B84, M2C_FIELD(arg0, s32 *, 0x10));
    func_00121eb0(M2C_FIELD(arg0, s32 *, 0x10));
    func_00121eb0(M2C_FIELD(arg0, s32 *, 0x14));
    return 2;
}

/* func_00101f80 (from auto/text_00100000_13.c). */
s32 func_00101f80(void *arg0) {
    iFlushCache(0);
    func_00266f38(D_002A6B84, M2C_FIELD(arg0, s32 *, 0x10));
    func_00121eb0(M2C_FIELD(arg0, s32 *, 0x10));
    return 2;
}

/* func_00101fc8 (from hand/text_00100000_s6_00.c). */
static inline u64 xyz(s32 x, s32 y) {
    x = x * 16 + 0x7000;
    y = y * 16 + 0x7400;
    return (u64)x | ((u64)y << 16) | 0xFFFFFFFE00000000;
}
void func_00101fc8(s32 a, s32 b, s32 x, s32 y, u64 *p) {
    p[0] = 0x6420000000008001;
    p[1] = 0x535310;
    p[2] = ((u64)a << 6) | 0x116;
    p[3] = ((u64)b << 24) | 0x100808080;
    p[4] = 0;
    p[5] = xyz(x, y);
    p[6] = 0x200080;
    p[7] = xyz(x + 8, y + 2);
}

/* func_00102070 (from hand/text_00100000_s6_00.c). */
void func_00102070(s32 a, s32 b, s32 x, s32 y, u64 *p) {
    p[0] = 0x6420000000008001;
    p[1] = 0x535310;
    p[2] = ((u64)a << 6) | 0x116;
    p[3] = ((u64)b << 24) | 0x100808080;
    p[4] = 0;
    p[5] = xyz(x, y);
    p[6] = 0x1000100;
    p[7] = xyz(x + 16, y + 16);
}

/* func_00102118 (from hand/text_00100000_s11_w58.c). */
typedef struct { u8 pad[0x10]; struct { f32 f10; } u10; struct { f32 f14; } u14; f32 f18; u8 state, id, idx, last; s32 *p20, *p24; } Task2;
typedef struct { u8 pad[0x10]; union { f32 f10; void *p10; } u10; union { f32 f14; void *p14; } u14; } Obj_02118;
typedef struct { s32 a, b, c, d; } Hdr;
typedef struct { s32 w[9]; s32 *p24; s32 w2[2]; } Buf48;
void func_00106bd8(void *, s32);
extern s32 D_0029BE20[][32][16];
extern f32 D_003732D0[];
extern s32 D_002A45D0[];
extern s32 D_002A4650[];
extern B48 D_002A4230;
extern B48 D_002A4430;
extern B48 D_002A4400;
extern B48 D_002A4260;
extern u8 D_002A4310[];
extern u8 D_002A43A0[];
extern u8 D_002A44E0[];
extern u8 D_002A4570[];
extern u8 D_002A45C0[];
#define func_0015ed80 ((Obj_02118 *(*)(s32, s32 (*)(void *))) func_0015ed80)
/* func_00102118 (hand). FLAGGED DEAD CODE: `x = (s32)t;` at entry and `if (x != (s32)t) h = 0;` /
   `if (x < (s32)t) h = 0;` right after `hh = h;` in the two conversion join blocks (never true;
   gcse cprop turns x into t, cse2 folds the test, jump deletes the arm before life1). They keep
   the gcse copy `hh = h` (the original's `move s0,s3` in the bnez slot); the two tests must differ.
   Section 2: `{ s32 four = 4; do { } while (0); hh->a = four; }` makes the hh->a store the sched1
   barrier insn (first insn after the loop notes), so h->b and the a1 argument issue together. */
s32 func_00102118(Task2 *t) {
    s32 k, v;
    u32 u;
    s32 a, b;
    Obj_02118 *o;
    Hdr *h;
    void *buf;
    Buf48 *bb;
    Hdr *hh; s32 x; s32 (*fn)(void *);

    x = (s32)t;
    switch (t->state) {
    case 0:
        t->u14.f14 = 0.0f;
        t->f18 = 4096.0f / ((f32)D_002A3E20[t->id].a * 2.0f);
        t->state = 1;
        t->last = D_002A3E20[t->id].c;
        if (D_002A3E20[t->id].d == 0) {
            t->p20 = D_0029BE20[t->id][t->idx - 1];
            t->p24 = D_0029BE20[t->id][t->idx];
        } else {
            t->p20 = D_0029BE20[t->id][0];
            t->p24 = D_0029BE20[t->id][16];
        }
    case 1:
        t->u10.f10 = D_003732D0[((s32)(t->u14.f14 * t->f18) + 0xc00) & 0xfff] * 64.0f + 64.0f;
        if (t->u10.f10 > 127.0f) {
            if (t->idx == t->last) {
                t->state = 2;
            } else {
                t->state = 0;
                t->idx++;
            }
        } else {
            t->u14.f14 += D_002BBDFC;
        }
        break;
    case 2:
        t->state++;
        t->u14.f14 = 0.0f;
        if (D_002A3E20[t->id].d == 0) {
            t->p20 = D_0029BE20[t->id][t->idx - 1];
            t->p24 = D_0029BE20[t->id][t->idx];
        } else {
            t->p20 = D_0029BE20[t->id][0];
            t->p24 = D_0029BE20[t->id][16];
        }
    case 3:
        t->u10.f10 = D_003732D0[((s32)(t->u14.f14 * t->f18) + 0x400) & 0xfff] * 64.0f + 64.0f;
        if (t->u10.f10 < 1.0f) {
            if (t->idx == 1) {
                t->state = 0;
            } else {
                t->state = 2;
                t->idx--;
            }
        } else {
            t->u14.f14 += D_002BBDFC;
        }
        break;
    }
    k = t->id * 10;
    o = func_0015ed80(0x15f92 + k, func_00101f30);
    h = func_00121e28(16, &o->u10.p10);
    if (D_002A3E20[t->id].d == 0) {
        buf = func_00121e28(64, &o->u14.p14);
    } else {
        buf = func_00121e28(64, &o->u14.p14);
    }
    o->u10.p10 = h;
    v = D_002A3E20[t->id].b;
    a = D_002A45D0[v % 32];
    b = D_002A4650[v % 32] + v / 32 * 32;
    u = 129.0f - t->u10.f10;
    hh = h; if (x != (s32)t) h = 0;
    if (D_002A3E20[t->id].d == 0) {
        func_00101fc8(0, u, a, b, buf);
    } else {
        func_00102070(0, u, a, b, buf);
    }
    hh->a = 4;
    h->b = (s32)buf;
    do { } while (0);
    fn = func_00101f80;
    h->c = 0;
    h->d = 0;
    o = func_0015ed80(0x15f90 + k, fn);
    bb = func_00121e28(48, &o->u10.p10);
    o->u10.p10 = bb;
    if (D_002A3E20[t->id].d == 0) {
        *(B48 *)bb = D_002A4230;
    } else {
        *(B48 *)bb = D_002A4400;
    }
    bb->p24 = t->p20;
    if (D_002A3E20[t->id].d == 0) {
        func_00106bd8(D_002A4310, 0x15f91 + k);
    } else {
        func_00106bd8(D_002A44E0, 0x15f91 + k);
    }
    o = func_0015ed80(0x15f95 + k, func_00101f30);
    h = func_00121e28(16, &o->u10.p10);
    if (D_002A3E20[t->id].d == 0) {
        buf = func_00121e28(64, &o->u14.p14);
    } else {
        buf = func_00121e28(64, &o->u14.p14);
    }
    o->u10.p10 = h;
    u = t->u10.f10 + 1.0f;
    hh = h; if (x < (s32)t) h = 0;
    if (D_002A3E20[t->id].d == 0) {
        func_00101fc8(1, u, a, b, buf);
    } else {
        func_00102070(1, u, a, b, buf);
    }
    { s32 four = 4; do { } while (0); hh->a = four; }
    h->b = (s32)buf;
    h->c = 0;
    h->d = 0;
    o = func_0015ed80(0x15f93 + k, func_00101f80);
    bb = func_00121e28(48, &o->u10.p10);
    o->u10.p10 = bb;
    if (D_002A3E20[t->id].d == 0) {
        *(B48 *)bb = D_002A4260;
    } else {
        *(B48 *)bb = D_002A4430;
    }
    bb->p24 = t->p24;
    if (D_002A3E20[t->id].d == 0) {
        func_00106bd8(D_002A43A0, 0x15f94 + k);
    } else {
        func_00106bd8(D_002A4570, 0x15f94 + k);
    }
    func_00106bd8(D_002A45C0, 0x15f96 + k);
    return 0;
}
#undef func_0015ed80

/* func_00102978 (from hand/text_00100000_h28.c). */
typedef struct { u8 pad[0x10]; f32 f10, f14; u8 pad18[4]; u8 b1c, b1d, b1e; } Task;
extern s32 D_002A3F24;
u8 D_004945F8[0x280] ALIGNED(8);
extern u8 D_00494878[];
#define func_0011f090 ((Task *(*)(void *, s32, void (*)(void))) func_0011f090)
void func_00102978(void) {
    s32 i;
    Task *t;
    func_0011efa8(D_00494878, D_004945F8, 40, 16);
    for (i = 0; i < D_002A3F24; i++) {
        t = func_0011f090(D_00494878, 120000, func_00102118);
        if (t != NULL) {
            t->b1c = 0;
            t->b1d = i;
            t->b1e = 1;
        }
    }
}
#undef func_0011f090

/* func_00102a28 (from auto/text_00100000.c). */
#define D_00494878 (*(M2C_UNK (*)) &D_00494878)
void func_00102a28(void) {
    func_0011f130(&D_00494878, 0);
}
#undef D_00494878

