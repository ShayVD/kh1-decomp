/* wm.x func_00f35188: matched by hand. */
#include "ovl.h"

void func_0011d140(s32, s32);
s32 func_001623e0(s32);
void func_001655e0(f32 (*)[4], s32, f32, s32);
s32 func_00167698(s32);
void func_001bfac8(void);
void func_00f2c310(s32);
extern f32 D_00F8C228;
extern s32 D_00F8C22C;
extern s32 D_00F8C230;
extern s32 D_00F8C234;
extern s32 D_00F8C238;
extern s32 D_00FCD5F0[8];
extern s32 D_00FCD610[8];
extern s32 *D_00FCD634;
extern s32 D_00FCD638;

void func_00f35188(void) {
    f32 m0[4][4];
    f32 m1[4][4];
    f32 r;

    sceVu0UnitMatrix(m0);
    sceVu0UnitMatrix(m1);
    sceVu0RotMatrixX(m1, m1, 3.1415927f);
    D_00F8C228 = 0.0f;
    for (;;) {
        if (D_00F8C228 >= 0.0f && D_00F8C228 <= 0.1f) {
            switch (D_00F8C22C) {
            case 3:
                func_0011d140(0xE2D0, 0);
                break;
            case 4:
                func_0011d140(0xE2D3, 0);
                break;
            }
        }
        func_001655e0(m1, D_00FCD638, D_00F8C228, D_00FCD634[D_00F8C22C]);
        func_00f2c310(func_001623e0(D_00FCD638));
        if (D_00F8C230 >= 0) {
            r = func_00167698(D_00FCD634[D_00F8C22C]);
            D_00F8C228 += 2.0f;
            if (r < D_00F8C228) {
                if (D_00F8C238 == 0) {
                    D_00F8C228 -= r;
                    if (D_00F8C230 > 0 && --D_00F8C230 == 0) {
                        D_00F8C228 = 0.0f;
                        D_00F8C22C = 0;
                        D_00F8C230 = 0;
                    }
                } else {
                    D_00F8C228 = 0.0f;
                    D_00F8C22C = D_00FCD5F0[D_00F8C234];
                    D_00F8C230 = D_00FCD610[D_00F8C234];
                    D_00F8C238--;
                    D_00F8C234 = (D_00F8C234 + 1) & 7;
                }
            }
        }
        func_001bfac8();
    }
}
