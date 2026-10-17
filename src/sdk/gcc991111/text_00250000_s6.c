#include "common.h"

/* libkernl: interrupts enabled? (COP0 Status.IE clear -> 1) */
s32 func_00258c30(void)
{
    s32 sr;

    __asm__ volatile("mfc0 %0, $12" : "=r"(sr));
    return (sr ^ 1) & 1;
}

typedef struct { void (*func)(s32); s32 arg; } Hook;

/* libkernl: run an optional hook, then re-enable interrupts. */
void func_0025b2c0(s32 a, Hook *h)
{
    if (h->func != 0) {
        h->func(h->arg);
    }
    __asm__ volatile("sync");
    __asm__ volatile("ei");
}
