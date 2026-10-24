/* The model renderer's DMA side (docs/modules.md "Session 49"),
 * 0x001a9e70-0x001aaf88 less the image loads (opimage.c), the file loads
 * (opfile.c), the hand asm text_001aa1f8.s and the VU0 routines in
 * src/hand/vu0.c.  The strings near its data ("op_oef2_set error",
 * "op_md0_onef() light no support !") suggest the original files were named
 * op_*.c; the data D_00372760 ... D_003730A0 is shared with the VU0 draw
 * routines in src/asm/vu0_render*.s.
 *
 * func_001a9e70 opens DMA channel 2 (D_00372908) and resets the two packet
 * stacks; func_001a9eb8 / func_001a9f88 build the GS set up packets
 * D_0061E800 / D_0061E8B0 and chain 288 tags into the priority lists
 * D_0061EEA0 (16 heads), D_0061FFA0 (16) and D_0061EFA0 (256), which
 * func_001aa6b0 / func_001aa700 / func_001aa750 insert into and
 * func_001aa650 sends.  func_001aa950 / func_001aa990 push on two s32 stacks
 * with s8 stack pointers (upwards from 0x70000000 and downwards from
 * 0x70004000: the scratchpad), func_001aa9d0 / func_001aa9e8 pop them and
 * func_001aaa00 / func_001aaa38 test for room.  func_001aaf88 picks the VU0
 * draw routine for a model from its flags (bit 2, bits 8-9, bit 7).
 * Read from the code, not proved by a boot. */
#include "m2c.h"
#include "data/types/text_001a0000_h13.h"
#include "data/types/text_001a0000_h13_p.h"

s32 sceGsSyncPath(s32, s32);
void FlushCache(s32);
s32 func_00266c08(M2C_UNK);
void func_00266f38(s32, void *);
s32 func_00265bc0(s32, s32);
s32 rand(void);
void func_001a9e90(void);
void func_001aa918(void);
void func_001aa6b0(GsTag *t, s32 qwc, s32 pri, s32 z);
void func_001aa700(GsTag *t, s32 qwc, s32 pri, s32 z);

extern u64 D_0061E800[];
extern u128 D_0061E8B0;  /* sized: cover_check sizes D_0061EEA0 after it */
extern GsTag D_0061EEA0[];  /* 16 priority list heads (followed by the tag pool) */
extern GsTag D_0061EFA0[];  /* 256 priority list heads */
GsTag D_0061FFA0[0x30] ALIGNED(32);
extern s32 D_00372908;
extern M2C_UNK D_00372F34;
extern f32 D_002BC120;
extern f32 D_002BC124;

void func_001a9e70(void) {
    func_001a9e90();
    func_001aa918();
}

void func_001a9e90(void) {
    D_00372908 = func_00266c08(2);
}

void func_001a9eb8(void) {
    u64 *p = D_0061E800;
    p[2] = 0x5000000000008001ULL;
    p[3] = 0xEEEEE;
    p[6] = 0x131000070ULL;
    p[7] = 78;
    p[12] = 0x7000D;
    p[13] = 71;
    p[14] = 33;
    p[15] = 20;
    p[18] = 0;
    p[19] = 8;
    p[16] = 0x8000000000ULL;
    p[17] = 59;
    p = (u64 *)&D_0061E8B0;
    p[2] = 0x5000000000008001ULL;
    p[3] = 0xEEEEE;
    p[6] = 0x31000070;
    p[7] = 78;
    p[12] = 0x7000D;
    p[13] = 71;
    p[14] = 33;
    p[15] = 20;
    p[18] = 0;
    p[19] = 8;
    p[16] = 0x8000000000ULL;
    p[17] = 59;
}

void func_001a9f88(void) {
    GsTag *p = D_0061EEA0;
    u128 k = 0x20000000;
    s32 i;
    for (i = 0; i < 288; i++) {
        __asm__ volatile("sq %0, 0(%1)" : : "r"(k), "r"(p));
        p->s.next = p + 1;
        p->s.tail = p;
        p++;
    }
    __asm__ volatile("sq %0, 0(%1)" : : "r"(k), "r"(p));
    p->s.w0 = 0x70000000;
    func_001aa6b0((GsTag *)D_0061E800, 7, 0, 0);
    func_001aa700((GsTag *)&D_0061E8B0, 7, 15, 0);
}

void func_001aa008(void) {
    u128 *p = &D_0061E8B0;
    u128 save = *p;
    *p = 0x70000006;
    sceGsSyncPath(0, 0);
    FlushCache(0);
    func_00266f38(D_00372908, p);
    sceGsSyncPath(0, 0);
    *p = save;
}

