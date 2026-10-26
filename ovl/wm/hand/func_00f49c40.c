/* wm.x func_00f49c40: the twin of gb.x func_00f22b48 (tools/ovl/twins.py). */
#include "ovl.h"

void func_001bfac8(void);
void func_0010a0d8(void);
void func_0010a320(void);
void func_001bfcd8(void);
void func_00f47428(void);
s32 func_001c00e8(s32, void (*)(void), kh1_u128);
extern s32 D_010809B8[];
extern s32 D_00FA5FB4;
extern void (*D_00FB4F70)(void);
void func_00f49c40(s32 a) {
    D_010809B8[0] = 1;
    if (D_00FA5FB4) {
        D_00FB4F70();
        while (D_00FA5FB4) func_001bfac8();
    }
    if (!a) {
        func_0010a0d8();
        func_0010a320();
    }
    func_001bfcd8();
    func_001c00e8(1, func_00f47428, KH1_Q(0));
}
