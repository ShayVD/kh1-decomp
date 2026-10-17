/* func_0025add8 (file I/O SIF handler, cmd 0x80000011), sdk/gcc991111 (991111a), rodata jump
 * table D_004922D0 (rr.py 004922D0). 1 word off: with "unsigned short sema" the original
 * has "move a2,v0" where we get "andi a2,v0,0xffff"; with int sema the copy disappears
 * (negu straight into a2, 8 words), with long sema and "sema == D[i]" only the two bne
 * operand orders differ (2 words). The needed source has some no-op conversion between
 * the negated value and the compared value. */
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
