/* wm.x func_00f222a0: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; s32 b; s32 c; s32 d; } S222a0;
extern s32 D_00F873F0;
extern S222a0 D_00F878F0;
void func_00f21f00(void);
void func_00f670c8(s32);
void func_00f671d8(s32);

s32 func_00f222a0(void) {
    if (D_00F873F0 == 0) {
        D_00F878F0.a = 0;
        D_00F878F0.b = 0;
        D_00F878F0.c = 0;
        D_00F878F0.d = 0;
        return 4;
    }
    func_00f21f00();
    if (D_00F878F0.a != 0 && D_00F878F0.b != 0 && D_00F878F0.c != 0 && D_00F878F0.d != 0) {
        func_00f670c8(D_00F878F0.a);
        func_00f671d8(D_00F878F0.b);
        func_00f671d8(D_00F878F0.c);
        func_00f671d8(D_00F878F0.d);
    }
    D_00F878F0.a = 0;
    D_00F878F0.b = 0;
    D_00F878F0.c = 0;
    D_00F878F0.d = 0;
    return 0;
}
