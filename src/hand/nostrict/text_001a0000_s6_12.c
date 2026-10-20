#include "common.h"
typedef struct {
    u8 pad[0x80];
    void *slots;
    u8 pad84[0x2C];
    u64 flags;
} PppSystem;
extern s32 D_0061621C;
extern PppSystem *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */
typedef struct {
    s16 off;
    s16 dur;
    s8 flags;
    u8 pad5[3];
} PppShapeFrame;
typedef struct {
    u8 pad0[6];
    s16 n;
    u8 pad8[8];
    PppShapeFrame f[1];
} PppShape;
typedef struct {
    PppShape *shape;
    s32 unk4;
} PppShapeEnt;
typedef struct {
    u8 pad00[0x14];
    PppShapeEnt *shapes;
} DSysS;
extern DSysS *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
typedef struct {
    f32 pos[4];
    f32 vel[4];
    u16 time;
    u16 cur;
    u16 prev;
    u16 live;
    u8 pad28[0x38];
} Part;
typedef struct {
    Part *parts;
    f32 *b;
    s32 n;
    s32 pad;
    u16 timer;
} PObj;
typedef struct {
    s32 unk0;
    s32 id;
    u16 speed;
    u8 pada[6];
    u16 max;
    u16 interval;
} PKey;
void func_001a2830(PObj *, PKey *, Part *, s32, f32 *);
void func_001a26f0(PObj *, PKey *, Part *, f32 *);
void func_002672f8(void *, void *, void *);
/* ---- func_001a26f0 ---- */
void *memset(void *, s32, u32);
f32 func_001a2178(void);
void func_002673b8(void *, void *);
void func_001a2248(void *, void *, void *);
extern u8 D_00615F30[];
typedef struct { f32 x, y, z, w; } V4_1a26f0;
typedef struct { u8 pad[124]; f32 p[3]; u8 pad2[20]; f32 r0, r1; } Emit_1a26f0;

static inline f32 vlen3_1a26f0(V4_1a26f0 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vmul.xyz $vf10xyz, $vf10xyz, $vf10xyz\n"
        "vaddx.y $vf10y, $vf10y, $vf10x\n"
        "vaddy.z $vf10z, $vf10z, $vf10y\n"
        "vsqrt Q, $vf10z\n"
        "vwaitq\n"
        "vaddq.x $vf10x, $vf0x, Q\n"
        "qmfc2 $2, $vf10\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(v) : "$2", "memory");
    return r;
}

CONTEXT_ONLY void func_001a26f0(PObj *a0, PKey *e0, Part *m0, f32 *b) {
    Emit_1a26f0 *e = (Emit_1a26f0 *)e0;
    V4_1a26f0 *m = (V4_1a26f0 *)m0;
    V4_1a26f0 t;
    f32 r, d;
    memset(m, 0, 96);
    if (b) memset(b, 0, 32);
    t.x = e->p[0];
    t.y = e->p[1];
    t.z = e->p[2];
    t.w = 1.0f;
    func_002673b8(m + 1, &t);
    r = e->r0 + e->r1;
    d = r + r;
    do {
        m->x = d * func_001a2178() - r;
        m->y = d * func_001a2178() - r;
        m->z = d * func_001a2178() - r;
    } while (r < vlen3_1a26f0(m));
    m->w = 1.0f;
    func_002672f8(m, D_00615F30, m);
    func_001a2248(e, m, b);
}


void func_001a2d40(PObj *o, PKey *k, s32 a2) {
    Part *p = o->parts;
    f32 *b = o->b;
    s32 n = o->n;
    s32 cnt = 0;
    s32 i;
    PppShape *sh;
    PppShapeFrame *fr;
    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    if (k->id == 0xFFFF)
        return;
    o->timer++;
    for (i = 0; i < n; i++, p++) {
        if (p->live) {
            func_001a2830(o, k, p, a2, b);
            {
            PppShapeEnt *se = &D_00615E64->shapes[k->id];
            sh = se->shape;
            }
            fr = &sh->f[p->prev];
            p->prev = p->cur;
            p->time += k->speed;
            if (p->time >= fr->dur) {
                p->time -= fr->dur;
                p->cur++;
                if (p->cur >= sh->n) {
                    if (fr->flags & 0x80) {
                        p->cur = 0;
                        p->time = 0;
                    } else {
                        p->time = 0;
                        p->cur--;
                    }
                }
            }
        } else if (k->interval <= o->timer && cnt < k->max) {
            func_001a26f0(o, k, p, b);
            cnt++;
        }
        if (b) b += 8;
    }
    if (cnt > 0) o->timer = 0;
}


typedef struct {
    u16 unk0;
    u16 flags;
    u8 r, g, b, a;
    s32 w8;
    s16 hC;
    s16 pad;
    s32 w10;
    s32 w14;
    u8 b18;
} P5740;
typedef struct {
    s16 pad[8];
    s16 off;
} E5740;
typedef struct {
    u8 **base;
    u8 *hdr;
    u8 pad8[8];
    P5740 p;
} S5740;
extern s32 D_00616224;
s32 func_001b8198(void *, P5740 *, s32);
void func_001a5740(S5740 *s) {
    u8 **b = s->base;
    E5740 *e;
    e = (E5740 *)(*b + s->hdr[2] * 8);
    s->p.w8 = 0;
    s->p.b18 = 0;
    s->p.w14 = D_00616224;
    s->p.flags |= 0x30;
    s->p.hC = 18;
    D_00616224 = func_001b8198(*b + e->off, &s->p, 0);
}
