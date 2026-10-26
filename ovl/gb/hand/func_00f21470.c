/* gb.x func_00f21470: the twin of wm.x func_00f48568 (tools/ovl/twins.py). */
#include "ovl.h"

#include "common.h"

typedef struct {
    s32 unk0;
    s32 cnt;
    s32 max;
    s32 unkC;
    s32 cur[4];
    s32 start[4];
    s32 end[4];
    f32 rad[3];
    f32 w;
} Rot48568;

s32 func_00f21470(Rot48568 *r)
{
    s32 i;

    if (r->cnt == 0) {
        r->cnt = 1;
    }
    if (r->cnt > r->max) {
        return 0;
    }
    if (r->cnt == r->max) {
        for (i = 0; i < 4; i++) {
            r->cur[i] = r->end[i];
        }
    } else {
        for (i = 0; i < 3; i++) {
            r->cur[i] = (r->end[i] - r->start[i]) * r->cnt / r->max + r->start[i];
        }
    }
    for (i = 0; i < 3; i++) {
        if (r->cur[i] >= 2048) {
            r->cur[i] -= 4096;
        }
        if (r->cur[i] < -2048) {
            r->cur[i] += 4096;
        }
        r->rad[i] = (f32)r->cur[i] * 3.141592503f * (1.0f / 2048.0f);
    }
    r->w = 1.0f;
    r->cnt++;
    return 1;
}
