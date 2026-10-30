/* gb.x func_00f51258: matched by hand. */
#include "ovl.h"

s32 func_0011ef10(s32, void (*)());
void func_001bfac8(void);
s32 func_001f31a8(void *, s32);
void func_0020bc48(s32, s32, s32);
void func_0020bda8(s32);
void func_0020be10(s32);
void func_00f50dd8();
extern u8 D_00F713B0[];
extern s32 D_00F829D4;
extern s32 D_00F829D8;
extern s32 D_00F829E8;
extern s32 D_00F829EC;
extern s32 D_00F829F0;
extern s32 D_00F82A98;
extern s32 D_00F82DA8;
extern s32 D_00F82DAC;
extern s32 D_00F82DB0;
extern s32 D_00F82DB4;
extern s32 D_00F82DB8;

s32 func_00f51258(s32 arg0, s32 arg1) {
    func_001bfac8();
    func_0020bda8(0x10);
    D_00F82DA8 = arg1;
    D_00F82A98 = 1;
    D_00F829E8 = 1;
    D_00F829F0 = arg0;
    D_00F82DAC = arg1;
    D_00F829EC = 0;
    func_0011ef10(0x2BFE9, func_00f50dd8);
    D_00F82DB4 = 1;
    D_00F82DB0 = 1;
    D_00F82DB8 = -8;
    func_001f31a8(D_00F713B0, 1);
    for (;;) {
        func_0020bc48(8, D_00F829D4, D_00F829D8);
        if (D_00F829EC == 2)
            break;
        func_001bfac8();
    }
    func_0020be10(0x10);
    return D_00F82DAC;
}
