#include "common.h"

typedef struct {
    u8 pad0[0x180];
    s32 sp;
    s32 stk[1];
} VM;
typedef struct { u8 pad0[0x3078]; u64 f3078; } Big19;
extern Big19 D_00389C90;
void func_001dbd90();
s32 func_001559f0(s32, s32);
s32 func_00120748(void *, s32, void (*)(), s32);
extern u8 D_004906C0[];

s32 func_001dbdc8(VM *vm) {
    s32 r = func_001559f0(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    func_00120748(D_004906C0, r, func_001dbd90, 0);
    D_00389C90.f3078 |= 0x200;
    vm->sp -= 2;
    return 2;
}
#include "data/data_0049.h"
