/* wm.x func_00f22778: matched by hand. */
#include "ovl.h"

typedef struct { s8 c[10]; } F22778;
extern F22778 D_00FB6630;
extern char D_00FB6640[];
extern char D_00FB6650[];
extern char D_00FB6660[];
void func_001bef40(char *, void *, ...);
s32 func_001bb7c8(char *, s32);
void func_00f64b88(s32);
s32 func_00f64c10(s32);
s32 func_00f64c38(s32, s32);
void func_00f65a68(s32);

s32 func_00f22778(s32 arg0, s32 arg1, s32 arg2) {
    F22778 fmt = D_00FB6630;
    char buf[128];
    s32 i;
    func_001bef40(buf, &fmt, D_00FB6640);
    if (func_001bb7c8(buf, arg0) == 0) {
        return 0;
    }
    func_00f64b88(arg0);
    func_001bef40(buf, &fmt, D_00FB6650);
    if (func_001bb7c8(buf, arg1) == 0) {
        return 0;
    }
    func_00f64b88(arg1);
    for (i = 0; i < func_00f64c10(arg1); i++) {
        func_00f65a68(func_00f64c38(i, arg1));
    }
    func_001bef40(buf, &fmt, D_00FB6660);
    if (func_001bb7c8(buf, arg2) == 0) {
        return 0;
    }
    func_00f65a68(arg2);
    return 1;
}
