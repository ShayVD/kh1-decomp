/* Pad vibration, default flags (docs/modules.md "Session 51"): two players
 * (one per pad, D_005757B0[2], 0x2C bytes each) step a type-20 vibration
 * pattern (two channels of {time, level} pairs, one per motor) and write the
 * levels into the pad's actuator bytes D_002C5AD0[i][2..3] (src/pad/padrec.c's
 * pad state).  func_00176c60 stops pad i, func_00176ea8 resets both and
 * func_00176ee0 steps both (its per-frame task, registered by pppapi.c's
 * func_00175980).  padvib.nostrict.c starts a pattern (func_00176ba8) and
 * steps one pad (func_00176cc8).  A platform wrapper (docs/portability.md)
 * belongs around the actuator writes.  Read from the code, not proved by a
 * boot. */
#include "common.h"
#include "m2c.h"

/* func_00176c60 (from hand/text_00170000_s9_w7.c). */
typedef struct { u8 *a; u8 *b; s32 c; f32 d; f32 e; } F20;
typedef struct { void *h; F20 e[2]; } T44;
extern T44 D_005757B0[];
extern u8 D_002C5AD0[][112];
void *memset(void *, s32, u32);
/* func_00176c60: clears two bytes of the 112-byte record (the D_002C5AD2[i][j] pair
   that func_00176cc8 writes) and the 44-byte channel record. The chained assignment
   computes the [2] address first and the [3] address second, so sched1 issues the [3]
   add (it holds the REG_DEAD notes) first and reload_cse turns the [2] add into a copy. */
void func_00176c60(s32 i) {
    D_002C5AD0[i][2] = D_002C5AD0[i][3] = 0;
    memset(&D_005757B0[i], 0, sizeof(T44));
}

/* func_00176ea8 (from auto/text_00170000_8.c). */
#define D_005757B0 (*(M2C_UNK (*)) &D_005757B0)
void func_00176ea8(void) {
    memset(&D_005757B0, 0, 0x58);
    func_00176c60(0);
    func_00176c60(1);
}
#undef D_005757B0

/* func_00176ee0 (from auto/text_00170000_8.c). */
M2C_UNK func_00176cc8(M2C_UNK);
s32 func_00176ee0(void) {
    func_00176cc8(0);
    func_00176cc8(1);
    return 0;
}

