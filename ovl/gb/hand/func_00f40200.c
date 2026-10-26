/* gb.x func_00f40200: matched by hand. */
#include "ovl.h"

void func_00f3fe80(s32, u64 *);
s32 func_00f3e9c8(s32);
u64 *func_00f3ec20(u64 *, s32, s32, s32);
u64 *func_00f3fc38(u64 *);

u64 *func_00f40200(s32 arg0, s32 arg1, s32 arg2, u64 *p) {
    func_00f3fe80(arg0, p); { s32 f = arg1; s32 i; for (i = 0; i < func_00f3e9c8(arg2); i++) { p = func_00f3ec20(p, f, arg2, i); f = -1; } } return func_00f3fc38(p);
}
