/* xs_tink.x func_00f200c8: matched by hand (session 131b). */
#include "ovl.h"

extern s32 D_00F20D88, D_00F20E80;
extern void *D_00F20D80;
s32 func_0013aa60(void);
s32 func_00147be0(void *);
void func_00f200b0(s32);
s32 func_00f200c8(void) {
    switch (D_00F20D88) {
    case 0:
        if (func_0013aa60() != 0) {
            func_00f200b0(100);
        }
        break;
    case 100:
        if (func_00147be0(D_00F20D80) == 0) {
            func_00f200b0(101);
        }
        break;
    case 101:
        D_00F20E80 = 0;
        return 4;
    }
    return 0;
}
