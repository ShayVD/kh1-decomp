/* The pppRyjMegaBirthFilter class, -fno-strict-aliasing (docs/modules.md
 * "Session 49"; s6_12 nostrict renamed): func_001a2d40 runs the particles
 * (moves the live ones with ryjmbfilter.nostrict_nofill.c's func_001a2830,
 * starts new ones with ryjmbfilter.c's func_001a26f0, a CONTEXT_ONLY copy
 * here); the frame (pppRyjMegaBirthFilterFrame) allocates the particles and
 * fades the emitter by its distance from the camera; the draw
 * (pppRyjMegaBirthFilterDraw) draws each live particle's shape frame through
 * the VU0 routine func_001b8198.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "ppp.h"
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
/* ---- func_001a26f0 ---- */
void *memset(void *, s32, u32);
f32 func_001a2178(void);
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
    PlatVu0Normalize(m + 1, &t);
    r = e->r0 + e->r1;
    d = r + r;
    do {
        m->x = d * func_001a2178() - r;
        m->y = d * func_001a2178() - r;
        m->z = d * func_001a2178() - r;
    } while (r < vlen3_1a26f0(m));
    m->w = 1.0f;
    PlatVu0ApplyMatrix(m, D_00615F30, m);
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

/* The frame (from text_001a0000_h65.c). */
void *func_0017f958(void *, s32);
#include "data/pieces/D_003701D0.h"
typedef FV4_3701d0 FV4;

extern FV4 D_00615F70; /* src/data/bss_0061.c: f32 D_00615F70[4] */

typedef struct { u8 pad0[0x20]; u16 t; u16 idx; u16 prev; u16 alive; u8 pad28[0x38]; } MbPart;
typedef struct { u8 pad[0x20]; } MbSub;
typedef struct { MbPart *parts; MbSub *subs; s32 n; f32 alpha; u16 timer; u8 active; } MbWork;
typedef struct { u8 pad0[0xe]; u16 n; u8 pad10[0xac - 0x10]; f32 dist; f32 fade; u8 test; u8 padb5; u8 sub; } MbfKey;

s32 func_001a2218();

