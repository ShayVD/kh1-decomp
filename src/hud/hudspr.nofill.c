/* The HUD's drawing helpers (docs/modules.md "Session 46"), nofill part:
 * func_00239a80 / func_00239d20 step a sprite and its optional second layer and
 * draw the first with its own colours (func_00239860 / func_00239b90 with
 * scale and all 0).  Both draw a1 twice when a2 is set: that is what the code
 * does. */
#include "common.h"

void func_00239860(s32, s32, s32, s32, f32, s32, s32, s32);
void func_00239b90(s32, s32, s32, s32, f32, s32, s32, s32);
void func_0024ae00(s32);
void func_0024af00(s32);

void func_00239a80(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, f32 f) {
    if (a0 != 0) {
        func_0024ae00(a1);
        if (a2 != 0) func_0024ae00(a2);
    }
    func_0024af00(a1);
    if (a2 != 0) func_0024af00(a2);
    func_00239860(a1, a3, a4, a5, f, 0, a6, 0);
    if (a2 != 0) func_00239860(a1, a3, a4, a5, f, 0, a6, 0);
}

void func_00239d20(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, f32 f) {
    if (a0 != 0) {
        func_0024ae00(a1);
        if (a2 != 0) func_0024ae00(a2);
    }
    func_0024af00(a1);
    if (a2 != 0) func_0024af00(a2);
    func_00239b90(a1, a3, a4, a5, f, 0, a6, 0);
    if (a2 != 0) func_00239b90(a1, a3, a4, a5, f, 0, a6, 0);
}

