/* 001f18e8: 48w LCS (was 115), hand/nofill, 1288 vs 1288. Changes: val reused as the x cursor after the digit loops (orig keeps cx in s2 = val's reg; fixes p=s1/val=s2 global-alloc order), `g->x20 = i = val + ((h - s) >> 1); g->x40 = i + s;` reusing i, then LCS hill-climb of header/neg/loop store orders. Left: in both glyph blocks the orig has gl in a1, f2+w in a2, s=w*sc in a3, 18 in a2 (neg block) - local-alloc order (ours f2+w a1, s a2, gl a3); header: tag=p+5 computed after the second call. Same pattern as 001fb428. */
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
    Glyph *gl;
    s32 n, neg;
    s32 cx, cy, h, adv, s, w;
    s32 f2, f4;
    u8 f7;
    s32 i;

    neg = 0;
    func_001efb78(0);
    func_001efb98(0);
    d = (u64 *)p;

    d[0] = 0x4000000000000001;
    d[5] = 22;
    d[3] = 63;
    d[8] = col;
    tag = p + 5;
    d[4] = 0x4007ff8001300000;
    d[1] = 0xeeee;
    d[6] = 68;
    d[7] = 66;
    d[2] = 0;
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
                    n++;
                    val /= 10;
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

        g = (Pg *)p;
        gl = D_003E8CD0;
        f4 = gl->f4;
        g->x48 = 0x100000;
        w = gl->w << 4;
        f7 = gl->f7;
        s = w * sc / 18;
        g->d[0] = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        g->x2c = 0x8000;
        f2 = gl->f2;
        g->x14 = f4;
        g->x20 = i = val + ((h - s) >> 1);
        g->x24 = cy;
        g->x34 = f4 + 288;
        g->d[1] = 22;
        g->x44 = cy + h;
        g->x30 = f2 + w;
        g->x4c = 0;
        g->x40 = i + s;
        g->x10 = f2;
        g->x28 = 0x100000;

        val += adv;
        p += 5;
    }
    for (n--; n >= 0; n--) {

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
        g->x40 = i + s;
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
