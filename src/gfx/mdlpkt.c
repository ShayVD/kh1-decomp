/* Model packets (a guess at the name), 0x00108900-0x00109268: the packet
 * templates D_0048C630 / D_0048C690 copied into a model's blocks
 * (func_00108900, func_00108a60), the VIF1 chain restarts (func_00108d90),
 * the draws through the frame's draw list (func_0015ed80), and image
 * uploads (func_001090e8, func_00109180). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "platform/thread.h"
#include "platform/gs.h"
#include "data/pieces/D_002A624C.h"
#include "data/bss_0049.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_002A6274.h"
#include "data/types/text_00100000_h1.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002A3F50.h"
#include "data/pieces/D_002A6208.h"
#include "data/pieces/D_002A6C10.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_0048C6F0.h"
#include "data/bss_004D.h"
#include "data/types/text_00100000_h2.h"
#include "data/pieces/D_002B677C.h"
#include "data/pieces/D_002B6778.h"
#include "data/types/text_00100000_h2_p.h"
#include "data/pieces/D_002B75A0.h"
#include "data/pieces/D_002BD118.h"
#include "vm/script_vm.h"
#include "data/types/text_00100000_h2_p2.h"
#include "m2c.h"
#include "data/pieces/D_002A3F48.h"
#include "data/pieces/D_002C5968.h"
#include "data/pieces/D_002B7590.h"
#include "data/pieces/D_002BBAA0.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "data/pieces/D_002A6C60.h"
#include "data/pieces/D_0037A378.h"
#include "data/types/text_00100000_h28.h"
#include "data/pieces/D_002BC0C0.h"
#include "data/pieces/D_002A6234.h"
#include "data/types/text_00100000_h28_p.h"
#include "data/pieces/D_002B1C60.h"
#include "data/pieces/D_002AA060.h"
#include "data/pieces/D_002A62B0.h"
#include "data/pieces/D_002A3F60.h"
#include "data/pieces/D_002A4060.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002A3E20.h"
#include "data/pieces/D_002A3F30.h"
#include "data/pieces/D_002A62D0.h"
#include "data/pieces/D_002BBDE4.h"

/* func_00108900 (from hand/text_00100000_h1.c). */
typedef struct { u8 pad[16]; s32 w16, w20, w24, w28; u8 pad2[80]; s32 w112, w116, w120, w124; } Blk128;
extern s32 D_0048BFD0[2];
void func_00108900(Blk128 *o, s32 unused, s32 *a, s32 *b) {
    a[0] = b[0] = D_0048BFD0[0];
    a[1] = b[1] = D_0048BFD0[1];
    o->w16 = D_0048C630.x10;
    o->w20 = (s32)a;
    o->w24 = D_0048C630.x18;
    o->w28 = D_0048C630.x1c;
    o->w112 = D_0048C690.x10;
    o->w116 = (s32)b;
    o->w120 = D_0048C690.x18;
    o->w124 = D_0048C690.x1c;
}

/* func_00108970 (from hand/text_00100000_h2.c). */
typedef struct {
    s32 v[2][24];
} SlotRows;
void func_00108970(SlotRows *a, s32 i, s32 j) {
    a->v[i][0] = D_0048C6F0[j].v[0];
    a->v[i][1] = D_0048C6F0[j].v[1];
    a->v[i][2] = D_0048C6F0[j].v[2];
    a->v[i][3] = D_0048C6F0[j].v[3];
}

/* func_001089d0 (from auto/text_00100000_8.c). */
void func_001089d0(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x5C) = 1.0f;
    M2C_FIELD(arg0, f32 *, 0x4C) = 1.0f;
    M2C_FIELD(arg0, f32 *, 0x3C) = 1.0f;
    M2C_FIELD(arg0, f32 *, 0x2C) = 1.0f;
    M2C_FIELD(arg0, f32 *, 0x1C) = 1.0f;
    M2C_FIELD(arg0, f32 *, 0xC) = 1.0f;
}

