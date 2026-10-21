#include "common.h"

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

/* 0xB0-byte entries at D_006298F0. */
typedef struct {
    u8 pad0[4];
    u16 h4;
    u8 pad6[6];
    u16 hc;
    u16 he;
    u8 pad10[0xc];
    f32 f1c;
    u8 pad20[0x10];
    f32 v30[2];
    u8 pad38[8];
    f32 v40[2];
    u8 pad48[0x4c];
    f32 f94;
    u8 pad98[0x18];
} __attribute__((aligned(8))) Obj;

extern Obj D_006298F0[];
extern s32 D_003C5870[];
extern s32 D_0037A378;

typedef struct {
    u8 a[4];
    u8 b[0x1030 - 4];
    s8 c[4];
    u8 pad1034[0x3070 - 0x1034];
    u64 f3070;
    u64 f3078;
} Big;

/* Message passed to func_001c4640. */
typedef struct {
    u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[4];
} Msg;

void func_001c4640(Msg *m);
void func_001c6720(void);

extern s32 D_002BC080[4];
extern s32 D_002BC090, D_002BC094, D_002BC09C, D_002BC0A0, D_002BC0A4, D_002BBE04;
#include "data/pieces/D_002BC098.h"
extern Big D_00389C90;

s32 func_001cc210(VM *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 1];
    f32 v = vm->stk[sp];
    vm->sp = sp - 2;
    D_006298F0[i].f1c = v;
    return 2;
}

s32 func_001cc260(VM *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 2];
    f32 a = vm->stk[sp - 1];
    f32 b = vm->stk[sp];
    vm->sp = sp - 3;
    D_006298F0[i].v30[0] = a;
    D_006298F0[i].v30[1] = b;
    return 2;
}

s32 func_001cc2c8(VM *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 2];
    f32 a = vm->stk[sp - 1];
    f32 b = vm->stk[sp];
    vm->sp = sp - 3;
    D_006298F0[i].v40[0] = a;
    D_006298F0[i].v40[1] = b;
    return 2;
}

s32 func_001cc330(VM *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 1];
    u16 v = vm->stk[sp];
    vm->sp = sp - 2;
    D_006298F0[i].h4 = v;
    return 2;
}

s32 func_001cc380(VM *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 1];
    u16 v = vm->stk[sp];
    vm->sp = sp - 2;
    D_006298F0[i].hc = v;
    return 2;
}

s32 func_001cc3d0(VM *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 1];
    u16 v = vm->stk[sp];
    vm->sp = sp - 2;
    D_006298F0[i].he = v;
    return 2;
}

s32 func_001cc420(VM *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 1];
    f32 v = vm->stk[sp];
    vm->sp = sp - 2;
    D_006298F0[i].f94 = v;
    return 2;
}

s32 func_001cc470(VM *vm) {
    s32 i;
    if (D_0037A378 & 1) return 2;
    for (i = 0; i < 4; i++) {
        if (D_00389C90.a[i] && D_00389C90.c[i] != 7) break;
    }
    if (i < 4) {
        if (!((s32)(vm->flags.x >> 4) & 1)) return 4;
    }
    return 2;
}

s32 func_001cc508(VM *vm) {
    s32 sp = vm->sp;
    u8 c = D_00389C90.b[vm->stk[sp]];
    if (c != 0 && c != 4) return 4;
    vm->sp = sp - 1;
    return 2;
}

s32 func_001cccf0(VM *vm) {
    D_003C5870[vm->stk[vm->sp - 1]] = vm->stk[vm->sp];
    vm->sp -= 2;
    return 2;
}

Obj func_001ccd30(s32 i) {
    return D_006298F0[i];
}

void func_001cce38(VM *vm) {
    vm->sp--;
    vm->stk[vm->sp] += vm->stk[vm->sp + 1];
}

void func_001cce70(VM *vm) {
    vm->sp--;
    vm->stk[vm->sp] -= vm->stk[vm->sp + 1];
}

void func_001ccea8(VM *vm) {
    vm->stk[vm->sp] = -vm->stk[vm->sp];
}

void func_001ccec8(VM *vm) {
    vm->sp--;
    vm->stk[vm->sp] *= vm->stk[vm->sp + 1];
}

void func_001ccf00(VM *vm) {
    vm->sp--;
    vm->stk[vm->sp] /= vm->stk[vm->sp + 1];
}

void func_001ccf40(VM *vm) {
    vm->sp--;
    vm->stk[vm->sp] %= vm->stk[vm->sp + 1];
}

void func_001ccf80(VM *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] == vm->stk[vm->sp + 1];
}

void func_001ccfb8(VM *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] > vm->stk[vm->sp + 1];
}

void func_001ccff0(VM *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] >= vm->stk[vm->sp + 1];
}

void func_001cd028(VM *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] < vm->stk[vm->sp + 1];
}

void func_001cd060(VM *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] <= vm->stk[vm->sp + 1];
}

void func_001cd098(VM *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] != vm->stk[vm->sp + 1];
}

void func_001cd0d0(VM *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] & vm->stk[vm->sp + 1];
}

void func_001cd108(VM *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] | vm->stk[vm->sp + 1];
}

void func_001cd140(VM *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] ^ vm->stk[vm->sp + 1];
}

void func_001cd178(VM *vm) {
    vm->stk[vm->sp] = ~vm->stk[vm->sp];
}

void func_001cd198(VM *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] >> vm->stk[vm->sp + 1];
}

void func_001cd1d0(VM *vm) {
    vm->sp--;
    vm->stk[vm->sp] = vm->stk[vm->sp] << vm->stk[vm->sp + 1];
}

s32 func_001cd280(VM *vm) {
    vm->flags.x |= 4;
    vm->f2f4 = vm->stk[vm->sp] * 2.0f;
    vm->sp--;
    return 6;
}

s32 func_001cd6b8(VM *vm) {
    Msg m;
    m.type = 5;
    m.val = (u32)vm->stk[vm->sp];
    m.x = vm->x0;
    func_001c4640(&m);
    vm->sp--;
    return 2;
}

s32 func_001cd778(VM *vm) {
    Msg m;
    m.type = 0;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    func_001c6720();
    D_00389C90.f3078 |= 0x400;
    return 2;
}

s32 func_001cd830(VM *vm) {
    Msg m;
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
    Msg m;
    m.type = 6;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cda60(VM *vm) {
    Msg m;
    m.type = 7;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdaa8(VM *vm) {
    Msg m;
    m.type = 8;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdaf0(VM *vm) {
    Msg m;
    m.type = 9;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdb38(VM *vm) {
    Msg m;
    m.type = 10;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdb80(VM *vm) {
    Msg m;
    m.type = 11;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdbc8(VM *vm) {
    Msg m;
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
    Msg m;
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
