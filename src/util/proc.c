/* The frame callback lists: pools of nodes sorted by priority (func_0011efa8
 * sets a pool up, func_0011efe8 takes a node, func_0011f090(list, prio, fn)
 * inserts, func_0011f2e0 finds, func_0011f058 the previous node,
 * func_0011f228 runs a list and drops the nodes whose callback returns bit
 * 2, func_0011f320 removes, func_0011f130 another pass over a list), and the
 * main list D_004E3A48: func_0011ef10(prio, fn) adds a callback (154
 * callers), func_0011ef38 asks whether one is there, func_0011ef58 removes
 * it. Flag mode: default (the other modes are in the sibling files). Read
 * from the code, not proved by a boot (docs/modules.md "Session 54"). */
#include "m2c.h"
#include "data/pieces/D_002BCB60.h"
#include "data/bss_004D.h"
#include "data/bss_004E.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002BCDAC.h"
#include "data/pieces/D_002BD118.h"
#include "common.h"
#include "platform/math.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004F.h"
#include "data/types/text_00110000_h30.h"
#include "data/pieces/D_002C5910.h"
#include "data/pieces/D_002BC140.h"
#include "data/types/text_00110000_h30_p.h"
#include "data/pieces/D_002C58D0.h"

/* func_0011ef10 (from auto/text_00110000_1.c). */
M2C_UNK func_0011f090(M2C_UNK *, s32, s32);
extern M2C_UNK D_004E3A48;
M2C_UNK func_0011ef10(s32 arg0, s32 arg1) {
    return func_0011f090(&D_004E3A48, arg0, arg1);
}

/* func_0011ef38 (from auto/text_00110000.c). */
M2C_UNK func_0011f2e0_ef38() __asm__("func_0011f2e0");
#define func_0011f2e0 ((M2C_UNK (*)(M2C_UNK *, s32)) func_0011f2e0_ef38)
M2C_UNK func_0011ef38(s32 arg0) {
    return func_0011f2e0(&D_004E3A48, arg0);
}
#undef func_0011f2e0

/* func_0011ef58 (from auto/text_00110000_1.c). */
s32 func_0011f320();
#define func_0011f320 ((M2C_UNK (*)(M2C_UNK *, s32)) func_0011f320)
#define func_0011f2e0 ((s32 (*)(M2C_UNK *, s32)) func_0011f2e0_ef38)
void func_0011ef58(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_0011f2e0(&D_004E3A48, arg0);
    if (temp_v0 != 0) {
        func_0011f320(&D_004E3A48, temp_v0);
    }
}
#undef func_0011f320
#undef func_0011f2e0

/* func_0011efa8 (from auto/text_00110000_10.c). */
void func_0011efa8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_a1;
    s32 var_a3;

    var_a1 = arg1;
    var_a3 = arg3;
    M2C_FIELD(arg0, s16 *, 0) = (s16) arg2;
    M2C_FIELD(arg0, s16 *, 2) = (s16) var_a3;
    M2C_FIELD(arg0, s32 *, 4) = var_a1;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    if (var_a3 > 0) {
        do {
            var_a3 -= 1;
            M2C_FIELD(var_a1, s16 *, 0) = 0;
            M2C_FIELD(var_a1, s16 *, 2) = 0;
            var_a1 += arg2;
        } while (var_a3 != 0);
    }
}

/* func_0011efe8 (from hand/text_00110000_h4.c). */
typedef struct Node { u16 type; u16 f2; s32 key; struct Node *next; s32 data; } Node;
typedef struct { u16 size; u16 count; u8 *base; Node *head; u8 *cur; } Pool;
u8 *func_0011efe8(Pool *p) {
    u8 *cur = p->cur;
    u8 *base;
    u8 *end;
    s32 i;
    if (cur == 0) cur = p->base;
    base = p->base;
    end = base + p->size * p->count;
    for (i = 0; i < p->count; i++) {
        cur += p->size;
        if (cur >= end) cur = base;
        if (*(u16 *)cur == 0) return cur;
    }
    return 0;
}

/* func_0011f058 (from auto/text_00110000.c). */
void *func_0011f058(void *arg0, s32 arg1) {
    void *var_v0;
    void *var_v1;

    var_v1 = M2C_FIELD(arg0, void **, 8);
    var_v0 = NULL;
    if ((var_v1 != NULL) && (var_v1 != arg1)) {
loop_2:
        var_v0 = var_v1;
        var_v1 = M2C_FIELD(var_v0, void **, 8);
        if (var_v1 != NULL) {
            if (var_v1 != arg1) {
                goto loop_2;
            }
        }
    }
    return var_v0;
}

/* func_0011f130 (from hand/text_00110000_h30.c). */
void func_0015f010(void);
#define func_0011f058 ((TNode *(*)(TPool *, TNode *)) func_0011f058)
s32 func_0011f130(TPool *p, u32 mask) {
    TNode *prev = 0;
    TNode *n;
    s32 cnt = 0;
    s32 r;
    for (n = p->head; n; n = n->next) {
        if ((n->mask & mask) != mask) continue;
        r = n->fn(n);
        func_0015f010();
        n->flags &= ~0x10;
        if (r & 4) {
            if (prev) {
                if (prev->next != n) prev = func_0011f058(p, n);
                prev->next = n->next;
            } else {
                p->head = n->next;
            }
            n->flags = 0;
        } else {
            prev = n;
        }
        cnt++;
        if (r & 8) break;
    }
    p->cur = 0;
    return cnt;
}
#undef func_0011f058

/* func_0011f228 (from hand/text_00110000_h30.c). */
#define func_0011f058 ((TNode *(*)(TPool *, TNode *)) func_0011f058)
s32 func_0011f228(TPool *p, s32 (*fn)(TNode *)) {
    s32 cnt = 0;
    TNode *n, *prev;
    for (n = p->head; n; n = n->next, cnt++) {
        if ((n->flags | fn(n)) & 4) {
            prev = func_0011f058(p, n);
            if (prev) prev->next = n->next;
            else p->head = n->next;
            n->flags = 0;
        }
    }
    return cnt;
}
#undef func_0011f058

/* func_0011f2d0 (from auto/text_00110000.c). */
s32 func_0011f2d0(u16 *arg0) {
    return *arg0 & 1;
}

/* func_0011f2e0 (from hand/text_00110000_h4.c). */
Node *func_0011f2e0(Pool *p, s32 data) {
    Node *it;
    for (it = p->head; it; it = it->next) {
        if (it->data == data) return it;
    }
    return 0;
}

/* func_0011f320 (from hand/text_00110000_h4.c). */
s32 func_0011f320(Pool *p, Node *n) {
    Node *it, *prev = 0;
    for (it = p->head; it; it = it->next) {
        if (it == n) {
            if (prev) prev->next = it->next; else p->head = it->next;
            it->next = 0;
            return 1;
        }
        prev = it;
    }
    return 0;
}

