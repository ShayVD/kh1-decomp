#include "common.h"

typedef struct { s32 x, y; u8 pad[0x18]; } Vtx20;
typedef struct { u8 pad[0x60]; Vtx20 v[4]; } S631620;

typedef struct {
    s32 x0;
    void *obj;
    f32 v08[3];
    f32 f14;
    f32 f18;
    f32 f1c;
    f32 f20;
    u8 pad24[0x15c];
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    union { u64 x; s32 i[2]; } flags;
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
typedef struct {
    u8 pad[0xad1];
    u8 name[10];
    u8 pad2[8];
    u8 fl[0x20];
    u8 fl2[0x11];
    s32 tbl[32][5];
    u32 w[11];
    u8 fl3[4];
} Sv;
Sv *func_00232cc0(s32);
typedef struct { s8 c[10]; } S10;
extern S10 D_004908E0;

extern s32 D_00631560;
extern volatile u32 D_002C5958;
extern u64 D_0038CD00;
extern s32 D_002E26A0;
extern S631620 D_00631620;

s32 func_0011e340(s32);
void func_00146928(s32);
s32 func_0011cdf0(s32, s32, void *);
s32 func_0011ef10(s32, void *);
void func_001e8e68(void);
void func_001e8e38(void);
void func_001557d0(void);
s32 func_00123158(s32, s32);
s32 func_0011c820(void);

s32 func_001e8ed8(s32 a0, s32 a1, s32 a2) {
    D_00631560 = a2;
    if (func_0011e340(0) == 0) {
        func_00146928(-6);
        func_00146928(-7);
        D_002C5958 |= 0x40000;
        return func_0011cdf0(-8, D_00631560, func_001e8e38);
    }
    return func_0011ef10(0xc352, func_001e8e68);
}

s32 func_001e9028(void) {
    return ((s32)(D_0038CD00 >> 55) & 1) ? 4 : 2;
}

s32 func_001e91c0(void) {
    if (func_0011e340(0) == 0) {
        func_001557d0();
        return 2;
    }
    return 4;
}

s32 func_001e9238(void) {
    s32 r = func_00123158(D_002E26A0, 0);
    while (r) r = func_00123158(D_002E26A0, r);
    return 2;
}

s32 func_001e9288(void) {
    return func_0011c820() ? 4 : 2;
}

void func_001e97d8(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 x0 = (a0 + 0x700) << 4;
    s32 y0 = (a1 + 0x740) << 4;
    s32 x1 = (a0 + a2 + 0x700) << 4;
    s32 y1 = (a1 + a3 + 0x740) << 4;
    D_00631620.v[0].x = x0;
    D_00631620.v[0].y = y0;
    D_00631620.v[1].x = x1;
    D_00631620.v[1].y = y0;
    D_00631620.v[2].x = x0;
    D_00631620.v[2].y = y1;
    D_00631620.v[3].x = x1;
    D_00631620.v[3].y = y1;
}

void func_001eac68(void) {
    S10 t = D_004908E0;
    u8 *p = func_00232cc0(1)->name;
    u32 i;
    for (i = 0; i < 10; i++) {
        *p++ = t.c[i];
    }
}

s32 func_001eb038(s32 n) {
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    return (func_00232cc0(1)->fl[q] >> s) & 1;
}

void func_001eb0a0(s32 n, s32 on) {
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    Sv *v = func_00232cc0(1);
    if (on) v->fl[q] |= 1 << s;
    else v->fl[q] &= ~(1 << s);
}

s32 func_001eb140(VM *vm) {
    s32 n = vm->stk[vm->sp];
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    func_00232cc0(1)->fl[q] |= 1 << s;
    vm->sp--;
    return 2;
}

s32 func_001eb1d8(VM *vm) {
    s32 n = vm->stk[vm->sp];
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    func_00232cc0(1)->fl[q] &= ~(1 << s);
    vm->sp--;
    return 2;
}

s32 func_001eb278(VM *vm) {
    s32 n = vm->stk[vm->sp];
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    vm->stk[vm->sp] = (func_00232cc0(1)->fl[q] >> s) & 1;
    return 2;
}

s32 func_001eb318(s32 n) {
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    return (func_00232cc0(1)->fl2[q] >> s) & 1;
}

s32 func_001eb380(VM *vm) {
    s32 n = vm->stk[vm->sp];
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    func_00232cc0(1)->fl2[q] |= 1 << s;
    vm->sp--;
    return 2;
}

void func_001eb418(s32 n, s32 on) {
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    Sv *v = func_00232cc0(1);
    if (on) v->fl2[q] |= 1 << s;
    else v->fl2[q] &= ~(1 << s);
}

s32 func_001eb4b8(VM *vm) {
    s32 n = vm->stk[vm->sp];
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    vm->stk[vm->sp] = (func_00232cc0(1)->fl2[q] >> s) & 1;
    return 2;
}

s32 func_001eb558(VM *vm) {
    Sv *v = func_00232cc0(1);
    s32 i, c;
    for (i = 0, c = 0; i < 100; i++) {
        s32 q = i / 8;
        s32 s = 7 - (i % 8);
        c += (v->fl2[q] >> s) & 1;
    }
    vm->sp++;
    vm->stk[vm->sp] = c;
    return 2;
}
