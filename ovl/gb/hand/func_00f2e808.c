/* gb.x func_00f2e808: matched by hand. */
#include "ovl.h"

u64 *func_00f26500(u64 *);
u64 *func_00f26ca8(u64 *, s32, s32, s32, s32, s32, s32, s32, u64, u64);
u64 *func_00f26fb8(u64 *, s32, s32);
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3f9e8(u64 *);
void func_00f3fe80(s32, u64 *);

void func_00f2e808(u64 **pp) {
    u64 t = 0x620013200;
    *pp = func_00f3f9d0(*pp);
    *pp = func_00f26500(*pp);
    *pp = func_00f26fb8(*pp, 0, 0);
    *pp = func_00f26ca8(*pp, 49, 279, 0, 0, 0, 88, 84, 0x3F80000080808080, t);
    *pp = func_00f26fb8(*pp, 0x700, 0x740);
    func_00f3fe80(0x2B72, func_00f3f9e8(*pp));
}
