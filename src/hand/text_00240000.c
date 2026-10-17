/* 0x00240000-0x0024FFFF game code by hand. */
#include "common.h"

/* The kernel's semaphore and thread parameters (SCE eekernel.h layout). */
typedef struct {
    s32 count, max_count, init_count, wait_threads;
    u32 attr, option;
} SemaParam;

typedef struct {
    s32 status;
    void *func;
    void *stack;
    s32 stack_size;
    void *gp_reg;
    s32 initial_priority;
    s32 current_priority;
    u32 attr, option;
} ThreadParam;

s32 CreateSema(SemaParam *);
s32 CreateThread(ThreadParam *);
s32 StartThread(s32, void *);
void func_0024d618(void *);
void func_0024d7b0(void);
void func_00269960(void *, s32);
extern u8 D_00669A80[];
extern u8 D_00494050[];

/* Starts the thread at func_0024d618 (4 KB stack at D_00669A80, priority
 * 1) with a new semaphore, and registers func_0024d7b0 with it. */
void func_0024d808(void) {
    ThreadParam tp;
    SemaParam sp;
    s32 sema;

    sp.max_count = 1;
    sp.init_count = 0;
    sp.option = 0;
    sema = CreateSema(&sp);
    tp.stack_size = 0x1000;
    tp.gp_reg = D_00494050;
    tp.func = func_0024d618;
    tp.stack = D_00669A80;
    tp.initial_priority = 1;
    StartThread(CreateThread(&tp), (void *) sema);
    func_00269960(func_0024d7b0, sema);
}

typedef struct {
    s32 a, b, c;
} Vec12;

/* A fixed array of 12-byte records filled from the front. */
typedef struct {
    s32 cap;    /* +0x0 */
    Vec12 *buf; /* +0x4 */
    s32 wr;     /* +0x8: records written */
    s32 rd;     /* +0xC: next record to read */
} Vec12Queue;

typedef struct {
    s32 on;   /* +0x0 */
    Vec12 v;  /* +0x4 */
    s32 unk10;
} Vec12Slot;

extern Vec12Slot D_006561D0;

void func_002431b8(Vec12Queue *q, Vec12 *v) {
    if (q->wr != q->cap) {
        q->buf[q->wr] = *v;
        q->wr++;
    }
}

/* Copies the next unread record to *v; 0 when there is none. */
s32 func_00243278(Vec12Queue *q, Vec12 *v) {
    if (q->wr == q->rd)
        return 0;
    *v = q->buf[q->rd];
    return 1;
}

void func_00243690(Vec12 *v) {
    D_006561D0.unk10 = 0;
    D_006561D0.v = *v;
    D_006561D0.on = 1;
}

/* Takes the next unread record into *v; the queue empties itself once all
 * are read. 0 when there is none. */
s32 func_00243208(Vec12Queue *q, Vec12 *v) {
    if (q->wr == q->rd)
        return 0;
    *v = q->buf[q->rd];
    q->rd++;
    if (q->wr == q->rd) {
        q->rd = 0;
        q->wr = 0;
    }
    return 1;
}
