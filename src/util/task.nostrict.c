/* The task starts of src/util/task.c (docs/modules.md "Session 48"),
 * 0x001c00e8-0x001c0460, compiled with -fno-strict-aliasing as their old
 * files were.  Each takes a free slot (func_001bfed8), marks it used with
 * the priority (0xffff for a negative one) and writes the task's stack top
 * and entry into its saved sp and ra: func_001c00e8(prio, fn, q) for a
 * large slot with one 128-bit word kept in Task.q; func_001c01b0(prio, fn,
 * ...) for a large slot ("already max task!" when none is free) and
 * func_001c0310(prio, fn, ...) for a small one copy eight arguments into
 * the saved a0-a7. */
#include "common.h"
#include "util/task.h"

typedef union { u128 q; s32 w; } TaskQW;

extern Task *D_0037A16C;
extern char D_00490300[];
s32 puts(const char *);

s32 func_001c00e8(s32 prio, s32 fn, u128 q) {
    s32 i;
    Task *s;
    TaskQW t;
    if (prio < 0) prio = 0xffff;
    i = func_001bfed8(0);
    if (i < 0) return -1;
    s = D_0037A16C;
    s[i].used = 1;
    s[i].prio = prio;
    t.q = 0;
    t.w = (s32)s[i].stk;
    s[i].ctx->sp = t.q;
    t.w = fn;
    D_0037A16C[i].ctx->ra = t.q;
    D_0037A16C[i].q = q;
    return i;
}

s32 func_001c01b0(s32 prio, void *fn, ...) {
    char *ap;
    s32 i, n;
    TaskQW tmp;
    Task *t;
    if (prio < 0) prio = 0xffff;
    n = func_001bfed8(0);
    if (n < 0) {
        puts(D_00490300);
        return -1;
    }
    ap = (char *)__builtin_next_arg(fn) - 8 * (8 - __builtin_args_info(2));
    { u32 off = n * 48; t = (Task *)(off + (u32)D_0037A16C); }
    t->used = 1;
    t->prio = prio;
    tmp.q = 0;
    tmp.w = (s32)t->stk;
    t->ctx->sp = tmp.q;
    tmp.w = (s32)fn;
    D_0037A16C[n].ctx->ra = tmp.q;
    tmp.q = 0;
    for (i = 0; i < 8; i++) {
        { char *p = ap; ap += 8; tmp.w = *(s32 *)p; }
        ((u128 *)D_0037A16C[n].ctx)[20 + i] = tmp.q; /* a[i] */
    }
    D_0037A16C[n].q = 0;
    return n;
}

s32 func_001c0310(s32 prio, void *fn, ...) {
    char *ap;
    s32 i, n;
    TaskQW tmp;
    Task *t;
    if (prio < 0) prio = 0xffff;
    n = func_001bfed8(1);
    if (n < 0) return -1;
    ap = (char *)__builtin_next_arg(fn) - 8 * (8 - __builtin_args_info(2));
    { u32 off = n * 48; t = (Task *)(off + (u32)D_0037A16C); }
    t->used = 1;
    t->prio = prio;
    tmp.q = 0;
    tmp.w = (s32)t->stk;
    t->ctx->sp = tmp.q;
    tmp.w = (s32)fn;
    D_0037A16C[n].ctx->ra = tmp.q;
    tmp.q = 0;
    for (i = 0; i < 8; i++) {
        { char *p = ap; ap += 8; tmp.w = *(s32 *)p; }
        ((u128 *)D_0037A16C[n].ctx)[20 + i] = tmp.q; /* a[i] */
    }
    D_0037A16C[n].q = 0;
    return n;
}
