/* Text in the text windows (docs/modules.md "Session 37"),
 * 0x001f86e0-0x001fd248: the scissor set to a window's rectangle
 * (func_001f86e0 ..., scaled like the frames; func_001f8f30 resets it to the
 * whole 512x384 screen), the current text colour D_003F1A60 and width
 * D_003F1A64 (in 1/16 pixels), and the wrappers of the drawing functions in
 * wintext.nostrict.c / wintext.nostrict_nogcse.c: by message id
 * (func_001efbb8), centred in the window (x = half its width +0xb8, y so a
 * line of size sz sits in a 20-pixel band), in the current colour, at size
 * 18, or with a one-pixel outline in a second colour (func_001fa318 ...).
 * W16(f) is a window field in 1/16 pixels as pixels, W32(f) half of it. */
#include "common.h"
#include "platform/dma.h"
#include "text/textwin.h"
#include "data/pieces/D_003F1A70.h"

typedef Q_3f1a70 Q;

#define W16(f) ((s32)((u16)(f) << 16) >> 20)
#define W32(f) ((s32)((u16)(f) << 16) >> 21)

extern s32 D_003F1A60;
extern s32 D_003F1A64;

Q *func_0011fb38(s32 reg, u64 val, Q *p);
Q *func_00122048(s32, s32);
void func_001220b8(void *);
u32 func_001edd88(u32, s32);
u8 *func_001efbb8(s32);
s32 func_001eff50(s32);
s32 func_001f4570(TextWin *);
s32 func_001f45e0(TextWin *);
s32 sceGsSyncPath(s32, u16);

void func_001f86e0(TextWin *o, s32 x, s32 y, s32 w, s32 h);
s32 func_001f9078(TextWin *w, s32 id, s32 sz);
s32 func_001f9098(TextWin *w, u8 *s, s32 sz);
void func_001f90b8(TextWin *w, u8 *s, s32 sz);
s32 func_001f9138(TextWin *w, s32 id, s32 sz, u32 col);
s32 func_001f9180(TextWin *w, u8 *s, s32 sz, u32 col);
void func_001f91c8(TextWin *w, u8 *s, s32 sz, u32 col);
s32 func_001f9270(TextWin *w, s32 mode, s32 x, s32 id, s32 sz, u32 col);
s32 func_001f92b0(TextWin *w, s32 mode, s32 x, u8 *s, s32 sz, u32 col);
void func_001f92f0(TextWin *w, s32 mode, s32 x, u8 *s, s32 sz, u32 col);
s32 func_001f9378(TextWin *w, s32 mode, s32 x, s32 y, s32 id, s32 sz);
s32 func_001f9398(TextWin *w, s32 mode, s32 x, s32 y, u8 *s, s32 sz);
void func_001f93b8(TextWin *w, s32 mode, s32 x, s32 y, u8 *s, s32 sz);
s32 func_001f9438(TextWin *w, s32 mode, s32 x, s32 y, s32 id, s32 sz, u32 col);
s32 func_001f94f0(TextWin *w, s32 mode, s32 x, s32 y, u8 *s, s32 sz, u32 col);
void func_001f9e48(TextWin *w, s32 mode, s32 x, s32 y, u8 *s, s32 sz, s32 col);
s32 func_001fa718(TextWin *w, s32 y, s32 id, s32 sz);
s32 func_001fa748(TextWin *w, s32 y, u8 *s, s32 sz);
void func_001fa778(TextWin *w, s32 y, u8 *s, s32 sz);
s32 func_001fa808(TextWin *w, s32 y, s32 id, s32 sz, u32 col);
s32 func_001fa840(TextWin *w, s32 y, u8 *s, s32 sz, u32 col);
void func_001fa878(TextWin *w, s32 y, u8 *s, s32 sz, u32 col);
void func_001fa8b0(TextWin *o, s32 x, s32 y, u8 *s, s32 sz, s32 col);
void func_001fade0(TextWin *o, s32 x, s32 y, s32 idx, s32 sz, s32 col);
void func_001fb248(TextWin *o, s32 x, s32 y, s32 code, s32 sz, s32 col);
s32 func_001fb408(TextWin *o, s32 mode, s32 nd, s32 pad, s32 x, s32 y, s32 val, u32 col);
/* s32, though the definition returns nothing: func_001fbb50 matches only so */
s32 func_001fb428(TextWin *o, s32 mode, u32 nd, s32 pad, s32 x, s32 y, s32 val, s32 sz, u32 col);
s32 func_001fbcd8(TextWin *o, s32 mode, u32 nd, s32 pad, s32 x, s32 y, s32 val, s32 alpha, u32 col);
s32 func_001fc308(TextWin *o, s32 x, s32 y, s32 w, s32 h, s32 idx, s32 a, u32 c0, u32 c1);
s32 func_001fc330(TextWin *o, s32 x, s32 y, s32 w, s32 h, s32 idx, s32 a, s32 c0, s32 c1, s32 c2, s32 c3);
s32 func_001fcdc8(s32 x, s32 y, s32 w, s32 h, s32 idx, s32 a, s32 c0, s32 c1);

