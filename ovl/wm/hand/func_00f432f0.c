/* wm.x func_00f432f0: matched by hand. */
#include "ovl.h"

extern s32 D_00F9B1C8;
extern s32 D_00F9B1CC;
extern s32 D_010807E4;
extern s32 D_00F85094;
extern s32 D_00F9B1C4;
extern s32 D_00F87270;
extern s32 D_00F850E0;
extern s32 D_00F9B1C0;
void func_00f309f0(void);
void func_00f3c6c0(void);
f32 func_00f2c2d8(void);
void func_00f40b38(f32);
void func_00f31430(void);
void func_00f3e408(void);
void func_00f3b490(void);
void func_00f371d8(void);
void func_00f3be50(void);
void func_0024e640(s32, s32, void (*)(void), s32);
void func_00f32770(void);
void func_00f404c8(s32, s32);
void func_001bfac8(void);

void func_00f432f0(void) {
    for (;;) {
        if (D_00F9B1C8 != 0) {
            func_00f309f0();
        }
        if (D_00F9B1CC != 0) {
            func_00f3c6c0();
        }
        if (D_010807E4 == 0 && D_00F85094 == 0) {
            func_00f40b38(func_00f2c2d8());
        }
        if (D_00F9B1C8 != 0) {
            func_00f31430();
        }
        if (D_00F9B1CC != 0) {
            func_00f3e408();
            func_00f3b490();
            if (D_00F9B1C4 != 0) {
                func_00f371d8();
            }
            func_0024e640(D_00F87270, 4096, func_00f3be50, 0);
        }
        func_00f32770();
        if (D_00F9B1CC != 0) {
            func_00f404c8(D_00F850E0, 0);
        }
        {
            s32 *p = &D_00F9B1C0;
            if (*p >= 0) {
                (*p)++;
            }
        }
        func_001bfac8();
    }
}
