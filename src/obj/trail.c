/* The leader's trail, default flags (docs/modules.md "Session 52"):
 * func_00159c10.  The rest is in trail.nostrict.c.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "platform/math.h"
#include "data/bss_0054.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350D78.h"

/* func_00159c10 (from hand/text_00140000_s6_07.c). */
typedef struct { s32 x0; s32 idx; s32 x8; s32 xc; f32 k[32][4]; } D9c10;
extern D9c10 D_00551740;
void func_00159c10(f32 *out, f32 t) {
    s32 i, cur, nx;

    cur = D_00551740.idx;
    for (i = 0; i < 32; i++) {
        if (D_00551740.k[cur][3] == 0.0f) {
            PlatVu0CopyVector(out, D_00551740.k[cur]);
            return;
        }
        nx = (cur + 31) % 32;
        if (!(D_00551740.k[cur][3] < t)) {
            PlatVu0InterVector(out, D_00551740.k[nx], D_00551740.k[cur], t / D_00551740.k[cur][3]);
            return;
        }
        t -= D_00551740.k[cur][3];
        cur = nx;
    }
}

