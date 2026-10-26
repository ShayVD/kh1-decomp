/* xs_mushu.x func_00f207a0: matched by hand. */
#include "ovl.h"

typedef struct { s32 used; s32 pad[11]; s32 f30; s32 pad2[3]; } Slot;
extern Slot D_00F21400[];
void func_00f207a0(void) {
    s32 i;
    Slot *s = D_00F21400;
    for (i = 0; i < 10; i++, s++) {
        if (s->used == 0) {
            s->f30 = 0;
            s->used = 1;
            break;
        }
    }
}
