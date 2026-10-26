/* xs_genie.x func_00f21ec0: matched by hand. */
#include "ovl.h"

typedef struct { u64 flags; s32 f8; f32 fC; OvlVec pos; } Sub;
typedef struct { u8 pad[0x10]; OvlVec pos; u8 pad2[4]; Sub *f24; } Obj;
s32 func_0014a408(Obj *);
s32 func_001477e0(s32);
Sub *func_0014a4a8(s32, s32, s32);
extern s32 D_00F22E90;
extern s32 D_00F22E98;
void func_00f21ec0(Obj *o) {
    s32 a = func_0014a408(o);
    o->f24 = func_0014a4a8(D_00F22E90, a, func_001477e0(4));
    o->f24->flags = (o->f24->flags & ~0xC) | 4;
    o->f24->flags |= 0x800000;
    o->f24->fC = 170.0f;
    o->f24->f8 = D_00F22E98;
    PlatVu0CopyVector(o->f24->pos, o->pos);
}
