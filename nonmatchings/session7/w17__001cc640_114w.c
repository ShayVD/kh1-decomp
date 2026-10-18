/* near miss, hand (strict), no rodata: ~114 seqdiff units, 1408 vs 1432 bytes. Off: per-case store order and register assignment of D_006298F0[i] field copies; copy-move chains present but ordered differently; 6 words short overall. */
#include "common.h"
typedef struct {
    s32 x0;
    void *obj;
    u8 pad8[0x178];
    s32 sp;
    s32 stk[92];
} VM;
typedef struct {
    s32 x0;
    u16 h4;
    u16 h6;
    u16 h8;
    u8 pada[2];
    u16 hc;
    u16 he;
    u8 pad10[0xc];
    f32 f1c;
    u8 pad20[0x10];
    f32 v30[2];
    u8 pad38[8];
    f32 v40[2];
    u8 pad48[0x38];
    u8 f80[0x10];
    u8 b90;
    u8 pad91[3];
    f32 f94;
    u8 pad98[0x18];
} __attribute__((aligned(8))) Obj;
typedef struct { u8 *x0; } P26A0;
extern P26A0 D_002E26A0;
extern Obj D_006298F0[];
s32 func_0017e428(void *, void *);
void func_0017e768(void);

s32 func_001cc640(VM *vm) {
    s32 sp, i, j;
    if (vm->obj == 0) {
        vm->sp -= 2;
        return 2;
    }
    switch (func_0017e428(D_002E26A0.x0 + 16, (u8 *)vm->obj + 16)) {
    case 0:
        i = vm->stk[vm->sp]; j = vm->stk[vm->sp - 1];
        D_006298F0[j].v30[0] = 100.0f;
        D_006298F0[j].h6 = 1;
        D_006298F0[j].v30[1] = 120.0f;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[j].f1c = 315.0f;
        D_006298F0[j].h8 = 3;
        D_006298F0[i].v30[0] = -100.0f;
        D_006298F0[i].v30[1] = -120.0f;
        D_006298F0[i].f1c = 135.0f;
        D_006298F0[i].h6 = 1;
        D_006298F0[i].v40[1] = 2.0f;
        D_006298F0[j].v40[1] = 2.0f;
        D_006298F0[i].h8 = 13;
        D_006298F0[j].v40[0] = 10.0f;
        break;
    case 1:
        i = vm->stk[vm->sp]; j = vm->stk[vm->sp - 1];
        D_006298F0[j].v30[0] = 100.0f;
        D_006298F0[j].h6 = 1;
        D_006298F0[j].v30[1] = -120.0f;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[j].f1c = 225.0f;
        D_006298F0[j].h8 = 11;
        D_006298F0[i].v30[0] = -100.0f;
        D_006298F0[i].v30[1] = 120.0f;
        D_006298F0[i].f1c = 45.0f;
        D_006298F0[i].h6 = 1;
        D_006298F0[i].v40[1] = 2.0f;
        D_006298F0[j].v40[1] = 2.0f;
        D_006298F0[i].h8 = 1;
        D_006298F0[j].v40[0] = 10.0f;
        break;
    case 2:
        i = vm->stk[vm->sp]; j = vm->stk[vm->sp - 1];
        D_006298F0[j].v30[0] = -100.0f;
        D_006298F0[j].h6 = 1;
        D_006298F0[j].v30[1] = -120.0f;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[j].f1c = 135.0f;
        D_006298F0[j].h8 = 13;
        D_006298F0[i].v30[0] = 100.0f;
        D_006298F0[i].v30[1] = 120.0f;
        D_006298F0[i].f1c = 315.0f;
        D_006298F0[i].h6 = 1;
        D_006298F0[i].v40[1] = 2.0f;
        D_006298F0[j].v40[1] = 2.0f;
        D_006298F0[i].h8 = 3;
        D_006298F0[j].v40[0] = 10.0f;
        break;
    case 3:
        i = vm->stk[vm->sp]; j = vm->stk[vm->sp - 1];
        D_006298F0[j].v30[0] = -100.0f;
        D_006298F0[j].h6 = 1;
        D_006298F0[j].v30[1] = 120.0f;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[j].f1c = 45.0f;
        D_006298F0[j].h8 = 1;
        D_006298F0[i].v30[0] = 100.0f;
        D_006298F0[i].v30[1] = -120.0f;
        D_006298F0[i].f1c = 225.0f;
        D_006298F0[i].h6 = 1;
        D_006298F0[i].v40[1] = 2.0f;
        D_006298F0[j].v40[1] = 2.0f;
        D_006298F0[i].h8 = 11;
        D_006298F0[j].v40[0] = 10.0f;
        break;
    case 4:
        i = vm->stk[vm->sp]; j = vm->stk[vm->sp - 1];
        D_006298F0[j].v30[0] = 100.0f;
        D_006298F0[j].h6 = 1;
        D_006298F0[j].v30[1] = 120.0f;
        D_006298F0[i].v40[0] = 10.0f;
        D_006298F0[j].f1c = 315.0f;
        D_006298F0[j].h8 = 3;
        D_006298F0[i].v30[0] = -100.0f;
        D_006298F0[i].v30[1] = -120.0f;
        D_006298F0[i].f1c = 135.0f;
        D_006298F0[i].h6 = 1;
        D_006298F0[i].v40[1] = 2.0f;
        D_006298F0[j].v40[1] = 2.0f;
        D_006298F0[i].h8 = 13;
        D_006298F0[j].v40[0] = 10.0f;
        func_0017e768();
        break;
    }
    vm->sp -= 2;
    return 2;
}
