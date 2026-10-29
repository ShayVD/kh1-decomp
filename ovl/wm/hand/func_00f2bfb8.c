/* wm.x func_00f2bfb8: matched by hand. */
#include "ovl.h"

/* wm.x func_00f2bfb8: matched by hand; func_001c0310 returns s32 (src/util/task.nostrict.c). */
#include "ovl.h"
extern s32 D_00F8C28C;
extern s32 D_00FBB800;
extern s32 D_00FBBA54;
void func_0011d768(s32);
s32 func_001c0310(s32, void (*)(s32), ...);
void func_00f2bf38(s32);

s32 func_00f2bfb8(void) {
    switch (D_00F8C28C) {
    case 2:
        if (D_00FBB800 != 0) {
            break;
        }
        func_0011d768(14);
        func_001c0310(-1, func_00f2bf38, D_00FBBA54 / 3);
        D_00FBB800 = 1;
        return 1;
    case 3:
        if (D_00FBB800 != 0) {
            break;
        }
        func_0011d768(14);
        func_001c0310(-1, func_00f2bf38, D_00FBBA54);
        D_00FBB800 = 1;
        return 1;
    }
    return 0;
}
