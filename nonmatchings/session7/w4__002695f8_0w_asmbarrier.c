/* MATCH (sdk/gcc991111, checkfile) but only with an empty __asm__ volatile("") barrier before the final store: it stops reorg from stealing the b-slot sw into the two beqz slots (beqzl). No plain-C construct found; lead decides if acceptable. Context: nonmatchings/session6/w6_28__ctx.h as ctx.h. */
#include "ctx.h"
void func_002695f8(void) {
    while (1) {
        WaitSema(D_0046C620);
        if (D_0046C654 == -1) {
            VS(D_0046C630) = 0;
            D_0046C654 = 0;
            D_0046C614 = 0;
            D_0067334C = 0;
            ExitDeleteThread();
        }
        if (D_0046C610 > 0) scePrintf(D_004930E0, D_00673340, D_0046C658);
        if (D_00673340 != 0) {
            if (VS(D_0046C658) != 0) ((void (*)(s32))D_00673340)(D_0046C658);
        }
        __asm__ volatile("");
        D_0046C630 = 0;
    }
}
