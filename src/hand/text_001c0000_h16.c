#include "common.h"
#include "vm/script_vm.h"
typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
} Actor;

typedef struct {
    s32 x0;
    Actor *obj;
    f32 v08[3];
    f32 f14;
    f32 f18;
    f32 f1c;
    f32 f20;
    u8 pad24[0x15c];
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    union { u64 x; s32 i[2]; } flags;
} VM;
typedef struct {
    s32 x0;
    u8 pad4[8];
    f32 f0c;
    f32 v10[4];
    f32 v20[4];
    f32 v30[4];
} Fx;
typedef struct {
    u8 pad0[0x3070];
    union { u64 x; s32 i[2]; } f3070;
    union { u64 x; s32 i[2]; } f3078;
    u8 pad3080[0x18];
    s32 idx;
    s32 cnt;
    f32 d[3];
    Fx *ptrs[4];
    u8 pad30bc[0x6c];
    s32 cnt2;
    s32 step2;
    s32 cnt3;
    s32 step3[3];
} Big;
extern Big D_00389C90;

/* func_001cdf98 .. func_001cff80 are in src/vm/vm_lib.c. */

typedef struct { s32 v[3]; s32 f0c; } Cam;
extern Cam D_002BC080;
extern s32 D_002BC08C;
void func_00111600(s32, s32, s32);
void func_001065a8(s32, s32, s32, s32);
void func_00106648(s32, s32, s32, s32);
s32 D_00F20000(s32, s32);
void func_001cfff8(void) {
    if (--D_00389C90.cnt3 <= 0) D_00389C90.f3070.x &= ~0x8000000000ULL;
    D_002BC080.v[0] += D_00389C90.step3[0];
    D_002BC080.v[1] += D_00389C90.step3[1];
    D_002BC080.v[2] += D_00389C90.step3[2];
}
s32 func_001d0548(VM *vm) {
    func_00111600(vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 3;
    return 2;
}
s32 func_001d05a0(VM *vm) {
    func_001065a8(vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 4;
    return 2;
}
s32 func_001d0600(VM *vm) {
    func_00106648(vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 4;
    return 2;
}
s32 func_001d09a0(void) {
    D_00389C90.f3078.x &= ~0x2000ULL;
    return D_00F20000(0, 0);
}
s32 func_001d1230(VM *vm) {
    s32 sp = vm->sp;
    vm->flags.x |= 0x40;
    vm->f20 = vm->stk[sp - 3];
    vm->f14 = vm->stk[sp - 2];
    vm->f18 = vm->stk[sp - 1];
    vm->f1c = vm->stk[sp];
    vm->sp = sp - 4;
    vm->v08[0] = vm->obj->pos[0];
    vm->v08[1] = vm->obj->pos[1];
    vm->v08[2] = vm->obj->pos[2];
    return 2;
}
void func_001d1610(void);
extern f32 D_002BBDFC;
extern u64 D_0038CD00;
extern s32 D_002BC09C;
#include "data/pieces/D_002BC098.h"
extern s32 D_002BC0A0;
extern s32 D_002BC0A4;
void func_001560f8(s32, void (*)(void));
void func_00124218(s32);
Actor *func_00123488(s32);
void func_00122f58(Actor *, f32, f32, f32);
s32 func_001d12b8(VM *vm) {
    s32 sp = vm->sp;
    vm->flags.x |= 0x40;
    vm->f20 = vm->stk[sp - 3] * D_002BBDFC;
    vm->f14 = vm->stk[sp - 2];
    vm->f18 = vm->stk[sp - 1];
    vm->f1c = vm->stk[sp];
    vm->sp = sp - 4;
    vm->v08[0] = vm->obj->pos[0];
    vm->v08[1] = vm->obj->pos[1];
    vm->v08[2] = vm->obj->pos[2];
    return 2;
}
void func_001d1610(void) {
    D_00389C90.f3070.x &= ~0x200000000000ULL;
}
s32 func_001d1640(VM *vm) {
    D_00389C90.f3070.x |= 0x200000000000ULL;
    func_001560f8(vm->stk[vm->sp], func_001d1610);
    vm->sp--;
    return 2;
}
s32 func_001d16a8(void) {
    return ((s32)(D_0038CD00 >> 45) & 1) ? 4 : 2;
}
s32 func_001d16c8(VM *vm) {
    func_00124218(vm->stk[vm->sp]);
    vm->obj = func_00123488(vm->x0);
    vm->sp--;
    return 2;
}
s32 func_001d1728(VM *vm) {
    s32 sp = vm->sp;
    D_002BC09C = vm->stk[sp - 1];
    D_002BC098 = vm->stk[sp] * 3.1415928f / 180.0f;
    vm->sp = sp - 2;
    return 2;
}
s32 func_001d1790(VM *vm) {
    s32 sp = vm->sp;
    D_002BC0A0 = vm->stk[sp - 1];
    D_002BC0A4 = vm->stk[sp];
    vm->sp = sp - 2;
    return 2;
}
#include "data/data_002B.h"
#include "data/pieces/D_002BBDFC.h"