/* func_001089f8 (from auto/text_00100000_3.c). */
void func_001089f8(s32 arg0, s32 arg1) {
    s32 var_a2;
    void *var_a0;

    var_a0 = arg0 + 0x4C;
    var_a2 = 1;
    do {
        var_a2 -= 1;
        M2C_FIELD(var_a0, s32 *, -0x1C) = (s32) M2C_FIELD(arg1, s32 *, 0x80);
        M2C_FIELD(var_a0, s32 *, -0x18) = (s32) (M2C_FIELD(arg1, s32 *, 0x84) + arg1);
        M2C_FIELD(var_a0, s32 *, -0x14) = (s32) M2C_FIELD(arg1, s32 *, 0x88);
        M2C_FIELD(var_a0, s32 *, -0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x8C);
        M2C_FIELD(var_a0, s32 *, -0xC) = (s32) M2C_FIELD(arg1, s32 *, 0x90);
        M2C_FIELD(var_a0, s32 *, -8) = (s32) (M2C_FIELD(arg1, s32 *, 0x94) + arg1);
        M2C_FIELD(var_a0, s32 *, -4) = (s32) M2C_FIELD(arg1, s32 *, 0x98);
        M2C_FIELD(var_a0, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0x9C);
        var_a0 += 0x60;
    } while (var_a2 >= 0);
}

/* func_00108a60 (from auto/text_00100000_9.c). */
extern s32 D_00472150[];
#define func_00108900 ((void (*)(s32, s32, s32, s32)) func_00108900)
#define func_00108970 ((void (*)(s32, s32, s32)) func_00108970)
void func_00108a60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_a1;
    s32 var_s3;
    void *var_s0;

    M2C_FIELD(arg2, s32 *, 0x20) = D_0048C630.x20.v[0];
    var_s0 = arg2 + 0x5C;
    M2C_FIELD(arg2, s32 *, 0x24) = D_0048C630.x20.v[1];
    M2C_FIELD(arg2, s32 *, 0x28) = D_0048C630.x20.v[2];
    M2C_FIELD(arg2, s32 *, 0x2C) = D_0048C630.x20.v[3];
    M2C_FIELD(arg2, s32 *, 0x80) = D_0048C690.x20.v[0];
    M2C_FIELD(arg2, s32 *, 0x84) = D_0048C690.x20.v[1];
    M2C_FIELD(arg2, s32 *, 0x88) = D_0048C690.x20.v[2];
    M2C_FIELD(arg2, s32 *, 0x8C) = D_0048C690.x20.v[3];
    func_00108900(arg2, arg0, arg3, arg4);
    var_s3 = 0;
    do {
        temp_a1 = var_s3;
        var_s3 += 1;
        func_00108970(arg2, temp_a1, arg1);
        M2C_FIELD(var_s0, s32 *, -0xC) = (s32) D_00472150[0];
        M2C_FIELD(var_s0, s32 *, -8) = (s32) D_00472150[1];
        M2C_FIELD(var_s0, s32 *, -4) = (s32) D_00472150[2];
        M2C_FIELD(var_s0, s32 *, 0) = (s32) D_00472150[3];
        var_s0 += 0x60;
    } while (var_s3 < 2);
}
#undef func_00108900
#undef func_00108970

/* func_00108b60 (from hand/text_00100000_h2.c). */
typedef struct {
    u8 pad[0x30];
    s32 w[8];
    u8 pad2[0x10];
} Slot60;
typedef struct {
    Slot60 e[2];
    void *owner;
} SlotObj;
typedef struct {
    u8 pad[0x80];
    s32 h[8];
} SlotHdr;
extern s32 D_00351BD0;
/* The 0xd0-byte object of func_00108b60/func_00108cf8 (two 0x60 slots,
 * owner at +0xc0), seen as rows of s32. */
