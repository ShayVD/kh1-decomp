/* xs_dumbo.x func_00f20238: matched by hand. */
#include "ovl.h"

typedef struct { u64 flags; u8 pad[0x48]; f32 f50; } Sub;
s32 func_0014a408(s32);
s32 func_001477e0(s32);
Sub *func_0014a4a8(s32, s32, s32);
extern s32 D_00F23200;
Sub *func_00f20238(s32 arg0) {
    s32 a = func_0014a408(arg0);
    Sub *s = func_0014a4a8(D_00F23200, a, func_001477e0(0));
    s->flags |= 0xC;
    s->flags |= 0x400;
    s->flags |= 0x40;
    s->flags |= 0x800000;
    s->f50 = 30.0f;
    return s;
}
