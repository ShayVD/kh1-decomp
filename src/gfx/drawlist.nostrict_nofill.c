/* The depth-sorted draw list, its nostrict_nofill part (docs/modules.md
 * "Session 45"), 0x00237548-0x00238440 with drawlist.c (the set up) and
 * drawlist.nostrict.c (the push and the raw packet).  include/gfx/drawlist.h
 * has the list.  A node is a GS primitive in model space: kind 1 a line
 * (func_00237790), 2 a flat triangle (func_002378c8), 3 a lit textured
 * triangle (func_00237d48), 4 a raw packet (func_00237ec0); func_002376c8
 * pushes one by its depth after the matrix m (bucket (1 - w / 3000) << bits)
 * and func_00237f20 walks the buckets and sends each node's packet over the
 * GIF DMA channel, double buffered (b0 / b1); func_002380c0 does the same with
 * one send per bucket.  func_00237548 projects a
 * triangle and is 1 when libvu0's screen clip rejects it; func_00237a48
 * projects one point to GS 12.4 coordinates (raw: z and w unscaled);
 * func_00237b30 is the lit textured fan of up to four triangles sharing three
 * vertices.  No C caller of func_002376c8, func_00237b30 or func_00237f20 in
 * the main ELF (overlays, most likely); func_00237a48 is the HUD's and the
 * sprites' projection.  Read from the code, not proved by a boot. */
#include "common.h"
#include "gfx/drawlist.h"
#include "gfx/gspkt.h"

typedef int u128 __attribute__((mode(TI)));
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4;
typedef struct { s32 x, y, z, w; } __attribute__((aligned(16))) I4b;
typedef I4b I4;
typedef union { u128 q; s32 i[4]; } Q4;
typedef struct { u128 q[5]; } Item;
typedef struct { u128 q[7]; } Item7;
typedef struct Node { struct Node *next; s32 kind; u8 pad[8]; V4 pos; } Node;
typedef struct { u128 tag; V4 v[3]; s32 n; s32 pad[3]; V4 nrm[4][3]; u128 col[4]; V4 uv[4][3]; } ObjB;
typedef struct { u64 a, b; } U64x2;
typedef struct { u128 tag; V4 v[3]; V4 nrm[3]; U64x2 col; V4 uv[3]; } ObjC;
typedef struct Nd { struct Nd *next; s32 type; u8 pad8[8]; u128 v[3]; u128 n[3]; u64 t0, t1; u128 c[3]; } Nd;

s32 *func_00266c08(s32);
void func_00266f38(s32 *, s32 *);
void FlushCache(s32);
s32 sceGsSyncPath(s32, s32);
void sceVu0ApplyMatrix(V4 *, void *, V4 *);
void sceVu0DivVectorXYZ(V4 *, V4 *, f32);
void sceVu0ScaleVector(V4 *, void *, f32);
void sceVu0FTOI0Vector(V4 *, void *);
void sceVu0RotTransPersN(void *, void *, u128 *, s32, s32);
s32 sceVu0ClipScreen3(V4 *, V4 *, V4 *);
/* Two parameters (drawlist.nostrict.c), but func_00237f20 passes a third 0. */
u128 *func_00237ec0(u128 *src, u128 *dst, s32);

CONTEXT_ONLY void func_00237680(DrawList *h, DrawNode *node, s32 idx) {
    s32 max = 1 << h->bits;
    if (idx < 0) idx = 0;
    if (idx >= max) idx = max - 1;
    node->next = h->tbl[idx].head;
    h->tbl[idx].head = node;
}

s32 func_00237548(V4 *a, V4 *b, V4 *c, void *m) {
    V4 v[3];
    sceVu0ApplyMatrix(&v[0], m, a);
    sceVu0ApplyMatrix(&v[1], m, b);
    sceVu0ApplyMatrix(&v[2], m, c);
    sceVu0DivVectorXYZ(&v[0], &v[0], v[0].w);
    sceVu0DivVectorXYZ(&v[1], &v[1], v[1].w);
    sceVu0DivVectorXYZ(&v[2], &v[2], v[2].w);
    return sceVu0ClipScreen3(&v[0], &v[1], &v[2]);
}

