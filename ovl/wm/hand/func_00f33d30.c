/* wm.x func_00f33d30: matched by hand. */
#include "ovl.h"

extern s32 D_00FCC560;
extern OvlVec D_00FCC570[];
extern s8 D_00FCC670[];

void func_00f33d30(f32 *arg0, s32 x, s32 y, s32 z, s32 w, s32 h, s32 d, s32 c) {
    OvlVec v;
    if (D_00FCC560 < 16) {
        f32 fw = w;
        v[0] = -arg0[0] - (x + fw * 0.5f) * 200.0f;
        v[1] = arg0[1] - (y + h * 0.5f) * 200.0f;
        v[3] = fw * 200.0f * 0.25f;
        v[2] = -arg0[2] - (z + d * 0.5f) * 200.0f;
        PlatVu0CopyVector(D_00FCC570[D_00FCC560], v);
        D_00FCC670[D_00FCC560] = c;
        D_00FCC560++;
    }
}
