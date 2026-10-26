/* xs_dumbo.x func_00f21a48: matched by hand. */
#include "ovl.h"

typedef struct { OvlMtx m[10]; f32 ang[10]; s32 pad[2]; OvlVec in[100]; OvlVec out[100]; } Wk;
extern Wk D_00F2BB20;
extern f32 D_00F2BADC;
void func_00f21a48(f32 *arg0) {
    s32 i;
    Wk *w = &D_00F2BB20;
    PlatVu0CopyVector(w->m[0][3], arg0);
    for (i = 1; i < 10; i++) {
        PlatVu0ScaleVectorXYZ(w->m[i][3], w->m[i - 1][2], D_00F2BADC);
        PlatVu0AddVector(w->m[i][3], w->m[i][3], w->m[i - 1][3]);
        w->m[i][3][3] = 1.0f;
    }
}
