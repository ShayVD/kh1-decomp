/* gb.x func_00f3bab0: matched by hand. */
#include "ovl.h"

typedef struct { u8 b; u8 pad[19]; } E20;
typedef struct { u8 pad[0x1c]; E20 *e; } H;
u8 func_00f3bab0(s32 arg0, H *arg1) {
    E20 *e = &arg1->e[arg0];
    return e->b;
}
