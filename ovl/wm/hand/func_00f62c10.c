/* wm.x func_00f62c10: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u8 a; u8 b; u8 pad2[0x3A]; } E62;
typedef struct { u8 pad[0x10]; s32 n; E62 *e; } H62;

E62 *func_00f62c10(s32 arg0, s32 arg1, H62 *h) {
    s32 i;
    E62 *e = h->e;

    for (i = 0; i < h->n; i++, e++) {
        if (e->b == arg0 && e->a == arg1) {
            return e;
        }
    }
    return NULL;
}
