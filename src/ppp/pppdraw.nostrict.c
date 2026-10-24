/* The basic ppp draw classes, -fno-strict-aliasing (docs/modules.md
 * "Session 50"): pppDrawMdlBS / DrawMdlSemi / DrawMdlTs draw a model with
 * the owner's matrix through opdma.c's func_001aaf88 (Semi translucent, Ts
 * with the work area's UV scroll, stepped in its frame); pppDrawShape steps
 * a shape animation's frames and draws the current one with func_001b8198.
 * Read from the code, not proved by a boot. */
#include "ppp.h"
#include "data/bss_0061.h"
#include "data/types/nostrict_text_00180000_h39.h"
#include "data/pieces/D_00362730.h"
#include "data/pieces/D_003701F0.h"
#include "data/pieces/D_00364130.h"
#include "common.h"

/* pppDrawMdlBSDraw (from hand/nostrict/text_00180000_h62.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;
typedef struct {
    s16 x, y, z;
} VtxS16;
typedef struct {
    s16 slot;  /* +0x0 */
    s16 n;     /* +0x2 */
    u16 *map;  /* +0x4 */
} VtxMap;
typedef struct {
    u32 flags;  /* +0x0 */
    u8 pad04[0x12];
    u16 unk16;  /* +0x16 */
} DMdl;
typedef struct {
    s32 n;       /* +0x0 */
    s32 pad04[4];
    VtxS16 *vtx; /* +0x14 */
    s32 pad18;
    DMdl *mdl;   /* +0x1C */
    s32 unk20;   /* +0x20 */
} VtxSlot;
typedef struct {
    u8 pad00[0x10];
    VtxSlot *slots; /* +0x10 */
    void *p14;
    VtxMap *maps;   /* +0x18 */
} VtxSys;
typedef struct {
    u8 pad00[0x10];
    u8 m10[0x40];   /* +0x10 */
    u8 m50[0x40];   /* +0x50 */
    VtxS16 *vtx;    /* +0x90 */
    s32 unk94;      /* +0x94 */
} VtxCur;
extern VtxSys *D_00615E64;
extern VtxCur *D_00615E68;
typedef struct {
    s32 flags;  /* +0x00 */
    void *p04;  /* +0x04 */
    u16 h08;    /* +0x08 */
    u8 b0A;     /* +0x0A */
    s32 w0C;    /* +0x0C */
    union {
        u64 d;
        s32 w[2];
    } d10;      /* +0x10 */
    u8 r, g, b, a; /* +0x18 */
    s32 w1C;    /* +0x1C */
    void *p20;  /* +0x20 */
    void *p24;  /* +0x24 */
    void *p28;  /* +0x28 */
    void *p2C;  /* +0x2C */
    s32 w30;    /* +0x30 */
    s32 w34;    /* +0x34 */
    s32 w38;    /* +0x38 */
    s32 w3C;    /* +0x3C */
    s32 w40;    /* +0x40 */
    s32 w44;    /* +0x44 */
    s32 w48;    /* +0x48 */
    u8 b4C;     /* +0x4C */
    u8 b4D;     /* +0x4D */
    u8 pad4E[0x12];
} DParam;
typedef struct {
    s32 frame;
    s32 slot; /* +0x4 */
    u16 h8;   /* +0x8 */
} DKey;
typedef struct {
    u8 pad[8];
    u8 r, g, b, a; /* +0x8 */
} DBSWork;
extern s32 D_00616224;
s32 func_001aaf88(DMdl *, DParam *, s32);
void pppDrawMdlBSDraw(PppObject *obj, DKey *key, PppEntry *e) {
    DParam p;
    DBSWork *w;
    VtxSlot *s;
    DMdl *m;
    VtxCur *cur;
    u8 r, g, b;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DBSWork, obj, e, 0);
    p.a = w->a;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    if (m->flags & 1)
        p.flags = 128;
    else
        p.flags = 12;
    if (!(m->flags & 2))
        p.flags |= 16;
/*P*/
    r = w->r;
    p.h08 = m->unk16;
    cur = D_00615E68;
    g = w->g;
    b = w->b;
    p.b0A = 0;
    p.w1C = 0;
    p.w38 = (s32) cur->vtx;
    p.w3C = cur->unk94;
    p.p04 = D_00616240;
    p.w0C = 0;
    p.r = r;
    p.g = g;
    p.b = b;
    p.d10.d = 0;
    p.w40 = 0;
    p.p20 = cur->m50;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.p2C = cur->m10;
    p.w34 = D_00616224;
    p.w44 = 0;
    p.b4C = 0;
    p.b4D = 0;
