/* SCE SDK libkernl leftovers (SIF RPC packet pool and server registration),
 * matched with ee-gcc 2.9-991111a -O2 -G0. sdk segment, session s1d. */
#include "common.h"

int DIntr(void);
int EIntr(void);

/* 64-byte SIF packet as allocated from the pool */
typedef struct { u8 pad[0x10]; int rid; void *pkt; int id; void *cd; u32 x20, x24, x28, x2c, x30, x34; u8 pad2[8]; } Pk;
/* the RPC library's state (D_0066C700): only the pool fields are used here */
typedef struct { int id; Pk *pk; int npk; } Ring;

/* Takes a free packet from the pool. The id wraps past 0: on id 1 the
 * counter is bumped again (the r = id copy on both paths gives `li v1,1`). */
Pk *func_00259ee8(Ring *p) {
    Pk *e;
    int i;
    int id, r;
    DIntr();
    e = p->pk;
    for (i = 0; i < p->npk; i++, e++) {
        if (!(e->rid & 1)) {
            e->rid = (i << 16) | 5;
            id = ++p->id;
            if (id == 1) { p->id++; r = id; } else r = id;
            e->pkt = e;
            e->id = r;
            EIntr();
            return e;
        }
    }
    EIntr();
    return 0;
}

/* RPC server node; next/next2 and the queue's list are void * so the
 * list load stays after the link and id stores */
typedef struct N8 {
    int id; int x4; int buf; int xc; int x10; int x14; u8 pad18[0x20];
    void * next; void * next2; struct Q8 *q;
} N8;
typedef struct Q8 { int tid; int busy; void * list; N8 *head; N8 *tail; struct Q8 *next; } Q8;
void func_0025a828(N8 *n, int id, int a, int buf, int b, int c, Q8 *q) {
    N8 *p;
    DIntr();
    n->next2 = 0;
    n->next = 0;
    n->id = id;
    n->x4 = (void *)a;
    n->buf = (void *)buf;
    n->x10 = (void *)b;
    n->x14 = (void *)c;
    n->q = q;
    if (!q->list)
        q->list = (void *)n;
    else {
        p = (N8 *)q->list;
        while (p->next)
            p = (N8 *)p->next;
        p->next = (void *)n;
    }
    EIntr();
}

