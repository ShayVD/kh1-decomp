/* 12w off: FP reg allocation only (orig t3=f6, 1.0f=f4, c[1]->f0, c[2]->f2; ours swapped). Insensitive to all modes/decl orders tried. */
#include "common.h"
typedef struct { f32 x, y, z, w; } V4f;
typedef struct { f32 c[4]; } Seg;
void func_00249718(V4f *o, Seg *s, f32 t) {
    f32 t2 = t * t;
    f32 t3 = t2 * t;
    o->x = s[0].c[0] * t3 + s[0].c[1] * t2 + s[0].c[2] * t + s[0].c[3];
    o->y = s[1].c[0] * t3 + s[1].c[1] * t2 + s[1].c[2] * t + s[1].c[3];
    o->z = s[2].c[0] * t3 + s[2].c[1] * t2 + s[2].c[2] * t + s[2].c[3];
    o->w = 1.0f;
}
