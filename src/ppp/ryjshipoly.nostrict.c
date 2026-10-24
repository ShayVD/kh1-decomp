/* The pppRyjDrawShipoly and pppRyjDrawShipolyBone classes, -fno-strict-aliasing
 * (docs/modules.md "Session 50"): a ribbon (a strip of quads) that follows
 * the owner's position (Shipoly) or a bone of a model (ShipolyBone,
 * func_00122ff8 / func_001315c0).  The frame keeps n points (4-32) in a
 * buffer and renumbers the model's strip primitives (types 4 and 6); the
 * strip builders func_00199ac8 / func_0019ab38 smooth the points with a
 * cubic spline (func_001996d0 / func_0019a828 solve its second derivatives
 * in VU0, func_00199888 / func_0019a9e0 evaluate it) and write the quads'
 * positions, UVs (the texture page from func_001999f0 / func_0019aa60) and
 * fading alphas; the draw sends the model through opdma.c's func_001aaf88.
 * ryjshipoly.c has the default-flag parts.  Each section names the file its
 * code came from.  Read from the code, not proved by a boot. */
/* func_001996d0 (from hand/nostrict/text_00190000_h64.c). */
#include "common.h"
#include "platform/vu.h"
#include "ppp.h"
#include "data/bss_0061.h"
#include "data/pieces/D_003701F0.h"
#include "data/pieces/D_003701D0.h"
#include "data/pieces/D_003701E0.h"
typedef int u128 __attribute__((mode(TI)));
extern u128 D_00372710;
void func_001996d0(u128 *a, s32 n, u128 *b) {
    u128 buf[32];
    register u128 *c asm("$2") = &D_00372710;

    __asm__ volatile(
        ".set noreorder\n"
        "addi $9, $5, -1\n"
        "addi $10, $5, -2\n"
        "lqc2 $vf1, 0($2)\n"
        "sqc2 $vf0, 0($6)\n"
        "sll $11, $9, 0x4\n"
        "add $11, $11, $6\n"
        "sqc2 $vf0, 0($11)\n"
        "move $8, $9\n"
        "move $11, $0\n"
        ".Lw64a_1:\n"
        "blez $8, .Lw64a_2\n"
        "addi $8, $8, -1\n"
        "sll $12, $11, 0x4\n"
        "addi $13, $12, 16\n"
        "add $14, $12, $4\n"
        "add $15, $13, $4\n"
        "add $16, $13, $29\n"
        "lqc2 $vf10, 0($14)\n"
        "lqc2 $vf11, 0($15)\n"
        "vsub.xyzw $vf10xyzw, $vf11xyzw, $vf10xyzw\n"
        "sqc2 $vf10, 0($16)\n"
        "b .Lw64a_1\n"
        "addi $11, $11, 1\n"
        ".Lw64a_2:\n"
        "lqc2 $vf10, 32($29)\n"
        "lqc2 $vf11, 16($29)\n"
        "lqc2 $vf12, 0($6)\n"
        "vsub.xyzw $vf10xyzw, $vf10xyzw, $vf11xyzw\n"
        "vsub.xyzw $vf10xyzw, $vf10xyzw, $vf12xyzw\n"
        "sqc2 $vf10, 16($6)\n"
        "vaddx.xyzw $vf11xyzw, $vf0xyzw, $vf1x\n"
        "sqc2 $vf11, 16($29)\n"
        "move $8, $10\n"
        "addi $8, $8, -1\n"
        "addi $11, $0, 1\n"
        ".Lw64a_3:\n"
        "blez $8, .Lw64a_4\n"
        "addi $8, $8, -1\n"
        "sll $12, $11, 0x4\n"
        "addi $13, $12, 16\n"
        "addi $14, $13, 16\n"
        "add $15, $12, $29\n"
        "add $16, $13, $29\n"
        "add $17, $14, $29\n"
        "add $18, $13, $6\n"
        "add $19, $12, $6\n"
        "lqc2 $vf10, 0($15)\n"
        "lqc2 $vf11, 0($16)\n"
        "lqc2 $vf12, 0($17)\n"
        "lqc2 $vf13, 0($19)\n"
        "vdiv Q, $vf0w, $vf10x\n"
        "vwaitq\n"
        "vaddq.x $vf15x, $vf0x, Q\n"
        "vdiv Q, $vf0w, $vf10y\n"
        "vwaitq\n"
        "vaddq.y $vf15y, $vf0y, Q\n"
        "vdiv Q, $vf0w, $vf10z\n"
        "vwaitq\n"
        "vaddq.z $vf15z, $vf0z, Q\n"
        "vsub.xyzw $vf16xyzw, $vf12xyzw, $vf11xyzw\n"
        "vmul.xyzw $vf17xyzw, $vf13xyzw, $vf15xyzw\n"
        "vsub.xyzw $vf17xyzw, $vf16xyzw, $vf17xyzw\n"
        "sqc2 $vf17, 0($18)\n"
        "vmuly.xyzw $vf18xyzw, $vf15xyzw, $vf1y\n"
        "vaddx.xyzw $vf18xyzw, $vf18xyzw, $vf1x\n"
        "sqc2 $vf18, 0($16)\n"
        "b .Lw64a_3\n"
        "addi $11, $11, 1\n"
        ".Lw64a_4:\n"
        "sll $11, $9, 0x4\n"
        "add $11, $11, $6\n"
        "sll $12, $10, 0x4\n"
        "add $12, $12, $6\n"
        "lqc2 $vf10, 0($11)\n"
        "lqc2 $vf11, 0($12)\n"
        "vsub.xyzw $vf11xyzw, $vf11xyzw, $vf10xyzw\n"
        "sqc2 $vf11, 0($12)\n"
        "move $11, $10\n"
        ".Lw64a_5:\n"
        "blezl $11, .Lw64a_6\n"
        "nop\n"
        "sll $12, $11, 0x4\n"
        "addi $13, $12, 16\n"
        "add $15, $12, $29\n"
        "add $16, $12, $6\n"
        "add $17, $13, $6\n"
        "lqc2 $vf10, 0($15)\n"
        "lqc2 $vf11, 0($16)\n"
        "lqc2 $vf12, 0($17)\n"
        "vsub.xyzw $vf11xyzw, $vf11xyzw, $vf12xyzw\n"
        "vdiv Q, $vf11x, $vf10x\n"
        "vwaitq\n"
        "vaddq.x $vf15x, $vf0x, Q\n"
        "vdiv Q, $vf11y, $vf10y\n"
        "vwaitq\n"
        "vaddq.y $vf15y, $vf0y, Q\n"
        "vdiv Q, $vf11z, $vf10z\n"
        "vwaitq\n"
        "vaddq.z $vf15z, $vf0z, Q\n"
        "sqc2 $vf15, 0($16)\n"
        "b .Lw64a_5\n"
        "addi $11, $11, -1\n"
        ".Lw64a_6:\n"
        ".set reorder\n"
        : : "r"(c), "r"(a), "r"(n), "r"(b), "m"(buf[0])
        : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15",
          "$16", "$17", "$18", "$19", "memory");
}

