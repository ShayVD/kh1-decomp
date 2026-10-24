/* Object class 0x11: the handlers func_00144e38 registers in the class table
 * D_00350D88 (func_0014f830(0x11, ...)) and their helpers. Flag mode:
 * default (the other modes are in the sibling files). Read from the code,
 * not proved by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/bss_0052.h"
#include "data/bss_0053.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/text_00130000_h7.h"
#include "data/pieces/D_00304C70.h"
#include "m2c.h"
#include "actor.h"
#include "data/bss_0054.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_00350D88.h"
#include "data/pieces/D_00304D64.h"

/* func_00144350 (from hand/text_00130000_h7.c). */
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
void func_00144350(W7Ch *o) {
    o->x148.p->xbc = 0;
    o->x148.p->xb0 = 0;
}

/* func_00144368 (from auto/text_00140000.c). */
f32 func_00144368(Actor *arg0) {
    return arg0->unk324 - arg0->unk2D4;
}

/* func_00144378 (from auto/text_00140000_10.c). */
f32 func_00144378(Actor *arg0) {
    return (arg0->unk014 - arg0->unk2D4) - *(f32 *)((s8 *)(s8 *)&D_00304D64 + (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) * 8));
}

/* func_001447a0 (from hand/text_00130000_h7.c). */
void func_0014cc88(W7Ob *o, f32 f);
void func_00267560(f32 *d, f32 *s, f32 f);
extern f32 D_002C5970;
void func_001447a0(W7Ob *o) {
    func_0014cc88(o, 0.0f);
    o->flags &= ~0x400;
    o->x3b0 = 6.0f;
    o->x3b4 -= 8.724489212036133f;
    func_00267560(o->x3c0, o->x200, D_002C5970);
}

/* func_00144ce0 (from auto/text_00140000_10.c). */
M2C_UNK func_00267e90(s32, s32, f32);
extern f32 D_002BBDFC;
void func_00144ce0(s32 arg0, s32 arg1) {
    func_00267e90(arg1, arg0 + 0x20, D_002BBDFC);
}

/* func_00144e38 (from auto/text_00140000_5.c). */
M2C_UNK func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK *);
void func_00144958();
void func_00144d08();
void func_00144e38(void) {
    func_0014f830(0x11, 1, &func_00144350, 0, &func_00144958, &func_00144ce0, 0, 0, &func_00144d08);
}

