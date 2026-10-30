/* wm.x func_00f25660: matched by hand. */
#include "ovl.h"

/* wm.x func_00f25660: matched by hand; func_001c01b0 returns s32 (src/util/task.nostrict.c). */
#include "ovl.h"
extern s32 D_00FBB330;
extern s32 D_00FBB33C;
extern s32 D_00FBB340;
extern s32 D_00F878E0;
extern s32 D_00F878E4;
extern s32 D_00F878E8;
extern s32 D_00FBAA70;
extern s32 D_00FBAA74;
extern s32 D_00FBAA94;
s32 func_001c01b0(s32, void (*)(), ...);
void func_00f25918();
void func_00f28258();
void func_00f25588();

void func_00f25660(void) {
    s32 one = 1;
    D_00FBB33C = 0;
    D_00FBB340 = 128;
    D_00F878E0 = 8;
    D_00F878E4 = one;
    D_00F878E8 = 0;
    if ((u32)(D_00FBB330 - 17) >= 2) {
        D_00FBAA70 = -512;
        D_00FBAA74 = 0;
        func_001c01b0(-1, func_00f25918);
        func_001c01b0(-1, func_00f28258);
        D_00FBAA94 = one;
    } else {
        D_00FBAA70 = 0;
        D_00FBAA74 = 0;
        func_001c01b0(-1, func_00f25588);
        D_00FBAA94 = one;
    }
}
