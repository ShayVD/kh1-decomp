/* Objects the player touches, default flags (docs/modules.md "Session
 * 52"): the contact handlers (func_0015a8f0 / func_0015a990 with their
 * tables D_00351AA0 / D_00351AB0, func_0015aa30, func_0015ab50 tests the
 * player's distance) and their motions.  The rest is in objtouch.nostrict.c.
 * Read from the code, not proved by a boot. */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350CE0.h"
#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E26A0.h"

/* func_0015a470 (from auto/text_00150000_3.c). */
M2C_UNK func_00176310(s32);
s32 func_0015a470(void *arg0, s32 arg1, s32 arg2) {
    if (arg2 == -2) {
        func_00176310(M2C_FIELD(arg0, s32 *, 0x144));
    }
    return 0;
}

/* func_0015a498 (from auto/text_00150000_3.c). */
s32 func_001354b8(s32, s32);
s32 func_001477e0(s32);
s32 func_0014a4a8(s32, s32, s32);
void func_001315c0(s32, s32, s32, f32);
s32 func_0015a498(Actor *arg0, s32 arg1) {
    s32 temp_v0;

    if (arg0->unk008 != 0) {
        temp_v0 = func_0014a4a8(arg0, 0, func_001477e0(arg1));
        func_001315c0(arg0, 0x8003, temp_v0 + 0x10, 0.0f);
        func_001354b8(temp_v0, arg0->unk008);
        arg0->unk000 = (s32) (arg0->unk000 | 0x20);
        return 1;
    }
    return 0;
}

/* func_0015a520 (from hand/text_00150000_h10.c). */
extern s32 D_0029B418;
void func_00147ed8(s32, s32, s32, void *);
void func_00135800(void *, f32, f32);
#define func_001315c0 ((void (*)(void *, s32, void *, f32)) func_001315c0)
s32 func_0015a520(u32 *a, s32 b) {
    u8 buf[16];
    f32 z;
    if (*a & 8) return 0;
    z = 0.0f;
    func_001315c0(a, 0x8003, buf, z);
    func_00147ed8(D_0029B418, b, 20000, buf);
    func_00135800(a, z, 8.0f);
    *a |= 0x68;
    return 1;
}
#undef func_001315c0

/* func_0015a8f0 (from hand/text_00150000_h10.c). */
typedef struct { u8 pad[0x18]; f32 f18; f32 x, y, z; u8 pad28[0x20]; s16 h48; u8 pad4a[2]; u16 h4C; } Sub130;
typedef struct { u8 pad[0x130]; Sub130 *p130; } Act130;
typedef struct { s32 w0; Act130 *w4; } Node15A;
extern u8 D_00351AA0[];
void func_0015a758(void *, void *);
Node15A *func_00134928(void *);
void func_001350d0(Node15A *);
void func_0015aa30(Act130 *a, Act130 *b);
#define func_0015a498 ((s32 (*)(void *, s32)) func_0015a498)
void func_0015a8f0(void *a) {
    Node15A *p;
    func_0015a758(a, D_00351AA0);
    while ((p = func_00134928(a)) != 0) {
        if (func_0015a520(a, 6)) func_0015aa30(a, p->w4);
        func_001350d0(p);
    }
    if (func_0015a498(a, 23)) func_0015a520(a, 6);
}
#undef func_0015a498

/* func_0015a990 (from hand/text_00150000_h10.c). */
extern u8 D_00351AB0[];
#define func_0015a498 ((s32 (*)(void *, s32)) func_0015a498)
void func_0015a990(void *a) {
    Node15A *p;
    func_0015a758(a, D_00351AB0);
    while ((p = func_00134928(a)) != 0) {
        if (func_0015a520(a, 6)) func_0015aa30(a, p->w4);
        func_001350d0(p);
    }
    if (func_0015a498(a, 24)) func_0015a520(a, 3);
}
#undef func_0015a498

