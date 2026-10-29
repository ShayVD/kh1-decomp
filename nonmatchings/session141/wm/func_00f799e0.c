/* 68 words, score 89 (was 72/93). Round 32 wwm2: hill2 reordered the x/y adjust, the xs[] stores in both branches (xs[0], xs[1] first) and the us/vs stores; ctx2 and interleave give nothing. Earlier header: score 93 (72 words; 716 vs 712 bytes), was 115. Ported back from func_00f693e0 (same code plus the trailing 4 argument): `(nv = bpp) == 8` with an unsigned long nv fixes the bpp branch block. Left: the y/h register swap, img in t5 instead of t1, and store order. Earlier note: size divide matches via t temp (t = w*h; t /= 128). */
#include "ovl.h"

extern void *D_0108FA60;
extern s32 D_00FB64A4;
void *func_00f79700(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f792c8(s32 *, s32 *, s32 *, s32 *, s32, s32, f32 *, f32 *, s32, s32, s32, u64, s32, u64, s32);

void func_00f799e0(void *img, void *clut, s32 x, s32 y, s32 w, s32 h, s32 bpp, s32 a7, s32 flip, u64 a9, s32 a10, u64 a11) {
    s32 xs[4];
    s32 ys[4];
    s32 zs[4];
    s32 qs[4];
    f32 us[4];
    f32 vs[4];
    s32 psm;
    s32 cw, ch, size;
    s32 p;
    s32 t;
    unsigned long nv;
    s32 x1, y1;
    f32 v;

    t = w * h;
    t /= 128;
    size = t;
    psm = 20;
    cw = 8;
    ch = 2;
    if (bpp != 4) {
        if ((nv = bpp) == 8) {
            psm = 19;
            cw = 16;
            ch = 16;
            t = w * h;
            t /= 64;
            size = t;
        } else {
            psm = 0;
            ch = 0;
            cw = 0;
            size = 0;
        }
    }
    if (img) {
        D_0108FA60 = func_00f79700(D_0108FA60, img, 0, 0, w, h, D_00FB64A4, psm, w / 64, bpp);
    }
    if (clut) {
        D_0108FA60 = func_00f79700(D_0108FA60, clut, 0, 0, cw, ch, D_00FB64A4 + size, 0, 1, 32);
    }
    x += 1792;
    x <<= 4;
    y += 1856;
    y <<= 4;
    if (flip == 0) {
        xs[0] = x + w * 16;
        xs[2] = x;
        xs[1] = x + w * 16;
        xs[3] = x;
    } else {
        xs[0] = x - w * 16;
        xs[1] = x - w * 16;
        xs[2] = x;
        xs[3] = x;
    }
    y1 = y + h * 16;
    ys[2] = y1;
    ys[3] = y;
    qs[0] = 1;
    ys[0] = y1;
    ys[1] = y;
    qs[3] = 1;
    qs[2] = 1;
    qs[1] = 1;
    for (p = 2; p < h; p <<= 1) {
    }
    v = (f32)(h - 1) / (f32)p;
    vs[3] = 0.0f;
    us[2] = 0.0f;
    vs[2] = v;
    us[1] = 1.0f;
    vs[1] = 0.0f;
    vs[0] = v;
    us[0] = 1.0f;
    us[3] = 0.0f;
    func_00f792c8(xs, ys, zs, qs, w, h, us, vs, psm, size, a7, a9, a10, a11, 4);
}
