/* wm.x func_00f78000: matched by hand. */
#include "ovl.h"

s32 func_0011ef10(s32, void (*)());
void func_001bfac8(void);
s32 func_001f31a8(void *, s32);
void func_00f77ed0();
extern u8 D_00FB5B00[];
extern s32 D_0108F1A8;
extern s32 D_0108F1AC;
extern s32 D_0108F1B0;
extern s32 D_0108F258;

void func_00f78000(s32 arg0) {
    func_001bfac8();
    D_0108F258 = 1;
    D_0108F1B0 = arg0;
    D_0108F1A8 = 0;
    D_0108F1AC = 0;
    func_0011ef10(0x2BFE9, func_00f77ed0);
    func_001f31a8(D_00FB5B00, 1);
    if (D_0108F1AC != 2) {
        do {
            func_001bfac8();
        } while (D_0108F1AC != 2);
    }
}
