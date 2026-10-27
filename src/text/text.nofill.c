/* The functions of src/text/text.c that need nofill: func_001efc10 (system
 * message id, from 1, to its string) and four GIF packet builders
 * (docs/modules.md "Session 37"): func_001f0ea8 draws a two-byte string,
 * func_001f12c0 an ASCII one, func_001f15f0 one glyph and func_001f18e8 a
 * number; func_001f1fc8 and func_001f2630 (session 128) draw a message string
 * and a two-byte string at once; func_001f2eb8 sets up the font.  func_001f0ea8 needs the CONTEXT_ONLY copies of its callees from
 * text.c above it.
 *
 * func_001f18e8 (session 18, s18m1, from s11w52's 2-word draft) keeps a dead
 * FP test after the second call, and the 63 header constant is a local
 * register variable `register u64 k3 KH1_REG("$3")` (plain C, no inline asm).
 * With k3 pinned to v1, `k3 = 63;` can be set right after the d[0] store
 * (li 63 born early, so sched2 issues it in the slot after li 0xeeee as in
 * the original) without local-alloc moving it to t0; `d[9] = 1;` written
 * last puts li t1,1 after li 66.  Without the pin: 6 words; without the dead
 * test: 6 words. */
#include "common.h"
#include "lang.h"
#include "platform/gs.h"
#include "platform/dma.h"
#include "data/pieces/D_003E8E28.h"
#include "data/pieces/D_003E8E08.h"
#include "data/pieces/D_003F1A70.h"

typedef Glyph_3e8e28 Glyph;
#include "data/types/nofill_text_001f0000_h69.h" /* Q, a GIF packet quadword */
#include "data/pieces/D_003F1E70.h"
#include "data/pieces/D_003F2270.h"
#include "data/pieces/D_003F27D0.h"
#include "data/pieces/D_003E9660.h"
#include "data/pieces/D_003F2670.h"
#include "data/pieces/D_003F1660.h"
#include "data/pieces/D_003F2720.h"
extern u8 D_003E4658[]; /* the English patch's message table (lang.h) */
typedef union { s32 i; f32 f; } UF;
/* one sprite: tag, then UV, XYZ, UV, XYZ */
typedef struct {
    u64 d[2];
    s32 x10, x14, x18, x1c;
    s32 x20, x24, x28, x2c;
    s32 x30, x34, x38, x3c;
    s32 x40, x44, x48, x4c;
} Pg;
/* func_001f15f0's packet: the header and one sprite */
typedef struct {
    u64 d[18];
    s32 x90, x94, x98, x9c;
    s32 xa0, xa4, xa8, xac;
    s32 xb0, xb4, xb8, xbc;
    s32 xc0, xc4, xc8, xcc;
} Pk;

extern u8 D_003E5ED8[];
extern u16 D_003E890E[];
extern Glyph *D_003E8CD0;
extern Glyph *D_003E8CD8[];
extern s32 D_003E8D00[];
extern u16 D_003E8D40[];
extern s32 D_003E8E00;
extern s32 D_003E8E04;
extern s32 D_003E8E2C;
extern s32 D_0063F740;
extern s32 D_0063F74C;
extern s32 D_0063F750;
extern s32 D_003F1A68;

void func_0011fb78(Q *, s32, Q *);
Q *func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, u32, Q *, Q *);
void func_001f3110(void);
u8 *func_00122048(s32, s32);
void func_001220b8(u8 *);
s32 func_001f0448(s32, s32, u8 *, s32);
s32 func_001f2d68(s32, s32, s32, s32, s32, s32, s32, s32);

u8 *func_001efc10(s32 a) {
    return (u8 *)KH1_EN_AT(D_003E4658, 0x1180, D_003E5ED8) + D_003E890E[a];
}

#define SETX() \
    switch (mode) { \
    case 0: \
    default: \
        cx = x * 16 + 0x7000; \
        break; \
    case 1: \
        cx = (x - func_001f0340(str, sc)) * 16 + 0x7000; \
        break; \
    case 2: \
        cx = (x - func_001f0340(str, sc) / 2) * 16 + 0x7000; \
        break; \
    }

