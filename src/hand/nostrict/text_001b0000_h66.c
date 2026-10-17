#include "common.h"

typedef unsigned int u128 __attribute__((mode(TI)));
typedef union { u128 q; s32 w; } Q;
typedef struct { u16 h0, h2, h4, h6; u8 *ctx; u8 *stk; u128 q16; u8 pad[16]; } Task;
typedef struct { u8 pad[208]; u128 sp; u8 pad224[16]; u128 ra; u8 pad256[64]; u128 a[8]; } Ctx;
extern Task *D_0037A16C;
extern char D_00490300[];
s32 func_001bfed8(s32);
s32 puts(const char *);

s32 func_001c01b0(s32 prio, void *fn, ...) {
    char *ap;
    s32 i, n;
    Q tmp;
    Task *t;
    if (prio < 0) prio = 0xffff;
    n = func_001bfed8(0);
    if (n < 0) {
        puts(D_00490300);
        return -1;
    }
    ap = (char *)__builtin_next_arg(fn) - 8 * (8 - __builtin_args_info(2));
    { u32 off = n * 48; t = (Task *)(off + (u32)D_0037A16C); }
    t->h0 = 1;
    t->h2 = prio;
    tmp.q = 0;
    tmp.w = (s32)t->stk;
    ((Ctx *)t->ctx)->sp = tmp.q;
    tmp.w = (s32)fn;
    ((Ctx *)D_0037A16C[n].ctx)->ra = tmp.q;
    tmp.q = 0;
    for (i = 0; i < 8; i++) {
        { char *p = ap; ap += 8; tmp.w = *(s32 *)p; }
        ((u128 *)D_0037A16C[n].ctx)[20 + i] = tmp.q;
    }
    D_0037A16C[n].q16 = 0;
    return n;
}

s32 func_001c0310(s32 prio, void *fn, ...) {
    char *ap;
    s32 i, n;
    Q tmp;
    Task *t;
    if (prio < 0) prio = 0xffff;
    n = func_001bfed8(1);
    if (n < 0) return -1;
    ap = (char *)__builtin_next_arg(fn) - 8 * (8 - __builtin_args_info(2));
    { u32 off = n * 48; t = (Task *)(off + (u32)D_0037A16C); }
    t->h0 = 1;
    t->h2 = prio;
    tmp.q = 0;
    tmp.w = (s32)t->stk;
    ((Ctx *)t->ctx)->sp = tmp.q;
    tmp.w = (s32)fn;
    ((Ctx *)D_0037A16C[n].ctx)->ra = tmp.q;
    tmp.q = 0;
    for (i = 0; i < 8; i++) {
        { char *p = ap; ap += 8; tmp.w = *(s32 *)p; }
        ((u128 *)D_0037A16C[n].ctx)[20 + i] = tmp.q;
    }
    D_0037A16C[n].q16 = 0;
    return n;
}
