/* xs_genie.x func_00f21ab0: matched by hand. */
#include "ovl.h"

typedef struct { u64 flags; s32 f8; f32 fC; OvlVec pos; } Sub;
s32 func_0014a408(s32);
s32 func_001477e0(s32);
Sub *func_0014a4a8(s32, s32, s32);
extern s32 D_00F22E90;
extern s32 D_00F22E98;
void func_00f21ab0(s32 arg0, f32 *v, f32 f) {
    s32 a = func_0014a408(arg0);
    Sub *s = func_0014a4a8(D_00F22E90, a, func_001477e0(arg0));
    s->fC = f;
    s->flags = (s->flags & ~0xC) | 4;
    s->flags |= 0x800000;
    s->f8 = D_00F22E98;
    PlatVu0CopyVector(s->pos, v);
}
