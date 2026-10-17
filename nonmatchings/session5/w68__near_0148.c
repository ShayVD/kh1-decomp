#include "common.h"
typedef struct { u16 code; u16 f2; u16 f4; u8 w; u8 f7; } Glyph;
extern Glyph *D_003E8E28;
extern u8 *D_003E8E08[];
s32 func_001efb88(void);
s32 func_001f0448(s32, s32, u8 *, s32);

s32 func_001f0148(u8 *s, s32 sz)
{
    s32 w = 0;
    u8 **a = D_003E8E08;
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
