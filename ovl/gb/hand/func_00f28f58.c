/* gb.x func_00f28f58: matched by hand. */
#include "ovl.h"

typedef struct { u8 r, g, b, a; } C28f58;
extern f32 D_00F61378;
extern s32 D_00F61384;
extern C28f58 D_00F61390[];
extern u32 D_00F80690[];

void func_00f28f58(void) {
    s32 i;
    s32 r, g, b;
    C28f58 *s;
    u32 *d;
    s32 x;

    s = D_00F61390;
    x = D_00F61384 << 24;
    d = D_00F80690;
    for (i = 6; i >= 0; i--) {
        r = s->r * D_00F61378; g = s->g * D_00F61378; b = s->b * D_00F61378;
        *d++ = r | (g << 8) | (b << 16) | x;
        s++;
    }
}
