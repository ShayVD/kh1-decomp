/* xl_limit.x func_00f20a20: matched by hand. */
#include "ovl.h"

typedef struct { s32 flags; u8 pad[0x3BC]; OvlVec v3c0; } LimObj;
void func_0012cab8(void (*)());
f32 func_00f209e0(LimObj *, f32);
extern OvlVec D_002C58B0;
void func_00f20988();
void func_00f20a20(LimObj *arg0) {
    arg0->flags |= 0x01200000;
    PlatVu0CopyVector(arg0->v3c0, D_002C58B0);
    func_00f209e0(arg0, 0.0f);
    func_0012cab8(func_00f20988);
}
