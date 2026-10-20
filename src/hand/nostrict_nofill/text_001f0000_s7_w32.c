/* func_001f0868: hand/nostrict_nofill (w10 draft unchanged; it was checked in hand/nofill only). Rodata jump table at 0x490a20. */
#include "common.h"

typedef struct { u16 code; u16 f2; u16 f4; u8 w; u8 f7; } Glyph;
typedef struct { u64 a, b; } Q;
typedef struct {
    u64 d[2];
    u64 col, one;
    s32 x20, x24, x28, x2c;
    s32 x30, x34, x38, x3c;
    s32 x40, x44, x48, x4c;
    s32 x50, x54, x58, x5c;
} Gl;
extern Glyph *D_003E8E28;
extern s32 D_003E8D00[];
extern s32 D_003E8E08[];
extern s32 D_0063F740;
extern s32 D_0063F74C;
extern s32 D_0063F750;

extern s32 D_003E8E00;
extern s32 D_003E8E04;
CONTEXT_ONLY void func_001efb78(s32 arg0) { D_003E8E00 = arg0; }
CONTEXT_ONLY s32 func_001efb88(void) { return D_003E8E00; }
CONTEXT_ONLY void func_001efb98(s32 arg0) { D_003E8E04 = arg0; }
s32 func_001f0148(u8 *, s32);

#define SETX() \
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

/* rodata */
Q *func_001f0868(Q *pk, s32 a1, s32 mode, s32 color, s32 x, s32 y, u8 *str, s32 sc) {
    u64 *d;
    Q *p, *start, *tag;
    Gl *g;
    Glyph *gl;
    s32 cx, cy, k, w, s, h;
    s32 *argp;
    s32 defcol;
    s32 f2, f4;
    u8 f7;

    func_001efb78(0);
    func_001efb98(0);
    cy = y * 16 + 0x7400;
    p = pk;
    d = (u64 *)p;
    d[0] = 0x1000000000000005;
    d[1] = 14;
    tag = p + 6;
    d[3] = 63;
    d[4] = 0x2007ff8622411000;
    d[5] = 6;
    d[6] = 97;
    d[7] = 20;
    argp = D_003E8E08;
    d[8] = 0x4007ff8001300000;
    h = sc << 4;
    defcol = color;
    d[9] = 22;
    d[10] = 68;
    d[11] = 66;
    d[2] = 0;
    p += 7;
    start = p;
    SETX();
    for (;;) {
        if (*str < 21) {
            switch (*str) {
            case 0:
            case 16:
                goto done;
            case 1:
                str++;
                cx += (sc << 8) / 18;
                break;
            case 3:
                str++;
                D_0063F740 = *str << 4;
            case 2:
                str++;
                cy += D_0063F740;
                SETX();
                break;
            case 4: str++; mode = 0; break;
            case 5: str++; mode = 1; break;
            case 6: str++; mode = 2; break;
            case 7:
                if (str[1]) color = D_003E8D00[str[1] + 1];
                else color = defcol;
            case 15:
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
            case 10: str++; break;
            case 11: str += 4; break;
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
            s = w * sc / 18;
            k = (w + func_001efb88()) * sc / 18;
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
            g->x44 = f4 + 288;
            g->x50 = cx + s;
            g->x54 = cy + h;
            g->x58 = 0x100000;
            g->x5c = 0;
            p += 6;
            cx += k;
        }
    }
done:
    {
    s32 ex = cx - 0x7000;
    s32 ey = cy - 0x7400;
    { u64 n = (p - start) / 6; tag->b = 0x4343ee; tag->a = n | ((u64)a1 << 15) | 0x60ab400000000000; }
    D_0063F74C = ex >> 4;
    D_0063F750 = ey >> 4;
    }
    return p;
}
#include "data/data_003E.h"
