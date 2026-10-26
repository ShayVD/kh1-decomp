/* gb.x func_00f26fb8: matched by hand. */
#include "ovl.h"

u64 *func_00f3fa80(s32);
void func_00f3fa98(u64 *);

u64 *func_00f26fb8(s32 arg0, s32 arg1, s32 arg2) {
    u64 *p;

    p = func_00f3fa80(arg0);
    p[1] = 0x18;
    p[0] = (u64)(arg1 << 4) | ((u64)(arg2 << 4) << 32);
    p += 2;
    func_00f3fa98(p);
    return p;
}
