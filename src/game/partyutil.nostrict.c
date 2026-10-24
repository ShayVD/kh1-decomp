/* Party helpers: a member's slot by id (func_0013daa8), the leader
 * (func_0013daf8), the per-class callback table D_00350DA4 (func_0013dfb8),
 * whether the party is together (func_0013dd40 sets bit 0 of D_002C5958),
 * and the name table D_00304BF0 (defined here). Flag mode: nostrict (the
 * other modes are in the sibling files). Read from the code, not proved by a
 * boot (docs/modules.md "Session 53"). */
#include "m2c.h"
#include "common.h"
#include "data/bss_0052.h"
#include "data/types/nostrict_text_00130000_h55.h"
#include "data/pieces/D_002E26A0.h"
#include "vm/script_vm.h"

/* func_0013dc10 (from hand/nostrict/text_00130000.c). */
s32 func_00130340(s32, s32, f32);
s32 func_0013dbe0(s32, s32);
s32 func_001477c8(s32);
s32 func_0014a408(void);
s32 func_0014a908(s32, s32, s32);
void func_0012c880(s32, s32);
void func_001487f8(s32, s32, s32, s32);
void func_00157a30(s32, s32, s32);
s32 func_0013dc10(s32 arg0, s32 arg1) {
    s16 temp_v0_2;
    s32 temp_s0;
    s32 temp_v0_3;
    s8 temp_a1;
    s8 temp_a1_2;
    s8 temp_v1;
    void *temp_a0;
    void *temp_v0;

    temp_v0 = func_0013dbe0(arg0, arg1);
    temp_v0_2 = M2C_FIELD(temp_v0, s16 *, 0);
    if (temp_v0_2 >= 0) {
        func_00130340(arg0, temp_v0_2 | 0x01000000, 0.0f);
    }
    temp_s0 = func_0014a408();
    temp_v0_3 = func_0014a908(arg0, temp_s0, func_001477c8(M2C_FIELD(temp_v0, s32 *, 4)));
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x14C), s32 *, 0x2C) = temp_v0_3;
    M2C_FIELD(temp_v0_3, s64 *, 0) = (s64) (M2C_FIELD(temp_v0_3, s64 *, 0) | 0x400000);
    M2C_FIELD(temp_v0_3, u8 *, 0xA8) = (u8) M2C_FIELD(temp_v0, u8 *, 0xC);
    M2C_FIELD(temp_v0_3, u8 *, 0xA9) = (u8) M2C_FIELD(temp_v0, u8 *, 0xD);
    M2C_FIELD(temp_v0_3, u8 *, 0xAA) = (u8) M2C_FIELD(temp_v0, u8 *, 0xE);
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x14C), s32 *, 0x14) != 0) {
        temp_a1 = M2C_FIELD(temp_v0, s8 *, 2);
        if (temp_a1 >= 0) {
            func_0012c880(arg0, (s32) temp_a1);
        }
        temp_a1_2 = M2C_FIELD(temp_v0, s8 *, 3);
        if (temp_a1_2 >= 0) {
            func_001487f8(M2C_FIELD(M2C_FIELD(arg0, void **, 0x14C), s32 *, 0x14), (s32) temp_a1_2, arg0, 0x30);
        }
    }
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x14C), s8 *, 0x28) = (s8) arg1;
    temp_a0 = M2C_FIELD(arg0, void **, 0x14C);
    M2C_FIELD(temp_a0, s32 *, 0x28) = (s32) (M2C_FIELD(temp_a0, s32 *, 0x28) | 0x10000);
    temp_v1 = M2C_FIELD(temp_v0, s8 *, 0xF);
    if (temp_v1 >= 0) {
        func_00157a30(arg0, (s32) temp_v1, 0);
    }
    return (s32) temp_v0;
}

/* func_0013dd40 (from hand/nostrict/text_00130000_h55.c). */
typedef struct { u8 pad[8]; f32 x8; f32 xc; } W55Dim;
typedef struct { u8 pad[0x10]; W55Dim *x10; } W55Mdl;
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0x4c - 0x8]; u16 x4c; u8 pad4e[0x54 - 0x4e]; s8 x54; } W55Inf;
typedef struct { u8 pad[0xcc]; f32 xcc; } W55Mv;
typedef struct { f32 *x0; } W55Fx;
typedef struct Actor_3dd40 {
    u32 x0;
    s32 x4;
    u8 pad08[0x10 - 0x8];
    f32 pos[4];
    f32 x20[4];
    u8 pad30[0x3c - 0x30];
    f32 x3c;
    f32 x40;
    f32 x44;
    u8 pad48[0x6c - 0x48];
    W55Mv *x6c;
    u32 x70;
    u8 pad74[0x98 - 0x74];
    void *x98;
    u8 pad9c[0x120 - 0x9c];
    f32 x120[4];
    W55Inf *x130;
    W55Mdl *x134;
    u8 pad138[0x148 - 0x138];
    f32 *x148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x2c0 - 0x154];
    f32 x2c0;
    f32 x2c4;
    u8 pad2c8[0x2de - 0x2c8];
    u16 x2de;
    u8 pad2e0[0x30c - 0x2e0];
    u16 x30c;
    u8 pad30e[0x316 - 0x30e];
    u16 x316;
    u8 pad318[0x370 - 0x318];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b39:1; u32 hi:24; } b; } x370;
    u8 pad378[0x398 - 0x378];
    s32 x398;
    u8 pad39c[0x3c0 - 0x39c];
    f32 x3c0[4];
    u8 pad3d0[0x444 - 0x3d0];
    s32 x444;
    u8 pad448[0x488 - 0x448];
    W55Fx *x488;
    s32 x48c;
} W55Ob;
extern f32 D_002BBDFC;
extern u32 D_002C5958;
extern f32 D_00304C40;
f32 D_0052AE68 ALIGNED(8);  /* moved from hand/nostrict/text_00130000_h55.c (session 53) */
W55Ob *func_001230a0(W55Ob *p);
f32 func_00267390(f32 *a, f32 *b);
void func_00267530(f32 *d, f32 *a, f32 *b);
void func_0013dd40(void) {
    f32 v[4];
    W55Ob *pl, *p;
    s32 i, near;
    f32 lim;
    u32 *fl = &D_002C5958;
    if (*fl & 0x12010) { *fl |= 1; return; }
    if ((*fl >> 12) & 1) { *fl &= ~1; return; }
    lim = 1440000.0f;
    near = 0;
    for (i = 0; i < 3; i++) {
        pl = D_002E26A0[i];
        if (!pl) continue;
        for (p = 0; (p = func_001230a0(p));) {
            if (p->x370.b.kind != 2) continue;
            func_00267530(v, pl->pos, p->pos);
            v[1] = 0.0f;
            if (func_00267390(v, v) < lim) { near = 1; break; }
        }
    }
    if (D_00304C40 > 0.0f) D_00304C40 -= D_002BBDFC;
    if ((D_002C5958 & 1) != near) {
        if (D_00304C40 > 0.0f) {
            D_00304C40 = 0.0f;
            D_002C5958 = (D_002C5958 & ~1) | near;
        } else if ((D_0052AE68 -= D_002BBDFC) <= 0.0f) {
            D_002C5958 = (D_002C5958 & ~1) | near;
        }
        if ((D_002C5958 & 1) != near) return;
    }
    if (D_002C5958 & 1) D_0052AE68 = 120.0f;
    else D_0052AE68 = 45.0f;
}

