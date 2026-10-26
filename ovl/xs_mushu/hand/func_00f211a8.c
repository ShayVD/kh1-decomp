/* xs_mushu.x func_00f211a8: the twin of xs_bambi.x func_00f20730 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct {
    OvlVec *pts;
    s32 flags;
    s32 n;
    s32 cur;
    s32 start;
} BambiPath;
f32 func_00120bf8(f32 *);
s32 func_00f211a8(BambiPath *p, f32 *pos, s32 min, f32 *out, f32 r) {
    OvlVec d;
    s32 k;
    f32 dist;

    do {
        PlatVu0SubVector(d, p->pts[p->start], pos);
        if (p->flags & 1) {
            d[1] = 0.0f;
        }
        dist = func_00120bf8(d);
        k = (p->cur + p->n - p->start) % p->n;
        if (!(r < dist) && k >= min) {
            p->start = (p->start + 1) % p->n;
            continue;
        }
        break;
    } while (1);
    PlatVu0CopyVector(out, p->pts[p->start]);
    return k;
}
