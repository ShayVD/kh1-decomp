/* 3w (LCS 3) PLAIN hand, right size 792, no casts (see 0011a410_2w.c for the 2w cast variant). Ent2430 *tbl = D_004E2430 local (orig keeps the base in s3 from the top), MdlEnt *e = &tbl[i].e set before h = mdl and used for x28/xc/verts stores, alloc arg written separately as &D_004E2430[i].e.verts (symbol form: stays a separate pseudo like the orig's dup addu); block-local h2 for the second header; nsrc before nn; m[3][0]=m[3][1]=m[3][2]; norm loop v[0],v[1],v[2]. Left: e computed (tbl+i64)+32, orig (i64+32)+tbl (every pointer/int form of e canonicalizes to the former; e = form-a field address would give the latter); norms store addu s1,s4,s1 vs orig s1,s1,s4 (re-setting e via (MdlEnt *)((s32)&D_004E2430[i] + 32) fixes that one). */
/* 98w: orig keeps i in s0 and i*64 in s4 (5 saved regs, frame 64); ours merges i/e into s1 (frame 48); norm loop lh order 2,0,1 vs ours 1,2,0. b4 variant ((&D[i])->e.x28) is 100w at equal size */
/* func_0011a410: ~144 words off (hand, strict). Structure and VU0 helpers right; orig keeps i*64 in s4 and base in s3 and computes slot addresses differently (dead dup addu a1). Second loop nop/alignment shifted by that. */
#include "common.h"
typedef f32 V4[4] __attribute__((aligned(16)));
typedef int u128 __attribute__((mode(TI)));
static inline void vcopymatrix(void *d, void *s) {
    __asm__ volatile(
        "lq $6, 0(%1)\n"
        "lq $7, 16(%1)\n"
        "lq $8, 32(%1)\n"
        "lq $9, 48(%1)\n"
        "sq $6, 0(%0)\n"
        "sq $7, 16(%0)\n"
        "sq $8, 32(%0)\n"
        "sq $9, 48(%0)\n"
        "nop\n"
        : : "r"(d), "r"(s) : "$6", "$7", "$8", "$9", "memory");
}
static inline void vapply(void *d, void *m, void *v) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 16(%1)\n"
        "lqc2 $vf6, 32(%1)\n"
        "lqc2 $vf7, 48(%1)\n"
        "lqc2 $vf8, 0(%2)\n"
        "vmulax.xyzw ACC, $vf4xyzw, $vf8x\n"
        "vmadday.xyzw ACC, $vf5xyzw, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6xyzw, $vf8z\n"
        "vmaddw.xyzw $vf9xyzw, $vf7xyzw, $vf8w\n"
        "sqc2 $vf9, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(m), "r"(v) : "memory");
}
static inline void vscalexyz(void *d, void *s, f32 t) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyz $vf4xyz, $vf4xyz, $vf5x\n"
        "sqc2 $vf4, 0(%0)\n"
        : : "r"(d), "r"(s), "r"(&t) : "$8", "memory");
}
static inline void vnormalize(void *d, void *s) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf4xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "vsqrt Q, $vf5x\n"
        "vwaitq\n"
        "vaddq.x $vf5x, $vf0x, Q\n"
        "vdiv Q, $vf0w, $vf5x\n"
        "vsub.xyzw $vf6xyzw, $vf0xyzw, $vf0xyzw\n"
        "vwaitq\n"
        "vmulq.xyz $vf6xyz, $vf4xyz, Q\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(s) : "memory");
}
typedef struct {
    V4 m[4];
    V4 v;
    f32 *src;
    s16 *nsrc;
    V4 *dst;
    V4 *ndst;
    u8 *hdr;
    u8 *hdr2;
    s32 nv;
    s32 nn;
} XfWork;
typedef struct {
    V4 *verts;
    V4 *norms;
    u8 *x28;
    f32 *xc;
    s32 loaded;
    u8 pad[12];
} MdlEnt;
typedef struct { u8 pad[0x20]; MdlEnt e; } Ent2430;
extern Ent2430 D_004E2430[];
typedef struct { void *mtx; u8 *mdl; s32 x8; s32 flags; } ColEntA;
extern ColEntA D_003044D8[];
void *func_00122048(s32, s32);
void *func_00121e28(s32, void *);
void func_00121eb0(void *);
void func_001220b8(void *);

static inline V4 *inl_alloc(V4 **slot, s32 n) {
    V4 *p = func_00121e28(n << 4, slot);
    func_00121eb0(p);
    *slot = p;
    return p;
}

void func_0011a410(s32 i) {
    XfWork *w;
    u8 *h;
    void *p;
    s32 j;
    Ent2430 *tbl = D_004E2430;
    MdlEnt *e;
    if (D_004E2430[i].e.loaded) return;
    D_004E2430[i].e.loaded = 1;
    w = func_00122048(112, 4);
    w->v[3] = 1.0f;
    vcopymatrix(w->m, D_003044D8[i].mtx);
    e = &tbl[i].e;
    h = D_003044D8[i].mdl;
    w->hdr = h + 16;
    h += *(s32 *)(h + 16);
    w->hdr2 = h;
    e->x28 = h + *(s32 *)(h + 24);
    w->src = (f32 *)(h + *(s32 *)(h + 8));
    e->xc = w->src;
    w->nv = *(u32 *)(h + 12) / 12;
    {
        V4 *q = func_00121e28(w->nv << 4, &D_004E2430[i].e.verts);
        func_00121eb0(q);
        e->verts = q;
        w->dst = q;
    }
    for (j = 0; j < w->nv; j++) {
        w->v[0] = w->src[0];
        w->v[1] = w->src[1];
        w->v[2] = w->src[2];
        vapply(w->dst, w->m, w->v);
        w->src += 3;
        w->dst++;
    }
    {
    u8 *h2 = w->hdr2;
    w->m[3][0] = w->m[3][1] = w->m[3][2] = 0.0f;
    w->nsrc = (s16 *)(h2 + *(s32 *)(h2 + 16));
    w->nn = *(u32 *)(h2 + 20) >> 3;
    }
    {
        V4 *q = func_00121e28(w->nn << 4, &D_004E2430[i].e.norms);
        func_00121eb0(q);
        D_004E2430[i].e.norms = q;
        w->ndst = q;
    }
    for (j = 0; j < w->nn; j++) {
        w->v[0] = w->nsrc[0];
        w->v[1] = w->nsrc[1];
        w->v[2] = w->nsrc[2];
        vscalexyz(w->v, w->v, 1.0f / 8192.0f);
        vapply(w->v, w->m, w->v);
        vnormalize(w->ndst, w->v);
        w->nsrc += 4;
        w->ndst++;
    }
    func_001220b8(w);
}