CONTEXT_ONLY void func_001efb78(s32 arg0) { D_003E8E00 = arg0; }
CONTEXT_ONLY s32 func_001efb88(void) { return D_003E8E00; }
CONTEXT_ONLY void func_001efb98(s32 arg0) { D_003E8E04 = arg0; }
CONTEXT_ONLY s32 func_001efba8(void) { return D_003E8E04; }
CONTEXT_ONLY s32 func_001eff50(s32 a) {
    s32 i;
    Glyph *e = D_003E8E28;
    for (i = 0; i < D_003E8E2C; i++, e++) {
        if (e->code == a) return i;
    }
    return 0;
}
CONTEXT_ONLY s32 func_001f0340(u8 *p, s32 scale) {
    s32 d = 18;
    s32 x = 0;
    for (;;) {
        s32 c = *p;
        s32 k;
        if (c == 0 || c == 10) return x >> 4;
        k = c | (p[1] << 8);
        p += 2;
        if (k == 0x4081) {
            x += (scale << 8) / d;
        } else {
            Glyph *g = &D_003E8E28[func_001eff50(k)];
            x += ((g->w << 4) + func_001efb88()) * scale / d;
        }
    }
}

Q *func_001f0ea8(Q *pk, s32 a1, s32 mode, u32 a3, s32 x, s32 y, u8 *str, s32 sc) {
    u64 *d;
    Q *start;
    Q *tag;
    Pg *g;
    Glyph *gl;
    s32 cx, cy, c, w, s, h;
    u8 f7;
    s32 f2, f4;
    Q *p;

    func_001efb78(0);
    func_001efb98(0);
    h = sc * 16;
    p = pk;
    d = (u64 *)p;
    d[0] = 0x6000000000000001;
    d[1] = 0xeeeeee;
    d[2] = 0;
    d[3] = 0x3f;
    d[4] = 0x2007ff8622411000;
    d[5] = 6;
    d[6] = 97;
    d[7] = 20;
    d[8] = 0x4007ff8001300000;
    d[9] = 22;
    d[10] = 68;
    d[11] = 66;
    d[12] = a3;
    cy = y * 16 + 0x7400;
    d[13] = 1;
    tag = p + 7;
    p += 8;
    start = p;
    SETX();
    for (;;) {
        c = *str;
        if (c == 0) goto done;
        if (c == '\n') {
            str++;
            cy += D_0063F740;
            SETX();
            continue;
        }
        c |= str[1] << 8;
        str += 2;
        if (c == 0x4081) {
            cx += (sc << (KH1_EN ? 6 : 8)) / KH1_GLYPH;
            continue;
        }
        gl = &D_003E8E28[func_001eff50(c)];
        w = gl->w << 4;
        s = w * sc / KH1_GLYPH;
        c = (w + func_001efb88()) * sc / KH1_GLYPH;
        g = (Pg *)p;
/*P*/
        f7 = gl->f7;
        f4 = gl->f4;
        g->d[0] = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        g->x20 = cx;
        f2 = gl->f2;
        g->x40 = cx + s;
        g->d[1] = 22;
        g->x24 = cy;
        g->x28 = 0x100000;
        g->x2c = 0x8000;
        g->x30 = f2 + w;
        g->x34 = f4 + KH1_GLYPH * 16;
        g->x44 = cy + h;
        g->x48 = 0x100000;
        g->x10 = f2;
        g->x14 = f4;
        g->x4c = 0;
/*Q*/
        p += 5;
        cx += c;
    }
done:
    {
    s32 ex = cx - 0x7000;
    s32 ey = cy - 0x7400;
    { u64 n = (p - start) / 5; tag->b = 0x4343e; tag->a = n | ((u64)a1 << 15) | 0x50ab400000000000; }
    D_0063F74C = ex >> 4;
    D_0063F750 = ey >> 4;
    }
    return p;
}

