/* gb.x func_00f3fda0: matched by hand. */
#include "ovl.h"

void func_0011ef10(s32, void (*)());
void func_001be820(void *, s32);
extern u8 D_00F6CA68[];
extern u8 D_00F6D268[];
extern s32 D_00F82880;
extern s32 D_00F82884;
void func_00f3fc68();
void func_00f3fda0(void) {
    func_001be820(D_00F6CA68, 0x800);
    func_001be820(D_00F6D268, 0x3000);
    D_00F82880 = 0;
    D_00F82884 = 1;
    func_0011ef10(0x2C01A, func_00f3fc68);
}
