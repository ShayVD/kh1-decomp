/* wm.x func_00f458f8: matched by hand. */
#include "ovl.h"

void func_001c0310(s32, void (*)(void), ...);
extern s32 D_00F86480;
extern s32 D_00F9A540;
void func_00f456b0(void);

void func_00f458f8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg4 == 0) {
        func_001c0310(-1, func_00f456b0, arg0, arg1, arg2, arg3, &D_00F86480);
    } else {
        func_001c0310(-1, func_00f456b0, arg0, arg1, arg2, arg3, &D_00F9A540);
    }
}
