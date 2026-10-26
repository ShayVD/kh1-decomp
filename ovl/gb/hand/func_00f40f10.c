/* gb.x func_00f40f10: matched by hand. */
#include "ovl.h"

void func_0011cbe0(s32, s32, s32, void (*)(void));
void func_001bfac8(void);
void func_00f40ec8(void);
extern s32 D_00F82990;

void func_00f40f10(s32 arg0, s32 arg1) {
    D_00F82990 = 0;
    func_0011cbe0(0, arg1, arg0, func_00f40ec8);
    while (D_00F82990 == 0) {
        func_001bfac8();
    }
    func_001bfac8();
}
