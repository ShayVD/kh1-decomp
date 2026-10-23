#include "common.h"
#include "data/bss_0064.h"

typedef int u128 __attribute__((mode(TI)));

/* 64-entry command ring at D_006477B0 (head D_00647FB8, id counter D_00647FC0) */
#include "data/types/text_00220000_h25.h"
#include "data/types/text_00220000_h25_p.h"
typedef struct { s32 used; s32 x; u8 pad[0xD8]; } Slot;
typedef struct { u8 pad[0x60]; u64 x60; u8 pad2[0x78]; u64 xe0; u8 tail[0x160 - 0xE8]; } Pkt;
s32 func_001ba3f0(s32);
void func_00237018(void *, s32, s32);
void func_002370c8(void *);
u128 *func_00237790(u8 *, u128 *, s32);
void func_0023c7a0(void);
s32 func_00243bd8(void);
s32 func_002448d8(void);
s32 func_00245228(void);
s32 func_00245f18(void);
s32 func_002474a8(void);
extern u128 D_00351E10[];
extern Str82A8 D_003F82A8;
extern Cmd D_006477B0[64];
extern s32 D_00647FB0;
extern s32 D_00647FB8;
extern s32 D_00647FC0;
extern s32 D_00647FC4;
extern s32 D_00647FD4;
extern s32 D_00647FD8;
extern s32 D_0064801C;
extern s32 (*D_00648034)(s32);
extern s32 D_00648038[5]; /* src/data/bss_0064.c: s32 D_00648038[0x6] */
extern f32 D_00648050[5];
u128 D_00648070[0x6] ALIGNED(16);
extern Slot D_00651310[10];
Pkt D_00650F40 ALIGNED(64);
extern u128 *D_00651200; /* src/data/bss_0065.c: s32 D_00651200 */
extern u128 *D_00651204; /* src/data/bss_0065.c: u8 *D_00651204 */

Str82A8 *func_00232fc8(u32 arg0) {
    D_003F82A8.e = arg0 / 10 + '0';
    D_003F82A8.f = arg0 % 10 + '0';
    D_003F82A8.e2 = arg0 / 10 + '0';
    D_003F82A8.f2 = arg0 % 10 + '0';
    return &D_003F82A8;
}

s32 func_00234018(s32 arg0, s32 arg1, s32 arg2) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 1;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[2] = arg2;
    return id;
}

s32 func_00234210(s32 arg0, s32 arg1, s32 arg2) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 4;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[2] = arg2;
    return id;
}

s32 func_00234290(s32 arg0, s32 arg1, s32 arg2) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 5;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[2] = arg2;
    return id;
}

s32 func_00234310(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 6;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[3] = arg3;
    return id;
}

s32 func_002343a8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 7;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[3] = arg3;
    return id;
}

s32 func_00234508(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 9;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_006477B0[i].a[0] = arg0;
    D_006477B0[i].a[1] = arg1;
    D_006477B0[i].a[2] = arg2;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[3] = arg3;
    return id;
}

s32 func_002347e0(s32 arg0) {
    s32 i = D_00647FB8;
    s32 id = D_00647FC0;
    D_006477B0[i].type = 13;
    D_00647FB8 = (i + 1) & 63;
    D_006477B0[i].id = id;
    D_00647FC0 = id + 1;
    D_006477B0[i].a[0] = arg0;
    return id;
}

void func_00236598(void) {
    D_00647FB0 = 0;
    D_00647FD8 = D_00647FD4;
    D_0064801C = D_00648034(D_00647FC4);
}

void func_00236618(void) {
    D_00648038[0] = 1484;
    D_00648038[1] = 12345;
    D_00648038[2] = 54321;
    D_00648038[3] = 765;
    D_00648038[4] = 9999;
    D_00648050[0] = 1.234f;
    D_00648050[1] = 2.345f;
    D_00648050[2] = 3.456f;
    D_00648050[3] = 4.567f;
    D_00648050[4] = 5.678f;
}

void func_002367a0(s32 arg0) {
    D_00648038[arg0] = ((s64)D_00648038[arg0] * 0x41C64E6D + 12345) & 0x7FFFFFFF;
}

void func_002368b0(s32 *arg0) {
    *arg0 = ((s64)*arg0 * 0x41C64E6D + 12345) & 0x7FFFFFFF;
}

void func_00238440(u8 *items, s32 count, s32 arg2) {
    s32 i;
    for (i = 0; i < count; i++) {
        u128 *end = func_00237790(items, D_00648070, arg2);
        items += 80;
        if (end != D_00648070) {
            *(s32 *)D_00648070 |= 0x70000000;
            func_00237018(D_00648070, end - D_00648070, 1);
        }
    }
}

s32 func_002394f8(void) {
    if (func_002448d8()) return 1;
    if (func_00245228()) return 1;
    if (func_00243bd8()) return 1;
    if (func_00245f18()) return 1;
    return func_002474a8() != 0;
}

Slot *func_0023c228(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        if (D_00651310[i].used == 0) {
            D_00651310[i].used = 1;
            D_00651310[i].x = 0;
            return &D_00651310[i];
        }
    }
    return 0;
}

s32 func_0023c8c8(void) {
    func_002370c8(&D_00650F40);
    D_00650F40.xe0 = 5;
    D_00650F40.x60 = 0x30003;
    func_00237018(&D_00650F40, 22, 1);
    D_00651204 = D_00351E10;
    D_00651200 = D_00351E10 + 1;
    func_0023c7a0();
    func_00237018(D_00651204, D_00651200 - D_00651204, 1);
    return 0;
}

/* needs make: uses rodata */

#include "data/bss_0064_typed.h"
#include "data/data_003F.h"
#include "data/pieces/D_003F6DF0.h"
#include "data/pieces/D_003F82A8.h"
