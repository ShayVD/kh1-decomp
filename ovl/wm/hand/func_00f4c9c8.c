/* wm.x func_00f4c9c8: the twin of gb.x func_00f258d0 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { u8 pad[0x7E]; s16 h; u8 pad2[0x94 - 0x80]; void * n; } S258;
u8 *func_001bb658(s32);
extern S258 *D_00F9B540;
s32 func_00f4c9c8(s32 arg0) {
    S258 *p = D_00F9B540;
    if (!p->n || (s32)p->n < 0 || (s32)p->n >= 3) {
        return func_001bb658(arg0)[0x11];
    }
    return p->h;
}
