/* The heaps: the main heap D_004F45B0 of 128-byte aligned blocks over
 * D_00820000 (func_00121e28 allocates for an owner pointer, func_00121eb0
 * frees the last, func_00121c78 the set up, func_00121b98 the ageing pass,
 * func_00121d00 / func_00121d60 / func_00121de0 the block list) and the
 * scratchpad stack D_004F6EB8 at 0x70000000 (func_00122028 resets it,
 * func_00122048 pushes an aligned frame, func_001220b8 pops). Flag mode:
 * nostrict (the other modes are in the sibling files). Read from the code,
 * not proved by a boot (docs/modules.md "Session 54"). */
#include "common.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004E.h"
#include "data/bss_004F.h"
#include "data/types/nostrict_text_00110000_s6_04_p.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002C58B0.h"
#include "data/types/nostrict_text_00110000_s6_04.h"
#include "data/pieces/D_002C5C48.h"

/* func_00121c78 (from hand/nostrict/text_00110000_s6_04.c). */
typedef struct { s32 x0; void *x4; s32 x8; s32 xc; s32 x10; } E20;
extern E20 D_004F45B0[];
extern E20 *D_004F6DB0;
extern u8 D_00820000[];
s32 func_00121b98(void);
typedef struct { s16 x0; s16 x2; } Tsk;
Tsk *func_0011ef10(s32, s32 (*)(void));
void func_00121c78(void) {
    E20 *p;
    s32 i;
    for (i = 1; i < 512; i++) D_004F45B0[i].x4 = 0;
    p = D_004F45B0;
    D_004F6DB0 = p + 1;
    p->x4 = D_00820000;
    p->xc = 0;
    p->x10 = 0;
    p->x8 = 0;
    func_0011ef10(200000, func_00121b98)->x2 = -1;
}

