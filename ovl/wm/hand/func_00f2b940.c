/* wm.x func_00f2b940: matched by hand. */
#include "ovl.h"

void func_001efaf0(void);
void func_001efb18(s32, s32);
s32 func_001efbb8(s32);
s32 func_00f2b808(void);
extern s32 D_00FBB574;
extern s32 D_00FBB578;
s32 func_00f2b940(void) {
    s32 r = func_00f2b808();
    if (r < 0) {
        return 0;
    }
    r += 33;
    func_001efb18(D_00FBB574, D_00FBB578);
    r = func_001efbb8(r);
    func_001efaf0();
    return r;
}
