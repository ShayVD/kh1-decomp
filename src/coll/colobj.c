/* Collision against the room's collision objects (a guess at the name),
 * 0x0011a068-0x0011c5e8: D_003044D8 lists D_003044D0 objects (a flag word
 * and a model header each), D_004E2430 holds a 64-byte bounding box per
 * object (func_0011a0a0 builds them from each model's min / max, func_0011a728
 * tests one against a query box), func_0011a410 transforms an object's
 * collision mesh, D_004E2450 / D_004E2458 are its triangle and group lists,
 * and func_0011b108 / func_0011b220 / func_0011bdf8 / func_0011c118 / func_0011c338
 * collect hits over every object for the map collision of src/coll/mapcoll.c.
 * Read from the code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "data/bss_004D.h"
#include "data/bss_004E.h"
#include "data/pieces/D_002BD250.h"
#include "data/types/text_00110000_h3.h"
#include "data/types/text_00110000_h3_p.h"
#include "data/pieces/D_003044D8.h"
#include "m2c.h"
#include "data/pieces/D_002BCB60.h"
#include "data/pieces/D_002C1260.h"
#include "data/pieces/D_002BBDF4.h"
#include "vm/script_vm.h"
#include "data/pieces/D_002BBDF0.h"
#include "data/pieces/D_002BBDF8.h"
#include "data/types/text_00110000_h52.h"
#include "data/pieces/D_002BBF20.h"
#include "data/pieces/D_002BBEE0.h"
#include "data/pieces/D_002BBEA0.h"
#include "data/pieces/D_002BBE60.h"
#include "data/pieces/D_002BBE20.h"
#include "data/pieces/D_002BBF60.h"
#include "data/pieces/D_002BD118.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC070.h"
#include "data/types/text_00110000_h52_p.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_0048C6F0.h"
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_002A3F48.h"
#include "data/types/text_00110000_h52_p2.h"
#include "data/pieces/D_003044DC.h"
#include "data/pieces/D_002BCCA0.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_002BCD60.h"
#include "data/types/text_00110000_h29_p.h"
#include "data/pieces/D_002A6208.h"
#include "data/types/text_00110000_h29_p3.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_002BBD48.h"
#include "data/types/text_00110000_h29.h"
#include "data/pieces/D_002BCDA0.h"
#include "data/pieces/D_002BCDAC.h"
#include "data/pieces/D_002A3F3C.h"
#include "data/types/text_00110000_h29_p2.h"
#include "data/pieces/D_002A623C.h"
#include "data/pieces/D_002C1300.h"
#include "data/bss_004F.h"
#include "data/types/text_00110000_h30.h"
#include "data/types/text_00110000_h53_p.h"

/* func_0011a068 (from hand/text_00110000_h3.c). */
extern s32 D_004E2430[64][16];
s32 func_0011a068(void) {
    s32 i;
    for (i = 0; i < 64; i++) D_004E2430[i][12] = 0;
    return 0;
}

/* func_0011a0a0 (from hand/text_00110000_s6_03.c). */
typedef struct { f32 min[4]; f32 max[4]; u8 pad[32]; } Box64;
extern s32 D_003044D0;
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
typedef struct { V4 x0; V4 mn; V4 mx; V4 c[8]; } BoxWork;
void *func_00122048(s32, s32);
void func_001220b8(void *);
extern Box64 D_004E2430_0011a0a0[] __asm__("D_004E2430");
#define D_004E2430 D_004E2430_0011a0a0
void func_0011a0a0(void) {
    BoxWork *w;
    s32 i, j, k;
    u8 *h;
    f32 mn, mx, v;
    w = func_00122048(176, 4);
    w->x0[3] = w->mn[3] = w->mx[3] = w->c[0][3] = w->c[1][3] = w->c[2][3] = w->c[3][3] = w->c[4][3] = w->c[5][3] = w->c[6][3] = w->c[7][3] = 1.0f;
    for (i = 0; i < D_003044D0; i++) {
        h = D_003044D8[i].x4;
        h += *(s32 *)(h + 16);
        h += *(s32 *)h;
        w->mn[0] = ((f32 *)h)[0];
        w->mn[1] = ((f32 *)h)[1];
        w->mn[2] = ((f32 *)h)[2];
        w->mx[0] = ((f32 *)h)[4];
        w->mx[1] = ((f32 *)h)[5];
        w->mx[2] = ((f32 *)h)[6];
        w->c[0][0] = w->mn[0]; w->c[0][1] = w->mn[1]; w->c[0][2] = w->mn[2];
        w->c[1][0] = w->mx[0]; w->c[1][1] = w->mn[1]; w->c[1][2] = w->mn[2];
        w->c[2][0] = w->mn[0]; w->c[2][1] = w->mx[1]; w->c[2][2] = w->mn[2];
        w->c[3][0] = w->mx[0]; w->c[3][1] = w->mx[1]; w->c[3][2] = w->mn[2];
        w->c[4][0] = w->mn[0]; w->c[4][1] = w->mn[1]; w->c[4][2] = w->mx[2];
        w->c[5][0] = w->mx[0]; w->c[5][1] = w->mn[1]; w->c[5][2] = w->mx[2];
        w->c[6][0] = w->mn[0]; w->c[6][1] = w->mx[1]; w->c[6][2] = w->mx[2];
        w->c[7][0] = w->mx[0]; w->c[7][1] = w->mx[1]; w->c[7][2] = w->mx[2];
        vapply(w->c[0], (f32 *)D_003044D8[i].x0, w->c[0]);
        vapply(w->c[1], (f32 *)D_003044D8[i].x0, w->c[1]);
        vapply(w->c[2], (f32 *)D_003044D8[i].x0, w->c[2]);
        vapply(w->c[3], (f32 *)D_003044D8[i].x0, w->c[3]);
        vapply(w->c[4], (f32 *)D_003044D8[i].x0, w->c[4]);
        vapply(w->c[5], (f32 *)D_003044D8[i].x0, w->c[5]);
        vapply(w->c[6], (f32 *)D_003044D8[i].x0, w->c[6]);
        vapply(w->c[7], (f32 *)D_003044D8[i].x0, w->c[7]);
        for (j = 0; j < 3; j++) {
            mn = mx = w->c[0][j];
            for (k = 1; k < 8; k++) {
                v = w->c[k][j];
                if (v < mn) mn = v;
                if (mx < v) mx = v;
            }
            D_004E2430[i].min[j] = mn;
            D_004E2430[i].max[j] = mx;
        }
    }
    func_001220b8(w);
}
#undef D_004E2430