Q *func_001f12c0(Q *p, s32 a1, u32 a2, s32 x, s32 y, u8 *str, s32 sc) {
    u64 *d;
    Q *start;
    Q *tag;
    Pg *g;
    Glyph *gl;
    s32 k, cx, cy, w, s, h, x16, t, hh;
    u8 f7;
    s32 f2, f4;
    s32 dv = KH1_GLYPH;
    u32 c;

    tag = p + 7;
    func_001efb78(0);
    func_001efb98(0);
    d = (u64 *)p;
    x16 = x * 16;
    h = sc * 16;
    cy = y * 16 + 0x7400;
    cx = x16 + 0x7000;
    d[0] = 0x6000000000000001;
    d[1] = 0xeeeeee;
    d[3] = 0x3f;
    d[4] = 0x2007ff8622411000;
    d[5] = 6;
    d[6] = 97;
    d[7] = 20;
    d[8] = 0x4007ff8001300000;
    d[9] = 22;
    d[10] = 68;
    d[11] = 66;
    d[12] = a2;
    d[13] = 1;
    d[2] = 0;
    hh = h + 16;
    p += 8;
    start = p;
    for (;;) {
        c = *str;
        if (c == 0) goto done;
        if (c == '\n') {
            str++;
            cx = x * 16 + 0x7000;
            cy += *(volatile s32 *)&D_0063F740;
            continue;
        }
        str++;
        if (c < 31) continue;
        if (c == ' ') {
            cx += (sc << 8) / dv;
            continue;
        }
        if (c >= 128) continue;
/*P*/
        k = D_003E8D40[c - 32];
        g = (Pg *)p;
        gl = &D_003E8E28[k];
        f7 = gl->f7;
        w = gl->w << 4;
        f4 = gl->f4;
        s = w * sc / dv;
        g->d[0] = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        g->x24 = cy;
        f2 = gl->f2;
        g->x28 = 0x100000;
        g->x30 = f2 + w;
        g->d[1] = 22;
        g->x2c = 0x8000;
        g->x34 = f4 + KH1_GLYPH * 16;
        g->x44 = cy + h;
        g->x10 = f2;
        g->x48 = 0x100000;
        t = cx + (h - s) / 2; /*FIX*/
        g->x20 = t;
        cx += hh; /*FIX*/
        g->x4c = 0;
        g->x14 = f4;
        g->x40 = t + s;
/*Q*/
        p += 5;
    }
done:
    { s32 n = (p - start) / 5; tag->b = 0x4343e; tag->a = n | ((u64)a1 << 15) | 0x50ab400000000000; }
    D_0063F74C = (cx - 0x7000) >> 4;
    D_0063F750 = (cy - 0x7400) >> 4;
    return p;
}

Q *func_001f15f0(Q *pk, s32 a1, u32 a2, s32 a3, s32 a4, s32 a5, s32 a6) {
    Pk *p = (Pk *)pk;
    Glyph *g;
    s32 w, x, y, z, s, t, h;
    s32 f2, f4;
    u8 f7;
    func_001efb78(0);
    func_001efb98(0);
    x = a4 * 16;
    p->d[0] = 0x6000000000000001;
    p->d[1] = 0xeeeeee;
    p->d[3] = 0x3f;
    p->d[9] = 22;
    p->d[4] = 0x2007ff8622411000;
    p->d[5] = 6;
    p->d[6] = 97;
    p->d[7] = 20;
    y = a3 * 16 + 0x7000;
    p->d[8] = 0x4007ff8001300000;
    h = a6 * 16;
    p->d[2] = 0;
    p->d[10] = 68;
    p->d[11] = 66;
    z = x + 0x7400;
    p->d[13] = 1;
    p->d[15] = 0x4343e;
    p->d[12] = a2;
    p->d[14] = ((u64)a1 << 15) | 0x50ab400000000001;
    g = &D_003E8E28[a5];
    w = g->w << 4;
    s = w * a6 / 18;
    t = (w + func_001efb88()) * a6 / 18;
    f2 = g->f2;
    f7 = g->f7;
    p->d[16] = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
    p->xa0 = y;
    f4 = g->f4;
    p->x90 = f2;
    p->d[17] = 22;
    p->xac = 0x8000;
    p->xb0 = f2 + w;
    p->x94 = f4;
    p->xa4 = z;
    p->xa8 = 0x100000;
    p->xcc = 0;
    p->xb4 = f4 + KH1_GLYPH * 16;
    p->xc0 = y + s;
    p->xc8 = 0x100000;
    p->xc4 = z + h;
    D_0063F74C = (y + t - 0x7000) >> 4;
    D_0063F750 = x >> 4;
    return (Q *)(p + 1);
}

