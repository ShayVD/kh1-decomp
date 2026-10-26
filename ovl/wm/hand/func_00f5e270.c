/* wm.x func_00f5e270: the twin of gb.x func_00f37178 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { f32 du; f32 dv; f32 pad[2]; } S;
typedef struct { S *src; s32 pad; f32 uv[4][2]; } O;
extern f32 D_002BBDFC;
extern O *D_0108DB90[192];

void func_00f5e270(void) {
    s32 i, j;
    S *s;
    f32 dt;
    for (i = 0; i < 192; i++) {
        if (D_0108DB90[i] != 0) {
            s = D_0108DB90[i]->src;
            dt = D_002BBDFC;
            for (j = 0; j < 4; j++) {
                D_0108DB90[i]->uv[j][0] += s[j].du * dt;
                D_0108DB90[i]->uv[j][1] += s[j].dv * dt;
                if (D_0108DB90[i]->uv[j][0] > 1.0f) D_0108DB90[i]->uv[j][0] -= 1.0f;
                if (D_0108DB90[i]->uv[j][1] > 1.0f) D_0108DB90[i]->uv[j][1] -= 1.0f;
                if (D_0108DB90[i]->uv[j][0] < 0.0f) D_0108DB90[i]->uv[j][0] += 1.0f;
                if (D_0108DB90[i]->uv[j][1] < 0.0f) D_0108DB90[i]->uv[j][1] += 1.0f;
            }
        }
    }
}
