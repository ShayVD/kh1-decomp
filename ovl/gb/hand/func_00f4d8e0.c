/* gb.x func_00f4d8e0: matched by hand. */
#include "ovl.h"

void func_0020b968(void);
void func_0020bc48(s32, s32, s32);
void func_0020bda8(s32);
void func_0024e468(s32);
extern s32 D_00F829E0;
extern s32 D_00F829D4;
extern s32 D_00F829D8;

void func_00f4d8e0(void) {
    func_0020b968();
    func_0020bda8(16);
    while (1) {
        func_0020bc48(D_00F829E0, D_00F829D4, D_00F829D8);
        func_0024e468(1);
    }
}
