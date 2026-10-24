/* Definitions of the shared bss names in include/data/bss_004E.h. */
#include "data/bss_004E.h"
#include "data/bss_004E_mixed.h"
#include "data/bss_004E_typed.h"

s32 D_004E0428[0x802] ALIGNED(8);
s32 D_004E3438 ALIGNED(8);
s32 D_004E343C ALIGNED(4);
s32 D_004E3440 ALIGNED(16);
s32 D_004E3448 ALIGNED(8);
s32 D_004E344C ALIGNED(4);
s32 D_004E3A40 ALIGNED(16);
s32 D_004E4280 ALIGNED(16);
s32 D_004E44F0 ALIGNED(16);
M2C_UNK *D_004E0420 ALIGNED(16);
s32 D_004E3444 ALIGNED(4);
u8 D_004E3A48[0x10] ALIGNED(8);
s32 D_004E44C0[0x2] ALIGNED(16);
u8 D_004E49E8[0x18] ALIGNED(8);
SndSlot *D_004E3450 ALIGNED(16);
Slot12 *D_004E3454 ALIGNED(4);
/* The 4 sound requests and, as a fifth Pair, the flags D_004E3A18 / D_004E3A1C: func_0011e1c8 writes entry [4]
 * when all four are taken (the original overwrites the flags). One definition, so the host does the same
 * (vita-port-plan 5.1i). */
Pair D_004E39F8[0x5] ALIGNED(8);
V4 D_004E3A20 ALIGNED(16);
V4 D_004E3A30 ALIGNED(16);
FileEnt D_004E4A00[0xe00] ALIGNED(64);
void (*D_004E3430)(void) ALIGNED(16);
void (*D_004E3434)(void) ALIGNED(4);
SndSlot D_004E3458[0x28] ALIGNED(8);
s32 D_004E4520 ALIGNED(16);
