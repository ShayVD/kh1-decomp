/* wm.x func_00f62ba8: the twin of gb.x func_00f3bab0 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { u8 b; u8 pad[19]; } E20;
typedef struct { u8 pad[0x1c]; E20 *e; } H;
u8 func_00f62ba8(s32 arg0, H *arg1) {
    E20 *e = &arg1->e[arg0];
    return e->b;
}
