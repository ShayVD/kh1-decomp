/* Lookups into the game's data tables (D_00547BA0 ... D_00547BB0,
 * D_00533BA0, D_00308874, D_00308C70): func_00147860 an item's stat bonuses,
 * func_00147840 an item's record, func_001478e0 sets the tables up. Flag
 * mode: default (the other modes are in the sibling files). Read from the
 * code, not proved by a boot (docs/modules.md "Session 53"). */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0054.h"
#include "data/pieces/D_00350CE0.h"
#include "common.h"
#include "data/bss_0053.h"
#include "vm/script_vm.h"
#include "data/types/text_00140000_h8.h"
#include "data/pieces/D_0035C710.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00350CE8.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00304C70.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_00350D88.h"

/* func_00147730 (from auto/text_00140000.c). */
s32 func_001477c8(M2C_UNK);
s32 func_00147730(s32 arg0) {
    return func_001477c8(0xC8A8) + (arg0 * 2);
}

/* func_00147760 (from auto/text_00140000.c). */
s32 func_00147808();
#define func_00147808 ((M2C_UNK (*)(s32)) func_00147808)
void func_00147760(s32 arg0) {
    func_00147808(arg0 + 0x127);
}
#undef func_00147808

/* func_00147778 (from auto/text_00140000.c). */
extern s32 D_00547BB0;
s32 func_00147778(s32 arg0) {
    return D_00547BB0 + (arg0 * 2);
}

/* func_00147790 (from hand/text_00140000_h8.c). */
extern s32 D_00308874[];
void func_00176ba8(void *, s32);
void func_00147790(s32 i) {
    func_00176ba8((u8 *)D_00308874 - 4 + D_00308874[i], 0);
}

/* func_001477e0 (from auto/text_00140000_4.c). */
extern M2C_UNK D_00308C70;
#define func_001477c8 ((M2C_UNK (*)(s32)) func_001477c8)
void func_001477e0(s32 arg0) {
    func_001477c8(*(M2C_UNK *)((s8 *)&D_00308C70 + (arg0 * 4)));
}
#undef func_001477c8

/* func_00147808 (from auto/text_00140000_15.c). */
s32 func_00147808(s32 arg0) {
    return *(M2C_UNK *)((s32) ((arg0 * 4)) + (s32) (func_001477c8(0x258)));
}

/* func_00147840 (from auto/text_00140000.c). */
extern s32 D_00547BA0;
s32 func_00147840(s32 arg0) {
    return (D_00547BA0 + (arg0 * 0x14)) - 0x14;
}

/* func_00147860 (from auto/text_00140000_1.c). */
extern s32 D_00547BA4;
#define func_00147840 ((void *(*)()) func_00147840)
s32 func_00147860(void) {
    return D_00547BA4 + (M2C_FIELD(func_00147840(), s16 *, 6) * 0x16);
}
#undef func_00147840

/* func_001478a0 (from auto/text_00140000.c). */
extern s32 D_00547BA8;
s32 func_001478a0(s32 arg0) {
    return (D_00547BA8 + ((arg0 & ~0x80) * 0xC)) - 0xC;
}

/* func_001478c8 (from auto/text_00140000.c). */
extern s32 D_00547BAC;
s32 func_001478c8(s32 arg0) {
    return D_00547BAC + (arg0 * 0x10);
}

