/* xs_genie.x func_00f20000: matched by hand. */
#include "ovl.h"

void func_00f200a0(s32);
void func_00f204e0(void);
extern s32 D_00F22E98;
extern s32 D_00F22EA0;
extern s32 D_00FC0F00;
s32 func_00f20000(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 0:
        if (arg1 == 0) {
            D_00F22E98 = (s32)&D_00F22EA0;
        } else {
            D_00F22E98 = arg1;
        }
        func_00f204e0();
        return 0;
    case 1:
        return D_00FC0F00;
    case 2:
        func_00f200a0(101);
        return 0;
    }
    return 0;
}
