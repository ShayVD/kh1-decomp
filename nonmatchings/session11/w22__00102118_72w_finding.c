/* func_00102118 FINDING, 72 LCS words (best stays s10 w9 6w), mode hand. Section 1 only: hand-written if-then u32 conversion `u = (s32)f; if (f >= 2^31) u = (s32)(f - 2^31) | 0x80000000;` plus `o2 = o;` after the first func_0015ed80 call and `hh = o2->u10.p10;` after the conversion. This DOES produce the original `move s0,s3` in the bnez slot of the conversion join block: cse2 (after gcse cprop o2->o) skips the then-arm (cse skip_blocks, no else) and turns the load into a copy of h that no later pass propagates. But cse1 then also carries the D_002A3E20[t->id] address across the join (orig recomputes lui/sll/addiu/addu there), so the builtin diamond is right for the address and wrong for the copy. Also: `h->d = 0; do { } while (0); h->c = 0;` gives the original d-before-c store order (6w, a different 6). Dead ends (each 6-22w): hh = h anywhere (cprop pass 1 replaces even a store address), copies/loads in both call arms, inline helpers (sethdr / whole draw with the arms), volatile hh->a, -fno-gcse (215). */
#include "common.h"

typedef struct { s32 w[12]; } B48;
typedef struct { u8 pad[0x10]; struct { f32 f10; } u10; struct { f32 f14; } u14; f32 f18; u8 state, id, idx, last; s32 *p20, *p24; } Task2;
typedef struct { u8 pad[0x10]; union { f32 f10; void *p10; } u10; union { f32 f14; void *p14; } u14; } Obj;
typedef struct { s32 a, b, c, d; } Hdr;
typedef struct { s32 w[9]; s32 *p24; s32 w2[2]; } Buf48;

Obj *func_0015ed80(s32, s32 (*)(void *));
void *func_00121e28(s32, void *);
s32 func_00101f30(void *);
s32 func_00101f80(void *);
void func_00106bd8(void *, s32);

extern s32 D_0029BE20[][32][16];
typedef struct { s32 a, b, c, d; } Cfg;
extern Cfg D_002A3E20[];
extern f32 D_003732D0[];
extern f32 D_002BBDFC;
extern s32 D_002A45D0[];
extern s32 D_002A4650[];
extern B48 D_002A4230, D_002A4260, D_002A4400, D_002A4430;
extern u8 D_002A4310[], D_002A43A0[], D_002A44E0[], D_002A4570[], D_002A45C0[];

static inline u64 xyz(s32 x, s32 y) {
    x = x * 16 + 0x7000;
    y = y * 16 + 0x7400;
    return (u64)x | ((u64)y << 16) | 0xFFFFFFFE00000000;
}
CONTEXT_ONLY void func_00101fc8(s32 a, s32 b, s32 x, s32 y, u64 *p) {
    p[0] = 0x6420000000008001;
    p[1] = 0x535310;
    p[2] = ((u64)a << 6) | 0x116;
    p[3] = ((u64)b << 24) | 0x100808080;
    p[4] = 0;
    p[5] = xyz(x, y);
    p[6] = 0x200080;
    p[7] = xyz(x + 8, y + 2);
}

CONTEXT_ONLY void func_00102070(s32 a, s32 b, s32 x, s32 y, u64 *p) {
    p[0] = 0x6420000000008001;
    p[1] = 0x535310;
    p[2] = ((u64)a << 6) | 0x116;
    p[3] = ((u64)b << 24) | 0x100808080;
    p[4] = 0;
    p[5] = xyz(x, y);
    p[6] = 0x1000100;
    p[7] = xyz(x + 16, y + 16);
}


s32 func_00102118(Task2 *t) {
    s32 k, v;
    u32 u;
    s32 a, b;
    Obj *o;
    Hdr *h;
    void *buf;
    Buf48 *bb;
    Hdr *hh; Obj *o2;

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
    o2 = o;
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
    { f32 f = 129.0f - t->u10.f10; u = (s32)f; if (f >= 2147483648.0f) u = (s32)(f - 2147483648.0f) | 0x80000000; }
    hh = o2->u10.p10;
    if (D_002A3E20[t->id].d == 0) {
        func_00101fc8(0, u, a, b, buf);
    } else {
        func_00102070(0, u, a, b, buf);
    }
    hh->a = 4;
    h->b = (s32)buf;
    h->c = 0;
    do { } while (0);
    h->d = 0;
    o = func_0015ed80(0x15f90 + k, func_00101f80);
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
    hh = o->u10.p10;
    if (D_002A3E20[t->id].d == 0) {
        func_00101fc8(1, u, a, b, buf);
    } else {
        func_00102070(1, u, a, b, buf);
    }
    hh->a = 4;
    h->b = (s32)buf;
    h->c = 0;
    do { } while (0);
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
