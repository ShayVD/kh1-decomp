/* gb.x func_00f40180: matched by hand. */
#include "ovl.h"

s32 func_00f3e9c8(s32);
u64 *func_00f3ec20(u64 *, s32, s32, s32);
u64 *func_00f3fc38(u64 *);

u64 *func_00f40180(s32 arg0, s32 arg1, u64 *p) {
    s32 i;
    for (i = 0; i < func_00f3e9c8(arg1); i++) { p = func_00f3ec20(p, arg0, arg1, i); arg0 = -1; }
    return func_00f3fc38(p);
}
