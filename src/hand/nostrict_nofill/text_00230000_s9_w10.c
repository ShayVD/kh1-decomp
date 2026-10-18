#include "common.h"

typedef struct { f32 x, y, z, w; } V4;
typedef struct Node { struct Node *next; s32 kind; u8 pad[8]; V4 pos; } Node;
typedef struct { Node *head; s32 n; } Bucket;
typedef struct { s32 bits; Bucket *tbl; } Hash;
void func_002672f8(V4 *, void *, V4 *);

CONTEXT_ONLY void func_00237680(Hash *h, Node *node, s32 idx) {
    s32 max = 1 << h->bits;
    if (idx < 0) idx = 0;
    if (idx >= max) idx = max - 1;
    node->next = h->tbl[idx].head;
    h->tbl[idx].head = node;
}

/* An else-if chain in the order 2, 3, 1 with the last arm through a block-local
 * temporary (a two-insn then-block for jump1's conditional-move conversion):
 * gives the original's movz, movz (li 3; xor), bne k,2 shape. */
s32 func_002376c8(Hash *h, Node *n, void *m) {
    V4 v;
    V4 *p;
    s32 s, r;
    s32 k = n->kind;
    p = 0;
    if (k == 2) {
        p = &n->pos;
    } else if (k == 3) {
        p = &n->pos;
    } else if (k == 1) {
        V4 *t = &n->pos;
        p = t;
    }
    s = 1 << h->bits;
    func_002672f8(&v, m, p);
    r = s - v.w / 3000.0f * s;
    func_00237680(h, n, r);
    return r;
}
