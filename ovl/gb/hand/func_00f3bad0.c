/* gb.x func_00f3bad0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[5]; u8 id; u8 pad6[0x3A]; } E3bad0;
typedef struct { u8 pad[0x10]; s32 n; E3bad0 *e; } L3bad0;

E3bad0 *func_00f3bad0(s32 id, L3bad0 *l) {
    s32 i;
    E3bad0 *e = l->e;
    for (i = 0; i < l->n; i++, e++) {
        if (e->id == id) {
            return e;
        }
    }
    return 0;
}
