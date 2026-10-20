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
extern f32 D_002C58A0[];

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
            func_00267530(v, D_002C58A0, v);
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


typedef  struct Nea98 {
    u16 x0;
    u8 pad2[6];
    struct Nea98 *x8;
    s32 (*volatile xc)(struct Nea98 *);
} Nea98;
Nea98 *D_00551D80 ALIGNED(16);
volatile s32 D_00559DB8 ALIGNED(8);
extern volatile s32 D_00559DB4;
s32 func_00265bc0(s32, s32);

s32 func_0015ea98(void) {
    s32 r;

    while (func_00265bc0(1, 0) != 0) {
    }
    while (D_00551D80 != 0) {
        D_00559DB8++;
        r = D_00551D80->xc(D_00551D80);
        if (!(r & 0x20)) {
            D_00551D80->x0 = 0;
            D_00551D80 = D_00551D80->x8;
        } else {
            D_00559DB8--;
        }
        if (r & 2) return 1;
    }
    D_00559DB4 = 0;
    return 0;
}


typedef struct { u8 pad[8]; Nea98 *x8; s32 xc; u8 buf[0x4000]; } Beb78;
extern Beb78 D_00551D90[];
extern Beb78 * D_00559DB0; /* src/data/bss_0055.c: s32 D_00559DB0 */
volatile s32 D_00559DBC ALIGNED(4);
extern  s32 D_00351BD0;
void func_002583e0(s32);
s32 func_00258d10(s32);
void func_00258d78(s32);
s32 func_0015ea98(void);

s32 func_0015eb78(void) {
    s32 idx;
    Beb78 *cur;
    Beb78 *p;

    func_002583e0(0);
    D_00551D80 = D_00559DB0->x8;
    idx = D_00351BD0 ^ 1;
    D_00559DB4 = 1;
    D_00559DBC = 0;
    D_00559DB8 = D_00559DBC;
    D_00351BD0 = idx;
    D_00559DB0 = p = &D_00551D90[idx];
    p->x8 = 0;
    p->xc = 0;
    while (func_00265bc0(1, 0) != 0) {
    }
    func_00258d10(2);
    func_00258d10(1);
    *(volatile s32 *)0x1000e010 = 6;

    if (func_0015ea98()) {
        func_00258d78(2);
        func_00258d78(1);
    }
    return 0;
}


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
typedef struct {
    GifTag gif;
    u64 ad[8];
    GifTag img;
    u8 pad[32];
} Pk1;
typedef struct {
    DmaTag call;
    DmaTag end;
    GifTag gif;
    u64 ad[18];
} Pk2;
extern DmaTag D_00573AC0; /* src/data/bss_0057.c: u8 D_00573AC0[0x10] */
extern Pk1 D_00573AD0[7];
extern Pk2 D_00573E40;

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

void func_0015f128(void) {
    s32 i;
    Pk1 *p;
    u128 z = 0;

    for (i = 0; i < 7; i++) {
        p = &D_00573AD0[i];
        *(u128 *)&p->gif = 0;
        *(u128 *)&p->img = 0;

        p->gif.NLOOP = 4;
        p->gif.NREG = 1;
        p->gif.REGS0 = 0xe;
        p->ad[1] = 0x50;
        p->ad[3] = 0x51;
        p->ad[5] = 0x52;
        p->ad[7] = 0x53;
        p->ad[6] = 0;
        p->img.EOP = 1;
        p->img.FLG = 2;
    }
    setTag(&D_00573E40.call, 0, 0x50, &D_00573AC0);
    setTag(&D_00573E40.end, 10, 0x70, 0);
    setGif(&D_00573E40.gif, 9, 1);
    D_00573E40.gif.REGS0 = 0xe;
    D_00573E40.ad[0] = 0;
    D_00573E40.ad[1] = 0x3f;
    D_00573E40.ad[2] = 0x2006e005dd313600ULL;
    D_00573E40.ad[3] = 6;
    D_00573E40.ad[4] = 0x60;
    D_00573E40.ad[5] = 0x14;
    D_00573E40.ad[6] = 0x5080b;
    D_00573E40.ad[7] = 0x47;
    D_00573E40.ad[8] = 0x800000002aULL;
    D_00573E40.ad[9] = 0x42;
    D_00573E40.ad[10] = 0x31000070;
    D_00573E40.ad[11] = 0x4e;
    D_00573E40.ad[12] = 0;
    D_00573E40.ad[13] = 0x3d;
    D_00573E40.ad[14] = 0x800d0;
    D_00573E40.ad[15] = 0x4c;
    D_00573E40.ad[16] = 5;
    D_00573E40.ad[17] = 8;
}
