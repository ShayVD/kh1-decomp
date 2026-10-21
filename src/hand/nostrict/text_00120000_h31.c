#include "common.h"

typedef union Arg { s32 i; u32 u; f32 f; void *p; } Arg;
typedef struct Ctx { u16 *pc; Arg *sp; } Ctx;
typedef struct Node {
    union {
        u64 flags;
        struct { u32 lo; u16 *code; } w;
    } u;
    Ctx ctx;
} Node;
typedef struct { s32 a, b; } Pair;
extern union { Node *p; u64 x; } D_00514F10;
extern void func_0012ba30(Node *, s32, s32);
extern s32 func_0012ba48(Node *);
extern void func_0013cf28(Ctx *, s32);
void func_0012bbc8(Node *n, s32 ofs, s32 cnt, Pair *pr, s32 arg) {
    Arg buf[256];
    Node *save;
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

typedef struct { u8 pad[0x4c]; u16 f4c; } S4c;
typedef struct { u8 pad[0x130]; S4c *f130; } E11;
typedef struct { u8 pad[0x10]; E11 *f10; s32 f14; u8 pad18[4]; f32 f1c; u8 f20[0x40]; } T11;
typedef struct { s32 f0, f4, f8; E11 *fc; u8 pad10[0x20]; s32 f30; } P11;
typedef struct { u8 pad[0x40]; struct { u8 a, b; } t[0x58]; f32 ff0; } G1;
extern G1 *D_00308CDC;
#include "data/pieces/D_002E31A4.h"
#include "data/pieces/D_00304BE8.h"
extern void func_0012c328();
extern T11 *func_00147d18(void *);
extern P11 *func_00121e28(s32, void *);
extern void func_0013cae8(s32, s32);
void func_0012c560(E11 *e, E11 *t, s32 fl) {
    T11 *k = func_00147d18(func_0012c328);
    P11 *p;
    k->f10 = e;
    k->f14 = 0;
    p = func_00121e28(0x40, k->f20);
    p->f30 = 0xfff;
    p->f0 = 0;
    p->f8 = fl;
    p->fc = t;
    if (t == 0 || e == t) {
        p->f4 = 1;
        k->f1c = D_00308CDC->t[e->f130->f4c].a;
    } else {
        p->f4 = 2;
        k->f1c = D_00308CDC->t[e->f130->f4c].b;
    }
    if (!(fl & 0x400)) {
        if (e->f130->f4c == 0) { s32 o = ((s32)D_00304BE8); (D_002E31A4 + o)[38] = 0; }
        else func_0013cae8(e->f130->f4c, fl);
    }
}

typedef struct { u8 pad[0x10]; u8 *f10; u32 f14; } O13;
typedef struct { u8 pad[0x1c]; O13 *f1c; s32 f20; s32 f24; } S13;
typedef struct { u64 flags; u8 pad[0x14c - 8]; S13 *f14c; u8 pad150[0x1cc - 0x150]; u32 f1cc; } E13;
extern s32 func_00122ff8(void *);
extern O13 *func_00148968(E13 *, s32, s32);
extern void func_00176310(O13 *);
void func_0012c760(E13 *e) {
    S13 *s = e->f14c;
    O13 *o = s->f1c;
    if (o) {
        s32 k = o->f14 & 3;
        if (k != 1) {
            s->f1c = 0;
            return;
        }
        if ((e->flags & 0xc001) != 0xc001) {
            func_00176310(o);
            e->f14c->f1c = 0;
            return;
        }
        if (!(e->f1cc & 0x800000)) *o->f10 = k;
        return;
    }
    if (s->f24 < 0) return;
    if (s->f24 & 0x40000000) {
        s->f24 &= ~0x40000000;
        return;
    }
    if (!(e->f1cc & 0x800000)) return;
    if (func_00122ff8(e)) {
        O13 *n = func_00148968(e, e->f14c->f20, e->f14c->f24);
        e->f14c->f1c = n;
        if (n) n->f14 &= ~0x20;
    }
    e->f14c->f24 = -1;
}

typedef struct { u8 pad0[0x40]; f32 f40[4]; u8 pad50[0x15c - 0x50]; s32 f15c; u8 pad160[0x220 - 0x160]; f32 f220[4]; u8 pad230[0x370 - 0x230]; u64 f370; } E598;
extern void func_00267e90(f32 *, f32 *, f32);
extern void func_002672f8(f32 *, f32 *, f32 *);
extern void func_001219c8(f32 *, f32 *, f32 *);
extern void func_00267530(f32 *, f32 *, f32 *);
extern void func_00166570(f32 *, s32, f32);
void func_00130598(E598 *e, f32 *m, f32 a, f32 b) {
    f32 v[4];
    func_00267e90(v, e->f220, b);
    v[3] = 0.0f;
    func_002672f8(v, m, v);
    if ((s32)(e->f370 >> 45) & 1) func_001219c8(v, v, e->f40);
    func_00267530(m + 12, m + 12, v);
    m[15] = 1.0f;
    func_00166570(m, e->f15c, a);
}

