#include "common.h"

/* Built without assembler delay-slot filling. */
typedef struct {
    u8 pad0[0x18];
    f32 f18;
} Sub130;
typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1c[0x50 - 0x1c];
    f32 p50[3];
    u8 pad5c[0x130 - 0x5c];
    Sub130 *f130;
    u8 pad134[0x164 - 0x134];
    s32 f164;
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
    f32 f330;
} VM;
typedef struct {
    u8 pad0[0x3040];
    s32 f3040;
    u8 pad3044[0x1c];
    s32 *f3060;
    u8 pad3064[0xc];
    union { u64 x; s32 i[2]; u8 c; } f3070;
    s32 w[8]; /* 0x3078 */
    u8 pad3098[0x3384 - 0x3098];
    struct { void *id; s32 f4; s32 f8; s32 fc; s32 f10; s32 f14; } e3384[8];
} Big;
extern Big D_00389C90;
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;
void func_001c4640(Msg *m);
typedef struct { u8 pad0[0x48e]; u8 a48e[11]; u8 a499[1]; } Save;
extern Save *D_00304BE8;
typedef struct { u8 pad0[0x3c]; s32 f3c; u8 pad40[4]; s32 f44; } Sub6c;
typedef struct { u8 pad0[0x6c]; Sub6c *f6c; } Sub4;
typedef struct { u8 pad0[4]; Sub4 *f4; u8 pad8[0x318 - 8]; s32 f318; } Ent;
Ent *func_001e98d0(s32, s32);
Ent *func_001e9b98(s32, s32);

void func_00104268(f32, f32);

s32 func_001d3cb8(VM *vm) {
    vm->sp++;
    if (vm->obj) {
        vm->stk[vm->sp] = vm->obj->p50[0];
    } else {
        vm->stk[vm->sp] = 0;
    }
    return 2;
}

s32 func_001d3d08(VM *vm) {
    vm->sp++;
    if (vm->obj) {
        vm->stk[vm->sp] = vm->obj->p50[1];
    } else {
        vm->stk[vm->sp] = 0;
    }
    return 2;
}

s32 func_001d3d58(VM *vm) {
    vm->sp++;
    if (vm->obj) {
        vm->stk[vm->sp] = vm->obj->p50[2];
    } else {
        vm->stk[vm->sp] = 0;
    }
    return 2;
}

s32 func_001d6658(VM *vm) {
    func_00104268(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}
