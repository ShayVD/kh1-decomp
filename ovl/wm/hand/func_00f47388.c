/* wm.x func_00f47388: matched by hand. */
#include "ovl.h"

extern s32 D_010809B8[];
s32 func_001c00e8(s32 prio, void *fn, kh1_u128 q);
void func_00f49718(void);
void func_00f55bf8(void);
void func_00f51518(void);
void func_00f47388(s32 n) {
    s32 r;
    switch (n) {
    case 10:
        r = func_001c00e8(n, func_00f49718, 0);
        break;
    case 11:
        r = func_001c00e8(n, func_00f55bf8, 0);
        break;
    case 12:
        r = func_001c00e8(n, func_00f51518, 0);
        break;
    default:
        return;
    }
    D_010809B8[n] = r;
}
