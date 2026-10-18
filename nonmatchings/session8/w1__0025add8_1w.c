/* 1w, sdk/gcc991111, rodata 004922D0 (unchanged draft, new finding): the original keeps a plain SImode copy sema=T (move a2,v0) that gcse COPY-PROP removes in every int form (dump: "COPY-PROP: Replacing reg 84 in insn 454 with reg 208"); a copy survives only if its src or dest is set again later in the same block, or as a non-copy (u16 zero_extend = this 1w; long sign_extend = move but the DI compare (ne:DI (subreg X) sema) only combines with the subreg second, so bne operands swap). Untried: a source shape that re-sets sema or T after the copy in the same block without changing code. */
#include "common.h"

#define UNCACHED(p) ((void *) ((u32) (p) | 0x20000000))
void *memcpy(void *, const void *, unsigned int);
int iSignalSema(int);
extern volatile int D_0046AE58[32];
typedef struct { int sema; int cmd; void *dst; int size; } FioHdr;
typedef struct { FioHdr h; u8 data[1]; } FioRes;
extern FioRes D_0066D400;
typedef struct { int n1; int n2; u8 *p1; u8 *p2; u8 b1[64]; u8 b2[64]; } FioRd;
typedef struct { u8 b[324]; } B324;
typedef struct { u8 b[64]; } B64;
extern u8 D_0066D414[];

void func_0025add8(void) {
    FioHdr r;
    struct { void *dst; unsigned int n; } d;
    unsigned short sema;
    unsigned int n;
    int i;

    __builtin_memcpy(&r.sema, UNCACHED(&D_0066D400.h.sema), 4);
    __builtin_memcpy(&r.cmd, UNCACHED(&D_0066D400.h.cmd), 4);
    __builtin_memcpy(&r.dst, UNCACHED(&D_0066D400.h.dst), 4);
    __builtin_memcpy(&r.size, UNCACHED(&D_0066D400.h.size), 4);
    if (r.sema >= 0)
        memcpy(r.dst, UNCACHED(D_0066D400.data), r.size);
    switch (r.cmd) {
    case 2: {
        FioRd *x = UNCACHED(D_0066D414);
        if (x->n1 > 0) {
            u8 *p = x->p1;
            for (i = 0; i < x->n1; i++)
                p[i] = x->b1[i];
        }
        if (x->n2 > 0) {
            u8 *p = x->p2;
            for (i = 0; i < x->n2; i++)
                p[i] = x->b2[i];
        }
        break;
    }
    case 11:
        __builtin_memcpy(&d.dst, UNCACHED(D_0066D414), 4);
        *(B324 *) d.dst = *(B324 *) UNCACHED(D_0066D414 + 4);
        break;
    case 12:
        __builtin_memcpy(&d.dst, UNCACHED(D_0066D414), 4);
        *(B64 *) d.dst = *(B64 *) UNCACHED(D_0066D414 + 4);
        break;
    case 23:
    case 25:
    case 26:
        __builtin_memcpy(&d.dst, UNCACHED(D_0066D414), 4);
        __builtin_memcpy(&d.n, UNCACHED(D_0066D414 + 4), 4);
        if (d.n > 1024)
            d.n = 1024;
        n = d.n;
        memcpy(d.dst, UNCACHED(D_0066D414 + 8), n);
        break;
    }
    if (r.sema < 0) {
        sema = r.sema = -r.sema;
        for (i = 0; i < 32; i++) {
            if (D_0046AE58[i] == sema) {
                D_0046AE58[i] = -1;
                break;
            }
        }
    } else {
        iSignalSema(r.sema);
    }
}