/* func_00199888 (from hand/nostrict/text_00180000_s6_11.c). */
#include "data/types/nostrict_text_00180000_s6_11.h"
extern SplV4 D_00372720;
void func_00199888(u128 *out, u128 *p, u128 *q, f32 t) {
    s32 i = (s32) t;
    SplV4 *c = &D_00372720;

    p += i;
    q += i;
    c->z = t - (f32) i;
    __asm__ volatile(
        ".set noreorder\n"
        "lqc2 $vf1, 0(%1)\n"
        "lqc2 $vf2, 16(%1)\n"
        "lqc2 $vf3, 0(%2)\n"
        "lqc2 $vf4, 16(%2)\n"
        "lqc2 $vf5, 0(%3)\n"
        "vsub.xyzw $vf10xyzw, $vf4xyzw, $vf3xyzw\n"
        "vmuly.xyzw $vf11xyzw, $vf3xyzw, $vf5y\n"
        "vmulx.xyzw $vf12xyzw, $vf3xyzw, $vf5x\n"
        "vsub.xyzw $vf13xyzw, $vf2xyzw, $vf1xyzw\n"
        "vmulz.xyzw $vf10xyzw, $vf10xyzw, $vf5z\n"
        "vadd.xyzw $vf11xyzw, $vf11xyzw, $vf4xyzw\n"
        "vadd.xyzw $vf10xyzw, $vf10xyzw, $vf12xyzw\n"
        "vsub.xyzw $vf13xyzw, $vf13xyzw, $vf11xyzw\n"
        "vmulz.xyzw $vf10xyzw, $vf10xyzw, $vf5z\n"
        "vadd.xyzw $vf10xyzw, $vf10xyzw, $vf13xyzw\n"
        "vmulz.xyzw $vf10xyzw, $vf10xyzw, $vf5z\n"
        "vadd.xyzw $vf10xyzw, $vf10xyzw, $vf1xyzw\n"
        "sqc2 $vf10, 0(%0)\n"
        ".set reorder\n"
        : : "r"(out), "r"(p), "r"(q), "r"(c) : "memory");
}

/* func_00199ac8 (from hand/nostrict/text_00190000_s11_w62.c). */
typedef struct {
    u8 b0;
    s8 type;
    s16 n;
    u8 pad4[12];
} ShipolyPrim;
typedef struct {
    s32 w0;
    s32 w4;
} ShipolyMdl;
typedef struct {
    s16 x, y, z;
} ShipolyEnt;
typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 padC[2];
    ShipolyEnt *ent;
    s32 pad18;
    ShipolyMdl *mdl;
    s32 unk20;
} ShipolySlot;
typedef struct {
    s32 frame;
    s32 id;
    u8 pad8[5];
    u8 bD;
    u8 padE[6];
    u8 b14;
    u8 b15;
} ShipolyKey;
typedef struct {
    u32 cur;
    u8 n;
    u8 b5;
    u8 pad6[2];
    f32 (*buf)[2][4];
} ShipolyWork;
typedef struct {
    u8 c[4][4];
    u16 idx[4];
    u16 uv[4][2];
} ShipolyVtx6;
typedef struct {
    u8 c[4][4];
    u16 idx[4];
} ShipolyVtx4;
void func_00199908(ShipolyKey *, f32 *, f32 *);
void func_001999f0(ShipolyKey *, s32 *, s32 *, s32 *, s32 *);
static inline void inl_alpha(u8 (*c)[4], s32 k, s32 d, f32 a, f32 db) {
    if (k >= d) {
        c[0][3] = c[1][3] = c[2][3] = c[3][3] = 0;
    } else {
        c[0][3] = c[1][3] = a;
        c[2][3] = c[3][3] = (u8) a - db;
    }
}
/* func_00199ac8: hand/nostrict (fill), rodata at 0x48fb70, no context. MATCH (wqb03_rr.py), FLAGGED:
   dead FP tests (2.96 flow2 deletes them, no code left): `(f32)same < a` in the seg - same > 0 block,
   the case-4 loop tests ((f32)(m * 2), m, m >> 1, u, (s32)q, u >> 1 against a), `(f32)m < 0.0f` at the
   top of the case-6 loop, and `(f32)u < a` before the `p = ...` step of the while body. They only
   steer global-alloc priorities (k/m/u counters, du vs the case-6 copy of d, db vs the loop 0.0f).
   From s11w43's 19w draft (s11w62). */
