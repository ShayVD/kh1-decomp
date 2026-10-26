/* wm.x func_00f39f60: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x30]; OvlVec v30; u8 pad40[0xA4]; u16 se; u8 pade6[0x22]; s32 id; } WmSnd;
void func_0011d210(s32, s32, f32 *, s32);
s32 func_00f39e98(void);
s32 func_00f39ef0(s32);
extern s32 D_00F8C2F4;
void func_00f39f60(WmSnd *arg0) {
    s32 id = func_00f39e98();
    arg0->id = id;
    if (id >= 0) {
        s32 se = arg0->se + 0x2000;
        func_0011d210(func_00f39ef0(id), se, arg0->v30, 0);
        D_00F8C2F4++;
    }
}
