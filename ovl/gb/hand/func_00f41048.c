/* gb.x func_00f41048: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[20]; s32 v; u8 pad2[72 - 24]; } E41;
extern E41 *D_00F70268;

s32 func_00f41048(s32 i) {
    if (i < 0) return 0;
    return D_00F70268[i].v != 0;
}
