/* DIntr 0x25f338: 4 words off in sdk/gcc991111_as296 (C + cop0 asm statements; the session-5 draft was 12w and the lead exported it as hand asm). Structure, the .p2align-3 loop nop (loop notes from the do-while(0)), the `move a0,zero; jr ra; move v0,a0` exit (else res = 0, 2.96 gas fills the jr slot) all match. Left: loop.c hoists the 0x10000 mask out of the loop (orig rebuilds `lui v1,1; and v0,v0,v1` inside), so one extra li before the loop and the mfc0/and registers differ. A plain goto loop keeps the li inside but loses the loop alignment. No -fno-* flag stops the hoist. */
#include "common.h"
#define MFC0(x) __asm__ volatile("mfc0 %0, $12" : "=r"(x))
int DIntr(void) {
    int eie, res;
    MFC0(eie);
    eie &= 0x10000;
    res = eie != 0;
    if (eie) {
        do {
        loop:
            __asm__ volatile("di");
            __asm__ volatile("sync.p");
            MFC0(eie);
            if (eie & 0x10000) goto loop;
        } while (0);
    } else
        res = 0;
    return res;
}
