#include "common.h"
#include "data/bss_0052.h"
#include "data/bss_0053.h"
/* Hand-matched functions near 0x13C000-0x145000 (worker 7). */
void *memcpy(void *, const void *, u32);

typedef struct {
    u8 pad00[8];
    union {
        u32 *p;
        u32 v;
    } u;
} W7Stack;

u32 func_0013cf28(W7Stack *q, void *dst) {
    u32 n = *--q->u.p;
    q->u.p -= n >> 2;
    memcpy(dst, q->u.p, n);
    return n;
}

u32 func_0013cfc0(W7Stack *q) {
    u32 n = *--q->u.p;
    q->u.p -= n >> 2;
    return n;
}

typedef struct {
    u8 pad00[0x48];
    s16 x48;
    s16 x4a;
    u16 x4c;
    u8 pad4e[0x54 - 0x4E];
    s8 x54;
    u8 pad55[0x5D - 0x55];
    u8 x5d;
} W7Info;

typedef struct Actor W7Obj;
struct Actor {
    u32 flags;
    u8 pad004[0x130 - 0x4];
    W7Info *info;
    u8 pad134[0x398 - 0x134];
    W7Obj *x398;
};

#include "data/pieces/D_002E26A0.h"

#include "data/types/text_00130000_h7.h"

#include "data/pieces/D_00304C70.h"

typedef St6C_304c70 W7Lv;

typedef struct {
    u8 pad00[0x6C];
    union {
        W7Lv *p;
        s16 h;
    } x6c;
} W7Pl;

void func_00141468(W7Pl *o, s32 v);

typedef struct {
    u8 pad[0xE4];
} W7Fx;

W7Fx D_0052AE98[32] ALIGNED(8);

typedef unsigned int u128 __attribute__((mode(TI)));

typedef struct {
    u8 pad00[0x5C];
    s32 x5c;
    u8 pad60[0x90 - 0x60];
    s32 x90;
    s32 x94;
    u8 pad98[0xB0 - 0x98];
    s32 xb0;
    u8 padb4[0xBC - 0xB4];
    s32 xbc;
} W7Ai;

typedef struct W7Ch W7Ch;
struct W7Ch {
    u32 flags;
    f32 x4[4];
    f32 x14;
    u8 pad018[0x70 - 0x18];
    s32 x70;
    u8 pad074[0x130 - 0x74];
    W7Info *info;
    u8 pad134[0x148 - 0x134];
    union {
        W7Ai *p;
        s32 i;
    } x148;
    u8 pad14c[0x2CC - 0x14C];
    s32 x2cc;
    u8 pad2d0[0x2D4 - 0x2D0];
    f32 x2d4;
    u8 pad2d8[0x2DC - 0x2D8];
    union {
        u16 h;
        s32 i;
    } x2dc;
    u8 pad2e0[0x360 - 0x2E0];
    s32 x360;
    u8 pad364[0x370 - 0x364];
    u64 x370;
    u8 pad378[0x398 - 0x378];
    W7Ch *x398;
};

f32 func_00144368(W7Ch *o);

typedef struct {
    f32 f;
    s32 pad;
} W7F8;
extern W7F8 D_00304D60[];
#include "data/bss_0052_mixed.h"
#include "data/data_0030.h"
