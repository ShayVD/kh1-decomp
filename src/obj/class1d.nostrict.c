/* Object class 0x1D, without strict aliasing (docs/modules.md "Session 52"):
 * the handlers func_00158648 registers in the class table D_00350D88
 * (func_0014f830(0x1D, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class1d.c. Read from
 * the code, not proved by a boot. */
#include "common.h"
#include "data/bss_0055.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/nostrict_text_00150000_h35.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_003519E0.h"
#include "platform/math.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/types/nostrict_text_00150000_h58_p.h"
#include "data/pieces/D_002E31B0.h"

/* func_00157f70 (from hand/nostrict/text_00150000_h35.c). */
void func_002675a8(void *, void *);
typedef struct { u8 pad[0x30]; f32 f30; f32 f34; } S5516E0;
S5516E0 *D_005516E0 ALIGNED(16);
extern u8 D_00351A10[];
extern u8 D_00351A00[];
typedef struct { u8 pad[0xCC]; f32 fCC; } S6C_157f70;
typedef struct { u8 pad[0x6C]; S6C_157f70 *p6C; u8 pad70[0x350]; u8 x3C0[4]; } Obj157f70;
S5516E0 *func_00159ea8(void *, void *, void *);
/* ---- func_00157f70 ---- */
void func_00157f70(Obj157f70 *a) {
    S5516E0 *r = func_00159ea8(a, D_00351A00, D_00351A10);
    S5516E0 **pp = &D_005516E0;
    *pp = r;
    r->f30 = 0.5f;
    (*pp)->f34 = 250.0f;
    a->p6C->fCC = 0.20943951606750488f;
    func_002675a8(a->x3C0, (*(f32 (*)[0x4])&D_002C58A0));
    D_002BC0F0.s2BC0F0.f0 = 10000.0f;
    D_002BC0F0.s2BC0F0.f4 = 4000.0f;
    D_002BC0F0.s2BC0F0.f8 = 64.0f;
    D_002BC0F0.s2BC0F0.fC = 255.0f;
    D_002BC0F0.s2BC0F0.w10 = D_003519E0[0];
    D_002BC0F0.s2BC0F0.w14 = D_003519E0[1];
    D_002BC0F0.s2BC0F0.w18 = D_003519E0[2];
}

/* func_00158100 (from hand/nostrict/text_00150000_h35.c). */
s32 func_00130340(void *, s32, f32);
s32 func_00130578(void *, s32, f32);
typedef struct { u8 pad[0xC]; void *pC; } Task158100;
void func_001580e8(void);
/* ---- func_00158100 ---- */
s32 func_00158100(s32 *a, f32 *v) {
    if (*v > 0.7999999523162842f) {
        func_00130340(a, 0x010000D1, 0.0f);
        func_00130578(a, 0x40000000, 0.0f);
    } else if (*v < -0.7999999523162842f) {
        func_00130340(a, 0x010000D2, 0.0f);
        func_00130578(a, 0x40000000, 0.0f);
    } else {
        *a |= 0x20;
        func_00130340(a, 0x010000D0, 0.0f);
        ((Task158100 *)func_00130578(a, 0x40000000, 0.0f))->pC = func_001580e8;
    }
    return 0;
}