static inline f32 vlen3_w65(FV4 *v) {
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

void pppRyjMegaBirthFilterFrame(void *obj, MbfKey *k, PppEntry *e) {
    MbWork *w = (MbWork *)((u8 *)obj + e->offsets[2] + 0xA0);
    void *w2 = (u8 *)obj + e->offsets[1] + 0xA0;
    FV4 d;
    f32 len, r;

    if (w->parts == NULL) {
        w->n = k->n;
        w->parts = func_0017f958(D_00615E64, w->n * 0x60);
        if (w->parts != NULL)
            memset(w->parts, 0, w->n * 0x60);
        if (k->sub) {
            w->subs = func_0017f958(D_00615E64, w->n << 5);
            if (w->subs != NULL)
                memset(w->subs, 0, w->n << 5);
        }
    }
    if (!func_001a2218(w, k))
        return;
    if (k->test) {
        PlatVu0SubVector(&d, &D_00615F70, &D_003701D0);
        len = vlen3_w65(&d);
        if (k->dist < len) {
            w->active = 0;
        } else {
            w->active = 1;
            r = k->dist - len;
            if (r < k->fade)
                w->alpha = r / k->fade;
            else
                w->alpha = 1.0f;
        }
    }
    if (w->active)
        func_001a2d40((PObj *)w, (PKey *)k, (s32)w2);
}


/* The draw (from text_001a0000_b09.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

/* shared ppp system globals */
typedef struct { s16 off; s16 dur; s32 pad; } FdFrame;
typedef struct { u8 pad0[0x10]; FdFrame f[1]; } FdShape;
typedef struct { FdShape *shape; s32 unk4; } FdShapeEnt;
typedef struct { u32 flags; u8 pad04[0x12]; u16 unk16; } MfMdl;
typedef struct { s32 pad0[7]; MfMdl *mdl; s32 unk20; } MfSlot;
typedef struct { u8 pad00[0x10]; MfSlot *slots; FdShapeEnt *shapes; } PppSys9;
#define D_00615E64 (*(PppSys9 **)&D_00615E64)
extern s32 D_00616224;
#define D_00616224 (*(volatile s32 *)&D_00616224)

typedef struct {
    u16 unk0;
    u16 flags;
    u8 r, g, b, a;
    u64 d8;
    void *p10;
    s32 w14;
    u8 b18;
    void *p1C;
    u8 pad20[0x10];
} FdParam;

typedef struct { u8 pad[8]; u8 r, g, b, a; } FdCol;
typedef struct { f32 f[4]; u8 pad[0x10]; } FdSub;
typedef struct {
    u8 pad0[0x24];
    u16 idx;
    u16 alive;
    s8 c[4];
    u8 pad2c[0x28];
    f32 alpha;
    u8 pad58[0];
    u64 flags;
} FdPart;
typedef struct { FdPart *parts; FdSub *subs; s32 n; f32 alpha; u16 timer; u8 active; } FdWork;
typedef struct { u8 pad0[4]; s32 id; u8 pad8[4]; u8 x0c; u8 pad0d[0x87]; f32 dist; f32 fade; } FdKey;

typedef struct { s32 unk0; s32 unk4; } PppA2218A;
typedef struct { u8 pad[0xB6]; u8 unkB6; } PppA2218B;
typedef struct { u8 pad[44]; f32 rot; u8 pad2[8]; f32 sx, sy; } Spr;
typedef struct { u8 pad[164]; f32 sc, of; } Cam;
void func_001a30d0(void);
f32 func_001a30d8(s32 a0, f32 (*m)[4], Cam *c, s32 a3, Spr *s);
s32 func_001b8198(void *, FdParam *, s32);

void pppRyjMegaBirthFilterDraw(void *obj, FdKey *k, PppEntry *e) {
    PppMtx m0;
    PppMtx m1;
    FdParam p;
    FdWork *w = PPP_WORK(FdWork, obj, e, 2);
    FdCol *c = PPP_WORK(FdCol, obj, e, 1);
    FdPart *pt = w->parts;
    FdSub *sb = w->subs;
    s32 n = w->n;
    FdShapeEnt *s;
    FdShape *sh;
    s32 cr, cg, cb, ca;
    s32 i;
    s32 id;

    if (!func_001a2218((PppA2218A *)w, (PppA2218B *)k))
        return;
    if (!w->active)
        return;
    id = k->id;
    if (id == 0xFFFF)
        return;
    ((void (*)(PppMtx, FdKey *, FdWork *))func_001a30d0)(m0, k, w);
/*P*/
    s = &D_00615E64->shapes[id];
    p.flags = 0x10;
    if (k->x0c) p.flags = 0x810;
    p.p1C = 0;
    p.d8 = 0;
    p.b18 = 0;
    p.p10 = m1;
    sh = s->shape;
    cr = c->r;
    cg = c->g;
    cb = c->b;
    ca = c->a;
/*Q*/
    for (i = 0; i < n; i++) {
        if (pt->alive && !(pt->flags & 0x100)) {
            f32 d, dist, fade;
            s32 r, g, bl, al;
            u8 *src;
            d = func_001a30d8((s32)m0, m1, (Cam *)k, (s32)w, (Spr *)pt);
            dist = k->dist;
            fade = k->fade;
            if (d < dist - fade) {
                pt->alpha = 0.0f;
            } else if (d < dist) {
                pt->alpha *= 1.0f - (dist - d) / fade;
            }
            r = cr + pt->c[0];
            { FdFrame *f = &sh->f[pt->idx]; src = (u8 *)sh + f->off; }
            g = cg + pt->c[1];
            bl = cb + pt->c[2];
            al = ca + pt->c[3];
            if (sb) {
                r += (s32)sb->f[0];
                g += (s32)sb->f[1];
                bl += (s32)sb->f[2];
                al += (s32)sb->f[3];
            }
            if (r < 0) r = 0; else if (r >= 256) r = 255;
            if (g < 0) g = 0; else if (g >= 256) g = 255;
            if (bl < 0) bl = 0; else if (bl >= 256) bl = 255;
            if (al < 0) al = 0; else if (al >= 128) al = 127;
            p.a = al;
            p.r = r;
            p.g = g;
            p.b = bl;
            p.a = p.a * pt->alpha * w->alpha;
            if (p.a) {
                p.w14 = D_00616224;
                D_00616224 = func_001b8198(src, &p, s->unk4);
            }
        }
        if (sb)
            sb++;
        pt++;
    }
}

#undef D_00615E64
#undef D_00616224
