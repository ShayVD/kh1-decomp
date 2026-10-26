/* wm.x func_00f30178: matched by hand. */
#include "ovl.h"

void func_00f30040(void);
void func_00f300a8(void);
extern s32 D_00F8C280;
extern s32 D_00F8C2D0;
extern s32 D_00FBBA60;

void func_00f30178(void) {
    if (D_00F8C280 != 0) {
        if (D_00FBBA60 <= 0 && D_00F8C2D0 >= 0) {
            func_00f30040();
        }
        if (D_00FBBA60 > 0 && D_00F8C2D0 < 0) {
            func_00f300a8();
        }
    }
}
