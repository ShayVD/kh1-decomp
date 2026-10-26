/* wm.x func_00f68cb0: matched by hand. */
#include "ovl.h"

void func_00206130(s32, s32, s32, s32, s32, s32);
void func_00f68cb0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s2;

    temp_s2 = (arg2 != 0) ? 0x80323296 : 0x80C2726E;
    if (arg1 < 2) {
        func_00206130(arg0, 0, 0, 0x200, 0x180, 0x6E000000);
    }
    if (arg1 == 2) {
        func_00206130(arg0, 0, 0, 0x200, 0x180, 0x5A000000);
    }
    func_00206130(arg0, 0, 0x80, 0x200, 0x7E, 0x60000000);
    func_00206130(arg0, 0, 0x80, 0x200, 2, temp_s2);
    func_00206130(arg0, 0, 0xFE, 0x200, 2, temp_s2);
}