void func_00108b60(SlotHdr *h, SlotObj *o) {
    o->e[D_00351BD0].w[0] = h->h[0];
    o->e[D_00351BD0].w[1] = h->h[1] + (s32)h;
    o->e[D_00351BD0].w[2] = h->h[2];
    o->e[D_00351BD0].w[3] = h->h[3];
    o->e[D_00351BD0].w[4] = h->h[4];
    o->e[D_00351BD0].w[5] = h->h[5] + (s32)h;
    o->e[D_00351BD0].w[6] = h->h[6];
    o->e[D_00351BD0].w[7] = h->h[7];
    o->owner = h;
}

/* func_00108be8 (from hand/text_00100000_h2.c). */
typedef struct {
    s32 pad[2];
    s32 a[16];
    s32 b[16];
} MatPair;
extern s32 D_002BC170[4][4];
void func_00108be8(s32 unused, s32 m[4][4], MatPair *d) {
    s32 i, j, k = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            d->a[k] = m[i][j];
            d->b[k] = D_002BC170[i][j];
            k++;
        }
    }
}

/* func_00108c58 (from hand/text_00100000_h2.c). */
void func_00108c58(s32 m[4][4], MatPair *d) {
    s32 i, j, k = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            d->a[k] = m[i][j];
            d->b[k] = D_002BC170[i][j];
            k++;
        }
    }
}

/* func_00108cd0 (from auto/text_00100000.c). */
void func_00108cd0(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s32 *, 0x68) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 0x6C) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 0x70) = (s32) M2C_FIELD(arg1, s32 *, 8);
    M2C_FIELD(arg0, s32 *, 0x74) = (s32) M2C_FIELD(arg1, s32 *, 0xC);
}

/* func_00108cf8 (from hand/text_00100000_h2.c). */
typedef struct {
    u8 pad[0xc0];
    void *owner;
    u8 pad2[0xc];
} Obj_D0;
typedef struct {
    u8 pad[0x90];
} Obj_90;
extern Obj_D0 D_00494D80[];
extern Obj_90 D_00494F20[];
#define func_00108a60 ((void (*)(s32, void *, Obj_D0 *, Obj_90 *, Obj_90 *)) func_00108a60)
#define func_001089f8 ((void (*)(Obj_D0 *, void *)) func_001089f8)
/* The 0xd0-byte object of func_00108b60/func_00108cf8 (two 0x60 slots,
 * owner at +0xc0), seen as rows of s32. */
void func_00108cf8(void *p, s32 i, void *q) {
    D_00494D80[i].owner = p;
    func_00108a60(i, q, &D_00494D80[i], &D_00494F20[i], &D_00494F20[i + 2]);
    func_001089f8(&D_00494D80[i], p);
    func_001089d0(p);
}
#undef func_00108a60
#undef func_001089f8

/* func_00108d90 (from hand/text_00100000_h2.c). */
s32 func_00108d90(void *arg) {
    *(volatile u32 *)0x10009020 = 0;
    *(volatile u32 *)0x10009030 = *(u32 *)((u8 *)arg + 0x10) & 0x0FFFFFFF;
    *(volatile u32 *)0x1000E010 = 2;
    PlatIFlushCache(0);
    *(volatile u32 *)0x10009000 = 0x145;
    return 2;
}

