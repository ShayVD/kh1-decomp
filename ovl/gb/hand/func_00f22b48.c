/* gb.x func_00f22b48: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_0010a0d8(void);
void func_0010a320(void);
void func_001bfcd8(void);
void func_00f20330(void);
s32 func_001c00e8(s32, void (*)(void), kh1_u128);
extern s32 D_00F74200[];
extern s32 D_00F61834;
extern void (*D_00F707F0)(void);
void func_00f22b48(s32 a) {
    D_00F74200[0] = 1;
    if (D_00F61834) {
        D_00F707F0();
        while (D_00F61834) func_001bfac8();
    }
    if (!a) {
        func_0010a0d8();
        func_0010a320();
    }
    func_001bfcd8();
    func_001c00e8(1, func_00f20330, KH1_Q(0));
}
