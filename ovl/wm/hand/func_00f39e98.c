/* wm.x func_00f39e98: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u8 kind; u8 pad2[3]; } I;
typedef struct { s32 n; I items[1]; } L;
typedef struct { u8 pad[0xF4]; L *list; } A;
s32 func_00f39e98(A *arg0) {
    s32 best = -1;
    L *l = arg0->list;
    s32 i;
    if (l != 0) {
        I *p = (I *)((u8 *)l + 4);
        for (i = 0; i < l->n; i++) {
            s32 k = p->kind - 1;
            p++;
            if (k < 9) {
                if (k >= 4) {
                    best = (best < k) ? k : best;
                }
            }
        }
    }
    return best;
}
