/* wm.x func_00f57db0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x4C]; s16 a; u8 pad2[2]; s8 b; u8 pad3[0x31]; s16 c; s16 d; } W57;
void func_0011d768(s32);
s32 func_00f4aaf8(s32);
s32 func_00f4aa20(s32);
void func_00f56780(s32);
void func_00f55fe0(s32);
s32 func_00f4abd0(s32);
s32 func_00f4c9c8(s32);
extern W57 *D_00F9B540;

void func_00f57db0(s32 arg0) {
    s32 v;
    s32 r;
    u16 n;

    func_0011d768(20);
    if (arg0 == 0) {
        v = func_00f4aaf8(D_00F9B540->d);
    } else {
        v = func_00f4aa20(D_00F9B540->d);
    }
    if (arg0 == 0) {
        func_00f56780(v);
    } else {
        func_00f55fe0(v);
    }
    D_00F9B540->d = v;
    r = func_00f4abd0((s16)v);
    v = (u16)(D_00F9B540->a = r + 1);
    D_00F9B540->c = r;
    D_00F9B540->b = func_00f4c9c8(v - 1);
}
