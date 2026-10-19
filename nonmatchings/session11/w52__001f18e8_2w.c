/* 001f18e8 2w LCS (2 pos; was 9), hand/nofill, no context, right size 1288. s11w52, FLAGGED dead FP test: s11w50 9w + `u64 cl = col;` between the two calls (no lwu), `kk = 0xeeee;` then `if ((f32)nd < 0.0f) neg = 0; else n = 0;` right after the 2nd call (block split: tag = p + 5 stays after jal 1efb98; flow2 deletes the test), constants k4..k9 assigned early and stored later (one-constant lever) so li 63 is born last in sched1 (local-alloc gives 63 v1, d0 a0), post-call order hill-climbed. Every register and store right; left only: sched2 issues li t1,1 in the slot after li eeee and li v1,63 last (original: li v1,63 there, li t1,1 last). li order in sched2 follows sched1 order, and with these lengths 63 must be born last for local-alloc; the original likely has an extra ref on the 63 pseudo or another structure. */
#include "common.h"

typedef struct { u16 code; u16 f2; u16 f4; u8 w; u8 f7; } Glyph;
typedef struct { u64 a, b; } Q;
typedef union { s32 i; f32 f; } UF;
typedef union { u16 h; s16 s; } UH;
typedef union { u8 b; s8 c; } UB;
typedef union { u64 d; s32 w[2]; } UQ;
typedef struct {
    u64 d[2];
    s32 x10, x14, x18, x1c;
    s32 x20, x24, x28, x2c;
    s32 x30, x34, x38, x3c;
    s32 x40, x44, x48, x4c;
} Pg;
extern Glyph *D_003E8CD0;
extern Glyph *D_003E8CD8[];
extern s32 D_003E8D00[];
extern s32 D_0063F74C;
extern s32 D_0063F750;
void func_001efb78(s32);
void func_001efb98(s32);
s32 func_001efba8(void);

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
    u64 k4, k5, k6, k7, k9;
    u64 kk;
    u64 cl;

    neg = 0;
    func_001efb78(0);
    cl = col;
    func_001efb98(0);
    kk = 0xeeee;
    if ((f32)nd < 0.0f) neg = 0; else n = 0;
    d = (u64 *)p;
    d[0] = 0x4000000000000001;
    tag = p + 5;
    k9 = 1;
    k4 = 0x4007ff8001300000;
    k5 = 22;
    d[1] = kk;
    k6 = 68;
    k7 = 66;
    d[3] = 63;
    d[4] = k4;
    d[2] = 0;
    d[5] = k5;
    d[6] = k6;
    d[7] = k7;
    d[8] = cl;
    d[9] = k9;
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
        s = w * sc / 18;
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
        g->x34 = f4 + 288;
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
        s = w * sc / 18;
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
        ((UF *)&g ->x34)->i = f4 + 288;
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
