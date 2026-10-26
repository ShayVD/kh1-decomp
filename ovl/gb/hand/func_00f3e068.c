/* gb.x func_00f3e068: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u16 id; s16 v; u8 pad2[4]; } E65;
typedef struct { u8 pad[8]; u32 n; E65 *e; } H65;

s32 func_00f3e068(H65 *h, s32 id) {
    s32 m = 0;
    u32 i;
    E65 *e;
    if (h == NULL) {
        return 0;
    }
    e = h->e;
    for (i = 0; i < h->n; i++, e++) {
        if (id < 0 || id == e->id) {
            if (m < e->v) {
                m = e->v;
            }
        }
    }
    return m;
}
