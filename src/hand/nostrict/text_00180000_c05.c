#include "common.h"
#include "ppp.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef int u128 __attribute__((mode(TI)));
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
typedef f32 PppVec4[4] __attribute__((aligned(16)));

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
    u8 pad[0x10];
    PppMtx m;
    PppMtx m2;
} PppMtxOwner;
extern PppMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
extern f32 D_00575A00; /* src/data/bss_0057.c: u8 D_00575A00[0x10] */

typedef struct {
    s32 frame;
    s32 slot;      /* +0x04 */
    s32 off;       /* +0x08 */
    u16 d[16];     /* +0x0C */
    f32 f2C;
    f32 f30, f34, f38, f3C, f40, f44, f48, f4C;
    u16 h50;
    u8 b52, b53;
    u8 pad54;
    u8 b55, b56, b57, b58;
} PppThKey;

typedef struct {
    u8 c0[8];      /* +0x00 */
    u8 pad8[4];
    f32 fC;        /* +0x0C */
    u8 c10[8];     /* +0x10 */
    u8 pad18[4];
    f32 f1C, f20, f24, f28, f2C, f30, f34, f38, f3C; /* +0x1C */
    u8 b40, b41, b42;
    u8 pad43;
} PppThSub;

typedef struct {
    u8 pad0[4];
    u8 flags;      /* +0x04 */
    u8 pad5[0xB];
    PppThSub s;    /* +0x10 */
    u8 pad54[0xC];
    u8 *a;         /* +0x60 */
    void *p;       /* +0x64 */
    f32 f68;       /* +0x68 */
    f32 f6C;       /* +0x6C */
    u16 c[16];     /* +0x70 */
} PppThWork;

typedef struct {
    PppThWork *w;
    void *p;
    PppThSub *s;
    u8 *a;
    f32 *v1;
    f32 *v0;
} PppThArgs;

void sceVu0CopyMatrix(PppMtx, PppMtx);
void func_002672f8(f32 *, PppMtx, f32 *);
void func_002673b8(f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
void func_001a89f0(PppThWork *, u8 *, f32 *, f32 *);
void func_001a8ae8(PppThArgs *);

/* needs make: uses rodata (doubles 3.141592654, 0.01745329252222222 @ 0x48fb38) */
void pppKeThFrame(PppObject *obj, PppThKey *key, PppEntry *e) {
    PppThWork *w = PPP_WORK(PppThWork, obj, e, 0);
    f32 *pos = PPP_WORK(f32, obj, e, 2);
    PppThSub *s = (PppThSub *) ((u8 *) obj + e->offsets[0] + 0xB0);
    PppMtx m;
    PppVec4 dir;
    PppVec4 org;
    PppThArgs args;
    f32 f;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    sceVu0CopyMatrix(m, D_00615E68->m);
    *(u128 *) m[3] = 0;
    m[3][3] = 1.0f;
    func_002672f8(dir, m, pos);
    func_002673b8(dir, dir);
    func_002675a8(org, D_00615E68->m[3]);
    if (obj->frame == key->frame) {
        if (obj->frame == 0) {
            u8 *p;
            u8 *a = PPP_WORK(u8, obj, e, 1);
            if (key->slot != -1)
                p = D_00615E60->slots[key->slot].inst + key->off + 0xA0;
            else
                p = (u8 *) &D_00575A00;
            if (w->p == &D_00575A00)
                return;
            w->p = p;
            w->a = a;
            if (key->b56 == 0)
                w->flags |= 8;
            if (key->b55 != 0)
                w->flags |= 4;
            if (key->b58 != 0)
                w->flags |= 0x10;
            if (key->b57 != 0)
                w->flags |= 0x20;
            func_001a89f0(w, w->a, org, dir);
        }
        w->c[0] += key->d[0];
        w->c[1] += key->d[1];
        w->c[2] += key->d[2];
        w->c[3] += key->d[3];
        w->c[4] += key->d[4];
        w->c[5] += key->d[5];
        w->c[6] += key->d[6];
        w->c[7] += key->d[7];
        w->c[8] += key->d[8];
        w->c[9] += key->d[9];
        w->c[10] += key->d[10];
        w->c[11] += key->d[11];
        w->c[12] += key->d[12];
        w->c[13] += key->d[13];
        w->c[14] += key->d[14];
        w->c[15] += key->d[15];
        w->f68 = key->f2C;
        w->f6C += key->f48;
        s->b42 = w->a[1] + 255;
        s->fC += key->f30;
        s->f30 = key->f38;
        s->f38 = key->f3C;
        s->f3C = key->f40;
        s->f24 += key->f44;
        s->f2C += key->f4C;
        s->f28 = key->h50 * 3.141592654 * 0.01745329252222222;
        s->b40 = key->b52;
        s->b41 = key->b53;
        s->f1C = -(s->fC - s->fC * key->f34) / s->b42;
    }
    f = w->f68 / s->b42;
    s->f20 = f;
    s->f34 = w->f6C / f;
    s->c0[0] = w->c[0] >> 7;
    s->c0[1] = w->c[1] >> 7;
    s->c0[2] = w->c[2] >> 7;
    s->c0[3] = w->c[3] >> 7;
    s->c0[4] = w->c[4] >> 7;
    s->c0[5] = w->c[5] >> 7;
    s->c0[6] = w->c[6] >> 7;
    s->c0[7] = w->c[7] >> 7;
    s->c10[0] = w->c[8] >> 7;
    s->c10[1] = w->c[9] >> 7;
    s->c10[2] = w->c[10] >> 7;
    s->c10[3] = w->c[11] >> 7;
    s->c10[4] = w->c[12] >> 7;
    s->c10[5] = w->c[13] >> 7;
    s->c10[6] = w->c[14] >> 7;
    s->c10[7] = w->c[15] >> 7;
    args.w = w;
    args.s = &w->s;
    args.a = w->a;
    args.p = w->p;
    args.v1 = org;
    args.v0 = dir;
    func_001a8ae8(&args);
}
