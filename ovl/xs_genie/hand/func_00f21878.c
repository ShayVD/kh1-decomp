/* xs_genie.x func_00f21878: matched by hand. */
#include "ovl.h"

typedef struct { s32 pad[5]; s32 f14; s32 pad2[2]; } It;
extern s32 D_00FC1DD0;
void func_0023c5a8(s32);
s32 func_00f215f8(void *, It *);
void func_00f21878(void) {
    It it;
    while (func_00f215f8(&D_00FC1DD0, &it)) {
        func_0023c5a8(it.f14);
    }
}
