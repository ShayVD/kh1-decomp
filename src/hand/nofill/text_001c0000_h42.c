#include "common.h"
typedef struct {
    s32 x0;
    s32 x4;
    u8 pad8[0x174];
    s32 pc;
    s32 sp;
    s32 stk[92];
} VM;
typedef struct {
    u8 pad0[0xc];
    f32 f0c;
} Lt;
extern Lt *D_0038CD3C[];
s32 func_001cede8(VM *vm) {
    s32 sp = vm->sp;
    Lt *p = D_0038CD3C[vm->stk[sp - 1]];
    p->f0c = 1.0 - vm->stk[sp] / 180.0f;
    vm->sp = sp - 2;
    return 2;
}