Q *func_001f18e8(Q *p, s32 a1, s32 mode, s32 nd, s32 pad, s32 x, s32 y, s32 val, s32 sc, u32 col) {
    s32 dig[12];
    u64 *d;
    Q *start;
    Q *tag;
    Pg *g;
    s32 n, neg;
    s32 cx, cy, h, adv;
    s32 w;
    s32 f2;
    s32 f4;
    u8 f7;
    s32 i;
    u64 k4, k5, k6, k7;
    u64 kk; register u64 k3 KH1_REG("$3");
    u64 cl;

    neg = 0;
    func_001efb78(0);
    cl = col;
    func_001efb98(0);
    kk = 0xeeee;
    if ((f32)nd < 0.0f) neg = 0; else n = 0;
    d = (u64 *)p;
    d[0] = 0x4000000000000001;
    k3 = 63;
    tag = p + 5;
    k4 = 0x4007ff8001300000;
    k5 = 22;
    d[1] = kk;
    k6 = 68;
    d[3] = k3;
    k7 = 66;
    d[4] = k4;
    d[2] = 0;
    d[5] = k5;
    d[6] = k6;
    d[7] = k7;
    d[8] = cl;
    d[9] = 1;
    p += 6;
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
    val = x * 16 + 0x7000;
    h = sc * 16;
    cy = y * 16 + 0x7400;
    adv = h + func_001efba8();
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
    if (neg) {

        Glyph *gl; s32 s;
        gl = D_003E8CD0;
        f7 = gl->f7;
        w = gl->w << 4;
        s = w * sc / KH1_GLYPH;
        g = (Pg *)p;
        g->d[0] = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        g->x20 = i = val + ((h - s) >> 1);
        f4 = gl->f4;
        f2 = gl->f2;
        g->d[1] = 22;
        g->x10 = f2;
        g->x14 = f4;
        g->x24 = cy;
        g->x28 = 0x100000;
        g->x2c = 0x8000;
        g->x30 = f2 + w;
        g->x40 = cx = i + s;
        g->x34 = f4 + KH1_GLYPH * 16;
        g->x4c = 0;
        ((UF *)&g->x44)->i = cy + h;
        g->x48 = 0x100000;

        val += adv;
        p += 5;
    }
    for (n--; n >= 0; n--) {

        Glyph *gl; s32 s;
        gl = D_003E8CD8[dig[n]];
        f7 = gl ->f7;
        w = gl ->w << 4;
        s = w * sc / KH1_GLYPH;
        g = (Pg *)p;
        g ->d[0] = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        g ->x20 = i = val + ((h - s) >> 1);
        f4 = gl ->f4;
        f2 = gl ->f2;
        g ->d[1] = 22;
        g ->x10 = f2;
        g ->x14 = f4;
        g ->x24 = cy;
        g ->x28 = 0x100000;
        g ->x2c = 0x8000;
        g ->x30 = f2 + w;
        g ->x40 = cx = i + s;
        ((UF *)&g ->x34)->i = f4 + KH1_GLYPH * 16;
        g ->x44 = cy + h;
        g ->x48 = 0x100000;
        g ->x4c = 0;

        val += adv;
        p += 5;
    }
    { s32 m = (p - start) / 5; tag->b = 0x4343e; tag->a = m | ((u64)a1 << 15) | 0x50ab400000000000; }
    D_0063F74C = (val - 0x7000) >> 4;
    D_0063F750 = (cy - 0x7400) >> 4;
    return p;
}

