/* The functions of src/text/wintext.c that need nostrict
 * (docs/modules.md "Session 37"): func_001f94f0 draws a message string in a
 * text window (mode 0/1/2 aligns left / right / centre around x; with bit 0
 * of the window's +0x48 every glyph is scaled by +0x74 / +0x78 around the
 * window's anchor), func_001fade0 one glyph, func_001fbcd8 a number in the
 * big digits D_003E9250 / D_003E9110, func_001fc330 / func_001fc750 /
 * func_001fcdc8 an icon of the sprite table D_003E9138 (in a window, rotated,
 * on the screen).  Each builds a GIF packet and sends it through path 2. */
#include "common.h"
#include "platform/gs.h"
#include "platform/dma.h"
#include "text/textwin.h"
#include "data/pieces/D_003E8E28.h"
#include "data/pieces/D_003E8E08.h"
#include "data/pieces/D_003F2270.h"
#include "data/pieces/D_003F1E70.h"
#include "data/types/nostrict_text_001f0000_s6_18.h"
#include "data/types/nostrict_text_001f0000_s11_w42.h"

typedef Glyph_3e8e28 Glyph;
typedef struct { u64 d0; u64 d1; u64 d2; u64 d3; s32 w[16]; } GP4;
typedef struct { u64 d0; u64 d1; s32 w[16]; } GP;
typedef struct {
    u64 tex0, reg;
    s32 u0, v0; u64 pad18;
    s32 x0, y0, z0, f0;
    s32 u1, v1; u64 pad38;
    s32 x1, y1, z1, f1;
} GSpr;
typedef struct { u64 h[12]; GSpr g; } Pkt;
typedef struct { s32 u, v; u64 pad; u64 rgba, q; s32 x, y, z, f; } Vx;
typedef struct { s32 w, h, idx, a; s32 c[4]; u32 rot; } SprPrm;
typedef struct { s32 w[16]; } GQ;

extern s32 D_003E8E00;
extern s32 D_003E8E04;
extern Glyph *D_003E8CD0;
extern Glyph *D_003E8CD8[];
extern s32 D_003E8D00[];
extern s32 D_003E8D04[];
extern s32 D_003F1A64;
extern s32 D_003F2BD0;
extern s32 D_003F2BD4;
extern u8 D_003F2C54[];
extern BigG D_003E9250;
extern SmG D_003E9110[];
extern Spr D_003E9138[];

u64 *func_00122048(s32, s32);
void func_001220b8(void *);
u32 func_001edd88(u32, s32);
s32 func_001efc10(s32);
s32 func_001f0148(u8 *, s32);
s32 func_001f4570(TextWin *);
s32 func_001f45e0(TextWin *);
void func_001f8270(void);
s32 func_001fb428(TextWin *, s32, s32, s32, s32, s32, s32, s32, u32);
void func_001fd070(TextWin *, s32, s32);
void func_00201460(TextWin *, s32, s32, s32, s32, s32, s32, u8 *, s32);
void func_00208280(TextWin *, s32, s32, s32, s32, s32);

/* rodata: func_001f94f0 (s12w16), hand/nostrict, jump table at RO=00490D90 (lchkro_s10 0 words, table bytes equal), natural.
   Sibling of func_001f0148 (same if (*s < 21) switch shape). Mode switch with `case 0: default:` first;
   case 15 uses a GNU case range `case 2 ... 28:`; case 15/0 does `cx += 1440` after the PlatDmaSend call;
   header and glyph store order hill-climbed (clb6_s12); `f32 fy, fx;` order gives fy f20. */
