/* xs_bambi.x func_00f20108: matched by hand (session 131b). */
#include "ovl.h"

extern s32 D_00F20904;
s32 func_00123488(s32);
void func_001247e8(s32);
void func_00137330(s32, s32, s32);
void func_00f20580(s32);
void func_00f20108(s32 arg0) {
    switch (arg0) {
    case 100:
        func_00137330(D_00F20904, 0, 2500);
        break;
    case 101:
        if (func_00123488(0x70001) != 0) {
            func_001247e8(D_00F20904);
        }
        break;
    }
    func_00f20580(arg0);
}
