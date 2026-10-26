/* wm.x func_00f65ac8: the twin of gb.x func_00f3e9d0 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { u8 pad[12]; s32 w; u8 pad2[12]; } E28;
typedef struct { u8 pad[0xc]; E28 *e; } H;
s32 func_00f65ac8(H *arg0, s32 arg1) {
    E28 *e = &arg0->e[arg1];
    return e->w;
}
