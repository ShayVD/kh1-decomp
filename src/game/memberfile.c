/* The party members' seven loaded files at D_00720000 (records D_00525368:
 * func_00133628 lays them out from the sizes D_00304318, func_00133000 asks
 * whether a member's file is in), and the small lists D_00525A30. Flag mode:
 * default (the other modes are in the sibling files). Read from the code,
 * not proved by a boot (docs/modules.md "Session 53"). */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0052.h"
#include "vm/script_vm.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_002E31A8.h"
#include "common.h"
#include "data/pieces/D_002A3F3C.h"
#include "data/pieces/D_0029B420.h"
#include "data/types/text_00100000_s7_w4.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/types/text_00130000_h32.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_003044D8.h"

/* func_00132f00 (from auto/text_00130000_4.c). */
extern M2C_UNK D_003042F0;
f32 func_00132f00(void *arg0) {
    return *(f32 *)((s8 *)&D_003042F0 + (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) * 4));
}

/* func_00132f20 (from auto/text_00130000_4.c). */
extern M2C_UNK D_0052536C;
void *func_00132f20(s32 arg0) {
    void *temp_v1;

    temp_v1 = *(M2C_UNK *)((s8 *)&D_0052536C + (arg0 * 0x1C));
    return temp_v1 + M2C_FIELD(temp_v1, s32 *, 8);
}

/* func_00132f48 (from auto/text_00130000.c). */
M2C_UNK func_00147808(s32);
void func_00132f48(s32 arg0) {
    func_00147808(arg0 + 0x11E);
}

/* func_00132f60 (from auto/text_00130000.c). */
void func_00132f60(s32 arg0, s32 arg1) {
    func_00147808((arg0 * 3) + arg1 + 6);
}

/* func_00132f88 (from auto/text_00130000_4.c). */
extern M2C_UNK D_00525368;
#define func_00132f60 ((s32 (*)(s32, s32)) func_00132f60)
s32 func_00132f88(s32 arg0) {
    s32 temp_v1;

    if (((u32) arg0 >= 7U) || (temp_v1 = *(M2C_UNK *)((s8 *)&D_00525368 + (arg0 * 0x1C)), (temp_v1 == 0))) {
        return 0;
    }
    return func_00132f60(arg0, temp_v1);
}
#undef func_00132f60

/* func_00132fe0 (from auto/text_00130000_4.c). */
s32 func_00132fe0(s32 arg0) {
    return *(M2C_UNK *)((s8 *)&D_00525368 + (arg0 * 0x1C));
}

/* func_00133000 (from hand/text_00100000_s7_w4.c). */
typedef struct { u8 pad[0x4c]; u16 f4c; } Info;
typedef struct { u8 pad[0x130]; Info *f130; } Ent;
typedef struct { u8 pad[0x30]; s32 f30; } Q30;
typedef struct { s32 f0; u8 pad[8]; Q30 *fc; u8 pad10[0xc]; } T28;
extern s32 func_00141288(Ent *, s32, s32);
extern T28 D_00525368_00133000[] __asm__("D_00525368");
#define D_00525368 D_00525368_00133000
s32 func_00133000(Ent *o, s32 i) {
    T28 *t = &D_00525368[i];
    Q30 *q;
    if ((D_002E31A8 >> 2) & 1) return 0;
    if (t->f0 == 0) goto r0;
    if (!(q = t->fc)) return 0;
    if (D_00304BE8->f874 & 1) goto r0;
    if ((D_00304BE8->m[o->f130->f4c].bits >> i) & 1) goto call;
r0:
    return 0;
call:
    return func_00141288(o, q->f30, i);
}
#undef D_00525368

/* func_001330c8 (from auto/text_00130000_8.c). */
M2C_UNK func_001763f0(void *);
void func_001330c8(void *arg0) {
    func_001763f0(arg0 + M2C_FIELD(arg0, s32 *, 8));
}

