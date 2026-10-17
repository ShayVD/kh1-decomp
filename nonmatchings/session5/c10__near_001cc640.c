#include "common.h"

typedef struct {
    void *obj;
    u8 pad4[0x178];
    s32 sp;
    s32 stk[105];
} Sub;
typedef struct {
    s32 x0;
    Sub s;
} VM;
typedef struct {
    s32 x0;
    s16 h4, h6, h8, ha, hc, he;
    u8 pad10[0xc];
    f32 f1c;
    u8 pad20[0x10];
    f32 f30, f34;
    u8 pad38[8];
    f32 f40, f44;
    u8 pad48[0x68];
} __attribute__((aligned(8))) Win;
typedef struct { u8 *x0; } P26A0;

extern P26A0 D_002E26A0;
extern Win D_006298F0[];

s32 func_0017e428(void *, void *);
void func_0017e768(void);

s32 func_001cc640(VM *vm) {
    Sub *s = &vm->s;
    Win *a, *b;
    s32 sp;

    if (vm->s.obj == 0) {
        vm->s.sp -= 2;
        return 2;
    }
    switch (func_0017e428(D_002E26A0.x0 + 16, (u8 *)vm->s.obj + 16)) {
    case 0:
        D_006298F0[s->stk[vm->s.sp]].f1c = 135.0f;
        D_006298F0[s->stk[vm->s.sp]].h8 = 13;
        D_006298F0[s->stk[vm->s.sp]].h6 = 1;
        D_006298F0[s->stk[vm->s.sp]].f30 = -100.0f;
        D_006298F0[s->stk[vm->s.sp]].f34 = -120.0f;
        D_006298F0[s->stk[vm->s.sp]].f40 = 10.0f;
        D_006298F0[s->stk[vm->s.sp]].f44 = 2.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f1c = 315.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].h8 = 3;
        D_006298F0[s->stk[vm->s.sp - 1]].h6 = 1;
        D_006298F0[s->stk[vm->s.sp - 1]].f30 = 100.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f34 = 120.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f40 = 10.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f44 = 2.0f;
        break;
    case 1:
        D_006298F0[s->stk[vm->s.sp]].f1c = 45.0f;
        D_006298F0[s->stk[vm->s.sp]].h8 = 1;
        D_006298F0[s->stk[vm->s.sp]].h6 = 1;
        D_006298F0[s->stk[vm->s.sp]].f30 = -100.0f;
        D_006298F0[s->stk[vm->s.sp]].f34 = 120.0f;
        D_006298F0[s->stk[vm->s.sp]].f40 = 10.0f;
        D_006298F0[s->stk[vm->s.sp]].f44 = 2.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f1c = 225.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].h8 = 11;
        D_006298F0[s->stk[vm->s.sp - 1]].h6 = 1;
        D_006298F0[s->stk[vm->s.sp - 1]].f30 = 100.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f34 = -120.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f40 = 10.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f44 = 2.0f;
        break;
    case 2:
        D_006298F0[s->stk[vm->s.sp]].f1c = 315.0f;
        D_006298F0[s->stk[vm->s.sp]].h8 = 3;
        D_006298F0[s->stk[vm->s.sp]].h6 = 1;
        D_006298F0[s->stk[vm->s.sp]].f30 = 100.0f;
        D_006298F0[s->stk[vm->s.sp]].f34 = 120.0f;
        D_006298F0[s->stk[vm->s.sp]].f40 = 10.0f;
        D_006298F0[s->stk[vm->s.sp]].f44 = 2.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f1c = 135.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].h8 = 13;
        D_006298F0[s->stk[vm->s.sp - 1]].h6 = 1;
        D_006298F0[s->stk[vm->s.sp - 1]].f30 = -100.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f34 = -120.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f40 = 10.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f44 = 2.0f;
        break;
    case 3:
        D_006298F0[s->stk[vm->s.sp]].f1c = 225.0f;
        D_006298F0[s->stk[vm->s.sp]].h8 = 11;
        D_006298F0[s->stk[vm->s.sp]].h6 = 1;
        D_006298F0[s->stk[vm->s.sp]].f30 = 100.0f;
        D_006298F0[s->stk[vm->s.sp]].f34 = -120.0f;
        D_006298F0[s->stk[vm->s.sp]].f40 = 10.0f;
        D_006298F0[s->stk[vm->s.sp]].f44 = 2.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f1c = 45.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].h8 = 1;
        D_006298F0[s->stk[vm->s.sp - 1]].h6 = 1;
        D_006298F0[s->stk[vm->s.sp - 1]].f30 = -100.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f34 = 120.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f40 = 10.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f44 = 2.0f;
        break;
    case 4:
        D_006298F0[s->stk[vm->s.sp]].f1c = 135.0f;
        D_006298F0[s->stk[vm->s.sp]].h8 = 13;
        D_006298F0[s->stk[vm->s.sp]].h6 = 1;
        D_006298F0[s->stk[vm->s.sp]].f30 = -100.0f;
        D_006298F0[s->stk[vm->s.sp]].f34 = -120.0f;
        D_006298F0[s->stk[vm->s.sp]].f40 = 10.0f;
        D_006298F0[s->stk[vm->s.sp]].f44 = 2.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f1c = 315.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].h8 = 3;
        D_006298F0[s->stk[vm->s.sp - 1]].h6 = 1;
        D_006298F0[s->stk[vm->s.sp - 1]].f30 = 100.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f34 = 120.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f40 = 10.0f;
        D_006298F0[s->stk[vm->s.sp - 1]].f44 = 2.0f;
        func_0017e768();
        break;
    }
    vm->s.sp -= 2;
    return 2;
}
