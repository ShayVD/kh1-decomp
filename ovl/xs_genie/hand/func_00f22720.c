/* xs_genie.x func_00f22720: matched by hand. */
#include "ovl.h"

typedef struct { s32 used; s32 pad[4]; } Slot;
extern Slot D_00FC2E20[];
Slot *func_00f22720(void) {
    s32 i;
    Slot *s = D_00FC2E20;
    for (i = 0; i < 10; i++, s++) {
        if (s->used == 0) {
            s->used = 1;
            return s;
        }
    }
    return 0;
}
