/* wm.x func_00f356a0: matched by hand. */
#include "ovl.h"

#include "ovl.h"

typedef struct { f32 du; f32 dv; f32 pad[2]; } S;
typedef struct { S *src; s32 pad; f32 uv[4][2]; } O;
extern f32 D_002BBDFC;
extern O *D_00FCE040[192];

void func_00f356a0(void) {
    s32 i, j;
    S *s;
    f32 dt;
    for (i = 0; i < 192; i++) {
        if (D_00FCE040[i] != 0) {
            s = D_00FCE040[i]->src;
            dt = D_002BBDFC;
            for (j = 0; j < 4; j++) {
                D_00FCE040[i]->uv[j][0] += s[j].du * dt;
                D_00FCE040[i]->uv[j][1] += s[j].dv * dt;
                if (D_00FCE040[i]->uv[j][0] > 1.0f) D_00FCE040[i]->uv[j][0] -= 1.0f;
                if (D_00FCE040[i]->uv[j][1] > 1.0f) D_00FCE040[i]->uv[j][1] -= 1.0f;
                if (D_00FCE040[i]->uv[j][0] < 0.0f) D_00FCE040[i]->uv[j][0] += 1.0f;
                if (D_00FCE040[i]->uv[j][1] < 0.0f) D_00FCE040[i]->uv[j][1] += 1.0f;
            }
        }
    }
}
