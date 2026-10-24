/* Definitions of the shared bss names in include/data/bss_0054.h. */
#include "data/bss_0054.h"
#include "data/bss_0054_mixed.h"
#include "data/bss_0054_typed.h"

u32 D_0054C434 ALIGNED(4);
s32 D_0054C43C ALIGNED(4);
s32 D_0054F740 ALIGNED(16);
s32 D_00547BA0 ALIGNED(16);
s32 D_00547BA4 ALIGNED(4);
s32 D_00547BA8 ALIGNED(8);
s32 D_00547BAC ALIGNED(4);
u8 D_0054B808[0x10] ALIGNED(8);
s32 D_0054C438 ALIGNED(8);
u8 D_0054F970[0x10] ALIGNED(16);
W34Mdl3C D_00547C00[256] ALIGNED(64);
W34Mdl3C *D_0054B800 ALIGNED(16);
Ent9c D_0054C1B0[0x3] ALIGNED(16);
W34E3C D_0054C218[0x9] ALIGNED(8);
/* The 64 hit records D_0054C440 (atkhit, 0xc0 each, no C definition before) end at 0x0054F440, inside
 * areabox.c's group 0: the groups count from 1 (D_0054F438[k] is group k, D_0054F450 = D_0054F438[1] the 31
 * groups), entry 0 holds D_0054F440 ... D_0054F44C, and its first 8 bytes are record 63's last 8. One
 * definition for both (vita-port-plan 5.1i, 5.1j); the names are views (out/host/aliases.ld). */
u8 D_0054C440[0x32f8] ALIGNED(64);
Slot57_15d0 D_0054F750[8] ALIGNED(16);
f32 D_0054F738 ALIGNED(8);
void *D_0054F950 ALIGNED(16);
void *volatile D_00547BB0 ALIGNED(16);
void *D_0054C210 ALIGNED(16);
