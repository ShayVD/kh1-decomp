/* Hand-matched functions near 0x14D000-0x158000 (worker 9). */
#include "common.h"
#include "data/bss_0054.h"

typedef struct {
    u8 pad0[0x10];
    f32 x10;
    u8 pad14[0xBD - 0x14];
    s8 xbd;
    u8 padbe[0xC4 - 0xBE];
    f32 xc4;
    u8 padc8[0xCC - 0xC8];
    union { f32 f; s32 i; u8 c; } xcc;
} W9Obj6c;
typedef struct {
    u8 pad0[0x100];
    u64 x100;
    u8 pad108[0x130 - 0x108];
    f32 x130[4];
    s32 x140;
} W9Obj148;
typedef struct {
    u8 pad0[0x1C];
    u8 *x1c;
} W9Obj134;
typedef struct {
    u8 pad0[0x120];
    f32 x120[4];
    u8 pad130[0x134 - 0x130];
    W9Obj134 *x134;
} W9Obj98;
typedef union { f32 f; s32 i; void *p; u8 c; } W9U;
typedef union {
    W9U w[0x20];
    u64 d[0x10];
} W9Obj144;
typedef struct Actor {
    s32 flags;
    s32 x4;
    u8 pad8[0x10 - 8];
    f32 x10[4];
    f32 x20[4];
    f32 x30[4];
    u8 pad40[0x6C - 0x40];
    W9Obj6c *x6c;
    s32 x70;
    u8 pad74[0x8C - 0x74];
    s32 x8c;
    u8 pad90[0x98 - 0x90];
    W9Obj98 *x98;
    u8 pad9c[0xA4 - 0x9C];
    f32 xa4;
    f32 xa8;
    u8 padac[0x120 - 0xAC];
    f32 x120[4];
    u8 pad130[0x144 - 0x130];
    W9Obj144 *x144;
    W9Obj148 *x148;
    u8 pad14c[0x164 - 0x14C];
    W9U x164;
    u8 pad168[0x1CC - 0x168];
    s32 x1cc;
    u8 pad1d0[0x1F0 - 0x1D0];
    f32 x1f0[4];
    u8 pad200[0x370 - 0x200];
    union { u64 x; struct { u64 lo:44; u64 b44:1; u64 hi:19; } b; } x370;
    s32 x378;
    u8 pad37c[0x3B0 - 0x37C];
    f32 x3b0;
    f32 x3b4;
    f32 x3b8;
    f32 x3bc;
    f32 x3c0[4];
    u8 pad3d0[0x45C - 0x3D0];
    f32 x45c;
    u8 pad460[0x470 - 0x460];
    u64 x470;
    u8 pad478[0x490 - 0x478];
    f32 x490[4];
    void *x4a0;
} W9Ent;
#include "data/types/text_00140000_h9_p.h"
#include "data/pieces/D_00350D88.h"
#include "data/types/text_00140000_h9.h"
void func_00267560(void *out, void *in, f32 s);
void func_00130398(W9Ent *e, f32 s, s32 n);
void func_00267518(void *out, void *a, void *b);
void func_002675a8(void *dst, void *src);
f32 func_00120c18(void *v);
typedef struct {
    union {
        s32 w;
        struct { s8 b0; u8 b1; u8 b2; u8 b3; } b;
        struct { u32 lo:16; u32 f16:1; u32 f17:1; u32 f18:1; u32 hi:13; } f;
    } h;
    u8 pad4[0x24 - 4];
    char name[0x20];
    s32 x44;
} W9Blk;
W9Blk D_005512A0[0xc] ALIGNED(32);

s32 func_00137618(void);
s32 func_0014d180(W9Ent *e) {
    s32 r;
    s32 f, g;
    r = func_00137618();
    if (r) {
        f = e->flags;
        g = f & 4;
        if ((f & 0x10000) && e->x3b0 < 15.0f) return 0;
        r = 0;
        if (e->x3b8 == 0.0f || e->x3b8 + 6.0f < e->x3b0) r = g == 0;
    }
    return r;
}

extern u32 D_002C5958;
s32 func_001443a8(W9Ent *e);
s32 func_0014db20(W9Ent *e);
s32 func_0014d330(W9Ent *e, s32 a1) {
    s32 f;
    if (a1 == 0 && func_001443a8(e) == 0) {
        f = e->flags;
        if (!(f & 0x1000)) goto L;
    }
    if ((D_002C5958 >> 5) & 1) {
        if (func_0014db20(e)) {
            e->flags &= ~4;
            return 8;
        }
    }
    return e->x70;
L:
    return (f & 0x2000) ? 6 : 0;
}

