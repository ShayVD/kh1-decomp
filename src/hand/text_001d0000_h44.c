#include "common.h"
typedef struct {
    u8 pad0[0x30];
    f32 v30[4];
    u8 pad40[0x370 - 0x40];
    union { u64 x; struct { u32 lo; u32 p:12; u32 b44:1; u32 hi:19; } b; } f370;
} Obj;
typedef struct {
    s32 x0;
    Obj *obj;
    u8 pad8[0x2c - 8];
    f32 f2c[3];
    f32 f38[3];
    f32 f44;
    s32 f48;
    u8 pad4c[0x180 - 0x4c];
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    union { u64 x; s32 i[2]; } flags; /* 0x328 */
} VM;

s32 func_001d95f0(VM *vm) {
    vm->flags.x |= 0x1000;
    vm->f44 = (f32)vm->stk[vm->sp - 3] * 2;
    if (vm->obj->f370.b.b44 == 1) {
        vm->f2c[0] = vm->obj->v30[0];
        vm->f2c[1] = vm->obj->v30[1];
        vm->f2c[2] = vm->obj->v30[2];
    } else {
        vm->f2c[0] = 0;
        vm->f2c[1] = vm->obj->v30[3];
        vm->f2c[2] = 0;
    }
    vm->f38[0] = vm->f2c[0] + vm->stk[vm->sp - 2] * 3.1415928f / 180.0f;
    vm->f38[1] = vm->f2c[1] + vm->stk[vm->sp - 1] * 3.1415928f / 180.0f;
    vm->f38[2] = vm->f2c[2] + vm->stk[vm->sp] * 3.1415928f / 180.0f;
    vm->obj->f370.b.b44 = 1;
    vm->f48 = 0;
    vm->sp -= 4;
    return 2;
}
