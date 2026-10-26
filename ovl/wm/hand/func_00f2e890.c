/* wm.x func_00f2e890: matched by hand. */
#include "ovl.h"

typedef struct { OvlVec a; OvlVec pos; } P;
extern P D_00FBB5D0[];
extern s32 D_00FCC3C4;
extern OvlVec D_00FCC3D0[];
extern s8 D_00FCC4D0[];

s32 func_00f2e890(s32 arg0) {
    f32 d[2];
    s32 found = 0;
    s32 best = -1;
    f32 bd = 0.0f;
    f32 dist;
    s32 i;
    for (i = 0; i < D_00FCC3C4; i++) {
        if (D_00FCC4D0[i] == 0) continue;
        d[0] = D_00FCC3D0[i][0] - D_00FBB5D0[arg0].pos[0];
        d[1] = D_00FCC3D0[i][1] - D_00FBB5D0[arg0].pos[1];
        dist = d[0] * d[0] + d[1] * d[1];
        if (found == 0 || dist < bd) {
            bd = dist;
            found = 1;
            best = i;
        }
    }
    return best;
}
