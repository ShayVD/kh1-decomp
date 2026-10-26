/* dktitle.x func_00f26c98: matched by hand. */
#include "ovl.h"

extern s32 D_00F26E34;
extern void (**D_00F26E4C)(void);
s32 func_00f26c98(void) {
    if (D_00F26E4C != 0) {
        (*D_00F26E4C)();
    }
    return D_00F26E34;
}
