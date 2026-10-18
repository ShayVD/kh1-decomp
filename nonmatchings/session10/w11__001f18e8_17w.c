/* 001f18e8: 17w LCS (posoff 54; was 48), hand/nofill, no context, 1288 bytes. New: gl and s block-local in each glyph block (local-alloc then gives gl a1, s a3 like the orig), the neg block in exactly the same statement order as the loop block (a shared macro-like body), 'g->x40 = cx = i + s;' (cx otherwise unused, function-level: a global pseudo so the sum is not tied to s), header order re-hill-climbed, pad loop 'dig[n] = val % 10; val /= 10; n++;'. Left: tag = p + 5 (spilled to 60(sp)) is hoisted by sched1 above the 2nd call (orig: after it; tag crosses calls so sched1 may move it), and glyph-block lhu f2/f4 vs sw x44/x4c order (both blocks; hill-climb of the shared order found nothing). */
#include "common.h"

typedef struct { u16 code; u16 f2; u16 f4; u8 w; u8 f7; } Glyph;
typedef struct { u64 a, b; } Q;
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

    neg = 0;
    func_001efb78(0);
    func_001efb98(0);
    d = (u64 *)p;

    d[0] = 0x4000000000000001;
    d[1] = 0xeeee;
    d[3] = 63;
    d[8] = col;
    d[4] = 0x4007ff8001300000;
    tag = p + 5;
    d[5] = 22;
    d[2] = 0;
    d[6] = 68;
    d[7] = 66;
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
        s = w * sc / 18;
        g = (Pg *)p;
        g->d[0] = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        g->x20 = i = val + ((h - s) >> 1);
        f4 = gl->f4;
        f2 = gl->f2;
        g->x4c = 0;
        g->d[1] = 22;
        g->x10 = f2;
        g->x14 = f4;
        g->x24 = cy;
        g->x28 = 0x100000;
        g->x2c = 0x8000;
        g->x30 = f2 + w;
        g->x40 = cx = i + s;
        g->x34 = f4 + 288;
        g->x44 = cy + h;
        g->x48 = 0x100000;

        val += adv;
        p += 5;
    }
    for (n--; n >= 0; n--) {

        Glyph *gl; s32 s;
        gl = D_003E8CD8[dig[n]];
        f7 = gl->f7;
        w = gl->w << 4;
        s = w * sc / 18;
        g = (Pg *)p;
        g->d[0] = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        g->x20 = i = val + ((h - s) >> 1);
        f4 = gl->f4;
        f2 = gl->f2;
        g->x4c = 0;
        g->d[1] = 22;
        g->x10 = f2;
        g->x14 = f4;
        g->x24 = cy;
        g->x28 = 0x100000;
        g->x2c = 0x8000;
        g->x30 = f2 + w;
        g->x40 = cx = i + s;
        g->x34 = f4 + 288;
        g->x44 = cy + h;
        g->x48 = 0x100000;

        val += adv;
        p += 5;
    }
    { s32 m = (p - start) / 5; tag->b = 0x4343e; tag->a = m | ((u64)a1 << 15) | 0x50ab400000000000; }
    D_0063F74C = (val - 0x7000) >> 4;
    D_0063F750 = (cy - 0x7400) >> 4;
    return p;
}
