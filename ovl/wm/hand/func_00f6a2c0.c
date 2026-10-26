/* wm.x func_00f6a2c0: the twin of gb.x func_00f431c8 (tools/ovl/twins.py). */
#include "ovl.h"

extern s8 D_00FB4EB8, D_00FB4EB9, D_00FB4EBB;
extern kh1_u128 *D_0108F248[];
typedef struct { void (*a)(void); void (*b)(void); } VT;
extern VT *D_00FB4F4C;
void func_00f699d8(s32);
void func_00f6a2c0(kh1_u128 **p) {
    s32 i;
    if (D_00FB4EB8) return;
    for (i = 0; i < 3; i++) D_0108F248[i] = p[i];
    D_00FB4F4C->a();
    for (i = 0; i < 3; i++) {
        if (D_0108F248[i] != p[i]) func_00f699d8(i);
        p[i] = D_0108F248[i];
    }
    if (D_00FB4EB9) {
        D_00FB4EB8 = D_00FB4EB9;
        D_00FB4EB9 = 0;
        D_00FB4EBB = 0;
        D_00FB4F4C->b();
        D_00FB4F4C = 0;
    }
}
