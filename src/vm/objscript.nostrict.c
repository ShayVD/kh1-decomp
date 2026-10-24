/* The object scripts: 64 script nodes D_004F8310 (func_0012b738 sets them up
 * with the command table descriptor D_002E2F20, func_0012b7a8 takes a free
 * one, func_0012b9b0 frees a chain), each running the stack VM of
 * src/vm/stackvm.nostrict.c on its own code (func_0012ba48 runs one node,
 * func_0012ba98 a node and its chain; func_0012bbc8 / func_0012bce0 call a
 * script entry with arguments; func_0012ba30 pushes one). The commands the
 * scripts call are 0x00128c60-0x0012b738. Flag mode: nostrict (the other
 * modes are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 54"). */
#include "common.h"
#include "data/pieces/D_002E31B0.h"
#include "data/bss_0052.h"
#include "data/pieces/D_002E3170.h"
#include "data/pieces/D_002E319C.h"
#include "data/pieces/D_002E31A0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_00308CDC.h"

/* func_0012b7a8 (from hand/nostrict/text_00120000_s6_05.c). */
typedef struct Node {
    union {
        u64 flags;
        struct { s32 w0; s32 f4; } w;
    };
    s32 f8;
    s32 *cur;
    s32 *f10;
    u8 pad014[0xc];
    s32 l20[0x100];
    s32 l420[0xc0];
    struct Node *next;
    s16 h724[6];
} Node;
extern Node D_004F8310[64];
Node *func_0012b7a8(s32 a) {
    Node *n = D_004F8310;
    s32 i;
    for (i = 0; i < 64; i++, n++) {
        if (!(n->flags & 1)) {
            n->w.w0 = 0;
            n->flags |= 1;
            n->flags |= 2;
            n->f8 = a;
            n->w.f4 = a;
            n->cur = n->l20;
            *n->cur++ = 0;
            *n->cur++ = 0;
            *n->cur++ = 0;
            *n->cur++ = 0;
            n->f10 = n->l420;
            n->next = 0;
            { s32 j; for (j = 0; j < 5; j++) n->h724[j] = 0; }
            break;
        }
    }
    return n;
}

/* func_0012bbc8 (from hand/nostrict/text_00120000_h31.c). */
typedef union Arg { s32 i; u32 u; f32 f; void *p; } Arg;
typedef struct Ctx { u16 *pc; Arg *sp; } Ctx;
typedef struct Node_2bbc8 {
    union {
        u64 flags;
        struct { u32 lo; u16 *code; } w;
    } u;
    Ctx ctx;
} Node_2bbc8;
typedef struct { s32 a, b; } Pair;
extern union { Node_2bbc8 *p; u64 x; } D_00514F10;
extern void func_0012ba30(Node_2bbc8 *, s32, s32);
extern s32 func_0012ba48(Node_2bbc8 *);
extern void func_0013cf28(Ctx *, s32);
void func_0012bbc8(Node_2bbc8 *n, s32 ofs, s32 cnt, Pair *pr, s32 arg) {
    Arg buf[256];
    Node_2bbc8 *save;
    Ctx *c;
    u16 *opc;
    Arg *osp;
    s32 i;
    if (ofs == 0) return;
    save = D_00514F10.p;
    D_00514F10.p = n;
    for (i = 0; i < cnt; i++) func_0012ba30(n, pr[i].a, pr[i].b);
    c = &n->ctx;
    opc = c->pc;
    osp = c->sp;
    c->pc = n->u.w.code + ofs;
    c->sp = buf;
    { Arg **spp = &n->ctx.sp; (*spp)++->i = 0; (*spp)++->i = 0; (*spp)++->i = 0; (*spp)++->i = 0; }
    func_0012ba48(n);
    c->pc = opc;
    c->sp = osp;
    if (arg) func_0013cf28(c, arg);
    D_00514F10.p = save;
}