/* func_001f1fc8: MATCHED (session 128), hand/nofill, rodata (jump table at
 * 0x00490a80).  Draws a message string at once: the font header, then one
 * sprite per glyph sent through path 2 (the control codes below 21 move the
 * pen, set the colour or size, or draw a nested string or number from
 * D_003E8E08's argument list).  From s11w32's 2-word draft
 * (nonmatchings/session11/w32__001f1fc8_2w.c); a long decomp-permuter run found
 * the last two words: `cx += adv;` written after the sceGsSyncPath call
 * instead of between the two sends, which moves the `one` (sd 24) and x30
 * stores of the glyph block to the original's places.  Needs the
 * CONTEXT_ONLY copy of func_001f0148 above it. */
CONTEXT_ONLY s32 func_001f0148(u8 *s, s32 sz)
{
    s32 w = 0;
    u8 **a = (u8 **)D_003E8E08;
    s32 c;
    Glyph *g;

    for (;;) {
        if (*s < 21) {
            switch (*s) {
            case 1:
                w += (sz << 8) / 18;
                s++;
                break;
            case 12:
                sz = s[1];
                s += 2;
                break;
            case 7:
            case 15:
                s += 2;
                break;
            case 10:
                if (*a) w += func_001f0148(*a, sz) << 4;
                a++;
                s++;
                break;
            case 4:
            case 5:
            case 6:
            case 9:
                s++;
                break;
            case 11:
                w += func_001f0448(s[2], s[3], *a, sz) << 4;
                a++;
                s += 4;
                break;
            case 13:
                w += (s16)(s[1] | (s[2] << 8)) * sz * 16 / 18;
                s += 3;
                break;
            case 8:
                s += 5;
                break;
            case 14:
            case 17:
            case 18:
            case 19:
            case 20:
                s += 3;
                break;
            case 0:
            case 2:
            case 3:
            case 16:
                return w >> 4;
            default:
                s++;
                break;
            }
        } else {
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
            w += ((g->w << 4) + func_001efb88()) * sz / 18;
        }
    }
}

/* the glyph sprite of func_001f1fc8's packet: tag, colour, then UV, XYZ, UV, XYZ */
typedef struct {
    u64 d[2];
    u64 col, one;
    s32 x20, x24, x28, x2c;
    s32 x30, x34, x38, x3c;
    s32 x40, x44, x48, x4c;
    s32 x50, x54, x58, x5c;
} Gl;

#define SETX_MSG() \
    switch (mode) { \
    case 0: \
    default: \
        cx = x * 16 + 0x7000; \
        break; \
    case 1: \
        cx = (x - func_001f0148(str, sc)) * 16 + 0x7000; \
        break; \
    case 2: \
        cx = (x - func_001f0148(str, sc) / 2) * 16 + 0x7000; \
        break; \
    }