void func_00199ac8(ShipolySlot *r, ShipolyKey *key, ShipolyWork *w) {
    f32 pts[32][4] __attribute__((aligned(16)));
    f32 tmp[32][4] __attribute__((aligned(16)));
    f32 out[4] __attribute__((aligned(16)));
    f32 v[2][4] __attribute__((aligned(16)));
    s32 u0, u1, t0, t1;
    u32 cur;
    f32 (*buf)[2][4];
    u8 n;
    s32 seg, segs, same;
    ShipolyEnt *ent;
    s32 i, j, k, d;
    s32 i2, i3, i4;
    f32 a, da, db;
    u32 ui;
    ShipolyPrim *p;
    s32 sz, u, du;
    s32 idx;
    s32 m;
    s32 nu;

    cur = w->cur;
    buf = w->buf;
    n = w->n;
    seg = r->w8;
    same = 0;
    func_00199908(key, buf[cur][0], buf[cur][1]);
    segs = seg + 1;
    ent = r->ent;
    for (j = 0; j < 2; j++) {
        for (i = 0; (u32) i < n; i++) {
            idx = cur - i;
            idx += (idx < 0) * n;
            PlatVu0CopyVector(pts[i], (f32 *) ((u32) buf + (idx * 2 + j) * 16));
            if (key->b15) PlatVu0SubVector(pts[i], pts[i], (*(f32 (*)[4])&D_003701D0));
        }
        func_001996d0(pts, n, tmp);
        for (i = 0; i < segs; i++) {
            func_00199888(out, pts, tmp, (f32) i / (f32) seg * (f32) (u32) (n - 1));
            ent[i * 2 + j].x = out[0];
            ent[i * 2 + j].y = out[1];
            ent[i * 2 + j].z = out[2];
        }
    }
    if (w->b5) {
        ShipolyEnt *e = r->ent;
        i3 = 0;
        for (i2 = seg; i2 > 0; i2--) {
            if (e[i2 * 2].x != e[(i2 - 1) * 2].x || e[i2 * 2].y != e[(i2 - 1) * 2].y || e[i2 * 2].z != e[(i2 - 1) * 2].z) break;
            same++;
        }
    }
    if (key->b14) {
        ShipolyEnt *e2;
        a = 1.0f;
        da = 1.0f;
        e2 = r->ent;
        if (seg - same > 0) {
            if ((f32)same < a) sz = 0;
            da = 1.0f / (f32) (same > 0 ? seg - same : seg);
        }
        for (i2 = 0; i2 < segs; i2++) {
            for (j = 0; j < 2; j++) {
                v[j][0] = e2[i2 * 2 + j].x;
                v[j][1] = e2[i2 * 2 + j].y;
                v[j][2] = e2[i2 * 2 + j].z;
            }
            PlatVu0InterVector(v[0], v[0], v[1], a);
            a -= da;
            e2[i2 * 2].x = v[0][0];
            e2[i2 * 2].y = v[0][1];
            e2[i2 * 2].z = v[0][2];
            if (a <= 0.0f) a = 0.0f;
        }
    }
    if (w->b5) {
        p = (ShipolyPrim *) ((u8 *) r->mdl + r->mdl->w4);
        a = 128.0f;
        func_001999f0(key, &u0, &u1, &t0, &t1);
        db = 0.0f;
        d = seg - same;
        k = i3;
        if (d <= 0) {
            a = 0.0f;
            u = 0;
            du = k;
        } else {
            u = u0;
            db = 128.0f / (f32) d;
            du = (u1 - u0) / d;
        }
        while (p->type != -1) {
            sz = 0;
            switch (p->type) {
            case 4: {
                ShipolyVtx4 *q = (ShipolyVtx4 *) (p + 1);
                for (m = 0; m < p->n; m++) {
                    inl_alpha(q->c, k, seg - same, a, db);
                    a -= db;
                    u += du;
                    if (u1 < u) u = u1;
                    if (a < 0.0f) a = 0.0f;
                    q++;
                    if ((f32)(m * 2) < a) sz = 0;
                    k++;
                    if ((f32)m < a) sz = 0;
                    if ((f32)(m >> 1) < a) sz = 0;
                    if ((f32)u < a) sz = 0;
                    if ((f32)(s32)q < a) sz = 0;
                    if ((f32)(u >> 1) < a) sz = 0;
                }
                sz = 24;
                break;
            }
            case 6: {
                ShipolyVtx6 *q = (ShipolyVtx6 *) (p + 1);
                for (m = 0; m < p->n; m++) {
                    if ((f32)m < 0.0f) sz = 0;
                    inl_alpha(q->c, k, seg - same, a, db);
                    q->uv[1][0] = u;
                    q->uv[0][0] = u;
                    nu = u + du;
                    q->c[0][2] = q->c[1][2] = q->c[2][2] = q->c[3][2] = 0xFF;
                    q->c[0][1] = q->c[1][1] = q->c[2][1] = q->c[3][1] = 0xFF;
                    q->c[0][0] = q->c[1][0] = q->c[2][0] = q->c[3][0] = 0xFF;
                    q->uv[3][0] = nu - 1;
                    q->uv[2][0] = nu - 1;
                    q->uv[0][1] = q->uv[2][1] = t1;
                    q->uv[1][1] = q->uv[3][1] = t0;
                    a -= db;
                    u = nu;
                    if (u1 < u) u = u1;
                    if (a < 0.0f) a = 0.0f;
                    q++;
                    k++;
                }
                sz = 40;
                break;
            }
            case 0: case 1: case 2: case 3: case 5: case 7:
                return;
            }
            if ((f32)u < a) i = 0;
            p = (ShipolyPrim *) ((u8 *) p + sz * p->n);
            p++;
        }
    }
    if (key->bD == 0) {
        w->cur++;
        if (w->cur >= w->n) {
            w->b5 = 0;
            w->cur = 0;
        }
    }
}

