/* pppKeTkFadeDraw and pppKeMatPhtFrame, -fno-strict-aliasing
 * (docs/modules.md "Session 50"): the fade draws a textured screen quad
 * (its CLUT built from D_00372770, sent with opdma.c's func_001aa950 /
 * func_001aa9d0 and sceGsExecLoadImage) whose level has speed and
 * acceleration in the work area; pppKeMatPht builds the photo matrix
 * D_0061E7C0.  The other matrix classes are in kemat.c.  Read from the
 * code, not proved by a boot. */

/* pppKeTkFadeDraw (from hand/nostrict/text_00180000_b07.c). */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"
#include "data/pieces/D_003701F0.h"
#include "data/pieces/D_003701E0.h"
#include "data/pieces/D_003701D0.h"
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;
typedef f32 PppVec4[4] __attribute__((aligned(16)));
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
} PppMdlRes; /* 0x24 */
typedef struct {
    u8 pad[0x10];
    PppMdlRes *res; /* +0x10 */
    void *p14;
    VtxMap *maps;   /* +0x18 */
} PppMdlBank;
typedef struct {
    s32 unk0;
    u8 *inst;   /* +0x4 */
    s32 time;   /* +0x8 */
    s32 unkC;
} PppSlot;
typedef struct {
    u8 pad[0x80];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem;
extern s32 D_0061621C;
extern PppSystem *D_00615E60;
extern PppMdlBank *D_00615E64;
void func_00267530(f32 *, f32 *, f32 *);
s32 sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct {
    s32 frame;
    s32 id;       /* +0x4 */
    f32 d[3];     /* +0x8 */
    u32 col0;     /* +0x14 */
    u32 col1;     /* +0x18 */
} PppTkFadeKey;
typedef struct {
    u8 pad0[0xC];
    s32 lo;       /* +0xC */
    s32 hi;       /* +0x10 */
} TkRes;
typedef struct {
    u32 clut[256];
    s8 tbl[32];
} TkBuf;
extern u128 D_00372770[2];
extern s8 D_00372790[];
void *func_001aa950(s32);
void func_001aa9d0(s32);
void func_00267518(f32 *, f32 *, f32 *);
void func_002674b0(f32 *, f32 *, f32);
void FlushCache(s32);
s32 sceGsExecLoadImage(void *, void *);
s32 sceGsSyncPath(s32, s32);
/* --- pppKeTkFadeDraw: build a faded 256-entry CLUT and upload it --- */
void pppKeTkFadeDraw(PppObject *obj, PppTkFadeKey *key, PppEntry *e) {
    f32 *w = PPP_WORK(f32, obj, e, 0);
    PppVec4 b;
    PppVec4 a;
    u8 li[96];
    TkBuf *buf;
    u32 *p;
    u32 c0, c1;
    u64 tex;
    s32 n, i;
    f32 sc;

    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w[1] += w[2];
        w[0] += w[1];
        if (obj->frame == key->frame) {
            w[0] += key->d[0];
            w[1] += key->d[1];
            w[2] += key->d[2];
        }
    }
    if (key->id == 0xFFFF)
        return;
    buf = func_001aa950(0x420);
    ((u128 *) buf->tbl)[0] = D_00372770[0];
    ((u128 *) buf->tbl)[1] = D_00372770[1];
    {
        TkRes *r = (TkRes *) &D_00615E64->res[key->id];
        c1 = key->col1;
        tex = ((u64) r->hi << 32) | r->lo;
        c0 = key->col0;
        n = w[0];
    }
    if (n < 0) {
        if (n < -256)
            n = -256;
        n += 256;
        p = &buf->clut[(n & 0xE0) + D_00372790[n & 0x1F]];
        for (i = n; i < 256; i++) {
            *p = c0;
            p += buf->tbl[i & 0x1F];
        }
        i = 0;
        sc = n;
        p = buf->clut;
    } else {
        if (n >= 256)
            n = 255;
        p = buf->clut;
        for (i = 0; i < n; i++) {
            *p = c1;
            p += buf->tbl[i & 0x1F];
        }
        sc = 256.0f - n;
        n = 256;
    }
    a[0] = (s32) (c1 & 0xFF);
    a[1] = (s32) ((c1 >> 8) & 0xFF);
    a[2] = (s32) ((c1 >> 16) & 0xFF);
    a[3] = (s32) (c1 >> 24);
    b[0] = (s32) (c0 & 0xFF);
    b[1] = (s32) ((c0 >> 8) & 0xFF);
    b[2] = (s32) ((c0 >> 16) & 0xFF);
    b[3] = (s32) (c0 >> 24);
    func_00267530(b, b, a);
    func_002674b0(b, b, sc);
    for (; i < n; i++) {
        *p = ((u32) a[3] << 24) | ((u32) a[2] << 16) | ((u32) a[1] << 8) | (u32) a[0];
        func_00267518(a, a, b);
        p += buf->tbl[i & 0x1F];
    }
    sceGsSetDefLoadImage(li, (u16) ((tex >> 37) & 0x3FFF), 4, (u16) ((tex >> 51) & 0xF), 0, 0, 16, 16);
    FlushCache(0);
    sceGsExecLoadImage(li, buf);
    sceGsSyncPath(0, 0);
    func_001aa9d0(0x420);
}

/* pppKeMatPhtFrame (from hand/nostrict/text_00180000_h40.c). */
#include "data/types/nostrict_text_00180000_h40.h"
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject_949c8;
typedef struct { f32 x, y, z; } PppFVec;
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;
void func_001a5490(PppMtx, void *);
static inline void vu0ScaleRow(f32 *row, f32 s) {
    __asm__ volatile(
        "qmtc2 %1, $vf9\n"
        "lqc2 $vf10, 0(%0)\n"
        "vmulx.xyz $vf10xyz, $vf10xyz, $vf9x\n"
        "sqc2 $vf10, 0(%0)\n"
        : : "r"(row), "r"(s));
}
extern PppMtx D_0061E7C0;
void sceVu0UnitMatrix(PppMtx);
void func_002675a8(f32 *, f32 *);
void pppKeMatPhtFrame(PppObject_949c8 *obj, void *key, PppEntry *e) {
    PppFVec *t = PPP_WORK(PppFVec, obj, e, 0);
    PppFVec *r = PPP_WORK(PppFVec, obj, e, 1);
    PppFVec *s = PPP_WORK(PppFVec, obj, e, 2);

    func_001a5490(D_0061E7C0, r);
    vu0ScaleRow(D_0061E7C0[0], s->x);
    vu0ScaleRow(D_0061E7C0[1], s->y);
    vu0ScaleRow(D_0061E7C0[2], s->z);
    D_0061E7C0[3][0] = t->x;
    D_0061E7C0[3][1] = t->y;
    D_0061E7C0[3][2] = t->z;
    sceVu0UnitMatrix(D_00615E68->m);
    D_00615E68->m[0][0] = s->x;
    D_00615E68->m[1][1] = s->y;
    D_00615E68->m[2][2] = s->z;
    func_002675a8(D_00615E68->m[3], D_0061E7C0[3]);
}

#include "data/data_0037.h"
#include "data/pieces/D_003727B0.h"
