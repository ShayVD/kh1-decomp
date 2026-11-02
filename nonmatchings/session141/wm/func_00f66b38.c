/* 14 words (score 28; was 15/30). Round 31 wwm2: hill2 over the four stores (the [3] store first, the [0] store last). The a1/a2/a3 register choice is still off by one; ctx2 has no callees to try. Earlier header: 15 words (score 30; same size, registers only). Closes a DMA packet: three zero words and (qwc-1)|0x50000000 through D_0108F034, with a reload for every store. The original puts the D_0108F034 address in a2, 0x50000000 in a3 and the result in a1 (as if a0/a1 were busy); ours starts at a1. Tried computing n before, after or inline, >>4 and /16 forms, a local copy of the pointer, extra unused params, all modes. A 10-minute -j1 permuter run only reached hand.py score 28. */
#include "ovl.h"

extern u32 *D_0108F034;

KH1_V0(u32) func_00f66b38(u32 *end) {
    u32 n = ((u32)end - (u32)D_0108F034) / 16 - 1;

    D_0108F034[3] = n | 0x50000000;
    D_0108F034[1] = 0;
    D_0108F034[2] = 0;
    D_0108F034[0] = 0;
    KH1_V0_RETURN(n + 1); /* v0 still holds the qword count */
}
