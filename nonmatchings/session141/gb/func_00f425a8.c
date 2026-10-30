/* Round 52 (wgb): score 15 -> 3, statement order from tools/ovl/hill3.py (240 s, seed 52; the same lines, every move keeps its dependencies, checked by hand). Left: the two move ..,zero of the bpp-not-4/8 branch get s7/s6 where the target has s6/s7; all 24 orders of that branch and 10 chained forms give 3 or worse, and a second hill3 run (seed 7) stays at 3. Earlier header below. */
/* Round 50 (wgb): score 29 -> 15. Rewritten on the head of the matched gb func_00f422e8 (same bpp 4/8 block and func_00f42180 calls, with t2 for the bpp == 8 w * h) and its vertex block with the s scale; then cw = 8 first in the defaults, ch = 2 third, and size = 0 before cw = 0 in the zero branch (sweeps over the default order, the declaration order of cw/ch/size and both branch orders). Left: cw and size take s7/s6 where the target has s6/s7 (7 words, plus the trailing nop). Earlier header below. */
/* Round 41 (wgb): score 31 -> 29, statement order from hill3 (120 s, seed 41, default mode). Earlier header below. */
/* Round 42 wwm2: score 35 -> 31, port.py of the wm twin func_00f696a0 draft. Earlier header below. */
/* 25 words / score 35 (permuter round 3, from 30/39). Left: s5/s7 swap for the two zeroed counters, and the stack-store schedule of the f41dc8 argument block. Tried every assignment order, declaration order, and a hill-climb on the store schedule. */
extern s32 D_00F82A88;
extern s32 D_00F82A9C;
s32 func_00f42180(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f41dc8(s32 *, s32 *, s32 *, s32 *, s32, s32, f32 *, f32 *, s32, s32, s32, u64, s32, u64);
void func_00f425a8(s32 tex0, s32 tex1, s32 x, s32 y, s32 w, s32 h, s32 bpp, s32 a7, f32 s, s32 flip, u64 a9, s32 a10, u64 a11) {
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
    s32 t2;
    unsigned long nv;
    s32 d, y1;
    f32 v;

    cw = 8;
    t = w * h;
    t /= 128;
    psm = 20;
    ch = 2;
    size = t;
    if (bpp != 4) {
        if ((nv = bpp) == 8) {
            psm = 19;
            cw = 16;
            ch = 16;
            t2 = w * h;
            t2 /= 64;
            size = t2;
        } else {
            ch = 0;
            size = 0;
            psm = 0;
            cw = 0;
        }
    }
    if (tex0) {
        D_00F82A88 = func_00f42180(D_00F82A88, tex0, 0, 0, w, h, D_00F82A9C, psm, w / 64, bpp);
    }
    if (tex1) {
        D_00F82A88 = func_00f42180(D_00F82A88, tex1, 0, 0, cw, ch, D_00F82A9C + size, 0, 1, 32);
    }
    x += 1792;
    y += 1856;
    y <<= 4;
    x <<= 4;
    d = (s32)(s * w);
    if (flip == 0) {
        xs[2] = x;
        xs[0] = x + (d << 4);
        xs[3] = x;
        xs[1] = x + (d << 4);
    } else {
        xs[0] = x - (d << 4);
        xs[1] = x - (d << 4);
        xs[2] = x;
        xs[3] = x;
    }
    y1 = y + ((s32)(s * h) << 4);
    ys[1] = y;
    ys[0] = y1;
    qs[3] = 1;
    ys[2] = y1;
    qs[2] = 1;
    ys[3] = y;
    qs[1] = 1;
    qs[0] = 1;
    for (p = 2; p < h; p <<= 1) {
    }
    us[3] = 0.0f;
    vs[3] = 0.0f;
    us[2] = 0.0f;
    v = (f32)(h - 1) / (f32)p;
    vs[2] = v;
    us[1] = 1.0f;
    vs[1] = 0.0f;
    vs[0] = v;
    us[0] = 1.0f;
    func_00f41dc8(xs, ys, zs, qs, w, p, us, vs, psm, size, a7, a9, a10, a11);
}