/* Seeds the VU0 random register R. */
void func_001aa080(void) {
    s32 r;
    r = rand();
    __asm__ volatile(
        "qmtc2 %0, $vf31\n"
        "vrxor R, $vf31x\n"
        : : "r"(r) : "$2");
}

void func_001aa650(void) {
    void *p = D_0061EEA0;
    sceGsSyncPath(0, 0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    func_00266f38(D_00372908, p);
    sceGsSyncPath(0, 0);
}

/* The original clears the tag with `sq $0`, which ee-gcc 2.96 cannot emit
 * from C (it loads a zero TImode register first); the empty asm keeps the
 * header store ahead of the clamp as in the original.  The callers pass a
 * fourth argument (0) the code does not read. */
void func_001aa6b0(GsTag *t, s32 qwc, s32 pri, s32 z) {
    GsTag *tail, *n;
    __asm__ volatile("sq $0, 0(%0)" : : "r"(t) : "memory");
    t->s.w0 = (qwc - 1) | 0x20000000;
    __asm__ volatile("" : : : "memory");
    if (pri < 1) pri = 0;
    if (pri >= 16) pri = 15;
    tail = D_0061EEA0[pri].s.tail;
    n = tail->s.next;
    tail->s.next = t;
    t->s.next = n;
    D_0061EEA0[pri].s.tail = t;
}

void func_001aa700(GsTag *t, s32 qwc, s32 pri, s32 z) {
    GsTag *tail, *n;
    __asm__ volatile("sq $0, 0(%0)" : : "r"(t) : "memory");
    t->s.w0 = (qwc - 1) | 0x20000000;
    __asm__ volatile("" : : : "memory");
    if (pri < 1) pri = 0;
    if (pri >= 16) pri = 15;
    tail = D_0061FFA0[pri].s.tail;
    n = tail->s.next;
    tail->s.next = t;
    t->s.next = n;
    D_0061FFA0[pri].s.tail = t;
}

void func_001aa750(GsTag *t, s32 qwc, s32 pri) {
    GsTag *tail, *n;
    __asm__ volatile("sq $0, 0(%0)" : : "r"(t) : "memory");
    t->s.w0 = (qwc - 1) | 0x20000000;
    __asm__ volatile("" : : : "memory");
    if (pri < 1) pri = 0;
    if (pri >= 256) pri = 255;
    tail = D_0061EFA0[pri].s.tail;
    n = tail->s.next;
    tail->s.next = t;
    t->s.next = n;
    D_0061EFA0[pri].s.tail = t;
}

/* A sprite packet (GIF tag, RGBA, two XYZ2 corners) linked at priority 0. */
typedef struct {
    u8 p0[16]; u64 tag; u64 regs;
    union { u128 q; struct { u8 a; u8 p1[3]; u8 b; u8 p2[3]; u64 d; } s; } u20;
    u128 rgba; u128 xy0; u128 xy1;
} Spr7a;

u8 *func_001aa7a0(p, col, a, b) Spr7a *p; u32 col; u8 a; u8 b; {
    u128 c;
    p->tag = 0x41A3400000008001ULL;
    p->regs = 0x441E;
    __asm__ volatile("sq $0, 32(%0)" : : "r"(p) : "memory");
    p->u20.s.a = a;
    p->u20.s.b = b;
    p->u20.s.d = 66;
    __asm__ volatile("pextlb %0, $0, %1\n\tpextlh %0, $0, %0\n\tsq %0, 48(%2)" : "=r"(c) : "r"(col), "r"(p) : "memory");
    p->xy0 = 0xFFFFFFFE0000780000007000;
    p->xy1 = 0xFFFFFFFE0000880000009000;
    func_001aa700((GsTag *)p, 6, 0, 0);
    return (u8 *)p + 96;
}

#include "data/pieces/D_00372800.h"

void func_001aa858(void) {
    f32 *d = D_00372800;
    d[0] = d[1] = 0.0f;
    d[2] = 255.0f;
    d[3] = 0.0f;
    d[4] = d[5] = 0.0f;
    d[6] = 255.0f;
    d[7] = 255.0f;
    d[8] = 0.7999999523162842f;
    d[9] = -32.0f;
    d[10] = 128.0f;
    d[11] = 0.0f;
    d[12] = 0.0f;
    d[13] = 128.0f;
    d[14] = 128.0f;
    d[15] = 0.0f;
}

void func_001aa8d0(void) {
    M2C_FIELD((M2C_UNK *)&D_00372800, f32 *, 0) = (f32) D_002BC120;
    M2C_FIELD((M2C_UNK *)&D_00372800, f32 *, 4) = (f32) D_002BC124;
}

void func_001aa8f8(void) {

}

void func_001aa900(void) {

}

void func_001aa908(void) {

}

void func_001aa910(void) {

}

/* Two small s32 stacks with s8 stack pointers. */
extern s8 D_00372EA0;
#include "data/pieces/D_00372EA8.h"
extern s8 D_00372F28;
#include "data/pieces/D_00372F30.h"

void func_001aa918(void) {
    (*(s32 *)&D_00372EA8) = 0x70000000;
    (*(s32 *)&D_00372F30) = 0x70004000;
    D_00372EA0 = 0;
    D_00372F28 = 0;
}

void func_001aa948(void) {

}

s32 func_001aa950(s32 n) {
    s8 *sp = &D_00372EA0;
    s32 *st = D_00372EA8;
    s32 i = *sp;
    s32 v = st[i];
    i++;
    *sp = i;
    st[i] = v + n;
    return v;
}

s32 func_001aa990(s32 n) {
    s8 *sp = &D_00372F28;
    s32 *st = D_00372F30;
    s32 i = *sp;
    s32 v = st[i];
    i++;
    *sp = i;
    st[i] = v;
    return v - n;
}

void func_001aa9d0(void) {
    s32 wide;
    wide = D_00372EA0;

    D_00372EA0 = wide - 1;
}

void func_001aa9e8(void) {
    s32 wide;
    wide = D_00372F28;

    D_00372F28 = wide - 1;
}

s32 func_001aaa00(s32 arg0) {
    return (*(M2C_UNK *)((s8 *)(s8 *)&D_00372F34 + (D_00372F28 * 4)) >= (s32) ((s8 *)&D_00372EA8 + arg0)) ? 0 : -1;
}

s32 func_001aaa38(s32 n) {
    if ((s32)D_00372F30 - n < D_00372EA8[D_00372EA0 + 1]) return -1;
    return 0;
}

/* Model draw dispatch (func_001aaf88) with its two helpers, which must be
 * defined above it (consolidated from w65). */
typedef struct { u32 flags; } DMdl;
typedef struct {
    s32 flags;
    u8 pad04[0x48];
    union { u16 h; struct { s8 a, b; } c; } x4c;
} DParam;
extern s32 D_00616224;
extern s32 D_00616228;
extern s32 D_00616230;
extern u8 D_00373000[], D_00373030[];

void func_001aaed0(void) {
    func_00265bc0(0, 0);
    func_00266f38(D_00372908, &D_00373000);
}

void func_001aaf00(void) {
    func_00265bc0(0, 0);
    func_00266f38(D_00372908, &D_00373030);
}

typedef struct { u8 pad[0x60]; u64 a; u64 b; } Gs800;
#define D_0061E800_g (*(Gs800 *)D_0061E800)
extern Gs060 D_00373060;

void func_001aaf30(void) {
    Gs060 *d = &D_00373060;
    d->a = D_0061E800_g.a;
    d->b = D_0061E800_g.b;
    sceGsSyncPath(0, 0);
    func_00266f38(D_00372908, d);
}

s32 func_001b6910(DMdl *, DParam *);
s32 func_001b3870(DMdl *, DParam *);
s32 func_001ae010(DMdl *, DParam *);
s32 func_001ab0e0(DMdl *, DParam *);
s32 func_001b1ab8(DMdl *, DParam *);
s32 func_001afac0(DMdl *, DParam *);

s32 func_001aaf88(DMdl *m, DParam *p, s32 n) {
    s32 r;

    if (p->flags & 4) {
        if (p->x4c.c.b)
            func_001aaed0();
        else if (p->x4c.c.a)
            func_001aaf00();
        if (p->flags & 0x300)
            r = func_001b6910(m, p);
        else
            r = func_001b3870(m, p);
        if (p->x4c.h)
            func_001aaf30();
    } else {
        if (D_00616228 + n >= D_00616230)
            return D_00616224;
        if (p->flags & 0x80) {
            if (p->flags & 0x300)
                r = func_001ae010(m, p);
            else
                r = func_001ab0e0(m, p);
        } else {
            if (p->flags & 0x300)
                r = func_001b1ab8(m, p);
            else
                r = func_001afac0(m, p);
        }
        D_00616228 += r - D_00616224;
    }
    return r;
}

#include "data/data_0037.h"
#include "data/data_002B.h"
#include "data/pieces/D_00373060.h"
