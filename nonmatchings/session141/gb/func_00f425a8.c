/* 30 words / score 39: structure right (switch on psm; x += 1792; x <<= 4). Left: a (2/16) and c (w*h/128) get s7/s5 instead of s5/s7 (tried every assignment order in all three cases, and declaration order), plus the xs/ws/ys store schedule (hill-climbed). */
extern s32 D_00F82A88;
extern s32 D_00F82A9C;
s32 func_00f42180(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f41dc8(s32 *, s32 *, s32 *, s32 *, s32, s32, f32 *, f32 *, s32, s32, s32, u64, s32, u64);

void func_00f425a8(s32 tex0, s32 tex1, s32 x, s32 y, s32 w, s32 h, s32 psm, s32 a7, f32 s, s32 flip, u64 a9, s32 a10, u64 a11) {
    s32 xs[4];
    s32 ys[4];
    s32 zs[4];
    s32 ws[4];
    f32 us[4];
    f32 vs[4];
    s32 a, b, c, k, p, d, e;
    switch (psm) {
    case 4:
        a = 2;
        b = 8;
        c = w * h / 128;
        k = 20;
        break;
    case 8:
        k = 19;
        b = 16;
        a = 16;
        c = w * h / 64;
        break;
    default:
        c = 0;
        b = 0;
        a = 0;
        k = 0;
        break;
    }
    if (tex0)
        D_00F82A88 = func_00f42180(D_00F82A88, tex0, 0, 0, w, h, D_00F82A9C, k, w / 64, psm);
    if (tex1)
        D_00F82A88 = func_00f42180(D_00F82A88, tex1, 0, 0, b, a, D_00F82A9C + c, 0, 1, 32);
    x += 1792;
    x <<= 4;
    y += 1856;
    y <<= 4;
    d = (s32)(s * w);
    if (flip == 0) {
        xs[3] = x;
        d = x + (d << 4);
    } else {
        xs[3] = x;
        d = x - (d << 4);
    }
    xs[2] = x;
    xs[1] = d;
    xs[0] = d;
    ys[3] = y;
    ys[1] = y;
    e = y + ((s32)(s * h) << 4);
    ys[0] = e;
    ys[2] = e;
    ws[0] = 1;
    ws[1] = 1;
    ws[3] = 1;
    ws[2] = 1;
    for (p = 2; p < h; p <<= 1)
        ;
    vs[0] = (f32)(h - 1) / (f32)p;
    us[3] = 0.0f;
    vs[3] = 0.0f;
    us[2] = 0.0f;
    vs[2] = vs[0];
    us[1] = 1.0f;
    us[0] = 1.0f;
    vs[1] = 0.0f;
    func_00f41dc8(xs, ys, zs, ws, w, p, us, vs, k, c, a7, a9, a10, a11);
}
