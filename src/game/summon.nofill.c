/* Likely the summons (a guess from the code): func_0013a910 asks whether
 * summon n is allowed (the leader's class flag, MP against the tuning table,
 * the world / room), the state D_0052AE54 loads the summon's two files named
 * from D_00304B00[D_0052AE50] (func_0013b3d0; code at D_00F20000), the
 * summon object D_0052AE38 of class 40 (func_0013bf20 registers it), the
 * party swap and its end (func_0013bb60, func_0013bd08), the fade
 * func_0013ab30. Flag mode: nofill (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002E27C8.h"

/* func_0013bb20 (from hand/nofill/text_00130000_s6_06.c). */
typedef struct { u8 pad[0x40]; s32 x40; s32 x44; s32 x48; } W606S6c;
typedef struct { u8 pad[0x6c]; W606S6c *x6c; } W606O26a0;
extern W606O26a0 *D_002E26A0_3bb20[3] __asm__("D_002E26A0");
#define D_002E26A0 D_002E26A0_3bb20
f32 func_0013bb20(void) {
    return (f32)((D_002E26A0[0]->x6c->x48 + (s32)(((*(u32 *)&D_002E27C8) >> 10) & 7)) * 3000);
}
#undef D_002E26A0

