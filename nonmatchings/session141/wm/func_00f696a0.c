/* Round 50 (wgb): score 29 -> 15, port.py of gb func_00f425a8 (see that file). Earlier header below. */
/* drafttwins.py: score 31 -> 29, port.py of the gb twin func_00f425a8 draft. Earlier header below. */
/* Round 42 wwm2: score 35 -> 31, store order from r42/hill3o.py (score-ranked, dependency-safe, distinct array elements may swap): ws[1] and ys[3] before xs[0], xs[new_var] last. The float-store block (us/vs) gave nothing in 300 iterations. Earlier header below. */
extern s32 D_0108F248;
extern s32 D_0108F25C;
s32 func_00f69278(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f68ec0(s32 *, s32 *, s32 *, s32 *, s32, s32, f32 *, f32 *, s32, s32, s32, u64, s32, u64);
void func_00f696a0(s32 tex0, s32 tex1, s32 x, s32 y, s32 w, s32 h, s32 bpp, s32 a7, f32 s, s32 flip, u64 a9, s32 a10, u64 a11) {
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
    psm = 20;
    ch = 2;
    t /= 128;
    size = t;
    if (bpp != 4) {
        if ((nv = bpp) == 8) {
            cw = 16;
            t2 = w * h;
            psm = 19;
            t2 /= 64;
            ch = 16;
            size = t2;
        } else {
            ch = 0;
            psm = 0;
            size = 0;
            cw = 0;
        }
    }
    if (tex0) {
        D_0108F248 = func_00f69278(D_0108F248, tex0, 0, 0, w, h, D_0108F25C, psm, w / 64, bpp);
    }
    if (tex1) {
        D_0108F248 = func_00f69278(D_0108F248, tex1, 0, 0, cw, ch, D_0108F25C + size, 0, 1, 32);
    }
    x += 1792;
    x <<= 4;
    y += 1856;
    y <<= 4;
    d = (s32)(s * w);
    if (flip == 0) {
        xs[2] = x;
        xs[0] = x + (d << 4);
        xs[1] = x + (d << 4);
        xs[3] = x;
    } else {
        xs[2] = x;
        xs[0] = x - (d << 4);
        xs[1] = x - (d << 4);
        xs[3] = x;
    }
    y1 = y + ((s32)(s * h) << 4);
    ys[0] = y1;
    ys[2] = y1;
    ys[1] = y;
    qs[3] = 1;
    qs[2] = 1;
    qs[1] = 1;
    ys[3] = y;
    qs[0] = 1;
    for (p = 2; p < h; p <<= 1) {
    }
    v = (f32)(h - 1) / (f32)p;
    us[3] = 0.0f;
    vs[3] = 0.0f;
    us[2] = 0.0f;
    vs[2] = v;
    us[1] = 1.0f;
    us[0] = 1.0f;
    vs[0] = v;
    vs[1] = 0.0f;
    func_00f68ec0(xs, ys, zs, qs, w, p, us, vs, psm, size, a7, a9, a10, a11);
}
