/* gb.x func_00f36508: matched by hand. */
#include "ovl.h"

s32 func_00f36508(OvlVec *v, OvlMtx m, s32 flip) {
    s32 out[5][4] __attribute__((aligned(16)));
    s32 i;
    s32 r, ax, ay, bx, by;

    for (i = 0; i < 3; i++) {
        PlatVu0RotTransPers(out[i], m, v[i], 1);
    }
    ax = out[1][0] - out[0][0];
    ay = out[1][1] - out[0][1];
    bx = out[2][0] - out[0][0];
    by = out[2][1] - out[0][1];
    r = ax * by - bx * ay;
    if (flip) {
        r = -r;
    }
    return r;
}
