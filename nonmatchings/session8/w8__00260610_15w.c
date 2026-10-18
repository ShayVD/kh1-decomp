/* 00260610 sdk/gcc991111, 15w (session-7 draft 25w), same size. Fixed: fn pointer local in both arms (fn = s->usr[id].func), s32 isceSifSetDChain (cid load in v1), pkt local + 'pkt[0] = 0; src = pkt;' (dst v1), if (n > 0) do-while(--i) loop (blez guard + copy). Left: pkt a2/src a1/size a0/n v0 vs orig pkt a3/src a2/size a1/n a1 (size is tied by local-alloc to size+30 in a0; orig keeps size+30 untied). */
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
