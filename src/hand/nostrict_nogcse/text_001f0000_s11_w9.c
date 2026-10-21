#include "common.h"

/* func_001fb428 (s11w9): t (w*sz/18) is one function-level variable shared by the neg block and
   the digit loop (a global pseudo, so local-alloc cannot tie it to x0 + t); x1 is block-local in
   the loop (its own pseudo, v0); neg block statement order hill-climbed. */
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
#include "data/pieces/D_003F2270.h"
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


void func_001fb428(Txt9 *o, s32 mode, u32 nd, s32 pad, s32 x, s32 y, s32 val, s32 sz, u32 col) {
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

    func_00266f38(func_00266c08(2), ((Q *)&D_003F2270));
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
    fl = o->x48 & 1;
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
    func_00266f38(func_00266c08(2), (void *)tag);
    sceGsSyncPath(0, 0);
    func_001220b8(base);
    D_003F2BD0 = (val - ox) >> 4;
    D_003F2BD4 = (yy - oy) >> 4;
}
#include "data/data_003E.h"
#include "data/data_003F.h"