/* pppRyjDrawShipolyFrame (from hand/nostrict/text_00190000_b08.c). */
#include "data/pieces/D_002E26A0.h"
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 unk0;
    u8 *inst;
    s32 time;
    s32 unkC;
} PppSlot;
typedef struct {
    u8 pad[0x80];
    PppSlot *slots;
    u8 pad84[0x2C];
    u64 flags;
} PppSystem;
extern s32 D_0061621C;
extern PppSystem *D_00615E60;
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame;
    u8 pad10[0x8D];
    u8 unk9D;
} PppObject;
typedef struct {
    u32 flags;
    u8 pad04[0x12];
    u16 unk16;
} DMdl;
typedef struct {
    s32 pad0[4];
    u32 tex;
    s32 pad14[2];
    DMdl *mdl;
    s32 unk20;
} DSlot;
typedef struct {
    u8 pad00[0x10];
    DSlot *slots;
    void *shapes;
} DSys;
extern DSys *D_00615E64;
typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 pad[4];
    ShipolyMdl *mdl;
    s32 unk20;
} ShipolySlot_9a290;
typedef struct {
    s32 frame;
    s32 id;
    u8 pad8[6];
    u8 n;
} ShipolyKey_9a290;
typedef struct {
    u8 pad0[4];
    u8 n;
    u8 pad5[3];
    u8 *buf;
} ShipolyWork_9a290;
void *func_0017f958(void *, s32);
void pppRyjDrawShipolyFrame(PppObject *obj, ShipolyKey_9a290 *key, PppEntry *e) {
    ShipolyWork_9a290 *w = PPP_WORK(ShipolyWork_9a290, obj, e, 2);
    ShipolySlot_9a290 *r;
    ShipolyPrim *p;
    s32 i, j, k, sz;
    u8 *q;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (key->id == 0xFFFF)
        return;
    r = &((ShipolySlot_9a290 *) D_00615E64->slots)[key->id];
    if (w->buf == 0) {
        w->n = key->n;
        if (w->n < 4)
            w->n = 4;
        else if (w->n >= 32)
            w->n = 32;
        w->buf = func_0017f958(D_00615E64, w->n << 5);
        for (i = 0; i < w->n; i++)
            func_00199908(key, w->buf + i * 32, w->buf + i * 32 + 16);
    }
    k = 0;
    p = (ShipolyPrim *) ((u8 *) r->mdl + r->mdl->w4);
    while (p->type != -1) {
        sz = 0;
        switch (p->type) {
        case 4:
            q = (u8 *) p + 16;
            for (j = 0; j < p->n; j++) {
                ((u16 *) (q + 16))[0] = k * 2;
                ((u16 *) (q + 16))[1] = k * 2 + 1;
                ((u16 *) (q + 16))[2] = k * 2 + 2;
                ((u16 *) (q + 16))[3] = k * 2 + 3;
                k++;
                q += 24;
            }
            sz = 24;
            break;
        case 6:
            q = (u8 *) p + 16;
            for (j = 0; j < p->n; j++) {
                ((u16 *) (q + 16))[0] = k * 2;
                ((u16 *) (q + 16))[1] = k * 2 + 1;
                ((u16 *) (q + 16))[2] = k * 2 + 2;
                ((u16 *) (q + 16))[3] = k * 2 + 3;
                k++;
                q += 40;
            }
            sz = 40;
            break;
        case 0: case 1: case 2: case 3: case 5: case 7:
            return;
        }
        p = (ShipolyPrim *) ((u8 *) p + sz * p->n);
        p++;
    }
    if (r->w0 != r->w8 * 2 + 2)
        return;
    func_00199ac8(r, key, w);
}

