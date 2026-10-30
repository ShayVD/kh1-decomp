/* Round 36 (wgb): gb.x func_00f422e8 near miss: 65 -> 65 words, score 77 -> 73 (aligned diff 46 -> 42). Statement order from tools/ovl/hill3.py (score-ranked, strict dependency rules). Tried: hill3 sweep of every gb RANKING row and wm RANKING rows 1-100 (85-90 s, seed 1; strict rules; the order kept passes hill3.py --check against the previous draft), and port.py from the twin (not better). Earlier header below. */
/* Round 35 (wgb): gb.x func_00f422e8 near miss: 71 -> 65 words, score 89 -> 77. Statement order from a dependency-safe statement-order hill climb (round 35 hill3.py: only orders that keep every read/write conflict in place) (size and psm computed after the defaults, y before x for the shifts, xs/ys/qs/us/vs store order). Left: scheduling in the vertex block and the 708 vs 704 size. Tried: ctx2 (no change). Earlier header below. */
/* gb.x func_00f422e8 near miss: 71 words differ, score 89 (ours 708 bytes, original 704). Port of wm func_00f693e0's near miss (port.py), not worked further this round. Its notes apply: y and h swap s3/s4, img lands in t5 instead of t1, and store order. */
extern void *D_00F82A88;
extern s32 D_00F82A9C;
void *func_00f42180(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f41dc8(s32 *, s32 *, s32 *, s32 *, s32, s32, f32 *, f32 *, s32, s32, s32, u64, s32, u64);

void func_00f422e8(void *img, void *clut, s32 x, s32 y, s32 w, s32 h, s32 bpp, s32 a7, s32 flip, u64 a9, s32 a10, u64 a11) {
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

    ch = 2;
    t = w * h;
    psm = 20;
    t /= 128;
    size = t;
    cw = 8;
    if (bpp != 4) {
        if ((nv = bpp) == 8) {
            cw = 16;
            t = w * h;
            psm = 19;
            t /= 64;
            ch = 16;
            size = t;
        } else {
            ch = 0;
            psm = 0;
            cw = 0;
            size = 0;
        }
    }
    if (img) {
        D_00F82A88 = func_00f42180(D_00F82A88, img, 0, 0, w, h, D_00F82A9C, psm, w / 64, bpp);
    }
    if (clut) {
        D_00F82A88 = func_00f42180(D_00F82A88, clut, 0, 0, cw, ch, D_00F82A9C + size, 0, 1, 32);
    }
    x += 1792;
    x <<= 4;
    y += 1856;
    y <<= 4;
    if (flip == 0) {
        xs[2] = x;
        xs[0] = x + w * 16;
        xs[1] = x + w * 16;
        xs[3] = x;
    } else {
        xs[2] = x;
        xs[0] = x - w * 16;
        xs[1] = x - w * 16;
        xs[3] = x;
    }
    y1 = y + h * 16;
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
    func_00f41dc8(xs, ys, zs, qs, w, h, us, vs, psm, size, a7, a9, a10, a11);
}