s32 func_001f94f0(TextWin *o, s32 mode, s32 x, s32 y, u8 *s, s32 sz, u32 col) {
    u64 *base;
    u32 tag;
    s32 sz16;
    u8 **a;
    u32 col0;
    u64 *p;
    u32 color;
    s32 ox, oy;
    s32 cx;
    s32 x90;
    s32 fl, ax, ay;
    f32 fy, fx;
    s32 c, k, r;
    Glyph *g;

    PlatDmaSend(PlatDmaGetChan(2), &D_003F2270);
    sz16 = sz << 4;
    base = func_00122048(1024, 128);
    p = base + 2;
    p[2] = 0;
    p[0] = 0x1000000000000003;
    p[1] = 14;
    p[3] = 63;
    p[4] = 0x4007ff8001300000;
    p[5] = 22;
    p[6] = 68;
    p[7] = 66;
    p[8] = 0x60ab400000008001;
    tag = ((u32)base & 0x0fffffff) | 0x80000000;
    p[9] = 0x4343ee;
    base[0] = 0x7000000b;
    a = ((u8 **)&D_003E8E08);
    p = base + 12;
    col0 = col;
    x90 = o->x90;
    oy = o->xb4;
    ox = o->xb0;
    y = oy + y * 16;
    color = func_001edd88(col, x90);
    switch (mode) {
    case 0:
    default:
        cx = ox + x * 16;
        break;
    case 1:
        cx = ox + (x - func_001f0148(s, sz)) * 16;
        break;
    case 2:
        cx = ox + (x - func_001f0148(s, sz) / 2) * 16;
        break;
    }
    fl = o->u48.w.lo & 1;
    if (fl) {
        ax = func_001f4570(o);
        ay = func_001f45e0(o);
        fx = o->x74;
        fy = o->x78;
    }
    for (;;) {
        if (*s < 21) {
            switch (*s) {
            case 1:
                cx += (sz << 8) / 18;
                s++;
                break;
            case 3:
                s++;
                D_003F1A64 = *s << 4;
            case 2:
                y += D_003F1A64;
                s++;
                switch (mode) {
                case 0:
                default:
                    cx = ox + x * 16;
                    break;
                case 1:
                    cx = ox + (x - func_001f0148(s, sz)) * 16;
                    break;
                case 2:
                    cx = ox + (x - func_001f0148(s, sz) / 2) * 16;
                    break;
                }
                break;
            case 4:
                s++;
                mode = 0;
                break;
            case 5:
                s++;
                mode = 1;
                break;
            case 6:
                s++;
                mode = 2;
                break;
            case 7:
                if (s[1]) {
                    col = D_003E8D04[s[1]];
                } else {
                    col = col0;
                }
                s += 2;
                color = func_001edd88(col, x90);
                break;
            case 8:
                col = s[1] | (s[2] << 8) | (s[3] << 16) | (s[4] << 24);
                s += 5;
                color = func_001edd88(col, x90);
                break;
            case 9:
                s++;
                col = (u32)*a++;
                color = func_001edd88(col, x90);
                break;
            case 10:
                if (*a) {
                    r = func_001f94f0(o, 0, (cx - ox) >> 4, (y - oy) >> 4, *a, sz, col);
                    cx = ox + r * 16;
                    y = oy + D_003F2BD4 * 16;
                }
                a++;
                s++;
                break;
            case 11:
                r = func_001fb428(o, s[1], s[2], s[3], (cx - ox) >> 4, (y - oy) >> 4, (s32)*a++, sz, col);
                s += 4;
                cx = ox + r * 16;
                y = oy + D_003F2BD4 * 16;
                break;
            case 12:
                sz = s[1];
                s += 2;
                sz16 = sz << 4;
                break;
            case 13:
                cx += (s16)(s[1] | (s[2] << 8)) * 16;
                s += 3;
                break;
            case 14:
                y += (s16)(s[1] | (s[2] << 8)) * 16;
                s += 3;
                break;
            case 15:
                k = s[1];
                switch (k) {
                case 0:
                    func_00201460(o, 2, 2, (cx - ox) >> 4, (y - oy) >> 4, 90, ((cx - ox) >> 4) + 45, D_003F2C54, func_001efc10(43));
                    PlatDmaSend(PlatDmaGetChan(2), &D_003F2270);
                    cx += 1440;
                    break;
                case 1:
                    func_001fd070(o, (cx - ox) >> 4, (y - oy) >> 4);
                    cx += 576;
                    PlatDmaSend(PlatDmaGetChan(2), &D_003F2270);
                    break;
                case 2 ... 28:
                    func_00208280(o, (cx - ox) >> 4, (y - oy) >> 4, 0, k + 25, 128);
                    PlatDmaSend(PlatDmaGetChan(2), &D_003F2270);
                    cx += 288;
                    break;
                }
                s += 2;
                break;
            case 17:
                x = (s16)(s[1] | (s[2] << 8)) - ((ox - 0x7000) >> 4);
                s += 3;
                cx = ox + x * 16;
                break;
            case 18:
                y = (s16)(s[1] | (s[2] << 8)) - ((oy - 0x7400) >> 4);
                s += 3;
                y = oy + y * 16;
                break;
            case 19:
                x = (s16)(s[1] | (s[2] << 8));
                s += 3;
                cx = ox + x * 16;
                break;
            case 20:
                y = oy + (s16)(s[1] | (s[2] << 8)) * 16;
                s += 3;
                break;
            case 0:
            case 16:
                goto end;
            default:
                s++;
                break;
            }
        } else {
            s32 w, t, adv, x1, y1;
            s32 f2, f4;
            u64 tex;
            u32 f7;
            if (*s == 24) {
                c = (s[1] << 8) - 0x1820;
                s += 2;
            } else if (*s < 32) {
                c = ((s[0] << 8) | s[1]) - 0x1820;
                s += 2;
            } else {
                c = *s - 32;
                s++;
            }
            g = &D_003E8E28[c];
            w = g->w << 4;
            f4 = g->f4;
            adv = (w + D_003E8E00) * sz / 18;
            t = w * sz / 18;
            f7 = g->f7;
            f2 = g->f2;
            tex = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
            ((GP4 *)p)->w[1] = f4;
            ((GP4 *)p)->d0 = tex;
            ((GP4 *)p)->d1 = 22;
            ((GP4 *)p)->d2 = color;
            ((GP4 *)p)->w[4] = cx;
            ((GP4 *)p)->d3 = 1;
            ((GP4 *)p)->w[5] = y;
            ((GP4 *)p)->w[7] = 0x8000;
            ((GP4 *)p)->w[8] = f2 + w;
            ((GP4 *)p)->w[6] = 0x100000;
            ((GP4 *)p)->w[13] = y1 = y + sz16;
            ((GP4 *)p)->w[12] = x1 = cx + t;
            ((GP4 *)p)->w[9] = f4 + 288;
            ((GP4 *)p)->w[15] = 0;
            ((GP4 *)p)->w[14] = 0x100000;
            ((GP4 *)p)->w[0] = f2;
            if (fl) {
                ((GP4 *)p)->w[4] = (s32)(ax + (cx - ax) * fx);
                ((GP4 *)p)->w[5] = (s32)(ay + (y - ay) * fy);
                ((GP4 *)p)->w[12] = (s32)(ax + (x1 - ax) * fx);
                ((GP4 *)p)->w[13] = (s32)(ay + (y1 - ay) * fy);
            }
            cx += adv;
            PlatDmaSend(PlatDmaGetChan(2), (void *)tag);
            PlatGsSyncPath(0, 0);
        }
    }
end:
    func_001220b8(base);
    D_003F2BD0 = (cx - ox) >> 4;
    D_003F2BD4 = (y - oy) >> 4;
    return (cx - ox) >> 4;
}

