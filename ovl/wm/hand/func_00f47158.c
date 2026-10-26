/* wm.x func_00f47158: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xA4]; u16 a4; } WmW;
extern WmW *D_00F9B540;
void func_00f47128(s32);
s32 func_00f47158(void) {
    WmW *w = D_00F9B540;
    if (w->a4 == 0) {
        func_00f47128(0xE4);
        return 1;
    }
    return 0;
}
