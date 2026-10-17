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
void func_00112b80(s32, s32, s32, s32);
void func_00112bb8(s32);
void func_00108180(s32);
void func_001081a0(s32);
s32 func_001ce020(VM *vm) {
    s32 d = vm->stk[vm->sp--];
    s32 c = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    s32 a = vm->stk[vm->sp--];
    func_00112b48(a, b, c, d);
    D_00389C90.f3070 |= 0x10000000000ULL;
    return 10;
}
s32 func_001ce0b8(VM *vm) {
    s32 d = vm->stk[vm->sp--];
    s32 c = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    s32 a = vm->stk[vm->sp--];
    func_00112b80(a, b, c, d);
    D_00389C90.f3070 |= 0x10000000000ULL;
    return 10;
}
s32 func_001ce150(VM *vm) {
    s32 a = vm->stk[vm->sp--];
    func_00112bb8(a);
    D_00389C90.f3070 |= 0x10000000000ULL;
    return 10;
}
s32 func_001ce1a8(VM *vm) {
    s32 d = vm->stk[vm->sp--];
    s32 c = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    s32 a = vm->stk[vm->sp--];
    func_00112b48(a, b, c, d);
    D_00389C90.f3070 |= 0x10000000000ULL;
    return 10;
}
s32 func_001ce240(VM *vm) {
    s32 a = vm->stk[vm->sp--];
    func_00112bb8(a);
    D_00389C90.f3070 |= 0x10000000000ULL;
    return 10;
}
s32 func_001ce2e8(VM *vm) {
    func_00108180(vm->stk[vm->sp--]);
    return 2;
}
s32 func_001ce320(VM *vm) {
    func_001081a0(vm->stk[vm->sp--]);
    return 2;
}
