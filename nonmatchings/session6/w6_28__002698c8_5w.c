/* 5 words off (sdk/gcc991111): original stores D_0046C654=-1 before loading D_0046C620 for SignalSema (load in jal slot); ours hoists the load above the store. Volatile on either breaks slot fill. */
/* Context: near/ctx.h (header of src/sdk/gcc991111/text_00260000_s2.c plus extra declarations). */
#include "ctx.h"
void func_002698c8(void) {
    s32 e;
    if (D_0046C614) {
        D_0046C654 = -1;
        SignalSema(D_0046C620);
    }
    DeleteSema(D_0046C628);
    DeleteSema(D_0046C62C);
    DeleteSema(D_0046C620);
    e = DIntr();
    func_00260430(0x80000012);
    if (e) EIntr();
}
