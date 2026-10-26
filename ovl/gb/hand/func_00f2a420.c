/* gb.x func_00f2a420: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f2b9b8(void *, s32, s32);
extern s32 D_00F56D98;
extern s32 D_00F56DC4;
extern u8 D_00F56DC8[];

void func_00f2a420(void) {
    while (1) {
        if (D_00F56D98 == 0) {
            func_00f2b9b8(D_00F56DC8, D_00F56DC4, 1);
        }
        func_001bfac8();
    }
}
