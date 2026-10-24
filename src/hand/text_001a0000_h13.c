/* Hand-matched functions in 0x001a0000-0x001c0000 (worker 13). */
#include "common.h"
#include "data/bss_0062.h"

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

#include "data/types/shared.h"

/* GS packet chain tags: 16-byte DMA tags; next at +4, list tail at +8. */
#include "data/types/text_001a0000_h13.h"

/* The original clears the tag with `sq $0`, which ee-gcc 2.96 cannot emit
 * from C (it loads a zero TImode register first); the empty asm keeps the
 * header store ahead of the clamp as in the original. */

/* Two small s32 stacks with s8 stack pointers. */

/* Returns a file's size (open, seek to end, close); exits if it is missing. */
#include "data/types/text_001a0000_h13_p.h"

/* Loads a program to 0x00F20000 and runs it. */

/* Declared as a real 2-D array: a cast to s32 (*)[2] does not match. */

/* Save data block with per-item "seen" flags at +0xAC20. */

/* Zero n bytes (the head loop clears p & 7 bytes, as in the original). */

/* Stack of 16 quadwords with a parallel s32 value per entry. The char member
 * makes the quadword stores alias n, as in the original (n is reloaded). */

/* Piecewise-linear lookup in {time, value} keys ending with a negative time. */

/* needs make: uses rodata */

/* Jump table (jtbl_00490070); checked word-for-word except the table relocs. */
#include "data/bss_0061_typed.h"
#include "data/data_0037.h"
#include "data/data_0048.h"
#include "data/data_0049.h"
