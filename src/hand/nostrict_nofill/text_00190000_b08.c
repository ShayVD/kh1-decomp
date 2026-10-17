/* 0x19c838 (worker b08): nostrict, no delay-slot filling. */
#include "common.h"
#include "ppp.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef int u128 __attribute__((mode(TI)));
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

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
extern PppMtxOwner *D_00615E68;
extern PppMtx D_00615E70;
void func_002672f8(f32 *, PppMtx, f32 *);
void func_002675a8(f32 *, f32 *);
void func_001a9098(void *, void *);
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
extern PppMtx D_00616040;
void func_00267518(f32 *, f32 *, f32 *);

typedef struct {
    PppVec4 pos;   /* +0x00 */
    PppVec4 vel;   /* +0x10 */
    u16 time;      /* +0x20 */
    u16 cur;       /* +0x22 */
    u16 prev;      /* +0x24 */
    u16 live;      /* +0x26 */
    u8 pad28[4];
    f32 ang;       /* +0x2C */
    f32 angv;      /* +0x30 */
    f32 anga;      /* +0x34 */
    f32 sx, sy;    /* +0x38 */
    f32 svx, svy;  /* +0x40 */
    f32 sax, say;  /* +0x48 */
    f32 spd;       /* +0x50 */
    f32 grav;      /* +0x54 */
    f32 alpha;     /* +0x58 */
    u8 n;          /* +0x5C */
    u8 fin;        /* +0x5D */
    u8 fout;       /* +0x5E */
    u8 pad5F;
} MegaPart;
typedef struct {
    u8 pad0[0x22];
    u16 h22;
    u8 pad24;
    u8 b25;
    u8 pad26[0x12];
    f32 c38[4];     /* +0x38 */
    u8 pad48[0x1C];
    f32 svx, svy;   /* +0x64 */
    u8 pad6C[0x18];
    f32 angv;       /* +0x84 */
    u8 pad88[0x1C];
    f32 spdv;       /* +0xA4 */
    f32 spda;       /* +0xA8 */
    u8 padAC[8];
    f32 grav;       /* +0xB4 */
    u8 padB8[0x12];
    u8 bCA, bCB;
    u8 padCC[2];
    u8 bCE;
} MegaKey;
typedef struct {
    PppMtx m;
    PppVec4 v;
} MegaObj;

void func_0019c838(MegaObj *w, MegaKey *key, MegaPart *pt, DColWork *c, f32 *b) {
    s32 a = c->a;
    f32 t;

    if (b) {
        b[0] += b[4];
        b[1] += b[5];
        b[2] += b[6];
        b[3] += b[7];
        t = b[3];
        b[4] += key->c38[0];
        b[5] += key->c38[1];
        b[6] += key->c38[2];
        b[7] += key->c38[3];
        a = c->a + (s32) t;
        if (a >= 256)
            a = 255;
    }
    pt->ang += pt->angv;
    if (key->bCB & 0x10)
        pt->angv += key->angv + pt->anga;
    else
        pt->angv += key->angv;
    while (pt->ang >= 180.0f)
        pt->ang -= 360.0f;
    while (pt->ang < -180.0f)
        pt->ang += 360.0f;
    pt->sx += pt->svx;
    pt->sy += pt->svy;
    if (key->bCA & 0x10) {
        pt->svx += key->svx + pt->sax;
        pt->svy += key->svy + pt->say;
    } else {
        pt->svx += key->svx;
        pt->svy += key->svy;
    }
    pt->spd += key->spda;
    if (!key->bCE) {
        if (0.0f < key->spdv && key->spda < 0.0f) {
            if (pt->spd < 0.0f)
                pt->spd = 0.0f;
        } else if (key->spdv < 0.0f && 0.0f < key->spda) {
            if (0.0f < pt->spd)
                pt->spd = 0.0f;
        }
    }
    pt->grav += key->grav;
    __asm__ volatile(
        "lqc2 $vf1, 0(%0)\n"
        "lqc2 $vf2, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf3\n"
        "lqc2 $vf4, 0(%3)\n"
        "lw $9, 0(%4)\n"
        "qmtc2 $9, $vf5\n"
        "vmulx.xyz $vf2xyz, $vf2xyz, $vf3x\n"
        "vmulx.xyz $vf4xyz, $vf4xyz, $vf5x\n"
        "vadd.xyz $vf1xyz, $vf1xyz, $vf2xyz\n"
        "vadd.xyz $vf1xyz, $vf1xyz, $vf4xyz\n"
        "sqc2 $vf1, 0(%0)\n"
        : : "r"(pt->pos), "r"(pt->vel), "r"(&pt->spd), "r"(w->v), "r"(&pt->grav)
        : "$8", "$9", "memory");
    if (key->h22)
        pt->live--;
    pt->n++;
    if (pt->fin && pt->n <= pt->fin)
        pt->alpha -= (f32) a / (f32) pt->fin;
    if (pt->fout && pt->fout >= pt->live)
        pt->alpha += (f32) a / (f32) key->b25;
}