/*Q*/
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

/* pppDrawMdlSemiDraw (from hand/nostrict/text_00180000_h62.c). */
typedef struct {
    u16 r, g, b;
    s16 a;
} DSemiWork;
void pppDrawMdlSemiDraw(PppObject *obj, DKey *key, PppEntry *e) {
    DParam p;
    DSemiWork *w;
    VtxSlot *s;
    DMdl *m;
    VtxCur *cur;
    u16 r, g, b;
    u16 h;

    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DSemiWork, obj, e, 0);
    p.a = w->a >> 7;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    p.flags = 128;
    if (!(m->flags & 2))
        p.flags = 144;
    h = key->h8;
    p.b0A = 0;
    p.w1C = 0;
    cur = D_00615E68;
    r = w->r;
    g = w->g;
    b = w->b;
    p.h08 = h;
    p.w38 = (s32) cur->vtx;
    p.w3C = cur->unk94;
    p.p04 = D_00616240;
    p.r = r >> 7;
    p.g = g >> 7;
    p.b = b >> 7;
    p.p20 = cur->m50;
    p.p24 = D_00616140;
    p.w0C = 0;
    p.d10.d = 0;
    p.w40 = 0;
    p.w44 = 0;
    p.p28 = D_00616100;
    p.w34 = D_00616224;
    p.p2C = cur->m10;
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

/* pppDrawMdlTsFrame (from hand/nostrict/text_00180000_h39.c). */
typedef struct {
    u8 pad00[0x20];
    s32 dataoff;  /* +0x20 */
    s16 prio;     /* +0x24 */
    s16 n;        /* +0x26 */
    PppEntry ent[1]; /* +0x28 */
} H39Prog;
struct H39Inst;
typedef struct {
    H39Prog *prog;          /* +0x0 */
    struct H39Inst *last;   /* +0x4 */
    s32 time;               /* +0x8 */
    u16 count;              /* +0xC */
} H39Slot2;
typedef struct H39Inst {
    struct H39Inst *next;   /* +0x0 */
    s32 unk04;
    H39Slot2 *slot;         /* +0x8 */
    s32 frame;              /* +0xC */
    u8 pad10[0x80];
    s32 unk90, unk94;
    u8 pad98[4];
    u8 unk9C, unk9D, unk9E;
} H39Inst;
typedef struct {
    u8 pad00[0x30];
    f32 col[4];             /* +0x30: colour scale */
    u8 pad40[0x34];
    H39Inst *head;          /* +0x74 */
    u8 pad78[8];
    H39Slot2 *slots;        /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;              /* +0xB0 */
} H39PSys;
extern H39PSys *D_00615E60;
extern s32 D_0061621C;
typedef struct {
    s32 frame;
    s32 unk04;
    f32 d[6]; /* +0x8 */
} H39TsKey;
void pppDrawMdlTsFrame(PppObject *obj, H39TsKey *key, PppEntry *e) {
    f32 *w = (f32 *) ((u8 *) obj + e->offsets[2] + 0xA0);

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w[1] += w[2];
    w[0] += w[1];
    w[4] += w[5];
    w[3] += w[4];
    if (key->frame == obj->frame) {
        w[0] += key->d[0];
        w[1] += key->d[1];
        w[2] += key->d[2];
        w[3] += key->d[3];
        w[4] += key->d[4];
        w[5] += key->d[5];
    }
}

/* pppDrawMdlTsDraw (from hand/nostrict/text_00180000_h62.c). */
typedef struct {
    f32 a, b, c, d;
} DTsWork2;
void pppDrawMdlTsDraw(PppObject *obj, DKey *key, PppEntry *e) {
    DParam p;
    DBSWork *w;
    VtxSlot *s;
    DMdl *m;
    DTsWork2 *w2;
    VtxCur *cur;
    u8 r, g, b;

    w2 = PPP_WORK(DTsWork2, obj, e, 2);
    if (key->slot == 0xFFFF)
        return;
    w = PPP_WORK(DBSWork, obj, e, 0);
    p.a = w->a;
    if (p.a == 0)
        return;
    s = &D_00615E64->slots[key->slot];
    m = s->mdl;
    if (m->flags & 1)
        p.flags = 128;
    else
        p.flags = 12;
    if (!(m->flags & 2))
        p.flags |= 16;
    p.h08 = m->unk16;
    r = w->r;
    p.b0A = 0;
    g = w->g;
    cur = D_00615E68;
    p.w1C = 0;
    p.w38 = (s32) cur->vtx;
    p.w3C = cur->unk94;
    p.p04 = D_00616240;
    p.w0C = 0;
    p.r = r;
    p.w40 = 0;
    p.g = g;
    b = w->b;
    p.b = b;
    p.d10.w[0] = w2->a * 65536.0f;
    p.w44 = 0;
    p.d10.w[1] = w2->d * 65536.0f;
    p.p20 = cur->m50;
    p.p24 = D_00616140;
    p.p28 = D_00616100;
    p.p2C = cur->m10;
    p.b4C = 0;
    p.b4D = 0;
    p.w34 = D_00616224;
    D_00616224 = func_001aaf88(m, &p, s->unk20);
}

