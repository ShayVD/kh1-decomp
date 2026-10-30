/* wm.x func_00f78458: matched, port.py of gb func_00f51360. D_00F829E0 = 8 is stored once, before D_00F82DAC = D_00F82DA8 = arg written as one chained assignment (from a decomp-permuter output, wgb round 54). */
#include "ovl.h"

extern u8 D_00FB5B30[];
extern s32 D_0108F578;
extern s32 D_0108F1B0;
extern s32 D_0108F1A0;
extern s32 D_0108F568;
extern s32 D_0108F56C;
extern s32 D_0108F258;
extern s32 D_0108F1A8;
extern s32 D_0108F574;
extern s32 D_0108F570;
extern s32 D_0108F1AC;
s32 func_001f31a8(void *, s32);
void func_0024e468(s32);

s32 func_00f78458(s32 arg) {
    D_0108F1AC = 0;
    D_0108F1A0 = 8;
    D_0108F56C = D_0108F568 = arg;
    D_0108F1B0 = 224;
    D_0108F258 = 1;
    D_0108F1A8 = 1;
    D_0108F574 = 0;
    D_0108F570 = 0;
    D_0108F578 = -8;
    func_001f31a8(D_00FB5B30, 1);
    while (D_0108F1AC != 1) {
        func_0024e468(1);
    }
    D_0108F1A0 = 16;
    return D_0108F56C;
}
