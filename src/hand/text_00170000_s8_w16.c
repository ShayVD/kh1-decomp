#include "common.h"
#include "data/pieces/D_00362438.h"
typedef Path_362438 Path;

f32 func_0017b668(s32 start, s32 end, f32 t, f32 te) {
    Path *p = D_00362438;
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
        if ((p->x18 & 1) && i == n - 1) break;
    }
    return sum;
}
