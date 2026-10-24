/* The KeTh node updates, -fno-strict-aliasing (docs/modules.md "Session 49"),
 * with keth.c: func_001a7c50 moves one node along its path (the step
 * functions D_00372750: libvu0's sceVu0RotMatrixZ / X / Y) and grows or cuts
 * its strip, taking new nodes from the pool; func_001a8780 starts a node's
 * header and its GIF tag; func_001a8ae8 runs a group's nodes (pppKeThFrame)
 * and frees the finished ones; func_001a8c40 sends each node's packet from
 * kethdraw.nostrict.c's func_001a7718 on DMA channel 2 (pppKeThDraw).
 * Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/gs.h"
#include "platform/dma.h"

typedef int u128 __attribute__((mode(TI)));
typedef f32 Vec[4] __attribute__((aligned(16)));
typedef f32 Mtx[4][4] __attribute__((aligned(16)));

typedef struct Path {
    f32 pos[3];
    f32 k;          /* 0x0c */
    f32 r1;         /* 0x10 */
    f32 dw;         /* 0x14 */
    f32 r0;         /* 0x18 */
    struct Path *next; /* 0x1c */
} Path;

struct Obj;

typedef struct {
    f32 pos[3];
    f32 w;          /* 0x0c */
    u8 pad10[8];
    struct Obj *chain; /* 0x18 */
    f32 f1c;        /* 0x1c */
    Vec v20;        /* 0x20 */
} Vtx;

typedef struct Obj {
    struct Obj *next;   /* 0x00 */
    struct Obj *prev;   /* 0x04 */
    struct Lnk { struct Obj *next; struct Obj **pprev; } link; /* 0x08 */
    u8 pad10[4];
    Path *path;         /* 0x14 */
    f32 f18;            /* 0x18 */
    u16 n1c;            /* 0x1c */
    u8 b1e;             /* 0x1e */
    u8 pad1f[0x11];
    f32 f30;            /* 0x30 */
    u16 n34;            /* 0x34 */
    u8 b36;             /* 0x36 */
    u8 b37;             /* 0x37 */
    u16 n38;            /* 0x38 */
    u16 pad3a;
    u16 n3c;            /* 0x3c */
    u16 f3e;            /* 0x3e */
    Vtx v[1];           /* 0x40 */
} Obj;

typedef struct {
    u8 pad0[0x20];
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2c;
    u8 pad30[4];
    f32 f34;
    u8 pad38[4];
    f32 f3c;
    u8 b40;
    u8 b41;
    u8 b42;
} Cfg;

typedef struct {
    u8 pad0;
    u8 b1;
} Pool;

typedef struct {
    u8 pad0[0x40];
    Obj *o;     /* 0x40 */
    Path *p44;  /* 0x44 */
    Pool *pool; /* 0x48 */
    Cfg *c;     /* 0x4c */
} A7c50;

typedef struct {
    Obj *o;
    u8 n;
} Msg;

typedef struct {
    f32 scl;
    f32 dist;
    f32 w;
    f32 w0;
    f32 r1;
    f32 r0;
    f32 dw;
    f32 k;
} Q;

