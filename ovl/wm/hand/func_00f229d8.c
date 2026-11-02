/* wm.x func_00f229d8: matched by hand. */
#include "ovl.h"

void func_001c01b0(s32, void (*)(void), s32);
s32 func_00f2b280(s32);
s32 func_00f2b2f8(s32);
s32 func_00f3f308(s32);
extern s32 D_00FB653C;
extern s32 D_00FBAA98;
void func_00f228b0(void);

void func_00f229d8(s32 arg0) {
    s32 i;
    s32 a;
    s32 b;
    D_00FBAA98 = -1;
    i = func_00f2b2f8(arg0);
    if (i < 0) {
        D_00FB653C = -1;
    } else {
        a = func_00f2b280(i);
        b = func_00f3f308(i);
        if (a == 0 && b == 0) {
            D_00FB653C = -1;
        } else {
            func_001c01b0(-1, func_00f228b0, i);
        }
    }
}
