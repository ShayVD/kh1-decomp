/* gb.x func_00f50fb0: matched by hand. */
#include "ovl.h"

void func_0011d768(s32);
void func_001bfac8(void);
void func_00f43ca0(void);
s32 func_001be278(void);
void func_00f446d0(void);
extern s32 D_00F702D8;
extern s32 D_00F702DC;
extern s8 D_00F70739;
extern s8 D_00F7073A;
extern s32 D_00F829C4;
extern s32 D_00F82A94;
extern s32 D_00F82A98;
extern s32 D_00F82ABC;
extern s32 D_00F82AC0;
extern s32 D_00F82AC4;

void func_00f50fb0(void) {
    s32 b = D_00F702DC;
    s32 a = D_00F702D8;
    s32 v;

    func_0011d768(2);
    func_001bfac8();
    D_00F82A94 = 0;
    D_00F82A98 = 1;
    D_00F70739 = 0;
    D_00F7073A = 0;
    func_00f43ca0();
    v = func_001be278() + 1;
    D_00F702DC = v;
    D_00F702D8 = v;
    D_00F82ABC = 1;
    D_00F82AC4 = 1;
    D_00F82AC0 = 0;
    func_00f446d0();
    D_00F7073A = 1;
    D_00F829C4 = 0;
    while (D_00F70739 == 0) {
        func_001bfac8();
    }
    D_00F702DC = b;
    D_00F702D8 = a;
}
