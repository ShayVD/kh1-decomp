/* Rows, tabs and titles of the menu windows (docs/modules.md "Session 38"),
 * 0x00207428-0x00208458.  D_003F2C40 is a table of row colour sets of 0x14
 * bytes (+0x0 the frame, +0x10 the text; S2C40 / E20 are two views of it):
 * func_002078f0 ... draw a row in set i (winpart.c's list rows at size 15),
 * func_00207a38 the two tabs of a window (the selected one is the column
 * cursor), func_00207b38 ... a window title (message id at size 15 under a
 * bar) with its tabs, func_00207cc0 ... the scroll arrows with a number,
 * func_002080e0 / func_002081b0 "n pages", func_00208280 ... icons of the
 * tables D_003F2EAC / D_003F2F88 / D_003F2FD8 in their colours.
 * D_00640E00 is a list of D_00640E20 ids and D_00640E24 the index of
 * D_00640E28 in it (func_00207598). */
#include "common.h"
#include "text/textwin.h"
#include "data/pieces/D_003F2C40.h"

typedef E20_3F2C40_2 E20;
typedef S2C40_3F2C40_2 S2C40;

extern s32 D_003F2C50;
extern s32 D_003F2EAC;
extern s32 D_003F2F10[];
extern s32 D_003F2F88;
extern s32 D_003F2FB0;
extern s32 D_003F2FD8;
extern s32 D_003F3010;
extern s32 D_00640E00[];
extern s32 D_00640E20;
extern s32 D_00640E24;
extern s32 D_00640E28;

