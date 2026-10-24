/* Likely the summons (a guess from the code): func_0013a910 asks whether
 * summon n is allowed (the leader's class flag, MP against the tuning table,
 * the world / room), the state D_0052AE54 loads the summon's two files named
 * from D_00304B00[D_0052AE50] (func_0013b3d0; code at D_00F20000), the
 * summon object D_0052AE38 of class 40 (func_0013bf20 registers it), the
 * party swap and its end (func_0013bb60, func_0013bd08), the fade
 * func_0013ab30. Flag mode: nostrict (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0052.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/nostrict_text_00130000_h55.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_0037A378.h"
#include "vm/script_vm.h"
#include "data/types/nostrict_text_00130000_h32.h"

/* func_0013b050 (from hand/nostrict/text_00130000_s6_06.c). */
extern u32 *D_0052AE38;
extern s32 D_0052AE60;
void func_0014f658(void *, s32);
s32 func_00130340(void *, s32, f32);
void func_001373f8(void *o, f32 f);
s32 func_00148768(s32, s32, void *, s32, f32);
void func_00124ce0(f32);
void func_001336d8(void);
void func_002414a8(s32 a, s32 b);
void func_00145080(s32 a, s32 b);
void *func_0011f090(void *, s32, void *);
void func_0011ef10(s32, void *);
s32 func_0013ab30();
void func_0013abf8();
s32 func_0013b050(void) {
    s32 i;
    s32 *pp;
    func_0014f658(D_0052AE38, 40);
    func_00130340(D_0052AE38, 0x1010040, 20.0f);
    func_001373f8(D_0052AE38, 0.0f);
    *D_0052AE38 |= 0x200000;
    pp = &D_0052AE60;
    *pp = func_00148768(D_00350CE0, 0, D_0052AE38, 28, 0.5f);
    func_00124ce0(53.0f);
    func_001336d8();
    func_002414a8(0, 3);
    func_002414a8(1, 3);
    func_002414a8(2, 3);
    func_00145080(1, 4);
    for (i = 0; i < 2; i++) {
        if (D_002E26A0[i + 1]) *((u32 *)D_002E26A0[i + 1]) |= 0x1000000;
    }
    func_0011f090(D_0052AD68, 0, func_0013ab30);
    func_0011ef10(100000, func_0013abf8);
    return 1;
}

