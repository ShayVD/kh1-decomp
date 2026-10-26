/* wm.x func_00f2d238: matched by hand. */
#include "ovl.h"

typedef struct { u16 f; u16 k; u8 pad[8]; } I;
typedef struct { s32 n; u8 pad[0x32]; I items[1]; } L;
extern L D_00F85240;
s32 func_00f2d238(void) {
    s32 best = -1;
    s32 i;
    for (i = 0; i < D_00F85240.n; i++) {
        s32 k = D_00F85240.items[i].k - 1;
        if (((D_00F85240.items[i].f >> 8) & 0xF) == 4) {
            if (k < 9) {
                if (k >= 4) {
                    best = (best < k) ? k : best;
                }
            }
        }
    }
    return best;
}
