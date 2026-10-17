/* libkernl C pieces: the vblank waits and the
 * low-level I/O newlib's reent wrappers call (_write/_read go to the DECI2
 * TTY, _sbrk grows the heap up to EndOfHeap()). sdk segment, ee-gcc
 * 2.9-991111. */

#define INTC_STAT ((volatile int *) 0x1000F000)
#define INTC_VBLANK_S 4
#define SR_EIE 0x10000

int DIntr(void);
int EIntr(void);
int SetVSyncFlag(volatile int *, volatile long *);

/* The DECI2 TTY (0x002592C0 opens it, 0x002590A0 writes, 0x002591F0
 * reads); opened on first use. */
extern int D_0046AE44;
int func_002592c0(void);
int func_002590a0(const void *, int);
int func_002591f0(void *, int);

int _write(int fd, const void *buf, int n) {
    if (fd == 1 || fd == 2) {
        if (!D_0046AE44) {
            if (!func_002592c0())
                return -1;
            D_0046AE44 = 1;
        }
        return func_002590a0(buf, n);
    }
    return -1;
}

int _read(int fd, void *buf, int n) {
    if (fd == 0) {
        if (!D_0046AE44) {
            if (!func_002592c0())
                return -1;
            D_0046AE44 = 1;
        }
        return func_002591f0(buf, n);
    }
    return -1;
}

/* The heap: D_0046AE48 is its current end (newlib's _sbrk_r calls this). */
extern char *D_0046AE48;
void *EndOfHeap(void);
int *__errno(void);

void *_sbrk(int incr) {
    int eie, t;
    char *end, *ret;

    /* DIntr() inlined: the mask is rebuilt inside the loop (as here, with
     * the loop's own variable). */
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

    end = D_0046AE48 + incr;
    if ((char *) EndOfHeap() < end) {
        *__errno() = 12; /* ENOMEM */
        if (eie)
            __asm__ volatile("ei");
        ret = (char *) -1;
    } else {
        ret = D_0046AE48;
        D_0046AE48 = end;
        if (eie)
            __asm__ volatile("ei");
    }
    return ret;
}

/* Clear INTC_STAT's vblank-start bit with interrupts off. (Written out as
 * plain statements: inside a do/while (0) the delay slots fill
 * differently.) */
#define CLEAR_VBLANK_S()          \
    i = DIntr();                  \
    *INTC_STAT = INTC_VBLANK_S;   \
    __asm__ volatile("sync.l");   \
    if (i)                        \
        EIntr()

/* Waits for the next vblank start. */
void func_002585f0(void) {
    int i;

    CLEAR_VBLANK_S();
    while (!(*INTC_STAT & INTC_VBLANK_S))
        ;
    CLEAR_VBLANK_S();
}

/* Waits for the next vblank start, or for the kernel's vsync flag
 * (SetVSyncFlag); returns the count the kernel stored with it. */
long func_00258680(void) {
    volatile int flag;
    volatile long count;
    int i;

    flag = 0;
    SetVSyncFlag(&flag, &count);
    CLEAR_VBLANK_S();
    while (!(*INTC_STAT & INTC_VBLANK_S) && !flag)
        ;
    CLEAR_VBLANK_S();
    return count;
}
