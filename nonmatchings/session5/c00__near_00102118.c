#include "common.h"

typedef struct { s32 w[12]; } B48;
typedef struct { u8 pad[0x10]; f32 f10, f14, f18; u8 state, id, idx, last; s32 *p20, *p24; } Task2;
typedef struct { u8 pad[0x10]; void *p10; void *p14; } Obj;
typedef struct { s32 a, b, c, d; } Hdr;
typedef struct { s32 w[9]; s32 *p24; s32 w2[2]; } Buf48;

Obj *func_0015ed80(s32, s32 (*)(void *));
void *func_00121e28(s32, void *);
s32 func_00101f30(void *);
s32 func_00101f80(void *);
void func_00101fc8(s32, u32, s32, s32, void *);
void func_00102070(s32, u32, s32, s32, void *);
void func_00106bd8(void *, s32);

extern s32 D_0029BE20[][32][16];
extern s32 D_002A3E20[][4];
extern f32 D_003732D0[];
extern f32 D_002BBDFC;
extern s32 D_002A45D0[];
extern s32 D_002A4650[];
extern B48 D_002A4230, D_002A4260, D_002A4400, D_002A4430;
extern u8 D_002A4310[], D_002A43A0[], D_002A44E0[], D_002A4570[], D_002A45C0[];

s32 func_00102118(Task2 *t) {
    s32 k, v;
    u32 u;
    s32 a, b;
    Obj *o;
    Hdr *h;
    void *buf;
    Buf48 *bb;

    switch (t->state) {
    case 0:
        t->f14 = 0.0f;
        t->state = 1;
        t->last = D_002A3E20[t->id][2];
        t->f18 = 4096.0f / ((f32)D_002A3E20[t->id][0] * 2.0f);
        if (D_002A3E20[t->id][3] == 0) {
            t->p20 = D_0029BE20[t->id][t->idx - 1];
            t->p24 = D_0029BE20[t->id][t->idx];
        } else {
            t->p20 = D_0029BE20[t->id][0];
            t->p24 = D_0029BE20[t->id][16];
        }
    case 1:
        t->f10 = D_003732D0[((s32)(t->f14 * t->f18) + 0xc00) & 0xfff] * 64.0f + 64.0f;
        if (t->f10 > 127.0f) {
            if (t->idx == t->last) {
                t->state = 2;
            } else {
                t->state = 0;
                t->idx++;
            }
        } else {
            t->f14 += D_002BBDFC;
        }
        break;
    case 2:
        t->state = 3;
        t->f14 = 0.0f;
        if (D_002A3E20[t->id][3] == 0) {
            t->p20 = D_0029BE20[t->id][t->idx - 1];
            t->p24 = D_0029BE20[t->id][t->idx];
        } else {
            t->p20 = D_0029BE20[t->id][0];
            t->p24 = D_0029BE20[t->id][16];
        }
    case 3:
        t->f10 = D_003732D0[((s32)(t->f14 * t->f18) + 0x400) & 0xfff] * 64.0f + 64.0f;
        if (t->f10 < 1.0f) {
            if (t->idx == 1) {
                t->state = 0;
            } else {
                t->state = 2;
                t->idx--;
            }
        } else {
            t->f14 += D_002BBDFC;
        }
        break;
    }
    k = t->id * 10;
    o = func_0015ed80(0x15f92 + k, func_00101f30);
    h = func_00121e28(16, &o->p10);
    if (D_002A3E20[t->id][3] == 0) {
        buf = func_00121e28(64, &o->p14);
    } else {
        buf = func_00121e28(64, &o->p14);
    }
    o->p10 = h;
    u = 129.0f - t->f10;
    v = D_002A3E20[t->id][1];
    a = D_002A45D0[v % 32];
    b = D_002A4650[v % 32] + v / 32 * 32;
    if (D_002A3E20[t->id][3] == 0) {
        func_00101fc8(0, u, a, b, buf);
    } else {
        func_00102070(0, u, a, b, buf);
    }
    h->a = 4;
    h->b = (s32)buf;
    h->c = 0;
    h->d = 0;
    o = func_0015ed80(0x15f90 + k, func_00101f80);
    bb = func_00121e28(48, &o->p10);
    o->p10 = bb;
    if (D_002A3E20[t->id][3] == 0) {
        *(B48 *)bb = D_002A4230;
    } else {
        *(B48 *)bb = D_002A4400;
    }
    bb->p24 = t->p20;
    if (D_002A3E20[t->id][3] == 0) {
        func_00106bd8(D_002A4310, 0x15f91 + k);
    } else {
        func_00106bd8(D_002A44E0, 0x15f91 + k);
    }
    o = func_0015ed80(0x15f95 + k, func_00101f30);
    h = func_00121e28(16, &o->p10);
    if (D_002A3E20[t->id][3] == 0) {
        buf = func_00121e28(64, &o->p14);
    } else {
        buf = func_00121e28(64, &o->p14);
    }
    o->p10 = h;
    u = t->f10 + 1.0f;
    if (D_002A3E20[t->id][3] == 0) {
        func_00101fc8(1, u, a, b, buf);
    } else {
        func_00102070(1, u, a, b, buf);
    }
    h->a = 4;
    h->b = (s32)buf;
    h->c = 0;
    h->d = 0;
    o = func_0015ed80(0x15f93 + k, func_00101f80);
    bb = func_00121e28(48, &o->p10);
    o->p10 = bb;
    if (D_002A3E20[t->id][3] == 0) {
        *(B48 *)bb = D_002A4260;
    } else {
        *(B48 *)bb = D_002A4430;
    }
    bb->p24 = t->p24;
    if (D_002A3E20[t->id][3] == 0) {
        func_00106bd8(D_002A43A0, 0x15f94 + k);
    } else {
        func_00106bd8(D_002A4570, 0x15f94 + k);
    }
    func_00106bd8(D_002A45C0, 0x15f96 + k);
    return 0;
}
