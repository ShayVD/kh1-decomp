/* Hand-matched functions in 0x001a0000-0x001c0000 (worker 13). */
#include "common.h"

/* Singly linked free list: pool->free at +4. */
typedef struct Node { struct Node *next; } Node;
typedef struct { u8 pad[4]; Node *free; } Pool;

Node *func_001a8900(Pool *p) {
    Node *n = p->free;
    if (n == NULL) return NULL;
    p->free = n->next;
    return n;
}
