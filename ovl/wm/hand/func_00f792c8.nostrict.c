/* wm.x func_00f792c8: matched by hand. */
#include "ovl.h"

typedef struct { u64 lo, hi; } GQ;
typedef union { kh1_u128 q; u32 w[4]; GQ d; f32 f[4]; } GPkt;
extern GPkt *D_0108FA60;
extern s32 D_00FB64A4;
static inline void ad(GQ *q, u64 v, u64 r) {
    q->lo = v;
    q->hi = r;
}
static inline void lg(s32 *pr, s32 v) {
    s32 r = 1;
    if (v > 16) r = 5;
    if (v > 32) r = 6;
    if (v > 64) r = 7;
    if (v > 128) r = 8;
    if (v > 256) r = 9;
    if (v > 512) r = 10;
    *pr = r;
}
typedef struct { u8 r, g, b, a; } Rgba;
void func_00f792c8(s32 *x, s32 *y, s32 unused, s32 *q, s32 w, s32 h, f32 *s, f32 *t, s32 psm, s32 cbp, Rgba *c, u64 alpha, s32 flag, u64 test, s32 cnt) {
    GPkt *p = D_0108FA60;
    s32 tw, th, n, i;
    s32 tbp, cbs;
    u32 *o;
    u32 cr, cg, cb, ca;
    tbp = D_00FB64A4;
    cbs = tbp + cbp;
    lg(&tw, w);
    lg(&th, h);
    p[0].q = KH1_Q(0);
    if (flag) {
        p[1].d.lo = 0x1000000000000007;
    } else {
        p[1].d.lo = 0x1000000000000006;
    }
    p[1].d.hi = 14;
    ad(&p[2].d, 0, 0x3F);
    ad(&p[3].d, tbp | (u64)(w / 64) << 14 | (u64)psm << 20 | (u64)tw << 26 | (u64)th << 30 | (u64)1 << 34 | (u64)cbs << 37 | (u64)1 << 61, 6);
    ad(&p[4].d, alpha, 0x42);
    ad(&p[5].d, test, 0x47);
    ad(&p[6].d, 0, 0x49);
    ad(&p[7].d, 0x60, 0x14);
    n = 8;
    if (flag) {
        do {} while (0);
        ad(&p[n++].d, (u64)flag << 32 | 0x800D0, 0x4C);
        if (cnt == 3) {
            p[n].d.lo = 0x9009C00000000001;
        } else {
            p[n].d.lo = (u64)(cnt * 3) << 60 | 0x000A400000000001;
        }
    } else {
        if (cnt == 3) {
            p[n].d.lo = 0x9029C00000008001;
        } else {
            p[n].d.lo = (u64)(cnt * 3) << 60 | 0x002A400000008001;
        }
    }
    p[n].d.hi = 0x412412412412;
    n++;
    cr = c->r;
    cg = c->g;
    cb = c->b;
    ca = c->a;
    i = 0;
    if (cnt > 0) {
        u32 ff = 0xFFFFFF;
        o = (u32 *)(n * 16 + (s32)p);
        do {
            f32 z = q[i];
            ((f32 *)o)[0] = s[i] / z;
            ((f32 *)o)[1] = t[i] / z;
            o[3] = 0;
            ((f32 *)o)[2] = 1.0f / z;
            o += 4;
            o[0] = cr;
            o[1] = cg;
            o[2] = cb;
            o[3] = ca;
            o += 4;
            o[0] = x[i];
            o[1] = y[i];
            o[2] = ff;
            o[3] = 0;
            o += 4;
            n += 3;
        } while (++i < cnt);
    }
    if (flag) {
        ad(&p[n++].d, 0x1000000000008001, 14);
        ad(&p[n++].d, 0x800D0, 0x4C);
    }
    p[0].w[0] = (n - 1) | 0x10000000;
    D_0108FA60 = p + n;
}
