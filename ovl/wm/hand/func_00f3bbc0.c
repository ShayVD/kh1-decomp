/* wm.x func_00f3bbc0: matched by hand. */
#include "ovl.h"

typedef struct { s32 fl; s32 a; s32 id; s32 h; s32 b; u8 pad2[0xC]; } St;
typedef struct { u8 pad[0xA0]; St st; } E;
extern E D_01067FE0[256];

void func_00f3bbc0(void) {
    s32 i;
    St *p;
    E *e = D_01067FE0;
    for (i = 0; i < 256; i++) {
        p = &e[i].st;
        p->fl = 0;
        p->b = 0;
        p->id = 0;
        p->h = 0;
    }
}
