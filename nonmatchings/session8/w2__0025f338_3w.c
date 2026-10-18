/* 3w, sdk/gcc991111_as296: plain goto loop + __asm__ volatile(".p2align 3") before the loop label (draft w23 4w used do{}while(0) for the alignment; this keeps the 0x10000 mask li inside the loop like orig). Left: loop block mfc0/mask regs swapped (ours mfc0 v1, lui v0; orig mfc0 v0, lui v1). Using a block-local st for the loop mfc0 fixes the loop but then block 0 flips (eie must stay a global pseudo for block 0, loop value local). The .p2align asm emits only the padding nop. */
#include "common.h"
#define MFC0(x) __asm__ volatile("mfc0 %0, $12" : "=r"(x))
int DIntr(void) {
    int eie, res;
    MFC0(eie);
    eie &= 0x10000;
    res = eie != 0;
    if (eie) {
        __asm__ volatile(".p2align 3");
    loop:
        __asm__ volatile("di");
        __asm__ volatile("sync.p");
        MFC0(eie);
        if (eie & 0x10000) goto loop;
    } else
        res = 0;
    return res;
}