/* func_0011a410 (from hand/text_00110000_s8_lead.c).  Its matching notes:
 * the first `e` keeps the (s32)&D[i] + 32 cast; the second, after the norms
 * alloc, is written as integer arithmetic (i * sizeof + 32) + base, which
 * gives the original's operand order.  Plain hand, strict. */
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
void *func_00121e28(s32, void *);
void func_00121eb0(void *);
extern Ent2430 D_004E2430_0011a410[] __asm__("D_004E2430");
#define D_004E2430 D_004E2430_0011a410
/* s8 (lead, from w19's 2w draft): func_0011a410. The first `e` keeps the (s32)&D[i] + 32 cast; the second, after the norms alloc, is written as integer arithmetic (i * sizeof + 32) + base, which gives the original's operand order. Plain hand, strict. */
/* func_0011a410: ~144 words off (hand, strict). Structure and VU0 helpers right; orig keeps i*64 in s4 and base in s3 and computes slot addresses differently (dead dup addu a1). Second loop nop/alignment shifted by that. */
void func_0011a410(s32 i) {
    XfWork *w;
    u8 *h;
    void *p;
    s32 j;
    MdlEnt *e;
    if (D_004E2430[i].e.loaded) return;
    D_004E2430[i].e.loaded = 1;
    w = func_00122048(112, 4);
    w->v[3] = 1.0f;
    vcopymatrix(w->m, (void *)D_003044D8[i].x0);
    e = (MdlEnt *)((s32)(i * sizeof(*D_004E2430) + 32) + (s32)D_004E2430);
    h = D_003044D8[i].x4;
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
        e = (MdlEnt *)((s32)&D_004E2430[i] + 32);
        e->norms = q;
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
#undef D_004E2430

/* func_0011a728 (from hand/text_00110000_s6_03.c). */
extern Box64 D_004E2430_0011a728[] __asm__("D_004E2430");
#define D_004E2430 D_004E2430_0011a728
s32 func_0011a728(f32 *a, s32 i) {
    if (a[3] >= D_004E2430[i].min[0] && D_004E2430[i].max[0] >= a[0] &&
        a[4] >= D_004E2430[i].min[1] && a[1] <= D_004E2430[i].max[1] &&
        a[5] >= D_004E2430[i].min[2] && a[2] <= D_004E2430[i].max[2]) return 1;
    return 0;
}
#undef D_004E2430

/* func_0011a7c0 (from hand/text_00110000_h3.c). */
typedef struct {
    u16 v[10];
} Rec20;
typedef struct {
    Rec20 *x0;
    u8 pad[60];
} Ent2458;
/* Sized for tools/shift/cover_check.py, which needs a size for D_004E2458:
 * the table runs to D_004E3430 (0xFD8 bytes, 63 whole entries). */
extern Ent2458 D_004E2458[63];
s32 func_0011a7c0(s32 a0, s32 a1, u16 *a2) {
    Rec20 *t = D_004E2458[a0].x0;
    a2[0] = t[a1].v[0];
    a2[1] = t[a1].v[1];
    a2[2] = t[a1].v[2];
    a2[3] = t[a1].v[3];
    return a2[3] == 0xffff ? 3 : 4;
}

/* func_0011a818 (from hand/text_00110000_h3.c). */
typedef struct {
    s16 v[10];
} Rec20s;
void func_0011a818(s32 *a0, s32 *a1, u16 *a2, s32 a3) {
    *a0 = ((Rec20s *)D_004E2458[a3].x0)[a2[0]].v[a2[1]];
    *a1 = ((Rec20s *)D_004E2458[a3].x0)[a2[0]].v[a2[2]];
}

/* func_0011a868 (from hand/text_00110000_s6_03.c). */
typedef int u128 __attribute__((mode(TI)));
typedef struct { f32 x, y, z; } V3;
typedef struct {
    u128 *x0;
    u128 *x4;
    Rec20s *x8;
    f32 *xc;
    u8 pad[48];
} Ent2450;
extern Ent2450 D_004E2450[];
s32 func_0011a868(s32 a0, s32 a1, f32 *a2) {
    Ent2450 *e = &D_004E2450[a0];
    V3 *b = (V3 *)e->xc;
    V3 *p0 = (V3 *)((u32)e->x8[a1].v[0] * 12 + (u32)b);
    V3 *p1 = (V3 *)((u32)e->x8[a1].v[1] * 12 + (u32)b);
    V3 *p2 = (V3 *)((u32)e->x8[a1].v[2] * 12 + (u32)b);
    V3 *p3 = (V3 *)((u32)e->x8[a1].v[3] * 12 + (u32)b);
    a2[0] = p0->x; a2[1] = p0->y; a2[2] = p0->z; a2[3] = 1.0f;
    a2[4] = p1->x; a2[5] = p1->y; a2[6] = p1->z; a2[7] = 1.0f;
    a2[8] = p2->x; a2[9] = p2->y; a2[10] = p2->z; a2[11] = 1.0f;
    if (e->x8[a1].v[3] == -1) return 3;
    a2[12] = p3->x; a2[13] = p3->y; a2[14] = p3->z; a2[15] = 1.0f;
    return 4;
}

/* func_0011a978 (from hand/text_00110000_h3.c). */
static inline void CopyQword(void *dst, void *src) {
    __asm__ volatile("lq $6, 0(%1)\nsq $6, 0(%0)\nnop\nnop" : : "r"(dst), "r"(src) : "$6");
}
typedef struct {
    u128 *x0;
    u128 *x4;
    Rec20 *x8;
    u8 pad[52];
} Ent2450_1a978;
extern Ent2450_1a978 D_004E2450_0011a978[] __asm__("D_004E2450");
#define D_004E2450 D_004E2450_0011a978
void func_0011a978(s32 a0, s32 a1, u128 *a2) {
    Ent2450_1a978 *e = &D_004E2450[a0];
    CopyQword(a2, &e->x4[((s16 *)&e->x8[a1])[4]]);
}
#undef D_004E2450

/* func_0011a9c8 (from hand/text_00110000_h3.c). */
typedef struct {
    u128 *x0;
    u128 *x4;
    Rec20 *x8;
    u8 pad[52];
} Ent2450_1a9c8;
extern Ent2450_1a9c8 D_004E2450_0011a9c8[] __asm__("D_004E2450");
#define D_004E2450 D_004E2450_0011a9c8
void func_0011a9c8(s32 a0, s32 a1, u128 *a2) {
    Ent2450_1a9c8 *e = &D_004E2450[a0];
    CopyQword(a2, &e->x0[((s16 *)&e->x8[a1])[0]]);
}
#undef D_004E2450

/* func_0011aa18 (from hand/text_00110000_s6_03.c). */
static inline void CopyQword1(void *dst, void *src) {
    __asm__ volatile("lq $6, 0(%1)\nsq $6, 0(%0)\nnop" : : "r"(dst), "r"(src) : "$6");
}
s32 func_0011aa18(s32 a0, s32 a1, u128 *a2) {
    Ent2450 *e = &D_004E2450[a0];
    CopyQword1(&a2[0], &e->x0[e->x8[a1].v[0]]);
    CopyQword1(&a2[1], &e->x0[e->x8[a1].v[1]]);
    CopyQword1(&a2[2], &e->x0[e->x8[a1].v[2]]);
    if (e->x8[a1].v[3] == -1) return 3;
    CopyQword1(&a2[3], &e->x0[e->x8[a1].v[3]]);
    return 4;
}

/* func_0011aac8 (from hand/text_00110000_h3.c). */
void func_0011aac8(s32 a0, f32 *a1, s32 a2) {
    f32 *v = a1 + 4;
    func_0011a978(a2, a0, (u128 *)v);
    a1[8] = -v[0];
    a1[9] = -a1[5];
    a1[10] = -a1[6];
    a1[11] = 1.0f;
}

/* func_0011ab38 (from auto/text_00110000_6.c). */
#define D_004E2458 (*(M2C_UNK (*)) &D_004E2458)
s32 func_0011ab38(s32 arg0, s32 arg1) {
    return *(M2C_UNK *)((s8 *)&D_004E2458 + (arg0 << 6)) + (arg1 * 0x14) + 0x10;
}
#undef D_004E2458

/* func_0011ab60 (from auto/text_00110000_6.c). */
#define D_004E2458 (*(M2C_UNK (*)) &D_004E2458)
u8 func_0011ab60(s32 arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 0x14) + *(M2C_UNK *)((s8 *)&D_004E2458 + (arg0 << 6))), u8 *, 0xB);
}
#undef D_004E2458

