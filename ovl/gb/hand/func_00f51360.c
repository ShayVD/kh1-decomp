/* gb.x func_00f51360: matched. D_00F829E0 = 8 is stored once, before D_00F82DAC = D_00F82DA8 = arg written as one chained assignment (from a decomp-permuter output, wgb round 54). */
#include "ovl.h"

extern u8 D_00F713B0[];
extern s32 D_00F82DB8;
extern s32 D_00F829F0;
extern s32 D_00F829E0;
extern s32 D_00F82DA8;
extern s32 D_00F82DAC;
extern s32 D_00F82A98;
extern s32 D_00F829E8;
extern s32 D_00F82DB4;
extern s32 D_00F82DB0;
extern s32 D_00F829EC;
s32 func_001f31a8(void *, s32);
void func_0024e468(s32);

s32 func_00f51360(s32 arg) {
    D_00F829EC = 0;
    D_00F829E0 = 8;
    D_00F82DAC = D_00F82DA8 = arg;
    D_00F829F0 = 224;
    D_00F82A98 = 1;
    D_00F829E8 = 1;
    D_00F82DB4 = 0;
    D_00F82DB0 = 0;
    D_00F82DB8 = -8;
    func_001f31a8(D_00F713B0, 1);
    while (D_00F829EC != 1) {
        func_0024e468(1);
    }
    D_00F829E0 = 16;
    return D_00F82DAC;
}
