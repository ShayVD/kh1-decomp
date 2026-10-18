/* 00260610: LCS 4 words (4 pos, right size 296), sdk/gcc991111 (same in 991111_01/nf/as296), no context (s9 draft 14). New: the handler index of both branches reuses n (`n = cid & 0x7fffffff; if (n < s->nsys) ...`), which fixes the pkt/src/n registers (pkt a3, src a2, n a1). Left: size takes a0 instead of a1: global-alloc gives it the a0 preference of the local size+30 and it conflicts with nothing in a0 (size dies at size+30's birth); orig size must still be live when size+30 is born. Decl orders, !size, (0 < n), size reuse elsewhere: no change. */
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
        n = ((volatile SifCmdHdr *)buf)->cid & 0x7fffffff;
        if (n < s->nsys) {
            fn = s->sys[n].func; if (fn) fn(buf, s->sys[n].data);
        }
    } else {
        n = ((volatile SifCmdHdr *)buf)->cid;
        if (n < s->nusr) {
            fn = s->usr[n].func; if (fn) fn(buf, s->usr[n].data);
        }
    }
    __asm__ volatile("sync.l; ei");
    return 0;
}
