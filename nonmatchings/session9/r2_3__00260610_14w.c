/* 00260610 14w, sdk/gcc991111 (was 15w). Change: `i = n; dst = buf;` inside `if (n > 0)` (dst after i), src = pkt stays before it: the preheader now matches (blez delay = move a0,a1 i = n, then move v1,sp). Left: size a0 vs a1 (and the knock-on pkt a2/a3, src a1/a2, n v0/a1). Cause (w6 s9, confirmed): global-alloc gives size the a0 preference of size+30 (local a0) because size dies there; orig needs size live when size+30 is born, i.e. sched1 issuing size+30 (prio 4) before size+15 (prio 5). Tried on top: (15+size), n = size+15; n /= 16, u8 size, psize bitfield, if ((size = pkt[0]) == 0), !size, pkt[0]=0 before n, size reused as n (drops the copy: 288 bytes). */
#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
s32 EIntr(void);
s32 isceSifSetDChain(void);
typedef struct { void (*func)(void *, void *); void *data; } SifCmdEnt;
typedef struct { volatile u8 *pkt; s32 x4, x8; SifCmdEnt *sys; s32 nsys; SifCmdEnt *usr; s32 nusr; } SifCmdState;
extern SifCmdState D_0066E6D8;
typedef struct { u32 x0, x4; s32 cid; } SifCmdHdr;

s32 func_00260610(void) {
    u128 buf[7];
    SifCmdState *s;
    SifCmdEnt *e;
    u128 *src, *dst;
    s32 size, n;
    s32 i;
    s32 id;
    volatile u8 *pkt;
    void (*fn)(void *, void *);
    EIntr();
    s = &D_0066E6D8;
    pkt = s->pkt;
    size = pkt[0];
    if (size == 0) return 0;
    n = (size + 15) / 16;
    pkt[0] = 0;
    src = (u128 *)pkt;
    if (n > 0) { i = n; dst = buf; do { *dst++ = *src++; } while (--i); }
    isceSifSetDChain();
    if (((volatile SifCmdHdr *)buf)->cid < 0) {
        id = ((volatile SifCmdHdr *)buf)->cid & 0x7fffffff;
        if (id < s->nsys) {
            fn = s->sys[id].func; if (fn) fn(buf, s->sys[id].data);
        }
    } else {
        id = ((volatile SifCmdHdr *)buf)->cid;
        if (id < s->nusr) {
            fn = s->usr[id].func; if (fn) fn(buf, s->usr[id].data);
        }
    }
    __asm__ volatile("sync.l; ei");
    return 0;
}