/* func_0011ab88 (from hand/text_00110000_s8_w2.c). */
typedef struct {
    V4 *x0;
    u128 *x4;
    Rec20 *x8;
    f32 *xc;
    u8 pad[48];
} Ent2450b;
static inline s32 vsubflags(void *a, void *b) {
    s32 f;
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "cfc2 %0, $vi17\n"
        : "=&r"(f) : "r"(a), "r"(b));
    return f;
}
extern Ent2450b D_004E2450_0011ab88[] __asm__("D_004E2450");
#define D_004E2450 D_004E2450_0011ab88
s32 func_0011ab88(s32 a0, s32 a1, void *a2) {
    V4 t;
    s32 m;
    Ent2450b *e = &D_004E2450[a0];
    u16 *r = e->x8[a1].v;
    f32 *p0 = e->x0[*r++];
    f32 *p1 = e->x0[*r++];
    f32 *p2 = e->x0[*r++];
    s16 k = ((s16 *)e->x8[a1].v)[3];
    if (k >= 0) goto quad;
    if (k < -2) goto quad;
    {
        t[0] = p0[0]; t[1] = p1[0]; t[2] = p2[0];
        if ((vsubflags(D_002C1260.mx[0], t) & 0xe0) == 0xe0) return 0;
        if ((vsubflags(t, D_002C1260.mn[0]) & 0xe0) == 0xe0) return 0;
        t[0] = p0[1]; t[1] = p1[1]; t[2] = p2[1];
        if ((vsubflags(D_002C1260.mx[1], t) & 0xe0) == 0xe0) return 0;
        if ((vsubflags(t, D_002C1260.mn[1]) & 0xe0) == 0xe0) return 0;
        t[0] = p0[2]; t[1] = p1[2]; t[2] = p2[2];
        if ((vsubflags(D_002C1260.mx[2], t) & 0xe0) == 0xe0) return 0;
        m = vsubflags(t, D_002C1260.mn[2]) & 0xe0;
        if (m != 0xe0) goto one;
        return 0;
    }
quad:
    {
        f32 *p3 = e->x0[*r];
        t[0] = p0[0]; t[1] = p1[0]; t[2] = p2[0]; t[3] = p3[0];
        if ((vsubflags(D_002C1260.mx[0], t) & 0xf0) == 0xf0) return 0;
        if ((vsubflags(t, D_002C1260.mn[0]) & 0xf0) == 0xf0) return 0;
        t[0] = p0[1]; t[1] = p1[1]; t[2] = p2[1]; t[3] = p3[1];
        if ((vsubflags(D_002C1260.mx[1], t) & 0xf0) == 0xf0) return 0;
        if ((vsubflags(t, D_002C1260.mn[1]) & 0xf0) == 0xf0) return 0;
        t[0] = p0[2]; t[1] = p1[2]; t[2] = p2[2]; t[3] = p3[2];
        if ((vsubflags(D_002C1260.mx[2], t) & 0xf0) == 0xf0) return 0;
        m = vsubflags(t, D_002C1260.mn[2]) & 0xf0;
        if (m == 0xf0) return 0;
    }
one:
    return 1;
zero:
    return 0;
}
#undef D_004E2450

