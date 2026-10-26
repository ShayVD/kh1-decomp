/* dktitle.x func_00f24a88: matched by hand. */
#include "ovl.h"

void func_0020be10(s32);
s32 func_00f24a58(void);
void func_0011d768(s32);
void func_0024e468(s32);
extern s32 D_00F2C89C;
extern s32 D_00F2C894;

void func_00f24a88(s32 arg0) {
    D_00F2C89C = arg0;
    func_0020be10(0x10);
    func_0024e468(1);
    while (!(func_00f24a58() & 0x6000)) {
        func_0024e468(1);
    }
    if (arg0 == 8 || func_00f24a58() == 0x2000) {
        func_0011d768(2);
    } else {
        func_0011d768(3);
    }
    D_00F2C894 = 0;
    while (1) {
        func_0024e468(1);
    }
}
