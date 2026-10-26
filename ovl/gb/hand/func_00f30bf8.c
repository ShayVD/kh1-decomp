/* gb.x func_00f30bf8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x4C]; s16 a; u8 pad2[2]; s8 b; u8 pad3[0x31]; s16 c; s16 d; } W57;
void func_0011d768(s32);
void func_00f20248(s32);
void func_00f20290(s32);
void func_00f30640(void);
void func_00f2fe38(void);
s32 func_00f23d50(s32);
s32 func_00f23c70(s32);
s32 func_00f23bb0(s32);
s32 func_00f258d0(s32);
extern W57 *D_00F56DC0;

void func_00f30bf8(s32 arg0) {
    s32 v;

    func_0011d768(19);
    func_00f20248(11);
    if (arg0 == 0) {
        func_00f30640();
        D_00F56DC0->c = func_00f23d50(D_00F56DC0->c);
    } else {
        func_00f2fe38();
        D_00F56DC0->c = func_00f23c70(D_00F56DC0->c);
    }
    D_00F56DC0->d = func_00f23bb0(D_00F56DC0->c);
    v = (u16)(D_00F56DC0->a = (u16)D_00F56DC0->c + 1);
    D_00F56DC0->b = func_00f258d0(v - 1);
    func_00f20290(11);
}
