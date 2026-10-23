#include "common.h"
#include "vm/script_vm.h"
#include "data/pieces/D_00304BE8_s.h"
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
    f32 f24;
    f32 f28;
    u8 pad2c[0x154];
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    union { u64 x; s32 i[2]; } flags;
} VM;
#include "vm/vm_mgr.h"
s32 func_00111090(void);
s32 func_00111090(void);
extern void (*D_00377344)(s32, s32, void *);
extern void (*D_0037733C)(s32, void *);
extern void (*D_00377340)(s32);
extern void (*D_00377348)(s32, s32);
extern void (*D_0037734C)(s32, s32, s32);
extern void (*D_00377350)(s32, s32);
extern void (*D_00377354)(s32, s32);
extern void (*D_00377358)(s32, s32);
extern void (*D_0037735C)(s32);
#include "data/pieces/D_002E26A0.h"
extern void (*D_00377360)(s32);
void func_0013c8c8(s32, s32);
#include "data/pieces/D_0037A378.h"
typedef struct { s32 f0; s32 f4; } P8;
P8 *func_001e98d0(s32, s32);
void func_00141218(s32);
s32 func_001da088(VM *vm) {
    func_00141218(func_001e98d0((s32)(vm->flags.x >> 5) & 1, vm->stk[vm->sp])->f4);
    vm->sp--;
    return 2;
}
extern u16 D_002C595A;
s32 func_001da0e8(void) {
    if (D_002C595A & 1) return 4;
    return 2;
}
extern s32 D_002C5958;
s32 func_001da108(void) {
    if (D_002C5958 & 0x6000) return 4;
    return 2;
}
extern void (*D_00377364)(s32);
s32 func_001da128(VM *vm) {
    D_00377364(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}
s32 func_002394f8(void);
s32 func_001da178(void) {
    return func_002394f8() ? 4 : 2;
}
typedef struct { u16 a:4; u16 b:4; u16 c:8; } B16;
B16 *func_00147778(s32);
void func_0013c9e0(s32, s32);
void func_0013c8c8(s32, s32);
s32 func_001da1d0(VM *vm) {
    B16 *p = func_00147778(vm->stk[vm->sp]);
    switch (p->a) {
    case 0:
        func_0013c9e0(p->c, p->b);
        break;
    case 1:
        func_0013c8c8(p->c, p->b);
        break;
    }
    vm->sp--;
    return 2;
}
s32 func_00111660(s32, s32);
s32 func_001da260(VM *vm) {
    s32 a = vm->stk[vm->sp - 1];
    s32 b = vm->stk[vm->sp];
    vm->sp--;
    vm->stk[vm->sp] = func_00111660(a, b);
    return 2;
}
typedef W606Mem_304be8 E74;
#include "data/pieces/D_00304BE8.h"
s32 func_001da3b8(VM *vm) {
    E74 *e = D_00304BE8->m;
    e += vm->stk[vm->sp];
    vm->stk[vm->sp] = e->sub.lv;
    return 2;
}
void func_00142388(f32 *, s32 *);
s32 func_001da400(VM *vm) {
    f32 v[3];
    s32 o[4];
    v[0] = vm->stk[vm->sp - 2];
    v[1] = vm->stk[vm->sp - 1];
    v[2] = vm->stk[vm->sp];
    func_00142388(v, o);
    vm->sp -= 2;
    vm->stk[vm->sp] = o[0];
    return 2;
}
void func_00142388(f32 *, s32 *);
s32 func_001da490(VM *vm) {
    f32 v[3];
    s32 o[4];
    v[0] = vm->stk[vm->sp - 2];
    v[1] = vm->stk[vm->sp - 1];
    v[2] = vm->stk[vm->sp];
    func_00142388(v, o);
    vm->sp -= 2;
    vm->stk[vm->sp] = o[1];
    return 2;
}
void func_00142388(f32 *, s32 *);
s32 func_001da520(VM *vm) {
    f32 v[3];
    s32 o[4];
    v[0] = vm->stk[vm->sp - 2];
    v[1] = vm->stk[vm->sp - 1];
    v[2] = vm->stk[vm->sp];
    func_00142388(v, o);
    vm->sp -= 2;
    vm->stk[vm->sp] = o[2];
    return 2;
}
void func_00142470(Actor *, s32 *);
s32 func_001da5b0(VM *vm) {
    s32 v[3];
    v[0] = vm->stk[vm->sp - 2];
    v[1] = vm->stk[vm->sp - 1];
    v[2] = vm->stk[vm->sp];
    if (vm->obj) func_00142470(vm->obj, v);
    vm->sp -= 3;
    return 2;
}
#include "data/data_002B.h"
#include "data/data_0038.h"
#include "data/pieces/D_0037733C.h"
#include "data/pieces/D_00377340.h"
#include "data/pieces/D_00377344.h"
#include "data/pieces/D_00377348.h"
#include "data/pieces/D_0037734C.h"
#include "data/pieces/D_00377350.h"
#include "data/pieces/D_00377354.h"
#include "data/pieces/D_00377358.h"
#include "data/pieces/D_0037735C.h"
#include "data/pieces/D_00377360.h"
#include "data/pieces/D_00377364.h"
