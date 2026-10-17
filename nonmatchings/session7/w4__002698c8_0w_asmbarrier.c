/* MATCH (sdk/gcc991111, checkfile) only with an empty __asm__ volatile("") between D_0046C654 = -1 and SignalSema (keeps the store before the lw that goes in the jal slot). Context ctx.h = nonmatchings/session6/w6_28__ctx.h. Lead decides. */
/* Context: near/ctx.h (header of src/sdk/gcc991111/text_00260000_s2.c plus extra declarations). */
#include "ctx.h"
void func_002698c8(void) {
    s32 e;
    if (D_0046C614) {
        D_0046C654 = -1;
        __asm__ volatile("");
        SignalSema(D_0046C620);
    }
    DeleteSema(D_0046C628);
    DeleteSema(D_0046C62C);
    DeleteSema(D_0046C620);
    e = DIntr();
    func_00260430(0x80000012);
    if (e) EIntr();
}
