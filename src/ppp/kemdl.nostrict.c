/* The ppp model texture classes' draws, -fno-strict-aliasing
 * (docs/modules.md "Session 50"): pppKeMdlTfd / TfdUv and the "2" versions
 * fade or scroll a model's texture by a value with speed and acceleration in
 * the work area (a 16x16 page rebuilt with kemdltfd.c's helpers and
 * uploaded before the model's draw); pppKeMdlDtt draws a model's polygons as
 * projected sprites.  kemdl.c has the Cons.  Types named NAME_xxxxx are one
 * function's own view (tools/shift/s50move/assemble.py).  Read from the
 * code, not proved by a boot. */

/* pppKeMdlTfdDraw (from hand/nostrict/text_00190000_h63.c). */
#include "common.h"
#include "platform/gs.h"
#include "ppp.h"
#include "data/bss_0061.h"
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 unk0;
    u8 *inst;   /* +0x4 */
    s32 time;   /* +0x8 */
    s32 unkC;
} PppSlot;
typedef struct {
    u8 pad[0x30];
    f32 col[4];     /* +0x30 */
    u8 pad40[0x40];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem;
extern PppSystem *D_00615E60;
extern s32 D_0061621C;
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;
typedef struct {
    u8 pad[0x10];
    u32 tex;    /* +0x10 */
    u8 pad14[8];
    s32 *mdl;   /* +0x1C */
    s32 arg;    /* +0x20 */
} PppMdlRes; /* 0x24 */
typedef struct {
    s16 unk0;
    s16 len;    /* +0x2 */
    s8 flags;   /* +0x4 */
    u8 pad5[3];
} PppAnimFrame;
typedef struct {
    u8 pad[6];
    s16 n;      /* +0x6 */
    u8 pad8[8];
    PppAnimFrame frames[1]; /* +0x10 */
} PppAnim;
typedef struct {
    PppAnim *anim;
    s32 unk4;
} PppAnimRef;
typedef struct {
    u8 pad[0x10];
    PppMdlRes *res; /* +0x10 */
    PppAnimRef *anims; /* +0x14 */
} PppMdlBank;
extern PppMdlBank *D_00615E64;
extern s32 D_00616224;
typedef struct {
    s32 frame;
    s32 id;       /* +0x4 */
    f32 da, db, dc; /* +0x8 */
    s32 u, v;     /* +0x14 */
    u8 page;      /* +0x1C */
    u8 mode;      /* +0x1D */
} PppTfdKey;
typedef struct {
    f32 a, b, c;
} PppTfd;
void func_001a9460(f32, s32, s32, void *);
void func_001aa6b0(void *, s32, s32, s32);
void func_001a9790(s32, void *, s32, s32, s32, s32, s32);
void pppKeMdlTfdDraw(PppObject *obj, PppTfdKey *key, PppEntry *e) {
    PppTfd *w = PPP_WORK(PppTfd, obj, e, 2);
    u32 tex;
    s32 n;
    u8 *p, *q;

    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w->b += w->c;
        w->a += w->b;
        if (obj->frame == key->frame) {
            w->a += key->da;
            w->b += key->db;
            w->c += key->dc;
        }
    }
    if (key->id == 0xFFFF)
        return;
    {
        PppMdlRes *r = &D_00615E64->res[key->id];
        tex = r->tex;
    }
    n = key->page * 4;
    p = (u8 *) D_00616224 + 16;
    PlatGsSetDefLoadImage(p, ((tex >> 5) & 0x3FFF) + n, 4, (tex >> 19) & 0xF, 0, 0, 16, 16);
    *(u64 *) (p + 0x50) = 0x0800000000008100ULL;
    q = (u8 *) D_00616224;
    func_001a9460(w->a, key->u, key->v, q + 0x70);
    func_001aa6b0((void *) D_00616224, 263, 0, 0);
    D_00616224 = (s32) (q + 0x1070);
    func_001a9790(key->id, PPP_WORK(void, obj, e, 0), n, 0, 0, 1, 0);
}