/* func_00108df8 (from auto/text_00100000_14.c). */
extern M2C_UNK D_002AD460;
extern M2C_UNK D_002BC190;
void *func_0015ed80(s32, M2C_UNK *);
void func_00267548(void *, M2C_UNK *, s32);
#define func_00108cd0 ((M2C_UNK (*)(void *, void *)) func_00108cd0)
#define func_00108b60 ((void (*)(s32, void *)) func_00108b60)
#define func_00108c58 ((void (*)(s32, void *)) func_00108c58)
void func_00108df8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
  s32 sp[4];
  s32 temp_s0;
  s32 temp_s1;
  temp_s0 = arg0 * 0xD0;
  func_00267548(sp, &D_002BC190, arg4);
  func_00108b60(arg3, temp_s0 + ((s8 *) (&D_002A6C60)));
  temp_s1 = arg0 * 0x90;
  func_00108c58(arg2, ((D_00351BD0 * 0x2400) + temp_s1) + ((s8 *) (&D_002AD460)));
  func_00108cd0(((D_00351BD0 * 0x2400) + temp_s1) + ((s8 *) (&D_002AD460)), sp);
  *((void **) (((s8 *) func_0015ed80(arg1, &func_00108d90)) + 0x10)) = (void *) ((temp_s0 + (D_00351BD0 * 0x60)) + (&D_002A6C60));
}
#undef func_00108cd0
#undef func_00108b60
#undef func_00108c58

/* func_00108f18 (from hand/text_00100000_h28.c). */
typedef struct { u8 pad[16]; void *p; } Obj10;
extern E90 D_00494F20_00108f18[][2] __asm__("D_00494F20");
#define D_00494F20 D_00494F20_00108f18
extern ED0 D_00494D80_00108f18[] __asm__("D_00494D80");
#define D_00494D80 D_00494D80_00108f18
#define func_0015ed80 ((Obj10 *(*)(s32, void (*)(void))) func_0015ed80)
#define func_00108be8 ((void (*)(s32, s32, E90 *)) func_00108be8)
void func_00108f18(s32 a, s32 b, s32 c) {
    func_00108be8(a, c, &D_00494F20[D_00351BD0][a]);
    func_0015ed80(b, func_00108d90)->p = &D_00494D80[a].e[D_00351BD0];
}
#undef D_00494F20
#undef D_00494D80
#undef func_0015ed80
#undef func_00108be8

/* func_00108fd0 (from hand/text_00100000_h28.c). */
#define func_0015ed80 ((Obj10 *(*)(s32, void (*)(void))) func_0015ed80)
#define func_00108b60 ((void (*)(s32, ED0 *)) func_00108b60)
#define func_00108c58 ((void (*)(s32, E90 *)) func_00108c58)
#define func_00108cd0 ((void (*)(E90 *, s32)) func_00108cd0)
void func_00108fd0(s32 a, s32 b, s32 c, s32 d, s32 e) {
    func_00108b60(d, &D_002AA060[a]);
    func_00108c58(c, &D_002B1C60[D_00351BD0][a]);
    func_00108cd0(&D_002B1C60[D_00351BD0][a], e);
    func_0015ed80(b, func_00108d90)->p = &D_002AA060[a].e[D_00351BD0];
}
#undef func_0015ed80
#undef func_00108b60
#undef func_00108c58
#undef func_00108cd0

/* func_00109180 (from auto/text_00100000_9.c). */
extern M2C_UNK D_002BC210;
void func_00109180(s32 arg0, s16 arg1) {
    PlatGsSetDefLoadImage(&D_002BC210, arg1, 0, 0, 0, 0, 8, 2);
    PlatFlushCache(0);
    PlatGsSyncPath(0, 0);
    PlatGsExecLoadImage(&D_002BC210, arg0);
}

/* func_001091f8 (from auto/text_00100000_12.c). */
void func_001090e8(s32, s32, s32, s32);
#define func_00109180 ((void (*)(s32, s32)) func_00109180)
void func_001091f8(s32 arg0, s32 arg1) {
    func_001090e8(arg0, 0x80, 0xE0, 0x3600);
    func_00109180(arg1, 0x3A00);
}
#undef func_00109180

/* func_00109230 (from auto/text_00100000_12.c). */
#define func_00109180 ((void (*)(s32, s32)) func_00109180)
void func_00109230(s32 arg0, s32 arg1) {
    func_001090e8(arg0, 0x80, 0x30, 0x3A00);
    func_00109180(arg1, 0x3C00);
}
#undef func_00109180

