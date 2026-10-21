#include "common.h"

typedef struct {
    s32 x0;
    void *obj;
    u8 pad8[0x178];
    s32 sp;
    s32 stk[92];
    f32 f2f4;
    u8 pad2f8[0x30];
    union { u64 x; s32 i[2]; } flags;
    f32 f330;
} VM;

/* Strict aliasing (also matches in plain hand): the B48 unions and the flags union
   alias the s32 VM fields, so vm->sp stays after the copies and is reloaded after the
   flags store; f3464 is an f32 (0 -> sw zero), so its store does not feed the stk load
   and sched puts the or first. */
#include "data/pieces/D_002BC0C0.h"
typedef B48_2BC0C0 B48;
typedef struct {
    u8 pad0[0x3078];
    union { u64 x; s32 i[2]; } flags;
    u8 pad3080[0x3460 - 0x3080];
    f32 f3460;
    f32 f3464;
    u8 pad3468[8];
    B48 a;
    B48 b;
} Big92;
extern Big92 D_00389C90;
extern B48 D_002BC0F0;

s32 func_001d9268(VM *vm) {
    f32 x;
    s32 i;
    D_00389C90.b = D_002BC0C0.b48;
    D_00389C90.a = D_002BC0F0;
    i = vm->sp;
    D_00389C90.f3464 = 0;
    x = vm->stk[i] * 2.0f;
    D_00389C90.flags.x |= 2;
    vm->sp--;
    D_00389C90.f3460 = x;
    return 2;
}