/* pppKeMdlTfdUvDraw (from hand/nostrict/text_00180000_b07.c). */
#include "data/pieces/D_003701F0.h"
#include "data/pieces/D_003701E0.h"
#include "data/pieces/D_003701D0.h"
typedef struct {
    s16 x, y, z;
} VtxS16;
typedef struct {
    s16 slot;  /* +0x0 */
    s16 n;     /* +0x2 */
    u16 *map;  /* +0x4 */
} VtxMap;
typedef struct {
    u8 pad[0x10];
    u32 tex;      /* +0x10 */
    VtxS16 *vtx;  /* +0x14 */
    s32 pad18;
    s32 *mdl;     /* +0x1C */
    s32 arg;      /* +0x20 */
} PppMdlRes_8eaa8; /* 0x24 */
typedef struct {
    u8 pad[0x10];
    PppMdlRes_8eaa8 *res; /* +0x10 */
    void *p14;
    VtxMap *maps;   /* +0x18 */
} PppMdlBank_8eaa8;
typedef struct {
    u8 pad[0x80];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem_8eaa8;
typedef struct {
    s32 frame;
    s32 id;         /* +0x4 */
    f32 d0[3];      /* +0x8 */
    s32 u, v;       /* +0x14 */
    u8 page;        /* +0x1C */
    u8 pad1D[3];
    f32 d1[3];      /* +0x20 */
    f32 d2[3];      /* +0x2C */
    u8 b38;         /* +0x38 */
} PppTfdUvKey;
#define D_00615E60 ((PppSystem_8eaa8 *) D_00615E60)
#define D_00615E64 (*(PppMdlBank_8eaa8 *(*)) &D_00615E64)
void pppKeMdlTfdUvDraw(PppObject *obj, PppTfdUvKey *key, PppEntry *e) {
    f32 *w = PPP_WORK(f32, obj, e, 2);
    u32 tex;
    s32 n;
    u8 *p, *q;

    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w[1] += w[2];
        w[5] += w[6];
        w[8] += w[9];
        w[0] += w[1];
        w[4] += w[5];
        w[7] += w[8];
        if (obj->frame == key->frame) {
            w[0] += key->d0[0];
            w[1] += key->d0[1];
            w[2] += key->d0[2];
            w[4] += key->d1[0];
            w[5] += key->d1[1];
            w[6] += key->d1[2];
            w[7] += key->d2[0];
            w[8] += key->d2[1];
            w[9] += key->d2[2];
        }
    }
    if (key->id == 0xFFFF)
        return;
    {
        PppMdlRes_8eaa8 *r = &D_00615E64->res[key->id];
        tex = r->tex;
    }
    n = key->page * 4;
    p = (u8 *) D_00616224 + 16;
    PlatGsSetDefLoadImage(p, ((tex >> 5) & 0x3FFF) + n, 4, (tex >> 19) & 0xF, 0, 0, 16, 16);
    *(u64 *) (p + 0x50) = 0x0800000000008100ULL;
    q = (u8 *) D_00616224;
    func_001a9460(w[0], key->u, key->v, q + 0x70);
    func_001aa6b0((void *) D_00616224, 263, 0, 0);
    D_00616224 = (s32) (q + 0x1070);
    func_001a9790(key->id, PPP_WORK(void, obj, e, 0), n, w[4], w[7], 1, 0);
}
#undef D_00615E60
#undef D_00615E64

/* pppKeMdlTfd2Draw (from hand/nostrict/text_00190000_h63.c). */
void pppKeMdlTfd2Draw(PppObject *obj, PppTfdKey *key, PppEntry *e) {
    PppTfd *w = PPP_WORK(PppTfd, obj, e, 2);
    u32 tex;
    s32 n;
    u8 *p, *q;

    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w->b += w->c;
        w->a += w->b;
        if (obj->frame == key->frame) {
            w->a += key->da;
            w->b += key->db;
            w->c += key->dc;
        }
    }
    if (key->id == 0xFFFF)
        return;
    {
        PppMdlRes *r = &D_00615E64->res[key->id];
        tex = r->tex;
    }
    n = key->page * 4;
    p = (u8 *) D_00616224 + 16;
    PlatGsSetDefLoadImage(p, ((tex >> 5) & 0x3FFF) + n, 4, (tex >> 19) & 0xF, 0, 0, 16, 16);
    *(u64 *) (p + 0x50) = 0x0800000000008100ULL;
    q = (u8 *) D_00616224;
    func_001a9460(w->a, key->u, key->v, q + 0x70);
    func_001aa6b0((void *) D_00616224, 263, 0, 0);
    D_00616224 = (s32) (q + 0x1070);
    func_001a9790(key->id, PPP_WORK(void, obj, e, 0), n, 0, 0, key->mode, 0);
}

