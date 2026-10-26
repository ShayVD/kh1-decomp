/* xs_dumbo.x func_00f21070: matched by hand. */
#include "ovl.h"

typedef void (*Fn)();
void func_0014f658(void *, s32);
void func_0014f830(s32, s32, Fn, Fn, Fn, Fn, Fn, Fn, s32);
extern f32 D_002C58A0[];
void func_0014f778();
void func_0014f828();
void func_00f209d0();
void func_00f20a60();
void func_00f20aa8();
void func_00f20d88();
void func_00f20e38();
void func_00f21010();
typedef struct { u8 pad[0x3C0]; OvlVec v; } Obj;
void func_00f21070(Obj *arg0) {
    func_0014f830(0x21, 6, func_00f209d0, func_00f20a60, func_00f20d88, func_00f20e38, func_0014f828, func_00f20aa8, 0);
    func_0014f830(0x22, 1, func_00f21010, 0, 0, func_0014f778, func_0014f828, 0, 0);
    func_0014f658(arg0, 0x21);
    PlatVu0CopyVector(arg0->v, D_002C58A0);
}
