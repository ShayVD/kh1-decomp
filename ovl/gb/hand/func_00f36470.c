/* gb.x func_00f36470: matched by hand. */
#include "ovl.h"

u64 *func_00f36470(OvlVec a, OvlVec b, u64 tag, OvlMtx m, u64 *p) {
    s32 *q;
    p[1] = 1; p[0] = tag;
    q = (s32 *)(p + 2);
    PlatVu0RotTransPers(q, m, a, 0);
    q[3] = 16;
    q = (s32 *)(p + 4);
    PlatVu0RotTransPers(q, m, b, 0);
    q[3] = 16;
    return p + 6;
}