/* func_0011af48 (from hand/text_00110000_h52.c). */
typedef Ent20_2a6238 Plane52;
typedef struct { Plane52 *tbl; u8 pad[60]; } Grp52;
typedef struct { u8 pad[0x18]; s16 cnt; } Qry52;
void func_001158c8(Qry52 *);
extern Grp52 D_004E2458_0011af48[] __asm__("D_004E2458");
#define D_004E2458 D_004E2458_0011af48
#define func_0011ab88 ((s32 (*)(s32, s32, Qry52 *)) func_0011ab88)
s32 *func_0011af48(s32 g, Qry52 *q, s32 mode, s32 *out) {
    Mdl52 *m;
    u16 *list;
    Plane52 *tbl;
    s32 cnt, i, id;
    cnt = 0;
    m = D_003044DC[g].m;
    tbl = D_004E2458[g].tbl;
    m = (Mdl52 *)((u8 *)m + m->x10);
    list = (u16 *)((u8 *)m + m->x20);
    func_001158c8(q);
    for (i = 0; i < list[0]; i++) {
        u32 *w;
        id = list[i + 1];
        w = &tbl[id].f.w;
        switch (mode) {
        case 0:
            if (!(*w & 0x106) && func_0011ab88(g, id, q)) {
                out[cnt] = id;
                cnt++;
            }
            break;
        case 1:
            if ((*w & 0x406) == 0x400 && func_0011ab88(g, id, q)) {
                out[cnt] = id;
                cnt++;
            }
            break;
        }
    }
    q->cnt = cnt;
    return out + cnt;
}
#undef D_004E2458
#undef func_0011ab88

