/* wm.x func_00f2c330: matched by hand. */
#include "ovl.h"

typedef struct { s32 x0; s32 x4; s32 x8; s32 xc; s32 mode; f32 f14; s32 x18; } GW2c330;
extern GW2c330 D_00454A20;
extern s32 D_00FBBA50;
extern s32 D_00FBBA54;
extern s32 D_00FBBA58;
extern s32 D_00FBBA5C;
extern s32 D_00FBBA60;
extern f32 D_00FBBA64;
extern s32 D_00F8C280;
extern s32 D_00F8C284;

void func_00f2c330(void) {
    GW2c330 *g = &D_00454A20;
    s32 u = D_00FBBA54;
    s32 t = D_00FBBA5C;
    g->xc = u;
    g->x8 = t / 10;
    D_00FBBA50 = u;
    D_00FBBA58 = t;
    g->x0 = t / 10;
    g->x4 = u;
    if (D_00F8C280 != 0) {
        if (D_00F8C284 != 0) {
            g->mode = 3;
        } else {
            g->mode = 2;
        }
    } else {
        if (D_00F8C284 != 0) {
            g->mode = 1;
        } else {
            g->mode = 0;
        }
    }
    D_00FBBA60 = 5;
    D_00FBBA64 = 1.0f;
    D_00454A20.x18 = 5;
    D_00454A20.f14 = 1.0f;
}
