/* The parts of a menu window (docs/modules.md "Session 38"),
 * 0x00200000-0x00206e28; the packet builders are in winpart.nostrict.c.
 * A list row (func_002014a0 / func_00201550 / func_00201600: the frame
 * func_00200648 with the colours cols, then a message id, a string or a
 * string with an outline in a 26-pixel band at the text size sz, colour
 * cols[4]), the scroll bars on the left and the right edge of the text area
 * (func_00202678, func_00203a10), the page counter "n / m" under the tabs
 * (func_00203788, func_00203890: message 84 is the slash), and the default
 * colours of the boxes and lines. */
#include "common.h"
#include "platform/gs.h"
#include "platform/dma.h"
#include "text/textwin.h"
#include "data/pieces/D_003F1E70.h"

/* func_00202678's view: +0x74 and +0x90 are unions (alias set 0), which
 * TextWin's f32 / s32 there are not (see the note above the function). */
typedef union { u64 d; s32 w[2]; } UQ;
typedef union { s32 i; f32 f; } UF;
typedef struct {
    u8 pad0[0x48];
    s32 x48;
    u8 pad4c[0x74 - 0x4c];
    UF sx;
    f32 sy;
    u8 pad7c[0x90 - 0x7c];
    UF x90;
    f32 x94;
    u8 pad98[0xb0 - 0x98];
    s32 xb0, xb4;
    s16 xb8, xba;
    u8 padbc[0xc0 - 0xbc];
    s16 c0, c2, c4, c6, c8, ca, cc, ce, d0;
} WinUF;
typedef struct { UQ a, b; } Q;
typedef struct { s32 u, v, p0, p1; s32 x, y, z, f; } UX;
typedef struct { u64 tag, regs; UX s[4]; } P4;
typedef struct { UQ tag, regs; UX s[2]; } H2;

UQ *func_00122048(s32, s32);
void func_001220b8(void *);
u32 func_001edd88(s32, s32);
u8 *func_001efc10(s32);
s32 func_001f4570(TextWin *);
s32 func_001f45e0(TextWin *);
s32 func_001f9438(TextWin *w, s32 mode, s32 x, s32 y, s32 id, s32 sz, u32 col);
s32 func_001f94f0(TextWin *w, s32 mode, s32 x, s32 y, u8 *s, s32 sz, u32 col);
s32 func_001f9e48(TextWin *w, s32 mode, s32 x, s32 y, u8 *s, s32 sz, s32 col);
s32 func_001fb428(TextWin *o, s32 mode, s32 nd, s32 pad, s32 x, s32 y, s32 val, s32 sz, u32 col);
s32 func_001fc308(TextWin *o, s32 x, s32 y, s32 a, s32 b, s32 idx, s32 c, u32 c0, u32 c1);
s32 func_001fd538(TextWin *w);
s16 func_001fd658(TextWin *w);
void func_00200648(TextWin *o, s32 type, s32 px, s32 py, s32 pw, s32 *cols);
s32 func_002014a0(TextWin *o, s32 type, s32 mode, s32 px, s32 py, s32 pw, s32 x, s32 *cols, s32 id, s32 sz);
s32 func_00201550(TextWin *o, s32 type, s32 mode, s32 px, s32 py, s32 pw, s32 x, s32 *cols, u8 *s, s32 sz);
s32 func_00201600(TextWin *o, s32 type, s32 mode, s32 px, s32 py, s32 pw, s32 x, s32 *cols, u8 *s, s32 sz);
void func_00202678(WinUF *o, s32 x, s32 c);
void func_00203028(TextWin *o, s32 x0, s32 y, s32 x1, s32 c);
s32 func_00203a10(TextWin *o, s32 x);
void func_00206130(TextWin *o, s32 px, s32 py, s32 pw, s32 ph, s32 col);
s32 func_00206370(TextWin *w, s32 px, s32 py, s32 pw, s32 ph, s32 k0, s32 k1, s32 k2, s32 k3);

