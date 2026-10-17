#include "common.h"

typedef struct { u16 code; u16 f2; u16 f4; u8 w; u8 f7; } Glyph;
typedef struct {
    u64 tag, reg, col, one;
    s32 x20, x24, x28, x2c;
    s32 x30, x34, x38, x3c;
    s32 x40, x44, x48, x4c;
    s32 x50, x54, x58, x5c;
} Gl;
typedef struct { u64 d[14]; Gl g[1]; } Hd;

extern Glyph *D_003E8E28;
extern s32 D_003E8D00[];
extern s32 D_003E8E08[];
extern s32 D_0063F740;
extern s32 D_0063F74C;
extern s32 D_0063F750;
void func_001efb78(s32);
void func_001efb98(s32);
s32 func_001efb88(void);
s32 func_001f0148(u8 *, s32);

Gl *func_001f0868(Hd *p, s32 a1, s32 align, s32 color, s32 x, s32 y, u8 *s, s32 scale) {
    s32 d = 18;
    Gl *g;
    u64 *q;
    s32 cx, cy, sc16, defcol;
    s32 *argp;
    s32 k, w, t;
    Glyph *gl;

    func_001efb78(0);
    func_001efb98(0);
    cy = y * 16 + 0x7400;
    p->d[0] = 0x1000000000000005;
    q = &p->d[12];
    p->d[1] = 14;
    p->d[3] = 63;
    p->d[4] = 0x2007ff8622411000;
    p->d[5] = 6;
    p->d[6] = 97;
    p->d[7] = 20;
    argp = D_003E8E08;
    p->d[8] = 0x4007ff8001300000;
    sc16 = scale << 4;
    defcol = color;
    p->d[9] = 22;
    p->d[10] = 68;
    p->d[11] = 66;
    p->d[2] = 0;
    g = p->g;
    switch (align) {
    case 1: cx = (x - func_001f0148(s, scale)) * 16 + 0x7000; break;
    case 2: cx = (x - func_001f0148(s, scale) / 2) * 16 + 0x7000; break;
    default: cx = x * 16 + 0x7000; break;
    }
    for (;;) {
        if (*s < 21) {
            switch (*s) {
            case 0:
            case 16:
                goto end;
            case 1:
                s++;
                cx += (scale << 8) / d;
                break;
            case 3:
                s++;
                D_0063F740 = *s << 4;
            case 2:
                s++;
                cy += D_0063F740;
                switch (align) {
                case 1: cx = (x - func_001f0148(s, scale)) * 16 + 0x7000; break;
                case 2: cx = (x - func_001f0148(s, scale) / 2) * 16 + 0x7000; break;
                default: cx = x * 16 + 0x7000; break;
                }
                break;
            case 4: s++; align = 0; break;
            case 5: s++; align = 1; break;
            case 6: s++; align = 2; break;
            case 7:
                if (s[1]) color = D_003E8D00[s[1] + 1];
                else color = defcol;
                s += 2;
                break;
            case 8:
                color = s[1] | (s[2] << 8) | (s[3] << 16) | (s[4] << 24);
                s += 5;
                break;
            case 9:
                s++;
                color = *argp++;
                break;
            case 10: s++; break;
            case 11: s += 4; break;
            case 12:
                scale = s[1];
                s += 2;
                sc16 = scale << 4;
                break;
            case 13:
                cx += (s16)(s[1] | (s[2] << 8)) << 4;
                s += 3;
                break;
            case 14:
                cy += (s16)(s[1] | (s[2] << 8)) << 4;
                s += 3;
                break;
            case 15: s += 2; break;
            case 17:
            case 19:
                x = (s16)(s[1] | (s[2] << 8));
                s += 3;
                cx = x * 16 + 0x7000;
                break;
            case 18:
            case 20:
                cy = ((s16)(s[1] | (s[2] << 8)) << 4) + 0x7400;
                s += 3;
                break;
            default:
                s++;
                break;
            }
        } else {
            if (*s == 24) {
                k = (s[1] << 8) - 0x1820;
                s += 2;
            } else if (*s < 32) {
                k = ((s[0] << 8) | s[1]) - 0x1820;
                s += 2;
            } else {
                k = *s - 32;
                s++;
            }
            gl = &D_003E8E28[k];
            w = gl->w << 4;
            t = w * scale / d;
            k = (w + func_001efb88()) * scale / d;
            g->tag = ((u64)D_003E8D00[gl->f7 >> 4] << 20) | ((u64)(gl->f7 & 0xf) << 56) | (0xfff0ULL << 35);
            g->reg = 22;
            g->col = (u32)color;
            g->one = 1;
            g->x20 = gl->f2;
            g->x24 = gl->f4;
            g->x30 = cx;
            g->x34 = cy;
            g->x38 = 0x100000;
            g->x3c = 0x8000;
            g->x40 = gl->f2 + w;
            g->x44 = gl->f4 + 288;
            g->x50 = cx + t;
            g->x54 = cy + sc16;
            g->x58 = 0x100000;
            g->x5c = 0;
            g++;
            cx += k;
        }
    }
end:
    q[1] = 0x4343ee;
    q[0] = (((u8 *)g - (u8 *)p->g) >> 4) / 6 | ((u64)a1 << 15) | 0x60ab400000000000;
    D_0063F74C = (cx - 0x7000) >> 4;
    D_0063F750 = (cy - 0x7400) >> 4;
    return g;
}
