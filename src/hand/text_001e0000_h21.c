#include "common.h"
#include "platform/math.h"
#include "data/bss_0063.h"

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
    u8 pad0[0x34c];
    s32 a34c[7];
    s32 a368[0x5a][4];
    u8 pad[0xad1 - 0x368 - 0x5a * 16];
    u8 name[10];
    u8 pad2[8];
    u8 fl[0x20];
    u8 fl2[0x11];
    s32 tbl[32][5];
    u32 w[11];
    u8 fl3[4];
    u32 dc4;
    u8 fl5[4];
    s32 dcc;
    s32 dd0;
    u32 dd4;
} Sv;
Sv *func_00232cc0(s32);
typedef struct { f32 x, y, z; } V3;
#include "data/types/text_001e0000_h21.h"
extern S10 D_004908E0;
extern S10 D_00490900;

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

s32 func_001eb910(VM *vm) {
    s32 a = vm->stk[vm->sp - 1];
    s32 b = vm->stk[vm->sp] - 1;
    Sv *v = func_00232cc0(1);
    vm->sp--;
    vm->stk[vm->sp] = v->tbl[a][b];
    return 2;
}

s32 func_001eb9a8(s32 a, s32 b) {
    s32 s = 31 - b;
    return (func_00232cc0(1)->w[a] >> s) & 1;
}

void func_001eb9f8(s32 a, s32 b, s32 on) {
    s32 s = 31 - b;
    Sv *v = func_00232cc0(1);
    if (on) v->w[a] |= 1 << s;
    else v->w[a] &= ~(1 << s);
}

s32 func_001eba80(VM *vm) {
    s32 a = vm->stk[vm->sp - 1];
    s32 b = vm->stk[vm->sp];
    s32 s = 32 - b;
    func_00232cc0(1)->w[a] |= 1 << s;
    vm->sp -= 2;
    return 2;
}

s32 func_001ebb10(VM *vm) {
    s32 a = vm->stk[vm->sp - 1];
    s32 b = vm->stk[vm->sp];
    s32 s = 32 - b;
    func_00232cc0(1)->w[a] &= ~(1 << s);
    vm->sp -= 2;
    return 2;
}

s32 func_001ebba0(VM *vm) {
    s32 b = vm->stk[vm->sp];
    s32 a = vm->stk[vm->sp - 1];
    s32 s = 32 - b;
    Sv *v = func_00232cc0(1);
    vm->sp--;
    vm->stk[vm->sp] = (v->w[a] >> s) & 1;
    return 2;
}

s32 func_001ebc38(s32 n) {
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    return (func_00232cc0(1)->fl3[q] >> s) & 1;
}

s32 func_001ebd48(VM *vm) {
    s32 n = vm->stk[vm->sp];
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    func_00232cc0(1)->fl3[q] |= 1 << s;
    vm->sp--;
    return 2;
}

s32 func_001ebde0(VM *vm) {
    s32 n = vm->stk[vm->sp];
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    vm->stk[vm->sp] = (func_00232cc0(1)->fl3[q] >> s) & 1;
    return 2;
}

s32 func_001ec040(VM *vm) {
    Sv *v = func_00232cc0(1);
    if (vm->stk[vm->sp]) v->dc4 |= 2;
    else v->dc4 &= ~2;
    vm->sp--;
    return 2;
}

s32 func_001ec258(s32 n) {
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    return (func_00232cc0(1)->fl5[q] >> s) & 1;
}

void func_001ec2c0(s32 n, s32 on) {
    s32 q = n / 8;
    s32 s = 7 - (n % 8);
    Sv *v = func_00232cc0(1);
    if (on) v->fl5[q] |= 1 << s;
    else v->fl5[q] &= ~(1 << s);
}

s32 func_001ec3f8(VM *vm) {
    Sv *v = func_00232cc0(1);
    if (vm->stk[vm->sp]) v->dc4 |= 8;
    else v->dc4 &= ~8;
    vm->sp--;
    return 2;
}