/* pppRyjDrawShipolyDraw (from hand/nostrict/text_00190000_b08.c). */
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
extern s32 D_00616224;
typedef struct {
    u8 pad[0x10];
    PppMtx m;
    PppMtx m2;
    s32 unk90;
    s32 unk94;
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;
typedef struct {
    s32 flags;
    void *p04;
    u16 h08;
    u8 b0A;
    s32 w0C;
    union { u64 d; struct { s32 u, v; } s; } t10;
    u8 r, g, b, a;
    s32 w1C;
    void *p20;
    void *p24;
    void *p28;
    void *p2C;
    void *p30;
    s32 w34;
    s32 w38;
    s32 w3C;
    s32 w40;
    void *p44;
    s32 w48;
    u8 b4C;
    u8 b4D;
    u8 pad4E[0x12];
} DParam;
typedef struct {
    u8 pad[8];
    u8 r, g, b, a;
} DColWork;
extern u8 D_00616240[];
extern u8 D_00616140[];
extern u8 D_00616100[];
extern PppMtx D_00615FC0;
s32 func_001aaf88(DMdl *, DParam *, s32);
typedef struct {
    s32 frame;
    s32 slot;
    u8 flags;
    u8 b9, bA, bB, bC;
    u8 padD[8];
    u8 b15;
    u8 pad16[3];
    u8 b19;
} ShipolyDKey;
extern PppMtx D_00616180;
extern PppMtx D_00616080;
void pppRyjDrawShipolyDraw(PppObject *obj, ShipolyDKey *key, PppEntry *e) {
    DParam p;
    PppMtx mtx;
    DColWork *w;
    DSlot *s;
    DMdl *m;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DColWork, obj, e, 1);
    p.a = w->a;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    p.flags = 0;
    if (key->flags & 2) {
        p.flags = 4;
        if (!(m->flags & 1))
            p.flags |= 8;
    } else {
        if (key->flags & 1)
            p.flags = 128;
        if (!(m->flags & 1))
            p.flags |= 8;
    }
    if (!(m->flags & 2))
        p.flags |= 16;
    if (key->b9)
        p.flags |= 0x200;
    if (key->bB)
        p.flags |= 0x100;
    if (key->bA) {
        p.flags |= 0x2000;
        p.p30 = mtx;
        PlatVu0MulMatrix(mtx, D_00615FC0, D_00615E68->m);
    }
    p.p44 = 0;
/*P*/
    p.h08 = m->unk16;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.p04 = D_00616240;
/*Q*/
    if (key->b15) {
        PlatVu0UnitMatrix(D_00615E68->m2);
        PlatVu0CopyVectorXYZ(D_00615E68->m2[3], (*(f32 (*)[4])&D_003701D0));
        PlatVu0MulMatrix(D_00615E68->m2, D_00616180, D_00615E68->m2);
        p.p20 = D_00615E68->m2;
    } else {
        p.p20 = D_00616080;
    }
/*P*/
    p.r = w->r;
    p.g = w->g;
    p.b = w->b;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.w0C = 0;
    p.t10.d = 0;
    p.w40 = 0;
    p.p2C = D_00615E68->m;
    p.w34 = D_00616224;
    p.b4C = key->bC;
    p.b4D = key->b19;
/*Q*/
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

/* func_0019a828 (from hand/nostrict/text_00190000_h64.c). */
extern u128 D_00372730;
void func_0019a828(u128 *a, s32 n, u128 *b) {
    u128 buf[128];
    register u128 *c asm("$2") = &D_00372730;

    __asm__ volatile(
        ".set noreorder\n"
        "addi $9, $5, -1\n"
        "addi $10, $5, -2\n"
        "lqc2 $vf1, 0($2)\n"
        "sqc2 $vf0, 0($6)\n"
        "sll $11, $9, 0x4\n"
        "add $11, $11, $6\n"
        "sqc2 $vf0, 0($11)\n"
        "move $8, $9\n"
        "move $11, $0\n"
        ".Lw64b_1:\n"
        "blez $8, .Lw64b_2\n"
        "addi $8, $8, -1\n"
        "sll $12, $11, 0x4\n"
        "addi $13, $12, 16\n"
        "add $14, $12, $4\n"
        "add $15, $13, $4\n"
        "add $16, $13, $29\n"
        "lqc2 $vf10, 0($14)\n"
        "lqc2 $vf11, 0($15)\n"
        "vsub.xyzw $vf10xyzw, $vf11xyzw, $vf10xyzw\n"
        "sqc2 $vf10, 0($16)\n"
        "b .Lw64b_1\n"
        "addi $11, $11, 1\n"
        ".Lw64b_2:\n"
        "lqc2 $vf10, 32($29)\n"
        "lqc2 $vf11, 16($29)\n"
        "lqc2 $vf12, 0($6)\n"
        "vsub.xyzw $vf10xyzw, $vf10xyzw, $vf11xyzw\n"
        "vsub.xyzw $vf10xyzw, $vf10xyzw, $vf12xyzw\n"
        "sqc2 $vf10, 16($6)\n"
        "vaddx.xyzw $vf11xyzw, $vf0xyzw, $vf1x\n"
        "sqc2 $vf11, 16($29)\n"
        "move $8, $10\n"
        "addi $8, $8, -1\n"
        "addi $11, $0, 1\n"
        ".Lw64b_3:\n"
        "blez $8, .Lw64b_4\n"
        "addi $8, $8, -1\n"
        "sll $12, $11, 0x4\n"
        "addi $13, $12, 16\n"
        "addi $14, $13, 16\n"
        "add $15, $12, $29\n"
        "add $16, $13, $29\n"
        "add $17, $14, $29\n"
        "add $18, $13, $6\n"
        "add $19, $12, $6\n"
        "lqc2 $vf10, 0($15)\n"
        "lqc2 $vf11, 0($16)\n"
        "lqc2 $vf12, 0($17)\n"
        "lqc2 $vf13, 0($19)\n"
        "vdiv Q, $vf0w, $vf10x\n"
        "vwaitq\n"
        "vaddq.x $vf15x, $vf0x, Q\n"
        "vdiv Q, $vf0w, $vf10y\n"
        "vwaitq\n"
        "vaddq.y $vf15y, $vf0y, Q\n"
        "vdiv Q, $vf0w, $vf10z\n"
        "vwaitq\n"
        "vaddq.z $vf15z, $vf0z, Q\n"
        "vsub.xyzw $vf16xyzw, $vf12xyzw, $vf11xyzw\n"
        "vmul.xyzw $vf17xyzw, $vf13xyzw, $vf15xyzw\n"
        "vsub.xyzw $vf17xyzw, $vf16xyzw, $vf17xyzw\n"
        "sqc2 $vf17, 0($18)\n"
        "vmuly.xyzw $vf18xyzw, $vf15xyzw, $vf1y\n"
        "vaddx.xyzw $vf18xyzw, $vf18xyzw, $vf1x\n"
        "sqc2 $vf18, 0($16)\n"
        "b .Lw64b_3\n"
        "addi $11, $11, 1\n"
        ".Lw64b_4:\n"
        "sll $11, $9, 0x4\n"
        "add $11, $11, $6\n"
        "sll $12, $10, 0x4\n"
        "add $12, $12, $6\n"
        "lqc2 $vf10, 0($11)\n"
        "lqc2 $vf11, 0($12)\n"
        "vsub.xyzw $vf11xyzw, $vf11xyzw, $vf10xyzw\n"
        "sqc2 $vf11, 0($12)\n"
        "move $11, $10\n"
        ".Lw64b_5:\n"
        "blezl $11, .Lw64b_6\n"
        "nop\n"
        "sll $12, $11, 0x4\n"
        "addi $13, $12, 16\n"
        "add $15, $12, $29\n"
        "add $16, $12, $6\n"
        "add $17, $13, $6\n"
        "lqc2 $vf10, 0($15)\n"
        "lqc2 $vf11, 0($16)\n"
        "lqc2 $vf12, 0($17)\n"
        "vsub.xyzw $vf11xyzw, $vf11xyzw, $vf12xyzw\n"
        "vdiv Q, $vf11x, $vf10x\n"
        "vwaitq\n"
        "vaddq.x $vf15x, $vf0x, Q\n"
        "vdiv Q, $vf11y, $vf10y\n"
        "vwaitq\n"
        "vaddq.y $vf15y, $vf0y, Q\n"
        "vdiv Q, $vf11z, $vf10z\n"
        "vwaitq\n"
        "vaddq.z $vf15z, $vf0z, Q\n"
        "sqc2 $vf15, 0($16)\n"
        "b .Lw64b_5\n"
        "addi $11, $11, -1\n"
        ".Lw64b_6:\n"
        ".set reorder\n"
        : : "r"(c), "r"(a), "r"(n), "r"(b), "m"(buf[0])
        : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15",
          "$16", "$17", "$18", "$19", "memory");
}

/* func_0019a9e0 (from hand/nostrict/text_00180000_s6_11.c). */
extern SplV4 D_00372740;
void func_0019a9e0(u128 *out, u128 *p, u128 *q, f32 t) {
    s32 i = (s32) t;
    SplV4 *c = &D_00372740;

    p += i;
    q += i;
    c->z = t - (f32) i;
    __asm__ volatile(
        ".set noreorder\n"
        "lqc2 $vf1, 0(%1)\n"
        "lqc2 $vf2, 16(%1)\n"
        "lqc2 $vf3, 0(%2)\n"
        "lqc2 $vf4, 16(%2)\n"
        "lqc2 $vf5, 0(%3)\n"
        "vsub.xyzw $vf10xyzw, $vf4xyzw, $vf3xyzw\n"
        "vmuly.xyzw $vf11xyzw, $vf3xyzw, $vf5y\n"
        "vmulx.xyzw $vf12xyzw, $vf3xyzw, $vf5x\n"
        "vsub.xyzw $vf13xyzw, $vf2xyzw, $vf1xyzw\n"
        "vmulz.xyzw $vf10xyzw, $vf10xyzw, $vf5z\n"
        "vadd.xyzw $vf11xyzw, $vf11xyzw, $vf4xyzw\n"
        "vadd.xyzw $vf10xyzw, $vf10xyzw, $vf12xyzw\n"
        "vsub.xyzw $vf13xyzw, $vf13xyzw, $vf11xyzw\n"
        "vmulz.xyzw $vf10xyzw, $vf10xyzw, $vf5z\n"
        "vadd.xyzw $vf10xyzw, $vf10xyzw, $vf13xyzw\n"
        "vmulz.xyzw $vf10xyzw, $vf10xyzw, $vf5z\n"
        "vadd.xyzw $vf10xyzw, $vf10xyzw, $vf1xyzw\n"
        "sqc2 $vf10, 0(%0)\n"
        ".set reorder\n"
        : : "r"(out), "r"(p), "r"(q), "r"(c) : "memory");
}

/* func_0019ab38 (from hand/nostrict/text_00190000_s11_w62.c). */
typedef struct {
    s32 frame;
    s32 id;
    u8 pad8[5];
    u8 bD;
    u8 padE[2];
    u16 h10, h12;
    f32 f14;
    u16 h18, h1A;
    f32 f1C;
    u8 b20;
    u8 pad21[5];
    s16 h26;
    s16 h28;
} BoneKey;
typedef struct {
    u32 cur;
    u8 n;
    u8 b5;
    u8 pad6[2];
    f32 (*buf)[2][4];
    u8 padC[4];
    f32 v0[4];
    f32 v1[4];
} BoneWork;
typedef struct {
    u8 pad[0xA0];
    u8 *pA0;
    u8 padA4[0xC];
    u64 flags;
    u8 padB8[0xFF];
} PppSystemB;
typedef struct {
    u8 pad[0xB7];
    u8 bB7;
} PppSystemB7;
void func_0019aa60(BoneKey *, s32 *, s32 *, s32 *, s32 *);
s32 func_00122ff8(void *);
void func_001315c0(void *, s32, f32, f32 *);
#define D_00615E60 (*(PppSystemB *(*)) &D_00615E60)
/* func_0019ab38: hand/nostrict (fill), rodata at 0x48fbb0, no context. MATCH (wqb03_rr.py), FLAGGED:
   the same dead FP tests as func_00199ac8 above (its while loop ported from that match), plus
   `if (out[0] < 0.0f) sz = 0;` after the func_0019a9e0 call (lengthens the out-address pseudo so segs
   outranks it for s7). From session8 w9's draft (s11w62). */
void func_0019ab38(ShipolySlot *r, BoneKey *key, BoneWork *w) {
    f32 pts[128][4] __attribute__((aligned(16)));
    f32 tmp[128][4] __attribute__((aligned(16)));
    f32 out[4] __attribute__((aligned(16)));
    f32 v[2][4] __attribute__((aligned(16)));
    s32 u0, u1, t0, t1;
    u32 cur;
    f32 (*buf)[2][4];
    void *src; /* the actor (D_002E26A0[0]) or pA0 */
    s32 same;
    f32 *v0p;
    f32 *v1p;
    u8 n;
    s32 seg, segs;
    ShipolyEnt *ent;
    s32 i, j, k, d;
    s32 i2, i3, i4;
    f32 a, da, db;
    u32 ui;
    ShipolyPrim *p;
    s32 sz, u, du;
    s32 idx;
    s32 m;
    s32 nu;
    s32 b0, b1;

    cur = w->cur;
    buf = w->buf;
    src = D_002E26A0[0];
    if (D_00615E60->pA0)
        src = D_00615E60->pA0;
    v0p = w->v0;
    v1p = w->v1;
    seg = r->w8;
    n = w->n;
    PlatVu0CopyVector(buf[cur][0], v0p);
    PlatVu0CopyVector(buf[cur][1], v1p);
    same = 0;
    segs = seg + 1;
    ent = r->ent;
    for (j = 0; j < 2; j++) {
        for (i = 0; (u32) i < n; i++) {
            idx = cur - i;
            idx += (idx < 0) * n;
            PlatVu0SubVector(pts[i], (f32 *) ((u32) buf + (idx * 2 + j) * 16), (f32 *) (src + 16));
        }
        func_0019a828(pts, n, tmp);
        for (i = 0; i < segs; i++) {
            func_0019a9e0(out, pts, tmp, (f32) i / (f32) seg * (f32) (u32) (n - 1));
            if (out[0] < 0.0f) sz = 0;
            ent[i * 2 + j].x = out[0];
            ent[i * 2 + j].y = out[1];
            ent[i * 2 + j].z = out[2];
        }
    }
    if (w->b5) {
        ShipolyEnt *e = r->ent;
        i3 = 0;
        for (i2 = seg; i2 > 0; i2--) {
            if (e[i2 * 2].x != e[(i2 - 1) * 2].x || e[i2 * 2].y != e[(i2 - 1) * 2].y || e[i2 * 2].z != e[(i2 - 1) * 2].z) break;
            same++;
        }
    }
    if (key->b20) {
        ShipolyEnt *e2;
        a = 1.0f;
        da = 1.0f;
        e2 = r->ent;
        if (seg - same > 0) {
            if ((f32)same < a) sz = 0;
            da = 1.0f / (f32) (same > 0 ? seg - same : seg);
        }
        for (i2 = 0; i2 < segs; i2++) {
            for (j = 0; j < 2; j++) {
                v[j][0] = e2[i2 * 2 + j].x;
                v[j][1] = e2[i2 * 2 + j].y;
                v[j][2] = e2[i2 * 2 + j].z;
            }
            PlatVu0InterVector(v[0], v[0], v[1], a);
            a -= da;
            e2[i2 * 2].x = v[0][0];
            e2[i2 * 2].y = v[0][1];
            e2[i2 * 2].z = v[0][2];
            if (a <= 0.0f) a = 0.0f;
        }
    }
    if (w->b5) {
        p = (ShipolyPrim *) ((u8 *) r->mdl + r->mdl->w4);
        a = 128.0f;
        func_0019aa60(key, &u0, &u1, &t0, &t1);
        db = 0.0f;
        d = seg - same;
        k = i3;
        if (d <= 0) {
            a = 0.0f;
            u = 0;
            du = k;
        } else {
            u = u0;
            db = 128.0f / (f32) d;
            du = (u1 - u0) / d;
        }
        while (p->type != -1) {
            sz = 0;
            switch (p->type) {
            case 4: {
                ShipolyVtx4 *q = (ShipolyVtx4 *) (p + 1);
                for (m = 0; m < p->n; m++) {
                    inl_alpha(q->c, k, seg - same, a, db);
                    a -= db;
                    u += du;
                    if (u1 < u) u = u1;
                    if (a < 0.0f) a = 0.0f;
                    q++;
                    if ((f32)(m * 2) < a) sz = 0;
                    k++;
                    if ((f32)m < a) sz = 0;
                    if ((f32)(m >> 1) < a) sz = 0;
                    if ((f32)u < a) sz = 0;
                    if ((f32)(s32)q < a) sz = 0;
                    if ((f32)(u >> 1) < a) sz = 0;
                }
                sz = 24;
                break;
            }
            case 6: {
                ShipolyVtx6 *q = (ShipolyVtx6 *) (p + 1);
                for (m = 0; m < p->n; m++) {
                    if ((f32)m < 0.0f) sz = 0;
                    inl_alpha(q->c, k, seg - same, a, db);
                    q->uv[1][0] = u;
                    q->uv[0][0] = u;
                    nu = u + du;
                    q->c[0][2] = q->c[1][2] = q->c[2][2] = q->c[3][2] = 0xFF;
                    q->c[0][1] = q->c[1][1] = q->c[2][1] = q->c[3][1] = 0xFF;
                    q->c[0][0] = q->c[1][0] = q->c[2][0] = q->c[3][0] = 0xFF;
                    q->uv[3][0] = nu - 1;
                    q->uv[2][0] = nu - 1;
                    q->uv[0][1] = q->uv[2][1] = t1;
                    q->uv[1][1] = q->uv[3][1] = t0;
                    a -= db;
                    u = nu;
                    if (u1 < u) u = u1;
                    if (a < 0.0f) a = 0.0f;
                    q++;
                    k++;
                }
                sz = 40;
                break;
            }
            case 0: case 1: case 2: case 3: case 5: case 7:
                return;
            }
            if ((f32)u < a) i = 0;
            p = (ShipolyPrim *) ((u8 *) p + sz * p->n);
            p++;
        }
    }
    if (key->bD == 0) {
        if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
            w->cur++;
            if (w->cur >= w->n) {
                w->b5 = 0;
                w->cur = 0;
            }
        }
        if (key->h26 >= 0)
            b0 = (s16) (key->h26 | 0x1000);
        else
            b0 = key->h10 * 4 + key->h12;
        if (key->h28 >= 0)
            b1 = (s16) (key->h28 | 0x1000);
        else
            b1 = key->h18 * 4 + key->h1A;
        if (func_00122ff8(src)) {
            func_001315c0(src, b0, key->f14, v0p);
            func_001315c0(src, b1, key->f1C, v1p);
            PlatVu0CopyVector((f32 *) D_00615E60, v0p);
        } else {
            ((PppSystemB7 *) D_00615E60)->bB7 = 1;
        }
    }
}
#undef D_00615E60

