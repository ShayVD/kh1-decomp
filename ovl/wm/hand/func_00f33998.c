/* wm.x func_00f33998: matched by hand. */
#include "ovl.h"

void func_0011d1a8(s32, s32, s32);
void func_001c0078(s32);
void func_00242b68(s32);
void func_00f2ce60(s32, s32, s32, s32);
s32 func_00f2d360(s32, s32);
void func_00f2d3d8(s32);
void func_00f30040(void);
extern s32 D_00454A24, D_00F850F4, D_00F8C1FC, D_00F8C200;
void func_00f33998(void) {
    s32 i, j;
    if (D_00F850F4 == 0) return;
    func_00f30040();
    func_00f2d3d8(-1);
    func_00f2ce60(-1, -1, -1, -1);
    D_00F850F4 = 0;
    if (D_00F8C1FC != 0) {
        func_001c0078(D_00F8C200);
        D_00F8C1FC = 0;
    }
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 4; j++) {
            func_0011d1a8(func_00f2d360(j, i + 4), j + 0x1000, 4);
        }
    }
    D_00454A24 = 0;
    func_00242b68(4);
}
