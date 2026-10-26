/* wm.x func_00f39fd0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x30]; OvlVec v30; u8 pad40[0xA4]; u16 se; u8 pade6[0x22]; s32 id; } WmSnd;
void func_0011d3c8(s32, s32, s32);
s32 func_00f39ef0(s32);
extern s32 D_00F8C2F8;
void func_00f39fd0(WmSnd *arg0) {
    s32 id = arg0->id;
    if (id >= 0) {
        s32 se = arg0->se + 0x2000;
        func_0011d3c8(func_00f39ef0(id), se, 0x3C);
        D_00F8C2F8++;
    }
}
