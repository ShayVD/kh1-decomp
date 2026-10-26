/* wm.x func_00f3b4e0: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; s32 id; u8 pad[0x108]; } S;
extern s32 D_00F9A534;
extern S *D_00FDFFD8;

S *func_00f3b4e0(s32 arg0) {
    s32 i;
    S *p;
    for (i = 0; i < D_00F9A534; i++) {
        p = &D_00FDFFD8[i];
        if (p->id == arg0) return p;
    }
    return 0;
}