/* func_0019b460 (from hand/nostrict/text_00190000_b08.c). */
typedef f32 PppVec4[4] __attribute__((aligned(16)));
typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 pad[4];
    ShipolyMdl *mdl;
    s32 unk20;
} ShipolySlot_9b460;
typedef struct {
    s32 frame;
    s32 id;
    u8 pad8[6];
    u8 n;
    u8 padF;
    u16 h10, h12;
    f32 f14;
    u16 h18, h1A;
    f32 f1C;
    u8 pad20[6];
    s16 h26;
    s16 h28;
} BoneKey_9b460;
typedef struct {
    u8 pad0[4];
    u8 n;
    u8 pad5[3];
    u8 *buf;
    u8 padC[4];
    PppVec4 v0;
    PppVec4 v1;
} BoneWork_9b460;
typedef struct {
    u8 c[4][4];
    u16 idx[4];
} ShipolyVtx;
typedef struct {
    u8 pad[0xA0];
    void *pA0;
    u8 padA4[0x13];
    u8 bB7;
} PppSystemB_9b460;
void func_0019b460(PppObject *obj, BoneKey_9b460 *key, PppEntry *e) {
    BoneWork_9b460 *w = PPP_WORK(BoneWork_9b460, obj, e, 1);
    ShipolySlot_9b460 *r;
    ShipolyPrim *p;
    s32 i, j, k, sz;
    u8 *q;

    if (key->id == 0xFFFF)
        return;
    if (w->buf == 0) {
        void *a;
        s32 b0, b1;
        w->n = key->n;
        w->buf = func_0017f958(D_00615E64, w->n << 5);
        a = D_002E26A0[0];
        if (((PppSystemB_9b460 *) D_00615E60)->pA0)
            a = ((PppSystemB_9b460 *) D_00615E60)->pA0;
        if (key->h26 >= 0)
            b0 = (s16) (key->h26 | 0x1000);
        else
            b0 = key->h10 * 4 + key->h12;
        if (key->h28 >= 0)
            b1 = (s16) (key->h28 | 0x1000);
        else
            b1 = key->h18 * 4 + key->h1A;
        if (func_00122ff8(a)) {
            func_001315c0(a, b0, key->f14, w->v0);
            func_001315c0(a, b1, key->f1C, w->v1);
        } else {
            ((PppSystemB_9b460 *) D_00615E60)->bB7 = 1;
        }
        for (i = 0; i < w->n; i++) {
            PlatVu0CopyVector((f32 *) (w->buf + i * 32), w->v0);
            PlatVu0CopyVector((f32 *) (w->buf + i * 32 + 16), w->v1);
        }
    }
    r = &((ShipolySlot_9b460 *) D_00615E64->slots)[key->id];
    k = 0;
    p = (ShipolyPrim *) ((u8 *) r->mdl + r->mdl->w4);
    while (p->type != -1) {
        sz = 0;
        switch (p->type) {
        case 4:
            q = (u8 *) p + 16;
            for (j = 0; j < p->n; j++) {
                ShipolyVtx *v = (ShipolyVtx *) q;
                v->idx[0] = k * 2;
                v->idx[1] = k * 2 + 1;
                v->idx[2] = k * 2 + 2;
                v->idx[3] = k * 2 + 3;
                k++;
                v->c[0][2] = v->c[1][2] = v->c[2][2] = v->c[3][2] = 0xFF;
                v->c[0][1] = v->c[1][1] = v->c[2][1] = v->c[3][1] = 0xFF;
                v->c[0][0] = v->c[1][0] = v->c[2][0] = v->c[3][0] = 0xFF;
                q += 24;
            }
            sz = 24;
            break;
        case 6:
            q = (u8 *) p + 16;
            for (j = 0; j < p->n; j++) {
                ShipolyVtx *v = (ShipolyVtx *) q;
                v->idx[0] = k * 2;
                v->idx[1] = k * 2 + 1;
                v->idx[2] = k * 2 + 2;
                v->idx[3] = k * 2 + 3;
                k++;
                v->c[0][2] = v->c[1][2] = v->c[2][2] = v->c[3][2] = 0xFF;
                v->c[0][1] = v->c[1][1] = v->c[2][1] = v->c[3][1] = 0xFF;
                v->c[0][0] = v->c[1][0] = v->c[2][0] = v->c[3][0] = 0xFF;
                q += 40;
            }
            sz = 40;
            break;
        case 0: case 1: case 2: case 3: case 5: case 7:
            return;
        }
        p = (ShipolyPrim *) ((u8 *) p + sz * p->n);
        p++;
    }
    if (r->w0 == r->w8 * 2 + 2)
        func_0019ab38(r, key, w);
}

