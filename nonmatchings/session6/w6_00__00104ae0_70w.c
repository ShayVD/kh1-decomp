/* 70 words off (hand/nostrict; strict similar): regalloc/sched: orig keeps n in v0 (li v0,3/4), loads indices v[0..3] in order after base. Size equal. */
#include "common.h"
typedef struct { s16 v[4]; u8 pad[12]; } Face;
typedef struct { f32 x, y, z; } Vtx;
extern Face *D_002A6238;
extern Vtx *D_002A624C;
s32 func_00104ae0(s32 i, f32 *o) {
    Face *f = &D_002A6238[i];
    s32 a = f->v[0], b = f->v[1], c = f->v[2], d = f->v[3];
    s32 n = 3;
    o[0] = D_002A624C[a].x;
    o[1] = D_002A624C[a].y;
    o[2] = D_002A624C[a].z;
    o[3] = 1.0f;
    o[4] = D_002A624C[b].x;
    o[5] = D_002A624C[b].y;
    o[6] = D_002A624C[b].z;
    o[7] = 1.0f;
    o[8] = D_002A624C[c].x;
    o[9] = D_002A624C[c].y;
    o[10] = D_002A624C[c].z;
    o[11] = 1.0f;
    if ((u32)(d + 2) >= 2) {
        n = 4;
        o[12] = D_002A624C[d].x;
        o[13] = D_002A624C[d].y;
        o[14] = D_002A624C[d].z;
        o[15] = 1.0f;
    }
    return n;
}
