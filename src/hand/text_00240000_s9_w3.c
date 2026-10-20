#include "common.h"
#include "data/bss_0066.h"
typedef union { u32 w; struct { s16 a; s16 b; } h; } E;
extern s32 D_0046A54C;
extern s32 D_0046A550;
extern s32 D_0046A540;
extern E *D_0046A568[];
extern s32 D_00669A5C;

/* func_0024bce8: *px / *py re-read at the end (gcse copies of the first loads, numbered after the -10 pseudo, so -10 wins the global-alloc tie). */
void func_0024bce8(s32 *px, s32 *py) {
    s32 x = *px;
    s32 y = *py;
    s32 dx, dy = 0;
    s32 i;
    E *e;
    if (x == D_0046A54C) {
        dx = (y == D_0046A550) ? -1 : 0;
    } else {
        dx = 1; if (x < D_0046A54C) dx = -1;
    }
    if (y != D_0046A550) {
        dy = 1; if (y < D_0046A550) dy = -1;
    }
    for (i = 0; i < 12; i++) {
        for (e = D_0046A568[D_0046A540]; e->h.b != -10; e++) {
            if (e->h.b != -1 && x == ((e->w >> 4) & 15) && y == ((e->w >> 8) & 15)) {
                *px = x;
                *py = y;
                return;
            }
        }
        x += dx;
        y += dy;
    }
    if (*px == 0) {
        if (D_00669A5C == 0) {
            if ((u32)*py < 3) {
                *px = 0;
                *py = 3;
                return;
            }
        } else if ((u32)*py < 4) {
            *px = 0;
            *py = 4;
            return;
        }
    }
    *px = D_0046A54C;
    *py = D_0046A550;
}
