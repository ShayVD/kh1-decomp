/* Likely the Trinity marks, without strict aliasing (docs/modules.md
 * "Session 52"; the name is a guess, see trinity.c): func_00158780 tests a
 * mark kind against the player and the partners, func_00158960 picks the
 * best mark in reach, func_00158c78 says when one may be used, func_00158ec8
 * is the state task (D_00351A48) that loads "xl_limit.dat" and runs the
 * code at D_00F20000.  Read from the code, not proved by a boot. */
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
#include "data/bss_0055.h"
#include "data/types/nostrict_text_00150000_h35.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_003519E0.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E3168.h"
#include "data/pieces/D_002E2790.h"
#include "data/types/nostrict_text_00150000_h58.h"

/* func_00158780 (from hand/nostrict/text_00150000_h58.c). */
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
typedef struct Actor_58780 { ACT_BODY(S144) } Act;
void func_00267530(void *, void *, void *);
f32 func_00267390(void *, void *);
typedef struct { u8 pad[0xe]; u16 xe; } R478c8;
R478c8 *func_001478c8(s32);
f32 func_0012ed88(Act *, void *, V4 *, V4 *);
s32 func_00153d78(Act *);
s32 func_0012f040(Act *, s32);
s32 func_00141288(Act *, s32);
/* ---- func_00158780 ---- */
extern Act *D_002E26A0_58780[3] __asm__("D_002E26A0");
#define D_002E26A0 D_002E26A0_58780
s32 func_00158780(s32 k) {
    V4 m;
    V4 d;
    Act *p = D_002E26A0[0];
    R478c8 *r = func_001478c8(D_00351A30.p2[k].b);
    s32 i;
    f32 f = func_0012ed88(p, &D_002E31B0, &m, &d);
    if (r->xe <= f) return 0;
    switch (D_00351A30.p2[k].b) {
    case 75:
        if (p->pos.y - m.y > 160.0f) return 0;
        break;
    case 90:
        if (p->pos.y - m.y < 160.0f) return 0;
        break;
    case 82:
        for (i = 1; i < 3; i++) {
            if (!D_002E26A0[i] || func_00153d78(D_002E26A0[i]) || !func_0012f040(D_002E26A0[i], -1)) return 0;
            func_00267530(&d, &D_002E26A0[i]->pos, &D_002E26A0[0]->pos);
            if (func_00267390(&d, &d) > 250000.0f) return 0;
        }
        break;
    }
    return func_00141288(p, (*(Cfg_308cdc **)&D_00308CDC)->hF4[k]) ? 2 : 1;
}
#undef D_002E26A0
#undef ACT_BODY

/* func_00158960 (from hand/nostrict/text_00150000_h58.c). */
s32 func_0012cc38(s32, s32);
s32 func_00122ff8(void *);
extern s16 D_002C595A;
extern s32 D_00351A48;
extern u8 D_00351A40[];
extern u32 D_005516EC;
void func_0012ccb0(s32);
/* ---- func_00158960 ---- */
extern Act *D_002E26A0_58960[3] __asm__("D_002E26A0");
#define D_002E26A0 D_002E26A0_58960
void func_00158960(void) {
    s32 i, k, r, best, bk;
    if (D_002C595A & 1) return;
    if ((D_002E31A8 >> 1) & 1) return;
    if (D_002E26A0[0]->x70) return;
    if (D_00351A48 != 5) return;
    if (!func_00122ff8(D_002E31B0.f0)) return;
    if (((s32)(((Act *) D_002E31B0.f0)->x370 >> 37) & 3) != 2) return;
    best = 0;
    bk = -1;
    for (i = 0; i < 5; i++) {
        k = D_00351A40[i];
        if (D_005516EC & (1 << k)) {
            r = func_00158780(k);
            if (best < r) {
                best = r;
                bk = k;
            }
        }
    }
    if (bk >= 0 && func_0012cc38(3, D_00351A30.p2[bk].b) && best != 2) func_0012ccb0(3);
}
#undef D_002E26A0

/* func_00158b88 (from hand/nostrict/text_00150000_h35.c). */
s32 D_00F20000(); /* code at a fixed address (overlay) */
s32 func_00158af0(s32, s32);
/* ---- func_00158b88 (switch jump table) ---- */
s32 func_00158b88(s32 a, u8 *b) {
    switch (*b) {
    case 0x4B:
        return func_00158af0(a, 0);
    case 0x4D:
    case 0x4E:
        return D_00F20000(7, 0);
    case 0x57:
        return func_00158af0(a, 1);
    case 0x58:
    case 0x59:
        return D_00F20000(8, 0);
    case 0x5E:
        return func_00158af0(a, 2);
    case 0x5F:
    case 0x60:
        return D_00F20000(9, 0);
    case 0x5A:
        return func_00158af0(a, 3);
    case 0x5B:
        return D_00F20000(11, 0);
    case 0x52:
        func_00158af0(a, 4);
        break;
    }
}

