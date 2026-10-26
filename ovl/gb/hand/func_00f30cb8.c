/* gb.x func_00f30cb8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x4C]; s16 a; u8 pad2[2]; s8 b; u8 pad3[0x31]; s16 c; s16 d; } W57;
void func_0011d768(s32);
s32 func_00f23a00(s32);
s32 func_00f23928(s32);
void func_00f2f688(s32);
void func_00f2eee8(s32);
s32 func_00f23ad8(s32);
s32 func_00f258d0(s32);
extern W57 *D_00F56DC0;

void func_00f30cb8(s32 arg0) {
    s32 v;
    s32 r;
    u16 n;

    func_0011d768(20);
    if (arg0 == 0) {
        v = func_00f23a00(D_00F56DC0->d);
    } else {
        v = func_00f23928(D_00F56DC0->d);
    }
    if (arg0 == 0) {
        func_00f2f688(v);
    } else {
        func_00f2eee8(v);
    }
    D_00F56DC0->d = v;
    r = func_00f23ad8((s16)v);
    v = (u16)(D_00F56DC0->a = r + 1);
    D_00F56DC0->c = r;
    D_00F56DC0->b = func_00f258d0(v - 1);
}
