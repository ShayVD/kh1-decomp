/* ppp draw/frame callbacks around 0x197000-0x1a1000 (worker b08). This
 * region was built without strict aliasing. */
#include "common.h"
#include "ppp.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef int u128 __attribute__((mode(TI)));
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

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

extern DSys *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
extern s32 D_00616224;
s32 sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
void func_001a9460(f32, s32, s32, void *);
void func_001aa6b0(void *, s32, s32, s32);
void func_001a9790(s32, void *, s32, s32, s32, s32, void *);
typedef f32 PppVec4[4] __attribute__((aligned(16)));
typedef struct {
    u8 pad[0x10];
    PppMtx m;
    PppMtx m2;
    s32 unk90;
    s32 unk94;
} PppMtxOwner;
extern PppMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
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
void sceVu0MulMatrix(PppMtx, PppMtx, PppMtx);
void sceVu0UnitMatrix(PppMtx);
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

typedef struct {
    u8 pad[0x54];
    u8 mode;
} ThKey;

typedef struct {
    s32 x0;
    f32 x4, x8;
    f32 xC, x10, x14, x18;
} B030Out;
typedef struct {
    u8 pad[8];
    f32 x8;
    u8 padC[8];
    f32 x14;
} B030In;

void func_0018b030(B030In *a, B030Out *b) {
    f32 z;

    b->x4 = a->x8;
    b->x10 = a->x14;
    z = 0.0f;
    b->x18 = z;
    b->x14 = z;
    b->xC = z;
    b->x8 = z;
    b->x0 = (s32)a;
}

void func_0018b470(B030In *a, B030Out *b) {
    f32 z;

    b->x4 = a->x8;
    b->x10 = a->x14;
    z = 0.0f;
    b->x18 = z;
    b->x14 = z;
    b->xC = z;
    b->x8 = z;
    b->x0 = (s32)a;
}

#include "data/types/nostrict_text_00180000_s6_11.h"

/* VU0 */

/* VU0 */
