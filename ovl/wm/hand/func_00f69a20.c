/* wm.x func_00f69a20: matched by hand. */
#include "ovl.h"

void func_0010c170(void (*)(void), s32);
void func_001bfac8(void);
void func_00f69990(void);
extern s32 D_0108F260;
extern s32 D_0108F268;
extern s32 D_0108F26C;
extern s32 D_0108F270;
extern s32 D_0108F274;
extern s32 D_0108F278;

void func_00f69a20(void) {
    D_0108F260 = 0;
    func_0010c170(func_00f69990, 0);
    while (D_0108F260 == 0) {
        func_001bfac8();
    }
    D_0108F26C = 2;
    D_0108F270 = D_0108F268;
    D_0108F274 = D_0108F278;
}
