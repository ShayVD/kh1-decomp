/* gb.x func_00f4d800: matched by hand. */
#include "ovl.h"

void func_0024e468(s32);
extern s32 D_00F82A04, D_00F82A08, D_00F82A0C, D_00F82A10, D_00F82A14, D_00F82A18, D_00F82A1C, D_00F82A20;

void func_00f4d800(void) {
    while (1) {
        D_00F82A04 = D_00F82A0C;
        D_00F82A08 = D_00F82A10;
        D_00F82A18 = D_00F82A14;
        D_00F82A20 = D_00F82A1C;
        func_0024e468(1);
    }
}