extern void (*D_00372750[])(Mtx, A7c50 *, f32);
void func_001a67b8(Vtx *, s32);
s32 func_001a8f30(void);
Obj *func_001a8900(Pool *);
void func_001a8780();  /* defined below with its own view (Bld8) */
void func_001a9098(void *, void *);
f32 func_001a9350(f32 *);
void func_002672f8(f32 *, Mtx, f32 *);
void func_002673b8(f32 *, f32 *);
void func_002674f0(f32 *, f32 *, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_002675a8(f32 *, f32 *);

void func_001a7c50(A7c50 *a) {
    Mtx m;
    Vec d;
    Vec dir;
    Vec cur;
    Vec tgt;
    Q q;
    Vec sA0;
    Vec sB0;
    Vec sC0;
    Msg msg;
    Obj *o;
    s32 fl;
    Vtx *base;
    s32 pos;
    s32 ti;
    s32 rem;
    s32 lim2;
    s32 size;
    s32 lim;
    s32 ok;
    s32 nrm;
    f32 t;
    f32 nt;
    Cfg *c;
    s32 ni;
    s32 k;
    s32 adv;
    s32 extra;
    s32 s0;
    Path *p;
    s32 head;
    Vtx *v;
    Vtx *prev;
    s32 i;
    s32 r;
    f32 f;
    Obj *no;
    Obj *ch;
    Vtx *cv;

    o = a->o;
    fl = o->f3e;
    if (fl & 0x800) {
        fl |= 0x40;
        fl &= 0xf7ff;
    }
    if (fl & 8) {
        if (!(fl & 0x20)) {
            fl |= 0x10;
            o->f3e = fl;
            return;
        }
        fl &= ~8;
        fl |= 0x100;
    }
    base = o->v;
    t = o->f18;
    c = a->c;
    ti = t;
    ok = 0;
    lim = c->b41;
    pos = o->n1c;
    size = o->b37;
    if (lim != 255) ok = o->b1e < c->b40;
    nt = t + c->f34;
    nrm = (u16)(o->f3e & 0x400);
    ni = nt;
    i = ni - ti;
    adv = i;
    if (!(fl & 2)) {
        t = nt;
        if (!(fl & 4)) {
            k = c->b42;
            if (ni >= k) {
                if (fl & 0x80) fl |= 0x20;
                if (!(fl & 0x20)) {
                    adv = ni - k;
                    t = k;
                    i -= adv;
                } else {
                    adv = ni - k;
                    fl |= 4;
                    fl &= ~0x200;
                }
            }
        }
        extra = i;
    } else {
        extra = 0;
    }
    s0 = fl & 0x20;
    if (!s0) {
        adv = 0;
        if (fl & 0x100) {
            p = a->p44;
            o->path = p;
        } else {
            p = o->path;
        }
    } else {
        p = o->path;
        pos += adv;
        if (!p) {
            o->f3e |= 0x10;
            return;
        }
        if (pos >= ti) {
            o->f3e |= 0x10;
            return;
        }
    }
    head = o->n34;
    v = base + head;
    for (i = adv; i > 0; i--) {
        func_001a67b8(v++, s0);
        if (++head == size) {
            v = base;
            head = 0;
        }
    }
    o->n34 = head;
    o->f30 += (f32)adv;
        rem = ti - pos;
    i = 0;
    lim2 = rem + extra;
    q.scl = a->c->f20;
    q.w0 = a->c->f2c;
    q.r1 = p->r1;
    q.r0 = p->r0;
    q.dw = p->dw;
    q.k = p->k;
    func_002675a8(tgt, p->pos);
    func_001a9098(dir, v->v20);
    dir[3] = 0.0f;
    func_002675a8(cur, v->pos);
    if ((fl & 0x120) == 0x100) {
        func_00267530(d, tgt, cur);
        q.dist = func_001a9350(d);
        q.w = q.w0;
        if (q.dist < q.r1) q.w = q.w0 + (q.dw - q.dw * (q.dist - q.r0) / (q.r1 - q.r0));
        func_002673b8(d, d);
        func_002674f0(dir, d, dir, q.w);
        if (nrm) func_002673b8(dir, dir);
        r = func_001a8f30();
        D_00372750[r % 3](m, a, a->c->f28 * (f32)(r % 1001 - 500) / 500.0f);
        func_002672f8(dir, m, dir);
        func_002674f0(dir, dir, v->v20, a->c->f24);
        if (nrm) func_002673b8(dir, dir);
    }
    for (;;) {
        func_00267530(d, tgt, cur);
        q.dist = func_001a9350(d);
        if ((q.k != 0.0f && p->r0 < q.dist) || (q.k == 0.0f && q.dist < p->r0)) {
            if (!p->next) {
                o->b36 = head;
                t = pos + i;
                i++;
                fl |= 0x800;
                for (; i <= rem; i++) {
                    if (++head == size) {
                        head = 0;
                        v = base;
                    } else {
                        v++;
                    }
                    func_001a67b8(v, fl & 0x20);
                }
                if (fl & 0x80) fl |= 0x20;
                break;
            }
            p = p->next;
            func_002675a8(tgt, p->pos);
            if (i == 0) o->path = p;
            q.r1 = p->r1;
            q.r0 = p->r0;
            q.dw = p->dw;
            q.k = p->k;
        }
        i++;
        if (lim2 < i) {
            o->b36 = head;
            break;
        }
        prev = v;
        if (++head == size) {
            head = 0;
            v = base;
        } else {
            v++;
        }
        func_002675a8(sB0, cur);
        func_001a9098(sA0, dir);
        func_00267560(sC0, dir, q.scl);
        func_00267518(cur, cur, sC0);
        func_001a9098(v->pos, cur);
        q.w = q.w0;
        if (q.dist < q.r1) q.w = q.w0 + (q.dw - q.dw * (q.dist - q.r0) / (q.r1 - q.r0));
        func_002673b8(d, d);
        func_002674f0(dir, d, dir, q.w);
        if (nrm) func_002673b8(dir, dir);
        r = func_001a8f30();
        D_00372750[r % 3](m, a, a->c->f28 * (f32)(r % 1001 - 500) / 500.0f);
        func_002672f8(dir, m, dir);
        if (i <= rem) {
                        func_002674f0(dir, dir, v->v20, a->c->f24);
            if (nrm) func_002673b8(dir, dir);
            f = (2.0f * ((f32)r / 2147483647.0f) + -1.0f) * a->c->f3c; f += prev->f1c;
            if (f > 1.0f) f = 1.0f;
            else if (f < 0.0f) f = 0.0f;
            v->f1c += (f - v->f1c) * a->c->f24;
            for (ch = v->chain; ch; ch = ch->link.next) {
                cv = &ch->v[ch->n34];
                func_001a9098(cv->pos, sB0);
                func_001a9098(cv->v20, sA0);
                cv->f1c = v->f1c;
                ch->path = p;
            }
        } else {
            v->chain = 0;
            v->w = 1.0f;
            f = (2.0f * ((f32)r / 2147483647.0f) + -1.0f) * a->c->f3c; f += prev->f1c;
            if (f > 1.0f) f = 1.0f;
            else if (f < 0.0f) f = 0.0f;
            v->f1c = f;
                        if (ok && !(r & lim)) {
                no = func_001a8900(a->pool);
                if (no) {
                    o->b1e++;
                    msg.o = no;
                    msg.n = a->pool->b1;
                    func_001a8780(&msg);
                    no->f3e |= o->f3e & 0x1400;
                    no->path = p;
                    no->b1e = o->b1e;
                    no->f30 = o->f30 + (f32)ti + (f32)i - (f32)rem;
                    func_001a9098(no->v[0].pos, sB0);
                    func_001a9098(no->v[0].v20, sA0);
                    no->v[0].f1c = prev->f1c;
                    if (o->next) o->next->prev = no;
                    no->next = o->next;
                    no->prev = o;
                    o->next = no;
                    {
                        struct Lnk *ln = &no->link;
                        if (v->chain) v->chain->link.pprev = &ln->next;
                        ln->next = v->chain;
                        ln->pprev = &v->chain;
                    }
                    v->chain = no;
                } else {
                    ok = 0;
                }
                                if (o->b1e >= a->c->b40) ok = 0;
            }
        }
        func_001a9098(v->v20, dir);
    }
    i = o->n34;
    head = o->b36;
    if (i < head) {
        o->n3c = 0;
        o->n38 = head - i + 1;
    } else if (head < i) {
        o->n3c = head + 1;
        o->n38 = o->b37 - i;
    } else {
        o->n38 = 0;
        o->n3c = 0;
    }
    o->f18 = t;
    o->n1c = pos;
    o->f3e = fl;
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
void func_002676c0();
void func_00267768();
void func_00267810();
void (*D_00372750[0x4])(Mtx, A7c50 *, f32) ALIGNED(16) = {
    (void *)func_00267768, (void *)func_00267810, (void *)func_002676c0, 0,
};

typedef struct { s32 w[4]; } Q4;
typedef struct Hdr8 {
    s32 w0, w4, w8, wc;
    struct Hdr8 *self; s32 w14; s32 w18; s16 h1c; u8 b1e; u8 p1f;
    s16 h20; u8 p22; u8 b23; u8 p24[4]; s32 w28; u8 p2c[8];
    s16 h34; u8 b36; u8 b37; s16 h38; u8 p3a[2]; s16 h3c; s16 h3e;
    u8 p40[12]; f32 f4c; u8 p50[8]; s32 w58;
} Hdr8;
typedef struct { Hdr8 *h; u8 n; } Bld8;

void func_001a8780(Bld8 *b) {
    Hdr8 *h = b->h;
    Q4 *q;
    h->h3e = 0;
    h->self = h;
    h->b37 = b->n;
    h->f4c = 1.0f;
    h->w18 = 0;
    h->h34 = 0;
    h->b36 = 0;
    h->h3c = 0;
    h->h38 = 0;
    h->b23 = 112;
    q = (Q4 *)h->p40 + h->b37 * 3;
    h->h20 = h->b37 * 3 + 2;
    h->b1e = 0;
    h->w14 = 0;
    h->w28 = 0x040000B0;
    h->w4 = 0;
    h->w0 = 0;
    h->wc = 0;
    h->w8 = 0;
    h->w58 = 0;
    h->h1c = 0;
    q->w[1] = 0x11000000;
    q->w[3] = 0x11000000;
    q->w[2] = 0x14000000;
    q->w[0] = 0;
}


typedef f32 Mtx4[4][4];
void sceVu0UnitMatrix(f32 (*)[4]);
typedef struct { u8 a[0x20]; u8 b[0x10]; } NdSlot;
typedef struct Nd {
    struct Nd *next;
    struct Nd **pprev;
    u8 pad8[0x2c];
    u16 idx;
    u8 pad36[8];
    u16 fl;
    NdSlot sl[1];
} Nd;
typedef struct { Nd *first; u8 fl; } NdHead;
typedef struct { u8 pad[4]; Nd *free; } NdPool;
typedef struct { NdHead *h; void *x4; void *x8; NdPool *pool; void *x10; void *x14; } NdArg;
typedef struct { Mtx4 m; Nd *n; void *x4; NdPool *pool; void *x8; } NdCtx;
void func_001a8828(Nd *);

void func_001a8ae8(NdArg *a) {
    NdHead *h = a->h;
    NdCtx c;
    Nd *n, *cur;
    s32 fl = 0;

    if (h->fl & 2) {
        fl = 0x20;
        h->fl &= ~2;
    }
    sceVu0UnitMatrix(c.m);
    c.x4 = a->x4;
    c.pool = a->pool;
    c.x8 = a->x8;
    n = h->first;
    while (n) {
        if (n->fl & 0x200) {
            func_001a9098(n->sl[n->idx].a, a->x10);
            func_001a9098(n->sl[n->idx].b, a->x14);
        }
        if (n->fl & 0x100)
            n->fl |= fl;
        c.n = n;
        func_001a7c50((A7c50 *)&c);
        if (n->fl & 0x10) {
            cur = n;
            n = n->next;
            if (cur->next)
                cur->next->pprev = cur->pprev;
            *cur->pprev = cur->next;
            func_001a8828(cur);
            cur->next = a->pool->free;
            a->pool->free = cur;
        } else {
            n = n->next;
        }
    }
}

typedef struct TNd { struct TNd *next; } TNd;
typedef union { u128 q; struct { u16 qwc; u8 b2; u8 id; } s; } Tag;
typedef struct { s32 a; TNd *n; u8 *end; s32 c; s32 b; u64 *flag; s64 d; s64 e; } Ctx;
void FlushCache(s32);
s32 func_001a7718(Ctx *);

void func_001a8c40(TNd **list, s32 a, s32 b, s32 c, u8 **buf, s64 d, s64 e) {
    Ctx x;
    PlatDmaChan *ch = PlatDmaGetChan(2);
    TNd *n = *list;
    Tag *t;
    x.c = c;
    x.a = a;
    x.b = b;
    x.d = d;
    x.e = e;
    PlatGsSyncPath(0, 0);
    for (; n; n = n->next) {
        x.n = n;
        x.end = *buf + 16;
        if (func_001a7718(&x)) {
            t = (Tag *)*buf;
            t->q = 0;
            t->s.id = 0x70;
            *x.flag |= 0x8000;
            t->s.qwc = (u32)(x.end - *buf) / 16 - 1;
            FlushCache(0);
            PlatDmaSend(ch, t);
            PlatGsSyncPath(0, 0);
        }
    }
}