/* An else-if chain in the order 2, 3, 1 with the last arm through a block-local
 * temporary (a two-insn then-block for jump1's conditional-move conversion):
 * gives the original's movz, movz (li 3; xor), bne k,2 shape. */
s32 func_002376c8(DrawList *h, Node *n, void *m) {
    V4 v;
    V4 *p;
    s32 s, r;
    s32 k = n->kind;
    p = 0;
    if (k == 2) {
        p = &n->pos;
    } else if (k == 3) {
        p = &n->pos;
    } else if (k == 1) {
        V4 *t = &n->pos;
        p = t;
    }
    s = 1 << h->bits;
    sceVu0ApplyMatrix(&v, m, p);
    r = s - v.w / 3000.0f * s;
    func_00237680(h, (DrawNode *)n, r);
    return r;
}

u128 *func_00237790(Item *src, u128 *dst, void *m) {
    u128 out[2];
    V4 a, b;
    u128 *h;
    sceVu0ApplyMatrix(&a, m, (V4 *)&src->q[1]);
    sceVu0ApplyMatrix(&b, m, (V4 *)&src->q[2]);
    sceVu0DivVectorXYZ(&a, &a, a.w);
    sceVu0DivVectorXYZ(&b, &b, b.w);
    if (sceVu0ClipScreen3(&a, &b, &b)) {
        return dst;
    }
    h = dst + 1;
    *h = 0;
    ((u64 *)h)[0] = 0x4004C00000008001;
    ((u64 *)h)[1] = 0x5151;
    sceVu0RotTransPersN(out, m, &src->q[1], 2, 1);
    dst[2] = src->q[3];
    dst[3] = out[0];
    dst[4] = src->q[4];
    dst[0] = 0;
    dst[5] = out[1];
    *(s32 *)dst = 0x10000005;
    return dst + 6;
}

u128 *func_002378c8(Item7 *src, u128 *dst, void *m) {
    Q4 out[3];
    V4 a, b, c;
    u128 *h;
    sceVu0ApplyMatrix(&a, m, (V4 *)&src->q[1]);
    sceVu0ApplyMatrix(&b, m, (V4 *)&src->q[2]);
    sceVu0ApplyMatrix(&c, m, (V4 *)&src->q[3]);
    sceVu0DivVectorXYZ(&a, &a, a.w);
    sceVu0DivVectorXYZ(&b, &b, b.w);
    sceVu0DivVectorXYZ(&c, &c, c.w);
    if (sceVu0ClipScreen3(&a, &b, &c)) {
        return dst;
    }
    h = dst + 1;
    *h = 0;
    ((u64 *)h)[0] = 0x6025C00000008001;
    ((u64 *)h)[1] = 0x414141;
    sceVu0RotTransPersN(out, m, &src->q[1], 3, 0);
    out[0].i[3] = 0;
    dst[2] = src->q[4];
    out[1].i[3] = 0;
    dst[3] = out[0].q;
    dst[4] = src->q[5];
    dst[5] = out[1].q;
    out[2].i[3] = 0;
    dst[6] = src->q[6];
    dst[0] = 0;
    dst[7] = out[2].q;
    *(s32 *)dst = 0x10000007;
    return dst + 8;
}

f32 func_00237a48(I4 *out, void *m, V4 *in, s32 raw) {
    V4 v;
    f32 r;
    sceVu0ApplyMatrix(&v, m, in);
    r = 1.0f / v.w;
    v.x *= r;
    v.y *= r;
    v.z *= r;
    if (raw == 0) {
        out->x = v.x * 16.0f;
        out->y = v.y * 16.0f;
        out->z = v.z * 16.0f;
        out->w = v.w * 16.0f;
    } else {
        out->z = v.z;
        out->x = v.x * 16.0f;
        out->y = v.y * 16.0f;
        out->w = v.w;
    }
    return r;
}