f32 sinf(f32);
u32 func_001edd88(u32, s32);
s32 func_001ee768(s32);
u8 *func_001efc10(s32);
void func_001f1fc8(s32, s32, s32, s32, u8 *, s32);
void func_001f9010(s32);
s32 func_001f9270(TextWin *w, s32 mode, s32 x, s32 id, s32 sz, u32 col);
s32 func_001f9438(TextWin *w, s32 mode, s32 x, s32 y, s32 id, s32 sz, u32 col);
s32 func_001fb428(TextWin *o, s32 mode, s32 nd, s32 pad, s32 x, s32 y, s32 val, s32 sz, u32 col);
s32 func_001fc308(TextWin *o, s32 x, s32 y, s32 a, s32 b, s32 idx, s32 c, u32 c0, u32 c1);
s32 func_001fd538(TextWin *w);
void func_00200648(TextWin *o, s32 type, s32 px, s32 py, s32 pw, s32 *cols);
void func_00200e28(s32, s32, s32, s32, void *);
void func_00201440(TextWin *, s32, s32, s32, s32, s32, s32, void *, s32);
void func_00201460(TextWin *, s32, s32, s32, s32, s32, s32, void *, s32);
void func_00201480(TextWin *, s32, s32, s32, s32, s32, s32, void *, s32);
void func_002016b0(TextWin *o, s32 x, s32 y, u32 c);
void func_00201988(TextWin *o, s32 x, s32 y, u32 c);
void func_00201c60(TextWin *o, s32 x, s32 y, u32 c);
void func_002053e8(TextWin *, s32, s32, s32, s32, u32);
void func_00207598(void);
void func_002076b0(s32, s32, s32, s32, s32, s32, u8 *);
void func_002078f0(TextWin *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00207938(TextWin *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00207980(TextWin *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_002079c8(TextWin *);
void func_00207a38(TextWin *);
void func_0020be10(s32);

/* The new-item mark: a pulsing box and icon 62. */
void func_00207428(TextWin *o, s32 x, s32 y) {
    s32 t = o->x94;
    u32 a = (u32)(sinf((f32)(t % 64) * 0.015625f * 3.1415928f) * 128.0f) << 24;
    u32 c1 = a | 0x1e9696;
    u32 c2 = a | 0xffffff;
    u32 c3 = a | 0x0a1e1e;
    func_002053e8(o, x + 2, y + 2, 26, 8, c2);
    func_001fc308(o, x, y, 0, 0, 62, 0, c1, c3);
}

void func_00207560(TextWin *w, s32 x, s32 y) {
    func_001f9438(w, 0, x, y, 0x1D1, 0x14, 0x8080FFFF);
}

void func_00207598(void) {
    s32 i;
    D_00640E24 = 0;
    for (i = 0; i < D_00640E20; i++) {
        if (D_00640E28 == D_00640E00[i]) D_00640E24 = i;
    }
}

void func_002075f8(void) {
    D_00640E28 = 7;
    func_00207598();
}

void func_00207618(void) {
    func_0020be10(0x10);
}

void func_00207630(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    func_002076b0(arg0, arg1, arg2, arg3, arg4, arg5, func_001efc10(arg6));
}

void func_002076b0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 *arg6) {
    void *e;

    e = (s8 *)&D_003F2C40.i + (arg0 * 0x14);
    func_00200e28(2, arg2, arg3, arg4, e);
    func_001f1fc8(arg1, M2C_FIELD(e, s32 *, 0x10), arg5, arg3 + 5, arg6, 0xF);
}

void func_00207748(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 col;
    void *e;

    e = &D_003F2C40.c + (arg0 * 0x14);
    func_00200e28(2, arg1, arg2, arg3, e);
    col = M2C_FIELD(e, s32 *, 0x10);
    func_001f1fc8(2, col, arg1 + ((s32)(arg3 + ((u32)arg3 >> 0x1F)) >> 1), arg2 + 5, func_001efc10(0x2B), 0xF);
}

void func_002077f0(TextWin *o, s32 i, s32 type, s32 px, s32 py, s32 pw) {
    func_00200648(o, type, px, py, pw, (s32 *)(&D_003F2C40.c + (i * 0x14)));
}

void func_00207830(TextWin *a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2) {
    func_002078f0(a0, a1, a2, 0, a3, t0, t1, a3 + 16, t2);
}

void func_00207870(TextWin *a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2) {
    func_00207938(a0, a1, a2, 0, a3, t0, t1, a3 + 16, t2);
}

void func_002078b0(TextWin *a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2) {
    func_00207980(a0, a1, a2, 0, a3, t0, t1, a3 + 16, t2);
}

void func_002078f0(TextWin *a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3, s32 s0) {
    func_00201440(a0, a2, a3, t0, t1, t2, t3, &D_003F2C40.s2C40_2[a1], s0);
}

void func_00207938(TextWin *a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3, s32 s0) {
    func_00201460(a0, a2, a3, t0, t1, t2, t3, &D_003F2C40.s2C40_2[a1], s0);
}

void func_00207980(TextWin *a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3, s32 s0) {
    func_00201480(a0, a2, a3, t0, t1, t2, t3, &D_003F2C40.s2C40_2[a1], s0);
}

/* The title bar over the margins (message 43). */
void func_002079c8(TextWin *a0) {
    s16 z = a0->xc2 >> 4;
    func_002078f0(a0, 1, 2, 2, a0->xbe >> 4, a0->xc0 >> 4, z, (a0->xbe >> 4) + z / 2, 43);
}

/* The two tabs; the column cursor picks one. */
void func_00207a38(TextWin *o) {
    s32 i;
    s32 w = o->xc2 >> 4;
    s32 h = w - (o->xc6 >> 4);
    s32 x = o->xbe >> 4;
    s32 y = o->xc0 >> 4;
    s32 half = h / 2;
    s32 sel = func_001fd538(o);
    for (i = 0; i < 2; i++) {
        func_002078f0(o, i == sel, 2, 2, x, y, h, x + half, D_003F2F10[i]);
        x += w;
    }
}

void func_00207b38(TextWin *w, s32 id) {
    func_001f9270(w, 0, 0x10, 0x32, 0xC, 0x801EC8C8);
    func_001f9010(0x17);
    func_001f9438(w, 0, 0xE, 0x22, id, 0xF, 0x80E6E6E6);
    func_002079c8(w);
}

void func_00207bb0(TextWin *w, s32 id) {
    func_001f9270(w, 0, 0x10, 0x31, 0xC, 0x801EC8C8);
    func_001f9010(0x17);
    func_001f9438(w, 0, 0xE, 0x22, id, 0xF, 0x80E6E6E6);
    func_002079c8(w);
}

void func_00207c28(TextWin *w, s32 id) {
    func_001f9270(w, 0, 0x10, 0x30, 0xC, 0x801EC8C8);
    func_001f9010(0x17);
    func_001f9438(w, 0, 0xE, 0x22, id, 0xF, 0x80E6E6E6);
    func_00207a38(w);
}

s32 func_00207ca0(s32 i) {
    return *(s32 *)((s8 *)&D_003F2C50 + (i * 0x14));
}

void func_00207cc0(TextWin *a0, s32 a1, s32 a2, s32 a3, s32 t0) {
    S2C40 *e = &D_003F2C40.s2C40_2[a1];
    func_002016b0(a0, a2, a3 + 2, e->a);
    func_001fb428(a0, 1, 2, 0, a2 + 37, a3 + 7, t0, 12, e->e);
}

void func_00207d60(TextWin *o, s32 i, s32 b, s32 y, s32 x, s32 p, s32 h) {
    E20 *e = &D_003F2C40.e20_2[i];
    func_002016b0(o, b, y + 2, e->a);
    func_001fb428(o, 1, 2, 0, x, y + (26 - h) / 2, p, h, e->x10);
}

void func_00207e20(TextWin *a0, s32 a1, s32 a2, s32 a3, s32 t0) {
    S2C40 *e = &D_003F2C40.s2C40_2[a1];
    func_00201988(a0, a2, a3 + 3, e->a);
    func_001fb428(a0, 1, 4, 0, a2 + 51, a3 + 7, t0, 12, e->e);
}

void func_00207ec0(TextWin *o, s32 i, s32 b, s32 y, s32 x, s32 p, s32 h) {
    E20 *e = &D_003F2C40.e20_2[i];
    func_00201988(o, b, y + 3, e->a);
    func_001fb428(o, 1, 4, 0, x, y + (26 - h) / 2, p, h, e->x10);
}

void func_00207f80(TextWin *a0, s32 a1, s32 a2, s32 a3, s32 t0) {
    S2C40 *e = &D_003F2C40.s2C40_2[a1];
    func_00201c60(a0, a2, a3 + 2, e->a);
    func_001fb428(a0, 1, 2, 0, a2 + 29, a3 + 7, t0, 12, e->e);
}

void func_00208020(TextWin *o, s32 i, s32 b, s32 y, s32 x, s32 p, s32 h) {
    E20 *e = &D_003F2C40.e20_2[i];
    func_00201c60(o, b, y + 2, e->a);
    func_001fb428(o, 1, 2, 0, x, y + (26 - h) / 2, p, h, e->x10);
}

/* Message 85 and a number of n (only when n > 1). */
void func_002080e0(TextWin *o, s32 i, s32 x, s32 y, s32 n) {
    E20 *e;
    if (n < 2) return;
    e = &D_003F2C40.e20_2[i];
    func_002016b0(o, x, y + 2, e->a);
    y += 7;
    func_001f9438(o, 0, x + 5, y, 85, 12, e->x10);
    func_001fb428(o, 1, 2, 0, x + 37, y, n, 12, e->x10);
}

void func_002081b0(TextWin *o, s32 i, s32 x, s32 y, s32 n) {
    E20 *e;
    if (n < 2) return;
    e = &D_003F2C40.e20_2[i];
    func_00201988(o, x, y + 3, e->a);
    y += 7;
    func_001f9438(o, 0, x + 5, y, 85, 12, e->x10);
    func_001fb428(o, 1, 3, 0, x + 51, y, n, 12, e->x10);
}

void func_00208280(TextWin *o, s32 x, s32 y, s32 s, s32 idx, s32 a) {
    u32 col;

    col = func_001edd88(*(s32 *)((s8 *)&D_003F2EAC + (idx * 4)), a);
    func_001fc308(o, x, y, s, s, idx, 0, col, col);
}

void func_00208310(TextWin *o, s32 x, s32 y, s32 s, s32 k, s32 a) {
    s32 off;
    u32 col;

    off = k * 4;
    col = func_001edd88(*(s32 *)((s8 *)&D_003F2FB0 + off), a);
    func_001fc308(o, x, y, s, s, *(s32 *)((s8 *)&D_003F2F88 + off), 0, col, col);
}

void func_002083a8(TextWin *o, s32 x, s32 y, s32 s, s32 k, s32 a) {
    s32 off;
    u32 col;

    if (k != 0) {
        off = func_001ee768(k) * 4;
        col = func_001edd88(*(s32 *)((s8 *)&D_003F3010 + off), a);
        func_001fc308(o, x, y, s, s, *(s32 *)((s8 *)&D_003F2FD8 + off), 0, col, col);
    }
}
