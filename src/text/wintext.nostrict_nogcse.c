/* The functions of src/text/wintext.c that need nostrict and nogcse
 * (docs/modules.md "Session 37"): func_001f9e48 draws a two-byte string in
 * a text window, func_001fa8b0 an ASCII one (D_003E8D40 maps it to glyphs)
 * and func_001fb428 a number (D_003E8CD0 the minus sign, D_003E8CD8 the
 * digits), scaled like func_001f94f0 (wintext.nostrict.c). */
#include "common.h"
#include "platform/gs.h"
#include "platform/dma.h"
#include "text/textwin.h"
#include "data/pieces/D_003E8E28.h"
#include "data/pieces/D_003F2270.h"

typedef Glyph_3e8e28 Glyph;
typedef struct { u64 d0; u64 d1; s32 w[16]; } GP;

extern Glyph *D_003E8CD0;
extern Glyph *D_003E8CD8[];
extern s32 D_003E8D00[];
extern u16 D_003E8D40[];
extern s32 D_003E8E00;
extern s32 D_003E8E04;
extern s32 D_003F1A64;
extern s32 D_003F2BD0;
extern s32 D_003F2BD4;

u64 *func_00122048(s32, s32);
void func_001220b8(void *);
u32 func_001edd88(u32, s32);
s32 func_001eff50(s32);
s32 func_001f0340(u8 *, s32);
s32 func_001f4570(TextWin *);
s32 func_001f45e0(TextWin *);

KH1_V0(s32) func_001f9e48(TextWin *o, s32 mode, s32 x, s32 y, u8 *s, s32 sz, s32 col) {
    u64 *base;
    u32 tag;
    s32 sz16;
    s32 org;
    s32 fl;
    s32 ax, ay;
    u64 *q;
    s32 xx, yy, ox;
    f32 fx, fy;
    s32 c;
    s32 n;
    Glyph *g;
    s32 w, wp, f2, f4;
    u8 f7;
    s32 x40, y44, ww, a;
    u64 tex;
    f32 fa, fb, t0, t1, t2, t3;


    PlatDmaSend(PlatDmaGetChan(2), &D_003F2270);
    sz16 = sz * 16;
    base = func_00122048(1024, 128);
    q = base + 2;
    tag = ((u32)base & 0x0fffffff) | 0x80000000;
    q[0] = 0x4000000000000001;
    q[1] = 0xeeee;
    q[3] = 63;
    q[4] = 0x4007ff8001300000;
    q[2] = 0;
    q[5] = 22;
    q[6] = 68;
    q[7] = 66;
    q[8] = func_001edd88(col, o->x90);
    q[9] = 1;
    q[10] = 0x50ab400000008001;
    q[11] = 0x4343e;
    base[0] = 0x7000000b;
    q = base + 14;
    org = o->xb4;
    yy = org + y * 16;
    ox = o->xb0;
    switch (mode) {
    case 0:
    default:
        xx = ox + x * 16;
        break;
    case 1:
        xx = ox + (x - func_001f0340(s, sz)) * 16;
        break;
    case 2:
        xx = ox + (x - func_001f0340(s, sz) / 2) * 16;
        break;
    }
    fl = o->u48.w.lo & 1;
    if (fl) {
        ax = func_001f4570(o);
        ay = func_001f45e0(o);
        fx = o->x74;
        fy = o->x78;
    }
    n = 18;
    for (;;) {
        c = *s;
        if (c == 0) goto done;
        if (c == '\n') {
            s++;
            yy += D_003F1A64;
            switch (mode) {
            case 0:
            default:
                xx = ox + x * 16;
                break;
            case 1:
                xx = ox + (x - func_001f0340(s, sz)) * 16;
                break;
            case 2:
                xx = ox + (x - func_001f0340(s, sz) / 2) * 16;
                break;
            }
            continue;
        }
        c |= s[1] << 8;
        s += 2;
        if (c == 0x4081) {
            xx += (sz << 8) / n;
            continue;
        }
        g = &D_003E8E28[func_001eff50(c)];
        w = g->w << 4;
        f2 = g->f2;
        a = w * sz / n;
        x40 = xx + a;
        f7 = g->f7;
        ww = w + D_003E8E00;
        tex = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        wp = ww * sz / n;
        f4 = g->f4;
        ((GP *)q)->d1 = 22;
        ((GP *)q)->d0 = tex;
        ((GP *)q)->w[12] = x40;
        ((GP *)q)->w[4] = xx;
        ((GP *)q)->w[7] = 0x8000;
        ((GP *)q)->w[8] = f2 + w;
        ((GP *)q)->w[9] = f4 + 288;
        ((GP *)q)->w[0] = f2;
        ((GP *)q)->w[1] = f4;
        ((GP *)q)->w[5] = yy;
        ((GP *)q)->w[6] = 0x100000;
        y44 = yy + sz16;
        ((GP *)q)->w[13] = y44;
        ((GP *)q)->w[14] = 0x100000;
        ((GP *)q)->w[15] = 0;
        if (fl) {
            s32 d0 = xx - ax, d1 = yy - ay, d2 = x40 - ax, d3 = y44 - ay;
            fa = ax;
            fb = ay;
            t0 = fa + d0 * fx;
            t1 = fb + d1 * fy;
            t2 = fa + d2 * fx;
            t3 = fb + d3 * fy;
            ((GP *)q)->w[12] = t2;
            ((GP *)q)->w[13] = t3;
            ((GP *)q)->w[4] = t0;
            ((GP *)q)->w[5] = t1;
        }
        xx += wp;
        PlatDmaSend(PlatDmaGetChan(2), (void *)tag);
        PlatGsSyncPath(0, 0);
        continue;
    }
done:
    func_001220b8(base);
    D_003F2BD0 = (xx - ox) >> 4;
    D_003F2BD4 = (yy - org) >> 4;
    KH1_V0_RETURN(D_003F2BD0);
}

