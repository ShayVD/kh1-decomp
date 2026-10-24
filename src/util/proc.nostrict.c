/* The frame callback lists: pools of nodes sorted by priority (func_0011efa8
 * sets a pool up, func_0011efe8 takes a node, func_0011f090(list, prio, fn)
 * inserts, func_0011f2e0 finds, func_0011f058 the previous node,
 * func_0011f228 runs a list and drops the nodes whose callback returns bit
 * 2, func_0011f320 removes, func_0011f130 another pass over a list), and the
 * main list D_004E3A48: func_0011ef10(prio, fn) adds a callback (154
 * callers), func_0011ef38 asks whether one is there, func_0011ef58 removes
 * it. Flag mode: nostrict (the other modes are in the sibling files). Read
 * from the code, not proved by a boot (docs/modules.md "Session 54"). */
#include "common.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004E.h"
#include "data/bss_004F.h"

/* func_0011f090 (from hand/nostrict/text_00110000_s6_04.c). */
typedef struct Node { u16 type; u16 f2; s32 key; struct Node *next; s32 data; } Node;
typedef struct { u16 size; u16 count; u8 *base; Node *head; u8 *cur; } Pool;
u8 *func_0011efe8(Pool *p);
Node *func_0011f090(Pool *l, s32 key, s32 val) {
    Node *n = (Node *)func_0011efe8(l);
    Node *prev, *p;
    if (n) {
        n->data = val;
        n->type = 17;
        prev = 0;
        n->key = key;
        n->f2 = 0;
        for (p = l->head; p && key >= p->key; p = p->next) prev = p;
        if (prev) prev->next = n;
        else l->head = n;
        n->next = p;
    }
    l->cur = (u8 *)n;
    return n;
}