/* pppKeMdlTfdUv2Draw (from hand/nostrict/text_00180000_b07.c). */
typedef struct {
    u8 pad[0x10];
    u32 tex;      /* +0x10 */
    VtxS16 *vtx;  /* +0x14 */
    s32 pad18;
    s32 *mdl;     /* +0x1C */
    s32 arg;      /* +0x20 */
} PppMdlRes_8ef98; /* 0x24 */
typedef struct {
    u8 pad[0x10];
    PppMdlRes_8ef98 *res; /* +0x10 */
    void *p14;
    VtxMap *maps;   /* +0x18 */
} PppMdlBank_8ef98;
typedef struct {
    u8 pad[0x80];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem_8ef98;
#define D_00615E60 ((PppSystem_8ef98 *) D_00615E60)
#define D_00615E64 (*(PppMdlBank_8ef98 *(*)) &D_00615E64)
void pppKeMdlTfdUv2Draw(PppObject *obj, PppTfdUvKey *key, PppEntry *e) {
    f32 *w = PPP_WORK(f32, obj, e, 2);
    u32 tex;
    s32 n;
    u8 *p, *q;

    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w[1] += w[2];
        w[5] += w[6];
        w[8] += w[9];
        w[0] += w[1];
        w[4] += w[5];
        w[7] += w[8];
        if (obj->frame == key->frame) {
            w[0] += key->d0[0];
            w[1] += key->d0[1];
            w[2] += key->d0[2];
            w[4] += key->d1[0];
            w[5] += key->d1[1];
            w[6] += key->d1[2];
            w[7] += key->d2[0];
            w[8] += key->d2[1];
            w[9] += key->d2[2];
        }
    }
    if (key->id == 0xFFFF)
        return;
    {
        PppMdlRes_8ef98 *r = &D_00615E64->res[key->id];
        tex = r->tex;
    }
    n = key->page * 4;
    p = (u8 *) D_00616224 + 16;
    PlatGsSetDefLoadImage(p, ((tex >> 5) & 0x3FFF) + n, 4, (tex >> 19) & 0xF, 0, 0, 16, 16);
    *(u64 *) (p + 0x50) = 0x0800000000008100ULL;
    q = (u8 *) D_00616224;
    func_001a9460(w[0], key->u, key->v, q + 0x70);
    func_001aa6b0((void *) D_00616224, 263, 0, 0);
    D_00616224 = (s32) (q + 0x1070);
    func_001a9790(key->id, PPP_WORK(void, obj, e, 0), n, w[4], w[7], key->b38, 0);
}
#undef D_00615E60
#undef D_00615E64

