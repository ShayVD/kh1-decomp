/* wm.x func_00f30ae0: matched by hand. */
#include "ovl.h"

s32 func_001ba228(s32);
s32 func_001ba3d8(void);
s32 func_001ba3f0(s32);
s32 func_001ba458(s32);
s32 func_001bb720(void);
void func_00248ac8(s32, s32);
s32 func_00f2ab00(s32);
s32 func_00f2c0c0(s32);
void func_00f2c0d8(s32);
void func_00f30a20(void);
void func_00f30a80(void);
void func_00f30ab0(void);
extern s32 D_00F87310[];
extern s32 D_00F8C23C, D_00F8C280, D_00FBBA50, D_00FBBA54, D_00FBBA58, D_00FBBA5C, D_00FBBA60;

void func_00f30ae0(s32 arg0) {
    if (D_00F8C23C == 0 && arg0 > 0) {
        switch (arg0) {
        case 0xC9:
            D_00F87310[3]++;
            func_00248ac8(0, func_00f2ab00(2));
            func_00f30a20();
            return;
        case 0xC8:
            D_00F87310[2]++;
            func_00248ac8(0, func_00f2ab00(1));
            func_00f30a80();
            return;
        case 0xCA:
            D_00F87310[4]++;
            func_00248ac8(0, func_00f2ab00(3));
            func_00f30ab0();
            return;
        default:
            if (arg0 < func_001bb720()) {
                D_00F87310[6]++;
            } else if (arg0 < func_001ba3d8()) {
                D_00F87310[7]++;
            }
            if (arg0 < func_001ba3d8()) {
                if (func_001ba3f0(arg0) + func_00f2c0c0(arg0) >= func_001ba458(arg0)) {
                    func_00248ac8(1, func_001ba228(arg0));
                    break;
                }
            }
            func_00248ac8(0, func_001ba228(arg0));
            func_00f2c0d8(arg0);
            return;
        case 0xCB:
            D_00F87310[5]++;
            func_00248ac8(0, func_00f2ab00(4));
            if (D_00F8C280 != 0) D_00FBBA60 = 5;
            D_00FBBA50 = D_00FBBA54;
            D_00FBBA58 = D_00FBBA5C;
            break;
        }
    }
}