/* func_001581d8 (from hand/nostrict/text_00140000_b04.c). */
typedef struct { u8 pad0[0x20]; f32 x20[4]; u8 pad30[0x164 - 0x30]; s32 x164; } B4A81;
s32 func_00137618(B4A81 *);
s32 func_0014efe0(B4A81 *, s32);
#define func_00130340 ((void (*)(B4A81 *, s32, f32)) func_00130340)
#define func_00130578 ((void (*)(B4A81 *, s32, f32)) func_00130578)
void func_001581d8(B4A81 *e, f32 *v) {
    f32 f;
    s32 i;
    s32 a;
    s32 b;
    if (func_00137618(e)) {
        if (0.7999999523162842f < v[0]) {
            v[0] = 1.0f;
            v[3] = 0.5f;
            v[1] = 0.0f;
            v[2] = 0.0f;
            switch (e->x164) {
            case 0:
                f = v[1];
                func_00130340(e, 202, f);
                func_00130578(e, 203, f);
                break;
            case 206:
                f = v[1];
                func_00130340(e, 207, f);
                func_00130578(e, 0, f);
                break;
            }
        } else if (v[0] < -0.7999999523162842f) {
            v[0] = -1.0f;
            v[3] = 0.5f;
            v[1] = 0.0f;
            v[2] = 0.0f;
            switch (e->x164) {
            case 0:
                f = v[1];
                func_00130340(e, 205, f);
                func_00130578(e, 206, f);
                break;
            case 203:
                f = v[1];
                func_00130340(e, 204, f);
                func_00130578(e, 0, f);
                break;
            }
        } else {
            func_002675a8(v, (*(f32 (*)[0x4])&D_002C58B0));
            switch (e->x164) {
            case 203:
                f = 0.0f;
                func_00130340(e, 204, f);
                func_00130578(e, 0, f);
                break;
            case 206:
                f = 0.0f;
                func_00130340(e, 207, f);
                func_00130578(e, 0, f);
                break;
            }
        }
        switch (e->x164) {
        case 0:
        case 202:
        case 204:
        case 205:
        case 207:
            v[3] *= 0.7f;
            break;
        }
    } else {
        func_002675a8(v, (*(f32 (*)[0x4])&D_002C58A0));
        switch (e->x164) {
        case 209:
            v[0] = 1.0f;
            v[3] = 2.0f;
            break;
        case 210:
            v[0] = -1.0f;
            v[3] = 2.0f;
            break;
        }
    }
    func_002675a8(e->x20, v);
    if (func_0014efe0(e, 1)) {
        for (i = 0; i < 3; i++) {
            if (D_002BC0F0.i[i + 4] < D_003519E0[i + 4]) D_002BC0F0.i[i + 4]++;
            else if (D_003519E0[i + 4] < D_002BC0F0.i[i + 4]) D_002BC0F0.i[i + 4]--;
        }
    }
}
#undef func_00130340
#undef func_00130578

/* func_001584c0 (from hand/nostrict/text_00150000_h58.c). */
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
typedef struct Actor_584c0 { ACT_BODY(S144) } Act;
void func_00267518(void *, void *, void *);
void func_00267560(void *, void *, f32);
void func_00137688(void *, f32);
extern f32 D_002BBDFC;
void func_00121fc4(void *, void *);
extern V4 D_00351A20;
V4 D_005516D0 ALIGNED(16);
void func_002673b8(void *, void *);
void func_00267370(void *, void *, void *);
f32 func_001376e8(void *, void *);
/* ---- func_001584c0 ---- */
void func_001584c0(Act *a, V4 *o) {
    V4 m;
    V4 t;
    f32 f;
    if (a->x20.w > 0.0f) {
        func_00267560(o, &a->x20, a->x20.w * D_002BBDFC);
        func_00267518(o, o, &a->x3c0);
        func_00121fc4(o, o);
    } else {
        func_00121fc4(o, &a->x3c0);
        o->w -= D_002BBDFC * 0.199999988079071044921875f;
    }
    if (o->w < 0.0f) f = 0.0f;
    else if (o->w > 20.0f) f = 20.0f;
    else f = o->w;
    func_00267560(&a->x3c0, o, f);
    func_002673b8(&m, &a->x148->v160);
    func_00267370(o, &D_00351A20, &m);
    func_002673b8(o, o);
    func_00267560(o, o, a->x3c0.x);
    func_00267518(&t, o, &a->x148->v160);
    func_00137688(a, func_001376e8(a, &t));
    func_00267560(o, o, D_002BBDFC);
    func_002675a8(&D_005516D0, o);
}
#undef ACT_BODY

