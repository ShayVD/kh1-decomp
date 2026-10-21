#include "common.h"
/* 001fbcd8 (hand/nostrict, no context). s11w42 MATCH, FLAGGED dead FP test. From s11w6's 15w draft: ONE v shared by the neg block and the digit loop (no v3), the loop's x2 renamed x3 (separate pseudo), and the dead test `if ((f32)v < 0.0f) i = 0;` at the end of the neg block (i is dead there; flow2 deletes the empty branch). The test keeps v live longer, so global-alloc ranks v below the loop temps (x3-ax temp a1, dig pointer giv a2, v t0). Neg block: the four g-> loads first (u, v, gw, gh, so no p-> store precedes a load under -fno-strict-aliasing), stores in a climbed order. */

typedef struct { u16 code; u16 f2; u16 f4; u8 w; u8 f7; } Glyph;
typedef struct { u64 d0; u64 d1; s32 w[16]; } GP;
typedef struct { u64 a, b; } Q;
typedef struct {
    u8 pad0[0x48];
    s32 x48;
    u8 pad4c[0x74 - 0x4c];
    f32 x74;
    f32 x78;
    u8 pad7c[0x90 - 0x7c];
    s32 x90;
    u8 pad94[0xb0 - 0x94];
    s32 xb0;
    s32 xb4;
} Txt9;

extern Glyph *D_003E8CD0;
extern Glyph *D_003E8CD8[];
extern s32 D_003E8D00[];
extern s32 D_003E8E04;
extern Q D_003F1E70[];
extern s32 D_003F2BD0;
extern s32 D_003F2BD4;
u64 *func_00122048(s32, s32);
void func_001220b8(void *);
u32 func_001edd88(u32, s32);
s32 func_001f4570(Txt9 *);
s32 func_001f45e0(Txt9 *);
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
s32 sceGsSyncPath(s32, s32);

#include "data/types/nostrict_text_001f0000_s11_w42.h"
typedef struct { s32 w[16]; } GQ;
extern BigG D_003E9250;
extern SmG D_003E9110[];

s32 func_001fbcd8(Txt9 *o, s32 mode, u32 nd, s32 pad, s32 x, s32 y, s32 val, s32 alpha, u32 col) {
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

    func_00266f38(func_00266c08(2), D_003F1E70);
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
    fl = o->x48 & 1;
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
    func_00266f38(func_00266c08(2), (void *)tag);
    sceGsSyncPath(0, 0);
    func_001220b8(base);
    return (xx - ox) >> 4;
}
#include "data/pieces/D_003E9110.h"
#include "data/pieces/D_003E9250.h"
