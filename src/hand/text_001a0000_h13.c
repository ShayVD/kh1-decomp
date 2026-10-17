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

/* Fixed-size block pool: n blocks of (sz-1)*48+128 bytes after a 16-byte header. */
typedef struct { u8 n; u8 sz; s16 stride; void *free; } Pool2;

void func_001a8920(Pool2 *p, u8 n, u8 sz) {
    u8 **q = (u8 **)((u8 *)p + 16);
    s32 i;
    s32 stride;
    p->free = q;
    p->n = n;
    p->sz = sz;
    stride = (u8)(sz - 1) * 48 + 128;
    p->stride = stride;
    for (i = n - 1; i > 0; i--) {
        u8 **c = q;
        q = (u8 **)((u8 *)q + stride);
        *c = (u8 *)q;
    }
    *q = NULL;
}

/* u16 free-list of ids: next[] table at +0, head id at +6 (0xffff = empty). */
typedef struct { u16 *next; u8 pad[2]; u16 cur; } IdList;

s32 func_001a93e0(IdList *l) {
    u16 c;
    if (l->cur == 0xffff) return 0xffff;
    c = l->cur;
    l->cur = l->next[l->cur];
    return c;
}
