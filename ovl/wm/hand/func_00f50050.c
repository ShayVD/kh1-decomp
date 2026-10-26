/* wm.x func_00f50050: the twin of gb.x func_00f28f58 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { u8 r, g, b, a; } C28f58;
extern f32 D_00FA5AF8;
extern s32 D_00FA5B04;
extern C28f58 D_00FA5B10[];
extern u32 D_0108CE50[];

void func_00f50050(void) {
    s32 i;
    s32 r, g, b;
    C28f58 *s;
    u32 *d;
    s32 x;

    s = D_00FA5B10;
    x = D_00FA5B04 << 24;
    d = D_0108CE50;
    for (i = 6; i >= 0; i--) {
        r = s->r * D_00FA5AF8; g = s->g * D_00FA5AF8; b = s->b * D_00FA5AF8;
        *d++ = r | (g << 8) | (b << 16) | x;
        s++;
    }
}