/* func_0013b238 (from hand/nostrict/text_00130000_h55.c). */
typedef struct { u8 pad[8]; f32 x8; f32 xc; } W55Dim;
typedef struct { u8 pad[0x10]; W55Dim *x10; } W55Mdl;
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0x4c - 0x8]; u16 x4c; u8 pad4e[0x54 - 0x4e]; s8 x54; } W55Inf;
typedef struct { u8 pad[0xcc]; f32 xcc; } W55Mv;
typedef struct { f32 *x0; } W55Fx;
typedef struct Actor_3b238 {
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
typedef struct { s32 x0, x4, x8, xc, x10, x14, x18; } W55Hdr;
extern u32 D_002C5958;
extern u32 D_002C5978;
f32 D_0052AE40[4] ALIGNED(16);  /* moved from hand/nostrict/text_00130000_h55.c (session 53) */
extern W55Hdr *D_0052AE58;
W55Ob *func_001230a0(W55Ob *p);
void func_00123438(W55Ob *p, u32 f);
void func_00123a88(s32 a, f32 *b);
void func_00131498(W55Ob *o, void *a);
void func_00137448(W55Ob *o);
void func_00176310(s32 a);
void func_00176388(s32 a);
void func_001763a0(s32 a);
#define D_0052AE38 (*(W55Ob *(*)) &D_0052AE38)
#define func_001373f8 ((void (*)(W55Ob *o, f32 f)) func_001373f8)
s32 func_0013b238(void) {
    W55Ob *p = 0;
    W55Ob **pl;
    W55Hdr **ph;
    u32 *fl;
    u32 f;
    while ((p = func_001230a0(p))) {
        f = p->x0;
        if (p == D_0052AE38) {
            f |= 0x30;
            f &= ~2;
            func_001373f8(p, 0.0f);
            p->x370.x |= 1UL << 52;
        } else {
            f &= ~0x8000;
            func_00137448(p);
            PlatVu0CopyVector(p->x120, (*(f32 (*)[0x4])&D_002C58B0));
        }
        func_00123438(p, f);
    }
    pl = &D_0052AE38;
    PlatVu0CopyVector(D_0052AE40, (*pl)->pos);
    D_0052AE40[3] = (*pl)->x3c;
    func_00123a88((*pl)->x4, (*(f32 (*)[0x4])&D_002C58B0));
    func_00176310(D_0052AE60);
    func_001763a0(0);
    func_00176388(1);
    fl = &D_002C5958;
    *fl = (*fl & ~0x100000) | 0x4000;
    if ((s32)((D_002C5978 >> 8) & 3) < 2) {
        ph = &D_0052AE58;
        if ((*ph)->x14 != (*ph)->x10) {
            func_00131498(*pl, (u8 *)*ph + (*ph)->xc);
            func_001c4d90((s32)((u8 *)*ph + (*ph)->x10), (s32)((u8 *)*ph + (*ph)->x14), (s32)((u8 *)*ph + (*ph)->x18));
        }
    }
    return 4;
}
#undef D_0052AE38
#undef func_001373f8

/* func_0013b4e8 (from hand/nostrict/text_00130000_h32.c). */
typedef struct {
    u8 pad00[0x30];
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3c;
} W32Spr;
typedef struct {
    u16 flags;
    u8 pad02[0x10 - 0x2];
    f32 x10;
} W32Fade;
extern f32 D_002BBDFC;
W32Spr *func_001226f0(s32 a, s32 b, s32 c);
void func_00122768(W32Spr *s);
W32Spr *D_0052AD54 ALIGNED(4);  /* moved from hand/nostrict/text_00130000_h32.c (session 53) */
void func_00100ab0(void);
s32 func_0013b4e8(W32Fade *f) {
    f32 t;
    if (f->flags & 0x10) {
        W32Spr *s = func_001226f0(1, 9, 0);
        D_0052AD54 = s;
        s->x30 = s->x34 = s->x38 = 0.0f;
        D_0052AD54->x3c = 1.0f;
        func_00100ab0();
        f->x10 = 60.0f;
    }
    f->x10 -= D_002BBDFC;
    t = f->x10 / 60.0f;
    if (t <= 0.0f) {
        func_00122768(D_0052AD54);
        return 4;
    }
    D_0052AD54->x30 = D_0052AD54->x34 = D_0052AD54->x38 = 1.0f - t;
    return 0;
}

/* func_0013b5d8 (from hand/nostrict/text_00130000_h55.c). */
typedef struct Actor_3b5d8 {
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
} W55Ob_3b5d8;
void func_00123460(W55Ob_3b5d8 *p);
void func_00124d08(void);
void func_00131500(W55Ob_3b5d8 *o);
void func_00133708(void);
#define D_0052AE38 (*(W55Ob_3b5d8 *(*)) &D_0052AE38)
#define func_0011f090 ((void (*)(void *a, s32 b, void *c)) func_0011f090)
#define func_001230a0 ((W55Ob_3b5d8 *(*)(W55Ob_3b5d8 *p)) func_001230a0)
#define func_00130340 ((void (*)(void *o, s32 a, f32 f)) func_00130340)
#define func_0014f658 ((s32 (*)(void *, s32)) func_0014f658)
void func_0013b5d8(void) {
    W55Ob_3b5d8 *p;
    W55Ob_3b5d8 **pl;
    u32 *fl;
    func_00133708();
    func_00124d08();
    func_002414a8(0, 1);
    for (p = func_001230a0(0); p; p = func_001230a0(p)) {
        if ((s32)(p->x370.x >> 33) & 1) continue;
        if (p == D_002E26A0[1]) continue;
        if (p == D_002E26A0[2]) continue;
        func_00123460(p);
    }
    pl = &D_0052AE38;
    func_0014f658(*pl, 0);
    func_00123a88((*pl)->x4, D_0052AE40);
    func_00131500(*pl);
    func_00130340(*pl, 0x40000000, 0.0f);
    (*pl)->x370.x &= ~(1UL << 52);
    (*pl)->x0 &= ~0x200000;
    (*pl)->x444 = 0;
    func_00176388(0);
    fl = &D_002C5958;
    *fl &= ~0x4000;
    func_00145080(0, 4);
    func_0011f090(D_0052AD68, 0, func_0013b4e8);
}
#undef D_0052AE38
#undef func_0011f090
#undef func_001230a0
#undef func_00130340
#undef func_0014f658

/* func_0013b740 (from hand/nostrict/text_00130000_h55.c). */
typedef struct Actor_3b740 {
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
} W55Ob_3b740;
typedef struct { s32 x0, x4, x8, xc, x10; } W55Hd5;
W55Ob_3b740 *D_0052AE3C ALIGNED(4);  /* moved from hand/nostrict/text_00130000_h55.c (session 53) */
extern s32 D_0052AE54;
extern W55Hd5 *D_0052AE5C;
void D_00F20000(s32 a, void *b);
void func_001247e8(W55Ob_3b740 *p);
s32 func_001ecfd8(void);
#define D_0052AE38 (*(W55Ob_3b740 *(*)) &D_0052AE38)
#define func_001230a0 ((W55Ob_3b740 *(*)(W55Ob_3b740 *p)) func_001230a0)
#define func_00130340 ((void (*)(void *o, s32 a, f32 f)) func_00130340)
#define func_00131498 ((void (*)(W55Ob_3b740 *o, void *a)) func_00131498)
#define func_00131500 ((void (*)(W55Ob_3b740 *o)) func_00131500)
s32 func_0013b740(void) {
    W55Ob_3b740 *p;
    W55Ob_3b740 **q;
    W55Ob_3b740 **pl;
    W55Hd5 **ph;
    if ((((u32)D_0037A378) >> 2) & 1) goto fail;
    if (D_0052AE54 != 4 || func_001ecfd8()) {
    fail:
        return 0;
    }
    func_0013b5d8();
    D_0052AE3C = 0;
    for (p = 0; (p = func_001230a0(p));) {
        if (((u8 *)p)[6] == 7) {
            D_0052AE3C = p;
            break;
        }
    }
    q = &D_0052AE3C;
    if (*q) {
        if (D_0052AE5C->x8 - D_0052AE5C->x4 > 0) {
            func_00131498(*q, (u8 *)D_0052AE5C + D_0052AE5C->x4);
            func_00130340(*q, 0, 0.0f);
            (*q)->x0 &= ~0x30;
        }
        (*q)->x444 = 0;
    }
    if (((D_002C5978 >> 8) & 3) != 1) {
        ph = &D_0052AE5C;
        if ((*ph)->xc - (*ph)->x8 > 0) {
            W55Ob_3b740 **pm = &D_0052AE38;
            func_00131498(*pm, (u8 *)*ph + (*ph)->x8);
            func_00130340(*pm, 0, 0.0f);
        }
        D_00F20000(0, (*ph)->x10 - (*ph)->xc > 0 ? (u8 *)*ph + (*ph)->xc : 0);
        return 1;
    }
    func_001247e8(D_0052AE3C);
    pl = &D_0052AE38;
    func_00131500(*pl);
    func_00130340(*pl, 0x40000000, 0.0f);
    return 1;
}
#undef D_0052AE38
#undef func_001230a0
#undef func_00130340
#undef func_00131498
#undef func_00131500

/* func_0013be00 (from hand/nostrict/text_00130000_h32.c). */
typedef struct {
    f32 dur;
    s32 (*fn)(void);
} W32Step;
typedef struct {
    W32Step *cur;
    s32 n;
    s32 idx;
    f32 t;
} W32Seq;
s32 func_0013be00(W32Seq *s) {
    W32Step *nx;
    if (s->idx == 0 && s->t == 0.0f && s->cur->fn) s->cur->fn();
    s->t += D_002BBDFC;
    while (s->cur->dur <= s->t) {
        if (s->idx + 1 >= s->n) return 0;
        nx = s->cur + 1;
        if (nx->fn && nx->fn() == 0) return 1;
        s->cur = nx;
        s->t = 0.0f;
        s->idx++;
    }
    return 1;
}

