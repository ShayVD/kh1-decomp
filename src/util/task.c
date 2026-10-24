/* The task slots (docs/modules.md "Session 48"), 0x001bfc90-0x001c06f8: a
 * second cooperative task system beside src/util/sa_task.c, with 400 slots
 * of 48 bytes (Task, include/util/task.h) at D_0037A16C and the run queue
 * D_0037A170 (slot index and saved context, ended by -1) that the hand asm
 * switcher func_001bfac8 (src/asm/text_001aa1f8.s) walks.
 * func_001bfe50(buf) carves the 0x171388 bytes (func_001bfec8) of buf into
 * the stacks, the contexts, the slots and the queue; func_001bfcd8 clears
 * them (slot 0 is the caller), func_001c0460 drops the slots marked to end
 * and sorts the rest by priority into the queue; func_001c0688(n) yields n
 * times.  The tasks are started by src/util/task.nostrict.c.  D_0037A15C /
 * D_0037A160 are set (0 and 15) but read nowhere in this file.  Read from
 * the code, not proved by a boot. */
#include "common.h"
#include "util/task.h"
#include "data/data_0037.h"
#include "data/bss_0062.h"
#include "data/pieces/D_0037A170.h"

extern Task *D_0037A16C;
void func_001be820(void *p, u32 n);

void func_001bfc90(s32 arg0) {
    D_0037A15C = arg0;
}

void func_001bfca0(s32 arg0) {
    D_0037A160 = arg0;
}

u128 *func_001bfcb0(void) {
    return &D_0037A16C[D_0037A168].q;
}

void func_001bfcd8(void) {
    u8 *p;
    Task *t;
    s32 i;

    D_0037A174 = 1;
    D_0037A164 = 0;
    D_0037A168 = 0;
    p = D_006257D4;
    func_001be820(D_0037A16C, 48);
    t = D_0037A16C;
    t->used = 1;
    t->stk = 0;
    t->prio = 0;
    t->flags = 0;
    t->h6 = 0;
    t->ctx = (TaskCtx *)p;
    p += 448;
    for (i = 1; i < 16; i++) {
        func_001be820(&D_0037A16C[i], 48);
        D_0037A16C[i].ctx = (TaskCtx *)p;
        p += 0x81b0;
        D_0037A16C[i].stk = p;
        p += 16;
        D_0037A16C[i].prio = 0;
        D_0037A16C[i].flags = 0;
        D_0037A16C[i].h6 = 0;
        D_0037A16C[i].used = 0;
    }
    for (i = 0; i < 384; i++) {
        func_001be820(&D_0037A16C[i + 16], 48);
        D_0037A16C[i + 16].ctx = (TaskCtx *)p;
        p += 0x9b0;
        D_0037A16C[i + 16].stk = p;
        p += 16;
        D_0037A16C[i + 16].prio = 0;
        D_0037A16C[i + 16].flags = 0;
        D_0037A16C[i + 16].h6 = 0;
        D_0037A16C[i + 16].used = 0;
    }
    {
        u8 *c = (u8 *)D_0037A16C->ctx;
        RunQ_37a170 *q = D_0037A170;
        q[1].arg = -1;
        q->ctx = c;
        q[1].ctx = 0;
        q->arg = 0;
    }
}

u8 *func_001bfe50(u8 *a) {
    u8 *r;
    r = a + 0x16BC00;
    D_0037A16C = (Task *)r;
    r = a + 0x170700;
    D_0037A170 = (RunQ_37a170 *)r;
    D_0037A15C = 0;
    D_0037A160 = 15;
    D_006257D4 = a;
    r = a + 0x171388;
    func_001bfcd8();
    return r;
}

s32 func_001bfec8(void) {
    return 0x171388;
}

s32 func_001bfed8(s32 small) {
    s32 i;
    if (small == 0) {
        for (i = 1; i < 16; i++) {
            if (D_0037A16C[i].used == 0) return i;
        }
        return -1;
    }
    for (i = 0; i < 384; i++) {
        if (D_0037A16C[i + 16].used == 0) return i + 16;
    }
    return -1;
}

u16 func_001bff70(s32 i) {
    u16 v;

    v = 0;
    if (i >= 0) {
        v = D_0037A16C[i].used;
    }
    return v;
}

void func_001bffa0(s32 i) {
    if (i >= 0) {
        if (D_0037A16C[i].fn) D_0037A16C[i].fn();
        D_0037A16C[i].used = 0;
        D_0037A16C[i].prio = 0;
        D_0037A16C[i].flags = 0;
    }
}

void func_001c0010(void) {
    s32 i;
    for (i = 1; i < 400; i++) {
        if (D_0037A16C[i].used != 0) func_001bffa0(i);
    }
    func_001bfcd8();
}

void func_001c0078(s32 i) {
    Task *t;
    Task *cur;

    if (i >= 0) {
        t = (Task *)(i * 0x30 + (s32)D_0037A16C);
        if (t->used != 0) {
            t->flags = t->flags | 1;
        }
    } else if (D_0037A168 != 0) {
        cur = (Task *)(D_0037A168 * 0x30 + (s32)D_0037A16C);
        cur->flags = cur->flags | 1;
    }
}

void func_001c0460(void) {
    s16 order[1024];
    s32 i, j, k, n;
    Task *p;
    n = 1;
    for (i = 1; i < 400; i++) {
        if (D_0037A16C[i].used != 0) {
            if (D_0037A16C[i].flags & 1) func_001bffa0(i);
        }
        if (D_0037A16C[i].used != 0) n++;
    }
    D_0037A174 = n;
    D_0037A170[0].arg = 0;
    D_0037A170[0].ctx = (u8 *)D_0037A16C[0].ctx;
    if (n < 2) return;
    order[0] = -1;
    n = 0;
    p = &D_0037A16C[1];
    for (i = 1; i < 400; i++, p++) {
        if (p->used == 0) continue;
        for (j = 0; j < n; j++) {
            if (D_0037A16C[i].prio < D_0037A16C[order[j]].prio) break;
        }
        for (k = n - 1; k >= j; k--) order[k + 1] = order[k];
        order[j] = i;
        n++;
    }
    for (i = 0; i < n; i++) {
        D_0037A170[i + 1].arg = order[i];
        D_0037A170[i + 1].ctx = (u8 *)D_0037A16C[order[i]].ctx;
    }
    D_0037A170[i + 1].arg = -1;
    D_0037A170[i + 1].ctx = 0;
}

void func_001c0688(s32 n) {
    s32 i;

    if (n > 0) {
        i = n;
        do {
            i -= 1;
            func_001bfac8();
        } while (i != 0);
    }
}

void func_001c06c0(s32 i, void (*fn)(void)) {
    if (i < 0) i = D_0037A168;
    D_0037A16C[i].fn = fn;
}