/* func_001330e8 (from hand/text_00130000_h32.c). */
typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xc;
    s32 x10;
    u32 x14;
    void (*x18)(void);
} W32Chan;
extern s32 D_003041F0[][3][3];
s32 func_001477c8(s32 a);
extern W32Chan D_00525368_001330e8[] __asm__("D_00525368");
#define D_00525368 D_00525368_001330e8
#define func_001330c8 ((void (*)(s32 a)) func_001330c8)
void func_001330e8(s32 a, s32 b, s32 key) {
    W32Chan *c = D_00525368;
    s32 i;
    s32 v;
        for (i = 0; i < 7; i++, c++) {
        if (c->x8 == key) break;
    }
    func_001330c8(key);
    c->x4 = key;
    c->xc = func_001477c8(D_003041F0[i][c->x0 - 1][1]);
    c->x10 = D_003041F0[i][c->x0 - 1][2] >= 0 ? func_001477c8(D_003041F0[i][c->x0 - 1][2]) : 0;
    if (c->x18) c->x18();
}
#undef D_00525368
#undef func_001330c8

/* func_001331d8 (from hand/text_00130000_h6.c). */
typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xc;
    s32 x10;
    u32 x14;
    s32 x18;
} W6Chan;
extern s32 D_003041E4[][3][3];
s32 func_00120748(s32 a, s32 b, void (*c)(void), s32 d);
extern W6Chan D_00525368_001331d8[] __asm__("D_00525368");
#define D_00525368 D_00525368_001331d8
s32 func_001331d8(s32 i, s32 j, void (*cb)(void)) {
    W6Chan *c = &D_00525368[i];
    s32 r;
    if (c->x0 == j) {
        if (cb) {
            cb();
        }
        r = -1;
    } else {
        c->x18 = (s32)cb;
        c->x0 = j;
        D_00304BE8->b492[i] = j;
        r = func_00120748(D_003041E4[i][j][0], c->x8, func_001330e8, 0);
    }
    return r;
}
#undef D_00525368

/* func_00133278 (from hand/text_00130000_h6.c). */
typedef struct {
    u8 pad000[0x370];
    u64 x370;
} W6Actor;
typedef struct {
    u8 pad00[0x10];
    W6Actor *actor;
    u8 pad14[0x2C - 0x14];
    s32 x2c;
} W6Task;
extern u32 D_002C5958;
s32 func_0012ba98(s32 a);
s32 func_00133278(W6Task *t) {
    s32 v;
    t->actor->x370 |= 0x80000000000000;
    if ((D_002C5958 >> 14) & 1) {
        return 0;
    }
    v = t->x2c;
    if (v == 0) {
        return 4;
    }
    if (func_0012ba98(v) < 0) {
        t->x2c = 0;
    }
    return 0;
}

/* func_001333e0 (from hand/text_00130000_h32.c). */
typedef struct { s32 x0; s32 off[9]; } W32Hdr;
typedef struct {
    u8 pad000[0x170];
    u64 x170;
} W32Sub;
typedef struct {
    u8 pad000[0x148];
    W32Sub *x148;
} W32Obj2;
typedef struct {
    W32Obj2 *a;
    s32 b;
} W32Pair;
void func_001373f8(W32Obj2 *o, f32 f);
s32 func_001332f0(W32Obj2 *a0, W32Obj2 *a1, s32 a2, void *a3, void *a4, s32 a5, s32 a6);
extern W32Chan D_00525368_001333e0[] __asm__("D_00525368");
#define D_00525368 D_00525368_001333e0
s32 func_001333e0(W32Obj2 *o, s32 i, W32Pair *q) {
    W32Chan *c = &D_00525368[i];
    W32Hdr *h;
    if (c->x0 != 0) {
    if (i == 3 && q->a == o && ((s32)(o->x148->x170 >> 38) & 1)) {
        func_001373f8(o, 0.0f);
    }
    h = (W32Hdr *)c->x4;
    return func_001332f0(o, q->a, q->b, (u8 *)h + h->off[1], (u8 *)h + h->off[0], c->xc, c->x10);
    }
    return 0;
}
#undef D_00525368