void func_001f86e0(TextWin *o, s32 x, s32 y, s32 w, s32 h) {
    s32 x0, y0, x1, y1, cx, cy, t;
    Q *buf, *e, *p;
    void *ub;
    x0 = x + ((o->xb0 - 0x7000) >> 4);
    y0 = y + ((o->xb4 - 0x7400) >> 4);
    x1 = x0 + w - 1;
    y1 = y0 + h - 1;
    if (o->u48.w.lo & 1) {
        cx = (func_001f4570(o) - 0x7000) >> 4;
        cy = (func_001f45e0(o) - 0x7400) >> 4;
        x0 = cx + (x0 - cx) * o->x74;
        x1 = cx + (x1 - cx) * o->x74;
        y0 = cy + (y0 - cy) * o->x78;
        y1 = cy + (y1 - cy) * o->x78;
        if (x1 < x0) { t = x0; x0 = x1; x1 = t; }
        if (y1 < y0) { t = y0; y0 = y1; y1 = t; }
    }
    if (x0 < 512 && y0 < 384 && x1 >= 0 && y1 >= 0) {
        if (x1 >= 512) x1 = 511;
        if (x0 < 0) x0 = 0;
        if (y0 < 0) y0 = 0;
        if (y1 >= 384) y1 = 383;

        p = func_00122048(1024, 128);
        buf = p;
        p = buf + 1;
        ub = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
        p->a = 0x1000000000008001;
        p->b = 14;

        e = func_0011fb38(64, (u64)x0 | ((u64)x1 << 16) | ((u64)y0 << 32) | ((u64)y1 << 48), p + 1);
        buf->a = ((e - buf) - 1) | 0x70000000;
        PlatDmaSend(PlatDmaGetChan(2), ub);
        sceGsSyncPath(0, 0);
        func_001220b8(buf);
    }
}

void func_001f8950(TextWin *o, s32 x0, s32 y0, s32 w, s32 h) {
    s32 x1, y1, cx, cy, t;
    Q *buf, *e, *p;
    void *ub;
    x1 = x0 + w - 1;
    y1 = y0 + h - 1;
    if (o->u48.w.lo & 1) {
        cx = (func_001f4570(o) - 0x7000) >> 4;
        cy = (func_001f45e0(o) - 0x7400) >> 4;
        x0 = cx + (x0 - cx) * o->x74;
        x1 = cx + (x1 - cx) * o->x74;
        y0 = cy + (y0 - cy) * o->x78;
        y1 = cy + (y1 - cy) * o->x78;
        if (x1 < x0) { t = x0; x0 = x1; x1 = t; }
        if (y1 < y0) { t = y0; y0 = y1; y1 = t; }
    }
    if (x0 < 512 && y0 < 384 && x1 >= 0 && y1 >= 0) {
        if (x1 >= 512) x1 = 511;
        if (x0 < 0) x0 = 0;
        if (y0 < 0) y0 = 0;
        if (y1 >= 384) y1 = 383;

        p = func_00122048(1024, 128);
        buf = p;
        p = buf + 1;
        ub = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
        p->a = 0x1000000000008001;
        p->b = 14;

        e = func_0011fb38(64, (u64)x0 | ((u64)x1 << 16) | ((u64)y0 << 32) | ((u64)y1 << 48), p + 1);
        buf->a = ((e - buf) - 1) | 0x70000000;
        PlatDmaSend(PlatDmaGetChan(2), ub);
        sceGsSyncPath(0, 0);
        func_001220b8(buf);
    }
}

