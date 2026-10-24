/* The first handlers of object classes 9 and 0xA (func_0013fd10,
 * func_0013fd20, func_0013fd38, func_0013fd60, registered by func_00141138
 * in class0a.c) and the helpers the class 9 / 0xA / 0xB handlers in class0a
 * call (func_0013fd88, func_0013fe10, func_0013fe28, func_0013fe80,
 * func_0013ff00). Flag mode: nostrict (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "common.h"
#include "data/bss_0052.h"
#include "data/types/nostrict_text_00130000_h55.h"
#include "data/pieces/D_002E26A0.h"
#include "vm/script_vm.h"

/* func_0013fe28 (from hand/nostrict/text_00130000_h55.c). */
typedef struct { u8 pad[8]; f32 x8; f32 xc; } W55Dim;
typedef struct { u8 pad[0x10]; W55Dim *x10; } W55Mdl;
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0x4c - 0x8]; u16 x4c; u8 pad4e[0x54 - 0x4e]; s8 x54; } W55Inf;
typedef struct { u8 pad[0xcc]; f32 xcc; } W55Mv;
typedef struct { f32 *x0; } W55Fx;
typedef struct Actor_3fe28 {
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
f32 func_0013fe10();
/* uses rodata. func_001401d8 only matches with func_0013fe28 defined above it. */
s32 func_0013fe28(W55Ob *o) {
    f32 t = func_0013fe10(o);
    s32 r = 0;
    if (t < 0.015f || t > 0.985f) r = 1;
    return r;
}

/* func_0013ff00 (from hand/nostrict/text_00130000_h55.c). */
typedef struct Actor_3ff00 {
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
} W55Ob_3ff00;
f32 func_00121550(f32 *o, f32 *a, f32 *d, f32 *p, f32 *v);
void func_00121fc4(f32 *d, f32 *s);
void func_00267530(f32 *d, f32 *a, f32 *b);
void func_00267560(f32 *d, f32 *s, f32 k);
f32 fabsf(f32);
s32 func_0013ff00(W55Ob_3ff00 *o, f32 *seg, f32 *v, f32 *r) {
    f32 d[4], w[4], tmp[4];
    f32 t;
    if (fabsf(seg[1] - seg[5]) > 5.0f) seg += 4;
    func_00267530(d, seg + 4, seg);
    func_00121fc4(d, d);
    t = func_00121550(tmp, seg, d, o->pos, v);
    if (t < 0.0f) {
        if (t < -20.0f) return 0;
        t = 0.0f;
    } else if (d[3] < t) {
        if (d[3] + 20.0f < t) return 0;
        t = d[3];
    }
    func_00267560(w, v, o->x2c0 - 1.0f);
    r[0] = seg[0] + d[0] * t + w[0];
    r[1] = o->pos[1];
    r[2] = seg[2] + d[2] * t + w[2];
    r[3] = 1.0f;
    return 1;
}

