#include "common.h"

/* func_00104ae0 (session 7, w6): the face pointer is built from a local
 * copy of the table base (`base` first, so its lui is scheduled first),
 * and the two counts are separate returns (li v0,3 hoisted). */
#include "data/pieces/D_002A6238.h"
typedef Ent20_2a6238 Face;
#include "data/types/text_00100000_s7_w6.h"
#include "data/pieces/D_002A624C.h"

s32 func_00104ae0(s32 i, f32 *o) {
    u32 base = (u32)D_002A6238;
    Face *f = (Face *)(i * 20 + base);
    s32 a = f->v[0], b = f->v[1], c = f->v[2], d = f->v[3];
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
    if ((u32)(d + 2) < 2) return 3;
    o[12] = D_002A624C[d].x;
    o[13] = D_002A624C[d].y;
    o[14] = D_002A624C[d].z;
    o[15] = 1.0f;
    return 4;
}
