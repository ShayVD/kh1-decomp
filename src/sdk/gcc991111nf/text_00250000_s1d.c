/* SCE SDK libkernl leftover (SIF RPC request enqueue), matched with
 * ee-gcc 2.9-991111a -O2 -G0 without delay-slot filling. session s1d. */
#include "common.h"

int func_0025fd10(int tid);

/* head is a word and tail a void *, x14 a node pointer: that keeps the
 * q->tail store ahead of the r->x14 load */
typedef struct NQ NQ;
typedef struct NodeQ {
    int id;
    u8 pad04[8];
    u32 xc;
    u8 pad10[0xc];
    u32 x1c;
    u32 x20;
    u32 x24, x28, x2c, x30, x34;
    struct NodeQ *next;
    struct NodeQ *next2;
    NQ *q;
} NodeQ;
struct NQ { int tid; int busy; int x8; u32 head; void * tail; };
typedef struct { u8 pad[0x10]; u32 x10; NodeQ * x14; u32 x18; void * x1c; u32 x20, x24, x28, x2c, x30; NodeQ *node; } Req;
void func_0025a4d0(Req *r) {
    NodeQ *n = r->node;
    NQ *q = n->q;
    if (q->head == 0)
        q->head = (void *)n;
    else
        ((NodeQ *)q->tail)->next2 = n;
    q->tail = (void *)n;
    n->x20 = (void *)r->x14;
    n->x1c = (void *)r->x1c;
    n->x24 = r->x20;
    n->xc = r->x24;
    n->x28 = r->x28;
    n->x2c = r->x2c;
    n->x30 = r->x30;
    n->x34 = r->x10;
    if (q->tid >= 0 && q->busy == 0)
        func_0025fd10(q->tid);
}
