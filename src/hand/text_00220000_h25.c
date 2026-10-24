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
u128 D_00648070[0x6] ALIGNED(16);
extern Slot D_00651310[10];
Pkt D_00650F40 ALIGNED(64);
extern u128 *D_00651200; /* src/data/bss_0065.c: s32 D_00651200 */
extern u128 *D_00651204; /* src/data/bss_0065.c: u8 *D_00651204 */

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
