/* func_0014cdc8: 9 words off (hand, strict): else-branch FP register choice (orig 0.5->f5, x14->f2, 20->f4, result f2). */
#include "common.h"

typedef struct {
    u8 pad0[0x14];
    f32 x14;
    u8 pad18[0x3b0 - 0x18];
    f32 x3b0;
    f32 x3b4;
    f32 x3b8;
    f32 x3bc;
    f32 v3c0[4];
} Pc;
f32 sinf(f32);
void func_0014cd38(Pc *);
extern f32 D_002BBDFC;

static inline f32 mn(f32 x, f32 l) { if (!(x < l)) x = l; return x; }
void func_0014cdc8(Pc *o, f32 *v) {
    f32 a;
    f32 b;
    f32 lim;
    f32 y;

    a = o->x3b0;
    b = o->x3b8;
    if (a < b) {
        a = sinf(a / b * 3.1415928f * 0.5f);
        a = sinf(a * 3.1415928f * 0.5f);
        y = o->x3b4 + a * o->x3bc; v[1] = y - o->x14;
        func_0014cd38(o);
    } else {
        a -= b;
        y = o->x3b4 + o->x3bc; y += 0.4846938625f * a * a * 0.5f;
        v[1] = mn(y - o->x14, D_002BBDFC * 20.0f);
    }
    o->v3c0[1] = v[1];
}
