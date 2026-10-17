#include "common.h"

/* Script VM handlers: value stack at +0x184, top index at +0x180. */
typedef struct {
    s32 x0;
    void *obj;
    u8 pad8[0x178];
    s32 sp;
    s32 stk[105];
    union { u64 x; s32 i[2]; } flags; /* 0x328 */
    f32 f330;
    u8 pad334[0xc];
    f32 f340;
    f32 f344;
    f32 f348;
} VM;

typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
void func_001c4640(Msg *m);

void func_00131c78(s32, s32);
extern void (*D_00377368)(s32, s32);
extern void (*D_0037736C)(s32, s32);
extern void (*D_00377370)(s32, s32);
extern void (*D_00377378)(s32, s32);
extern void (*D_0037737C)(s32, s32);
extern void (*D_00377380)(s32, s32, s32, s32);
extern void (*D_00377384)(s32);
extern s32 (*D_00377388)(s32, s32, s32);
extern void (*D_0037738C)(s32, s32);
extern void (*D_0037739C)(s32, s32, s32, s32, s32);
extern void (*D_00377390)(s32, s32, s32, s32);
extern void (*D_00377394)(s32, s32, s32, s32);
extern void (*D_00377398)(s32, s32, s32, s32, s32);
extern void (*D_003773A0)(s32, s32, s32, s32, s32);
extern void (*D_003773A4)(s32);
extern void (*D_003773A8)(s32);
extern void (*D_003773AC)(s32);
extern void (*D_003773B0)(s32, s32);
extern void (*D_003773B4)(s32);
extern void (*D_003773B8)(s32);
extern u64 D_0038CD08;
typedef struct { u8 pad0[0x36]; u8 f36; u8 pad37[116 - 0x37]; } E116;
extern E116 *D_00304BE8;

s32 func_001da6d0(VM *vm) {
    vm->flags.x |= 0x8000;
    vm->f330 = (f32)vm->stk[vm->sp - 3] * 2;
    vm->f340 = vm->stk[vm->sp - 2];
    vm->f344 = vm->stk[vm->sp - 1];
    vm->f348 = vm->stk[vm->sp];
    vm->sp -= 4;
    return 2;
}

s32 func_001da7b8(VM *vm) {
    func_00131c78(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001da808(VM *vm) {
    D_00377368(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001da860(VM *vm) {
    D_0037736C(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001da8b8(VM *vm) {
    D_00377370(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001da910(VM *vm) {
    D_00377378(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001da968(VM *vm) {
    Msg m;
    m.type = 41;
    m.val = (u32)vm->stk[vm->sp];
    m.x = vm->x0;
    func_001c4640(&m);
    vm->sp -= 1;
    return 2;
}

s32 func_001dab20(VM *vm) {
    if ((s32)(D_0038CD08 >> 4) & 1) return 4;
    return 2;
}

s32 func_001dabe8(VM *vm) {
    D_0037737C(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001dac40(VM *vm) {
    D_00377380(vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 4;
    return 2;
}

s32 func_001dad30(VM *vm) {
    if ((s32)(D_0038CD08 >> 5) & 1) return 4;
    return 2;
}

s32 func_001db080(VM *vm) {
    D_00377384(vm->stk[vm->sp]);
    vm->sp -= 1;
    return 2;
}

s32 func_001db0d0(VM *vm) {
    if (D_00377388(vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp])) {
        vm->sp -= 3;
        return 2;
    }
    return 4;
}

s32 func_001db140(VM *vm) {
    D_0037738C(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001db198(VM *vm) {
    D_0037739C(vm->stk[vm->sp - 4], vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 5;
    return 2;
}

s32 func_001db208(VM *vm) {
    D_003773A0(vm->stk[vm->sp - 4], vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 5;
    return 2;
}

s32 func_001db278(VM *vm) {
    D_00377390(vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 4;
    return 2;
}

s32 func_001db2e0(VM *vm) {
    D_00377394(vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 4;
    return 2;
}

s32 func_001db348(VM *vm) {
    D_00377398(vm->stk[vm->sp - 4], vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 5;
    return 2;
}

s32 func_001db3b8(VM *vm) {
    D_003773A4(vm->stk[vm->sp]);
    vm->sp -= 1;
    return 2;
}

s32 func_001db408(VM *vm) {
    D_003773A8(vm->stk[vm->sp]);
    vm->sp -= 1;
    return 2;
}

s32 func_001db458(VM *vm) {
    D_003773AC(vm->stk[vm->sp]);
    vm->sp -= 1;
    return 2;
}

s32 func_001db4a8(VM *vm) {
    D_003773B0(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001db500(VM *vm) {
    D_003773B4(vm->stk[vm->sp]);
    vm->sp -= 1;
    return 2;
}

s32 func_001db550(VM *vm) {
    D_003773B8(vm->stk[vm->sp]);
    vm->sp -= 1;
    return 2;
}

s32 func_001db600(VM *vm) {
    D_00304BE8[vm->stk[vm->sp - 1]].f36 = vm->stk[vm->sp];
    vm->sp -= 2;
    return 2;
}
