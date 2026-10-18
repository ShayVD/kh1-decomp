#include "common.h"

#define SR_EIE 0x10000

/* DIntr 0x25f338: disable interrupts; returns whether they were enabled.
 * Plain C, same shape as _sbrk's inlined copy (src/sdk/libkernl/kernl.c):
 * the loop's own variable, eie still live after the loop (return eie != 0). */
int DIntr(void) {
    int eie, t;

    __asm__ volatile("mfc0 %0, $12" : "=r"(eie));
    eie &= SR_EIE;
    if (eie) {
        do {
            __asm__ volatile("di");
            __asm__ volatile("sync.p");
            __asm__ volatile("mfc0 %0, $12" : "=r"(t));
            t &= SR_EIE;
        } while (t);
    }
    return eie != 0;
}
