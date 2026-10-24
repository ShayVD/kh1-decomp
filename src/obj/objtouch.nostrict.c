/* Objects the player touches, without strict aliasing (docs/modules.md
 * "Session 52"): func_0015a5b8, func_0015a758, func_0015ad08.  Read from the code, not proved by a boot. */
#include "common.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8_s.h"
#include "platform/math.h"
#include "data/types/nostrict_text_00150000_h58_p.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002E3168.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_002E2780.h"

/* func_0015a5b8 (from hand/nostrict/text_00150000_h58.c). */
typedef S31b0_2e31b0 P8;
typedef struct {
    u32 w0; s32 w4; s32 w8; s32 wC; s32 x10; f32 f14; s32 x18; f32 f1c; s32 x20; u8 pad24[0xc]; V4 v30; f32 f40; f32 f44; s32 x48; s32 x4c;
} S144;
typedef struct {
    u8 pad0[0x10]; V4 pos; u8 pad20[0x10]; V4 v30; u8 pad40[0x30]; s32 x70; u8 pad74[0xf0]; s32 x164;
} S98;
typedef struct { u8 pad0[5]; u8 b5; u8 pad6[0xe]; struct { u8 pad0[1]; u8 b1; } *x14; } S134;
#define ACT_BODY(T144) \
    u32 w0; u8 pad4[4]; s32 x8; u8 padc[4]; V4 pos; V4 x20; V4 x30; V4 x40; u8 pad50[0x18]; s32 x68; struct { u8 pad[0x3c]; s32 x3c; } *x6c; s32 x70; P8 x74; u8 pad7c[0xc]; s32 x88; s32 x8c; u64 x90; S98 *x98; u8 pad9c[0x24]; V4 xc0; f32 xd0[4][4]; u8 pad110[0x10]; V4 x120; \
    struct { u8 pad[0x44]; f32 x44; s16 x48; u8 pad4a[2]; u16 x4c; } *x130; S134 *x134; u8 pad138[0xc]; T144 *x144; \
    struct { u8 pad[0x160]; V4 v160; } *x148; u8 pad14c[0x1d4]; V4 x320; u8 pad330[0x40]; u64 x370; u8 pad378[0x26]; u8 x39e; u8 pad39f[0x11]; f32 x3b0; u8 pad3b4[0xc]; V4 x3c0; u8 pad3d0[0x14]; f32 x3e4; u8 pad3e8[8]; V4 x3f0; s32 x400; u8 pad404[0x9c]; void *x4a0;
typedef struct Actor_5a5b8 { ACT_BODY(S144) } Act;
void func_001315c0(void *, s32, void *, f32);
void func_00267530(void *, void *, void *);
void func_002675a8(void *, void *);
f32 func_00267390(void *, void *);
s32 func_00122ff8(void *);
void *func_00147ed8(s32, s32, s32, void *);
void func_00121fc4(void *, void *);
void func_001247e8(void *);
typedef struct { V4 *v; } E144;
typedef struct { ACT_BODY(E144) } ActY;
extern s32 D_0029B418;
void func_0015a470();
void *func_00147c98(s32, s32, s32);
s32 func_0015a498(ActY *, s32);
/* ---- func_0015a5b8 ---- */
void func_0015a5b8(ActY *a) {
    V4 t;
    V4 d;
    Act *p;
    f32 f;
    E144 *e;
    if (!a->x4a0) a->x4a0 = func_0015a470;
    p = D_002E26A0[0];
    if (!func_00122ff8(p)) return;
    func_00267530(&d, &a->pos, &p->pos);
    d.y = 0.0f;
    func_00121fc4(&d, &d);
    f = func_00267390(&d, &p->x30);
    e = a->x144;
    if (!e) {
        if (!(f > 0.0f && d.w < 10000.0f)) return;
        e = a->x144 = func_00147c98(D_0029B418, 1, 20000);
    }
    if (f < 0.0f && d.w > 2000.0f) {
        func_001247e8(a);
        return;
    }
    func_002675a8(e->v, &a->pos);
    if (func_0015a498(a, 25)) {
        func_001315c0((void *)a->x8, 0x8003, &t, 0.0f);
        t.x = (t.x + a->pos.x) * 0.5f;
        t.z = (t.z + a->pos.z) * 0.5f;
        func_00147ed8(D_0029B418, 2, 20000, &t);
    }
}

/* func_0015a758 (from hand/nostrict/text_00150000_h58.c). */
typedef struct Actor_5a758 { ACT_BODY(S144) } Act_5a758;
void func_00267518(void *, void *, void *);
void func_00267560(void *, void *, f32);
void func_0014f658(void *, s32);
extern f32 D_002BBDFC;
f32 func_00176850(void);
/* ---- func_0015a758 ---- */
void func_0015a758(Act_5a758 *a, f32 *prm) {
    V4 d;
    Act_5a758 *p = D_002E26A0[0];
    f32 *dt;
    if (!func_00122ff8(p)) return;
    func_00267530(&d, &a->pos, &p->pos);
    d.y = 0.0f;
    func_00121fc4(&d, &d);
    if (a->x70 == 0) {
        if (d.w < a->x130->x44) {
            func_0014f658(a, 2);
            a->x3c0.x = func_00176850() * prm[2] - prm[2] * 0.5f;
            a->x3c0.y = 0.0f;
            a->x3c0.z = func_00176850() * prm[2] - prm[2] * 0.5f;
            a->x3b0 = 0.0f;
        }
    } else {
        if (func_00267390(&d, &p->x30) < 0.0f && d.w > 2000.0f) {
            func_001247e8(a);
            return;
        }
        dt = &D_002BBDFC;
        a->x20.x = 0.0f;
        a->x20.y = 1.0f;
        a->x20.z = 0.0f;
        a->x3b0 += prm[0] * *dt;
        if (prm[1] <= a->x3b0) a->x3b0 = prm[1];
        a->x20.w = a->x3b0;
        func_00267560(&d, &a->x3c0, *dt);
        func_00267518(&a->x30, &a->x30, &d);
    }
}

/* func_0015ad08 (from hand/nostrict/text_00140000_s6_07.c). */
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
void *func_00121e28(s32, void *);
void func_0015ace0(void);
s32 func_001477e0(s32);
Oad08 *func_0014a4a8(Aad08 *, s32, s32);
void * func_001354b8(Oad08 *, s32);
f32 func_00120c88(f32);
void func_00142388(f32 *, f32 *);
void func_00142470(Aad08 *, f32 *);
#define func_002675a8 ((void (*)(f32 *, f32 *)) func_002675a8)
#define func_001315c0 ((void (*)(Aad08 *, s32, f32, f32 *)) func_001315c0)
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
#undef func_002675a8
#undef func_001315c0

