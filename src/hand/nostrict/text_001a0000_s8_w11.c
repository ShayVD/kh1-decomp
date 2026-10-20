#include "common.h"
#include "ppp.h"

typedef int u128 __attribute__((mode(TI)));
typedef f32 KkV4[4] __attribute__((aligned(16)));
typedef f32 KkMtx[4][4] __attribute__((aligned(16)));

typedef struct {
    u8 pad[0x10];
    KkMtx m;    /* +0x10 */
    KkMtx m2;   /* +0x50 */
} KkCam;

typedef struct {
    u8 pad0[8];
    u32 w8;
    u32 wC;
} KkTex;

typedef struct {
    u8 pad0[4];
    s32 off4;
    u8 pad8[0xE];
    u8 b16;
    u8 b17;
} KkTexHdr;

typedef struct {
    u8 pad0[0x1C];
    KkTexHdr *tex;
    u8 pad20[4];
} KkShape;

typedef struct {
    u8 pad0[0x10];
    KkShape *shapes;
} KkSys;

typedef struct {
    s32 frame;
    s32 id;        /* +0x4 */
    f32 w;         /* +0x8 */
    f32 len;       /* +0xC */
    f32 sc[8];     /* +0x10 */
    u8 flag;       /* +0x30 */
} KkKey;

typedef struct {
    u8 pad[8];
    u8 c[4];
} KkCol;

typedef struct {
    u128 tag;      /* +0x00 */
    u64 gif;       /* +0x10 */
    u64 regs;      /* +0x18 */
    u32 tex0[2];   /* +0x20 */
    u64 tex0r;     /* +0x28 */
    u32 tex1[2];   /* +0x30 */
    u64 tex1r;     /* +0x38 */
    u128 q;        /* +0x40 */
    u64 gif2;      /* +0x50 */
    u64 regs2;     /* +0x58 */
} KkPkt;

typedef union {
    f32 f;
    s32 i;
} KkW;

typedef struct {
    u8 pad[0x30];
    u128 q;
} KkGs;

extern KkSys *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
extern KkCam *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
extern KkMtx D_00615FC0;
extern KkMtx D_00616040; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
extern KkGs D_0061E800;
extern s8 D_00372EA0;
extern s32 D_00372EA8[];

#include "platform/math.h"
void sceVu0MulMatrix(KkMtx, KkMtx, KkMtx);
void func_002672f8(f32 *, KkMtx, f32 *);
void func_002675a8(f32 *, f32 *);
void func_00267e90(f32 *, f32 *, f32);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_002673b8(f32 *, f32 *);
void func_002675e0(s32 *, f32 *);
s32 func_00267ea8(f32 *);
void FlushCache(s32);
s32 func_00266c08(s32);
void func_00266f38(s32, s32);
void sceGsSyncPath(s32, s32);

static inline f32 kkSqrt(f32 x) {
    f32 r;
    __asm__ volatile(".set noreorder\n\tsqrt.s %0, %1\n\t.set reorder" : "=f"(r) : "f"(x));
    return r;
}

static inline s32 kkPush(s32 n) {
    s8 *sp = &D_00372EA0;
    s32 *st = D_00372EA8;
    s32 i = *sp;
    s32 v = st[i];
    i++;
    *sp = i;
    st[i] = v + n;
    return v;
}