/* pppRyjDrawShipolyBoneDraw (from hand/nostrict/text_00190000_b08.c). */
typedef struct {
    s32 frame;
    s32 id;
    u8 pad8[6];
    u8 n;
    u8 padF;
    u16 h10, h12;
    f32 f14;
    u16 h18, h1A;
    f32 f1C;
    u8 pad20[6];
    s16 h26;
    s16 h28;
} BoneKey_9b7f0;
typedef struct {
    u8 pad[0xA0];
    void *pA0;
    u8 padA4[0x13];
    u8 bB7;
} PppSystemB_9b7f0;
typedef struct {
    s32 frame;
    s32 slot;
    u8 flags;
    u8 b9, bA, bB, bC;
    u8 padD[0x17];
    u8 b24;
} BoneDKey;
void pppRyjDrawShipolyBoneDraw(PppObject *obj, BoneDKey *key, PppEntry *e) {
    DParam p;
    PppMtx mtx;
    DColWork *w;
    DSlot *s;
    DMdl *m;
    void *a; /* the actor (D_002E26A0[0]) or pA0 */

    func_0019b460(obj, (BoneKey_9b7f0 *) key, e);
    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DColWork, obj, e, 0);
    a = D_002E26A0[0];
    if (((PppSystemB_9b7f0 *) D_00615E60)->pA0)
        a = ((PppSystemB_9b7f0 *) D_00615E60)->pA0;
    p.a = w->a;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    p.flags = 0;
    if (key->flags & 2) {
        p.flags = 4;
        if (!(m->flags & 1))
            p.flags |= 8;
    } else {
        if (key->flags & 1)
            p.flags = 128;
        if (!(m->flags & 1))
            p.flags |= 8;
    }
    if (!(m->flags & 2))
        p.flags |= 16;
    if (key->b9)
        p.flags |= 0x200;
    if (key->bB)
        p.flags |= 0x100;
    if (key->bA) {
        p.flags |= 0x2000;
        p.p30 = mtx;
        PlatVu0MulMatrix(mtx, D_00615FC0, D_00615E68->m);
    }
    p.p44 = 0;
/*P*/
    p.h08 = m->unk16;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.p04 = D_00616240;
/*Q*/
    PlatVu0UnitMatrix(D_00615E68->m2);
    PlatVu0CopyVector(D_00615E68->m2[3], (f32 *) (a + 16));
    PlatVu0MulMatrix(D_00615E68->m2, D_00616180, D_00615E68->m2);
/*P*/
    p.p20 = D_00615E68->m2;
    p.r = w->r;
    p.g = w->g;
    p.b = w->b;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.w0C = 0;
    p.t10.d = 0;
    p.w40 = 0;
    p.p2C = D_00615E68->m;
    p.w34 = D_00616224;
    p.b4C = key->bC;
    p.b4D = key->b24;
/*Q*/
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

#include "data/pieces/D_00372720.h"
#include "data/pieces/D_00372740.h"
#include "data/pieces/D_002E26A0.h"
#include "data/data_0037.h"
