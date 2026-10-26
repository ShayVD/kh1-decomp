/* wm.x func_00f5d568: matched by hand. */
#include "ovl.h"

u64 *func_00f5d568(f32 *v0, f32 *v1, u64 tag, f32 (*m)[4], u64 *p) {
    s32 *q;
    p[1] = 1;
    p[0] = tag;
    q = (s32 *)(p + 2);
    PlatVu0RotTransPers(q, m, v0, 0);
    q[3] = 16;
    q = (s32 *)(p + 4);
    PlatVu0RotTransPers(q, m, v1, 0);
    q[3] = 16;
    return p + 6;
}