/* func_0011b0c0 (from auto/text_00110000_11.c). */
#define func_0011af48 ((s32 (*)(s32, s32, s32, s32)) func_0011af48)
s32 func_0011b0c0(s32 arg0, s32 arg1) {
    func_0011a410(arg0);
    return func_0011af48(arg0, arg1, 0, (s32) &D_002BD250);
}
#undef func_0011af48

/* func_0011b108 (from hand/text_00110000_h29.c). */
extern u8 D_002BF250[];
typedef struct { u32 h; s32 i; void *p; } W29Lnk;
typedef struct { u8 pad[0x18]; u16 x18; u8 pad1a[2]; s32 x1c; W29Lnk l[1]; } W29Grp;
#define func_0011a728 ((s32 (*)(W29Grp *, s32)) func_0011a728)
#define func_0011af48 ((void *(*)(s32, W29Grp *, s32, void *)) func_0011af48)
void func_0011b108(W29Grp *g, s32 k) {
    void *prev = D_002BF250;
    s32 i;
    for (i = 0; i < D_003044D0; i++) {
        if (D_003044D8[i].flags.b0 != 1 && func_0011a728(g, i)) {
            void *r;
            func_0011a410(i);
            r = func_0011af48(i, g, 1, prev);
            if (g->x18 != 0) {
                g->x1c++;
                g->l[k].h = g->x18;
                g->l[k].i = i;
                g->l[k].p = prev;
                k++;
            }
            prev = r;
        }
    }
}
#undef func_0011a728
#undef func_0011af48

