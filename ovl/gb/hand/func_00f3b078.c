/* gb.x func_00f3b078: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f39eb0(s32, void *, void *);
extern u8 D_00F56DC8[];
extern u8 D_00379F28[];

void func_00f3b078(void) {
    while (1) {
        func_00f39eb0(0x2E40, D_00F56DC8, D_00379F28);
        func_001bfac8();
    }
}
