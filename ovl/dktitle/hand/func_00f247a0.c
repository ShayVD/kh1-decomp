/* dktitle.x func_00f247a0: matched by hand. */
#include "ovl.h"

u64 *func_00f241c8(u64 *pk, u32 addr, s32 dx, s32 dy, s32 w, s32 h, s32 dbp, s32 dpsm, s32 dbw, s32 bpp);
void func_00f24330(s32 *x, s32 *y, s32 *z, s32 *q, s32 w, s32 h, f32 *s, f32 *t,
                   s32 psm, s32 cbp, s32 col, u8 *rgba, s64 r1, s32 flag, s64 r2, s32 n, u64 *pk, s32 tbp);

void func_00f247a0(u32 tex, u32 clut, s32 x, s32 y, s32 w, s32 h, s32 bpp, u8 *rgba, s32 flip, s64 r1, s32 flag, s64 r2, u64 *pk, s32 tbp) {
    s32 xs[4];
    s32 ys[4];
    s32 zs[4];
    s32 qs[4];
    f32 ss[4];
    f32 ts[4];
    s32 psm, cw, ch, cbp;
    s32 n;
    f32 v;

    switch (bpp) {
    case 4: psm = 20; cw = 8; ch = 2; cbp = w * h / 128; break;
    case 8: psm = 19; cw = 16; ch = 16; cbp = w * h / 64; break;
    default: psm = 0; ch = 0; cw = 0; cbp = 0; break;
    }
    if (tex) {
        pk = func_00f241c8(pk, tex, 0, 0, w, h, tbp, psm, w / 64, bpp);
    }
    if (clut) {
        pk = func_00f241c8(pk, clut, 0, 0, cw, ch, tbp + cbp, 0, 1, 32);
    }
    x += 0x700; y += 0x740; x *= 16; y *= 16;
    if (flip == 0) {
        xs[0] = x + w * 16; xs[1] = x + w * 16; xs[2] = x; xs[3] = x;
    } else {
        xs[0] = x - w * 16; xs[1] = x - w * 16; xs[2] = x; xs[3] = x;
    }
    ys[0] = y + h * 16;
    ys[2] = y + h * 16;
    ys[1] = y;
    ys[3] = y;
    qs[0] = qs[1] = qs[2] = qs[3] = 1;
    n = 2;
    while (n < h) n *= 2;
    v = (f32)(h - 1) / (f32)n;
    ss[3] = 0.0f;
    ts[3] = 0.0f;
    ss[2] = 0.0f;

    ts[2] = v;
    ss[1] = 1.0f;
    ss[0] = 1.0f;
    ts[1] = 0.0f;
    ts[0] = v;

    func_00f24330(xs, ys, zs, qs, w, n, ss, ts, psm, cbp, 1, rgba, r1, flag, r2, 4, pk, tbp);
}
