/* The depth-sorted draw list, its nostrict part (docs/modules.md "Session
 * 45"): func_00237680(l, node, i) pushes a node on bucket i (clamped to the
 * list) and func_00237ec0(src, dst) copies a kind 4 node's raw packet (its
 * qword count at word 2, the qwords after the node's head) behind a DMA cnt
 * tag. */
#include "common.h"
#include "gfx/drawlist.h"

typedef kh1_s128 u128;

void func_00237680(DrawList *h, DrawNode *node, s32 idx) {
    s32 max = 1 << h->bits;
    if (idx < 0) idx = 0;
    if (idx >= max) idx = max - 1;
    node->next = h->tbl[idx].head;
    h->tbl[idx].head = node;
}

/* func_002376c8 ... func_00237d48 are in drawlist.nostrict_nofill.c. */

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
