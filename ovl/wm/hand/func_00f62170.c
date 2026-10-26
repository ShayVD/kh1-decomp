/* wm.x func_00f62170: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f60fa8(s32, void *, void *);
extern u8 D_00F9B548[];
extern u8 D_00379F28[];

void func_00f62170(void) {
    while (1) {
        func_00f60fa8(0x2E40, D_00F9B548, D_00379F28);
        func_001bfac8();
    }
}
