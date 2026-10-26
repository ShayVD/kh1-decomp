/* wm.x func_00f3b0b0: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; s32 id; u8 pad[0x108]; } S;
extern s32 D_00F9A530;
extern s32 D_00F9A538;
extern S D_00FDFFE0[2][0x400];

S *func_00f3b0b0(s32 arg0) {
    s32 i;
    S *p = D_00FDFFE0[D_00F9A530 ^ 1];
    for (i = 0; i < D_00F9A538; i++, p++) {
        if (p->id == arg0) return p;
    }
    return 0;
}