void pppRyjDrawKekotoDraw(u8 *obj, KkKey *key, PppEntry *e)
{
    KkV4 v0, v1;
    KkV4 c[8];
    s32 d[8][4] __attribute__((aligned(16)));
    s32 col0[4], col1[4];
    f32 inv[2];
    KkV4 dir, perp, tmp;
    KkV4 a, b;
    KkMtx mtx;
    KkV4 a2, b2;
    KkMtx mtx2;
    KkV4 *pos;
    KkCol *col;
    f32 r0, r1;
    s32 i, j;
    s8 *spp;
    s32 *st;
    s32 k, k1, v;
    KkTexHdr *th;
    KkTex *tx;
    KkPkt *p;
    KkW *out;
    s32 dma;
    u64 *tag;
    s32 cnt;
    KkV4 *src;
    s32 (*dp)[4];
    s32 *cs;

    pos = (KkV4 *) (obj + e->offsets[2] + 0xA0);
    col = (KkCol *) (obj + e->offsets[0] + 0xA0);
    if (key->id == 0xFFFF) return;
    v0[0] = -key->w;
    v0[1] = 0.0f;
    v0[2] = 0.0f;
    v0[3] = 1.0f;
    v1[0] = key->w;
    v1[1] = 0.0f;
    v1[2] = 0.0f;
    v1[3] = 1.0f;
    if (key->flag) {
        sceVu0MulMatrix(mtx, D_00615FC0, D_00615E68->m);
        func_002672f8(a, mtx, v0);
        func_002675a8(b, a);
        b[0] += key->len;
        func_002672f8(a, D_00616040, a);
        func_002672f8(b, D_00616040, b);
        if (a[3] > 0.0f && b[3] > 0.0f) {
            a[3] = 1.0f / a[3];
            func_00267e90(a, a, a[3]);
            b[3] = 1.0f / b[3];
            func_00267e90(b, b, b[3]);
            func_00267530(a, a, b);
            r0 = PlatSqrtf(a[0] * a[0] + a[1] * a[1]);
        } else {
            r0 = 0.0f;
        }
        func_002672f8(a, mtx, v1);
        func_002675a8(b, a);
        b[0] += key->len;
        func_002672f8(a, D_00616040, a);
        func_002672f8(b, D_00616040, b);
        if (a[3] > 0.0f && b[3] > 0.0f) {
            a[3] = 1.0f / a[3];
            func_00267e90(a, a, a[3]);
            b[3] = 1.0f / b[3];
            func_00267e90(b, b, b[3]);
            func_00267530(a, a, b);
            r1 = kkSqrt(a[0] * a[0] + a[1] * a[1]);
        } else {
            r1 = 0.0f;
        }
        if (r0 == 0.0f && r1 == 0.0f) return;
    } else {
        sceVu0MulMatrix(mtx2, D_00615FC0, D_00615E68->m);
        a2[0] = a2[1] = a2[2] = 0.0f;
        a2[3] = 1.0f;
        func_002672f8(a2, mtx2, a2);
        func_002675a8(b2, a2);
        b2[0] += key->len;
        func_002672f8(a2, D_00616040, a2);
        func_002672f8(b2, D_00616040, b2);
        if (a2[3] > 0.0f && b2[3] > 0.0f) {
            a2[3] = 1.0f / a2[3];
            func_00267e90(a2, a2, a2[3]);
            b2[3] = 1.0f / b2[3];
            func_00267e90(b2, b2, b2[3]);
            func_00267530(a2, a2, b2);
            r0 = r1 = PlatSqrtf(a2[0] * a2[0] + a2[1] * a2[1]);
        } else {
            r0 = r1 = 0.0f;
        }
    }
    func_002672f8(c[2], D_00615E68->m2, v0);
    func_002672f8(c[4], D_00615E68->m2, v1);
    if (c[2][3] <= 0.0f && c[4][3] <= 0.0f) return;
    if (c[2][3] > 0.0f) {
        inv[0] = c[2][3] = 1.0f / c[2][3];
        func_00267e90(c[2], c[2], inv[0]);
    }
    if (c[4][3] > 0.0f) {
        inv[1] = c[4][3] = 1.0f / c[4][3];
        func_00267e90(c[4], c[4], inv[1]);
    }
    dir[0] = c[4][0] - c[2][0];
    dir[1] = c[4][1] - c[2][1];
    dir[2] = 0.0f;
    dir[3] = 0.0f;
    func_002673b8(dir, dir);
    perp[0] = -dir[1];
    perp[1] = dir[0];
    perp[2] = 0.0f;
    perp[3] = 0.0f;
    func_00267560(tmp, perp, r0);
    func_00267518(c[3], c[2], tmp);
    func_00267560(tmp, perp, r1);
    func_00267518(c[5], c[4], tmp);
    perp[0] = -perp[0];
    perp[1] = -perp[1];
    func_00267560(tmp, perp, r0);
    func_00267518(c[2], c[2], tmp);
    func_00267560(tmp, perp, r1);
    func_00267518(c[4], c[4], tmp);
    func_00267560(tmp, dir, r0);
    func_00267530(c[0], c[2], tmp);
    func_00267530(c[1], c[3], tmp);
    func_00267560(tmp, dir, r1);
    func_00267518(c[6], c[4], tmp);
    func_00267518(c[7], c[5], tmp);
    for (i = 0; i < 8; i++) {
        func_002675e0(d[i], c[i]);
    }
    col0[0] = (f32) col->c[0] * key->sc[0];
    col0[1] = (f32) col->c[1] * key->sc[1];
    col0[2] = (f32) col->c[2] * key->sc[2];
    col0[3] = (f32) col->c[3] * key->sc[3];
    col1[0] = (f32) col->c[0] * key->sc[4];
    col1[1] = (f32) col->c[1] * key->sc[5];
    col1[2] = (f32) col->c[2] * key->sc[6];
    col1[3] = (f32) col->c[3] * key->sc[7];
    for (i = 0; i < 4; i++) {
        if (col0[i] < 0) col0[i] = 0;
        else if (col0[i] >= 256) col0[i] = 255;
        if (col1[i] < 0) col1[i] = 0;
        else if (col1[i] >= 256) col1[i] = 255;
    }
    cnt = 0;
    { KkShape *sh = D_00615E64->shapes + key->id; th = sh->tex; }
    tx = (KkTex *) ((u8 *) th + th->off4);
    p = (KkPkt *) kkPush(0x800);
    p->gif = 0x3000000000000001ULL;
    tag = &p->gif2;
    dma = ((s32) p & 0x0FFFFFFF) | 0x80000000;
    p->regs = 0xEEE;
    p->tex0[0] = tx->w8;
    p->tex0[1] = tx->wC;
    p->tex0r = 6;
    p->tex1[0] = th->b16;
    p->tex1[1] = th->b17;
    p->tex1r = 0x42;
    p->q = D_0061E800.q;
    out = (KkW *) (p + 1);
    src = pos;
    dp = d;
    for (i = 0; i < 8; i++, dp++, src++) {
        if (func_00267ea8(c[i]) == 0) {
            if (key->flag) {
                if (i < 4) func_00267560(tmp, pos[i], inv[0]);
                else func_00267560(tmp, pos[i], inv[1]);
                out->f = tmp[0]; out++;
                out->f = tmp[1]; out++;
                out->f = tmp[2]; out++;
            } else {
                out->f = (*src)[0]; out++;
                out->f = (*src)[1]; out++;
                out->f = (*src)[2]; out++;
            }
            out->i = 0; out++;
            if (i < 4) {
                for (j = 0; j < 4; j++) {
                    out->i = col0[j]; out++;
                }
            } else {
                for (j = 0; j < 4; j++) {
                    out->i = col1[j]; out++;
                }
            }
            cnt++;
            out->i = (*dp)[0]; out++;
            out->i = (*dp)[1]; out++;
            out->i = (*dp)[2]; out++;
            out->i = 0; out++;
        }
    }
    tag[0] = cnt | 0x8000 | (0xC0B9ULL << 46);
    tag[1] = 0x412;
    __asm__ volatile("sync");
    p->tag = 0;
    *(s32 *) &p->tag = ((((u8 *) out - (u8 *) p) >> 4) - 1) | 0x70000000;
    FlushCache(0);
    func_00266f38(func_00266c08(2), dma);
    sceGsSyncPath(0, 0);
    { s8 *sp = &D_00372EA0; s32 k = *sp; *sp = k - 1; }
}

/* ---- func_001a7c50 ---- */

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
void func_001a8780(Msg *);
void func_001a9098(f32 *, f32 *);
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
#include "data/data_0037.h"
