/* xs_tink.x func_00f20000: matched by hand. */
#include "ovl.h"

extern void *D_00F20D80;
extern s32 D_00F20E80;
void func_00148768(void *, s32, void *, s32, f32);
void func_00f200b0(s32);
void func_00f20170(void);
s32 func_00f20000(s32 arg0, void *arg1) {
    switch (arg0) {
    case 0:
        D_00F20D80 = arg1;
        func_00f20170();
        return 0;
    case 1:
        return D_00F20E80;
    case 2:
        func_00f200b0(101);
        return 0;
    case 4:
        func_00148768(D_00F20D80, 4, arg1, 0x8003, 0.0f);
        return 0;
    }
    return 0;
}