/* pppDrawShapeFrame (from hand/nostrict/text_00180000_h39.c). */
typedef struct {
    s16 unk00;
    s16 dur;    /* +0x2 */
    s8 flags;   /* +0x4 */
    u8 pad5[3];
} H39ShFrm;
typedef struct {
    u8 pad[6];
    s16 n;      /* +0x6 */
    u8 pad8[8];
    H39ShFrm frm[1]; /* +0x10 */
} H39Shape;
typedef struct { H39Shape *shape; s32 unk04; } H39ShEnt;
typedef struct {
    u8 pad00[0x14];
    H39ShEnt *shapes;  /* +0x14 */
} H39ShSys;
typedef struct { s32 frame; s32 id; u16 speed; } H39ShKey;
typedef struct { u16 time, frame, prev; } H39ShW;
#define D_00615E64 (*(H39ShSys *(*)) &D_00615E64)
void pppDrawShapeFrame(PppObject *obj, H39ShKey *key, PppEntry *e) {
    H39ShW *w;
    H39Shape *sh;
    H39ShFrm *f;
    u16 cur;
    H39ShEnt *se;
    s8 fl;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    w = (H39ShW *) ((u8 *) obj + e->offsets[0] + 0xA0);
    if (key->id == 0xFFFF)
        return;
    cur = w->frame;
    se = &D_00615E64->shapes[key->id];
    sh = se->shape;
    f = &sh->frm[w->prev];
    w->prev = cur;
    w->time += key->speed;
    if (w->time < f->dur)
        return;
    w->time -= f->dur;
    w->frame = cur + 1;
    if (w->frame < sh->n)
        return;
    fl = f->flags;
    w->time = 0;
    if (fl & 0x80) {
        w->frame = 0;
        return;
    }
    w->frame--;
}
#undef D_00615E64

/* pppDrawShapeDraw (from hand/nostrict/text_00180000_s6_11.c). */
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
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
typedef struct {
    u8 pad[0x10];
    PppMtx m;
    PppMtx m2;
    s32 unk90;
    s32 unk94;
} PppMtxOwner;
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
} DShpParam;
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
s32 func_001b8198(void *, DShpParam *, s32);
typedef struct { u8 r, g, b, a; } Col;
typedef struct {
    s32 frame;
    s32 id;
    u8 pad8[4];
    u8 bC, bD;
} ShpKey;
typedef struct {
    u8 pad[4];
    u16 idx;
} ShpW0;
typedef struct {
    u8 pad[8];
    Col col;
} ShpW1;
#define D_00615E64 ((DSys *) D_00615E64)
#define D_00615E68 ((PppMtxOwner *) D_00615E68)
void pppDrawShapeDraw(void *obj, ShpKey *key, PppEntry *e) {
    DShpParam p;
    ShpW0 *w = PPP_WORK(ShpW0, obj, e, 0);
    ShpW1 *c = PPP_WORK(ShpW1, obj, e, 1);
    PppShapeEnt *s;
    PppShape *sh;

    if (key->id == 0xFFFF)
        return;
    s = &((DSysS *) D_00615E64)->shapes[key->id];
    p.d8 = 0;
    p.p10 = D_00615E68->m2;
    p.b18 = 0;
    p.p1C = 0;
    if (!key->bC)
        p.flags = 128;
    else
        p.flags = 0;
    if (key->bD == 1)
        p.flags |= 0x10;
    {
        s32 *g = &D_00616224;
        u8 *src;
        p.r = c->col.r;
        p.g = c->col.g;
        p.b = c->col.b;
        p.a = c->col.a;
        { PppShapeFrame *f; sh = s->shape; f = &sh->f[w->idx]; src = (u8 *) sh + f->off; }
        p.w14 = *g;
        *g = func_001b8198(src, &p, s->unk4);
    }
}
#undef D_00615E64
#undef D_00615E68

