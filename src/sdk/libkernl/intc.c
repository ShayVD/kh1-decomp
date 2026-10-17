/* libkernl: interrupt and DMA channel enable/disable, wrapped around the
 * kernel calls (syscall.s) with interrupts held off. sdk segment, ee-gcc
 * 2.9-991111. */

#define SR_EIE 0x10000

int DIntr(void);
int EIntr(void);
int _EnableIntc(int);
int _DisableIntc(int);
int _EnableDmac(int);
int _DisableDmac(int);
int _iEnableIntc(int);
int _iDisableIntc(int);
int _iEnableDmac(int);
int _iDisableDmac(int);

#define LOCKED_CALL(call)                              \
    int eie, res;                                      \
                                                       \
    __asm__ volatile("mfc0 %0, $12" : "=r"(eie));      \
    eie &= SR_EIE;                                     \
    if (eie)                                           \
        DIntr();                                       \
    res = call;                                        \
    __asm__ volatile("sync.l");                        \
    if (eie)                                           \
        EIntr();                                       \
    return res

#define SYNCED_CALL(call)                              \
    int res;                                           \
                                                       \
    res = call;                                        \
    __asm__ volatile("sync.l");                        \
    return res

int DisableIntc(int ch) {
    LOCKED_CALL(_DisableIntc(ch));
}

int EnableIntc(int ch) {
    LOCKED_CALL(_EnableIntc(ch));
}

int DisableDmac(int ch) {
    LOCKED_CALL(_DisableDmac(ch));
}

int EnableDmac(int ch) {
    LOCKED_CALL(_EnableDmac(ch));
}

int iEnableIntc(int ch) {
    SYNCED_CALL(_iEnableIntc(ch));
}

int iDisableIntc(int ch) {
    SYNCED_CALL(_iDisableIntc(ch));
}

int iEnableDmac(int ch) {
    SYNCED_CALL(_iEnableDmac(ch));
}

int iDisableDmac(int ch) {
    SYNCED_CALL(_iDisableDmac(ch));
}
