/* xs_genie.x func_00f21f68: matched by hand. */
#include "ovl.h"

typedef struct { u64 flags; s32 pad; f32 fC; OvlVec pos; } Sub;
typedef struct { u8 pad[0x10]; OvlVec pos; u8 pad2[4]; Sub *f24; } Obj;
s32 func_00f21f68(Obj *o) {
    o->f24->flags = (o->f24->flags & ~0xC) | 4;
    o->f24->fC = 170.0f;
    PlatVu0CopyVector(o->f24->pos, o->pos);
    return 0;
}
