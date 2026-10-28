/* gb.x func_00f50f08: matched by hand. */
#include "ovl.h"

s32 func_0011ef10(s32, void (*)());
void func_001bfac8(void);
s32 func_001f31a8(void *, s32);
void func_00f50dd8();
extern u8 D_00F71380[];
extern s32 D_00F829E8;
extern s32 D_00F829EC;
extern s32 D_00F829F0;
extern s32 D_00F82A98;

void func_00f50f08(s32 arg0) {
    func_001bfac8();
    D_00F82A98 = 1;
    D_00F829F0 = arg0;
    D_00F829E8 = 0;
    D_00F829EC = 0;
    func_0011ef10(0x2BFE9, func_00f50dd8);
    func_001f31a8(D_00F71380, 1);
    if (D_00F829EC != 2) {
        do {
            func_001bfac8();
        } while (D_00F829EC != 2);
    }
}
