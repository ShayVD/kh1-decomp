/* wm.x func_00f21bc8: matched by hand. */
#include "ovl.h"

s32 func_00f20a98(void);
void func_00f2b7e0(void);
void func_00f44578(void);
void func_001bb7c8(void *, s32);
void func_00f2b870(s32);
s32 func_001c00e8(s32 prio, void *fn, kh1_u128 q);
void func_001bfc90(s32);
void func_00f23628(void);
extern s32 D_00F850A4;
extern s32 D_00F850CC;
extern s32 D_00F8706C;
extern u8 D_00FB6618[];

void func_00f21bc8(void) {
    func_00f20a98();
    D_00F850A4 = 0;
    func_00f2b7e0();
    func_00f44578();
    func_001bb7c8(D_00FB6618, D_00F8706C);
    func_00f2b870(D_00F8706C);
    func_001c00e8(2, func_00f23628, 0);
    func_001bfc90(3);
    D_00F850CC = 1;
}
