/* func_002376c8: ~37w off, nostrict_nofill, CONTEXT_ONLY func_00237680 above. kind-select (movz x2 + bne for kind==2, li a3,2 hoisted) shape wrong; rest fine */
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
s32 func_002376c8(Hash *h, Node *n, void *m) {
    V4 v;
    V4 *p;
    s32 s, r;
    V4 *q = &n->pos; s32 k = n->kind; p = 0; if (k == 1) p = q; else if (k == 3) p = q; else if (k == 2) p = q;
    s = 1 << h->bits;
    func_002672f8(&v, m, p);
    r = s - v.w / 3000.0f * s;
    func_00237680(h, n, r);
    return r;
}
