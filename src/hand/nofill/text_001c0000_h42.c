#include "common.h"
typedef struct {
    s32 x0;
    s32 x4;
    u8 pad8[0x174];
    s32 pc;
    s32 sp;
    s32 stk[92];
} VM;
#include "data/types/nofill_text_001c0000_h42.h"
extern Lt *D_0038CD3C[];
s32 func_001cede8(VM *vm) {
    s32 sp = vm->sp;
    Lt *p = D_0038CD3C[vm->stk[sp - 1]];
    p->f0c = 1.0 - vm->stk[sp] / 180.0f;
    vm->sp = sp - 2;
    return 2;
}
#include "data/pieces/D_00389C90.h"
