/* wm.x func_00f5ac08: the twin of gb.x func_00f33b10 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { u16 id; u16 f; u16 k; u16 flags; u8 pad[4]; } Kind;
typedef struct { u8 pad[0xA4]; u16 n; u8 padA6[0x6A]; Kind k[1]; } World;
extern World *D_00F9B540;

s32 func_00f5ac08(void) {
    s32 best = -1;
    s32 i;
    for (i = 0; i < D_00F9B540->n; i++) { s32 k = D_00F9B540->k[i].k - 1; if (((D_00F9B540->k[i].f >> 8) & 0xF) == 4) { if (k < 9) { if (k >= 4) { best = (best < k) ? k : best; } } } }
    return best;
}
