/* DIntr (0x0025F338), closest draft (ee-gcc 2.96, src/sdk/libkernl/ flags).
 * The goto loop stops gcc hoisting the 0x10000 mask (the original rebuilds
 * it inside the loop); the return path still differs: the original returns
 * `res` through two `jr ra; move v0,a0` exits, with `move a0,zero` on the
 * interrupts-off path. ps2sdk's do/while form hoists the mask under every
 * ee-gcc tried (2.96, 2.9-991111a/-01, 2.9-990721). */
#define SR_EIE 0x10000

/* Disable interrupts; returns whether they were enabled. */
int DIntr(void) {
    int eie, res;

    __asm__ volatile("mfc0 %0, $12" : "=r"(eie));
    eie &= SR_EIE;
    res = eie != 0;

    if (!eie)
        goto none;

    __asm__(".p2align 3");
loop:
    __asm__ volatile("di");
    __asm__ volatile("sync.p");
    __asm__ volatile("mfc0 %0, $12" : "=r"(eie));
    eie &= SR_EIE;
    if (eie)
        goto loop;
    return res;

none:
    res = 0;
    return res;
}

