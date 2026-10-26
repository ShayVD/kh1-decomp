/* xl_limit.x func_00f215b8: matched by hand. */
#include "ovl.h"

void func_0012cab8(void *);
s32 func_00148968(s32 *, s32, s32);
void func_00f21528(void);
extern s32 D_00F23208;
extern s32 D_00F23E10;
void func_00f215b8(s32 *arg0) {
    s32 *p;
    func_0012cab8(func_00f21528);
    *arg0 |= 0x01200080;
    p = &D_00F23E10;
    *p = func_00148968(arg0, D_00F23208, 1);
}
