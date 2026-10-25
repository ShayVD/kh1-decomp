/* Definitions of the shared bss names in include/data/bss_0057.h. */
#include "data/bss_0057.h"
#include "data/bss_0057_mixed.h"
#include "data/bss_0057_typed.h"

s32 D_00574FB4 ALIGNED(4);
s32 D_00574FB8 ALIGNED(8);
s32 D_00575088 ALIGNED(8);
s32 D_0057508C ALIGNED(4);
f32 D_005758C0 ALIGNED(16);
s32 D_005739F8[0x32] ALIGNED(8);
/* A DMA packet area: the call tag, then D_00573AD0 (mdlgs.nostrict.c's 7 Pk1), then D_00573E40 (Pk2, no C
 * definition before): func_0015fa20 builds its packets over the first two, and D_00573E40's call tag calls
 * D_00573AC0, whose chain ends in a ret. The 7th Pk1 runs 0x10 into D_00573E40 (its "pad" is packet 6's ref
 * tag and the terminator after it): func_00162428's chain (func_0015f8c8's s->n & 7 packets of 0x80 and an
 * end tag) reaches +0x390. The last 0x10 (after Pk2's 0xc0) is what motion.nostrict.c's D_00573F10[n - 1] and
 * func_001636d0's D_00573F10[s1 - 1] would read for a bone number 0 (relcheck / layoutcheck REVIEWED). One
 * definition (vita-port-plan 5.1j, 5.1k); D_00573AD0 / D_00573E40 are views (out/host/aliases.ld). */
u8 D_00573AC0[0x450] ALIGNED(16);
s32 D_00575010[2] ALIGNED(16); /* partyai.c frees both tasks; [1] is D_00575014 (partyctl.nostrict.c). One definition (vita-port-plan 5.1i) */
void *D_00575780 ALIGNED(16);
void *D_00575784 ALIGNED(4);
u8 D_00575788[8] ALIGNED(8);
s32 D_00575890 ALIGNED(16);
f32 D_005758C4 ALIGNED(4);
f32 D_005758D0[4] ALIGNED(16);
f32 D_005758E0[4] ALIGNED(16);
u8 D_00575A00[0x10] ALIGNED(16);
f32 D_00575090[40][4] ALIGNED(16);
LockEA D_00575080 ALIGNED(16);
TalkEA D_00575310 ALIGNED(16);
Node6F D_00575528[30] ALIGNED(8);
S920 D_00575920 ALIGNED(16);
T44 D_005757B0[0x2] ALIGNED(16);
void *D_00575894 ALIGNED(4);
void *D_00574FC0[20] ALIGNED(64);
C03Act *D_00575328[0x80] ALIGNED(8);