void func_001fade0(TextWin *o, s32 x, s32 y, s32 idx, s32 sz, s32 col) {
    u64 *buf;
    Pkt *p;
    void *u;
    Glyph *gl;
    s32 X, Y, ox, w, a, b, cx, cy;
    f32 sx, sy, fx, fy;
    s32 gu, gv, ww, z;
    u64 tex;
    s32 k = 22;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F2270));
    buf = func_00122048(1024, 128);
    p = (Pkt *)(buf + 2);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p->h[0] = 0x4000000000000001;
    p->h[1] = 0xEEEE;
    p->h[3] = 63;
    p->h[4] = 0x4007FF8001300000;
    p->h[2] = 0;
    p->h[6] = 68;
    p->h[5] = k;
    p->h[7] = 66;
    p->h[8] = func_001edd88(col, o->x90);
/*P*/
    p->h[9] = 1;
    p->h[10] = 0x50AB400000008001;
    z = 0x100000;
    p->h[11] = 0x4343E;
    gl = &D_003E8E28[idx];
    ox = o->xb0;
    Y = o->xb4 + (y << 4);
    gu = gl->f2;
    w = gl->w << 4;
    gv = gl->f4;
    X = ox + (x << 4);
    ww = w + D_003E8E00;
    a = w * sz / 18;
    b = ww * sz / 18;
    tex = ((u64)D_003E8D00[gl->f7 >> 4] << 20) | ((u64)(gl->f7 & 0xf) << 56) | (0xfff0ULL << 35);
    p->g.u0 = gu;
    p->g.v0 = gv;
    p->g.x1 = X + a;
    p->g.tex0 = tex;
    p->g.x0 = X;
    p->g.reg = k;
    p->g.f0 = 0x8000;
    p->g.y0 = Y;
    p->g.u1 = gu + w;
    p->g.v1 = gv + 288;
    p->g.y1 = Y + (sz << 4);
    p->g.z0 = z;
    p->g.f1 = 0;
    p->g.z1 = z;
