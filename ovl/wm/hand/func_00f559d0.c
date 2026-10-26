/* wm.x func_00f559d0: matched by hand. */
#include "ovl.h"

s32 func_00f4aa20(s32);
s32 func_00f4aaf8(s32);
void func_00f55670(void *);
void func_00f55758(void *, s32, s32, s32, s32);
void func_00f55880(void *, s32);
void func_00f55900(void *);
extern u8 *D_00F9B540;
extern u8 D_00F9B548[];
extern f32 D_00FA5CEC;

void func_00f559d0(void) {
    s32 cur;
    s32 next;
    s32 prev;
    s32 s0;
    s32 s1;

    func_00f55670(D_00F9B548);
    cur = *(s16 *)(D_00F9B540 + 0x84);
    next = func_00f4aa20(cur);
    prev = func_00f4aaf8(cur);
    s0 = D_00FA5CEC * 80.0f;
    s1 = D_00FA5CEC * 128.0f;
    func_00f55758(D_00F9B548, prev, -432, 352, s0);
    func_00f55758(D_00F9B548, cur, 0, 512, s1);
    func_00f55758(D_00F9B548, next, 432, 352, s0);
    func_00f55880(D_00F9B548, *(u16 *)(D_00F9B540 + 0x4C) - 1);
    func_00f55900(D_00F9B548);
}
