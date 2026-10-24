/* The player's moves by state (a guess from the code): func_001271b0 (called
 * from the player's move, src/obj/plctl.c) picks a handler by state
 * (func_00126c10, func_00126f18), with the move's motions (func_00125b68,
 * func_00125be8), effects and jump arcs (func_00125dc8), the state block
 * D_002E27C8 / D_002E3190; func_001252f8 checks the abilities
 * (func_0013c968) for the moves allowed. Flag mode: nofill (the other modes
 * are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 54"). */
#include "common.h"
#include "data/bss_004F.h"
#include "data/types/nofill_text_00110000_h53.h"
#include "data/pieces/D_00308CDC.h"

/* func_00127340 (from hand/nofill/text_00110000_h53.c). */
extern E7810 *D_004F7810;
extern f32 D_002E27CC;
extern f32 D_002E27D0;
f32 cosf(f32);
void *func_001477c8(s32);
void func_00127340(void) {
    D_002E27CC = (*(u32 **)&D_00308CDC)[2];
    D_004F77F4 = cosf((f32)((*(u32 **)&D_00308CDC)[0] >> 1) / 180.0f * 3.1415928f);
    D_004F77F0 = cosf((f32)((*(u32 **)&D_00308CDC)[1] >> 1) / 180.0f * 3.1415928f);
    D_002E27D0 = (*(u32 **)&D_00308CDC)[3];
    D_004F7810 = func_001477c8(0xa9f0);
}