/* func_0011b220 (from hand/text_00110000_s11_w13.c). */
typedef struct { u8 pad[16]; s32 x10; } Rec20w;
typedef struct { Rec20w *x0; u8 pad[60]; } Ent2458_1b220;
extern f32 D_002C1250;
s32 func_00119ad8(s32, s32, f32 *, f32 *, f32 *, f32 *);
typedef struct { u32 lo : 4; u32 type : 4; u32 rest : 24; } RFlg;
typedef struct { u8 pad[16]; RFlg f; } Rec20b;
extern s32 D_002BC128;
extern s32 D_002BC130;
s32 func_00119ef8(s32, s32, f32 *, f32 *, f32 *, f32 *);
static inline void vscale2(f32 *d, f32 *v, f32 s) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyz $vf4xyz, $vf4xyz, $vf5x\n"
        "sqc2 $vf4, 0(%0)\n"
        : : "r"(d), "r"(v), "r"(&s) : "$8", "memory");
}
static inline void vadd3(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vadd.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
static inline void vsub3(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
static inline void vnorm(f32 *d, f32 *a) {
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
        : : "r"(d), "r"(a) : "memory");
}
extern Ent2458_1b220 D_004E2458_0011b220[] __asm__("D_004E2458");
#define D_004E2458 D_004E2458_0011b220
#define func_001158c8 ((void (*)(void *)) func_001158c8)
#define func_0011a978 ((void (*)(s32, s32, f32 *)) func_0011a978)
u64 func_0011b220(s32 a0, f32 *out, void *a2, s32 a3, f32 scale) {
    V4 p;
    V4 n;
    s32 list1[256];
    s32 list2[256];
    s32 n2;
    s32 cnt;
    s32 i, id;
    s64 hit;
    Rec20b *rec;
    u16 *ids;
    u8 *h;
    u16 *hd;
    RFlg *f;

    h = (u8 *)D_003044D8[a0].x4;
    h += *(s32 *)(h + 16);
    rec = (Rec20b *)D_004E2458[a0].x0;
    hd = (u16 *)(h + *(s32 *)(h + 32));
    p[3] = 1.0f;
    hit = 0;
    cnt = 0;
    n2 = 0;
    func_001158c8(a2);
    for (i = 0; i < *hd; i++) {
        id = hd[i + 1];
        f = &rec[id].f;
        if (f->type == 0) continue;
        if (!func_0011ab88(a0, id, a2)) continue;
        func_0011a978(a0, id, n);
        if (f->type == 3) {
            if (a3 == 0 && n[1] < -0.167f) continue;
            if (func_00119ef8(a0, id, n, out, p, &D_002C1250)) {
                hit = 1;
                vscale2(n, n, scale);
                vadd3(out, p, n);
                list2[n2++] = id;
            } else {
                list1[cnt++] = id;
            }
        } else {
            if (D_002BC128 == 10 && D_002BC130 == 7 && D_002C1300(f)) continue;
            if (func_00119ef8(a0, id, n, out, p, &D_002C1250)) {
                hit = 1;
                vscale2(n, n, scale);
                vadd3(out, p, n);
                list2[n2++] = id;
            } else {
                list1[cnt++] = id;
            }
        }
    }
    for (i = 0; i < cnt; i++) {
        id = list1[i];
        f = &rec[id].f;
        if (f->type == 0) continue;
        func_0011a978(a0, id, n);
        if (f->type == 3) {
            if (n[1] < -0.167f) continue;
            if (func_00119ad8(a0, id, n, out, p, &D_002C1250)) {
                hit = 1;
                vsub3(out, out, p);
                vnorm(out, out);
                vscale2(out, out, scale);
                vadd3(out, p, out);
            }
        } else {
            if (D_002BC128 == 10 && D_002BC130 == 7 && D_002C1300(f)) continue;
            if (func_00119ad8(a0, id, n, out, p, &D_002C1250)) {
                hit = 1;
                vsub3(out, out, p);
                vnorm(out, out);
                vscale2(out, out, scale);
                vadd3(out, p, out);
            }
        }
    }
    return hit << (a0 + 1);
}
#undef D_004E2458
#undef func_001158c8
#undef func_0011a978

/* func_0011b6a0 (from hand/text_00110000_s6_03.c). */
typedef struct { u8 pad[0x20]; f32 r; f32 h; s32 flags; u8 pad2[0x54]; } ColObj;
void func_00116690(void);
void func_001166a0(void);
void func_001166b0(void);
void func_001166c0(void);
void func_001166c8(void);
void func_001166d8(void);
#define func_0011b220 ((u64 (*)(s32, f32 *, f32 *, s32, f32)) func_0011b220)
u64 func_0011b6a0(ColObj *o, f32 *pos, s32 a2) {
    f32 box[6];
    f32 box2[6];
    f32 r, g, y;
    s32 i;
    u64 res;
    switch (o->flags & 0x7c) {
    case 4: (*(void **)&D_002C1300) = func_00116690; break;
    case 16: (*(void **)&D_002C1300) = func_001166a0; break;
    case 8: (*(void **)&D_002C1300) = func_001166b0; break;
    case 32: (*(void **)&D_002C1300) = func_001166c0; break;
    case 64: (*(void **)&D_002C1300) = func_001166c8; break;
    default: (*(void **)&D_002C1300) = func_001166d8; break;
    }
    r = D_002C1250 + o->r * 0.5f;
    res = 0;
    for (i = 0; i < D_003044D0; i++) {
        if (D_003044D8[i].flags.b0 == 1) continue;
        y = pos[1] - o->h;
        g = D_002C1250;
        box[0] = pos[0] - g;
        box[2] = pos[2] - g;
        box[1] = y - g;
        box[3] = pos[0] + g;
        box[5] = pos[2] + g;
        box[4] = y + g;
        if (func_0011a728(box, i)) {
            func_0011a410(i);
            box2[0] = pos[0] - r;
            box2[3] = pos[0] + r;
            pos[1] = pos[1] - o->h;
            box2[2] = pos[2] - r;
            box2[5] = pos[2] + r;
            box2[4] = pos[1] + r;
            box2[1] = pos[1] - r;
            res |= func_0011b220(i, pos, box2, a2, o->r);
            pos[1] = pos[1] + o->h;
        }
    }
    return res;
}
#undef func_0011b220

/* func_0011b908 (from hand/text_00110000_h30.c). */
extern s32 D_002BD150[];
extern s32 D_002BD160[];
static inline void vsubv(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
static inline void vcross(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vopmula.xyz ACC, $vf4xyz, $vf5xyz\n"
        "vopmsub.xyz $vf6xyz, $vf5xyz, $vf4xyz\n"
        "vsub.w $vf6w, $vf6w, $vf6w\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
#define func_0011aa18 ((s32 (*)(s32, s32, V4 *)) func_0011aa18)
s32 func_0011b908(s32 a0, s32 a1, f32 *a2) {
    V4 e, f, c;
    V4 pts[4];
    s32 i;
    s32 *idx;
    s32 n = func_0011aa18(a0, a1, pts);
    if (n == 3) idx = D_002BD150;
    else idx = D_002BD160;
    for (i = 0; i < n; i++) {
        vsubv(e, pts[idx[i]], pts[i]);
        vsubv(f, a2, pts[i]);
        vcross(c, e, f);
        if (c[1] < 0.0f) return 0;
    }
    return 1;
}
#undef func_0011aa18

/* func_0011b9f8 (from hand/text_00110000_h52.c). */
typedef f32 V4_52[4] __attribute__((aligned(16)));
f32 fabsf(f32);
static inline void v52_sub(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
static inline void v52_cross(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vopmula.xyz ACC, $vf4xyz, $vf5xyz\n"
        "vopmsub.xyz $vf6xyz, $vf5xyz, $vf4xyz\n"
        "vsub.w $vf6w, $vf6w, $vf6w\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
static inline void v52_normalize(f32 *d, f32 *s) {
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
static inline f32 v52_dot(f32 *a, f32 *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
#define func_0011a9c8 ((void (*)(s32, s32, f32 *)) func_0011a9c8)
#define func_0011a978 ((void (*)(s32, s32, f32 *)) func_0011a978)
#define func_0011aa18 ((void (*)(s32, s32, V4_52 *)) func_0011aa18)
void func_0011b9f8(s32 g, s32 id, f32 *p, f32 *out) {
    V4_52 a, n, e1, e2, tri[4];
    f32 d;
    func_0011a9c8(g, id, a);
    func_0011a978(g, id, n);
    d = v52_dot(n, a);
    if (fabsf(n[1]) > 0.09999999776f) {
        *out = (d - (n[0] * p[0] + n[2] * p[2])) / n[1];
        return;
    }
    func_0011aa18(g, id, tri);
    v52_sub(e1, tri[0], tri[1]);
    v52_sub(e2, tri[2], tri[1]);
    v52_cross(n, e1, e2);
    v52_normalize(n, n);
    d = v52_dot(n, a);
    if (n[1] != 0.0f) {
        *out = (d - (n[0] * p[0] + n[2] * p[2])) / n[1];
    } else {
        *out = 1000000.0f;
    }
}
#undef func_0011a9c8
#undef func_0011a978
#undef func_0011aa18

/* func_0011bbe8 (from hand/text_00110000_h52.c). */
typedef PlaneBits_2a6238 Bf52;
typedef struct { f32 x0, x4; u8 pad8[0x1c]; f32 x24; } Obj52;
extern Grp52 D_004E2458_0011bbe8[] __asm__("D_004E2458");
#define D_004E2458 D_004E2458_0011bbe8
s32 func_0011bbe8(Obj52 *o, f32 *p, s32 g, f32 *out) {
    s32 ids[512];
    f32 h[2];
    Mdl52 *m;
    u16 *list;
    s32 best, cnt, i, id;
    Plane52 *tbl;
    f32 e, dy;
    *out = 1000000.0f;
    best = -1;
    cnt = 0;
    m = D_003044DC[g].m;
    tbl = D_004E2458[g].tbl;
    m = (Mdl52 *)((u8 *)m + m->x10);
    list = (u16 *)((u8 *)m + m->x20);
    for (i = 0; i < list[0]; i++) {
        Bf52 *w;
        id = list[i + 1];
        w = &tbl[id].f.p;
        if (D_002BC128 == 10 && D_002BC130 == 7 && D_002C1300(w)) break;
        if (func_0011b908(g, id, p)) {
            ids[cnt] = id;
            cnt++;
        }
    }
    e = *out;
    for (i = 0; i < cnt; i++) {
        func_0011b9f8(g, ids[i], p, &h[1]);
        dy = fabsf(o->x4 - h[1]);
        if (dy < e) {
            if (h[1] < p[1] - o->x24) {
                if (dy < o->x24) {
                    e = dy;
                    *out = h[1];
                    best = ids[i];
                }
            } else {
                e = dy;
                *out = h[1];
                best = ids[i];
            }
        }
    }
    return best;
}
#undef D_004E2458

/* func_0011bdf8 (from hand/text_00110000_h52.c). */
typedef struct { f32 mn[3]; f32 mx[3]; u16 cnt; } Box52;
#define func_0011a728 ((s32 (*)(void *, s32)) func_0011a728)
s32 func_0011bdf8(Obj52 *o, f32 *p, s32 *og, f32 *out) {
    Box52 bx;
    s32 gs[64];
    f32 hs[64];
    s32 rs[64];
    s32 i, n, bi;
    f32 best;
    n = 0;
    bx.mn[0] = p[0];
    bx.mn[2] = p[2];
    bx.mx[0] = p[0];
    bx.mx[2] = p[2];
    bx.mn[1] = p[1] - o->x24;
    bx.mx[1] = p[1] + 1000000.0f;
    for (i = 0; i < D_003044D0; i++) {
        if (D_003044D8[i].flags.b0 == 1) continue;
        if (func_0011a728(&bx, i)) {
            func_0011a410(i);
            gs[n] = i;
            n++;
        }
    }
    if (n == 0) return -1;
    best = 1000000.0f;
    bi = 0;
    for (i = 0; i < n; i++) {
        rs[i] = func_0011bbe8(o, p, gs[i], &hs[i]);
        if (hs[i] < best) {
            best = hs[i];
            bi = i;
        }
    }
    *out = best;
    *og = gs[bi];
    return rs[bi];
}
#undef func_0011a728

/* func_0011bfc8 (from hand/text_00110000_h53.c). */
static inline f32 w53_dot(void *a, void *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
static inline void w53_scale(void *d, void *s, f32 t) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyz $vf4xyz, $vf4xyz, $vf5x\n"
        "sqc2 $vf4, 0(%0)\n"
        : : "r"(d), "r"(s), "r"(&t) : "$8", "memory");
}
static inline void w53_add(void *d, void *a, void *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vadd.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
#define func_0011a978 ((void (*)(s32, s32, V53 *)) func_0011a978)
#define func_0011a9c8 ((void (*)(s32, s32, V53 *)) func_0011a9c8)
s32 func_0011bfc8(s32 a0, s32 a1, void *p0, void *dir, void *out) {
    V53 n, p;
    f32 den, t;
    func_0011a978(a0, a1, &n);
    den = w53_dot(&n, dir);
    if (den >= 0.0f) return 0;
    func_0011a9c8(a0, a1, &p);
    t = (w53_dot(&n, &p) - w53_dot(&n, p0)) / den;
    if (t < 0.0f) return 0;
    if (t > 1.0f) return 0;
    w53_scale(out, dir, t);
    w53_add(out, out, p0);
    return 1;
}
#undef func_0011a978
#undef func_0011a9c8

/* func_0011c118 (from hand/text_00110000_s6_03.c). */
static inline f32 vdist2(void *a, void *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf6, 0(%1)\n"
        "lqc2 $vf4, 0(%2)\n"
        "vsub.xyzw $vf5xyzw, $vf6xyzw, $vf4xyzw\n"
        "vmove.xyzw $vf4xyzw, $vf5xyzw\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
typedef struct { Rec20w *x0; u8 pad[60]; } Ent2458_1c118;
s32 func_001198c8(s32, s32, void *);
extern Ent2458_1c118 D_004E2458_0011c118[] __asm__("D_004E2458");
#define D_004E2458 D_004E2458_0011c118
#define func_001158c8 ((void (*)(void *)) func_001158c8)
s32 func_0011c118(s32 a0, f32 *p, void *dir, void *q, f32 *out) {
    s32 ids[32];
    V4 hits[32];
    V4 tmp;
    V4 pad;
    u8 *h;
    u16 *list;
    Rec20w *rec;
    s32 i, n, best, idx;
    f32 min, d;
    h = D_003044D8[a0].x4;
    h += *(s32 *)(h + 16);
    list = (u16 *)(h + *(s32 *)(h + 32));
    rec = D_004E2458[a0].x0;
    func_001158c8(q);
    n = 0;
    for (i = 0; i < list[0]; i++) {
        idx = list[i + 1];
        { Rec20w *r = &rec[idx]; if (r->x10 & 0xe) continue; }
        if (func_0011ab88(a0, idx, q) && func_0011bfc8(a0, idx, p, dir, tmp) && func_001198c8(a0, idx, tmp)) {
            CopyQword1(hits[n], tmp);
            ids[n] = idx;
            n++;
        }
    }
    if (n != 0) {
        idx = 0;
        min = 1.0e12f;
        for (i = 0; i < n; i++) {
            d = vdist2(p, hits[i]);
            if (d < min) { min = d; idx = i; }
        }
        CopyQword1(out, hits[idx]);
        return ids[idx];
    }
    return -1;
}
#undef D_004E2458
#undef func_001158c8

/* func_0011c338 (from hand/text_00110000_s6_03.c). */
s32 func_0011c338(f32 *box, f32 *p, void *dir, f32 *out, s32 mask, s32 *idout) {
    s32 list[64];
    V4 hits[64];
    s32 res[64];
    s32 i, cnt, best, id, r;
    f32 min, d;
    cnt = 0;
    if (mask == -1) {
        for (i = 0; i < D_003044D0; i++) {
            if (D_003044D8[i].flags.b0 == 1) continue;
            if (func_0011a728(box, i)) {
                func_0011a410(i);
                list[cnt++] = i;
            }
        }
    } else {
        for (i = 0; i < D_003044D0; i++) {
            if (D_003044D8[i].flags.b0 == 1) continue;
            if ((D_003044D8[i].flags.mask & mask) != mask) continue;
            if (func_0011a728(box, i)) {
                func_0011a410(i);
                list[cnt++] = i;
            }
        }
    }
    if (cnt == 0) return -1;
    if (cnt == 1) {
        i = list[0];
        r = func_0011c118(i, p, dir, box, out);
        *idout = i;
        return r;
    }
    min = 1.0e12f;
    best = 0;
    for (i = 0; i < cnt; i++) {
        res[i] = func_0011c118(list[i], p, dir, box, hits[i]);
        d = vdist2(p, hits[i]);
        if (d < min) { min = d; best = i; }
    }
    CopyQword1(out, hits[best]);
    *idout = list[best];
    return res[best];
}

