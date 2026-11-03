/* gb.x func_00f258d0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x7E]; s16 h; u8 pad2[0x94 - 0x80]; void * n; } S258;
u8 *func_001bb658(s32);
extern S258 *D_00F56DC0;
s32 func_00f258d0(s32 id) {
    S258 *p = D_00F56DC0;
    if (!p->n || (s32)p->n < 0 || (s32)p->n >= 3) {
        return func_001bb658(id)[0x11];
    }
    return p->h;
}
