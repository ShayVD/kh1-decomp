/* func_00102118: 9 words off by position, 6 by LCS (was 28/17), mode hand. New: t (Task2) has plain f32 fields (struct { f32 f10; } u10 etc.), only Obj keeps the f32/void* unions: a direct union-member access has alias set 0, so t->u14.f14 = 0 conflicted with the D_002A3E20 loads in cases 0/2 (fixes both case blocks). Plus a compiled-out do{}while(0) between h->c and h->d. Left: hh->a = 4 goes through hh = o->u10.p10 (lw s0,16(s0)); the original has move s0,s3 (a copy of h that survives gcse cprop) in the bnez slot, and the c/d store vs lui/addiu order at the two joins follows from it. Not found: o2 copies, store after the conversion, hand-written u32 conversion, hh = h. */
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
    Hdr *hh;

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
    hh = o->u10.p10;
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
