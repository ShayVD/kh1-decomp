#include "common.h"
#include "data/types/vm_rec.h"
typedef struct VmObj {
    u8 pad0[0x10];
    f32 pos[3];
} Actor;
typedef VmRec VM;
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
void func_001c4640(Msg *m);
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
typedef struct { s32 v[3]; s32 f0c; } Cam;
extern Cam D_002BC080;
double sqrt(double);
extern s32 D_003888C4[];
static inline double inl_dist(f32 x1, f32 y1, f32 x2, f32 y2) {
    f32 dx = x2 - x1;
    f32 dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}
s32 func_001d17d0(VM *vm) {
    f32 d = inl_dist(vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    if (vm->stk[32] >= 2304) D_003888C4[vm->stk[32]] = d;
    vm->sp -= 5;
    return 2;
}
s32 func_001d1890(VM *vm) {
    f32 d = inl_dist(vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 3;
    vm->stk[vm->sp] = d;
    return 2;
}
static inline double inl_dist3(f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2) {
    f32 dx = x2 - x1;
    f32 dy = y2 - y1;
    f32 dz = z2 - z1;
    return sqrt(dx * dx + dz * dz + dy * dy);
}
s32 func_001d1948(VM *vm) {
    f32 d = inl_dist3(vm->stk[vm->sp - 5], vm->stk[vm->sp - 4], vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    if (vm->stk[32] >= 2304) D_003888C4[vm->stk[32]] = d;
    vm->sp -= 7;
    return 2;
}
s32 func_001d1a28(VM *vm) {
    f32 d = inl_dist3(vm->stk[vm->sp - 5], vm->stk[vm->sp - 4], vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 5;
    vm->stk[vm->sp] = d;
    return 2;
}
VM *func_001e98d0(s32, s32);
s32 func_001d1b00(VM *vm) {
    VM *a = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    VM *b = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    Actor *p = a->obj;
    Actor *q = b->obj;
    f32 d = inl_dist(p->pos[0], p->pos[2], q->pos[0], q->pos[2]);
    if (vm->stk[32] >= 2304) D_003888C4[vm->stk[32]] = d;
    vm->sp -= 3;
    return 2;
}
s32 func_001d1bf8(VM *vm) {
    VM *a = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    VM *b = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    Actor *p = a->obj;
    Actor *q = b->obj;
    f32 d = inl_dist(p->pos[0], p->pos[2], q->pos[0], q->pos[2]);
    vm->sp -= 1;
    vm->stk[vm->sp] = d;
    return 2;
}
s32 func_001d1ce0(VM *vm) {
    VM *a = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    VM *b = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    Actor *p = a->obj;
    Actor *q = b->obj;
    f32 d = inl_dist3(p->pos[0], p->pos[2], p->pos[1], q->pos[0], q->pos[2], q->pos[1]);
    if (vm->stk[32] >= 2304) D_003888C4[vm->stk[32]] = d;
    vm->sp -= 3;
    return 2;
}
s32 func_001d1df0(VM *vm) {
    VM *a = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    VM *b = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    Actor *p = a->obj;
    Actor *q = b->obj;
    f32 d = inl_dist3(p->pos[0], p->pos[2], p->pos[1], q->pos[0], q->pos[2], q->pos[1]);
    vm->sp -= 1;
    vm->stk[vm->sp] = d;
    return 2;
}
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
