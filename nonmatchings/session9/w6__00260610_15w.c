/* 00260610 15w, sdk/gcc991111 (s8 w8 draft unchanged). Finding (w6 s9, -dl -dg, sched1 verbose): global-alloc order i(a0) size pkt...; size gets a0 by preference from the local size+30 (reg126, a0) because size dies at insn 220 (size+30). Orig size=a1 means size was still live when size+30 was born, i.e. sched1 issued 220 (size+30, prio 4) before 36 (size+15, prio 5, tie with const -1 insn 222, both issued at t=1). With 220 first, size conflicts with a0 -> a1, and n (sra) then takes a1 too. Tried: u8/u32 size, split n = size + 15; n /= 16, !size, pkt[0]=0 before n, reusing size as n (worse): all 15w. Needs a source shape where size+30 gets priority >= 5 or size+15 is delayed. */
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
    dst = buf;
    if (n > 0) { i = n; do { *dst++ = *src++; } while (--i); }
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
