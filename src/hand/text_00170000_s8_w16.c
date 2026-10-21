#include "common.h"
typedef struct { f32 x, y, z, len; } Seg;
typedef struct Path {
    s32 n; f32 x4; f32 x8; f32 xc; u8 pad10[4]; f32 x14; s32 flags; u8 pad1c[4]; Seg seg[1];
} Path;
#include "data/pieces/D_00362438.h"

f32 func_0017b668(s32 start, s32 end, f32 t, f32 te) {
    Path *p = ((Path *)D_00362438);
    s32 n = p->n;
    s32 i = start;
    f32 sum = 0.0f;
    s32 k;
    for (k = 0; k <= n; k++) {
        if (i == end && t < te) {
            sum += (p->seg + end)->len * (te - t);
            break;
        }
        sum += (p->seg + i)->len * (1.0f - t);
        t = 0.0f;
        i++;
        if (i >= n) i = 0;
        if ((p->flags & 1) && i == n - 1) break;
    }
    return sum;
}
