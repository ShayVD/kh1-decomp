/* The SDK functions the game still calls by address, named (docs/sdk.md, the disassembly in
 * `kh1tool.py asm`) and mapped to the host libc or to nothing, for every port platform; plus the
 * libc pieces whose PS2 behaviour (newlib) the host libc does not share.  Not part of the PS2
 * build (it lives outside src/). */
#include "common.h"
#include "platform/dma.h"
#include "platform/gs.h"

typedef unsigned int size_t_;
void *bsearch(const void *, const void *, size_t_, size_t_, int (*)(const void *, const void *));
void *memset(void *, int, size_t_);
float cosf(float);
float sinf(float);
float tanf(float);
float acosf(float);
float atan2f(float, float);
float fmodf(float, float);
int printf(const char *, ...);
void abort(void);

/* libc / libm (0x0024f318 ... 0x0026b9c0) */
void *func_0024f318(const void *key, const void *base, size_t_ n, size_t_ size,
                    int (*cmp)(const void *, const void *)) {
    return bsearch(key, base, n, size, cmp); /* bsearch */
}
void *func_00250054(void *d, int c, size_t_ n) { return memset(d, c, n); } /* memset */
float func_0026b6f8(float x) { return cosf(x); }
float func_0026b7d0(float x) { return sinf(x); }
float func_0026b8b8(float x) { return tanf(x); }
float func_0026b978(float x) { return acosf(x); }
float func_0026b9a8(float y, float x) { return atan2f(y, x); }
float func_0026b9c0(float x, float y) { return fmodf(x, y); }

/* newlib's rand (0x00250d50 / 0x00250d68, docs/sdk.md): the host libc's differs, and the game's
 * random sequences (drops, AI) should not */
static u64 rand_next = 1;
void srand(unsigned int seed) { rand_next = seed; }
int rand(void) {
    rand_next = rand_next * 0x5851F42D4C957F2DULL + 1;
    return (int)((rand_next >> 32) & 0x7FFFFFFF);
}

/* newlib's __assert(file, line, expression): glibc's takes (expression, file, line) */
void __assert(const char *file, int line, const char *expr) {
    printf("assertion \"%s\" failed: file \"%s\", line %d\n", expr, file, line);
    abort();
}

/* __main (0x00262c78): gcc's once-only __do_global_ctors; the host runs constructors itself */
void func_00262c78(void) {}

/* sceGsSyncVCallback (0x00266a10: replaces the INTC 2 (VBlank start) handler, returns the old
 * one): kept for the platform's vsync to call (kh1_vsync_cb); the null platform never does */
void *kh1_vsync_cb;
#define vsync_cb kh1_vsync_cb
void *func_00266a10(void *fn) {
    void *old = vsync_cb;
    vsync_cb = fn;
    return old;
}

/* sceDmaGetChan / sceDmaSend (0x00266c08 / 0x00266f38) and sceGsSyncPath, which three drafts
 * of unmatched functions (shift/drafts.tsv) call directly: the dma.h / gs.h calls */
void *func_00266c08(int id) { return PlatDmaGetChan(id); }
void func_00266f38(void *ch, void *tag) { PlatDmaSend((PlatDmaChan *)ch, tag); }
int sceGsSyncPath(int mode, unsigned short timeout) { return PlatGsSyncPath(mode, timeout); }

/* sceDmaReset (0x00266c30): dma.h's chains need no reset */
int func_00266c30(int mode) { return 0; }

/* sceIpuInit / sceIpuSync (src/game/dkmovie.c): the movie decision (vita-port-plan section 3) */
void sceIpuInit(void) {}
int sceIpuSync(int mode, unsigned short timeout) { return 0; }

/* Entries of SDK tables in the data blob (src/data/data_0035.s, data_0046.s: FlushCache /
 * SyncDCache, newlib's stdio and the kernel's handlers); the game never calls them off the EE */
void func_002583e0(void) {} /* FlushCache */
void func_00258a58(void) {} /* SyncDCache */
void func_00259468(void) {} /* a putchar that writes \r before \n (func_00259380) */
void func_0025f3f0(void) {} /* word copies of kernel tables */
void func_0025f428(void) {}
void func_0025f620(void) {}
void func_0025f790(void) {}
void func_0025fa40(void) {}
void func_002608e0(void) {}
