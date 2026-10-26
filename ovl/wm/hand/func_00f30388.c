/* wm.x func_00f30388: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00242b68(s32);
void func_00f2d3d8(s32);
void func_00f2ce60(s32, s32, s32, s32);
void func_00f32ac8(void);
void func_00f33e48(s32, s32);
s32 func_001ba9d8(s32);
void func_00f300a8(void);
void func_00f30210(void);
void func_00f2d480(void);
void func_00241c60(s32, s32);
void func_00f2cf78(s32);
extern s32 D_00F8C120;
extern f32 D_00F8C148;
extern s32 D_00F8C1FC;
extern s32 D_00F8C280;
extern s32 D_00F8C2D0, D_00F8C2D4, D_00F8C2D8, D_00F8C2DC;
extern s32 D_00FBBA60;
extern s32 D_00FBDAF0;
extern s32 D_00FCC3C0;

void func_00f30388(s32 arg0) {
    s32 i;
    D_00F8C120 = D_00FBDAF0;
    for (i = 0; i < 10; i++) func_001bfac8();
    func_00242b68(4);
    for (i = 0; i < 30; i++) {
        D_00F8C148 = 1.0f + -(f32)i / 30.0f;
        func_001bfac8();
    }
    D_00FCC3C0 = arg0;
    D_00F8C148 = 0.0f;
    func_00f2d3d8(-1);
    func_00f2ce60(-1, -1, -1, -1);
    D_00F8C2D0 = -1;
    D_00F8C2D4 = -1;
    D_00F8C2D8 = -1;
    D_00F8C2DC = -1;
    func_00f32ac8();
    func_00f33e48(func_001ba9d8(D_00FBDAF0), 0);
    if (D_00F8C280 != 0 && D_00FBBA60 > 0) func_00f300a8();
    func_00f30210();
    for (i = 0; i < 10; i++) func_001bfac8();
    func_00f2d480();
    for (i = 0; i < 30; i++) {
        D_00F8C148 = 0.0f + (f32)i / 30.0f;
        func_001bfac8();
    }
    D_00F8C148 = 1.0f;
    func_00241c60(0, 4);
    for (i = 0; i < 10; i++) func_001bfac8();
    func_00f2cf78(arg0);
    D_00F8C1FC = 0;
}
