/* wm.x func_00f2c3f8: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; s32 b; s32 c; s32 d; s32 mode; f32 f; s32 g; } G;
extern G D_00454A20;
extern s32 D_00F8C280, D_00F8C284;
extern s32 D_00FBBA50, D_00FBBA54, D_00FBBA58, D_00FBBA60;
extern f32 D_00FBBA64;

void func_00f2c3f8(void) {
    D_00454A20.d = D_00FBBA54;
    if (D_00FBBA54 < D_00FBBA50) D_00FBBA50 = D_00FBBA54;
    D_00454A20.b = (D_00FBBA50 >= 0) ? D_00FBBA50 : 0;
    if (D_00FBBA58 >= 0) {
        if (D_00FBBA58 % 10 != 0) D_00454A20.a = D_00FBBA58 / 10 + 1;
        else D_00454A20.a = D_00FBBA58 / 10;
    } else {
        D_00454A20.a = 0;
    }
    if (D_00FBBA60 >= 0) D_00454A20.g = D_00FBBA60;
    else D_00454A20.g = 0;
    D_00454A20.f = D_00FBBA64;
    if (D_00F8C280 != 0) {
        if (D_00F8C284 != 0) D_00454A20.mode = 3;
        else D_00454A20.mode = 2;
    } else {
        if (D_00F8C284 != 0) D_00454A20.mode = 1;
        else D_00454A20.mode = 0;
    }
}
