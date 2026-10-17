/* 4 words off (sdk/gcc991111): same fail-path issue as sceCdRead: orig keeps 'sw 654; lui; sw 630; jal SignalSema; lw a0,628' (load ordered after store, then in slot); ours hoists the lw. All-volatile matches except the volatile lw can't fill the jal slot. */
/* Context: near/ctx.h (header of src/sdk/gcc991111/text_00260000_s2.c plus extra declarations). */
#include "ctx.h"
s32 func_0026a9d0(s32 a) {
    CdReadArg *p = &D_0046C700;
    if (func_00269f38() == 6) return 0;
    if (!func_00269dc8(9)) return 0;
    p->lbn = a;
    func_00260738(p, 4);
    VS(D_0046C654) = 4;
    VS(D_0046C630) = 1;
    if (sceSifCallRpc(D_0046D7D0, 5, 1, p, 4, 0, 0, func_00269558, &D_0046C654) < 0) {
        D_0046C654 = 0;
        D_0046C630 = 0;
        SignalSema(D_0046C628);
        return 0;
    }
    return 1;
}
