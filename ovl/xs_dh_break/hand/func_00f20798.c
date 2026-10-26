/* xs_dh_break.x func_00f20798: matched by hand. */
#include "ovl.h"

typedef struct { f32 pos[8][4]; f32 u[4]; f32 v[4]; } Q;
void func_00f20798(Q *q, s32 i, f32 *uv) {
    q->pos[i][0] = uv[0] * 1500.0f - 750.0f;
    q->pos[i][1] = 7.5f;
    q->pos[i][2] = uv[1] * 1500.0f - 750.0f;
    q->pos[i][3] = 1.0f;
    q->u[i] = uv[0];
    q->v[i] = 1.0f - uv[1];
}
