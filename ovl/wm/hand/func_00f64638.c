/* wm.x func_00f64638: the twin of gb.x func_00f3d540 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { u8 pad[4]; s16 h; u8 pad2[14]; } E20;
typedef struct { u8 pad[0x10]; E20 *e; } H;
s32 func_00f64638(s32 arg0, H *arg1) {
    E20 *e = &arg1->e[arg0];
    return e->h + 1;
}
