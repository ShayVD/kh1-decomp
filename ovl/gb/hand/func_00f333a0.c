/* gb.x func_00f333a0: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f36020(s32, s32, void *, s32, s32, void *, void *);
extern u8 *D_00F56DC0;
extern u8 D_00F56DC8[];
extern u8 D_00F80860[];

void func_00f333a0(void) {
    while (1) {
        func_00f36020(1, 0x2F80, D_00F56DC8, 0x6F0, 0x720, D_00F80860, D_00F56DC0 + 0xA0);
        func_001bfac8();
    }
}