/* func_001334b8 (from auto/text_00130000_8.c). */
#define func_001332f0 ((s32 (*)(s32, s32, s32, s32, s32, s32, s32)) func_001332f0)
s32 func_001334b8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_a7;

    temp_a7 = M2C_FIELD(arg0, s32 *, 0x13C);
    return func_001332f0(arg0, arg2, 0, M2C_FIELD(arg0, s32 *, 0x68), temp_a7 + M2C_FIELD(((arg1 * 4) + temp_a7), s32 *, 4), arg3, arg4);
}
#undef func_001332f0

/* func_001334f8 (from auto/text_00130000_8.c). */
M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
extern M2C_UNK D_00525A30;
s32 func_001334f8(void) {
    func_0011f130(&D_00525A30, 0);
    return 0;
}

/* func_00133520 (from auto/text_00130000_8.c). */
M2C_UNK func_0011efa8(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK D_00525430[0x180] ALIGNED(16);  /* moved from auto/text_00130000_8.c (session 53) */
void func_00133520(void) {
    func_0011efa8(&D_00525A30, &D_00525430, 0x30, 0x20);
}

/* func_00133550 (from auto/text_00130000_8.c). */
s32 func_00133550(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK (**)(M2C_UNK), 0x48)(-1);
    return 4;
}

/* func_00133578 (from hand/text_00130000_h32.c). */
typedef struct {
    u8 pad00[0x48];
    void (*x48)(s32);
} W32Proc;
W32Proc *func_001208e0(void (*f)(void));
void func_00133578(void (*cb)(s32)) {
    s32 i;
    s32 n = 0;
    s32 j;
    for (i = 0; i < 7; i++) {
        j = D_00304BE8->b492[i];
        if (j > 0) {
            if (func_001331d8(i, j, 0) >= 0) n++;
        }
    }
    if (n > 0) {
        func_001208e0(func_00133550)->x48 = cb;
    } else {
        cb(-1);
    }
}

/* func_00133628 (from hand/text_00130000_h6.c). */
extern u32 D_00304318[];
extern u8 D_00720000[];
void func_0011ef10(s32 a, void (*b)(void));
extern W6Chan D_00525368_00133628[] __asm__("D_00525368");
#define D_00525368 D_00525368_00133628
void func_00133628(void) {
    s32 p = (s32)D_00720000;
    s32 i;
    for (i = 0; i < 7; i++) {
        D_00525368[i].x8 = p;
        D_00525368[i].x0 = 0;
        D_00525368[i].xc = 0;
        D_00525368[i].x14 = D_00304318[i];
        p += (D_00304318[i] >> 4) << 4;
    }
    func_0011ef10(0x21728, func_001334f8);
    func_00133520();
}
#undef D_00525368

/* func_001336a0 (from auto/text_00130000.c). */
s32 func_001336a0(void) {
    return ((u32) D_002E31A8 >> 1) & 1;
}

/* func_001336b8 (from auto/text_00130000_1.c). */
void func_001336b8(void) {
    D_002E31A8 &= ~2;
}

/* func_001336d8 (from auto/text_00130000.c). */
M2C_UNK func_0012fc58();
M2C_UNK func_0017e7d8();
extern s32 D_002C5958_001336d8 __asm__("D_002C5958");
#define D_002C5958 D_002C5958_001336d8
void func_001336d8(void) {
    func_0012fc58();
    D_002C5958 |= 2;
    func_0017e7d8();
}
#undef D_002C5958

/* func_00133708 (from auto/text_00130000_8.c). */
s32 func_0017e840(void);
extern s32 D_002C5958_00133708 __asm__("D_002C5958");
#define D_002C5958 D_002C5958_00133708
void func_00133708(void) {
    D_002C5958 &= ~2;
    func_0017e840();
}
#undef D_002C5958

