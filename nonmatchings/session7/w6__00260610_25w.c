/* 00260610 (SIF cmd interrupt handler) sdk/gcc991111, same size, 25w: register naming only (orig pkt a3/size a1/src a2/dst v1, fn ptr in a2; ours one reg lower). Keys vs session-5 draft: s32 loop counter (reversed loop with blez guard), s->usr[id].func indexed like sys. */
#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
s32 EIntr(void);
void isceSifSetDChain(void);
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
    EIntr();
    s = &D_0066E6D8;
    size = s->pkt[0];
    if (size == 0) return 0;
    n = (size + 15) / 16;
    src = (u128 *)s->pkt;
    s->pkt[0] = 0;
    dst = buf;
    for (i = 0; i < n; i++) *dst++ = *src++;
    isceSifSetDChain();
    if (((volatile SifCmdHdr *)buf)->cid < 0) {
        id = ((volatile SifCmdHdr *)buf)->cid & 0x7fffffff;
        if (id < s->nsys) {
            if (s->sys[id].func) s->sys[id].func(buf, s->sys[id].data);
        }
    } else {
        id = ((volatile SifCmdHdr *)buf)->cid;
        if (id < s->nusr) {
            if (s->usr[id].func) s->usr[id].func(buf, s->usr[id].data);
        }
    }
    __asm__ volatile("sync.l; ei");
    return 0;
}
