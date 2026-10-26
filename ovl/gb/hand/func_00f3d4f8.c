/* gb.x func_00f3d4f8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[6]; s16 h; u8 pad2[12]; } E20;
typedef struct { u8 pad[0x10]; E20 *e; } H;
s16 func_00f3d4f8(s32 arg0, H *arg1) {
    E20 *e = &arg1->e[arg0];
    return e->h;
}
