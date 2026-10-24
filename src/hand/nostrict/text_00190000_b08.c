/* ppp draw/frame callbacks around 0x197000-0x1a1000 (worker b08). This
 * region was built without strict aliasing. */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"

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
extern PppSystem *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */

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

extern DSys *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
extern s32 D_00616224;
s32 sceGsSetDefLoadImage(void *, s32, s32, s32, s32, s32, s32, s32);
void func_001a9460(f32, s32, s32, void *);
void func_001aa6b0(void *, s32, s32, s32);
void func_001a9790(s32, void *, s32, s32, s32, s32, void *);
typedef f32 PppVec4[4] __attribute__((aligned(16)));
void func_001a9098(void *, void *);

typedef struct {
    s32 frame;
    s32 id;
    f32 da, db, dc;
    s32 u, v;
    u8 page;
    u8 pad1D[3];
    f32 dd, de, df, dg, dh, di;
    u8 b38, b39, b3A, b3B, b3C;
} PppTfdUv3Key;
typedef struct {
    f32 a, b, c, pc;
    f32 d, e, f;
    f32 g, h, i;
} PppTfdUv3;

void pppKeMdlTfdUv3Draw(PppObject *obj, PppTfdUv3Key *key, PppEntry *e) {
    PppTfdUv3 *w = PPP_WORK(PppTfdUv3, obj, e, 2);
    u32 tex;
    s32 n;
    u8 *p, *q;

    if (D_0061621C == 0 && !(D_00615E60->flags & 0xFF0000FF00ULL)) {
        w->b += w->c;
        w->e += w->f;
        w->h += w->i;
        w->a += w->b;
        w->d += w->e;
        w->g += w->h;
        if (obj->frame == key->frame) {
            w->a += key->da;
            w->b += key->db;
            w->c += key->dc;
            w->d += key->dd;
            w->e += key->de;
            w->f += key->df;
            w->g += key->dg;
            w->h += key->dh;
            w->i += key->di;
        }
    }
    if (key->id == 0xFFFF)
        return;
    {
        DSlot *r = &D_00615E64->slots[key->id];
        tex = r->tex;
    }
    n = key->page * 4;
    p = (u8 *) D_00616224 + 16;
    sceGsSetDefLoadImage(p, ((tex >> 5) & 0x3FFF) + n, 4, (tex >> 19) & 0xF, 0, 0, 16, 16);
    *(u64 *) (p + 0x50) = 0x0800000000008100ULL;
    q = (u8 *) D_00616224;
    func_001a9460(w->a, key->u, key->v, q + 0x70);
    func_001aa6b0((void *) D_00616224, 263, 0, 0);
    D_00616224 = (s32) (q + 0x1070);
    {
        void *w0 = PPP_WORK(void, obj, e, 0);
        void *w3 = PPP_WORK(void, obj, e, 3);
        func_001a9790(key->id, w0, n, (s32) w->d, (s32) w->g,
                      key->b38 | key->b39 | key->b3B | key->b3A | key->b3C, w3);
    }
}
extern PppMtx D_00616180, D_00616080;
extern PppMtx D_00616180;
#define D_00616224 (*(volatile s32 *) &D_00616224)
#undef D_00616224
extern PppMtx D_00615EB0;
void sceVu0CopyMatrix(PppMtx, PppMtx);
extern PppMtx D_00615EB0;
void sceVu0CopyMatrix(PppMtx, PppMtx);
extern PppMtx D_00615EB0, D_00616180;

static inline void vu0ScaleRow(f32 *row, f32 s) {
    __asm__ volatile(
        "qmtc2 %1, $vf9\n"
        "lqc2 $vf10, 0(%0)\n"
        "vmulx.xyz $vf10xyz, $vf10xyz, $vf9x\n"
        "sqc2 $vf10, 0(%0)\n"
        : : "r"(row), "r"(s));
}
extern PppMtx D_00615EB0;
void sceVu0CopyMatrix(PppMtx, PppMtx);
#define D_00616224 (*(volatile s32 *) &D_00616224)
#undef D_00616224

/* needs make: uses rodata */

void *func_0017f958(void *, s32);

void *func_0017f958(void *, s32);
#include "data/data_0037.h"