static inline s32 inl_sc(s32 v, s32 c, f32 fc, f32 s) { return fc + (f32)(v - c) * s; }

/* The rows at text size 15. */
s32 func_00201440(TextWin *o, s32 type, s32 mode, s32 px, s32 py, s32 pw, s32 x, s32 *cols, s32 id) {
    return func_002014a0(o, type, mode, px, py, pw, x, cols, id, 15);
}

s32 func_00201460(TextWin *o, s32 type, s32 mode, s32 px, s32 py, s32 pw, s32 x, s32 *cols, u8 *s) {
    return func_00201550(o, type, mode, px, py, pw, x, cols, s, 15);
}

s32 func_00201480(TextWin *o, s32 type, s32 mode, s32 px, s32 py, s32 pw, s32 x, s32 *cols, u8 *s) {
    return func_00201600(o, type, mode, px, py, pw, x, cols, s, 15);
}

s32 func_002014a0(TextWin *o, s32 type, s32 mode, s32 px, s32 py, s32 pw, s32 x, s32 *cols, s32 id, s32 sz) {
    u32 t;

    func_00200648(o, type, px, py, pw, cols);
    t = 0x1A - sz;
    return func_001f9438(o, mode, x, py + ((s32)(t + (t >> 0x1F)) >> 1), id, sz, cols[4]);
}

s32 func_00201550(TextWin *o, s32 type, s32 mode, s32 px, s32 py, s32 pw, s32 x, s32 *cols, u8 *s, s32 sz) {
    u32 t;

    func_00200648(o, type, px, py, pw, cols);
    t = 0x1A - sz;
    return func_001f94f0(o, mode, x, py + ((s32)(t + (t >> 0x1F)) >> 1), s, sz, cols[4]);
}

s32 func_00201600(TextWin *o, s32 type, s32 mode, s32 px, s32 py, s32 pw, s32 x, s32 *cols, u8 *s, s32 sz) {
    u32 t;

    func_00200648(o, type, px, py, pw, cols);
    t = 0x1A - sz;
    return func_001f9e48(o, mode, x, py + ((s32)(t + (t >> 0x1F)) >> 1), s, sz, cols[4]);
}

