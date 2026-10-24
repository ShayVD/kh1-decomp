/* The task slots of src/util/task.c (docs/modules.md "Session 48"). */
#ifndef KH1_UTIL_TASK_H
#define KH1_UTIL_TASK_H

#include "common.h"
#include "data/types/shared.h"

/* A task's saved registers, as the switcher func_001bfac8 (src/asm/text_001aa1f8.s)
 * stores them: 128-bit slots, sp at 0xd0, ra at 0xf0, a0-a7 from 0x140. */
typedef struct {
    u8 pad0[0xd0];
    u128 sp;        /* 0x0d0 */
    u8 pade0[0x10];
    u128 ra;        /* 0x0f0: where the task starts */
    u8 pad100[0x40];
    u128 a[8];      /* 0x140: its eight arguments */
} TaskCtx;

/* One slot of D_0037A16C (48 bytes): slot 0 is the main loop, 1-15 the large
 * tasks (0x81b0-byte stacks), 16-399 the small ones (0x9b0). */
typedef struct {
    u16 used;           /* 0x00 */
    u16 prio;           /* 0x02: lower runs first (func_001c0460) */
    u16 flags;          /* 0x04: bit 0 ends the task at the next schedule */
    u16 h6;             /* 0x06 */
    TaskCtx *ctx;       /* 0x08 */
    u8 *stk;            /* 0x0c: the top of its stack */
    u128 q;             /* 0x10 */
    void (*fn)(void);   /* 0x20: called when the task ends (func_001c06c0) */
    u8 pad24[12];
} Task;

void func_001bfac8(void);
void func_001bfcd8(void);
u8 *func_001bfe50(u8 *a);
s32 func_001bfed8(s32 small);
void func_001bffa0(s32 i);

#endif /* KH1_UTIL_TASK_H */