/* pppKeMdlDttDraw (from hand/nostrict/text_00180000_s8_w15.c). */
typedef struct {
    f32 x, y;
    union { f32 z; s32 *p; } u;
} DttW0;
typedef struct {
    u8 pad[8];
    u8 c[4];
} DttW1;
typedef struct {
    s32 unk0;
    s32 id;      /* +0x4 */
    f32 dx, dy, dz; /* +0x8 */
    u8 mode;     /* +0x14 */
    u8 b15;      /* +0x15 */
} DttKey;
typedef struct {
    u8 pad[0x10];
    u8 *tbl;
} DttSys;
typedef struct {
    u8 pad[0x1C];
    struct DttShape *shape;
} DttEnt;
typedef struct DttShape {
    s32 unk0;
    s32 prims;  /* +0x4 */
    s32 verts;  /* +0x8 */
} DttShape;
typedef struct {
    u8 pad0;
    u8 type;    /* +0x1 */
    s16 n;      /* +0x2 */
    u8 pad4[0xC];
} DttGroup;
typedef struct {
    u8 col[12];
    u16 v[3];   /* +0xC */
    u8 pad12[2];
} DttPrim;
typedef struct {
    u64 q0, q1;
    u64 test, test_a;  /* +0x10 */
    u8 pad20[0x10];
    u64 r30, r38;      /* +0x30 */
    u8 pad40[0x10];
    u64 clamp, clamp_a; /* +0x50 */
    s32 v[3][4];       /* +0x60 */
    f32 c[12];         /* +0x90 */
    s32 ox, oy;        /* +0xC0 */
    s32 z;             /* +0xC8 */
    s32 padCC;
    s32 cache;         /* +0xD0 */
} DttBuf;
typedef struct {
    u64 xyoff;          /* +0x0 */
    u64 test;           /* +0x8 */
    void *mtx0;         /* +0x10 */
    void *mtx1;         /* +0x14 */
    u8 *pkt;            /* +0x18 */
    DttShape *shape;    /* +0x1C */
    f32 scale;          /* +0x20 */
    s32 flag;           /* +0x24 */
    u64 scissor;        /* +0x28 */
    f32 *colA;          /* +0x30 */
    f32 *colB;          /* +0x34 */
    s32 cache;          /* +0x38 */
    s32 rd;             /* +0x3C */
    s32 use;            /* +0x40 */
    s16 *verts;         /* +0x44 */
} DttWork;
typedef struct { u8 pad[0xB0]; u64 pad_b0; } DttPad;
extern struct { u8 pad[0x90]; s16 *verts; } *D_00615E68;
extern f32 D_00616040[4][4];
extern s32 D_00616228;
void func_00267560(f32 *, f32 *, f32);
void *func_001aa950(s32);
void func_001aa9d0(s32);
void func_001aa750(u8 *, s32, s32, s32);
#define D_00615E60 (*(DttPad *(*)) &D_00615E60)
#define D_00615E64 ((DttSys *) D_00615E64)
#define D_00616224 ((u8 *) D_00616224)
/* 0018f268 pppKeMdlDttDraw: MATCH (hand/nostrict). From w11's 47w draft: nostrict load/store order is source order (stack stores vs pointer loads alias), so buf->test before buf->test_a, r = w.scissor before buf->clamp_a, flag = w.flag before buf->cache, then-block use, cache, rd, and w.pkt stored after w.colA (pkt's shorter life lets id win v1). */
void pppKeMdlDttDraw(void *obj, DttKey *key, PppEntry *e) {
    DttWork w;
    f32 col[4] __attribute__((aligned(16)));
    DttPad **pp;
    DttW0 *w0;
    void *w2;
    DttW1 *w1;
    DttBuf *buf;
    DttGroup *g;
    DttPrim *pr;
    s16 *verts;
    u8 *pkt;
    s32 use, rd;
    s32 flag;
    s16 n;
    u32 mode;
    u64 r;

    pp = &D_00615E60;
    w2 = (u8 *) obj + e->offsets[2] + 0xA0;
    w0 = (DttW0 *) ((u8 *) obj + e->offsets[0] + 0xA0);
    if (D_0061621C == 0 && !((*pp)->pad_b0 & 0xFF0000FF00ULL)) {
        w0->y += w0->u.z;
        w0->x += w0->y;
        if (*(s32 *) ((u8 *) obj + 0xC) == key->unk0) {
            w0->x += key->dx;
            w0->y += key->dy;
            if (key->mode < 4)
                w0->u.z += key->dz;
        }
    }
    if (key->id == 0xFFFF)
        return;
    w1 = (DttW1 *) ((u8 *) obj + e->offsets[1] + 0xA0);
    if (w1->c[0] == 0)
        return;
    col[0] = w1->c[0];
    col[1] = w1->c[1];
    col[2] = w1->c[2];
    col[3] = w1->c[3];
    func_00267560(col, col, 1.0f / 255.0f);
    mode = key->mode;
    w.mtx0 = D_00616040;
    w.mtx1 = w2;
    w.colA = col;
    w.pkt = D_00616224;
    w.colB = col;
    w.shape = ((DttEnt *) (D_00615E64->tbl + key->id * 36))->shape;
    w.flag = key->b15;
    w.scale = w0->x * D_003701F0[0];
    w.verts = D_00615E68->verts;
    if (mode >= 4 && w0->u.p != 0) {
        w.use = 1;
        w.cache = *w0->u.p;
        w.rd = mode & 8;
    } else {
        w.use = 0;
    }
    {
        u8 m = mode;
        if (m == 0) {
            w.test = 0x2A8021A00ULL;
            w.xyoff = 0x740000007000ULL;
        } else if (m == 1) {
            w.test = 0x2A8020000ULL;
            w.xyoff = 0x720000007000ULL;
        } else {
            w.test = 0x2A8220000ULL;
            w.xyoff = 0x720000007000ULL;
        }
    }
    w.scissor = 0x017F000001FF0000ULL;
    verts = w.verts;
    g = (DttGroup *) ((u8 *) w.shape + w.shape->prims);
    use = w.use;
    rd = w.rd;
    pkt = w.pkt;
    buf = func_001aa950(224);
    if (!verts)
        verts = (s16 *) ((u8 *) w.shape + w.shape->verts);
    buf->q0 = 0xC02DC00000008001ULL;
    buf->q1 = 0x412412412EEEULL;
    buf->test = w.test;
    buf->test_a = 6;
    buf->r30 = 0x44;
    buf->r38 = 0x42;
    r = w.scissor;
    buf->clamp_a = 8;
    buf->clamp = ((r & 0x7ff) << 4) | (((r & 0x7ff00000000ULL) >> 32) << 24) | ((((r & 0x7ff0000) >> 16) - 1) << 14) | 10 | ((((r & 0x7ff000000000000ULL) >> 48) - 1) << 34);
    buf->ox = (w.xyoff & 0xFFFF) - 8;
    buf->oy = ((w.xyoff >> 32) & 0xFFFF) - 8;
    flag = w.flag;
    buf->cache = w.cache;
    {
        register void *m0 asm("$6") = w.mtx0;
        register void *m1 asm("$5") = w.mtx1;
        register f32 *ca asm("$4") = w.colA;
        register f32 *cb asm("$3") = w.colB;
        __asm__ volatile(
        ".set noreorder\n"
        "vsub.xyzw $vf9xyzw, $vf0xyzw, $vf0xyzw\n"
        "lqc2 $vf31, 0($6)\n"
        "vmove.x $vf1x, $vf31x\n"
        "lqc2 $vf31, 16($6)\n"
        "vmove.y $vf1y, $vf31y\n"
        "lqc2 $vf2, 32($6)\n"
        "lqc2 $vf31, 48($6)\n"
        "vmove.zw $vf1zw, $vf31zw\n"
        "lqc2 $vf16, 0($5)\n"
        "lqc2 $vf17, 16($5)\n"
        "lqc2 $vf18, 32($5)\n"
        "lqc2 $vf19, 48($5)\n"
        "lqc2 $vf29, %0\n"
        "vmove.x $vf13x, $vf1x\n"
        "vmove.y $vf13y, $vf1y\n"
        "vmulx.xy $vf13xy, $vf13xy, $vf29x\n"
        "lqc2 $vf5, 0(%5)\n"
        "lqc2 $vf6, 16(%5)\n"
        "lqc2 $vf8, 48(%5)\n"
        "lqc2 $vf10, 80(%5)\n"
        "lui $2, 0x3a80\n"
        "qmtc2 $2, $vf31\n"
        "vaddx.z $vf4z, $vf0z, $vf31x\n"
        "lqc2 $vf12, 192(%5)\n"
        "vitof4.xyzw $vf12xyzw, $vf12xyzw\n"
        "lui $2, 0x4580\n"
        "qmtc2 $2, $vf31\n"
        "vaddx.xy $vf4xy, $vf0xy, $vf31x\n"
        "lqc2 $vf23, 0($4)\n"
        "lqc2 $vf24, 0($3)\n"

        ".set reorder\n"
        : : "m"(w.scale), "r"(m0), "r"(m1), "r"(ca), "r"(cb), "r"(buf) : "$2");
    }
    do {
        pr = (DttPrim *) (g + 1);
        n = g->n;
        if (g->type != 0)
            break;
        g = (DttGroup *) (pr + n);
        for (; n > 0; n--) {
            s32 res;
            s16 *v;
            v = &verts[pr->v[0] * 3];
            buf->v[0][0] = v[0];
            buf->v[0][1] = v[1];
            buf->v[0][2] = v[2];
            v = &verts[pr->v[1] * 3];
            buf->v[1][0] = v[0];
            buf->v[1][1] = v[1];
            buf->v[1][2] = v[2];
            v = &verts[pr->v[2] * 3];
            buf->v[2][0] = v[0];
            buf->v[2][1] = v[1];
            buf->v[2][2] = v[2];
            buf->c[0] = pr->col[0];
            buf->c[1] = pr->col[1];
            buf->c[2] = pr->col[2];
            buf->c[3] = pr->col[3];
            buf->c[4] = pr->col[4];
            buf->c[5] = pr->col[5];
            buf->c[6] = pr->col[6];
            buf->c[7] = pr->col[7];
            buf->c[8] = pr->col[8];
            buf->c[9] = pr->col[9];
            buf->c[10] = pr->col[10];
            buf->c[11] = pr->col[11];
            {
                __asm__ volatile(
        ".set noreorder\n"
        "lqc2 $vf31, 96(%1)\n"
        "vitof0.xyzw $vf31xyzw, $vf31xyzw\n"
        "vaddax.xyzw ACC, $vf19xyzw, $vf0x\n"
        "vmaddax.xyzw ACC, $vf16xyzw, $vf31x\n"
        "vmadday.xyzw ACC, $vf17xyzw, $vf31y\n"
        "vmaddz.xyz $vf22xyz, $vf18xyz, $vf31z\n"
        "vaddax.zw ACC, $vf1zw, $vf0x\n"
        "vmulax.x ACC, $vf1x, $vf22x\n"
        "vmulay.y ACC, $vf1y, $vf22y\n"
        "vmaddz.xyzw $vf11xyzw, $vf2xyzw, $vf22z\n"
        "vdiv Q, $vf0w, $vf11w\n"
        "vwaitq \n"
        "vaddq.w $vf22w, $vf1w, Q\n"
        "vmulq.xyz $vf11xyz, $vf11xyz, Q\n"
        "ctc2 $0, $vi16\n"
        "vsub.w $vf0w, $vf11w, $vf0w\n"
        "vsub.xy $vf0xy, $vf11xy, $vf0xy\n"
        "vsub.xy $vf0xy, $vf4xy, $vf11xy\n"
        "vnop \n"
        "vnop \n"
        "vnop \n"
        "vnop \n"
        "vnop \n"
        "cfc2 $2, $vi16\n"
        "andi %0, $2, 0xc0\n"
        "bnez %0, .Lw14d_0018FB5C\n"
        "vnop \n"
        "lqc2 $vf31, 112(%1)\n"
        "vitof0.xyzw $vf31xyzw, $vf31xyzw\n"
        "vaddax.xyzw ACC, $vf19xyzw, $vf0x\n"
        "vmaddax.xyzw ACC, $vf16xyzw, $vf31x\n"
        "vmadday.xyzw ACC, $vf17xyzw, $vf31y\n"
        "vmaddz.xyz $vf21xyz, $vf18xyz, $vf31z\n"
        "vaddax.zw ACC, $vf1zw, $vf0x\n"
        "vmulax.x ACC, $vf1x, $vf21x\n"
        "vmulay.y ACC, $vf1y, $vf21y\n"
        "vmaddz.xyzw $vf25xyzw, $vf2xyzw, $vf21z\n"
        "vdiv Q, $vf0w, $vf25w\n"
        "vwaitq \n"
        "vaddq.w $vf21w, $vf1w, Q\n"
        "vmulq.xyz $vf25xyz, $vf25xyz, Q\n"
        "ctc2 $0, $vi16\n"
        "vsub.w $vf0w, $vf25w, $vf0w\n"
        "vsub.xy $vf0xy, $vf25xy, $vf0xy\n"
        "vsub.xy $vf0xy, $vf4xy, $vf25xy\n"
        "vnop \n"
        "vnop \n"
        "vnop \n"
        "vnop \n"
        "vnop \n"
        "cfc2 $2, $vi16\n"
        "andi %0, $2, 0xc0\n"
        "bnez %0, .Lw14d_0018FB5C\n"
        "vnop \n"
        "lqc2 $vf31, 128(%1)\n"
        "vitof0.xyzw $vf31xyzw, $vf31xyzw\n"
        "vaddax.xyzw ACC, $vf19xyzw, $vf0x\n"
        "vmaddax.xyzw ACC, $vf16xyzw, $vf31x\n"
        "vmadday.xyzw ACC, $vf17xyzw, $vf31y\n"
        "vmaddz.xyz $vf20xyz, $vf18xyz, $vf31z\n"
        "vaddax.zw ACC, $vf1zw, $vf0x\n"
        "vmulax.x ACC, $vf1x, $vf20x\n"
        "vmulay.y ACC, $vf1y, $vf20y\n"
        "vmaddz.xyzw $vf26xyzw, $vf2xyzw, $vf20z\n"
        "vdiv Q, $vf0w, $vf26w\n"
        "vwaitq \n"
        "vaddq.w $vf20w, $vf1w, Q\n"
        "vmulq.xyz $vf26xyz, $vf26xyz, Q\n"
        "ctc2 $0, $vi16\n"
        "vsub.w $vf0w, $vf26w, $vf0w\n"
        "vsub.xy $vf0xy, $vf26xy, $vf0xy\n"
        "vsub.xy $vf0xy, $vf4xy, $vf26xy\n"
        "vnop \n"
        "vnop \n"
        "vnop \n"
        "vnop \n"
        "vnop \n"
        "cfc2 $2, $vi16\n"
        "andi %0, $2, 0xc0\n"
        "bnez %0, .Lw14d_0018FB5C\n"
        "vnop \n"
        "sqc2 $vf5, 16(%5)\n"
        "sqc2 $vf6, 32(%5)\n"
        "sqc2 $vf8, 48(%5)\n"
        "sqc2 $vf10, 64(%5)\n"
        "lqc2 $vf3, 144(%1)\n"
        "vmul.xyzw $vf3xyzw, $vf3xyzw, $vf23xyzw\n"
        "vftoi0.xyzw $vf3xyzw, $vf3xyzw\n"
        "sqc2 $vf3, 96(%5)\n"
        "vsub.xyz $vf28xyz, $vf22xyz, $vf19xyz\n"
        "vmul.xyz $vf31xyz, $vf28xyz, $vf28xyz\n"
        "vaddy.x $vf31x, $vf31x, $vf31y\n"
        "vaddz.x $vf31x, $vf31x, $vf31z\n"
        "vsqrt Q, $vf31x\n"
        "vaddz.x $vf14x, $vf0x, $vf11z\n"
        "vftoi4.xyz $vf9xyz, $vf11xyz\n"
        "sqc2 $vf9, 112(%5)\n"
        "vaddw.z $vf15z, $vf0z, $vf0w\n"
        "vwaitq \n"
        "vaddq.z $vf12z, $vf0z, Q\n"
        "vdiv Q, $vf0w, $vf12z\n"
        "vwaitq \n"
        "vmulq.xyz $vf31xyz, $vf28xyz, Q\n"
        "beqz %6, .Lw14d_0018F9E0\n"
        "nop \n"
        "vmulz.xy $vf31xy, $vf31xy, $vf31z\n"
        ".Lw14d_0018F9E0:\n"
        "vmul.xy $vf31xy, $vf31xy, $vf13xy\n"
        "vmulw.xyz $vf31xyz, $vf31xyz, $vf22w\n"
        "vadd.xy $vf31xy, $vf31xy, $vf11xy\n"
        "vsub.xy $vf31xy, $vf31xy, $vf12xy\n"
        "vmulz.xy $vf15xy, $vf31xy, $vf4z\n"
        "beqz %3, .Lw14d_0018FA14\n"
        "nop \n"
        "beqz %4, .Lw14d_0018FA10\n"
        "nop \n"
        "lqc2 $vf15, 0(%2)\n"
        "j .Lw14d_0018FA14\n"
        "nop \n"
        ".Lw14d_0018FA10:\n"
        "sqc2 $vf15, 0(%2)\n"
        ".Lw14d_0018FA14:\n"
        "vaddw.z $vf15z, $vf0z, $vf22w\n"
        "vmulz.xy $vf15xy, $vf15xy, $vf15z\n"
        "sqc2 $vf15, 80(%5)\n"
        "lqc2 $vf30, 160(%1)\n"
        "vmul.xyzw $vf30xyzw, $vf30xyzw, $vf23xyzw\n"
        "vftoi0.xyzw $vf30xyzw, $vf30xyzw\n"
        "sqc2 $vf30, 144(%5)\n"
        "vsub.xyz $vf28xyz, $vf21xyz, $vf19xyz\n"
        "vmul.xyz $vf31xyz, $vf28xyz, $vf28xyz\n"
        "vaddy.x $vf31x, $vf31x, $vf31y\n"
        "vaddz.x $vf31x, $vf31x, $vf31z\n"
        "vsqrt Q, $vf31x\n"
        "vaddz.y $vf14y, $vf0y, $vf25z\n"
        "vftoi4.xyz $vf9xyz, $vf25xyz\n"
        "sqc2 $vf9, 160(%5)\n"
        "vaddw.z $vf15z, $vf0z, $vf0w\n"
        "vwaitq \n"
        "vaddq.z $vf12z, $vf0z, Q\n"
        "vdiv Q, $vf0w, $vf12z\n"
        "vwaitq \n"
        "vmulq.xyz $vf31xyz, $vf28xyz, Q\n"
        "beqz %6, .Lw14d_0018FA74\n"
        "nop \n"
        "vmulz.xy $vf31xy, $vf31xy, $vf31z\n"
        ".Lw14d_0018FA74:\n"
        "vmul.xy $vf31xy, $vf31xy, $vf13xy\n"
        "vmulw.xyz $vf31xyz, $vf31xyz, $vf21w\n"
        "vadd.xy $vf31xy, $vf31xy, $vf25xy\n"
        "vsub.xy $vf31xy, $vf31xy, $vf12xy\n"
        "vmulz.xy $vf15xy, $vf31xy, $vf4z\n"
        "beqz %3, .Lw14d_0018FAA8\n"
        "nop \n"
        "beqz %4, .Lw14d_0018FAA4\n"
        "nop \n"
        "lqc2 $vf15, 16(%2)\n"
        "j .Lw14d_0018FAA8\n"
        "nop \n"
        ".Lw14d_0018FAA4:\n"
        "sqc2 $vf15, 16(%2)\n"
        ".Lw14d_0018FAA8:\n"
        "vaddw.z $vf15z, $vf0z, $vf21w\n"
        "vmulz.xy $vf15xy, $vf15xy, $vf15z\n"
        "sqc2 $vf15, 128(%5)\n"
        "lqc2 $vf30, 176(%1)\n"
        "vmul.xyzw $vf30xyzw, $vf30xyzw, $vf23xyzw\n"
        "vftoi0.xyzw $vf30xyzw, $vf30xyzw\n"
        "sqc2 $vf30, 192(%5)\n"
        "vsub.xyz $vf28xyz, $vf20xyz, $vf19xyz\n"
        "vmul.xyz $vf31xyz, $vf28xyz, $vf28xyz\n"
        "vaddy.x $vf31x, $vf31x, $vf31y\n"
        "vaddz.x $vf31x, $vf31x, $vf31z\n"
        "vsqrt Q, $vf31x\n"
        "vaddz.z $vf14z, $vf0z, $vf26z\n"
        "vftoi4.xyz $vf9xyz, $vf26xyz\n"
        "sqc2 $vf9, 208(%5)\n"
        "vaddw.z $vf15z, $vf0z, $vf0w\n"
        "vwaitq \n"
        "vaddq.z $vf12z, $vf0z, Q\n"
        "vdiv Q, $vf0w, $vf12z\n"
        "vwaitq \n"
        "vmulq.xyz $vf31xyz, $vf28xyz, Q\n"
        "beqz %6, .Lw14d_0018FB08\n"
        "nop \n"
        "vmulz.xy $vf31xy, $vf31xy, $vf31z\n"
        ".Lw14d_0018FB08:\n"
        "vmul.xy $vf31xy, $vf31xy, $vf13xy\n"
        "vmulw.xyz $vf31xyz, $vf31xyz, $vf20w\n"
        "vadd.xy $vf31xy, $vf31xy, $vf26xy\n"
        "vsub.xy $vf31xy, $vf31xy, $vf12xy\n"
        "vmulz.xy $vf15xy, $vf31xy, $vf4z\n"
        "beqz %3, .Lw14d_0018FB3C\n"
        "nop \n"
        "beqz %4, .Lw14d_0018FB38\n"
        "nop \n"
        "lqc2 $vf15, 32(%2)\n"
        "j .Lw14d_0018FB3C\n"
        "nop \n"
        ".Lw14d_0018FB38:\n"
        "sqc2 $vf15, 32(%2)\n"
        ".Lw14d_0018FB3C:\n"
        "vaddw.z $vf15z, $vf0z, $vf20w\n"
        "vmulz.xy $vf15xy, $vf15xy, $vf15z\n"
        "sqc2 $vf15, 176(%5)\n"
        "vminix.y $vf31y, $vf14y, $vf14x\n"
        "vminiy.z $vf31z, $vf14z, $vf31y\n"
        "vftoi4.xyzw $vf31xyzw, $vf31xyzw\n"
        "sqc2 $vf31, 192(%1)\n"
        "add %0, $0, $0\n"
        ".Lw14d_0018FB5C:\n"

        ".set reorder\n"
                : "=&r"(res) : "r"(buf), "r"(buf->cache), "r"(use), "r"(rd), "r"(pkt), "r"(flag) : "$2", "memory");
            }
            if (res == 0) {
                func_001aa750(pkt, 14, buf->z / 0x3000, 0);
                pkt += 224;
            }
            pr++;
            buf->cache += 48;
        }
    } while ((s8) g->type != -1);
    w.pkt = pkt;
    w.cache = buf->cache;
    func_001aa9d0(224);
    D_00616228 += w.pkt - D_00616224;
    D_00616224 = w.pkt;
    if (key->mode >= 4 && w0->u.p != 0)
        *w0->u.p = w.cache;
}
#undef D_00615E60
#undef D_00615E64
#undef D_00616224