/* func_00237b30: one loop counter i shared by both loops (global pseudo outranks the dst giv: s3),
   header stores [0] before [1], and pn = o->nrm[j] after the col store (s5 giv inits before s8). */
u128 *func_00237b30(ObjB *o, u128 *dst, void *m) {
    I4b iv[3];
    f32 f[3];
    V4 t1, t2;
    u128 *h, *d;
    s32 i, j, k;
    if (func_00237548(&o->v[0], &o->v[1], &o->v[2], m)) {
        return dst;
    }
    h = dst + 1;
    *h = 0;
    ((u64 *)h)[0] = ((u64)(o->n * 3 | 0x58) << 47) | 0xA000400000008001ULL;
    ((u64 *)h)[1] = 0x512512512EULL;
    k = 2;
    {
        f32 *pf = f;
        I4b *pv = iv;
        V4 *ps = o->v;
        for (i = 0; i < 3; i++) {
            *pf++ = func_00237a48(pv++, m, ps++, 1);
        }
    }
    for (j = 0; j < o->n; j++) {
        V4 *pn;
        f32 *pf;
        V4 *pu;
        I4b *pi;
        dst[k++] = o->col[j];
        pn = o->nrm[j];
        pu = o->uv[j];
        pi = iv;
        pf = f;
        for (i = 0; i < 3; i++) {
            sceVu0ScaleVector(&t1, pu, *pf);
            sceVu0FTOI0Vector(&t2, pn);
            pf++; pu++;
            dst[k++] = *(u128 *)&t1;
            dst[k++] = *(u128 *)&t2;
            dst[k++] = *(u128 *)pi;
            pi++;
        }
    }
    return dst + k;
}

/* p1/p2 pointer locals and the init order pv, pn, pu, p1, p2, i, d set the sched1 (LUID)
   order of the pre-loop inits, which sched2 keeps for its ties. */
u128 *func_00237d48(ObjC *o, u128 *dst, void *m) {
    I4b iv;
    V4 t1, t2;
    u128 *h, *d;
    V4 *pv, *pu, *pn;
    s32 i;
    V4 *p1, *p2;
    if (func_00237548(&o->v[0], &o->v[1], &o->v[2], m)) {
        return dst;
    }
    h = dst + 1;
    *h = 0;
    ((u64 *)h)[0] = 0xA02DC00000008001ULL;
    ((u64 *)h)[1] = 0x512512512EULL;
    { U64x2 *c = (U64x2 *)&dst[2]; *c = o->col; }
    pv = o->v;
    pn = o->nrm;
    pu = o->uv;
    p1 = &t1;
    p2 = &t2;
    i = 2;
    d = dst + 3;
    for (; i >= 0; i--) {
        sceVu0ScaleVector(p1, pu++, func_00237a48(&iv, m, pv++, 1));
        sceVu0FTOI0Vector(p2, pn); pn++;
        *d++ = *(u128 *)&t1;
        *d++ = *(u128 *)&t2;
        *d++ = *(u128 *)&iv;
    }
    dst[0] = 0;
    *(s32 *)dst = 0x1000000B;
    return dst + 12;
}

void func_00237f20(DrawList *h, s32 *b0, s32 *b1, s32 a3, void *m) {
    s32 *buf = b0;
    s32 n = 1 << h->bits;
    DrawBucket *bk = h->tbl;
    s32 *r, *q;
    DrawNode *p;
    s32 i;
    for (i = 0; i < n; i++, bk++) {
        if (bk->head != 0) {
            p = bk->head;
            do {
                r = buf;
                if (p->kind == 2) r = (s32 *)func_002378c8((Item7 *)p, (u128 *)buf, m);
                else if (p->kind == 1) r = (s32 *)func_00237790((Item *)p, (u128 *)buf, m);
                else if (p->kind == 3) r = (s32 *)func_00237d48((ObjC *)p, (u128 *)buf, m);
                else if (p->kind == 4) r = (s32 *)func_00237ec0((u128 *)p, (u128 *)buf, 0);
                if (r != buf) {
                    *r |= 0x70000000;
                    q = func_00266c08(2);
                    *q |= 0x40;
                    FlushCache(0);
                    sceGsSyncPath(0, 0);
                    func_00266f38(q, buf);
                    buf = (buf == b0) ? b1 : b0;
                }
                if (p->next == 0) break;
                p = p->next;
            } while (p != 0);
        }
    }
    sceGsSyncPath(0, 0);
}

