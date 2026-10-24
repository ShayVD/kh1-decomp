#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"

void *memset(void *, s32, u32);
void *func_0017f958(void *, s32);
s32 func_0019f1a8(void *, void *);
void func_001a0628(void *, void *, void *);
void func_002673b8(void *, void *);
typedef struct { u8 pad0[2]; s16 dur; s8 flag; u8 pad5[3]; } AnFrm;
typedef struct { u8 pad0[6]; s16 n; u8 pad8[8]; AnFrm fr[1]; } Anim;
typedef struct { Anim *anim; s32 pad; } AnEnt;
typedef f32 Mtx4[4][4];
typedef struct { u32 flags; u8 pad04[0x12]; u16 h16; } DMdl;
typedef struct { u8 pad[0x14]; void *x14; u8 pad18[4]; DMdl *mdl; s32 x20; } Ent24;
typedef struct { s16 a; s16 n; u16 *list; } Grp;
typedef struct { u8 pad0[0x10]; Ent24 *x10; AnEnt *anims; Grp *grps; } PppRes;
extern PppRes *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
#include "data/pieces/D_003701D0.h"
typedef FV4_3701d0 FV4;

typedef struct {
    f32 x, y, z, w;
    void *p10;
    void *p14;
    void *p18;
    s32 n;
} MbmW;

typedef struct {
    u8 pad0[0x1c];
    u16 n;
    u8 pad1e[0xd0 - 0x1e];
    f32 x, y, z;
    u8 paddc[0x101 - 0xdc];
    u8 b101;
    u8 pad102[4];
    u8 b106;
} MbmK;

void pppRyjMegaBirthModelFrame(void *obj, MbmK *k, PppEntry *e) {
    MbmW *w = (MbmW *)((u8 *)obj + e->offsets[2] + 0xA0);
    void *w2 = (u8 *)obj + e->offsets[1] + 0xA0;

    if (w->p10 == NULL) {
        w->n = k->n;
        w->p10 = func_0017f958(D_00615E64, w->n * 0xB0);
        if (w->p10 != NULL)
            memset(w->p10, 0, w->n * 0xB0);
        if (k->b106) {
            w->p14 = func_0017f958(D_00615E64, w->n << 6);
            if (w->p14 != NULL)
                memset(w->p14, 0, w->n << 6);
        }
        if (k->b101) {
            w->p18 = func_0017f958(D_00615E64, w->n << 5);
            if (w->p18 != NULL)
                memset(w->p18, 0, w->n << 5);
        }
        w->x = k->x;
        w->y = k->y;
        w->z = k->z;
        w->w = 0;
        func_002673b8(w, w);
    }
    if (func_0019f1a8(w, k))
        func_001a0628(w, k, w2);
}
void func_00267560(void *, void *, f32);

extern FV4 D_00615F70; /* src/data/bss_0061.c: f32 D_00615F70[4] */
void func_00267530(FV4 *, FV4 *, FV4 *);

typedef struct { u8 pad0[0x20]; u16 t; u16 idx; u16 prev; u16 alive; u8 pad28[0x38]; } MbPart;
typedef struct { u8 pad[0x20]; } MbSub;
typedef struct { MbPart *parts; MbSub *subs; s32 n; f32 alpha; u16 timer; u8 active; } MbWork;
typedef struct { u8 pad0[0xe]; u16 n; u8 pad10[0xac - 0x10]; f32 dist; f32 fade; u8 test; u8 padb5; u8 sub; } MbfKey;

s32 func_001a2218(MbWork *, MbfKey *);
void func_001a2d40(MbWork *, MbfKey *, void *);

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
        func_00267530(&d, &D_00615F70, &D_003701D0);
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
        func_001a2d40(w, k, w2);
}

typedef struct { MbPart *parts; MbSub *subs; s32 n; f32 alpha; u16 timer; u8 active; } MbmWork;
typedef struct { u8 pad0[0xa]; u16 n; u8 padc[0xe8 - 0xc]; f32 dist; f32 fade; u8 test; u8 padf1; u8 sub; } MbmfKey;
s32 func_001a36f0(MbmWork *, MbmfKey *);
void func_001a47b0(MbmWork *, MbmfKey *, void *);

void pppRyjMegaBirthModelFilterFrame(void *obj, MbmfKey *k, PppEntry *e) {
    MbmWork *w = (MbmWork *)((u8 *)obj + e->offsets[2] + 0xA0);
    void *w2 = (u8 *)obj + e->offsets[1] + 0xA0;
    FV4 d;
    f32 len, r;

    if (w->parts == NULL) {
        w->n = k->n;
        w->parts = func_0017f958(D_00615E64, w->n * 0xA0);
        if (w->parts != NULL)
            memset(w->parts, 0, w->n * 0xA0);
        if (k->sub) {
            w->subs = func_0017f958(D_00615E64, w->n << 5);
            if (w->subs != NULL)
                memset(w->subs, 0, w->n << 5);
        }
    }
    if (!func_001a36f0(w, k))
        return;
    if (k->test) {
        func_00267530(&d, &D_00615F70, &D_003701D0);
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
        func_001a47b0(w, k, w2);
}

void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_002678b8(f32 (*)[4], void *, f32 *);

void func_002675a8(f32 *, void *);
void func_002672f8(f32 *, void *, f32 *);
extern u8 D_006161C0[];
extern u8 D_00615EB0[];
extern f32 D_00616040[4][4]; /* src/data/bss_0061.c: u8 D_00616040[0x40] */

typedef struct { u8 pad[0xe0]; f32 mul; f32 add; } RkKey;
typedef struct {
    u8 pad0[0x28];
    union { u64 d; s32 i[2]; } r01;
    s32 r2;
    u8 pad34[0x54 - 0x34];
    f32 scale[3];
} RkObj;

f32 func_001a4a98(void *a0, f32 (*m)[4], RkKey *k, void *a3, RkObj *o) {
    Mtx4 rm;
    f32 rot[3];
    f32 z;
    s32 i;
    sceVu0UnitMatrix(m);
    if (o->r01.d || o->r2) {
        for (i = 0; i < 3; i++)
            rot[i] = (f32)o->r01.i[i] * 3.1415926f * 3.0517578125e-05f;
        func_002678b8(rm, D_006161C0, rot);
        sceVu0MulMatrix(m, m, rm);
    }
    for (i = 0; i < 3; i++)
        func_00267560(m[i], m[i], o->scale[i]);
    func_002675a8(m[3], o);
    func_002672f8(m[3], D_00615EB0, m[3]);
    m[3][1] *= k->mul;
    z = m[3][2];
    m[3][1] += k->add;
    sceVu0MulMatrix(m, D_00616040, m);
    return z;
}
#include "data/bss_0057_mixed.h"
