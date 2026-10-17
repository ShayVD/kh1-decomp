/* libkernl: interrupt enable (DIntr, its pair at 0x0025F338, is in
 * nonmatchings/). sdk segment, ee-gcc 2.9-991111. */

#define SR_EIE 0x10000

/* Enable interrupts; returns whether they were enabled before. */
int EIntr(void) {
    int eie;

    __asm__ volatile("mfc0 %0, $12" : "=r"(eie));
    eie &= SR_EIE;
    __asm__ volatile("ei");

    return eie != 0;
}
