/* wm.x func_00f323b8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x50]; u8 sub[0x80]; f32 x; f32 y; f32 z; f32 w; } E323b8;
s32 func_00f32378(void *);
void func_00f324f0(OvlMtx);

s32 func_00f323b8(E323b8 *arg0, f32 *arg1, f32 *arg2) {
    OvlMtx m;
    f32 ax, ay, bx, by, dx, dy;
    if (func_00f32378(arg0->sub) == 0) {
        return 0;
    }
    func_00f324f0(m);
    ax = arg0->x / arg0->w;
    bx = m[3][0] / m[3][3];
    by = m[3][1] / m[3][3];
    ay = arg0->y / arg0->w;
    dx = ax - bx;
    if (-32.0f <= dx && dx <= 32.0f) {
        dy = ay - by;
        if (-32.0f <= dy && dy <= 32.0f) {
            *arg1 = (bx - ax) * (bx - ax) + (by - ay) * (by - ay);
            *arg2 = arg0->w;
            return 1;
        }
    }
    return 0;
}
