/* Likely the Trinity marks, default flags (docs/modules.md "Session 52";
 * the name is a guess: five mark kinds in D_00351A30, a check that both
 * partners are near, "xl_limit.dat"): the use counters
 * D_00304BE8->cnt_848[i] (func_001586a8), the available-kinds mask
 * D_005516EC (func_001586f0), the calls into the code loaded at D_00F20000
 * (func_00158af0).  The rest is in trinity.nostrict.c.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/thread.h"
#include "data/bss_0055.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002C58A0.h"
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350CE0.h"

/* func_001586a8 (from hand/text_00150000_h10.c). */
void func_001586a8(s32 i) {
    if (D_00304BE8->cnt_848[i] < 9999) D_00304BE8->cnt_848[i]++;
}

/* func_001586d8 (from auto/text_00150000.c). */
u16 func_001586d8(s32 arg0) {
    return M2C_FIELD(((arg0 * 2) + ((s32)D_00304BE8)), u16 *, 0x848);
}

/* func_001586f0 (from hand/text_00150000_h10.c). */
extern s32 D_005516EC;
s32 func_0013c968(s32, s32);
void func_001586f0(void) {
    s32 i;
    u8 *p = D_00351A30.b;
    D_005516EC = 0;
    for (i = 0; i < 5; i++, p += 2) {
        if (func_0013c968(*p, 0)) D_005516EC |= 1 << i;
    }
}

/* func_00158ad0 (from auto/text_00150000_3.c). */
void func_00131498(s32, s32);
void func_00158ad0(s32 arg0) {
    func_00131498(arg0, D_005516E8);
}

/* func_00158af0 (from hand/text_00150000_h10.c). */
typedef struct { u32 lo:16; u32 b16:1; u32 m:6; u32 b23:1; u32 hi:8; } Flg2C5958;
typedef union { u32 w; Flg2C5958 f; } U2C5958;
extern U2C5958 D_002C5958;
extern s32 *D_005516E4;
s32 D_00F20000(); /* code at a fixed address (overlay) */
void func_001412f8(s32, s32);
void func_00158af0(s32 a, s32 b) {
    volatile u32 *f = &D_002C5958.w;
    *f = (*f | 0x10000) & ~0x800000;
    func_00131498(a, D_005516E8);
    D_00F20000(b, (s32)D_005516E4 + D_005516E4[b + 2]);
    func_001412f8(a, (*(Cfg_308cdc **)&D_00308CDC)->hF4[b]);
}

/* func_00158d30 (from auto/text_00150000.c). */
s32 func_00155a90();
s32 func_00158c78();
s32 func_00158d30(void) {
    s32 var_s0;

    var_s0 = 0;
    if (func_00158c78() != 0) {
        var_s0 = func_00155a90() == 0;
    }
    return var_s0;
}

/* func_00158d70 (from auto/text_00150000_1.c). */
extern s32 D_00351A48;
#define func_00158d30 ((s32 (*)()) func_00158d30)
void func_00158d70(void) {
    if (func_00158d30() != 0) {
        D_00351A48 = 5;
        return;
    }
    D_00351A48 = 0;
}
#undef func_00158d30

/* func_00158db0 (from auto/text_00150000_1.c). */
#define func_00158d30 ((s32 (*)()) func_00158d30)
void func_00158db0(void) {
    if (func_00158d30() != 0) {
        PlatFlushCache(2);
        D_00351A48 = 3;
        return;
    }
    D_00351A48 = 0;
}
#undef func_00158d30

/* func_001590a8 (from hand/text_00150000_h10.c). */
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
void func_00158ec8(void);
void func_001590a8(void) {
    Flg2C5958 *f = &D_002C5958.f;
    if (f->b16) {
        D_00F20000(6, 0);
    }
    D_00351A48 = 0;
    f->b16 = 0;
    f->b23 = 0;
    func_001586f0();
    if (func_0011ef38(func_00158ec8) == 0) {
        func_0011ef10(0xCF08, func_00158ec8);
    }
}

