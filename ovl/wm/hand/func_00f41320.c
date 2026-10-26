/* wm.x func_00f41320: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f32ac8(void);
void func_00f3b490(void);
void func_00f3cac8(void);
void func_00f3f2d0(f32);
void func_00f404c8(s32, s32);
s32 func_00f40c98(void);
extern f32 D_00F850C8;
extern s32 D_00F850E0;
extern s32 D_00F9B1C4;
extern s32 D_00F9B1CC;

f32 func_00f41320(void) {
    OvlVec unused[2]; /* never used, but the original frame reserves 32 bytes for it */
    while (func_00f40c98() < 2) {
        func_00f404c8(D_00F850E0, 1);
        func_001bfac8();
    }
    D_00F9B1C4 = 0;
    D_00F9B1CC = 0;
    func_00f3b490();
    func_00f3cac8();
    while (func_00f40c98() >= 2) {
        func_001bfac8();
    }
    func_00f32ac8();
    D_00F9B1CC = 1;
    D_00F9B1C4 = 1;
    while (func_00f40c98() != 0) {
        func_00f404c8(D_00F850E0, 1);
        func_001bfac8();
    }
    func_00f3f2d0(1.0f);
    return D_00F850C8;
}
