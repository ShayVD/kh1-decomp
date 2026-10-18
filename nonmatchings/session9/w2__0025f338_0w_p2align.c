#include "common.h"

/* DIntr 0x25f338 (sdk/gcc991111_as296). Needs __asm__ volatile(".p2align 3") before the loop label: it emits only the alignment nop that is in the binary (a real C loop gets the alignment but loop.c hoists the 0x10000 mask). The block-0 eie must be a global pseudo (res = eie != 0 inside the then-block) and the loop value a block-local st. */
#define MFC0(x) __asm__ volatile("mfc0 %0, $12" : "=r"(x))
int DIntr(void) {
    int eie, res;
    MFC0(eie);
    eie &= 0x10000;
    if (eie) {
        res = eie != 0;
        __asm__ volatile(".p2align 3");
    loop:
        __asm__ volatile("di");
        __asm__ volatile("sync.p");
        { int st; MFC0(st); if (st & 0x10000) goto loop; }
    } else
        res = 0;
    return res;
}