/* rodata (jump table at 0x00490a80) */
s32 func_001f1fc8(s32 mode, s32 color, s32 x, s32 y, u8 *str, s32 sc) {
    u8 *buf;
    u32 ua;
    u64 *d;
    Q *p;
    Gl *g;
    Glyph *gl;
    s32 cx, cy, k, w, s, h, adv;
    s32 *argp;
    s32 defcol;
    s32 f2, f4;
    u8 f7;

    func_001efb78(0);
    h = sc << 4;
    func_001efb98(0);
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F2270));
    buf = func_00122048(1024, 128);
    ua = PLAT_DMA_SPR_ADDR(buf);
    p = (Q *)(buf + 16);
    d = (u64 *)p;
    d[0] = 0x1000000000000003;
    d[1] = 14;
    d[3] = 63;
    d[4] = 0x4007ff8001300000;
    cy = y * 16 + 0x7400;
    defcol = color;
    d[2] = 0;
    d[5] = 22;
    d[6] = 68;
    d[7] = 66;
    d[8] = 0x60ab400000008001;
    d[9] = 0x4343ee;
    p = (Q *)(buf + 96);
    *(u64 *)buf = 0x7000000b;
    argp = D_003E8E08;
    SETX_MSG();
    for (;;) {
        if (*str < 21) {
            switch (*str) {
            case 0:
            case 16:
                goto done;
            case 1:
                str++;
                cx += (sc << 8) / KH1_GLYPH;
                break;
            case 3:
                str++;
                D_0063F740 = *str << 4;
            case 2:
                str++;
                cy += D_0063F740;
                SETX_MSG();
                break;
            case 4: str++; mode = 0; break;
            case 5: str++; mode = 1; break;
            case 6: str++; mode = 2; break;
            case 7:
                if (str[1]) color = D_003E8D00[str[1] + 1];
                else color = defcol;
                str += 2;
                break;
            case 8:
                color = str[1] | (str[2] << 8) | (str[3] << 16) | (str[4] << 24);
                str += 5;
                break;
            case 9:
                str++;
                color = *argp++;
                break;
            case 10:
                if (*argp) {
                    cx = func_001f1fc8(0, color, cx >> 4, cy >> 4, (u8 *)*argp, sc) << 4;
                    cy = D_0063F750 << 4;
                }
                str++;
                argp++;
                break;
            case 11:
                cx = func_001f2d68(str[1], str[2], str[3], cx >> 4, cy >> 4, *argp, sc, color) << 4;
                argp++;
                str += 4;
                cy = D_0063F750 << 4;
                break;
            case 12:
                sc = str[1];
                str += 2;
                h = sc << 4;
                break;
            case 13:
                cx += (s16)(str[1] | (str[2] << 8)) << 4;
                str += 3;
                break;
            case 14:
                cy += (s16)(str[1] | (str[2] << 8)) << 4;
                str += 3;
                break;
            case 15: str += 2; break;
            case 17:
            case 19:
                x = (s16)(str[1] | (str[2] << 8));
                str += 3;
                cx = x * 16 + 0x7000;
                break;
            case 18:
            case 20:
                cy = ((s16)(str[1] | (str[2] << 8)) << 4) + 0x7400;
                str += 3;
                break;
            default:
                str++;
                break;
            }
        } else {
            if (*str == 24) {
                k = (str[1] << 8) - 0x1820;
                str += 2;
            } else if (*str < 32) {
                k = ((str[0] << 8) | str[1]) - 0x1820;
                str += 2;
            } else {
                k = *str - 32;
                str++;
            }
            gl = &D_003E8E28[k];
            w = gl->w << 4;
            s = w * sc / KH1_GLYPH;
            adv = (w + func_001efb88()) * sc / KH1_GLYPH;
            f2 = gl->f2;
            f4 = gl->f4;
            g = (Gl *)p;
            f7 = gl->f7;
            g->d[0] = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
            g->d[1] = 22;
            g->col = (u32)color;
            g->one = 1;
            g->x20 = f2;
            g->x24 = f4;
            g->x30 = cx;
            g->x34 = cy;
            g->x38 = 0x100000;
            g->x3c = 0x8000;
            g->x40 = f2 + w;
            g->x44 = f4 + KH1_GLYPH * 16;
            g->x50 = cx + s;
            g->x54 = cy + h;
            g->x58 = 0x100000;
            g->x5c = 0;
            PlatDmaSend(PlatDmaGetChan(2), ua);
            PlatGsSyncPath(0, 0);
            cx += adv;
        }
    }
done:
    func_001220b8(buf);
    D_0063F74C = (cx - 0x7000) >> 4;
    D_0063F750 = (cy - 0x7400) >> 4;
    return D_0063F74C;
}

/* func_001f2630: MATCHED (session 128), hand/nofill.  Draws a two-byte string
 * at once (the func_001f0ea8 glyph walk, one sprite per glyph sent through
 * path 2; '\n' starts a new line D_0063F740 lower).  KH1_V0: the callers read
 * D_0063F74C back from v0 (portability rule 10).  From s11w32's 1-word draft
 * (nonmatchings/session11/w32__001f2630_1w.c); the last word (the x2c store
 * issued right after d[1]) went with the same change as func_001f1fc8's:
 * `cx += a;` written after the sceGsSyncPath call. */
