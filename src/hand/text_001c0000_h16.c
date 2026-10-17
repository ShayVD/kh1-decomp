#include "common.h"
typedef struct {
    s32 x0;
    void *obj;
    u8 pad8[0x178];
    s32 sp;
    s32 stk[92];
} VM;
typedef struct {
    u8 pad0[0x3070];
    u64 f3070;
    u64 f3078;
} Big;
extern Big D_00389C90;
void func_00112b48(s32, s32, s32, s32);
s32 func_001cdf98(VM *vm) {
    s32 c = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    s32 a = vm->stk[vm->sp--];
    func_00112b48(a, b, c, -1);
    D_00389C90.f3070 |= 0x10000000000ULL;
    return 10;
}
