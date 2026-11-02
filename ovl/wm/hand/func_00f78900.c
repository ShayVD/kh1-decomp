/* wm.x func_00f78900: matched by hand. */
#include "ovl.h"

void func_00120748(s32, s32, void (*)(void), s32);
void func_001bfac8(void);
void func_00f78828(void);
extern s32 D_0108F6B0;

s32 func_00f78900(s32 a0, s32 a1) {
    D_0108F6B0 = -1;
    func_00120748(a0, a1, func_00f78828, 0);
    {
        /* register pin: the first poll of D_0108F6B0 is read into v1 in the target */
        register s32 t KH1_REG("v1") = D_0108F6B0;
        if (t == -1) {
            do {
                func_001bfac8();
            } while (D_0108F6B0 == -1);
        }
    }
    return D_0108F6B0;
}