/*Q*/
    if (o->u48.w.lo & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
        fx = cx;
        fy = cy;
        p->g.x0 = fx + (f32)(p->g.x0 - cx) * sx;
        p->g.y0 = fy + (f32)(p->g.y0 - cy) * sy;
        p->g.x1 = fx + (f32)(p->g.x1 - cx) * sx;
        p->g.y1 = fy + (f32)(p->g.y1 - cy) * sy;
    }
    buf[0] = (((s32)(p + 1) - (s32)buf) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), u);
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
    D_003F2BD0 = (X + b - ox) >> 4;
    D_003F2BD4 = y;
}

/* 001fbcd8 (hand/nostrict, no context). s11w42 MATCH, FLAGGED dead FP test. From s11w6's 15w draft: ONE v shared by the neg block and the digit loop (no v3), the loop's x2 renamed x3 (separate pseudo), and the dead test `if ((f32)v < 0.0f) i = 0;` at the end of the neg block (i is dead there; flow2 deletes the empty branch). The test keeps v live longer, so global-alloc ranks v below the loop temps (x3-ax temp a1, dig pointer giv a2, v t0). Neg block: the four g-> loads first (u, v, gw, gh, so no p-> store precedes a load under -fno-strict-aliasing), stores in a climbed order. */
s32 func_001fbcd8(TextWin *o, s32 mode, u32 nd, s32 pad, s32 x, s32 y, s32 val, s32 alpha, u32 col) {
    s32 dig[12];
    u64 *start;
    u32 tag;
    u64 *hdr;
    s32 neg;
    s32 ox;
    s32 fl;
    u64 *base, *p;
    s32 n, i;
    s32 xx, yy;
    s32 ax, ay;
    f32 fx, fy;
    BigG *g;
    f32 fa, fb, t0, t1, t2, t3;
    SmG *h;
    s32 u, v;
    s32 x2, y2;
    s32 gh, gw;
    s32 x3, y3, u3;

    PlatDmaSend(PlatDmaGetChan(2), &D_003F1E70);
    neg = 0;
    base = func_00122048(1024, 128);
    p = base + 2;
    tag = ((u32)base & 0x0fffffff) | 0x80000000;
    p[0] = 0x5000000000000001;
    p[2] = 0;
    p[1] = 0xeeeee;
    p[3] = 63;
    p[4] = 0x4007bf8001300000;
    hdr = base + 14;
    p[5] = 22;
    p[6] = ((u64)alpha << 56) | 0x0007bf8001400000;
    p[7] = 22;
    p[8] = 68;
    p[9] = 66;
    p[10] = func_001edd88(col, o->x90);
    p[11] = 1;
    p = base + 16;
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
    xx = ox + x * 16;
    yy = o->xb4 + y * 16;
    switch (mode) {
    case 1:
        xx -= (n + neg) * 240;
        break;
    case 2:
        xx -= (n + neg) * 120;
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

        g = &D_003E9250;
        u = g->u;
        v = g->v;
        gw = g->w;
        gh = g->h;
        ((GQ *)p)->w[1] = v;
        ((GQ *)p)->w[8] = u + gw - 16;
        ((GQ *)p)->w[9] = v + gh - 16;
        ((GQ *)p)->w[7] = 0x8000;
        x2 = xx + 304;
        ((GQ *)p)->w[4] = xx;
        ((GQ *)p)->w[5] = yy;
        ((GQ *)p)->w[6] = 0x100000;
        ((GQ *)p)->w[14] = 0x100000;
        ((GQ *)p)->w[12] = x2;
        y2 = yy + 288;
        ((GQ *)p)->w[13] = y2;
        ((GQ *)p)->w[0] = u;
        ((GQ *)p)->w[15] = 0;
        if (fl) {
            ((GQ *)p)->w[4] = (s32)(ax + (f32)(xx - ax) * fx);
            ((GQ *)p)->w[5] = (s32)(ay + (f32)(yy - ay) * fy);
            ((GQ *)p)->w[12] = (s32)(ax + (f32)(x2 - ax) * fx);
            ((GQ *)p)->w[13] = (s32)(ay + (f32)(y2 - ay) * fy);
        }
        p += 8;
        xx += 240;
        if ((f32)v < 0.0f) i = 0; /* FLAGGED dead FP test: extends v (shared neg/loop) life so global-alloc ranks it below the loop temps */
    }
    for (n--; n >= 0; n--) {
        h = &D_003E9110[dig[n]];
        u = h->u;
        x3 = xx + 304;
        v = h->v;
        ((GQ *)p)->w[4] = xx;
        ((GQ *)p)->w[5] = yy;
        y2 = yy + 288;
        ((GQ *)p)->w[0] = u;
        ((GQ *)p)->w[8] = u + 288;
        ((GQ *)p)->w[12] = x3;
        ((GQ *)p)->w[1] = v;
        ((GQ *)p)->w[6] = 0x100000;
        ((GQ *)p)->w[13] = y2;
        ((GQ *)p)->w[7] = 0x8000;
        ((GQ *)p)->w[9] = v + 272;
        ((GQ *)p)->w[14] = 0x100000;
        ((GQ *)p)->w[15] = 0;
        if (fl) {
            ((GQ *)p)->w[4] = (s32)(ax + (f32)(xx - ax) * fx);
            ((GQ *)p)->w[5] = (s32)(ay + (f32)(yy - ay) * fy);
            ((GQ *)p)->w[12] = (s32)(ax + (f32)(x3 - ax) * fx);
            ((GQ *)p)->w[13] = (s32)(ay + (f32)(y2 - ay) * fy);
        }
        p += 8;
        xx += 240;
    }
    hdr[1] = 0x4343;
    hdr[0] = ((((s32)p - (s32)start) >> 4) / 4) | 0x8000 | 0x40ab400000000000;
    base[0] = (((s32)p - (s32)base) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)tag);
    PlatGsSyncPath(0, 0);
    func_001220b8(base);
    return (xx - ox) >> 4;
}

