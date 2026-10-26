/* dkmovie.x func_00f20230: matched by hand. */
#include "ovl.h"

extern s32 (*D_00F28484)(void);

/* the player's status (its table's +0x0C) */
s32 func_00f20230(void) {
    return D_00F28484();
}
