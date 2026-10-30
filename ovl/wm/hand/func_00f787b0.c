/* wm.x func_00f787b0: matched by hand. */
#include "ovl.h"

typedef struct { f32 x0; f32 x4; f32 x8; f32 xC; f32 x10; } Bob;
extern Bob D_00FB5ED8[];

void func_00f787b0(s32 i) {
    f32 d;
    /* do { } while (0) (a macro in the original, likely) fixes the v0/v1 choice (permuter) */
    do {
        if (D_00FB5ED8[i].x8 >= 0.0f) {
            d = -D_00FB5ED8[i].xC;
        } else {
            d = D_00FB5ED8[i].xC;
        }
    } while (0);
    D_00FB5ED8[i].x4 += d;
    D_00FB5ED8[i].x8 += D_00FB5ED8[i].x4;
}