s32 func_001fc330(TextWin *o, s32 x, s32 y, s32 w, s32 h, s32 idx, s32 a, s32 c0, s32 c1, s32 c2, s32 c3) {
    u64 *buf;
    u64 *p;
    void *u;
    Spr *t;
    s32 X, Y, W = w << 4;
    s32 al;
    s32 one, z;
    s32 cx, cy, nx, ny, nx2, ny2;
    f32 fx, fy, sx, sy;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1024, 128);
    p = buf + 2;
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p[0] = 0x4000000000000001;
    p[1] = 0xEEEE;
    p[2] = 0;
    p[3] = 63;
    p[4] = 0x4007BF8001300000;
    p[5] = 22;
    p[6] = ((u64)a << 56) | 0x0007BF8001400000;
    p[7] = 22;
    p[8] = 68;
    p[9] = 66;
    p[10] = 0x30AE400000008004;
    p[11] = 1251;
/*P*/
    p += 12;
    one = 1;
    al = o->x90;
    X = o->xb0 + (x << 4);
    t = &D_003E9138[idx];
    Y = o->xb4 + (y << 4);
    W = !w ? t->w : W;
    h = h ? h << 4 : t->h;
    z = 0x100000;
/*Q*/
    ((Vx *)p)[0].u = t->uv[0];
    ((Vx *)p)[0].v = t->uv[1];
    ((Vx *)p)[0].rgba = func_001edd88(c0, al);
    ((Vx *)p)[0].q = one;
    ((Vx *)p)[0].x = X;
    ((Vx *)p)[0].y = Y;
    ((Vx *)p)[0].z = z;
    ((Vx *)p)[0].f = 0;
    ((Vx *)p)[1].u = t->uv[2];
    ((Vx *)p)[1].v = t->uv[3];
    ((Vx *)p)[1].rgba = func_001edd88(c1, al);
    ((Vx *)p)[1].q = one;
    ((Vx *)p)[1].x = ((Vx *)p)[0].x + W;
    ((Vx *)p)[1].y = ((Vx *)p)[0].y;
    ((Vx *)p)[1].z = z;
    ((Vx *)p)[1].f = 0;
    ((Vx *)p)[2].u = t->uv[4];
    ((Vx *)p)[2].v = t->uv[5];
    ((Vx *)p)[2].rgba = func_001edd88(c2, al);
    ((Vx *)p)[2].q = one;
    ((Vx *)p)[2].x = ((Vx *)p)[0].x;
    ((Vx *)p)[2].y = ((Vx *)p)[0].y + h;
    ((Vx *)p)[2].z = z;
    ((Vx *)p)[2].f = 0;
    ((Vx *)p)[3].u = t->uv[6];
    ((Vx *)p)[3].v = t->uv[7];
    ((Vx *)p)[3].rgba = func_001edd88(c3, al);
    ((Vx *)p)[3].q = one;
    ((Vx *)p)[3].x = ((Vx *)p)[1].x;
    ((Vx *)p)[3].y = ((Vx *)p)[2].y;
    ((Vx *)p)[3].z = z;
    ((Vx *)p)[3].f = 0;
    if (o->u48.w.lo & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
        fx = cx;
        fy = cy;
        nx = fx + (f32)(((Vx *)p)[0].x - cx) * sx;
        ny = fy + (f32)(((Vx *)p)[0].y - cy) * sy;
        nx2 = fx + (f32)(((Vx *)p)[1].x - cx) * sx;
        ny2 = fy + (f32)(((Vx *)p)[2].y - cy) * sy;
        ((Vx *)p)[2].x = ((Vx *)p)[0].x = nx;
        ((Vx *)p)[1].y = ((Vx *)p)[0].y = ny;
        ((Vx *)p)[3].x = ((Vx *)p)[1].x = nx2;
        ((Vx *)p)[3].y = ((Vx *)p)[2].y = ny2;
    }
    buf[0] = (((s32)((Vx *)p + 4) - (s32)buf) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), u);
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
    return x + (W >> 4);
}