/* func_00158c78 (from hand/nostrict/text_00150000_h35.c). */
extern u32 D_002C5958;
s32 func_001140a0(void);
/* ---- func_00158c78 ---- */
s32 func_00158c78(void) {
    s32 m = func_001140a0();
    s32 r = 0;
    if (!(D_002C5958 & 0x92000)) {
        if (!((D_002E31A8 >> 1) & 1)) {
            if (!(D_00304BE8->f874 & 0x40)) {
                if (!((((u32)D_0037A378) >> 1) & 1)) {
                    if (m == 0 || m == 2 || (m == 3 && ((((u32)D_0037A378) >> 4) & 1))) r = 1;
                }
            }
        }
    }
    return r;
}

/* func_00158df8 (from hand/nostrict/text_00150000_h35.c). */
extern s32 *D_005516E4;
extern char D_0048E718[];
s32 func_00158d30(void);
void func_00155be0(s32);
void func_001763f0(void *);
s32 func_00120748(char *, void *, void (*)(void), s32);
void func_00158db0(void);
/* ---- func_00158df8 ---- */
void func_00158df8(s32 a, s32 b, s32 *t) {
    s32 i;
    s32 *p;
    if (func_00158d30()) {
        D_005516E4 = t;
        D_005516E8 = (s32)t + t[1];
        func_00155be0(D_005516E8);
        for (i = 0, p = t + 1; i < 5; i++, p++) {
            if (p[2] - p[1] > 0) func_001763f0((u8 *)t + p[1]);
        }
        func_00120748(D_0048E718, (void *)D_00F20000, func_00158db0, 0);
    } else {
        D_00351A48 = 0;
    }
}

/* func_00158ec8 (from hand/nostrict/text_00150000_h58.c). */
typedef union { u32 w; struct { u32 b0:1; u32 b1:1; u32 p2:14; u32 b16:1; u32 p17:6; u32 b23:1; u32 b24:1; u32 b25:1; u32 p26:6; } b; } F5958;
typedef struct { u8 pad[0x1c]; s32 x1c; } R16E4;
void *func_00155a50(void);
s32 func_00146878(void);
s32 func_00157090(void);
void func_00158d70();
s32 func_00146b90(void *, s32, void *, void *);
#define D_002C5958 (*(F5958 (*)) &D_002C5958)
#define D_00F20000 ((s32 (*)(s32, s32)) D_00F20000)
#define func_00120748 ((s32 (*)(char *, void *, void *, s32)) func_00120748)
#define D_005516E4 ((R16E4 *) D_005516E4)
/* ---- func_00158ec8 ---- */
s32 func_00158ec8(void) {
    D_002C5958.b.b25 = 0;
    if (D_002C5958.b.b16) {
        if (D_002C5958.b.b23) {
            D_002C5958.b.b16 = 0;
            D_002C5958.b.b23 = 0;
        } else {
            if (D_00F20000(5, 0)) return 0;
            D_002C5958.b.b23 = 1;
        }
    } else
    switch (D_00351A48) {
    case 0:
        D_00351A48 = 1;
        break;
    case 1:
        if (func_00158c78()) {
            func_00120748("xl_limit.dat", func_00155a50(), func_00158df8, 0);
            D_00351A48 = 2;
            D_002C5958.b.b25 = 1;
        }
        break;
    case 2:
    case 4:
        D_002C5958.b.b25 = 1;
        break;
    case 3:
        if (!func_00158d30()) {
            D_00351A48 = 0;
        } else if (func_00146878() && !func_00157090()) {
            D_00351A48 = 4;
            if (!func_00146b90((u8 *)D_005516E4 + D_005516E4->x1c, -7, func_00158d70, 0)) D_00351A48 = 0;
        }
        D_002C5958.b.b25 = 1;
        break;
    case 5:
        if (func_00158d30()) return 0;
        D_00351A48 = 0;
        break;
    case 6:
        return 4;
    default:
        return 0;
    }
    return 0;
}
#undef D_002C5958
#undef D_00F20000
#undef func_00120748
#undef D_005516E4

