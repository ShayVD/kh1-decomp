/* wm.x func_00f5a498: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f5d118(s32, s32, void *, s32, s32, void *, void *);
extern u8 *D_00F9B540;
extern u8 D_00F9B548[];
extern u8 D_0108D020[];

void func_00f5a498(void) {
    while (1) {
        func_00f5d118(1, 0x2F80, D_00F9B548, 0x6F0, 0x720, D_0108D020, D_00F9B540 + 0xA0);
        func_001bfac8();
    }
}