/* rodata */
s32 func_001fc750(TextWin *o, s32 x, s32 y, SprPrm *pr) {
    u64 *buf;
    u64 *p;
    void *u;
    Spr *t;
    s32 X, Y, W, H, al;
    s32 cx, cy;
    f32 fx, fy, sx, sy;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1024, 128);
    p = buf + 2;
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p[0] = 0x4000000000000001;
    p[1] = 0xEEEE;
    p[2] = 0;
    p[3] = 63;
    p[4] = 0x4007BF8001300000;
    p[5] = 22;
    p[6] = ((u64)pr->a << 56) | 0x0007BF8001400000;
    p[7] = 22;
    p[8] = 68;
    p[9] = 66;
    p[10] = 0x30AE400000008004;
    p[11] = 1251;
    p += 12;
    t = &D_003E9138[pr->idx];
    X = o->xb0 + (x << 4);
    Y = o->xb4 + (y << 4);
    al = o->x90;
    W = pr->w ? pr->w << 4 : t->w;
    H = pr->h ? pr->h << 4 : t->h;
    switch (pr->rot) {
    case 0:
        {
        s32 yb = Y + H;
        s32 xr = X + W;
        ((Vx *)p)[0].rgba = func_001edd88(pr->c[0], al);
        ((Vx *)p)[0].x = X;
        ((Vx *)p)[0].y = Y;
        ((Vx *)p)[1].rgba = func_001edd88(pr->c[1], al);
        ((Vx *)p)[1].x = xr;
        ((Vx *)p)[1].y = Y;
        ((Vx *)p)[2].rgba = func_001edd88(pr->c[2], al);
        ((Vx *)p)[2].x = X;
        ((Vx *)p)[2].y = yb;
        ((Vx *)p)[3].rgba = func_001edd88(pr->c[3], al);
        ((Vx *)p)[3].x = xr;
        ((Vx *)p)[3].y = yb;
        }
        break;
    case 1:
        {
        s32 yb = Y + H;
        s32 xr = X + W;
        ((Vx *)p)[0].rgba = func_001edd88(pr->c[1], al);
        ((Vx *)p)[0].x = xr;
        ((Vx *)p)[0].y = Y;
        ((Vx *)p)[1].rgba = func_001edd88(pr->c[0], al);
        ((Vx *)p)[1].x = X;
        ((Vx *)p)[1].y = Y;
        ((Vx *)p)[2].rgba = func_001edd88(pr->c[3], al);
        ((Vx *)p)[2].x = xr;
        ((Vx *)p)[2].y = yb;
        ((Vx *)p)[3].rgba = func_001edd88(pr->c[2], al);
        ((Vx *)p)[3].x = X;
        ((Vx *)p)[3].y = yb;
        }
        break;
    case 2:
        {
        s32 yb = Y + H;
        s32 xr = X + W;
        ((Vx *)p)[0].rgba = func_001edd88(pr->c[2], al);
        ((Vx *)p)[0].x = X;
        ((Vx *)p)[0].y = yb;
        ((Vx *)p)[1].rgba = func_001edd88(pr->c[3], al);
        ((Vx *)p)[1].x = xr;
        ((Vx *)p)[1].y = yb;
        ((Vx *)p)[2].rgba = func_001edd88(pr->c[0], al);
        ((Vx *)p)[2].x = X;
        ((Vx *)p)[2].y = Y;
        ((Vx *)p)[3].rgba = func_001edd88(pr->c[1], al);
        ((Vx *)p)[3].x = xr;
        ((Vx *)p)[3].y = Y;
        }
        break;
    case 3:
        {
        s32 yb = Y + H;
        s32 xr = X + W;
        ((Vx *)p)[0].rgba = func_001edd88(pr->c[2], al);
        ((Vx *)p)[0].x = X;
        ((Vx *)p)[0].y = yb;
        ((Vx *)p)[1].rgba = func_001edd88(pr->c[0], al);
        ((Vx *)p)[1].x = X;
        ((Vx *)p)[1].y = Y;
        ((Vx *)p)[2].rgba = func_001edd88(pr->c[3], al);
        ((Vx *)p)[2].x = xr;
        ((Vx *)p)[2].y = yb;
        ((Vx *)p)[3].rgba = func_001edd88(pr->c[1], al);
        ((Vx *)p)[3].x = xr;
        ((Vx *)p)[3].y = Y;
        }
        break;
    case 4:
        {
        s32 yb = Y + H;
        s32 xr = X + W;
        ((Vx *)p)[0].rgba = func_001edd88(pr->c[1], al);
        ((Vx *)p)[0].x = xr;
        ((Vx *)p)[0].y = Y;
        ((Vx *)p)[1].rgba = func_001edd88(pr->c[3], al);
        ((Vx *)p)[1].x = xr;
        ((Vx *)p)[1].y = yb;
        ((Vx *)p)[2].rgba = func_001edd88(pr->c[0], al);
        ((Vx *)p)[2].x = X;
        ((Vx *)p)[2].y = Y;
        ((Vx *)p)[3].rgba = func_001edd88(pr->c[2], al);
        ((Vx *)p)[3].x = X;
        ((Vx *)p)[3].y = yb;
        }
        break;
    }
    ((Vx *)p)[0].u = t->uv[0];
    ((Vx *)p)[0].v = t->uv[1];
    ((Vx *)p)[0].q = 1;
    ((Vx *)p)[0].z = 0x100000;
    ((Vx *)p)[0].f = 0;
    ((Vx *)p)[1].u = t->uv[2];
    ((Vx *)p)[1].v = t->uv[3];
    ((Vx *)p)[1].q = 1;
    ((Vx *)p)[1].z = 0x100000;
    ((Vx *)p)[1].f = 0;
    ((Vx *)p)[2].u = t->uv[4];
    ((Vx *)p)[2].v = t->uv[5];
    ((Vx *)p)[2].q = 1;
    ((Vx *)p)[2].z = 0x100000;
    ((Vx *)p)[2].f = 0;
    ((Vx *)p)[3].u = t->uv[6];
    ((Vx *)p)[3].v = t->uv[7];
    ((Vx *)p)[3].q = 1;
    ((Vx *)p)[3].z = 0x100000;
    ((Vx *)p)[3].f = 0;
    if (o->u48.w.lo & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
        fx = cx;
        fy = cy;
        ((Vx *)p)[0].x = fx + (f32)(((Vx *)p)[0].x - cx) * sx;
        ((Vx *)p)[0].y = fy + (f32)(((Vx *)p)[0].y - cy) * sy;
        ((Vx *)p)[1].x = fx + (f32)(((Vx *)p)[1].x - cx) * sx;
        ((Vx *)p)[1].y = fy + (f32)(((Vx *)p)[1].y - cy) * sy;
        ((Vx *)p)[2].x = fx + (f32)(((Vx *)p)[2].x - cx) * sx;
        ((Vx *)p)[2].y = fy + (f32)(((Vx *)p)[2].y - cy) * sy;
        ((Vx *)p)[3].x = fx + (f32)(((Vx *)p)[3].x - cx) * sx;
        ((Vx *)p)[3].y = fy + (f32)(((Vx *)p)[3].y - cy) * sy;
    }
    buf[0] = (((s32)((Vx *)p + 4) - (s32)buf) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), u);
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
    return x + (W >> 4);
}