/* func_001fa8b0 (hand/nostrict_nogcse): s9 w6 12w draft + `cm = c - 32; k = D_003E8D40[cm];` and a FLAGGED dead FP test `if ((f32)cm < (f32)n) a = 0;` after `x40 = xx + a;` (cm read in a later block -> global, so local-alloc no longer gives the c-32 chain v0; flow2 deletes the test). checkfile MATCH. */
void func_001fa8b0(TextWin *o, s32 x, s32 y, u8 *s, s32 sz, s32 col) {
    u64 *base;
    u32 tag;
    s32 sz16;
    s32 ox;
    s32 org;
    s32 fl;
    s32 x16;
    s32 ax, ay;
    u64 *q;
    s32 xx, yy;
    f32 fx, fy;
    u32 c;
    s32 n, z, k, cm;
    Glyph *g;
    s32 w, wp, f2, f4;
    u8 f7;
    s32 x40, y44, ww, a;
    u64 tex;
    f32 fa, fb, t0, t1, t2, t3;



    PlatDmaSend(PlatDmaGetChan(2), &D_003F2270);
    x16 = x * 16;
    sz16 = sz * 16;
    base = func_00122048(1024, 128);
    q = base + 2;
    tag = ((u32)base & 0x0fffffff) | 0x80000000;
    q[0] = 0x4000000000000001;
    q[1] = 0xeeee;
    q[3] = 63;
    q[4] = 0x4007ff8001300000;
    q[2] = 0;
    q[5] = 22;
    q[6] = 68;
    q[7] = 66;
    q[8] = func_001edd88(col, o->x90);
    q[9] = 1;
    q[10] = 0x50ab400000008001;
    q[11] = 0x4343e;
    base[0] = 0x7000000b;
    q = base + 14;
    ox = o->xb0;
    fl = o->u48.w.lo & 1;
    org = o->xb4;
    xx = ox + x16;
    yy = org + y * 16;
    if (fl) {
        ax = func_001f4570(o);
        ay = func_001f45e0(o);
        fx = o->x74;
        fy = o->x78;
    }
    n = 18;
    z = 0x100000;
    for (;;) {
        c = *s;
        if (c == 0) goto done;
        if (c == '\n') {
            s++;
            yy += D_003F1A64;
            xx = ox + x16;
            continue;
        }
        s++;
        if (c < 31) continue;
        if (c == ' ') {
            xx += (sz << 8) / n;
            continue;
        }
        if (c >= 128) continue;
/*P*/
        cm = c - 32;
        k = D_003E8D40[cm];
        g = &D_003E8E28[k];
        f2 = g->f2;
        w = g->w << 4;
        ww = w + D_003E8E00;
        wp = ww * sz / n;
        f4 = g->f4;
        a = w * sz / n;
        f7 = g->f7;
        tex = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        ((GP *)q)->w[0] = f2;
        ((GP *)q)->d0 = tex;
        y44 = yy + sz16;
        ((GP *)q)->d1 = 22;
        ((GP *)q)->w[7] = 0x8000;
        ((GP *)q)->w[8] = f2 + w;
        ((GP *)q)->w[5] = yy;
        ((GP *)q)->w[4] = xx;
        ((GP *)q)->w[1] = f4;
        x40 = xx + a;
        if ((f32)cm < (f32)n) a = 0; /* FLAGGED dead FP test: makes cm = c - 32 global (read in a later block); flow2 deletes it */
        ((GP *)q)->w[12] = x40;
        ((GP *)q)->w[6] = z;
        ((GP *)q)->w[14] = z;
        ((GP *)q)->w[9] = f4 + 288;
        ((GP *)q)->w[15] = 0;
        ((GP *)q)->w[13] = y44;
/*Q*/
        if (fl) {
            fa = ax;
            fb = ay;
            t0 = fa + (xx - ax) * fx;
            t1 = fb + (yy - ay) * fy;
            t2 = fa + (x40 - ax) * fx;
            t3 = fb + (y44 - ay) * fy;
            ((GP *)q)->w[4] = t0;
            ((GP *)q)->w[5] = t1;
            ((GP *)q)->w[12] = t2;
            ((GP *)q)->w[13] = t3;
        }
        xx += wp;
        PlatDmaSend(PlatDmaGetChan(2), (void *)tag);
        PlatGsSyncPath(0, 0);
    }
done:
    func_001220b8(base);
    D_003F2BD0 = (xx - ox) >> 4;
    D_003F2BD4 = (yy - org) >> 4;
}

