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
extern Glyph *D_003E8E28;
extern s32 D_003E8D00[];
extern s32 D_0063F740;
extern s32 D_0063F74C;
extern s32 D_0063F750;
void func_001efb78(s32);
void func_001efb98(s32);
s32 func_001efb88(void);
s32 func_001eff50(s32);
s32 func_001f0340(u8 *, s32);

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
            cx += (sc << 8) / 18;
            continue;
        }
        gl = &D_003E8E28[func_001eff50(c)];
        w = gl->w << 4;
        s = w * sc / 18;
        c = (w + func_001efb88()) * sc / 18;
        g = (Pg *)p;
/*P*/
        f7 = gl->f7;
        g->d[0] = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        g->d[1] = 22;
        f4 = gl->f4;
        g->x40 = cx + s;
        g->x2c = 0x8000;
        g->x20 = cx;
        g->x48 = 0x100000;
        g->x14 = f4;
        f2 = gl->f2;
        g->x24 = cy;
        g->x30 = f2 + w;
        g->x34 = f4 + 288;
        g->x28 = 0x100000;
        g->x44 = cy + h;
        g->x4c = 0;
        g->x10 = f2;
/*Q*/
        p += 5;
        cx += c;
    }
done:
    {
    s32 ex = cx - 0x7000;
    s32 ey = cy - 0x7400;
    tag->b = 0x4343e;
    tag->a = (p - start) / 5 | ((u64)a1 << 15) | 0x50ab400000000000;
    D_0063F74C = ex >> 4;
    D_0063F750 = ey >> 4;
    }
    return p;
}
