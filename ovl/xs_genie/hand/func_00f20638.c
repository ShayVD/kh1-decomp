/* xs_genie.x func_00f20638: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x10]; s8 *p; } Gn10;
extern Gn10 *D_00FC1728[7];
void func_00f20638(void) {
    s32 i;
    for (i = 0; i < 7; i++) {
        *D_00FC1728[i]->p = 1;
    }
}
