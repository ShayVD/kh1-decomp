/* sceCdRead: MATCH (sdk/gcc991111, checkfile) only with an empty __asm__ volatile("") between the two fail-path stores (keeps sw 654 / sw 630 / lw 628 order and the lw in the jal slot). Context ctx.h = nonmatchings/session6/w6_28__ctx.h. Lead decides. */
/* Context: near/ctx.h (header of src/sdk/gcc991111/text_00260000_s2.c plus extra declarations). */
#include "ctx.h"
s32 sceCdRead(u32 lbn, u32 sectors, void *buf, CdRMode *mode) {
    CdReadArg *a = &D_0046C700;
    s32 size;
    if (!(D_0046C634 & 1)) {
        if (func_00269f38() == 6) return 0;
    }
    if (!func_00269dc8(4)) return 0;
    a->lbn = lbn;
    a->sectors = sectors;
    a->buf = buf;
    a->mode.trycount = mode->trycount;
    a->mode.spindlctrl = mode->spindlctrl;
    a->mode.datapattern = mode->datapattern;
    a->x10 = D_0046D700;
    a->x14 = D_0046D7C0;
    switch (mode->datapattern) {
    case 1:
        size = sectors * 2328;
        break;
    case 2:
        size = sectors * 2340;
        break;
    case 0:
    default:
        size = sectors << 11;
        break;
    }
    D_0046D7C0[0] = 0;
    if (!(VS(D_0046C634) & 2)) func_00260738(buf, size);
    func_00260738(D_0046D700, 144);
    func_00260738(a, 24);
    func_00260738(D_0046D7C0, 4);
    if (D_0046C610 > 0) PRINTF(D_00493290);
    VS(D_0046C654) = 1;
    VS(D_0046C630) = 1;
    if (sceSifCallRpc(D_0046D7D0, 1, 1, a, 24, 0, 0, func_00269790, D_0046D700) < 0) {
        D_0046C654 = 0;
        __asm__ volatile("");
        D_0046C630 = 0;
        SignalSema(D_0046C628);
        return 0;
    }
    if (D_0046C610 > 0) PRINTF(D_004932A8);
    return 1;
}
