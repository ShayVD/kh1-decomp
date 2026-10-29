/* score 182 (760 vs 752). Sprite setup: uploads image + CLUT via func_00f69278, builds x/y/q/s/t arrays and calls func_00f68ec0. Statements and call args are right. Left: the original computes the 4bpp defaults (w*h/128) before the bpp tests and recomputes w*h in the 8bpp arm (mine CSEs it; if/else-chain, switch and commuted h*w all tried), and it spills psm/c to the stack where mine spills y. */
typedef struct { u8 r, g, b, a; } Rgba;
extern u64 *D_0108F248;
extern s32 D_0108F25C;
u64 *func_00f69278(u64 *, u32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f68ec0(s32 *, s32 *, s32 *, s32 *, s32, s32, f32 *, f32 *, s32, s32, Rgba *, u64, s32, u64);

void func_00f696a0(u32 img, u32 clut, s32 x, s32 y, s32 w, s32 h, s32 bpp, Rgba *c, f32 sc, s32 flip, u64 alpha, s32 flag, u64 test)
{
    s32 xs[4];
    s32 ys[4];
    s32 un[4];
    s32 q[4];
    f32 s[4];
    f32 t[4];
    s32 psm, cw, ch, off, n, x0, x1, y0;
    f32 v;

    ch = 2;
    cw = 8;
    off = w * h / 128;
    psm = 20;
    if (bpp != 4) {
        if (bpp == 8) {
            psm = 19;
            cw = 16;
            ch = 16;
            off = w * h / 64;
        } else {
            psm = 0;
            ch = 0;
            cw = 0;
            off = 0;
        }
    }
    if (img) D_0108F248 = func_00f69278(D_0108F248, img, 0, 0, w, h, D_0108F25C, psm, w / 64, bpp);
    if (clut) D_0108F248 = func_00f69278(D_0108F248, clut, 0, 0, cw, ch, D_0108F25C + off, 0, 1, 32);
    x0 = (x + 1792) * 16;
    y0 = (y + 1856) * 16;
    if (flip == 0) {
        xs[3] = x0;
        x1 = x0 + (s32)(sc * w) * 16;
    } else {
        xs[3] = x0;
        x1 = x0 - (s32)(sc * w) * 16;
    }
    xs[2] = x0;
    xs[1] = x1;
    xs[0] = x1;
    q[0] = 1;
    q[3] = 1;
    q[2] = 1;
    q[1] = 1;
    ys[3] = y0;
    ys[1] = y0;
    ys[2] = ys[0] = y0 + (s32)(sc * h) * 16;
    for (n = 2; n < h; n *= 2)
        ;
    v = (f32)(h - 1) / (f32)n;
    s[0] = 1.0f;
    t[0] = v;
    s[3] = 0;
    t[3] = 0;
    s[2] = 0;
    t[2] = v;
    s[1] = 1.0f;
    t[1] = 0;
    func_00f68ec0(xs, ys, un, q, w, n, s, t, psm, off, c, alpha, flag, test);
}
