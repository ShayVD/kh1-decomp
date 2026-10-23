#include "common.h"
#include "vm/script_vm.h"
#include "data/types/vm_rec.h"
typedef struct VmObj {
    u8 pad0[0x10];
    f32 pos[3];
} Actor;
typedef VmRec VM;
typedef struct {
    s32 x0;
    u8 pad4[8];
    f32 f0c;
    f32 v10[4];
    f32 v20[4];
    f32 v30[4];
} Fx;
typedef struct {
    s32 key;
    s32 x4;
    s32 x8;
    s32 xc;
    f32 v[2][4];
} __attribute__((aligned(8))) E48;
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
    u8 pad3140[0x18];
    struct VmObj *f3158;
    u8 pad315c[0x1c];
    s32 n3178;
    s32 pad317c;
    E48 ent3180[1];
} Big;
extern Big D_00389C90;
double sqrt(double);
#include "data/types/nofill_text_001d0000_h43.h"
extern s32 D_0039A570;
#include "data/pieces/D_0038D170.h"
extern s32 D_003A7980;
#include "data/pieces/D_0039A580.h"
void func_001248e8(s32);
s32 func_001d5168(VM *vm) {
    s32 i, n;
    KEnt *p;
    func_001248e8(vm->stk[vm->sp]);
    vm->fl.x |= 4;
    vm->x2f4 = 2.0f;
    p = D_0038D170;
    n = D_0039A570;
    for (i = 0; i < n; i++, p++) {
        if (p->x0 == vm->stk[vm->sp]) p->obj = 0;
    }
    p = D_0039A580;
    n = D_003A7980;
    for (i = 0; i < n; i++, p++) {
        if (p->x0 == vm->stk[vm->sp]) p->obj = 0;
    }
    vm->sp--;
    return 2;
}
s32 func_001d58c8(VM *vm) {
    s32 i, n;
    KEnt *p;
    func_001248e8((s32)D_00389C90.f3158);
    p = D_0038D170;
    n = D_0039A570;
    for (i = 0; i < n; i++, p++) {
        if (p->x0 == (s32)D_00389C90.f3158) p->obj = 0;
    }
    p = D_0039A580;
    n = D_003A7980;
    for (i = 0; i < n; i++, p++) {
        if (p->x0 == (s32)D_00389C90.f3158) p->obj = 0;
    }
    return 2;
}

/* needs make: uses rodata */
double sin(double);
double cos(double);
s32 func_001d4c08(VM *vm) {
    f32 r = sin(vm->stk[vm->sp] * 3.1415928f / 180.0f) * 10000.0;
    vm->stk[vm->sp] = r;
    return 2;
}
s32 func_001d4cb8(VM *vm) {
    f32 r = cos(vm->stk[vm->sp] * 3.1415928f / 180.0f) * 10000.0;
    vm->stk[vm->sp] = r;
    return 2;
}
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_0038.h"