KH1_V0(s32) func_001f2630(s32 mode, u32 a1, s32 x, s32 y, u8 *str, s32 sc) {
    u64 *d;
    Q *buf;
    void *dma;
    Pg *g;
    Glyph *gl;
    s32 cx, cy, c, w, s, h;
    u8 f7;
    s32 f2, f4, a;

    func_001efb78(0);
    func_001efb98(0);
    h = sc * 16;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F2270));
    buf = (Q *)func_00122048(1024, 128);
    dma = (void *)PLAT_DMA_SPR_ADDR(buf);
    g = (Pg *)(buf + 1);
    d = (u64 *)g;
    d[0] = 0x4000000000000001;
    d[1] = 0xeeee;
    d[2] = 0;
    d[3] = 0x3f;
    d[4] = 0x4007ff8001300000;
    d[5] = 22;
    d[6] = 68;
    d[7] = 66;
    d[8] = a1;
    d[9] = 1;
    d[10] = 0x50ab400000008001;
    d[11] = 0x4343e;
    *(u64 *)buf = 0x7000000b;
    g = (Pg *)(buf + 7);
    cy = y * 16 + 0x7400;
    SETX();
    for (;;) {
        c = *str;
        if (c == 0) goto done;
        if (c == '\n') {
            str++;
            cy += D_0063F740;
            SETX();
            continue;
        }
        c |= str[1] << 8;
        str += 2;
        if (c == 0x4081) {
            cx += (sc << 8) / KH1_GLYPH;
            continue;
        }
        gl = &D_003E8E28[func_001eff50(c)];
        w = gl->w << 4;
        s = w * sc / KH1_GLYPH;
        a = (w + func_001efb88()) * sc / KH1_GLYPH;
        f7 = gl->f7;
        f4 = gl->f4;
        g->d[0] = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        g->x24 = cy;
        g->x40 = cx + s;
        g->d[1] = 22;
        g->x2c = 0x8000;
        g->x20 = cx;
        f2 = gl->f2;
        g->x28 = 0x100000;
        g->x30 = f2 + w;
        g->x34 = f4 + KH1_GLYPH * 16;
        g->x48 = 0x100000;
        g->x44 = cy + h;
        g->x10 = f2;
        g->x14 = f4;
        g->x4c = 0;
        PlatDmaSend(PlatDmaGetChan(2), dma);
        PlatGsSyncPath(0, 0);
        cx += a;
    }
done:
    func_001220b8((u8 *)buf);
    D_0063F74C = (cx - 0x7000) >> 4;
    D_0063F750 = (cy - 0x7400) >> 4;
    KH1_V0_RETURN(D_0063F74C);
}

void func_001f2eb8(void) {
    Q *p, *d;
    p = &D_003F1A70;
    d = p;
    p++;
    p->a = 0x1000000000008001;
    p->b = 14;
    p++;
    p->b = 0x47;
    p->a = 0x4000d;
    p++;
    func_0011fb78(d, 7, p);
    func_0011fbb0(0x3d7c, 4, 20, 0, 0, 256, 256, 2048, D_003E9660, D_003F2670);
    func_0011fbb0(0x3dfc, 1, 0, 0, 0, 16, 16, 64, D_003F1660, D_003F2720);
    p = &D_003F1E70;
    d = p;
    p++;
    p->a = 0x1000000000008004;
    p->b = 14;
    p++;
    p->a = 0x4000d;
    p->b = 0x47;
    p++;
    p->b = 0x3f;
    p->a = 0;
    p++;
    p->a = 0x2007bf8621413d7c;
    p->b = 6;
    p++;
    p->a = 0x61;
    p->b = 0x14;
    p++;
    func_0011fb78(d, 7, p);
    p = &D_003F2270;
    d = p;
    p++;
    p->a = 0x1000000000008004;
    p->b = 14;
    p++;
    p->a = 0x4000d;
    p->b = 0x47;
    p++;
    p->b = 0x3f;
    p->a = 0;
    p++;
    p->a = 0x2007ff8622411000;
    p->b = 6;
    p++;
    p->a = 0x61;
    p->b = 0x14;
    p++;
    func_0011fb78(d, 7, p);
    p = D_003F27D0;
    d = p;
    p++;
    p->a = 0x1000000000008001;
    p->b = 14;
    p++;
    p->b = 0x47;
    p->a = 0x5000d;
    p++;
    func_0011fb78(d, 7, p);
    D_003F1A68 = 0;
    func_001f3110();
}