void func_001f8ba8(TextWin *o) {
    s32 x0, y0, x1, y1, cx, cy, t;
    f32 fsx, fsy;
    Q *buf, *e, *p;
    void *ub;
    x0 = (o->xb0 - 0x7000) >> 4;
    y0 = (o->xb4 - 0x7400) >> 4;
    x1 = x0 + (o->xb8 >> 4) - 1;
    y1 = y0 + (o->xba >> 4) - 1;
    if (o->u48.w.lo & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        fsx = o->x74; fsy = o->x78;
        y0 = cy + (y0 - cy) * fsy;
        y1 = cy + (y1 - cy) * fsy;
        x0 = cx + (x0 - cx) * fsx;
        x1 = cx + (x1 - cx) * fsx;

        if (x1 < x0) { t = x0; x0 = x1; x1 = t; }
        if (y1 < y0) { t = y0; y0 = y1; y1 = t; }
    }
    if (x0 < 512 && y0 < 384 && x1 >= 0 && y1 >= 0) {
        if (x1 >= 512) x1 = 511;
        if (x0 < 0) x0 = 0;
        if (y0 < 0) y0 = 0;
        if (y1 >= 384) y1 = 383;

        p = func_00122048(1024, 128);
        buf = p;
        p = buf + 1;
        ub = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
        p->a = 0x1000000000008001;
        p->b = 14;

        e = func_0011fb38(64, (u64)x0 | ((u64)x1 << 16) | ((u64)y0 << 32) | ((u64)y1 << 48), p + 1);
        buf->a = ((e - buf) - 1) | 0x70000000;
        PlatDmaSend(PlatDmaGetChan(2), ub);
        sceGsSyncPath(0, 0);
        func_001220b8(buf);
    }
}

/* The scissor to the window's text area: +0xbe / +0xc0 the origin, +0xc2 /
 * +0xc4 a cell, +0xd8 / +0xce the number of cells, +0xc6 / +0xc8 margins. */
void func_001f8e18(TextWin *w) {
    func_001f86e0(w, W16(w->xbe), W16(w->xc0), W16(w->xc2) * w->xd8 - W16(w->xc6), W16(w->xc4) * w->xce - W16(w->xc8));
}

void func_001f8e90(TextWin *w) {
    func_001f86e0(w, W16(w->xbe), 0, W16(w->xc2) * w->xd8 - W16(w->xc6), 384);
}

void func_001f8ee0(TextWin *w) {
    func_001f86e0(w, 0, W16(w->xc0), 512, W16(w->xc4) * w->xce - W16(w->xc8));
}

