#include "common.h"
typedef kh1_u128 u128;
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
    s32 n;
    s32 i;
    s32 id;
    volatile u8 *pkt;
    void (*fn)(void *, void *);
    EIntr();
    s = &D_0066E6D8;
    pkt = s->pkt;
    n = pkt[0];
    if (n == 0) return 0;
    n = (n + 15) / 16;
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