/* func_0015aa30 (from hand/text_00150000_h10.c). */
typedef struct { u8 pad[8]; u8 e[3][2]; } Tbl144;
void *func_00144e88(s32);
s32 func_00122ff8(Act130 *);
void func_00150d30(s32, s32);
void func_0015aa30(Act130 *a, Act130 *b) {
    Tbl144 *t = func_00144e88(a->p130->h48);
    s32 i;
    for (i = 0; i < 3; i++) {
        u8 c = t->e[i][0];
        if (c) {
            func_00150d30(c, func_00122ff8(b) ? b->p130->h4C : 12);
        }
    }
}

/* func_0015aac0 (from hand/text_00150000_h10.c). */
void func_00146188(s32, f32 *, s32);
s32 func_0015aac0(Sub130 *a) {
    u8 *t = func_00144e88(a->h48);
    s32 i;
    f32 v[4];
    for (i = 0; i < 7; i++) {
        if (t[i]) {
            v[0] = a->x;
            v[1] = a->y;
            v[2] = a->z;
            v[3] = 1.0f;
            func_00146188(i, v, 2);
            return 1;
        }
    }
    return 0;
}

/* func_0015ab50 (from auto/text_00150000_17.c). */
M2C_UNK func_001247e8(void *);
M2C_UNK func_00267530(void *, s32, s32);
f32 func_00120bf8(void *);
#define func_0015aa30 ((M2C_UNK (*)(void *, s32)) func_0015aa30)
#define func_00122ff8 ((s32 (*)(s32)) func_00122ff8)
void func_0015ab50(void *arg0) {
    s32 sp[4];
    s32 temp_s0;

    temp_s0 = (*(s32 *)&D_002E26A0);
    if (func_00122ff8(temp_s0) != 0) {
        func_00267530(sp, arg0 + 0x10, temp_s0 + 0x10);
        if (func_00120bf8(sp) < M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), f32 *, 0x44)) {
            func_0015aa30(arg0, temp_s0);
            func_001247e8(arg0);
        }
    }
}
#undef func_0015aa30
#undef func_00122ff8

/* func_0015abd0 (from auto/text_00150000_21.c). */
s32 func_00130340(s32, s32, f32);
s32 func_00130578(s32, s32, f32);
void func_001373f8(s32, f32);
void func_0015abd0(s32 arg0) {
    func_001373f8(arg0, 12.0f);
    *(M2C_UNK *)arg0 = (s32) (*(M2C_UNK *)arg0 | 0x100000);
    func_00130340(arg0, 0x010000DC, 0.0f);
    func_00130578(arg0, 0x40000000, 8.0f);
}

/* func_0015ac30 (from auto/text_00150000_16.c). */
void func_0015ac30(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x3C0) = (f32) (M2C_FIELD(arg0, f32 *, 0x30) * 4.0f);
    M2C_FIELD(arg0, f32 *, 0x3C8) = (f32) (M2C_FIELD(arg0, f32 *, 0x38) * 4.0f);
}

/* func_0015ac58 (from hand/text_00150000_h10.c). */
typedef struct { u8 pad[0xC]; void *cb; } Task;
typedef struct { u32 flags; u8 pad[0x3BC]; u8 x3C0[4]; } Obj15A;
void func_00130398(void *, s32, f32);
void func_0014cce0(void *, f32);
void func_002675a8(void *, void *);
#define func_00130578 ((Task *(*)(void *, s32, f32)) func_00130578)
void func_0015ac58(Obj15A *a) {
    f32 z = 0.0f;
    func_00130398(a, 0x10000DC, z);
    func_00130578(a, 0x40000006, 8.0f)->cb = func_0015ac30;
    func_0014cce0(a, z);
    a->flags &= ~0x400;
    func_002675a8(a->x3C0, &D_002C58B0);
}
#undef func_00130578

/* func_0015ace0 (from auto/text_00150000_16.c). */
M2C_UNK func_00121eb0(s32);
s32 func_0015ace0(void *arg0, s32 arg1, s32 arg2) {
    if (arg2 == -2) {
        func_00121eb0(M2C_FIELD(arg0, s32 *, 0x144));
    }
    return 0;
}

