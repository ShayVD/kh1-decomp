#include "common.h"

typedef int u128 __attribute__((mode(TI)));
typedef struct Node { struct Node *next; } Node;
typedef struct { Node *head; s32 n; } Bucket;
typedef struct { s32 bits; Bucket *tbl; } Hash;

void func_00237680(Hash *h, Node *node, s32 idx) {
    s32 max = 1 << h->bits;
    if (idx < 0) idx = 0;
    if (idx >= max) idx = max - 1;
    node->next = h->tbl[idx].head;
    h->tbl[idx].head = node;
}

u128 *func_00237ec0(u128 *src, u128 *dst) {
    s32 i;
    s32 n = 1;
    for (i = 0; i < ((s32 *)src)[2]; i++) {
        dst[n++] = src[i + 1];
    }
    *dst = 0;
    *(s32 *)dst = (n - 1) | 0x10000000;
    return dst + n;
}

