#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

/* shared ppp system globals */
typedef struct { s16 off; s16 dur; s32 pad; } FdFrame;
typedef struct { u8 pad0[0x10]; FdFrame f[1]; } FdShape;
typedef struct { FdShape *shape; s32 unk4; } FdShapeEnt;
typedef struct { u32 flags; u8 pad04[0x12]; u16 unk16; } MfMdl;
typedef struct { s32 pad0[7]; MfMdl *mdl; s32 unk20; } MfSlot;
typedef struct { u8 pad00[0x10]; MfSlot *slots; FdShapeEnt *shapes; } PppSys9;
extern PppSys9 *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
extern volatile s32 D_00616224;

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
s32 func_001a2218(PppA2218A *p, PppA2218B *q);
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

typedef struct { u8 pad[0x10]; PppMtx m; PppMtx m2; s32 unk90; s32 unk94; } MfMtxOwner;
extern MfMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
extern u8 D_00616240[];

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
} MfParam;

typedef struct { u8 pad[8]; u8 r, g, b, a; } MfCol;
typedef struct { f32 f[4]; u8 pad[0x10]; } MfSub;
typedef struct {
    u8 pad0[0x20];
    u16 alive;
    s8 c[4];
    u8 pad26[0x7c - 0x26];
    f32 u, v;
    u8 pad84[0x94 - 0x84];
    f32 alpha;
    u64 flags;
} MfPart;
typedef struct { MfPart *parts; MfSub *subs; s32 n; f32 alpha; u16 timer; u8 active; } MfWork;
typedef struct { u8 pad0[4]; s32 id; u8 x08; u8 pad09[0xc7]; f32 dist; f32 fade; } MfKey;

s32 func_001a36f0(MfWork *w, MfKey *k);
void func_001a4a90(PppMtx m, MfKey *k, MfWork *w);
f32 func_001a4a98(PppMtx m0, PppMtx m1, MfKey *k, MfWork *w, MfPart *p);
s32 func_001aaf88(MfMdl *, MfParam *, s32);

void pppRyjMegaBirthModelFilterDraw(void *obj, MfKey *k, PppEntry *e) {
    PppMtx m0;
    PppMtx m1;
    MfParam p;
    MfWork *w = PPP_WORK(MfWork, obj, e, 2);
    MfCol *c = PPP_WORK(MfCol, obj, e, 1);
    MfPart *pt = w->parts;
    MfSub *sb = w->subs;
    s32 n = w->n;
    MfSlot *s;
    MfMdl *mdl;
    s32 cr, cg, cb, ca;
    s32 i;
    s32 id;
    u8 f8;

    if (!func_001a36f0(w, k))
        return;
    if (!w->active)
        return;
    id = k->id;
    if (id == 0xFFFF)
        return;
    func_001a4a90(m0, k, w);
    s = &D_00615E64->slots[id];
    mdl = s->mdl;
    p.p44 = 0;
    p.p2C = 0;
    p.p28 = 0;
    f8 = k->x08;
    p.p24 = 0;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = D_00615E68->unk90;
    p.w3C = D_00615E68->unk94;
    p.p20 = m1;
    p.w0C = 0;
    p.t10.d = 0;
    p.p04 = D_00616240;
    p.flags = 4;
    p.w40 = 0;
    if (f8) p.flags = 0x204;
    p.b4D = 1;
    cr = c->r;
    cg = c->g;
    p.h08 = mdl->unk16;
    cb = c->b;
    ca = c->a;
    for (i = 0; i < n; i++) {
        if (pt->alive && !(pt->flags & 0x100)) {
            f32 d, dist, fade;
            s32 r, g, bl, al;
            d = func_001a4a98(m0, m1, k, w, pt);
            dist = k->dist;
            fade = k->fade;
            if (d < dist - fade) {
                pt->alpha = 0.0f;
            } else if (d < dist) {
                pt->alpha *= 1.0f - (dist - d) / fade;
            }
            r = cr + pt->c[0];
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
            p.t10.s.u = pt->u * 65536.0f;
            p.t10.s.v = pt->v * 65536.0f;
            if (p.a) {
                p.w34 = D_00616224;
                D_00616224 = func_001aaf88(mdl, &p, s->unk20);
            }
        }
        if (sb)
            sb++;
        pt++;
    }
}
