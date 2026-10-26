/* dkmovie.x func_00f20320: matched by hand. */
#include "ovl.h"

void func_00114820(void);
void func_00100ae0(void);
extern s32 D_002BBE04;
extern s32 D_002BBE14;
extern s32 D_002BBE18;
extern s32 D_002C5958;
extern s32 D_0035C6F0;
extern s32 (*D_00F2847C)(void);
void func_00f20320(void) {
    func_00114820();
    D_002BBE04 = 2;
    D_002BBE14 = 1;
    D_002BBE18 = 1;
    func_00100ae0();
    D_0035C6F0 = 0;
    D_002C5958 |= 0x40;
    D_00F2847C();
}
