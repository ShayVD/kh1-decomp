#include "common.h"

typedef struct {
    union {
        u64 x;
        struct { u32 lo; u32 hi; } w;
    } f;
    u8 pad8[0x10 - 0x8];
    f32 x10[4];
    u8 pad20[0x30 - 0x20];
    union { u64 x; struct { s32 lo; s32 hi; } w; } x30;
    u8 pad38[0x5c - 0x38];
    s32 x5c;
    u8 pad60[0xa9 - 0x60];
    s8 xa9;
} B7P;

typedef struct {
    union { u64 x; struct { u32 lo; s32 hi; } w; } f;
    union { u64 x; struct { s32 i; s32 c; } w; struct { u64 lo:32; u64 b32:5; u64 r:27; } b; } x8;
    u8 x10[0x10];
    u8 pad20[0x2c - 0x20];
    s32 x2c;
} B7O;

typedef struct { f32 p[4]; f32 d[4]; f32 hit[4]; s16 x30; s32 x34; } B7Q;

void func_002675a8(f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_00118628(B7Q *, s32);
s32 func_00105b68(s32, s32);
void func_00105a30(s32, s32, f32 *);
void func_00146fb8(s32, s32, s32);
void *func_0014a1b0(B7P *, s32, f32 *);
void func_00147d50(void *, f32 *);
void func_0014ac00(B7P *, s32);
B7O *func_00135070(s32, s32);
void func_0014aaf0(B7P *);
#include "data/pieces/D_002C58A0.h"

B7P *func_0014b768(B7P *a, f32 *p0, f32 *p1) {
    B7Q q;
    f32 v[4];
    s32 k;
    s32 r;
    void *h;
    B7O *o;

    func_002675a8(q.p, p0);
    func_00267530(q.d, p1, p0);
    func_00118628(&q, ((s32)(a->x30.x >> 10) & 1) ? 2 : 1);
    if (q.x30 >= 0) {
        r = func_00105b68(q.x34, q.x30);
        switch (r) { case 0: k = 0x100; break; case 5: k = 8; break; default: k = 2; break; }
        if ((k & 0x102) && ((s32)(a->f.x >> 22) & 1)) {
            func_00146fb8(a->x30.w.hi, 0, a->xa9);
        }
        h = func_0014a1b0(a, k, q.hit);
        if (h) {
            func_00105a30(q.x34, q.x30, v);
            func_00267530(v, (*(f32 (*)[0x4])&D_002C58A0), v);
            func_00147d50(h, v);
        }
        func_0014ac00(a, k);
        if ((s32)(a->f.x >> 26) & 1) {
            func_002675a8(a->x10, q.hit);
        }
        if (!((s32)(a->x30.x >> 10) & 1) && !(k & 8) && a->x30.w.hi) {
            o = func_00135070(a->x30.w.hi, 0);
            if (o) {
                o->x8.w.i = -20;
                o->x8.b.b32 = 6;
                o->x2c = a->x5c;
                o->f.w.hi = 0;
            }
            func_0014aaf0(a);
            a = 0;
        }
    }
    return a;
}

typedef struct { u8 pad[4]; s32 x4; u8 pad8[8]; f32 v10[4]; } B3360;
typedef struct { u8 pad[0x30]; s32 x30; f32 x34; s32 x38; u8 pad3c[0x370 - 0x3c]; union { u64 x370; struct { u64 lo:44; u64 b44:1; u64 hi:19; } b370; }; } A3360;
s32 func_00152688(A3360 *, s32, s32);
f32 atan2f(f32, f32);
void func_00152d50(A3360 *, s32, f32 *);

void func_00153360(A3360 *a, B3360 *b) {
    func_00152688(a, b->x4, 17);
    a->x370 = 0x100000000000ULL | a->x370;
    a->x30 = 0;
    a->x34 = atan2f(b->v10[0], b->v10[2]);
    a->x38 = 0;
    func_00152d50(a, 3, b->v10);
}

typedef struct { u64 x0; u8 pad8[8]; f32 x10[4]; } Oad08;
typedef struct {
    u8 pad0[8];
    s32 x8;
    u8 padc[0x38 - 0xc];
    f32 x38;
    u8 pad3c[0x144 - 0x3c];
    f32 *x144;
    u8 pad148[0x4a0 - 0x148];
    void *x4a0;
} Aad08;
extern f32 D_002BBDFC;
void func_001315c0(Aad08 *, s32, f32, f32 *);
void *func_00121e28(s32, void *);
void func_0015ace0(void);
s32 func_001477e0(s32);
Oad08 *func_0014a4a8(Aad08 *, s32, s32);
void * func_001354b8(Oad08 *, s32);
f32 func_00120c88(f32);
void func_00142388(f32 *, f32 *);
void func_00142470(Aad08 *, f32 *);

void func_0015ad08(Aad08 *a) {
    f32 v[4];
    f32 w[4];
    Oad08 *o;
    f32 z;

    z = 0.0f;
    func_001315c0(a, 0x8003, z, v);
    if (a->x144 == 0) {
        a->x144 = func_00121e28(4, &a->x144);
        a->x4a0 = func_0015ace0;
        *a->x144 = z;
    }
    if (z < *a->x144) {
        *a->x144 -= D_002BBDFC;
    } else if (a->x8 != 0) {
        o = func_0014a4a8(a, 0, func_001477e0(26));
        o->x0 |= 64;
        func_002675a8(o->x10, v);
        func_001354b8(o, a->x8);
        *a->x144 = 30.0f;

    }
    a->x38 = func_00120c88(a->x38 + D_002BBDFC * 0.008726645261049271f);
    func_00142388(v, w);
    func_00142470(a, w);
}

#include "data/types/nostrict_text_00140000_s6_07.h"
Nea98 *D_00551D80 ALIGNED(16);
volatile s32 D_00559DB8 ALIGNED(8);
volatile s32 D_00559DBC ALIGNED(4);

typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct {
    u64 NLOOP : 15;
    u64 EOP : 1;
    u64 pad16 : 16;
    u64 id : 14;
    u64 PRE : 1;
    u64 PRIM : 11;
    u64 FLG : 2;
    u64 NREG : 4;
    u64 REGS0 : 4;
    u64 REGS1 : 4;
    u64 REGS2 : 4;
    u64 REGS3 : 4;
    u64 REGS4 : 4;
    u64 REGS5 : 4;
    u64 REGS6 : 4;
    u64 REGS7 : 4;
    u64 REGS8 : 4;
    u64 REGS9 : 4;
    u64 REGS10 : 4;
    u64 REGS11 : 4;
    u64 REGS12 : 4;
    u64 REGS13 : 4;
    u64 REGS14 : 4;
    u64 REGS15 : 4;
} GifTag;
typedef struct DmaTag {
    u16 qwc;
    u8 mark;
    u8 id;
    struct DmaTag *next;
    u32 p[2];
} DmaTag;

static inline void setTag(DmaTag *t, s32 qwc, s32 id, DmaTag *next) {
    t->id = id;
    t->next = next;
    t->qwc = qwc;
}
static inline void setGif(GifTag *g, s32 nloop, s32 nreg) {
    *(u128 *)g = 0;
    g->NLOOP = nloop;
    g->EOP = 1;
    g->NREG = nreg;
}
#include "data/bss_0055_typed.h"
#include "data/data_0035.h"
#include "data/pieces/D_002BBDFC.h"
