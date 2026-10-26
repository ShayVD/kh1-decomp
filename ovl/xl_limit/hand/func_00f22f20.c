/* xl_limit.x func_00f22f20: the twin of xs_bambi.x func_00f20638 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct {
    OvlVec *pts;
    s32 flags;
    s32 n;
    s32 cur;
    s32 start;
} BambiPath;
f32 func_00120bf8(f32 *);
void func_00f22f20(BambiPath *p, f32 *pos, f32 r) {
    OvlVec d;
    s32 i;

    i = p->start;
    for (;;) {
        PlatVu0SubVector(d, p->pts[i], pos);
        if (p->flags & 1) {
            d[1] = 0.0f;
        }
        if (func_00120bf8(d) < r) {
            p->cur = i;
            return;
        }
        if (i == p->cur) {
            break;
        }
        i = (i + 1) % p->n;
    }
    i = (i + 1) % p->n;
    if (i != p->start) {
        p->cur = i;
        PlatVu0CopyVector(p->pts[i], pos);
    }
}