void func_001ec570(s32 n, s32 on) {
    Sv *v = func_00232cc0(1);
    if (on) v->dd4 |= 1 << (31 - n);
    else v->dd4 &= ~(1 << (31 - n));
}

typedef struct { u8 pad[27]; u8 f1b; } Sv2;
void func_001ec610(s32 n, s32 on) {
    Sv2 *v = (Sv2 *)func_00232cc0(2);
    if (on) v->f1b |= 1 << n;
    else v->f1b &= ~(1 << n);
}

void func_001ba2a8(s32, u8 *);
s32 func_001ec678(void) {
    S10 t = D_00490900;
    Sv *v = func_00232cc0(1);
    u32 i;
    for (i = 0; i < 10; i++) {
        v->name[i] = t.c[i];
    }
    func_001ba2a8(0, v->name);
    return 2;
}

s32 func_001ec6f8(s32 a, s32 b) {
    u8 *v = (u8 *)func_00232cc0(1);
    s32 off;
    if (b == 0) off = a * 4 + 0x34c;
    else off = (a * 4 + b) * 4 + 0x368;
    return *(s32 *)(v + off);
}

void func_001ec758(s32 a, s32 b, s32 x) {
    u8 *v = (u8 *)func_00232cc0(1);
    s32 off;
    if (b == 0) off = a * 4 + 0x34c;
    else off = (a * 4 + b) * 4 + 0x368;
    *(s32 *)(v + off) = x;
}

typedef struct { u8 pad0[4]; s8 b4; u8 pad5[11]; s32 f10; u8 pad14[4]; s32 f18; u8 pad1c[0x2c]; } Ent48;
extern Ent48 D_0063EE40[4];
void FlushCache(s32);
s32 func_001eced0(s32 id) {
    s32 i;
    Ent48 *e;
    FlushCache(0);
    for (e = D_0063EE40, i = 0; i < 4; i++, e++) {
        if (e->b4 != 0 && e->f10 == id) return e->f18;
    }
    return 0;
}

extern s8 D_0063F640[]; /* src/data/bss_0063.c: u8 D_0063F640[256] */
s32 func_001ecf40(s8 *dst) {
    s32 i;
    s8 *p;
    for (i = 0; i < 255; i++) *dst++ = D_0063F640[i];
    D_0063F640[255] = 0;
    if (D_0063F640[0] == 0) return 0;
    p = &D_0063F640[255];
    for (i = 255; i >= 0; i--) *p-- = 0;
    return 1;
}

f32 func_001edc80(V3 *a, V3 *b) {
    V3 d;
    d.x = a->x - b->x;
    d.y = a->y - b->y;
    d.z = a->z - b->z;
    return PlatSqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
}

u32 func_001edd88(u32 c, s32 s) {
    u8 *p = (u8 *)&c;
    u32 a;
    if (s != 128) {
        a = ((c >> 24) * s) >> 7;
        if (a > 255) a = 255;
        p[3] = a;
    }
    return c;
}

u32 func_001edf40(u32 x, u32 y) {
    u32 res;
    u8 *r = (u8 *)&res;
    u8 *p = (u8 *)&x;
    u8 *q = (u8 *)&y;
    res = (res & ~0xff) | ((u32)(p[0] + q[0]) >> 1);
    r[1] = (p[1] + q[1]) >> 1;
    r[2] = (p[2] + q[2]) >> 1;
    r[3] = (p[3] + q[3]) >> 1;
    return res;
}

#include "data/pieces/D_002BBDF4.h"
extern f32 D_002BBDEC;
u32 func_001ee118(void) {
    return *(volatile u32 *)&D_002BBDF4 * D_002BBDEC;
}
#include "data/pieces/D_00389C90.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDEC.h"
#include "data/pieces/D_004908E0.h"
#include "data/pieces/D_00490900.h"
