/* libkernl: data cache maintenance over an address range. Both walk all
 * 64 lines x 2 ways of the 8 KiB D-cache by index, read each line's tag
 * (cache 0x10, index load tag) and write back + invalidate (0x14) or just
 * invalidate (0x16) the lines whose address falls in [start, end]. sdk
 * segment, ee-gcc 2.9-991111. */

#define SR_EIE 0x10000
#define LINE_MASK 0xFFFFFFC0

int DIntr(void);
int EIntr(void);

#define CACHE_WAY(way, op)                                              \
    __asm__ volatile("sync.l");                                         \
    __asm__ volatile("cache 0x10, " #way "(%0)" : : "r"(i));            \
    __asm__ volatile("sync.l");                                         \
    __asm__ volatile("mfc0 %0, $28" : "=r"(tag));                       \
    tag = (tag & 0xFFFFF000) + i;                                       \
    if (tag >= start && tag <= end) {                                   \
        __asm__ volatile("sync.l");                                     \
        __asm__ volatile("cache " #op ", " #way "(%0)" : : "r"(i));     \
        __asm__ volatile("sync.l");                                     \
    }

void _SyncDCache(unsigned int start, unsigned int end) {
    int i;
    unsigned int tag;

    for (i = 0; i < 4096; i += 64) {
        CACHE_WAY(0, 0x14)
        CACHE_WAY(1, 0x14)
        __asm__ volatile("sync.l");
    }
}

void SyncDCache(void *start, void *end) {
    int eie;

    __asm__ volatile("mfc0 %0, $12" : "=r"(eie));
    eie &= SR_EIE;
    if (eie)
        DIntr();
    _SyncDCache((unsigned int) start & LINE_MASK, (unsigned int) end & LINE_MASK);
    if (eie)
        EIntr();
}

void iSyncDCache(void *start, void *end) {
    _SyncDCache((unsigned int) start & LINE_MASK, (unsigned int) end & LINE_MASK);
}

void _InvalidDCache(unsigned int start, unsigned int end) {
    int i;
    unsigned int tag;

    for (i = 0; i < 4096; i += 64) {
        CACHE_WAY(0, 0x16)
        CACHE_WAY(1, 0x16)
        __asm__ volatile("sync.l");
    }
}

void InvalidDCache(void *start, void *end) {
    int eie;

    __asm__ volatile("mfc0 %0, $12" : "=r"(eie));
    eie &= SR_EIE;
    if (eie)
        DIntr();
    _InvalidDCache((unsigned int) start & LINE_MASK, (unsigned int) end & LINE_MASK);
    if (eie)
        EIntr();
}

void iInvalidDCache(void *start, void *end) {
    _InvalidDCache((unsigned int) start & LINE_MASK, (unsigned int) end & LINE_MASK);
}
