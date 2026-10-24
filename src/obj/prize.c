/* Prizes, the HP / MP balls and munny an enemy drops (a guess from the
 * code): the drop table of an object (func_00144e88, func_00144eb0 spawns
 * d->cnt[i] of each of 7 kinds), the 0x3000-byte pool D_0052EB60 with its
 * per-prize records D_0035C710 and free list D_0052EB50 / D_0052EB58
 * (func_00146188 spawns one, func_00145ce8 updates one), the ground probe
 * D_00531B60, the drop rate D_00306844 / D_00306848, and an object's
 * attached effect (func_00145188, func_00145240). Flag mode: default (the
 * other modes are in the sibling files). Read from the code, not proved by a
 * boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/bss_0052.h"
#include "data/bss_0053.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/text_00130000_h7.h"
#include "data/pieces/D_00304C70.h"
#include "data/bss_0054.h"
#include "vm/script_vm.h"
#include "data/types/text_00140000_h8.h"
#include "data/pieces/D_0035C710.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_00350CE8.h"
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00304BE8.h"

/* func_00145008 (from hand/text_00130000_h7.c). */
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
void func_001315c0(W7Ch *o, s32 k, void *buf, f32 f);
void func_00144eb0(s32 v, void *buf);
void func_00145008(W7Ch *o, s32 k) {
    u8 buf[16];
    s32 v;
    if (D_00531B64) return;
    switch (k) {
    case 0:
        v = o->info->x48;
        break;
    case 1:
        v = o->info->x4a;
        break;
    default:
        return;
    }
    func_001315c0(o, 0x8003, buf, 0.0f);
    func_00144eb0(v, buf);
}

/* func_00145138 (from hand/text_00140000_h8.c). */
typedef struct W8Node { u8 pad[8]; struct W8Node *next; u8 pad2[10]; u8 x16; u8 p17; f32 x18; } W8Node;
extern W8Node *D_0052EB58;
void func_00150d70(void);
void func_00145138(void) {
    W8Node *n;
    for (n = D_0052EB58; n; n = n->next) { n->x16 = 3; n->x18 = 12.0f; }
    func_00150d70();
}

/* func_00145240 (from auto/text_00140000_4.c). */
M2C_UNK func_0011d350(M2C_UNK, s32);
f32 func_00176310(s32);
void func_00145240(Actor *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), s32 *, 0x154);
    if (temp_v1 != 0) {
        func_00176310(temp_v1);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), s32 *, 0x154) = 0;
        func_0011d350(0xA8, arg0->unk004 + 1);
    }
}

/* func_001464a0 (from auto/text_00140000_2.c). */
extern f32 D_00306844;
s32 func_001464a0(void *arg0) {
    return ((s32) ((f32) M2C_FIELD(arg0, s32 *, 4) * D_00306844) * 5) + ((s32) ((f32) M2C_FIELD(arg0, s32 *, 8) * D_00306844) * 0x14) + (s32) ((f32) M2C_FIELD(arg0, s32 *, 0) * D_00306844);
}

/* func_00146508 (from hand/text_00140000_h8.c). */
extern s32 D_00304E3C;
extern u8 D_0052EB50[];
extern u8 D_0052EB60[];
void func_00176340(s32);
void func_0011efa8(void *, void *, s32, s32);
void func_00146508(void) {
    s32 i;
    if (D_00304E3C) { func_00176340(D_00304E3C); D_00304E3C = 0; }
    func_0011efa8(D_0052EB50, D_0052EB60, 48, 256);
    for (i = 0; i < 256; i++) D_0035C710[i].u.b.f8 = 0;
}

/* func_00146590 (from hand/text_00140000_h8.c). */
void func_001460b8(void);
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
s32 func_00148e20(void);
s32 func_0014dab8(void);
extern s32 D_00531B68;
void func_00146590(void) {
    func_00146508();
    if (!func_0011ef38(func_001460b8)) func_0011ef10(0x17318, func_001460b8);
    D_00304E3C = func_00148e20();
    D_00531B64 = 0;
    D_00531B68 = func_0014dab8();
}

/* func_00146600 (from hand/text_00140000_h8.c). */
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0x144-8]; s32 x144; u8 pad148[0x376-0x148]; u16 x376; } W8Obj;
void func_0012bce0(s32, s32, s32, void *, s32);
void func_00146600(W8Obj *a, s32 b) {
    s32 buf[2];
    s64 t = (s32)a->x376;
    if ((s32)t & 1) {
        if (a->x144) { buf[0] = (s32)&b; buf[1] = 4; func_0012bce0(a->x144, 0, 1, buf, 0); }
    } else func_001c48c8(a->x4, 2, (s32 *)b);
}

/* func_00146678 (from hand/text_00140000_h8.c). */
typedef struct { u8 pad[4]; void *x4; s32 x8; } W8Ent78;
extern u32 D_002C5958;
W8Ent78 *func_00134928(void *);
void func_001350d0(W8Ent78 *);
void func_00146678(void *a, void (*cb)(void *, W8Ent78 *)) {
    W8Ent78 *e;
    while ((e = func_00134928(a)) != 0) {
        if (!((D_002C5958 >> 20) & 1)) {
            if (e->x8 > 0 || e->x4 == D_002E26A0[0]) cb(a, e);
        }
        func_001350d0(e);
    }
}

/* func_00146718 (from hand/text_00140000_h8.c). */
s32 func_0012ba98(s32);
void func_00146718(W8Obj *a) {
    s64 t;
    func_00146678(a, (void *)func_00146600);
    t = (s32)a->x376;
    if ((s32)t & 1) {
        if (a->x144 && func_0012ba98(a->x144) < 0) a->x144 = 0;
    }
}

/* func_00146778 (from hand/text_00140000_h8.c). */
typedef struct {
    union { u64 x; struct { u64 b0:1; u64 b1:1; u64 b2:1; u64 b3:1; u64 f4:1; u64 r:59; } b; struct { u32 w0; s32 x4; } w; } f;
    u16 x8; u16 xa; s32 xc; u8 x10[16];
} W8S78;
void func_0011d2d0(s32, s32, s32);
void func_00146778(W8S78 *p, s32 v) {
    if (((s32)(p->f.x >> 4) & 1) != v) {
        func_0011d2d0(p->x8, p->f.w.x4, v);
        p->f.b.f4 = v;
    }
}

