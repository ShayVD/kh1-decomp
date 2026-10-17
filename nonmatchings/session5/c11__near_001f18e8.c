#include "common.h"

typedef struct { u16 code; u16 f2; u16 f4; u8 w; u8 f7; } Glyph;
typedef struct { u64 d0; u64 d1; s32 w[16]; } GP;

extern Glyph *D_003E8CD0;
extern Glyph *D_003E8CD8[];
extern s32 D_003E8D00[];
extern s32 D_0063F74C;
extern s32 D_0063F750;
void func_001efb78(s32);
void func_001efb98(s32);
s32 func_001efba8(void);

u64 *func_001f18e8(u64 *p, s32 pri, s32 mode, s32 nd, s32 pad, s32 x, s32 y, s32 val, s32 sz, u32 col) {
    s32 dig[12];
    u64 *start;
    u64 *hdr;
    s32 n, neg, i;
    s32 xx, yy, sz16, adv, t, w;
    Glyph *g;
    s32 f2, f4;
    u8 f7;

    neg = 0;
    func_001efb78(0);
    func_001efb98(0);
    p[2] = 0;
    p[1] = 0xeeee;
    p[6] = 68;
    p[0] = 0x4000000000000001;
    p[4] = 0x4007ff8001300000;
    p[5] = 22;
    p[3] = 63;
    p[7] = 66;
    p[8] = col;
    p[9] = 1;
    hdr = p + 10;
    p += 12;
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
                    n++;
                    val /= 10;
                }
            } while (n < nd);
        }
    }
    val = x * 16 + 0x7000;
    sz16 = sz * 16;
    yy = y * 16 + 0x7400;
    adv = sz16 + func_001efba8();
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
/*P*/
        g = D_003E8CD0;
        f7 = g->f7;
        w = g->w << 4;
        t = w * sz / 18;
        f2 = g->f2;
        ((GP *)p)->w[7] = 0x8000;
        f4 = g->f4;
        ((GP *)p)->d1 = 22;
        ((GP *)p)->d0 = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        ((GP *)p)->w[14] = 0x100000;
        ((GP *)p)->w[0] = f2;
        ((GP *)p)->w[1] = f4;
        ((GP *)p)->w[13] = yy + sz16;
        ((GP *)p)->w[8] = f2 + w;
        ((GP *)p)->w[5] = yy;
        ((GP *)p)->w[15] = 0;
        ((GP *)p)->w[12] = val + ((sz16 - t) >> 1) + t;
        ((GP *)p)->w[4] = val + ((sz16 - t) >> 1);
        ((GP *)p)->w[6] = 0x100000;
        ((GP *)p)->w[9] = f4 + 288;
/*Q*/
        val += adv;
        p += 10;
    }
    for (n--; n >= 0; n--) {
        g = D_003E8CD8[dig[n]];
        f2 = g->f2;
        f7 = g->f7;
        f4 = g->f4;
        w = g->w << 4;
        ((GP *)p)->d0 = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        ((GP *)p)->w[9] = f4 + 288;
        ((GP *)p)->d1 = 22;
        ((GP *)p)->w[0] = f2;
        ((GP *)p)->w[8] = f2 + w;
        t = w * sz / 18;
        ((GP *)p)->w[4] = val + ((sz16 - t) >> 1);
        ((GP *)p)->w[5] = yy;
        ((GP *)p)->w[15] = 0;
        ((GP *)p)->w[1] = f4;
        ((GP *)p)->w[12] = val + ((sz16 - t) >> 1) + t;
        ((GP *)p)->w[7] = 0x8000;
        ((GP *)p)->w[14] = 0x100000;
        ((GP *)p)->w[6] = 0x100000;
        ((GP *)p)->w[13] = yy + sz16;
        val += adv;
        p += 10;
    }
    hdr[1] = 0x4343e;
    hdr[0] = (((u64 (*)[2])p - (u64 (*)[2])start) / 5) | ((u64)pri << 15) | 0x50ab400000000000;
    D_0063F74C = (val - 0x7000) >> 4;
    D_0063F750 = (yy - 0x7400) >> 4;
    return p;
}