/* func_001fb428 (s11w9): t (w*sz/18) is one function-level variable shared by the neg block and
   the digit loop (a global pseudo, so local-alloc cannot tie it to x0 + t); x1 is block-local in
   the loop (its own pseudo, v0); neg block statement order hill-climbed. */
KH1_V0(s32) func_001fb428(TextWin *o, s32 mode, u32 nd, s32 pad, s32 x, s32 y, s32 val, s32 sz, u32 col) {
    s32 dig[12];
    s32 mode2;
    s32 x2, y2, sz2;
    u64 *start;
    u32 tag;
    u64 *hdr;
    s32 adv;
    s32 neg;
    s32 ox, oy;
    s32 fl;
    u64 *base, *p;
    s32 n, i;
    s32 yy, sz16, t, w;
    s32 ax, ay;
    f32 fx, fy;
    Glyph *g;
    s32 f2, f4;
    u8 f7;
    u64 tex;
    s32 x0, x1, y1;
    f32 fa, fb, t0, t1, t2, t3;

    PlatDmaSend(PlatDmaGetChan(2), &D_003F2270);
    neg = 0;
    base = func_00122048(1024, 128);
    p = base + 2;
    tag = ((u32)base & 0x0fffffff) | 0x80000000;
    p[0] = 0x4000000000000001;
    p[2] = 0;
    p[1] = 0xeeee;
    p[3] = 63;
    p[4] = 0x4007ff8001300000;
    hdr = base + 12;
    p[5] = 22;
    p[6] = 68;
    p[7] = 66;
    p[8] = func_001edd88(col, o->x90);
    p[9] = 1;
    p = base + 14;
    start = p;
    if (val == 0) {
        if (nd == 0 || pad == 0) {
            dig[0] = 0;
            n = 1;
        } else {
            for (i = nd - 1; i >= 0; i--) dig[i] = 0;
            n = nd;
        }
    } else {
        if (val < 0) {
            val = -val;
            neg = 1;
        }
        n = 0;
        if (nd == 0) {
            do {
                dig[n++] = val % 10;
                val /= 10;
                if (val == 0) break;
            } while (n < 10);
        } else if (pad == 0) {
            do {
                dig[n++] = val % 10;
                val /= 10;
                if (val == 0) break;
            } while (n < nd);
        } else {
            do {
                if (val == 0) {
                    dig[n] = 0;
                    n++;
                } else {
                    dig[n] = val % 10;
                    val /= 10;
                    n++;
                }
            } while (n < nd);
        }
    }
    ox = o->xb0;
    sz16 = sz * 16;
    oy = o->xb4;
    val = ox + x * 16;
    yy = oy + y * 16;
    adv = sz16 + D_003E8E04;
    switch (mode) {
    case 1:
        val -= (n + neg) * adv;
        break;
    case 2:
        val -= (n + neg) * adv / 2;
        break;
    case 0:
    default:
        break;
    }
    fl = o->u48.w.lo & 1;
    if (fl) {
        ax = func_001f4570(o);
        ay = func_001f45e0(o);
        fx = o->x74;
        fy = o->x78;
    }
    if (neg) {
        Glyph *g;
        g = D_003E8CD0;
        w = g->w << 4;
        f7 = g->f7;
        f4 = g->f4;
        tex = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        t = w * sz / 18;
        f2 = g->f2;
        ((GP *)p)->w[1] = f4;
        x0 = val + ((sz16 - t) >> 1);
        ((GP *)p)->w[9] = f4 + 288;
        ((GP *)p)->d1 = 22;
        ((GP *)p)->w[5] = yy;
        ((GP *)p)->w[6] = 0x100000;
        ((GP *)p)->w[7] = 0x8000;
        ((GP *)p)->w[12] = x1 = x0 + t;
        ((GP *)p)->d0 = tex;
        ((GP *)p)->w[4] = x0;
        ((GP *)p)->w[8] = f2 + w;
        ((GP *)p)->w[14] = 0x100000;
        ((GP *)p)->w[13] = yy + sz16;
        ((GP *)p)->w[0] = f2;
        ((GP *)p)->w[15] = 0;
        if (fl) {
            ((GP *)p)->w[4] = (s32)(ax + (x0 - ax) * fx);
            ((GP *)p)->w[5] = (s32)(ay + (yy - ay) * fy);
            ((GP *)p)->w[12] = (s32)(ax + (x1 - ax) * fx);
            ((GP *)p)->w[13] = (s32)(ay + (yy + sz16 - ay) * fy);
        }
        val += adv;
        p += 10;
    }
    for (n--; n >= 0; n--) {
        Glyph *g; s32 x1;
        g = D_003E8CD8[dig[n]];
        f7 = g->f7;
        w = g->w << 4;
        f4 = g->f4;
        t = w * sz / 18;
        f2 = g->f2;
        tex = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        ((GP *)p)->d1 = 22;
        ((GP *)p)->w[0] = f2;
        ((GP *)p)->d0 = tex;
        ((GP *)p)->w[1] = f4;
        ((GP *)p)->w[9] = f4 + 288;
        x0 = val + ((sz16 - t) >> 1);
        ((GP *)p)->w[8] = f2 + w;
        ((GP *)p)->w[5] = yy;
        ((GP *)p)->w[6] = 0x100000;
        ((GP *)p)->w[4] = x0;
        ((GP *)p)->w[7] = 0x8000;
        ((GP *)p)->w[14] = 0x100000;
        ((GP *)p)->w[12] = x1 = x0 + t;
        ((GP *)p)->w[13] = yy + sz16;
        ((GP *)p)->w[15] = 0;
        if (fl) {
            ((GP *)p)->w[4] = (s32)(ax + (x0 - ax) * fx);
            ((GP *)p)->w[5] = (s32)(ay + (yy - ay) * fy);
            ((GP *)p)->w[12] = (s32)(ax + (x1 - ax) * fx);
            ((GP *)p)->w[13] = (s32)(ay + (yy + sz16 - ay) * fy);
        }
        val += adv;
        p += 10;
    }
    hdr[0] = ((((s32)p - (s32)start) >> 4) / 5) | 0x8000 | 0x50ab400000000000;
    hdr[1] = 0x4343e;
    base[0] = (((s32)p - (s32)base) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)tag);
    PlatGsSyncPath(0, 0);
    func_001220b8(base);
    D_003F2BD0 = (val - ox) >> 4;
    D_003F2BD4 = (yy - oy) >> 4;
    KH1_V0_RETURN(D_003F2BD0);
}
