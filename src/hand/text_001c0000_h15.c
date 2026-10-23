#include "common.h"
#include "vm/script_vm.h"

/* Script VM: value stack at +0x184, stack pointer (index of top) at +0x180. */
typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
} Actor;

typedef struct {
    s32 x0;
    Actor *obj;
    u8 pad8[0x178];
    s32 sp;
    s32 stk[92];
    f32 f2f4;
    u8 pad2f8[0x30];
    union { u64 x; s32 i[2]; } flags;
} VM;


typedef struct {
    u8 a[4];
    u8 b[0x1030 - 4];
    s8 c[4];
    u8 pad1034[0x3070 - 0x1034];
    u64 f3070;
    u64 f3078;
} Big;

/* Message passed to func_001c4640. */

void func_001c6720(void);

extern s32 D_002BC080[4];
extern s32 D_002BC090, D_002BC094, D_002BC09C, D_002BC0A0, D_002BC0A4, D_002BBE04;
#include "data/pieces/D_002BC098.h"
extern Big D_00389C90;

/* func_001cc210 .. func_001cc508, func_001cccf0 and func_001ccd30 are in src/msgwin/msgwin.c,
 * func_001cce38 .. func_001cd1d0 (the opcode 1 operations) in src/vm/vm_calc.c. */

s32 func_001cd280(VM *vm) {
    vm->flags.x |= 4;
    vm->f2f4 = vm->stk[vm->sp] * 2.0f;
    vm->sp--;
    return 6;
}

s32 func_001cd6b8(VM *vm) {
    VmMsg m;
    m.type = 5;
    m.val = (u32)vm->stk[vm->sp];
    m.x = vm->x0;
    func_001c4640(&m);
    vm->sp--;
    return 2;
}

s32 func_001cd778(VM *vm) {
    VmMsg m;
    m.type = 0;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    func_001c6720();
    D_00389C90.f3078 |= 0x400;
    return 2;
}

s32 func_001cd830(VM *vm) {
    VmMsg m;
    m.type = 1;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    D_00389C90.f3070 &= ~0x2000000000ULL;
    D_00389C90.f3078 &= ~0x400ULL;
    return 2;
}

s32 func_001cd8b0(VM *vm) {
    vm->sp++;
    vm->stk[vm->sp] = vm->obj->pos[0];
    return 2;
}

s32 func_001cd8e0(VM *vm) {
    vm->sp++;
    vm->stk[vm->sp] = vm->obj->pos[1];
    return 2;
}

s32 func_001cd910(VM *vm) {
    vm->sp++;
    vm->stk[vm->sp] = vm->obj->pos[2];
    return 2;
}

s32 func_001cd9e8(VM *vm) {
    u64 f = vm->flags.x;
    if ((f & 0xa41) && !((s32)(f >> 4) & 1)) return 4;
    return 2;
}

s32 func_001cda18(VM *vm) {
    VmMsg m;
    m.type = 6;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cda60(VM *vm) {
    VmMsg m;
    m.type = 7;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdaa8(VM *vm) {
    VmMsg m;
    m.type = 8;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdaf0(VM *vm) {
    VmMsg m;
    m.type = 9;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdb38(VM *vm) {
    VmMsg m;
    m.type = 10;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdb80(VM *vm) {
    VmMsg m;
    m.type = 11;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdbc8(VM *vm) {
    VmMsg m;
    m.type = 12;
    m.val = 0;
    m.x = vm->x0;
    m.v[0] = 0.0f;
    m.v[1] = vm->stk[vm->sp];
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    func_001c4640(&m);
    vm->sp--;
    return 2;
}



s32 func_001cde38(void) {
    D_002BBE04 = 1;
    D_002BC080[0] = 128;
    D_002BC080[1] = 128;
    D_002BC080[2] = 128;
    D_002BC080[3] = 64;
    D_002BC090 = 256;
    D_002BC094 = 192;
    D_002BC098 = 0;
    D_002BC09C = 1;
    D_002BC0A0 = 0;
    D_002BC0A4 = 0;
    return 2;
}

s32 func_001cdf00(VM *vm) {
    VmMsg m;
    m.type = 17;
    m.val = (u32)vm->stk[vm->sp - 1];
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp];
    func_001c4640(&m);
    vm->sp -= 2;
    return 2;
}
#include "data/data_002B.h"
#include "data/data_003C.h"
#include "data/pieces/D_002BC080.h"
#include "data/pieces/D_002BBE04.h"
