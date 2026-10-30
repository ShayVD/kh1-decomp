/* wm.x func_00f48aa8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x76]; s16 state; } W48aa8;
void func_0011d768(s32);
void func_00106880(s32);
s32 func_001c01b0(s32, void *, s32, s32);
void func_001bfac8(void);
void func_00f59820(s32, s32);
void func_00f5a4f0(s32);
void func_00f48870(s32, s32);
extern W48aa8 *D_00F9B540;

void func_00f48aa8(s32 arg0) {
    s32 old;
    s32 n;
    s32 i;

    if (arg0 == D_00F9B540->state) {
        return;
    }
    if (arg0 == 3) {
        D_00F9B540->state = arg0;
        func_0011d768(arg0);
        func_00106880(30);
        return;
    }
    func_001c01b0(-1, func_00f48870, arg0, 30);
    old = D_00F9B540->state;
    arg0 |= old << 8;
    if (arg0 == 1 || arg0 == 0x100) {
        func_0011d768(21);
    } else {
        func_0011d768(22);
    }
    func_001bfac8();
    switch (arg0) {
    case 0x100:
        for (i = 0; i < 30; i++) {
            func_00f59820(5, old * 15 - i / 2);
            func_001bfac8();
        }
        break;
    case 0x001:
        for (i = 0; i < 30; i++) {
            func_00f59820(5, old * 15 + i / 2);
            func_001bfac8();
        }
        break;
    case 0x002:
    case 0x102:
    case 0x200:
    case 0x201:
        func_00f5a4f0(arg0 & 0xFF);
        break;
    }
    n = arg0 & 0xFF;
    func_00f59820(5, n * 15);
    D_00F9B540->state = n;
}