s32 func_001fcdc8(s32 x, s32 y, s32 w, s32 h, s32 idx, s32 a, s32 c0, s32 c1) {
    u64 *buf;
    u64 *p;
    void *u;
    Spr *t;
    s32 X, Y, W, H;
    func_001f8270();
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1024, 128);
    p = buf + 2;
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p[0] = 0x4000000000000001;
    p[1] = 0xEEEE;
    p[2] = 0;
    p[3] = 63;
    p[4] = 0x4007BF8001300000;
    p[5] = 22;
    p[6] = ((u64)a << 56) | 0x0007BF8001400000;
    p[7] = 22;
    p[8] = 68;
    p[9] = 66;
    p[10] = 0x30AE400000008004;
    p[11] = 1251;
    p += 12;
    X = (x << 4) + 0x7000;
    t = &D_003E9138[idx];
    Y = (y << 4) + 0x7400;
    W = w ? w << 4 : t->w;
    H = h ? h << 4 : t->h;
    ((Vx *)p)[0].u = t->uv[0];
    ((Vx *)p)[0].v = t->uv[1];
    ((Vx *)p)[0].rgba = c0;
    ((Vx *)p)[0].q = 1;
    ((Vx *)p)[0].x = X;
    ((Vx *)p)[0].y = Y;
    ((Vx *)p)[0].z = 0x100000;
    ((Vx *)p)[0].f = 0;
    ((Vx *)p)[1].u = t->uv[2];
    ((Vx *)p)[1].v = t->uv[3];
    ((Vx *)p)[1].rgba = c0;
    ((Vx *)p)[1].q = 1;
    ((Vx *)p)[1].x = X + W;
    ((Vx *)p)[1].y = Y;
    ((Vx *)p)[1].z = 0x100000;
    ((Vx *)p)[1].f = 0;
    ((Vx *)p)[2].u = t->uv[4];
    ((Vx *)p)[2].v = t->uv[5];
    ((Vx *)p)[2].rgba = c1;
    ((Vx *)p)[2].q = 1;
    ((Vx *)p)[2].x = X;
    ((Vx *)p)[2].y = Y + H;
    ((Vx *)p)[2].z = 0x100000;
    ((Vx *)p)[2].f = 0;
    ((Vx *)p)[3].u = t->uv[6];
    ((Vx *)p)[3].v = t->uv[7];
    ((Vx *)p)[3].rgba = c1;
    ((Vx *)p)[3].q = 1;
    ((Vx *)p)[3].x = X + W;
    ((Vx *)p)[3].y = Y + H;
    ((Vx *)p)[3].z = 0x100000;
    ((Vx *)p)[3].f = 0;
    buf[0] = (((s32)((Vx *)p + 4) - (s32)buf) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), u);
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
    return x + (W >> 4);
}
