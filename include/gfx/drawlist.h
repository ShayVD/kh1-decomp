/* The depth-sorted draw list (src/gfx/drawlist*.c; docs/modules.md "Session
 * 45"): 1 << bits buckets, each a singly linked list of nodes pushed by
 * depth; func_00237f20 walks the buckets in order and sends each node's GS
 * packet.  The HUD's list is D_00425F80 with 256 buckets at D_00425F88. */
#ifndef KH1_GFX_DRAWLIST_H
#define KH1_GFX_DRAWLIST_H

#include "common.h"

typedef struct DrawNode {
    struct DrawNode *next;
    s32 kind; /* 1, 2, 3: a projected primitive, 4: a raw GS packet */
} DrawNode;

typedef struct {
    DrawNode *head;
    s32 n;
} DrawBucket;

typedef struct {
    s32 bits;
    DrawBucket *tbl;
} DrawList;

void func_00237660(DrawList *l, DrawBucket *tbl, s32 bits);

#endif /* KH1_GFX_DRAWLIST_H */
