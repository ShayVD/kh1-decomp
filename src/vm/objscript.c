/* The object scripts: 64 script nodes D_004F8310 (func_0012b738 sets them up
 * with the command table descriptor D_002E2F20, func_0012b7a8 takes a free
 * one, func_0012b9b0 frees a chain), each running the stack VM of
 * src/vm/stackvm.nostrict.c on its own code (func_0012ba48 runs one node,
 * func_0012ba98 a node and its chain; func_0012bbc8 / func_0012bce0 call a
 * script entry with arguments; func_0012ba30 pushes one). The commands the
 * scripts call are 0x00128c60-0x0012b738. Flag mode: default (the other
 * modes are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 54"). */
#include "common.h"
#include "data/bss_004F.h"
#include "data/bss_0051.h"
#include "data/bss_0052.h"
#include "data/types/text_00120000_h5.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002E31B8.h"
#include "data/types/text_00120000_h31_p.h"
#include "data/pieces/D_002E26AC.h"
#include "data/pieces/D_00308CDC.h"
#include "data/types/text_00120000_h31.h"
#include "data/pieces/D_00351BC8.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002BC098.h"
#include "m2c.h"
#include "data/pieces/D_002E2F28.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_002BBDE4.h"
#include "actor.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_002C6440.h"

/* func_0012b738 (from hand/text_00120000_h5.c). */
extern Node D_004F8310[64];
extern u8 D_002E2F20[];
extern union { Node *p; u64 x; } D_00514F10;
void func_0012b738(void) {
    s32 i;
    u8 *q;
    Node *n = D_004F8310;
    for (i = 0; i < 64; i++, n++) {
        n->flags &= ~1ULL;
        n->f18 = D_002E2F20;
    }
    q = D_00524F20;
    q += 31;
    for (i = 31; i >= 0; i--) *q-- = 0;
    D_00514F10.p = 0;
}

/* func_0012b888 (from hand/text_00120000_h31.c). */
typedef struct { u8 pad[0x14]; u8 *f14; } N2;
extern N2 *func_0012b7a8();
extern void *memset(void *, s32, u32);
N2 *func_0012b888(s32 a) {
    N2 *n = func_0012b7a8(a);
    s32 i;
    u8 *p;
    for (i = 0; i < 32; i++) {
        if (D_00524F20[i] == 0) break;
    }
    D_00524F20[i] = 1;
    p = D_00514F20 + i * 2048;
    memset(p, 0, 2048);
    n->f14 = p;
    return n;
}

/* func_0012b930 (from hand/text_00120000_h5.c). */
#define func_0012b7a8 ((Node *(*)(s32)) func_0012b7a8)
Node *func_0012b930(Node *a, s32 b) {
    Node *n = func_0012b7a8(b);
    Node *t;
    n->flags |= 4;
    n->f14 = a->f14;
    for (t = a; t->next; t = t->next);
    t->next = n;
    return n;
}
#undef func_0012b7a8

/* func_0012b9b0 (from hand/text_00120000_h5.c). */
void func_0012b9b0(Node *a) {
    if (a->flags & 4) {
        a->flags &= ~2ULL;
        return;
    }
    D_00524F20[((u8 *)a->f14 - D_00514F20) / 2048] = 0;
    do {
        a->flags &= ~1ULL;
        a = a->next;
    } while (a);
}

/* func_0012ba30 (from auto/text_00120000.c). */
M2C_UNK func_0013cec8(s32);
void func_0012ba30(s32 arg0) {
    func_0013cec8(arg0 + 8);
}

/* func_0012ba48 (from hand/text_00120000_h5.c). */
extern Node *D_00514F14;
s32 func_0013cfe8(void *, s32, Node *);
s32 func_0012ba48(Node *n) {
    Node *t = D_00514F14;
    s32 r;
    D_00514F14 = n;
    r = func_0013cfe8((u8 *)n + 8, 0, n);
    D_00514F14 = t;
    return r;
}

/* func_0012ba98 (from hand/text_00120000_h5.c). */
s32 func_0012ba98(Node *a) {
    Node *save = D_00514F10.p;
    Node *n, *prev;
    s32 cnt;
    D_00514F10.p = a;
    if ((a->flags & 2) && func_0012ba48(a) < 0) a->flags &= ~2;
    prev = a;
    cnt = 0;
    for (n = a->next; n; n = n->next) {
        if (!(n->flags & 2)) {
            n->flags &= ~1;
            prev->next = n->next;
        } else {
            if ((n->flags & 8) || func_0012ba48(n) < 0) n->flags |= 8;
            else cnt++;
            prev = n;
        }
    }
    D_00514F10.p = save;
    if (!(a->flags & 2) && cnt == 0) {
        func_0012b9b0(a);
        return -1;
    }
    return 0;
}

/* func_0012bce0 (from auto/text_00120000_3.c). */
void func_0012bbc8(s32, s32, s32, s32, s32);
void func_0012bce0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_0012bbc8(arg0, (s32) M2C_FIELD(((arg1 * 2) + arg0), u16 *, 0x724), arg2, arg3, arg4);
}

/* func_0012bd00 (from auto/text_00120000_5.c). */
void func_0012bd00(void *arg0, void *arg1) {
    f32 temp_f0;
    void *temp_a1;
    void *temp_v0;

    if (arg0 != NULL) {
        temp_a1 = M2C_FIELD(arg1, void **, 0x6C);
        if (temp_a1 != NULL) {
            temp_v0 = M2C_FIELD(arg0, void **, 0x24);
            temp_f0 = M2C_FIELD(temp_a1, f32 *, 0x64);
            M2C_FIELD(temp_v0, f32 *, 8) = temp_f0;
            M2C_FIELD(temp_v0, f32 *, 4) = temp_f0;
            M2C_FIELD(temp_v0, f32 *, 0) = temp_f0;
        }
    }
}