void func_001f8f30(void) {
    void *u;
    u64 *p = (u64 *)func_00122048(0x400, 0x80);
    u64 *buf = p;
    p += 2;
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p[0] = 0x1000000000008001;
    p[1] = 0xe;
    buf[0] = ((s32)((u8 *)func_0011fb38(0x40, 0x017F000001FF0000, (Q *)(p + 2)) - (u8 *)buf) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}

void func_001f8ff0(s32 col) {
    D_003F1A60 = col;
}

s32 func_001f9000(void) {
    return D_003F1A60;
}

void func_001f9010(s32 w) {
    D_003F1A64 = w * 16;
}

s32 func_001f9020(void) {
    return D_003F1A64 >> 4;
}

s32 func_001f9030(TextWin *w, s32 id) {
    return func_001f9078(w, id, 18);
}

s32 func_001f9048(TextWin *w, u8 *s) {
    return func_001f9098(w, s, 18);
}

void func_001f9060(TextWin *w, u8 *s) {
    func_001f90b8(w, s, 18);
}

s32 func_001f9078(TextWin *w, s32 id, s32 sz) {
    return func_001f9138(w, id, sz, D_003F1A60);
}

s32 func_001f9098(TextWin *w, u8 *s, s32 sz) {
    return func_001f9180(w, s, sz, D_003F1A60);
}

void func_001f90b8(TextWin *w, u8 *s, s32 sz) {
    func_001f91c8(w, s, sz, D_003F1A60);
}

s32 func_001f90d8(TextWin *w, s32 id, u32 col) {
    return func_001f9138(w, id, 18, col);
}

s32 func_001f90f8(TextWin *w, u8 *s, u32 col) {
    return func_001f9180(w, s, 18, col);
}

void func_001f9118(TextWin *w, u8 *s, u32 col) {
    func_001f91c8(w, s, 18, col);
}

s32 func_001f9138(TextWin *w, s32 id, s32 sz, u32 col) {
    return func_001f9438(w, 2, W32(w->xb8), (20 - sz) / 2 + 2, id, sz, col);
}

s32 func_001f9180(TextWin *w, u8 *s, s32 sz, u32 col) {
    return func_001f94f0(w, 2, W32(w->xb8), (20 - sz) / 2 + 2, s, sz, col);
}

void func_001f91c8(TextWin *w, u8 *s, s32 sz, u32 col) {
    func_001f9e48(w, 2, W32(w->xb8), (20 - sz) / 2 + 2, s, sz, col);
}

s32 func_001f9210(TextWin *w, s32 mode, s32 x, s32 id, s32 sz) {
    return func_001f9270(w, mode, x, id, sz, D_003F1A60);
}

s32 func_001f9230(TextWin *w, s32 mode, s32 x, u8 *s, s32 sz) {
    return func_001f92b0(w, mode, x, s, sz, D_003F1A60);
}

void func_001f9250(TextWin *w, s32 mode, s32 x, u8 *s, s32 sz) {
    func_001f92f0(w, mode, x, s, sz, D_003F1A60);
}

s32 func_001f9270(TextWin *w, s32 mode, s32 x, s32 id, s32 sz, u32 col) {
    return func_001f9438(w, mode, x, (20 - sz) / 2 + 2, id, sz, col);
}

s32 func_001f92b0(TextWin *w, s32 mode, s32 x, u8 *s, s32 sz, u32 col) {
    return func_001f94f0(w, mode, x, (20 - sz) / 2 + 2, s, sz, col);
}

void func_001f92f0(TextWin *w, s32 mode, s32 x, u8 *s, s32 sz, u32 col) {
    func_001f9e48(w, mode, x, (20 - sz) / 2 + 2, s, sz, col);
}

s32 func_001f9330(TextWin *w, s32 mode, s32 x, s32 y, s32 id) {
    return func_001f9378(w, mode, x, y, id, 18);
}

s32 func_001f9348(TextWin *w, s32 mode, s32 x, s32 y, u8 *s) {
    return func_001f9398(w, mode, x, y, s, 18);
}

void func_001f9360(TextWin *w, s32 mode, s32 x, s32 y, u8 *s) {
    func_001f93b8(w, mode, x, y, s, 18);
}

s32 func_001f9378(TextWin *w, s32 mode, s32 x, s32 y, s32 id, s32 sz) {
    return func_001f9438(w, mode, x, y, id, sz, D_003F1A60);
}

s32 func_001f9398(TextWin *w, s32 mode, s32 x, s32 y, u8 *s, s32 sz) {
    return func_001f94f0(w, mode, x, y, s, sz, D_003F1A60);
}

void func_001f93b8(TextWin *w, s32 mode, s32 x, s32 y, u8 *s, s32 sz) {
    func_001f9e48(w, mode, x, y, s, sz, D_003F1A60);
}

s32 func_001f93d8(TextWin *w, s32 mode, s32 x, s32 y, s32 id, u32 col) {
    return func_001f9438(w, mode, x, y, id, 18, col);
}

s32 func_001f93f8(TextWin *w, s32 mode, s32 x, s32 y, u8 *s, u32 col) {
    return func_001f94f0(w, mode, x, y, s, 18, col);
}

void func_001f9418(TextWin *w, s32 mode, s32 x, s32 y, u8 *s, u32 col) {
    func_001f9e48(w, mode, x, y, s, 18, col);
}

s32 func_001f9438(TextWin *w, s32 mode, s32 x, s32 y, s32 id, s32 sz, u32 col) {
    if (id == 0) return x;
    return func_001f94f0(w, mode, x, y, func_001efbb8(id), sz, col);
}

/* func_001f94f0 is in wintext.nostrict.c, func_001f9e48 in
 * wintext.nostrict_nogcse.c. */

s32 func_001fa318(TextWin *o, s32 mode, s32 x, s32 y, s32 id, s32 sz, u32 col, u32 ecol) {
    u8 *s;
    if (id == 0) return x;
    s = func_001efbb8(id);
    func_001f94f0(o, mode, x - 1, y - 1, s, sz, ecol);
    func_001f94f0(o, mode, x + 1, y - 1, s, sz, ecol);
    func_001f94f0(o, mode, x - 1, y + 1, s, sz, ecol);
    func_001f94f0(o, mode, x + 1, y + 1, s, sz, ecol);
    return func_001f94f0(o, mode, x, y, s, sz, col);
}

s32 func_001fa490(TextWin *arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4, s32 arg5, u32 arg6, u32 arg7) {
  s32 sp0;
  u32 sp4;
  s32 temp_s5;
  s32 temp_s5_2;
  s32 temp_s7;
  s32 temp_s8;
  temp_s5 = arg3 - 1;
  temp_s8 = arg2 - 1;
  sp0 = arg3;
  sp4 = arg6;
  func_001f94f0(arg0, arg1, temp_s8, temp_s5, arg4, arg5, arg7);
  temp_s7 = arg2 + 1;
  func_001f94f0(arg0, arg1, temp_s7, temp_s5, arg4, arg5, arg7);
  temp_s5_2 = sp0 + 1;
  func_001f94f0(arg0, arg1, temp_s8, temp_s5_2, arg4, arg5, arg7);
  func_001f94f0(arg0, arg1, temp_s7, temp_s5_2, arg4, arg5, arg7);
  return func_001f94f0(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}

void func_001fa5b0(TextWin *a, s32 mode, s32 x, s32 y, u8 *s, s32 sz, s32 c, s32 ec) {
    func_001f9e48(a, mode, x - 1, y - 1, s, sz, ec);
    func_001f9e48(a, mode, x + 1, y - 1, s, sz, ec);
    func_001f9e48(a, mode, x - 1, y + 1, s, sz, ec);
    func_001f9e48(a, mode, x + 1, y + 1, s, sz, ec);
    func_001f9e48(a, mode, x, y, s, sz, c);
}

s32 func_001fa6d0(TextWin *w, s32 y, s32 id) {
    return func_001fa718(w, y, id, 18);
}

s32 func_001fa6e8(TextWin *w, s32 y, u8 *s) {
    return func_001fa748(w, y, s, 18);
}

void func_001fa700(TextWin *w, s32 y, u8 *s) {
    func_001fa778(w, y, s, 18);
}

s32 func_001fa718(TextWin *w, s32 y, s32 id, s32 sz) {
    return func_001f9378(w, 2, W32(w->xb8), y, id, sz);
}

s32 func_001fa748(TextWin *w, s32 y, u8 *s, s32 sz) {
    return func_001f9398(w, 2, W32(w->xb8), y, s, sz);
}

void func_001fa778(TextWin *w, s32 y, u8 *s, s32 sz) {
    func_001f93b8(w, 2, W32(w->xb8), y, s, sz);
}

s32 func_001fa7a8(TextWin *w, s32 y, s32 id, u32 col) {
    return func_001fa808(w, y, id, 18, col);
}

s32 func_001fa7c8(TextWin *w, s32 y, u8 *s, u32 col) {
    return func_001fa840(w, y, s, 18, col);
}

void func_001fa7e8(TextWin *w, s32 y, u8 *s, u32 col) {
    func_001fa878(w, y, s, 18, col);
}

s32 func_001fa808(TextWin *w, s32 y, s32 id, s32 sz, u32 col) {
    return func_001f9438(w, 2, W32(w->xb8), y, id, sz, col);
}

s32 func_001fa840(TextWin *w, s32 y, u8 *s, s32 sz, u32 col) {
    return func_001f94f0(w, 2, W32(w->xb8), y, s, sz, col);
}

void func_001fa878(TextWin *w, s32 y, u8 *s, s32 sz, u32 col) {
    func_001f9e48(w, 2, W32(w->xb8), y, s, sz, col);
}

/* func_001fa8b0 is in wintext.nostrict_nogcse.c. */

void func_001facd8(TextWin *a, s32 x, s32 y, u8 *s, s32 sz, s32 c, s32 ec) {
    func_001fa8b0(a, x - 1, y - 1, s, sz, ec);
    func_001fa8b0(a, x + 1, y - 1, s, sz, ec);
    func_001fa8b0(a, x - 1, y + 1, s, sz, ec);
    func_001fa8b0(a, x + 1, y + 1, s, sz, ec);
    func_001fa8b0(a, x, y, s, sz, c);
}

/* func_001fade0 is in wintext.nostrict.c. */

void func_001fb140(TextWin *a, s32 x, s32 y, s32 idx, s32 sz, s32 c, s32 ec) {
    func_001fade0(a, x - 1, y - 1, idx, sz, ec);
    func_001fade0(a, x + 1, y - 1, idx, sz, ec);
    func_001fade0(a, x - 1, y + 1, idx, sz, ec);
    func_001fade0(a, x + 1, y + 1, idx, sz, ec);
    func_001fade0(a, x, y, idx, sz, c);
}

void func_001fb248(TextWin *o, s32 x, s32 y, s32 code, s32 sz, s32 col) {
    func_001fade0(o, x, y, func_001eff50(code), sz, col);
}

void func_001fb2b8(TextWin *a, s32 x, s32 y, s32 code, s32 sz, s32 c, s32 ec) {
    func_001fb248(a, x - 1, y - 1, code, sz, ec);
    func_001fb248(a, x + 1, y - 1, code, sz, ec);
    func_001fb248(a, x - 1, y + 1, code, sz, ec);
    func_001fb248(a, x + 1, y + 1, code, sz, ec);
    func_001fb248(a, x, y, code, sz, c);
}

s32 func_001fb3c0(TextWin *o, s32 mode, s32 nd, s32 pad, s32 x, s32 y, s32 val) {
    return func_001fb408(o, mode, nd, pad, x, y, val, D_003F1A60);
}

s32 func_001fb3e0(TextWin *o, s32 mode, s32 nd, s32 pad, s32 x, s32 y, s32 val, s32 sz) {
    return func_001fb428(o, mode, nd, pad, x, y, val, sz, D_003F1A60);
}

s32 func_001fb408(TextWin *o, s32 mode, s32 nd, s32 pad, s32 x, s32 y, s32 val, u32 col) {
    return func_001fb428(o, mode, nd, pad, x, y, val, 18, col);
}

/* func_001fb428 is in wintext.nostrict_nogcse.c. */

s32 func_001fbb50(TextWin *o, s32 mode, s32 nd, s32 pad, s32 x, s32 y, s32 val, s32 sz, s32 col, s32 ecol) {
    func_001fb428(o, mode, nd, pad, x - 1, y - 1, val, sz, ecol);
    func_001fb428(o, mode, nd, pad, x + 1, y - 1, val, sz, ecol);
    func_001fb428(o, mode, nd, pad, x - 1, y + 1, val, sz, ecol);
    func_001fb428(o, mode, nd, pad, x + 1, y + 1, val, sz, ecol);
    return func_001fb428(o, mode, nd, pad, x, y, val, sz, col);
}

s32 func_001fbcb0(TextWin *o, s32 mode, s32 nd, s32 pad, s32 x, s32 y, s32 val, s32 alpha) {
    return func_001fbcd8(o, mode, nd, pad, x, y, val, alpha, 0x80808080);
}

/* func_001fbcd8 is in wintext.nostrict.c. */

s32 func_001fc308(TextWin *o, s32 x, s32 y, s32 w, s32 h, s32 idx, s32 a, u32 c0, u32 c1) {
    return func_001fc330(o, x, y, w, h, idx, a, c0, c0, c1, c1);
}

/* func_001fc330, func_001fc750 and func_001fcdc8 are in wintext.nostrict.c. */

/* Icons 57 and 56 (a shadow under a white one). */
void func_001fd070(TextWin *o, s32 x, s32 y) {
    func_001fc308(o, x, y, 0, 0, 57, 0, 0x64323296, 0x64323296);
    func_001fc308(o, x + 14, y + 6, 0, 0, 56, 0, 0x64ffffff, 0x64ffffff);
}

void func_001fd100(s32 x, s32 y) {
    func_001fcdc8(x, y, 0, 0, 57, 0, 0x64323296, 0x64323296);
    func_001fcdc8(x + 14, y + 6, 0, 0, 56, 0, 0x64ffffff, 0x64ffffff);
}

void func_001fd170(s32 x, s32 y, s32 a) {
    s32 c;

    c = func_001edd88(0x64323296, a);
    func_001fcdc8(x, y, 0, 0, 57, 0, c, func_001edd88(0x64323296, a));
    c = func_001edd88(0x64ffffff, a);
    func_001fcdc8(x + 14, y + 6, 0, 0, 56, 0, c, func_001edd88(0x64ffffff, a));
}