/* func_00237f20 with one DMA send per bucket: the bucket's packets run on
 * from each other and the last one's tag ends the chain. */
void func_002380c0(DrawList *h, s32 *b0, s32 *b1, s32 a3, void *m) {
    s32 *buf = b0;
    s32 n = 1 << h->bits;
    DrawBucket *bk = h->tbl;
    s32 *r, *q, *prev, *last;
    DrawNode *p;
    s32 i;
    for (i = 0; i < n; i++, bk++) {
        last = 0;
        if (bk->head != 0) {
            p = bk->head;
            r = buf;
            do {
                prev = r;
                if (p->kind == 2) r = (s32 *)func_002378c8((Item7 *)p, (u128 *)r, m);
                else if (p->kind == 1) r = (s32 *)func_00237790((Item *)p, (u128 *)r, m);
                else if (p->kind == 3) r = (s32 *)func_00237d48((ObjC *)p, (u128 *)r, m);
                else if (p->kind == 4) r = (s32 *)func_00237ec0((u128 *)p, (u128 *)r, 0);
                if (prev != r) last = prev;
                if (p->next == 0) break;
                p = p->next;
            } while (1);
            if (r != buf) {
                *last |= 0x70000000;
                q = func_00266c08(2);
                *q |= 0x40;
                FlushCache(0);
                sceGsSyncPath(0, 0);
                func_00266f38(q, buf);
                buf = (buf == b0) ? b1 : b0;
            }
        }
    }
    sceGsSyncPath(0, 0);
}

/* func_00237f20 for lists of kind 3 nodes only: every triangle in one packet
 * (one GIFtag of num triangles), sent once. */
void func_00238258(DrawList *h, s32 a1, u128 *dst, s32 a3, void *m) {
    u128 t0, t1, t2;
    s32 k, num;
    DrawBucket *bk;
    s32 n = 1 << h->bits;
    s32 i, j;
    Nd *p;
    u128 *d, *o, *pv, *pn, *pc;
    bk = h->tbl;
    k = 2;
    num = 0;
    for (i = 0; i < n; i++, bk++) {
        if (bk->head != 0) {
            p = (Nd *)bk->head;
            do {
                d = p->v;
                if (func_00237548((V4 *)d, (V4 *)&p->v[1], (V4 *)&p->v[2], m) == 0) {
                    pv = d;
                    pn = p->n;
                    pc = p->c;
                    o = (u128 *)((k << 4) + (s32)dst);
                    ((u64 *)o)[0] = p->t0;
                    d = o + 1;
                    ((u64 *)o)[1] = p->t1;
                    for (j = 0; j < 3; j++) {
                        sceVu0ScaleVector((V4 *)&t1, pc, func_00237a48((I4 *)&t0, m, (V4 *)pv, 1));
                        sceVu0FTOI0Vector((V4 *)&t2, pn);
                        pv++; pc++; pn++;
                        { u128 x = t1, y = t2, z;
                        *d++ = x;
                        z = t0;
                        *d++ = y;
                        *d++ = z; }
                    }
                    o = d;
                    k += 10;
                    num++;
                }
                if (p->next == 0) break;
                p = p->next;
            } while (p != 0);
        }
    }
    if (num != 0) {
        dst[1] = 0;
        ((u64 *)dst)[2] = num | 0x8000 | 0xA02DC00000000000ULL;
        ((u64 *)dst)[3] = 0x512512512EULL;
        func_00237018(dst, k, 1);
    }
}
