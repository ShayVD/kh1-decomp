/* wm.x func_00f504f8: matched by hand. */
#include "ovl.h"

#include "ovl.h"

void func_00f504a8(void);
extern s32 D_00FA5B30;
extern s32 D_0108CD40;
void func_00f504f8(s32 arg0) {
    if (arg0 == 0) {
        func_00f504a8();
        D_00FA5B30 = 0;
    }
    D_0108CD40 = arg0;
    D_00FA5B30 = 1;
}