extern W9Tab12 D_00350D30[];
extern s32 D_002BC128;
extern s32 D_002BC130;
W9Tab12 *func_0014dab8(void) {
    W9Tab12 *p;
    for (p = D_00350D30; p->a >= 0; p++) {
        if (p->a == D_002BC128 && p->b == D_002BC130) return p;
    }
    return 0;
}

W9Tab12 *func_0014dab8(void);
s32 func_0014db20(W9Ent *e) {
    W9Tab12 *p;
    if (e->x148) {
        p = func_0014dab8();
        if (p && e->x10[1] > p->f4) return 1;
    }
    return 0;
}

void func_0014db78(W9Ent *e, f32 *v) {
    f32 t[4];
    func_00267560(t, v, v[3]);
    func_00267518(t, e->x3c0, t);
    {
        f32 len = func_00120c18(t);
        if (16.0f < len) func_00267560(t, t, 16.0f / len);
    }
    e->x3c0[0] = t[0];
    e->x3c0[2] = t[2];
}

void func_0014dc08(W9Ent *e) {
    e->x6c->xcc.f = 0.06981316208839417f;
    e->x1cc &= ~1;
    func_00267560(e->x3c0, e->x3c0, 0.29999998211860657f);
    if (e->x148) e->x148->x100 &= ~((u64)1 << 34);
}

void func_00147338(s32 a, s32 b);
void func_0014dc90(W9Ent *e) {
    e->x6c->xcc.f = 0.19634954631328583f;
    e->x1cc |= 1;
    func_00147338(17108, e->x4 + 1);
}

void func_0014cc88(W9Ent *e, f32 s);
void func_0014e3a0(W9Ent *e) {
    f32 s = 12.0f;
    func_00267560(e->x3c0, e->x3c0, 0.7f);
    func_0014cc88(e, s);
    func_00130398(e, s, 6);
}

s32 func_0014ee08(f32 *lo, f32 *hi, f32 *box) {
    s32 r = 0;
    if (hi[0] >= box[4] && lo[0] <= box[8] &&
        hi[1] >= box[5] && lo[1] <= box[9] &&
        hi[2] >= box[6] && lo[2] <= box[10]) r = 1;
    return r;
}

void *func_00134928(void *a);
void func_001350d0(void *p);
void func_0014f3d0(void *a) {
    void *p;
    while ((p = func_00134928(a)) != 0) func_001350d0(p);
}

typedef void (*W9Fn)(W9Ent *);
s32 func_0014f658(W9Ent *e, s32 s) {
    s32 old = e->x70;
    if (old != s) {
        e->x378 = old;
        e->x70 = s;
        e->flags |= 0x400;
        if (D_00350D88[old].f8) ((W9Fn)D_00350D88[old].f8)(e);
        if (D_00350D88[s].f4) ((W9Fn)D_00350D88[s].f4)(e);
        return 1;
    }
    return 0;
}

void func_0014f9b0(W9Ent *e, f32 *src, f32 t) {
    func_002675a8(e->x1f0, src);
    if (0.0f < t) {
        e->x1f0[3] = 0.0f;
        e->x45c = 1.0f / t;
    } else {
        e->x45c = 0.0f;
        e->x1f0[3] = 1.0f;
    }
    e->x470 |= (u64)1 << 33;
}

void func_0014fa38(W9Ent *e, f32 t) {
    if ((s32)(e->x470 >> 33) & 1) {
        if (0.0f < t) {
            e->x470 |= (u64)1 << 33;
            e->x45c = -e->x1f0[3] / t;
        } else {
            e->x470 &= ~((u64)1 << 33);
        }
    }
}

#include "data/pieces/D_002E26A0.h"

typedef struct {
    u8 pad0[8];
    u8 *x8;
    u8 padc[0x55 - 0xC];
    s8 x55;
} W9Obj55;
typedef struct {
    u8 pad0[0x14];
    W9Obj55 *x14;
    s32 x18;
} W9Task;
W9Task *func_0011f090(void *q, s32 a, void (*fn)(void));

/* needs make: uses rodata */
s32 func_0014f600(W9Ent *e) {
    switch (e->x70) {
    case 2:
    case 11:
    case 16:
    case 17:
    case 19:
    case 20:
    case 22:
        return 1;
    }
    return (D_00350D88[e->x70].f0 & 3) == 1;
}
#include "data/bss_0055_mixed.h"
#include "data/data_002B.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BC128.h"
#include "data/pieces/D_00350D30.h"