/* 00202678 (hand, strict): from session8 w12 7w (nostrict). Strict mode, with alias-set-0 (union) types exactly where the original keeps a nostrict-like ordering: the Q header stores, the H2 tag/regs, the buf[0] DMA tag stores, o->x90 and o->sx. Everything else keeps real alias sets, so the o-> loads pass the a/100, b/100 spill stores. */
void func_00202678(WinUF *o, s32 x, s32 c) {
    s32 ys[2];
    s32 xx[2];
    UQ *buf;
    Q *h;
    Q *q;
    u32 ub;
    s32 a, b, X, i, fl;
    s32 a100, a10, a1, b100, b10, b1;
    s32 cx, cy;
    f32 sx, sy, fcx, fcy;
    s32 X0, X1, Y0, Y1, Y2, Y3;
    if (o->cc == 0) return;
    if (!(o->ce < o->cc)) return;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(2048, 128);
    h = (Q *)buf + 1;
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    h->a.d = 0x6000000000008001;
    h->b.d = 0xeeeeee;
    q = h + 1;
    q->a.d = 0;
    q->b.d = 63;
    q++;
    q->a.d = 0x7bf8621413d7c;
    q->b.d = 6;
    q++;
    q->a.d = 0x4007bf8001300000;
    q->b.d = 22;
    q++;
    q->a.d = 0x7bf8001400000;
    q->b.d = 22;
    q++;
    q->a.d = 68;
    q->b.d = 66;
    q++;
    q->a.d = func_001edd88(c, o->x90.i);
    q->b.d = 1;
    q++;
    a = o->d0 >> 4;
    b = o->cc - (a + o->ce); if (b < 0) b = 0;
    ys[0] = o->xb4 + o->c0;
    X = o->xb0 + (x << 4);
    ys[1] = ys[0] + (((o->c4 >> 4) * o->ce - (o->c8 >> 4) - 9) << 4);
    a100 = a / 100;
    a10 = a % 100 / 10;
    a1 = a % 100 % 10;
    b100 = b / 100;
    b10 = b % 100 / 10;
    b1 = b % 100 % 10;
    ((P4 *)q)->tag = 0x40ab400000008002;
    ((P4 *)q)->regs = 0x4343;
    if (a) {
        ((P4 *)q)->s[0].u = 1768; ((P4 *)q)->s[0].v = 1048; ((P4 *)q)->s[1].u = 1960; ((P4 *)q)->s[1].v = 1192;
    } else {
        ((P4 *)q)->s[0].u = 1768; ((P4 *)q)->s[0].v = 1240; ((P4 *)q)->s[1].u = 1960; ((P4 *)q)->s[1].v = 1384;
    }
    if (b) {
        ((P4 *)q)->s[2].u = 1768; ((P4 *)q)->s[2].v = 1176; ((P4 *)q)->s[3].u = 1960; ((P4 *)q)->s[3].v = 1032;
    } else {
        ((P4 *)q)->s[2].u = 1768; ((P4 *)q)->s[2].v = 1368; ((P4 *)q)->s[3].u = 1960; ((P4 *)q)->s[3].v = 1224;
    }
    ((P4 *)q)->s[0].x = X; ((P4 *)q)->s[0].y = ys[0]; ((P4 *)q)->s[0].z = 0x100000; ((P4 *)q)->s[0].f = 0x8000;
    ((P4 *)q)->s[1].x = X + 192; ((P4 *)q)->s[1].y = ys[0] + 144; ((P4 *)q)->s[1].z = 0x100000; ((P4 *)q)->s[1].f = 0;
    ((P4 *)q)->s[2].x = X; ((P4 *)q)->s[2].y = ys[1]; ((P4 *)q)->s[2].z = 0x100000; ((P4 *)q)->s[2].f = 0x8000;
    ((P4 *)q)->s[3].x = X + 192; ((P4 *)q)->s[3].y = ys[1] + 144; ((P4 *)q)->s[3].z = 0x100000; ((P4 *)q)->s[3].f = 0;
    fl = o->x48 & 1;
    if (fl) {
        cx = func_001f4570((TextWin *)o);
        cy = func_001f45e0((TextWin *)o);
        sx = o->sx.f;
        sy = o->sy;
        fcx = cx;
        fcy = cy;
        X0 = inl_sc(((P4 *)q)->s[0].x, cx, fcx, sx);
        X1 = inl_sc(((P4 *)q)->s[1].x, cx, fcx, sx);
        Y0 = inl_sc(((P4 *)q)->s[0].y, cy, fcy, sy);
        Y1 = inl_sc(((P4 *)q)->s[1].y, cy, fcy, sy);
        Y2 = inl_sc(((P4 *)q)->s[2].y, cy, fcy, sy);
        Y3 = inl_sc(((P4 *)q)->s[3].y, cy, fcy, sy);
        ((P4 *)q)->s[0].x = X0; ((P4 *)q)->s[0].y = Y0;
        ((P4 *)q)->s[1].x = X1; ((P4 *)q)->s[1].y = Y1;
        ((P4 *)q)->s[2].x = X0; ((P4 *)q)->s[2].y = Y2;
        ((P4 *)q)->s[3].x = X1; ((P4 *)q)->s[3].y = Y3;
    }
    buf[0].d = ((((s32)((P4 *)q + 1) - (s32)buf) >> 4) - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
    PlatGsSyncPath(0, 0);
    xx[0] = ((P4 *)q)->s[0].x;
    xx[1] = ((P4 *)q)->s[1].x;
    ((H2 *)h)->tag.d = 0x4000000000008001;
    ((H2 *)h)->regs.d = 0x4343;
    ((H2 *)h)->s[0].u = 2216; ((H2 *)h)->s[0].v = 1752;
    ((H2 *)h)->s[0].x = xx[0]; ((H2 *)h)->s[0].z = 0x100000; ((H2 *)h)->s[0].f = 0x8000;
    ((H2 *)h)->s[1].u = 2408; ((H2 *)h)->s[1].v = 1880;
    ((H2 *)h)->s[1].x = xx[1]; ((H2 *)h)->s[1].z = 0x100000; ((H2 *)h)->s[1].f = 0;
    buf[0].d = ((((s32)((H2 *)h + 1) - (s32)buf) >> 4) - 1) | 0x70000000;
    ys[0] += 176;
    ys[1] -= 32;
    for (i = a100; i > 0; i--) {
        ((H2 *)h)->s[0].y = ys[0];
        ((H2 *)h)->s[1].y = ys[0] + 256;
        if (fl) {
            ((H2 *)h)->s[0].y = inl_sc(((H2 *)h)->s[0].y, cy, cy, sy);
            ((H2 *)h)->s[1].y = inl_sc(((H2 *)h)->s[1].y, cy, cy, sy);
        }
        PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
        PlatGsSyncPath(0, 0);
        ys[0] += 288;
    }
    for (i = b100; i > 0; i--) {
        ((H2 *)h)->s[0].y = ys[1] - 256;
        ((H2 *)h)->s[1].y = ys[1];
        if (fl) {
            ((H2 *)h)->s[0].y = inl_sc(((H2 *)h)->s[0].y, cy, cy, sy);
            ((H2 *)h)->s[1].y = inl_sc(((H2 *)h)->s[1].y, cy, cy, sy);
        }
        PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
        PlatGsSyncPath(0, 0);
        ys[1] -= 288;
    }
    ((H2 *)h)->s[0].u = 2216; ((H2 *)h)->s[0].v = 1752;
    ((H2 *)h)->s[1].u = 2408; ((H2 *)h)->s[1].v = 1880;
    for (i = a10; i > 0; i--) {
        ((H2 *)h)->s[0].y = ys[0];
        ((H2 *)h)->s[1].y = ys[0] + 128;
        if (fl) {
            ((H2 *)h)->s[0].y = inl_sc(((H2 *)h)->s[0].y, cy, cy, sy);
            ((H2 *)h)->s[1].y = inl_sc(((H2 *)h)->s[1].y, cy, cy, sy);
        }
        PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
        PlatGsSyncPath(0, 0);
        ys[0] += 160;
    }
    for (i = b10; i > 0; i--) {
        ((H2 *)h)->s[0].y = ys[1] - 128;
        ((H2 *)h)->s[1].y = ys[1];
        if (fl) {
            ((H2 *)h)->s[0].y = inl_sc(((H2 *)h)->s[0].y, cy, cy, sy);
            ((H2 *)h)->s[1].y = inl_sc(((H2 *)h)->s[1].y, cy, cy, sy);
        }
        PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
        PlatGsSyncPath(0, 0);
        ys[1] -= 160;
    }
    ((H2 *)h)->s[0].u = 2024; ((H2 *)h)->s[0].v = 1336;
    ((H2 *)h)->s[1].u = 2216; ((H2 *)h)->s[1].v = 1368;
    for (i = a1; i > 0; i--) {
        ((H2 *)h)->s[0].y = ys[0];
        ((H2 *)h)->s[1].y = ys[0] + 32;
        if (fl) {
            ((H2 *)h)->s[0].y = inl_sc(((H2 *)h)->s[0].y, cy, cy, sy);
            ((H2 *)h)->s[1].y = inl_sc(((H2 *)h)->s[1].y, cy, cy, sy);
        }
        PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
        PlatGsSyncPath(0, 0);
        ys[0] += 64;
    }
    for (i = b1; i > 0; i--) {
        ((H2 *)h)->s[0].y = ys[1] - 32;
        ((H2 *)h)->s[1].y = ys[1];
        if (fl) {
            ((H2 *)h)->s[0].y = inl_sc(((H2 *)h)->s[0].y, cy, cy, sy);
            ((H2 *)h)->s[1].y = inl_sc(((H2 *)h)->s[1].y, cy, cy, sy);
        }
        PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
        PlatGsSyncPath(0, 0);
        ys[1] -= 64;
    }
    func_001220b8(buf);
}

void func_00202fc0(TextWin *o) {
    func_00202678((WinUF *)o, ((s32)((u16)o->xbe << 0x10) >> 0x14) - 0x10, 0x80C8C8C8);
}

void func_00202ff0(TextWin *o) {
    func_00202678((WinUF *)o, ((s32)(o->xbe + o->xc2) >> 4) + 4, 0x80C8C8C8);
}

/* The page counter between the tabs: current column + 1, "/", columns. */
void func_00203788(TextWin *o, s32 x0, s32 y, s32 x1, s32 c) {
    s32 mid;
    if (o->xd8 < 2) return;
    func_00203028(o, x0, y, x1, c);
    y--;
    mid = x0 + (x1 - x0 + 9) / 2;
    func_001fb428(o, 1, 0, 0, mid - 7, y, func_001fd538(o) + 1, 15, c);
    func_001f94f0(o, 0, mid - 7, y, func_001efc10(84), 15, c);
    func_001fb428(o, 0, 0, 0, mid + 6, y, func_001fd658(o), 15, c);
}

/* The same with arrow icons (17 / 18 at the ends, 15 / 16 otherwise). */
void func_00203890(TextWin *o, s32 x, s32 y, s32 x2, s32 col) {
    s32 cur, mid, a, b;
    if (o->xd8 < 2) return;
    cur = func_001fd538(o);
    a = cur == 0 ? 17 : 15;
    b = cur == o->xd8 - 1 ? 18 : 16;
    func_001fc308(o, x, y, 0, 0, a, 0, col, col);
    func_001fc308(o, x2, y, 0, 0, b, 0, col, col);
    y--;
    mid = x + (x2 - x + 9) / 2;
    func_001fb428(o, 1, 0, 0, mid - 7, y, func_001fd538(o) + 1, 15, col);
    func_001f94f0(o, 0, mid - 7, y, func_001efc10(84), 15, col);
    func_001fb428(o, 0, 0, 0, mid + 6, y, func_001fd658(o), 15, col);
}

s32 func_002040a0(TextWin *o) {
    return func_00203a10(o, ((s32)((u16)o->xbe << 0x10) >> 0x14) - 0x10);
}

void func_002040c8(TextWin *o) {
    func_00203a10(o, ((s32)(o->xbe + o->xc2) >> 4) + 4);
}

void func_00206110(TextWin *o, s32 px, s32 py, s32 pw, s32 ph) {
    func_00206130(o, px, py, pw, ph, 0x80F04646);
}

void func_00206690(TextWin *o, s32 px, s32 py, s32 pw) {
    func_00206130(o, px, py, pw, 2, 0x80F04646);
}

s32 func_002066b0(TextWin *w, s32 px, s32 py, s32 pw, s32 k0, s32 k1) {
    return func_00206370(w, px, py, pw, 2, k0, k1, k0, k1);
}

void func_002066e8(TextWin *o, s32 px, s32 py, s32 ph) {
    func_00206130(o, px, py, 2, ph, 0x80F04646);
}

s32 func_00206710(TextWin *w, s32 px, s32 py, s32 ph, s32 k0, s32 k1) {
    return func_00206370(w, px, py, 2, ph, k0, k0, k1, k1);
}
